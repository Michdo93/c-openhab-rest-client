/*
 * Server-Sent Events – the C counterpart of Client.executeSSE and SSE.py.
 *
 * The stream is read with the curl multi interface: openhab_sse_next_*() pumps
 * the connection until a complete line has arrived or the time is up. No thread
 * is needed, and openhab_sse_interrupt() wakes up a waiting call at once.
 */
#if !defined(_WIN32) && !defined(_POSIX_C_SOURCE)
#  define _POSIX_C_SOURCE 200809L
#endif
#include "oh_internal.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#ifdef _WIN32
#  include <windows.h>
static long long now_ms(void) { return (long long)GetTickCount64(); }
#else
#  include <time.h>
static long long now_ms(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (long long)t.tv_sec * 1000 + t.tv_nsec / 1000000;
}
#endif

struct openhab_sse {
    CURLM* multi;
    CURL* easy;
    struct curl_slist* headers;
    oh_buf in;                  /* received, not yet returned bytes */
    size_t pos;                 /* start of the next line in "in" */
    int headers_done;           /* status line and headers received */
    int status;                 /* HTTP status */
    char reason[128];
    int running;                /* transfer still active */
    volatile sig_atomic_t interrupted;
    char* error;                /* set if the stream failed */
    int error_status;
    char* url;
};

static size_t sse_body(char* p, size_t s, size_t n, void* u) {
    openhab_sse_t* x = (openhab_sse_t*)u;
    return oh_buf_add(&x->in, p, s * n) ? s * n : 0;
}

static size_t sse_header(char* line, size_t s, size_t n, void* u) {
    openhab_sse_t* x = (openhab_sse_t*)u;
    size_t len = s * n;
    if (len > 5 && strncmp(line, "HTTP/", 5) == 0) {
        x->headers_done = 0;
        x->reason[0] = '\0';
        const char* sp = memchr(line, ' ', len);
        if (sp) x->status = atoi(sp + 1);
        if (sp) sp = memchr(sp + 1, ' ', (size_t)(line + len - sp - 1));
        if (sp) {
            size_t k = (size_t)(line + len - sp - 1);
            while (k && (sp[k] == '\r' || sp[k] == '\n')) k--;
            if (k >= sizeof x->reason) k = sizeof x->reason - 1;
            memcpy(x->reason, sp + 1, k);
            x->reason[k] = '\0';
        }
    } else if (len <= 2 && (line[0] == '\r' || line[0] == '\n')) {
        x->headers_done = 1; /* empty line ends the headers */
    }
    return len;
}

openhab_sse_t* oh_sse_failed(const char* message, int status) {
    openhab_sse_t* x = (openhab_sse_t*)calloc(1, sizeof *x);
    if (!x) return NULL;
    x->error = oh_strdup(message ? message : "error");
    x->error_status = status;
    return x;
}

int oh_sse_status(const openhab_sse_t* s) { return s ? s->error_status : 0; }

static void fail(openhab_sse_t* x, const char* msg, int status) {
    if (!x->error) x->error = oh_strdup(msg);
    x->error_status = status;
    x->running = 0;
}

/* Pumps the transfer for at most wait_ms; returns 0 if the transfer has ended. */
static int pump(openhab_sse_t* x, int wait_ms) {
    if (!x->multi || !x->running) return 0;
    int still = 0, numfds = 0;
    curl_multi_poll(x->multi, NULL, 0, wait_ms, &numfds);
    curl_multi_perform(x->multi, &still);
    if (!still) {
        x->running = 0;
        CURLMsg* m;
        int q;
        while ((m = curl_multi_info_read(x->multi, &q)) != NULL) {
            if (m->msg == CURLMSG_DONE && m->data.result != CURLE_OK && !x->interrupted &&
                x->status < 400)
                fail(x, curl_easy_strerror(m->data.result), 0);
        }
    }
    return x->running;
}

