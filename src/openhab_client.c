#include "openhab/openhab_client.h"

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/* ── Internal structs ────────────────────────────────────────────────────────*/

typedef struct {
    char*  data;
    size_t size;
    size_t capacity;
} write_buf_t;

struct openhab_client {
    char* base_url;
    char* username;
    char* password;
    char* token;
    int   is_cloud;
    int   is_logged_in;
    char  last_error[512];
    int   last_status;
};

/* ── Helper: strdup ─────────────────────────────────────────────────────────*/

static char* oh_strdup(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char* d = (char*)malloc(len + 1);
    if (d) memcpy(d, s, len + 1);
    return d;
}

/* ── CURL write callback ─────────────────────────────────────────────────────*/

static size_t write_cb(char* ptr, size_t size, size_t nmemb, void* userdata) {
    write_buf_t* buf = (write_buf_t*)userdata;
    size_t incoming = size * nmemb;

    if (buf->size + incoming + 1 > buf->capacity) {
        size_t new_cap = (buf->capacity == 0) ? 4096 : buf->capacity * 2;
        while (new_cap < buf->size + incoming + 1) new_cap *= 2;
        char* new_data = (char*)realloc(buf->data, new_cap);
        if (!new_data) return 0;
        buf->data     = new_data;
        buf->capacity = new_cap;
    }
    memcpy(buf->data + buf->size, ptr, incoming);
    buf->size += incoming;
    buf->data[buf->size] = '\0';
    return incoming;
}

/* ── Auth header ─────────────────────────────────────────────────────────────*/

static void set_auth(struct curl_slist** headers, const openhab_client_t* c) {
    if (c->token && c->token[0]) {
        char buf[1024];
        snprintf(buf, sizeof(buf), "Authorization: Bearer %s", c->token);
        *headers = curl_slist_append(*headers, buf);
    } else if (c->username && c->username[0] && c->password) {
        /* libcurl handles Basic auth internally via CURLOPT_USERPWD */
    }
}

/* ── URL builder ─────────────────────────────────────────────────────────────*/

static char* build_url(const openhab_client_t* c, const char* endpoint, const char* query) {
    /* ensure /rest prefix */
    const char* rest = "/rest";
    int has_rest = (strncmp(endpoint, "/rest", 5) == 0);
    size_t base_len  = strlen(c->base_url);
    size_t ep_len    = strlen(endpoint);
    size_t rest_len  = has_rest ? 0 : 5;
    size_t query_len = query ? strlen(query) + 1 : 0; /* +1 for '?' */
    size_t total     = base_len + rest_len + ep_len + query_len + 1;

    char* url = (char*)malloc(total);
    if (!url) return NULL;

    if (has_rest)
        snprintf(url, total, "%s%s%s%s", c->base_url, endpoint,
                 query ? "?" : "", query ? query : "");
    else
        snprintf(url, total, "%s%s%s%s%s", c->base_url, rest, endpoint,
                 query ? "?" : "", query ? query : "");
    return url;
}

/* ── Core execute ────────────────────────────────────────────────────────────*/

static char* execute(openhab_client_t* c,
                     const char* method,
                     const char* endpoint,
                     const char* body,
                     const char* content_type,
                     const char* accept,
                     const char* query) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        snprintf(c->last_error, sizeof(c->last_error), "curl_easy_init failed");
        return NULL;
    }

    char* url = build_url(c, endpoint, query);
    if (!url) { curl_easy_cleanup(curl); return NULL; }

    write_buf_t buf = {NULL, 0, 0};

    struct curl_slist* headers = NULL;

    /* Accept header */
    if (accept) {
        char hdr[256];
        snprintf(hdr, sizeof(hdr), "Accept: %s", accept);
        headers = curl_slist_append(headers, hdr);
    }

    /* Content-Type */
    if (body && content_type) {
        char hdr[256];
        snprintf(hdr, sizeof(hdr), "Content-Type: %s", content_type);
        headers = curl_slist_append(headers, hdr);
    }

    /* Auth */
    set_auth(&headers, c);

    curl_easy_setopt(curl, CURLOPT_URL,            url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,      &buf);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,        30L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    if (c->username && c->username[0] && c->token == NULL) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, c->username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, c->password ? c->password : "");
    }

    if (strcmp(method, "POST") == 0) {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        if (body) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS,    body);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(body));
        } else {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS,    "");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0L);
        }
    } else if (strcmp(method, "PUT") == 0) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        if (body) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS,    body);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(body));
        } else {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS,    "");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0L);
        }
    } else if (strcmp(method, "DELETE") == 0) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    }

    if (headers)
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    c->last_status = (int)http_code;

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free(url);

    if (res != CURLE_OK) {
        snprintf(c->last_error, sizeof(c->last_error),
                 "curl error: %s", curl_easy_strerror(res));
        free(buf.data);
        return NULL;
    }

    if (http_code >= 400) {
        snprintf(c->last_error, sizeof(c->last_error),
                 "HTTP %ld: %s", http_code,
                 buf.data ? buf.data : "");
        free(buf.data);
        return NULL;
    }

    c->last_error[0] = '\0';

    if (!buf.data || buf.size == 0) {
        char* status_json = (char*)malloc(32);
        if (status_json) snprintf(status_json, 32, "{\"status\":%ld}", http_code);
        return status_json;
    }

    return buf.data; /* caller owns this */
}

