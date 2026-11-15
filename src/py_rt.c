/* Runtime for the generated REST functions – see py_rt.h. */
#include "py_rt.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void py_init(py_ctx* X, openhab_client_t* c) {
    memset(X, 0, sizeof *X);
    X->client = c;
    X->pool = cJSON_CreateArray();
}

static cJSON* error_from_exc(py_ctx* X) {
    char text[1300];
    if (X->exc == 1) snprintf(text, sizeof text, "HTTP error %d: %s", X->status, X->msg);
    else snprintf(text, sizeof text, "Request error: %s", X->msg);
    cJSON* o = cJSON_CreateObject();
    cJSON_AddStringToObject(o, "error", text);
    return o;
}

cJSON* py_finish(py_ctx* X, cJSON* result) {
    cJSON* out;
    if (X->exc) out = error_from_exc(X);
    else if (!result) out = cJSON_CreateNull();
    else out = cJSON_Duplicate(result, 1);
    cJSON_Delete(X->pool);
    X->pool = NULL;
    return out;
}

openhab_sse_t* py_finish_stream(py_ctx* X, openhab_sse_t* s, cJSON* result) {
    if (!s) {
        cJSON* r = py_finish(X, result);
        const char* e = openhab_error(r);
        s = oh_sse_failed(e ? e : "no event stream", 0);
        cJSON_Delete(r);
        return s;
    }
    cJSON_Delete(X->pool);
    X->pool = NULL;
    return s;
}

cJSON* py_keep(py_ctx* X, cJSON* v) {
    if (!v) v = cJSON_CreateNull();
    cJSON_AddItemToArray(X->pool, v);
    return v;
}

cJSON* py_none(py_ctx* X) { return py_keep(X, cJSON_CreateNull()); }
cJSON* py_bool(py_ctx* X, int b) { return py_keep(X, cJSON_CreateBool(b)); }
cJSON* py_num(py_ctx* X, double d) { return py_keep(X, cJSON_CreateNumber(d)); }
cJSON* py_s(py_ctx* X, const char* s) {
    return py_keep(X, s ? cJSON_CreateString(s) : cJSON_CreateNull());
}

cJSON* py_arg_flag(py_ctx* X, openhab_flag f, cJSON* dflt) {
    if (f == OPENHAB_TRUE) return py_bool(X, 1);
    if (f == OPENHAB_FALSE) return py_bool(X, 0);
    return dflt;
}

cJSON* py_arg_json(py_ctx* X, const cJSON* v) {
    return v ? py_keep(X, cJSON_Duplicate(v, 1)) : py_none(X);
}

/* ── truth, comparison ─────────────────────────────────────────────────────── */

int py_isnone(const cJSON* v) { return v == NULL || cJSON_IsNull(v); }

int py_truthy(const cJSON* v) {
    if (py_isnone(v) || cJSON_IsFalse(v)) return 0;
    if (cJSON_IsTrue(v)) return 1;
    if (cJSON_IsNumber(v)) return v->valuedouble != 0;
    if (cJSON_IsString(v)) return v->valuestring[0] != '\0';
    if (cJSON_IsArray(v) || cJSON_IsObject(v)) return v->child != NULL || py_isstatus(v);
    return 1;
}

static int numeric(const cJSON* v, double* d) {
    if (cJSON_IsNumber(v)) { *d = v->valuedouble; return 1; }
    if (cJSON_IsBool(v)) { *d = cJSON_IsTrue(v) ? 1 : 0; return 1; }
    return 0;
}

int py_eq(const cJSON* a, const cJSON* b) {
    double x, y;
    if (py_isnone(a) || py_isnone(b)) return py_isnone(a) && py_isnone(b);
    if (numeric(a, &x) && numeric(b, &y)) return x == y;
    if (cJSON_IsString(a) && cJSON_IsString(b)) return strcmp(a->valuestring, b->valuestring) == 0;
    if ((cJSON_IsArray(a) && cJSON_IsArray(b)) || (cJSON_IsObject(a) && cJSON_IsObject(b)))
        return cJSON_Compare(a, b, 1);
    return 0;
}

int py_cmp(const cJSON* a, const cJSON* b) {
    double x = 0, y = 0;
    numeric(a, &x);
    numeric(b, &y);
    return x < y ? -1 : x > y;
}

