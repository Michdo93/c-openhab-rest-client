#define _GNU_SOURCE
/*
 * Unit tests with a small local HTTP server – no openHAB needed.
 * POSIX only (Linux, macOS); on Windows the test reports "skipped".
 */
#include <openhab/openhab.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
int main(void) { puts("unit tests need POSIX sockets – skipped"); return 0; }
#else

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

static int failures = 0, checks = 0;
#define CHECK(cond, ...) do { checks++; if (!(cond)) { failures++; \
    printf("FAIL %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); } } while (0)

/* ── a tiny HTTP server ─────────────────────────────────────────────────────── */

typedef struct {
    const char* response;      /* complete raw response */
    const char* chunks[8];     /* for streams: sent one after the other */
    int chunk_delay_ms;
    int keep_open_ms;          /* keep the connection open after the chunks */
} reply_t;

static reply_t current;
static char last_request[8192];
static int port;
static int listen_fd;

static void sleep_ms(int ms) {
    struct timespec t = {ms / 1000, (ms % 1000) * 1000000L};
    nanosleep(&t, NULL);
}

static void* server(void* arg) {
    (void)arg;
    for (;;) {
        int fd = accept(listen_fd, NULL, NULL);
        if (fd < 0) return NULL;
        size_t n = 0;
        last_request[0] = '\0';
        /* read headers and (Content-Length) body */
        for (;;) {
            ssize_t k = recv(fd, last_request + n, sizeof last_request - 1 - n, 0);
            if (k <= 0) break;
            n += (size_t)k;
            last_request[n] = '\0';
            char* end = strstr(last_request, "\r\n\r\n");
            if (!end) continue;
            char* cl = strcasestr(last_request, "content-length:");
            size_t want = cl ? (size_t)atoi(cl + 15) : 0;
            if (n >= (size_t)(end + 4 - last_request) + want) break;
        }
        reply_t r = current;
        if (r.response) send(fd, r.response, strlen(r.response), MSG_NOSIGNAL);
        for (int i = 0; i < 8 && r.chunks[i]; i++) {
            if (i) sleep_ms(r.chunk_delay_ms);
            send(fd, r.chunks[i], strlen(r.chunks[i]), MSG_NOSIGNAL);
        }
        if (r.keep_open_ms) sleep_ms(r.keep_open_ms);
        close(fd);
    }
}

static void start_server(void) {
    struct sockaddr_in a;
    memset(&a, 0, sizeof a);
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    int one = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one);
    bind(listen_fd, (struct sockaddr*)&a, sizeof a);
    socklen_t len = sizeof a;
    getsockname(listen_fd, (struct sockaddr*)&a, &len);
    port = ntohs(a.sin_port);
    listen(listen_fd, 8);
    pthread_t t;
    pthread_create(&t, NULL, server, NULL);
    pthread_detach(t);
}

static void respond(const char* raw) {
    memset(&current, 0, sizeof current);
    current.response = raw;
}

static int has(const char* text) { return strstr(last_request, text) != NULL; }

static const char* json(const cJSON* v) {
    static char buf[2048];
    char* t = cJSON_PrintUnformatted(v);
    snprintf(buf, sizeof buf, "%s", t ? t : "NULL");
    free(t);
    return buf;
}

#define OK200 "HTTP/1.1 200 OK\r\nContent-Length: 0\r\nConnection: close\r\n\r\n"

/* ── tests ──────────────────────────────────────────────────────────────────── */