/* ── Public API ──────────────────────────────────────────────────────────────*/

openhab_client_t* openhab_client_create(const char* url,
                                         const char* username,
                                         const char* password,
                                         const char* token) {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    openhab_client_t* c = (openhab_client_t*)calloc(1, sizeof(*c));
    if (!c) return NULL;

    /* Strip trailing slashes */
    c->base_url = oh_strdup(url);
    if (c->base_url) {
        size_t len = strlen(c->base_url);
        while (len > 0 && c->base_url[len-1] == '/') c->base_url[--len] = '\0';
    }

    c->username = oh_strdup(username);
    c->password = oh_strdup(password);
    c->token    = oh_strdup(token);

    /* Cloud detection */
    c->is_cloud = (c->base_url && strstr(c->base_url, "myopenhab.org") != NULL);

    /* Login check */
    if (c->is_cloud) {
        c->is_logged_in = 1;
    } else {
        char* resp = execute(c, "GET", "/rest", NULL, NULL, "application/json", NULL);
        if (resp) {
            c->is_logged_in = 1;
            free(resp);
        } else {
            c->is_logged_in = 0;
        }
    }

    return c;
}

void openhab_client_destroy(openhab_client_t* c) {
    if (!c) return;
    free(c->base_url);
    free(c->username);
    free(c->password);
    free(c->token);
    free(c);
}

int         openhab_client_is_logged_in(const openhab_client_t* c) { return c ? c->is_logged_in : 0; }
int         openhab_client_is_cloud(const openhab_client_t* c)     { return c ? c->is_cloud : 0; }
const char* openhab_client_base_url(const openhab_client_t* c)     { return c ? c->base_url : NULL; }
const char* openhab_last_error(const openhab_client_t* c)          { return c && c->last_error[0] ? c->last_error : NULL; }
int         openhab_last_status(const openhab_client_t* c)         { return c ? c->last_status : 0; }

char* openhab_get(openhab_client_t* c, const char* ep, const char* accept, const char* query) {
    return execute(c, "GET", ep, NULL, NULL, accept ? accept : "application/json", query);
}

char* openhab_post(openhab_client_t* c, const char* ep, const char* body, const char* ct) {
    return execute(c, "POST", ep, body, ct ? ct : "application/json", NULL, NULL);
}

char* openhab_put(openhab_client_t* c, const char* ep, const char* body, const char* ct) {
    return execute(c, "PUT", ep, body, ct ? ct : "application/json", NULL, NULL);
}

char* openhab_delete(openhab_client_t* c, const char* ep) {
    return execute(c, "DELETE", ep, NULL, NULL, NULL, NULL);
}

/* ── SSE ─────────────────────────────────────────────────────────────────────*/

typedef struct {
    openhab_sse_callback_t cb;
    void*  userdata;
    char   buf[4096];
    size_t buf_len;
    int    stop;
} sse_ctx_t;

static size_t sse_write_cb(char* ptr, size_t size, size_t nmemb, void* userdata) {
    sse_ctx_t* ctx = (sse_ctx_t*)userdata;
    if (ctx->stop) return 0;

    size_t incoming = size * nmemb;

    /* append to buffer */
    for (size_t i = 0; i < incoming && !ctx->stop; i++) {
        char ch = ptr[i];
        if (ch == '\n') {
            ctx->buf[ctx->buf_len] = '\0';
            /* check for "data: " prefix */
            if (strncmp(ctx->buf, "data: ", 6) == 0 && ctx->buf_len > 6) {
                int cont = ctx->cb(ctx->buf + 6, ctx->userdata);
                if (!cont) ctx->stop = 1;
            }
            ctx->buf_len = 0;
        } else if (ctx->buf_len < sizeof(ctx->buf) - 1) {
            ctx->buf[ctx->buf_len++] = ch;
        }
    }
    return ctx->stop ? 0 : incoming;
}

void openhab_sse_listen(openhab_client_t* c, const char* url,
                         openhab_sse_callback_t cb, void* userdata) {
    CURL* curl = curl_easy_init();
    if (!curl) return;

    sse_ctx_t ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.cb       = cb;
    ctx.userdata = userdata;

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: text/event-stream");
    headers = curl_slist_append(headers, "Cache-Control: no-cache");
    set_auth(&headers, c);

    curl_easy_setopt(curl, CURLOPT_URL,            url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  sse_write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,      &ctx);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER,     headers);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,        0L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    if (c->username && c->username[0] && !c->token) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, c->username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, c->password ? c->password : "");
    }

    curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}