static const char* key_text(const cJSON* k, char* buf, size_t n) {
    if (cJSON_IsString(k)) return k->valuestring;
    if (cJSON_IsNumber(k)) { snprintf(buf, n, "%.0f", k->valuedouble); return buf; }
    return NULL;
}

int py_contains(const cJSON* c, const cJSON* x) {
    char buf[32];
    if (cJSON_IsObject(c)) {
        const char* k = key_text(x, buf, sizeof buf);
        return k && cJSON_GetObjectItemCaseSensitive(c, k) != NULL;
    }
    if (cJSON_IsArray(c)) {
        for (const cJSON* e = c->child; e; e = e->next)
            if (py_eq(e, x)) return 1;
        return 0;
    }
    if (cJSON_IsString(c) && cJSON_IsString(x)) return strstr(c->valuestring, x->valuestring) != NULL;
    return 0;
}

cJSON* py_or(cJSON* a, cJSON* b) { return py_truthy(a) ? a : b; }
cJSON* py_and(cJSON* a, cJSON* b) { return py_truthy(a) ? b : a; }

/* ── strings ───────────────────────────────────────────────────────────────── */

static void repr(oh_buf* b, const cJSON* v, int top);

static void num_text(oh_buf* b, double d) {
    char t[64];
    if (d == floor(d) && fabs(d) < 1e16) snprintf(t, sizeof t, "%.0f", d);
    else snprintf(t, sizeof t, "%.17g", d);
    oh_buf_add(b, t, strlen(t));
}

static void repr(oh_buf* b, const cJSON* v, int top) {
    if (py_isnone(v)) { oh_buf_add(b, "None", 4); return; }
    if (cJSON_IsTrue(v)) { oh_buf_add(b, "True", 4); return; }
    if (cJSON_IsFalse(v)) { oh_buf_add(b, "False", 5); return; }
    if (cJSON_IsNumber(v)) { num_text(b, v->valuedouble); return; }
    if (cJSON_IsString(v)) {
        if (top) { oh_buf_add(b, v->valuestring, strlen(v->valuestring)); return; }
        oh_buf_add(b, "'", 1);
        oh_buf_add(b, v->valuestring, strlen(v->valuestring));
        oh_buf_add(b, "'", 1);
        return;
    }
    int obj = cJSON_IsObject(v);
    oh_buf_add(b, obj ? "{" : "[", 1);
    for (const cJSON* e = v->child; e; e = e->next) {
        if (e != v->child) oh_buf_add(b, ", ", 2);
        if (obj) {
            oh_buf_add(b, "'", 1);
            oh_buf_add(b, e->string, strlen(e->string));
            oh_buf_add(b, "': ", 3);
        }
        repr(b, e, 0);
    }
    oh_buf_add(b, obj ? "}" : "]", 1);
}

cJSON* py_str(py_ctx* X, const cJSON* v) {
    oh_buf b = {0};
    oh_buf_add(&b, "", 0);
    repr(&b, v, 1);
    cJSON* s = py_s(X, b.data);
    oh_buf_free(&b);
    return s;
}

cJSON* py_cat(py_ctx* X, int n, ...) {
    oh_buf b = {0};
    oh_buf_add(&b, "", 0);
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) repr(&b, va_arg(ap, const cJSON*), 1);
    va_end(ap);
    cJSON* s = py_s(X, b.data);
    oh_buf_free(&b);
    return s;
}

static const char* text(const cJSON* s) {
    return cJSON_IsString(s) ? s->valuestring : "";
}

cJSON* py_lower(py_ctx* X, const cJSON* s) {
    cJSON* r = cJSON_IsString(s) ? py_s(X, s->valuestring) : py_str(X, s);
    for (char* p = r->valuestring; *p; p++)
        if (*p >= 'A' && *p <= 'Z') *p = (char)(*p - 'A' + 'a');
    return r;
}

cJSON* py_strip(py_ctx* X, const cJSON* s) {
    const char* p = text(s);
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') p++;
    cJSON* r = py_s(X, p);
    size_t n = strlen(r->valuestring);
    while (n && strchr(" \t\r\n", r->valuestring[n - 1])) r->valuestring[--n] = '\0';
    return r;
}

cJSON* py_rstrip(py_ctx* X, const cJSON* s, const cJSON* chars) {
    cJSON* r = py_s(X, text(s));
    size_t n = strlen(r->valuestring);
    while (n && strchr(text(chars), r->valuestring[n - 1])) r->valuestring[--n] = '\0';
    return r;
}

