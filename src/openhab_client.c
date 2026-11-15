/*
 * HTTP client – the C counterpart of python-openhab-rest-client/openhab/Client.py.
 */
#include "oh_internal.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#  include <windows.h>
#else
#  include <pthread.h>
#endif

/* ── small helpers ─────────────────────────────────────────────────────────── */

char* oh_strdup(const char* s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char* d = (char*)malloc(n);
    if (d) memcpy(d, s, n);
    return d;
}

int oh_buf_add(oh_buf* b, const char* s, size_t n) {
    if (b->len + n + 1 > b->cap) {
        size_t cap = b->cap ? b->cap : 256;
        while (cap < b->len + n + 1) cap *= 2;
        char* d = (char*)realloc(b->data, cap);
        if (!d) return 0;
        b->data = d;
        b->cap = cap;
    }
    memcpy(b->data + b->len, s, n);
    b->len += n;
    b->data[b->len] = '\0';
    return 1;
}

void oh_buf_free(oh_buf* b) {
    free(b->data);
    b->data = NULL;
    b->len = b->cap = 0;
}

static int starts_with(const char* s, const char* p) { return strncmp(s, p, strlen(p)) == 0; }

static int ieq_prefix(const char* s, const char* p) {
    for (; *p; s++, p++)
        if (tolower((unsigned char)*s) != tolower((unsigned char)*p)) return 0;
    return 1;
}

#ifdef _WIN32
static INIT_ONCE curl_once = INIT_ONCE_STATIC_INIT;
static BOOL CALLBACK curl_init_cb(PINIT_ONCE o, PVOID p, PVOID* c) {
    (void)o; (void)p; (void)c;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    return TRUE;
}
void oh_curl_init_once(void) { InitOnceExecuteOnce(&curl_once, curl_init_cb, NULL, NULL); }
#else
static pthread_once_t curl_once = PTHREAD_ONCE_INIT;
static void curl_init_cb(void) { curl_global_init(CURL_GLOBAL_DEFAULT); }
void oh_curl_init_once(void) { pthread_once(&curl_once, curl_init_cb); }
#endif

/* ── URL building ──────────────────────────────────────────────────────────── */

char* oh_quote(const char* s, const char* safe) {
    static const char hex[] = "0123456789ABCDEF";
    oh_buf b = {0};
    if (!s) s = "";
    oh_buf_add(&b, "", 0);
    for (const unsigned char* p = (const unsigned char*)s; *p; p++) {
        if (isalnum(*p) || strchr("_.-~", *p) || (safe && *p < 128 && strchr(safe, *p))) {
            oh_buf_add(&b, (const char*)p, 1);
        } else {
            char e[3] = {'%', hex[*p >> 4], hex[*p & 15]};
            oh_buf_add(&b, e, 3);
        }
    }
    return b.data;
}

char* oh_build_url(const openhab_client_t* c, const char* resource_path) {
    if (starts_with(resource_path, "http://") || starts_with(resource_path, "https://"))
        return oh_strdup(resource_path);
    oh_buf path = {0};
    oh_buf_add(&path, "", 0);
    if (resource_path[0] != '/') oh_buf_add(&path, "/", 1);
    oh_buf_add(&path, resource_path, strlen(resource_path));
    oh_buf out = {0};
    oh_buf_add(&out, c->url, strlen(c->url));
    const char* p = path.data;
    if (!(strcmp(p, "/rest") == 0 || starts_with(p, "/rest/") || starts_with(p, "/rest?")))
        oh_buf_add(&out, "/rest", 5);
    /* "#" is valid inside openHAB UIDs but would start a URL fragment */
    const char* q = strchr(p, '?');
    for (const char* x = p; *x && (!q || x < q); x++) {
        if (*x == '#') oh_buf_add(&out, "%23", 3);
        else oh_buf_add(&out, x, 1);
    }
    if (q) oh_buf_add(&out, q, strlen(q));
    oh_buf_free(&path);
    return out.data;
}

static void add_param(oh_buf* b, const char* key, const cJSON* v) {
    char num[64];
    const char* text;
    if (cJSON_IsNull(v)) return;
    if (cJSON_IsBool(v)) {
        text = cJSON_IsTrue(v) ? "true" : "false";
    } else if (cJSON_IsNumber(v)) {
        double d = v->valuedouble;
        if (d == floor(d) && fabs(d) < 1e15) snprintf(num, sizeof num, "%.0f", d);
        else snprintf(num, sizeof num, "%.17g", d);
        text = num;
    } else if (cJSON_IsString(v)) {
        text = v->valuestring;
    } else {
        return;
    }
    char* k = oh_quote(key, "");
    char* t = oh_quote(text, "");
    oh_buf_add(b, b->len ? "&" : "?", 1);
    oh_buf_add(b, k, strlen(k));
    oh_buf_add(b, "=", 1);
    oh_buf_add(b, t, strlen(t));
    free(k);
    free(t);
}