static void test_requests(openhab_client_t* c) {
    respond(OK200);
    cJSON* r = openhab_items_sendCommand(c, "Wohnzimmer_Licht", "ON");
    CHECK(strcmp(json(r), "{\"message\":\"OK\"}") == 0, "sendCommand result %s", json(r));
    CHECK(has("POST /rest/items/Wohnzimmer_Licht HTTP/1.1"), "request line: %s", last_request);
    CHECK(has("Authorization: Bearer oh.test.123"), "token header missing");
    CHECK(has("Content-Type: text/plain"), "content type of a command");
    CHECK(has("\r\n\r\nON"), "command body");
    cJSON_Delete(r);

    respond("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 27\r\n"
            "Connection: close\r\n\r\n[{\"name\":\"A\",\"state\":\"ON\"}]");
    r = openhab_items_getItems(c, .tags = "Light", .fields = "name,state");
    CHECK(cJSON_IsArray(r) && strcmp(openhab_json_str(r, "0.state"), "ON") == 0, "getItems %s",
          json(r));
    CHECK(has("GET /rest/items?tags=Light&metadata=.%2A&recursive=false&fields=name%2Cstate"
              "&staticDataOnly=false HTTP/1.1"), "query: %s", last_request);
    cJSON_Delete(r);

    respond("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 8\r\n"
            "Connection: close\r\n\r\n21.5 \xc2\xb0" "C");
    r = openhab_items_getItemState(c, "Temp");
    CHECK(cJSON_IsString(r) && strcmp(r->valuestring, "21.5 \xc2\xb0" "C") == 0, "state %s",
          json(r));
    cJSON_Delete(r);

    /* "#" in a channel UID must not start a URL fragment */
    respond(OK200);
    r = openhab_links_unlinkItemFromChannel(c, "Licht", "astro:sun:home:rise#start");
    CHECK(has("DELETE /rest/links/Licht/astro%3Asun%3Ahome%3Arise%23start"), "link url: %.120s",
          last_request);
    cJSON_Delete(r);

    /* dict bodies are sent as JSON */
    respond(OK200);
    cJSON* item = cJSON_Parse("{\"type\":\"Switch\",\"name\":\"X\"}");
    r = openhab_items_addOrUpdateItem(c, "X", item);
    CHECK(has("PUT /rest/items/X") && has("Content-Type: application/json") &&
          has("{\"type\":\"Switch\",\"name\":\"X\"}"), "addOrUpdateItem: %s", last_request);
    cJSON_Delete(r);
    cJSON_Delete(item);

    /* persistence: the state goes into the query, not into the body */
    respond(OK200);
    r = openhab_persistence_storeItemData(c, "T", "2026-11-06T10:00:00.000Z", "19.5",
                                          .serviceID = "inmemory");
    CHECK(has("PUT /rest/persistence/items/T?serviceId=inmemory&time=2026-11-06T10%3A00%3A00.000Z"
              "&state=19.5 "), "storeItemData: %.160s", last_request);
    cJSON_Delete(r);
}

static void test_errors(openhab_client_t* c) {
    respond("HTTP/1.1 404 Not Found\r\nContent-Type: application/json\r\nContent-Length: 62\r\n"
            "Connection: close\r\n\r\n{\"error\":{\"message\":\"Item X does not exist!\",\"http-code\":404}}");
    cJSON* r = openhab_items_getItem(c, "X");
    CHECK(openhab_is_error(r) && strcmp(openhab_error(r), "Item not found.") == 0, "404 %s",
          json(r));
    cJSON_Delete(r);

    respond("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 4\r\nConnection: close\r\n\r\nboom");
    r = openhab_uuid_getUUID(c);
    CHECK(openhab_is_error(r) && strstr(openhab_error(r), "HTTP error 500: 500 Server Error: "
          "Internal Server Error for url: ") && strstr(openhab_error(r), "(boom)"), "500 %s", json(r));
    cJSON_Delete(r);

    openhab_client_t* dead = openhab_client_new("http://127.0.0.1:1", .timeout = 2);
    CHECK(!openhab_client_is_logged_in(dead) && openhab_client_last_error(dead), "login check");
    r = openhab_items_getItems(dead);
    CHECK(openhab_is_error(r) && strncmp(openhab_error(r), "Request error: ", 15) == 0,
          "unreachable %s", json(r));
    cJSON_Delete(r);
    openhab_client_destroy(dead);
}

static void test_json(void) {
    cJSON* v = cJSON_Parse("{\"payload\":{\"value\":\"ON\",\"n\":\"21.5\"},\"list\":[1,{\"a\":\"b\"}]}");
    CHECK(strcmp(openhab_json_str(v, "payload.value"), "ON") == 0, "path");
    CHECK(openhab_json_num(v, "payload.n", 0) == 21.5, "number from string");
    CHECK(strcmp(openhab_json_str(v, "list.1.a"), "b") == 0, "array index");
    CHECK(openhab_json_get(v, "list.-1.a") != NULL, "negative index");
    CHECK(openhab_json_get(v, "nope.x") == NULL, "missing part");
    CHECK(!openhab_is_error(v), "not an error");
    cJSON_Delete(v);

    cJSON* e = openhab_sse_parse_data(
        "data: {\"topic\":\"openhab/items/A/statechanged\",\"payload\":\"{\\\"value\\\":\\\"OFF\\\"}\","
        "\"type\":\"ItemStateChangedEvent\"}");
    CHECK(e && strcmp(openhab_json_str(e, "payload.value"), "OFF") == 0, "parseSSEData %s", json(e));
    cJSON_Delete(e);
    CHECK(openhab_sse_parse_data("event: message") == NULL, "non-data line");
}

