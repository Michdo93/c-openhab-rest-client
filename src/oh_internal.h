/* Internal declarations shared by the C files of the library. */
#ifndef OH_INTERNAL_H
#define OH_INTERNAL_H

#include "openhab/openhab_client.h"
#include <curl/curl.h>

struct openhab_client {
    char* url;          /* without trailing slash */
    char* username;
    char* password;
    char* token;
    double timeout;
    int verify;
    int is_cloud;
    int is_logged_in;
    char last_error[512];
};

/* Outcome of one HTTP request (Python: __executeRequest). */
typedef struct {
    int exc;            /* 0 = ok, 1 = HTTPError, 2 = RequestException */
    int status;         /* HTTP status code */
    char message[1024]; /* str(err) */
    cJSON* result;      /* on success: JSON, text or StatusResponse (caller owns) */
} oh_response;

/* Simple growable buffer. */
typedef struct {
    char* data;
    size_t len, cap;
} oh_buf;

int oh_buf_add(oh_buf* b, const char* s, size_t n);
void oh_buf_free(oh_buf* b);

char* oh_strdup(const char* s);
void oh_curl_init_once(void);

/* Absolute URL for a resource path (Python: _buildUrl); caller frees. */
char* oh_build_url(const openhab_client_t* c, const char* resource_path);

/* "?a=b&c=d" (with leading "?") from a params object, None dropped, booleans lower case;
 * empty string if there are none. Caller frees. */
char* oh_query_string(const cJSON* params);

/* Percent-encoding like urllib.parse.quote(s, safe=...). Caller frees. */
char* oh_quote(const char* s, const char* safe);

/* Sets authentication, TLS verification and the User-Agent on an easy handle. */
void oh_apply_auth(CURL* h, const openhab_client_t* c);

/* Executes a request; verb = "get", "post", "put" or "delete". */
void oh_request(openhab_client_t* c, const char* verb, const char* resource_path,
                const cJSON* headers, const cJSON* data, const cJSON* params, oh_response* out);

/* Formats the HTTPError text like requests/_raiseForStatus. */
void oh_http_error_text(char* dst, size_t n, int status, const char* reason, const char* url,
                        const char* body);

/* Marks an object as StatusResponse. */
void oh_mark_status(cJSON* obj);

/* Opens an event stream (Python: client.executeSSE); never NULL. */
openhab_sse_t* oh_sse_open(openhab_client_t* c, const char* path, const cJSON* headers,
                           const cJSON* params);

/* A stream that only carries an error message. */
openhab_sse_t* oh_sse_failed(const char* message, int status);

/* HTTP status of a failed stream (0 = not an HTTP error). */
int oh_sse_status(const openhab_sse_t* s);

#endif