char* oh_query_string(const cJSON* params) {
    oh_buf b = {0};
    oh_buf_add(&b, "", 0);
    if (cJSON_IsObject(params)) {
        for (const cJSON* it = params->child; it; it = it->next) {
            if (cJSON_IsArray(it)) {
                for (const cJSON* e = it->child; e; e = e->next) add_param(&b, it->string, e);
            } else {
                add_param(&b, it->string, it);
            }
        }
    }
    return b.data;
}

/* ── client ────────────────────────────────────────────────────────────────── */

void oh_apply_auth(CURL* h, const openhab_client_t* c) {
    if (!c->verify) {
        curl_easy_setopt(h, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(h, CURLOPT_SSL_VERIFYHOST, 0L);
    }
    if (!(c->token && c->token[0]) && c->username && c->username[0] && c->password && c->password[0]) {
        curl_easy_setopt(h, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
        curl_easy_setopt(h, CURLOPT_USERNAME, c->username);
        curl_easy_setopt(h, CURLOPT_PASSWORD, c->password);
    }
    curl_easy_setopt(h, CURLOPT_USERAGENT, "c-openhab-rest-client/" OPENHAB_CLIENT_VERSION);
    curl_easy_setopt(h, CURLOPT_NOSIGNAL, 1L);
}

static struct curl_slist* auth_header(struct curl_slist* l, const openhab_client_t* c) {
    if (c->token && c->token[0]) {
        size_t n = strlen(c->token) + 32;
        char* h = (char*)malloc(n);
        if (h) {
            snprintf(h, n, "Authorization: Bearer %s", c->token);
            l = curl_slist_append(l, h);
            free(h);
        }
    }
    return l;
}

openhab_client_t* openhab_client_new_(const char* url, openhab_client_args a) {
    oh_curl_init_once();
    openhab_client_t* c = (openhab_client_t*)calloc(1, sizeof *c);
    if (!c) return NULL;
    c->url = oh_strdup(url ? url : "");
    size_t n = strlen(c->url);
    while (n && c->url[n - 1] == '/') c->url[--n] = '\0';
    c->username = oh_strdup(a.username);
    c->password = oh_strdup(a.password);
    c->token = oh_strdup(a.token);
    c->timeout = a.timeout > 0 ? a.timeout : OPENHAB_DEFAULT_TIMEOUT;
    c->verify = a.verify != OPENHAB_FALSE;
    openhab_client_login(c);
    return c;
}

openhab_client_t* openhab_client_create(const char* url, const char* username,
                                        const char* password, const char* token) {
    return openhab_client_new(url, .username = username, .password = password, .token = token);
}

void openhab_client_destroy(openhab_client_t* c) {
    if (!c) return;
    free(c->url);
    free(c->username);
    free(c->password);
    free(c->token);
    free(c);
}

static size_t discard_cb(char* p, size_t s, size_t n, void* u) { (void)p; (void)u; return s * n; }

int openhab_client_login(openhab_client_t* c) {
    c->is_cloud = strcmp(c->url, "https://myopenhab.org") == 0 ||
                  strcmp(c->url, "https://home.myopenhab.org") == 0;
    c->is_logged_in = 0;
    c->last_error[0] = '\0';
    char* url = (char*)malloc(strlen(c->url) + 8);
    if (!url) return 0;
    sprintf(url, "%s/rest/", c->url);
    CURL* h = curl_easy_init();
    struct curl_slist* hd = auth_header(NULL, c);
    char err[CURL_ERROR_SIZE] = "";
    curl_easy_setopt(h, CURLOPT_URL, url);
    curl_easy_setopt(h, CURLOPT_HTTPHEADER, hd);
    curl_easy_setopt(h, CURLOPT_WRITEFUNCTION, discard_cb);
    curl_easy_setopt(h, CURLOPT_TIMEOUT_MS, (long)(c->timeout * 1000));
    curl_easy_setopt(h, CURLOPT_ERRORBUFFER, err);
    curl_easy_setopt(h, CURLOPT_FOLLOWLOCATION, 1L);
    oh_apply_auth(h, c);
    CURLcode rc = curl_easy_perform(h);
    long status = 0;
    curl_easy_getinfo(h, CURLINFO_RESPONSE_CODE, &status);
    if (rc != CURLE_OK)
        snprintf(c->last_error, sizeof c->last_error, "Connection error occurred: %s",
                 err[0] ? err : curl_easy_strerror(rc));
    else if (status >= 400)
        snprintf(c->last_error, sizeof c->last_error, "HTTP error occurred: %ld for url: %s",
                 status, url);
    else
        c->is_logged_in = 1;
    curl_slist_free_all(hd);
    curl_easy_cleanup(h);
    free(url);
    return c->is_logged_in;
}

int openhab_client_is_logged_in(const openhab_client_t* c) { return c && c->is_logged_in; }
int openhab_client_is_cloud(const openhab_client_t* c) { return c && c->is_cloud; }
const char* openhab_client_base_url(const openhab_client_t* c) { return c ? c->url : NULL; }
const char* openhab_client_last_error(const openhab_client_t* c) {
    return c && c->last_error[0] ? c->last_error : NULL;
}

/* ── requests ──────────────────────────────────────────────────────────────── */

typedef struct {
    oh_buf body;
    char reason[128];
    char content_type[256];
    char location[1024];
} reply;

static size_t body_cb(char* p, size_t s, size_t n, void* u) {
    return oh_buf_add(&((reply*)u)->body, p, s * n) ? s * n : 0;
}

static void header_value(const char* line, size_t n, char* dst, size_t dn) {
    const char* v = memchr(line, ':', n);
    if (!v) return;
    v++;
    while (v < line + n && (*v == ' ' || *v == '\t')) v++;
    size_t len = (size_t)(line + n - v);
    while (len && (v[len - 1] == '\r' || v[len - 1] == '\n' || v[len - 1] == ' ')) len--;
    if (len >= dn) len = dn - 1;
    memcpy(dst, v, len);
    dst[len] = '\0';
}

static size_t header_cb(char* line, size_t s, size_t n, void* u) {
    reply* r = (reply*)u;
    size_t len = s * n;
    if (len > 5 && strncmp(line, "HTTP/", 5) == 0) {
        /* status line: HTTP/1.1 404 Not Found – a new response starts (redirects) */
        r->content_type[0] = r->location[0] = r->reason[0] = '\0';
        const char* sp = memchr(line, ' ', len);
        if (sp) sp = memchr(sp + 1, ' ', (size_t)(line + len - sp - 1));
        if (sp) {
            size_t k = (size_t)(line + len - sp - 1);
            while (k && (sp[k] == '\r' || sp[k] == '\n')) k--;
            if (k >= sizeof r->reason) k = sizeof r->reason - 1;
            memcpy(r->reason, sp + 1, k);
            r->reason[k] = '\0';
        }
    } else if (ieq_prefix(line, "content-type:")) {
        header_value(line, len, r->content_type, sizeof r->content_type);
    } else if (ieq_prefix(line, "location:")) {
        header_value(line, len, r->location, sizeof r->location);
    }
    return len;
}

void oh_http_error_text(char* dst, size_t n, int status, const char* reason, const char* url,
                        const char* body) {
    char message[256] = "";
    cJSON* j = body ? cJSON_Parse(body) : NULL;
    if (j) {
        if (cJSON_IsObject(j)) {
            const cJSON* e = cJSON_GetObjectItemCaseSensitive(j, "error");
            if (cJSON_IsObject(e)) {
                const cJSON* m = cJSON_GetObjectItemCaseSensitive(e, "message");
                if (cJSON_IsString(m)) snprintf(message, sizeof message, "%s", m->valuestring);
            } else if (cJSON_IsString(e)) {
                snprintf(message, sizeof message, "%s", e->valuestring);
            }
        }
        cJSON_Delete(j);
    } else if (body) {
        while (isspace((unsigned char)*body)) body++;
        snprintf(message, sizeof message, "%.200s", body);
        size_t k = strlen(message);
        while (k && isspace((unsigned char)message[k - 1])) message[--k] = '\0';
    }
    snprintf(dst, n, "%d %s: %s for url: %s%s%s%s", status,
             status < 500 ? "Client Error" : "Server Error", reason ? reason : "", url,
             message[0] ? " (" : "", message, message[0] ? ")" : "");
}

void oh_mark_status(cJSON* obj) {
    /* objects do not use valuedouble – it marks a StatusResponse */
    if (obj) obj->valuedouble = -7777.25;
}

int openhab_is_status(const cJSON* r) {
    return cJSON_IsObject(r) && r->valuedouble == -7777.25;
}

static int only_space(const char* s) {
    for (; s && *s; s++)
        if (!isspace((unsigned char)*s)) return 0;
    return 1;
}

void oh_request(openhab_client_t* c, const char* verb, const char* resource_path,
                const cJSON* headers, const cJSON* data, const cJSON* params, oh_response* out) {
    memset(out, 0, sizeof *out);
    oh_curl_init_once();
    char* base = oh_build_url(c, resource_path ? resource_path : "/");
    char* query = oh_query_string(params);
    char* url = (char*)malloc(strlen(base) + strlen(query) + 2);
    if (strchr(base, '?') && query[0]) sprintf(url, "%s&%s", base, query + 1);
    else sprintf(url, "%s%s", base, query);
    free(base);
    free(query);

    /* body: strings as they are, everything else as JSON */
    char* body = NULL;
    int body_is_json = 0;
    if (data && !cJSON_IsNull(data)) {
        if (cJSON_IsString(data)) {
            body = oh_strdup(data->valuestring);
            const char* s = body;
            while (isspace((unsigned char)*s)) s++;
            body_is_json = *s == '{' || *s == '[';
        } else {
            body = cJSON_PrintUnformatted(data);
            body_is_json = 1;
        }
    }

    struct curl_slist* hl = auth_header(NULL, c);
    int has_ct = 0;
    if (cJSON_IsObject(headers)) {
        for (const cJSON* h = headers->child; h; h = h->next) {
            if (!cJSON_IsString(h)) continue;
            if (ieq_prefix(h->string, "content-type") && strlen(h->string) == 12) has_ct = 1;
            size_t n = strlen(h->string) + strlen(h->valuestring) + 4;
            char* line = (char*)malloc(n);
            snprintf(line, n, "%s: %s", h->string, h->valuestring);
            hl = curl_slist_append(hl, line);
            free(line);
        }
    }
    if (body && body[0] && !has_ct)
        hl = curl_slist_append(hl, body_is_json ? "Content-Type: application/json"
                                                : "Content-Type: text/plain");
    if (!has_ct && !(body && body[0])) hl = curl_slist_append(hl, "Content-Type:");
    hl = curl_slist_append(hl, "Expect:");

    reply r;
    memset(&r, 0, sizeof r);
    char err[CURL_ERROR_SIZE] = "";
    CURL* h = curl_easy_init();
    curl_easy_setopt(h, CURLOPT_URL, url);
    curl_easy_setopt(h, CURLOPT_HTTPHEADER, hl);
    curl_easy_setopt(h, CURLOPT_WRITEFUNCTION, body_cb);
    curl_easy_setopt(h, CURLOPT_WRITEDATA, &r);
    curl_easy_setopt(h, CURLOPT_HEADERFUNCTION, header_cb);
    curl_easy_setopt(h, CURLOPT_HEADERDATA, &r);
    curl_easy_setopt(h, CURLOPT_ERRORBUFFER, err);
    curl_easy_setopt(h, CURLOPT_TIMEOUT_MS, (long)(c->timeout * 1000));
    curl_easy_setopt(h, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(h, CURLOPT_ACCEPT_ENCODING, "");
    oh_apply_auth(h, c);
    if (strcmp(verb, "post") == 0) {
        curl_easy_setopt(h, CURLOPT_POST, 1L);
    } else if (strcmp(verb, "put") == 0) {
        curl_easy_setopt(h, CURLOPT_CUSTOMREQUEST, "PUT");
    } else if (strcmp(verb, "delete") == 0) {
        curl_easy_setopt(h, CURLOPT_CUSTOMREQUEST, "DELETE");
    }
    if (strcmp(verb, "get") != 0) {
        curl_easy_setopt(h, CURLOPT_POSTFIELDS, body ? body : "");
        curl_easy_setopt(h, CURLOPT_POSTFIELDSIZE, (long)(body ? strlen(body) : 0));
    }
    oh_buf_add(&r.body, "", 0);
    CURLcode rc = curl_easy_perform(h);
    long status = 0;
    char* eff = NULL;
    curl_easy_getinfo(h, CURLINFO_RESPONSE_CODE, &status);
    curl_easy_getinfo(h, CURLINFO_EFFECTIVE_URL, &eff);
    out->status = (int)status;

    if (rc != CURLE_OK) {
        out->exc = 2;
        snprintf(out->message, sizeof out->message, "%s", err[0] ? err : curl_easy_strerror(rc));
    } else if (status >= 400) {
        out->exc = 1;
        oh_http_error_text(out->message, sizeof out->message, (int)status, r.reason,
                           eff ? eff : url, r.body.data);
    } else if (only_space(r.body.data)) {
        out->result = cJSON_CreateObject();
        cJSON_AddNumberToObject(out->result, "status", (double)status);
        if (r.location[0]) cJSON_AddStringToObject(out->result, "location", r.location);
        oh_mark_status(out->result);
    } else {
        if (strstr(r.content_type, "json")) out->result = cJSON_Parse(r.body.data);
        if (!out->result) out->result = cJSON_CreateString(r.body.data);
    }
    curl_easy_cleanup(h);
    curl_slist_free_all(hl);
    oh_buf_free(&r.body);
    free(body);
    free(url);
}

static cJSON* error_object(const oh_response* r) {
    char text[1200];
    if (r->exc == 1) snprintf(text, sizeof text, "HTTP error %d: %s", r->status, r->message);
    else snprintf(text, sizeof text, "Request error: %s", r->message);
    cJSON* o = cJSON_CreateObject();
    cJSON_AddStringToObject(o, "error", text);
    return o;
}

static cJSON* low_level(openhab_client_t* c, const char* verb, const char* endpoint,
                        const cJSON* headers, const cJSON* data, const cJSON* params) {
    oh_response r;
    oh_request(c, verb, endpoint, headers, data, params, &r);
    return r.exc ? error_object(&r) : r.result;
}

cJSON* openhab_client_get(openhab_client_t* c, const char* e, const cJSON* h, const cJSON* p) {
    return low_level(c, "get", e, h, NULL, p);
}
cJSON* openhab_client_post(openhab_client_t* c, const char* e, const cJSON* h, const cJSON* d,
                           const cJSON* p) {
    return low_level(c, "post", e, h, d, p);
}
cJSON* openhab_client_put(openhab_client_t* c, const char* e, const cJSON* h, const cJSON* d,
                          const cJSON* p) {
    return low_level(c, "put", e, h, d, p);
}
cJSON* openhab_client_delete(openhab_client_t* c, const char* e, const cJSON* h, const cJSON* d,
                             const cJSON* p) {
    return low_level(c, "delete", e, h, d, p);
}

/* ── results and JSON helpers ──────────────────────────────────────────────── */

int openhab_is_error(const cJSON* r) {
    return r == NULL || (cJSON_IsObject(r) && !openhab_is_status(r) &&
                         cJSON_GetObjectItemCaseSensitive(r, "error") != NULL);
}

const char* openhab_error(const cJSON* r) {
    if (!r) return "no result";
    if (!cJSON_IsObject(r) || openhab_is_status(r)) return NULL;
    const cJSON* e = cJSON_GetObjectItemCaseSensitive(r, "error");
    if (cJSON_IsString(e)) return e->valuestring;
    if (cJSON_IsObject(e)) {
        const cJSON* m = cJSON_GetObjectItemCaseSensitive(e, "message");
        if (cJSON_IsString(m)) return m->valuestring;
    }
    return e ? "error" : NULL;
}

cJSON* openhab_json_get(const cJSON* v, const char* path) {
    if (!v || !path) return (cJSON*)v;
    const cJSON* cur = v;
    char part[256];
    while (*path && cur) {
        size_t n = strcspn(path, ".");
        if (n >= sizeof part) return NULL;
        memcpy(part, path, n);
        part[n] = '\0';
        path += n;
        if (*path == '.') path++;
        if (cJSON_IsArray(cur)) {
            char* end;
            long i = strtol(part, &end, 10);
            if (*end) return NULL;
            if (i < 0) i += cJSON_GetArraySize(cur);
            cur = cJSON_GetArrayItem(cur, (int)i);
        } else if (cJSON_IsObject(cur)) {
            cur = cJSON_GetObjectItemCaseSensitive(cur, part);
        } else {
            return NULL;
        }
    }
    return (cJSON*)cur;
}

const char* openhab_json_str(const cJSON* v, const char* path) {
    const cJSON* x = openhab_json_get(v, path);
    return cJSON_IsString(x) ? x->valuestring : NULL;
}

double openhab_json_num(const cJSON* v, const char* path, double fallback) {
    const cJSON* x = openhab_json_get(v, path);
    if (cJSON_IsNumber(x)) return x->valuedouble;
    if (cJSON_IsString(x)) {
        char* end;
        double d = strtod(x->valuestring, &end);
        if (end != x->valuestring) return d;
    }
    return fallback;
}

char* openhab_json_print(const cJSON* v) { return v ? cJSON_PrintUnformatted(v) : oh_strdup("null"); }

void openhab_free(void* p) { free(p); }