#define SSE_HEAD "HTTP/1.1 200 OK\r\nContent-Type: text/event-stream\r\nConnection: close\r\n\r\n"

typedef struct { openhab_sse_t* s; } interrupt_arg;
static void* interrupter(void* p) {
    sleep_ms(300);
    openhab_sse_interrupt(((interrupt_arg*)p)->s);
    return NULL;
}

static long long now(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (long long)t.tv_sec * 1000 + t.tv_nsec / 1000000;
}

static void test_sse(openhab_client_t* c) {
    memset(&current, 0, sizeof current);
    current.chunks[0] = SSE_HEAD "event: message\ndata: {\"type\":\"ALIVE\",\"interval\":10}\n\n";
    /* an event split in the middle of a line */
    current.chunks[1] = "event: message\ndata: {\"topic\":\"openhab/items/A/statechanged\",\"pay";
    current.chunks[2] = "load\":\"{\\\"value\\\":\\\"ON\\\"}\",\"type\":\"ItemStateChangedEvent\"}\n\n";
    current.chunk_delay_ms = 150;
    current.keep_open_ms = 3000;
    openhab_sse_t* s = openhab_item_events_ItemStateChangedEvent(c, "A");
    CHECK(!openhab_sse_is_error(s), "stream error %s", openhab_sse_error(s));
    CHECK(has("GET /rest/events?topics=openhab%2Fitems%2FA%2Fstatechanged") &&
          has("Accept: text/event-stream"), "stream request: %.200s", last_request);
    cJSON* ev = openhab_sse_next_event(s, 2000, 0);
    CHECK(ev && strcmp(openhab_json_str(ev, "payload.value"), "ON") == 0, "event %s", json(ev));
    cJSON_Delete(ev);
    long long t0 = now();
    ev = openhab_sse_next_event(s, 300, 0);
    CHECK(ev == NULL && now() - t0 < 900 && openhab_sse_is_open(s), "timeout");
    interrupt_arg a = {s};
    pthread_t t;
    pthread_create(&t, NULL, interrupter, &a);
    t0 = now();
    ev = openhab_sse_next_event(s, -1, 0);
    CHECK(ev == NULL && now() - t0 < 1500 && !openhab_sse_is_open(s), "interrupt took %lld ms",
          now() - t0);
    pthread_join(t, NULL);
    openhab_sse_close(s);

    /* ALIVE only on request */
    memset(&current, 0, sizeof current);
    current.chunks[0] = SSE_HEAD "data: {\"type\":\"ALIVE\",\"interval\":10}\n\n";
    s = openhab_events_getEvents(c);
    ev = openhab_sse_next_event(s, 2000, 1);
    CHECK(ev && strcmp(openhab_json_str(ev, "type"), "ALIVE") == 0, "alive %s", json(ev));
    cJSON_Delete(ev);
    openhab_sse_close(s);

    /* HTTP error of a stream: message of the Python library */
    respond("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
    s = openhab_events_getEvents(c, .topics = "bad topic");
    CHECK(openhab_sse_is_error(s) &&
          strcmp(openhab_sse_error(s), "Topic is empty or contains invalid characters.") == 0,
          "stream error: %s", openhab_sse_error(s));
    CHECK(openhab_sse_next_event(s, 100, 0) == NULL, "no events from a failed stream");
    openhab_sse_close(s);
}

int main(void) {
    start_server();
    char url[64];
    snprintf(url, sizeof url, "http://127.0.0.1:%d/", port);
    respond(OK200);
    openhab_client_t* c = openhab_client_new(url, .token = "oh.test.123", .timeout = 5);
    CHECK(openhab_client_is_logged_in(c), "login");
    CHECK(has("GET /rest/ HTTP/1.1"), "login request: %.60s", last_request);
    CHECK(strcmp(openhab_client_base_url(c), url) != 0, "trailing slash removed");

    openhab_client_t* basic = openhab_client_new(url, .username = "user", .password = "pass");
    CHECK(has("Authorization: Basic dXNlcjpwYXNz"), "basic auth");
    openhab_client_destroy(basic);

    test_requests(c);
    test_errors(c);
    test_json();
    test_sse(c);
    openhab_client_destroy(c);
    printf("%d checks, %d failed\n", checks, failures);
    return failures ? 1 : 0;
}
#endif