openhab_sse_t* oh_sse_open(openhab_client_t* c, const char* path, const cJSON* headers,
                           const cJSON* params) {
    oh_curl_init_once();
    openhab_sse_t* x = (openhab_sse_t*)calloc(1, sizeof *x);
    if (!x) return NULL;
    char* base = oh_build_url(c, path);
    char* query = oh_query_string(params);
    x->url = (char*)malloc(strlen(base) + strlen(query) + 2);
    if (strchr(base, '?') && query[0]) sprintf(x->url, "%s&%s", base, query + 1);
    else sprintf(x->url, "%s%s", base, query);
    free(base);
    free(query);

    /* identity: a compressed stream would be flushed late */
    x->headers = curl_slist_append(NULL, "Accept: text/event-stream");
    x->headers = curl_slist_append(x->headers, "Cache-Control: no-cache");
    if (c->token && c->token[0]) {
        size_t n = strlen(c->token) + 32;
        char* h = (char*)malloc(n);
        snprintf(h, n, "Authorization: Bearer %s", c->token);
        x->headers = curl_slist_append(x->headers, h);
        free(h);
    }
    if (cJSON_IsObject(headers)) {
        for (const cJSON* h = headers->child; h; h = h->next) {
            if (!cJSON_IsString(h)) continue;
            size_t n = strlen(h->string) + strlen(h->valuestring) + 4;
            char* line = (char*)malloc(n);
            snprintf(line, n, "%s: %s", h->string, h->valuestring);
            x->headers = curl_slist_append(x->headers, line);
            free(line);
        }
    }
    x->easy = curl_easy_init();
    curl_easy_setopt(x->easy, CURLOPT_URL, x->url);
    curl_easy_setopt(x->easy, CURLOPT_HTTPHEADER, x->headers);
    curl_easy_setopt(x->easy, CURLOPT_WRITEFUNCTION, sse_body);
    curl_easy_setopt(x->easy, CURLOPT_WRITEDATA, x);
    curl_easy_setopt(x->easy, CURLOPT_HEADERFUNCTION, sse_header);
    curl_easy_setopt(x->easy, CURLOPT_HEADERDATA, x);
    curl_easy_setopt(x->easy, CURLOPT_CONNECTTIMEOUT_MS, (long)(OPENHAB_SSE_CONNECT_TIMEOUT * 1000));
    curl_easy_setopt(x->easy, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(x->easy, CURLOPT_TCP_KEEPALIVE, 1L);
    oh_apply_auth(x->easy, c);
    x->multi = curl_multi_init();
    curl_multi_add_handle(x->multi, x->easy);
    x->running = 1;
    oh_buf_add(&x->in, "", 0);

    /* Like requests: wait for the response headers (there is no read timeout –
     * openHAB sends the headers of sitemap streams only with the first event). */
    while (x->running && !x->headers_done && !x->interrupted) pump(x, 200);
    if (x->status >= 400) {
        /* read the error body, then report it like _raiseForStatus */
        long long end = now_ms() + (long long)(c->timeout * 1000);
        while (x->running && now_ms() < end) pump(x, 100);
        char text[1024];
        oh_http_error_text(text, sizeof text, x->status, x->reason, x->url, x->in.data);
        fail(x, text, x->status);
    } else if (!x->headers_done && !x->error && !x->interrupted) {
        fail(x, "connection closed before the response headers", 0);
    }
    return x;
}

char* openhab_sse_next_line(openhab_sse_t* x, int timeout_ms) {
    if (!x) return NULL;
    long long end = timeout_ms < 0 ? -1 : now_ms() + timeout_ms;
    for (;;) {
        char* nl = x->in.data ? memchr(x->in.data + x->pos, '\n', x->in.len - x->pos) : NULL;
        if (nl) {
            size_t n = (size_t)(nl - (x->in.data + x->pos));
            char* line = (char*)malloc(n + 1);
            memcpy(line, x->in.data + x->pos, n);
            line[n] = '\0';
            if (n && line[n - 1] == '\r') line[n - 1] = '\0';
            x->pos += n + 1;
            if (x->pos > 65536) { /* compact the buffer */
                memmove(x->in.data, x->in.data + x->pos, x->in.len - x->pos + 1);
                x->in.len -= x->pos;
                x->pos = 0;
            }
            return line;
        }
        if (x->interrupted) return NULL;
        if (!x->running) {
            if (x->in.data && x->pos < x->in.len) { /* last line without newline */
                char* line = oh_strdup(x->in.data + x->pos);
                x->pos = x->in.len;
                return line;
            }
            return NULL;
        }
        long long left = end < 0 ? 200 : end - now_ms();
        if (left <= 0) return NULL;
        pump(x, (int)(left > 200 ? 200 : left));
    }
}

cJSON* openhab_sse_parse_data(const char* line) {
    if (!line || strncmp(line, "data:", 5) != 0) return NULL;
    cJSON* ev = cJSON_Parse(line + 5);
    if (!ev) return NULL;
    cJSON* payload = cJSON_GetObjectItemCaseSensitive(ev, "payload");
    if (cJSON_IsString(payload)) {
        cJSON* p = cJSON_Parse(payload->valuestring);
        if (p) cJSON_ReplaceItemInObjectCaseSensitive(ev, "payload", p);
    }
    return ev;
}

cJSON* openhab_sse_next_event(openhab_sse_t* x, int timeout_ms, int include_alive) {
    long long end = timeout_ms < 0 ? -1 : now_ms() + timeout_ms;
    for (;;) {
        int left = end < 0 ? -1 : (int)(end - now_ms());
        if (end >= 0 && left < 0) left = 0;
        char* line = openhab_sse_next_line(x, left);
        if (!line) return NULL;
        cJSON* ev = openhab_sse_parse_data(line);
        free(line);
        if (!ev) continue;
        if (cJSON_GetObjectItemCaseSensitive(ev, "topic") || include_alive) return ev;
        cJSON_Delete(ev);
    }
}

int openhab_sse_is_open(const openhab_sse_t* x) {
    return x && !x->error && !x->interrupted && (x->running || x->pos < x->in.len);
}

int openhab_sse_is_error(const openhab_sse_t* x) { return !x || x->error != NULL; }

const char* openhab_sse_error(const openhab_sse_t* x) {
    return x ? x->error : "no stream";
}

cJSON* openhab_sse_error_result(const openhab_sse_t* x) {
    if (x && !x->error) return NULL;
    cJSON* o = cJSON_CreateObject();
    cJSON_AddStringToObject(o, "error", openhab_sse_error(x));
    return o;
}

void openhab_sse_interrupt(openhab_sse_t* x) {
    if (!x) return;
    x->interrupted = 1;
    if (x->multi) curl_multi_wakeup(x->multi);
}

void openhab_sse_close(openhab_sse_t* x) {
    if (!x) return;
    if (x->multi) {
        curl_multi_remove_handle(x->multi, x->easy);
        curl_multi_cleanup(x->multi);
    }
    if (x->easy) curl_easy_cleanup(x->easy);
    curl_slist_free_all(x->headers);
    oh_buf_free(&x->in);
    free(x->error);
    free(x->url);
    free(x);
}