cJSON* py_split(py_ctx* X, const cJSON* s, const cJSON* sep) {
    cJSON* l = py_keep(X, cJSON_CreateArray());
    const char* p = text(s);
    const char* d = text(sep);
    size_t dn = strlen(d);
    for (;;) {
        const char* q = dn ? strstr(p, d) : NULL;
        size_t n = q ? (size_t)(q - p) : strlen(p);
        char* part = (char*)malloc(n + 1);
        memcpy(part, p, n);
        part[n] = '\0';
        cJSON_AddItemToArray(l, cJSON_CreateString(part));
        free(part);
        if (!q) break;
        p = q + dn;
    }
    return l;
}

cJSON* py_join(py_ctx* X, const cJSON* sep, const cJSON* items) {
    oh_buf b = {0};
    oh_buf_add(&b, "", 0);
    for (const cJSON* e = items ? items->child : NULL; e; e = e->next) {
        if (e != items->child) oh_buf_add(&b, text(sep), strlen(text(sep)));
        repr(&b, e, 1);
    }
    cJSON* r = py_s(X, b.data);
    oh_buf_free(&b);
    return r;
}

int py_len(const cJSON* v) {
    if (cJSON_IsString(v)) return (int)strlen(v->valuestring);
    if (cJSON_IsArray(v) || cJSON_IsObject(v)) return cJSON_GetArraySize(v);
    return 0;
}

int py_isdict(const cJSON* v) { return cJSON_IsObject(v); }
int py_islist(const cJSON* v) { return cJSON_IsArray(v); }
int py_isstr(const cJSON* v) { return cJSON_IsString(v); }
int py_isbool(const cJSON* v) { return cJSON_IsBool(v); }
int py_isstatus(const cJSON* v) { return openhab_is_status(v); }

/* ── containers ────────────────────────────────────────────────────────────── */

cJSON* py_dict(py_ctx* X, int n, ...) {
    cJSON* d = py_keep(X, cJSON_CreateObject());
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        const char* k = va_arg(ap, const char*);
        const cJSON* v = va_arg(ap, const cJSON*);
        cJSON_AddItemToObject(d, k, v ? cJSON_Duplicate(v, 1) : cJSON_CreateNull());
    }
    va_end(ap);
    return d;
}

cJSON* py_list(py_ctx* X, int n, ...) {
    cJSON* l = py_keep(X, cJSON_CreateArray());
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        const cJSON* v = va_arg(ap, const cJSON*);
        cJSON_AddItemToArray(l, v ? cJSON_Duplicate(v, 1) : cJSON_CreateNull());
    }
    va_end(ap);
    return l;
}

cJSON* py_copy(py_ctx* X, const cJSON* m) {
    return m ? py_keep(X, cJSON_Duplicate(m, 1)) : py_keep(X, cJSON_CreateObject());
}

cJSON* py_without_none(py_ctx* X, const cJSON* m) {
    cJSON* d = py_keep(X, cJSON_CreateObject());
    for (const cJSON* e = m ? m->child : NULL; e; e = e->next)
        if (!py_isnone(e)) cJSON_AddItemToObject(d, e->string, cJSON_Duplicate(e, 1));
    return d;
}

cJSON* py_get(py_ctx* X, const cJSON* obj, const cJSON* key) {
    char buf[32];
    const cJSON* v = NULL;
    if (cJSON_IsObject(obj)) {
        const char* k = key_text(key, buf, sizeof buf);
        if (k) v = cJSON_GetObjectItemCaseSensitive(obj, k);
    } else if (cJSON_IsArray(obj) && cJSON_IsNumber(key)) {
        int i = (int)key->valuedouble;
        if (i < 0) i += cJSON_GetArraySize(obj);
        v = cJSON_GetArrayItem(obj, i);
    }
    return v ? py_keep(X, cJSON_Duplicate(v, 1)) : py_none(X);
}

cJSON* py_getor(py_ctx* X, const cJSON* obj, const cJSON* key, cJSON* dflt) {
    char buf[32];
    const char* k = key_text(key, buf, sizeof buf);
    if (cJSON_IsObject(obj) && k && cJSON_GetObjectItemCaseSensitive(obj, k))
        return py_get(X, obj, key);
    return dflt ? dflt : py_none(X);
}

void py_set(py_ctx* X, cJSON* obj, const cJSON* key, const cJSON* value) {
    char buf[32];
    (void)X;
    if (!cJSON_IsObject(obj)) return;
    const char* k = key_text(key, buf, sizeof buf);
    if (!k) return;
    cJSON* v = value ? cJSON_Duplicate(value, 1) : cJSON_CreateNull();
    if (cJSON_GetObjectItemCaseSensitive(obj, k)) cJSON_ReplaceItemInObjectCaseSensitive(obj, k, v);
    else cJSON_AddItemToObject(obj, k, v);
}

/* ── encoding ──────────────────────────────────────────────────────────────── */

cJSON* py_quote(py_ctx* X, const cJSON* s, const char* safe) {
    cJSON* t = cJSON_IsString(s) ? (cJSON*)s : py_str(X, s);
    char* q = oh_quote(t->valuestring, safe);
    cJSON* r = py_s(X, q);
    free(q);
    return r;
}

cJSON* py_urlencode(py_ctx* X, const cJSON* params) {
    char* q = oh_query_string(params);
    cJSON* r = py_s(X, q[0] == '?' ? q + 1 : q);
    free(q);
    return r;
}

cJSON* py_dumps(py_ctx* X, const cJSON* v) {
    char* t = cJSON_PrintUnformatted(v ? v : py_none(X));
    cJSON* r = py_s(X, t);
    cJSON_free(t);
    return r;
}

/* ── HTTP and streams ──────────────────────────────────────────────────────── */

cJSON* py_http(py_ctx* X, const char* verb, const cJSON* path, const cJSON* headers,
               const cJSON* data, const cJSON* params) {
    if (X->exc) return NULL;
    oh_response r;
    oh_request(X->client, verb, text(path), py_isnone(headers) ? NULL : headers,
               py_isnone(data) ? NULL : data, py_isnone(params) ? NULL : params, &r);
    if (r.exc) {
        X->exc = r.exc;
        X->status = r.status;
        snprintf(X->msg, sizeof X->msg, "%s", r.message);
        return NULL;
    }
    return py_keep(X, r.result);
}

cJSON* py_exc_status(py_ctx* X) { return py_num(X, X->status); }
cJSON* py_exc_str(py_ctx* X) { return py_s(X, X->msg); }
void py_clear_exc(py_ctx* X) { X->exc = 0; }

openhab_sse_t* py_open_stream(py_ctx* X, const cJSON* topics, const cJSON* path,
                              const cJSON* headers, const cJSON* errors) {
    cJSON* params = NULL;
    if (py_truthy(topics)) {
        params = cJSON_CreateObject();
        cJSON_AddItemToObject(params, "topics", cJSON_Duplicate(topics, 1));
    }
    const char* p = cJSON_IsString(path) ? path->valuestring : "/rest/events";
    openhab_sse_t* s = oh_sse_open(X->client, p, py_isnone(headers) ? NULL : headers, params);
    cJSON_Delete(params);
    if (!openhab_sse_is_error(s)) return s;
    char text_[1300];
    int status = oh_sse_status(s);
    char key[16];
    snprintf(key, sizeof key, "%d", status);
    const cJSON* custom = cJSON_IsObject(errors) ? cJSON_GetObjectItemCaseSensitive(errors, key) : NULL;
    if (status && cJSON_IsString(custom)) snprintf(text_, sizeof text_, "%s", custom->valuestring);
    else if (status) snprintf(text_, sizeof text_, "HTTP error %d: %s", status, openhab_sse_error(s));
    else snprintf(text_, sizeof text_, "Request error: %s", openhab_sse_error(s));
    openhab_sse_close(s);
    return oh_sse_failed(text_, status);
}

openhab_sse_t* py_sse(py_ctx* X, const cJSON* path, const cJSON* headers, const cJSON* params) {
    if (X->exc) return NULL;
    openhab_sse_t* s = oh_sse_open(X->client, text(path), py_isnone(headers) ? NULL : headers,
                                   py_isnone(params) ? NULL : params);
    if (!openhab_sse_is_error(s)) return s;
    X->status = oh_sse_status(s);
    X->exc = X->status ? 1 : 2;
    snprintf(X->msg, sizeof X->msg, "%s", openhab_sse_error(s));
    openhab_sse_close(s);
    return NULL;
}

openhab_sse_t* py_as_stream(py_ctx* X, cJSON* v) {
    if (!v || X->exc) return NULL;
    const char* e = openhab_error(v);
    return oh_sse_failed(e ? e : "no event stream", 0);
}
