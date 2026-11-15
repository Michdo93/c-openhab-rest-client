/*
 * c-openhab-rest-client – client, JSON helpers and Server-Sent Events.
 *
 * Every REST function of this library (openhab_api.h) returns a cJSON value that
 * the caller owns and frees with cJSON_Delete():
 *   - JSON responses as cJSON object or array,
 *   - text responses (e.g. an item state) as cJSON string,
 *   - errors as object {"error": "..."} and empty successes as {"message": "OK"} –
 *     exactly like python-openhab-rest-client.
 */
#ifndef OPENHAB_CLIENT_H
#define OPENHAB_CLIENT_H

#include <stddef.h>
#include <cjson/cJSON.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Export macros ─────────────────────────────────────────────────────────── */
#if defined(_WIN32) || defined(__CYGWIN__)
#  ifdef OPENHAB_BUILDING_DLL
#    define OPENHAB_API __declspec(dllexport)
#  elif defined(OPENHAB_STATIC)
#    define OPENHAB_API
#  else
#    define OPENHAB_API __declspec(dllimport)
#  endif
#else
#  if defined(OPENHAB_BUILDING_DLL) && defined(__GNUC__) && __GNUC__ >= 4
#    define OPENHAB_API __attribute__((visibility("default")))
#  else
#    define OPENHAB_API
#  endif
#endif

#define OPENHAB_CLIENT_VERSION "2.0.0"

/* Default timeout for normal requests in seconds (Python: DEFAULT_TIMEOUT). */
#define OPENHAB_DEFAULT_TIMEOUT 10.0
/* Timeout for opening an event stream in seconds (Python: SSE_CONNECT_TIMEOUT). */
#define OPENHAB_SSE_CONNECT_TIMEOUT 10.0

/* Optional boolean argument: OPENHAB_UNSET (0) keeps the default of the Python library. */
typedef enum { OPENHAB_UNSET = 0, OPENHAB_TRUE = 1, OPENHAB_FALSE = 2 } openhab_flag;

/* ── Client ────────────────────────────────────────────────────────────────── */

/** Opaque client handle. Thread-safe: every request uses its own connection. */
typedef struct openhab_client openhab_client_t;

/** Optional arguments of openhab_client_new(). */
typedef struct {
    int _;                  /* reserved, keeps the struct non-empty */
    const char* username;   /* Basic Authentication (also myopenHAB) */
    const char* password;
    const char* token;      /* API token (Bearer) – takes precedence */
    double timeout;         /* seconds for normal requests, 0 = OPENHAB_DEFAULT_TIMEOUT */
    openhab_flag verify;    /* TLS certificate check, default: on */
} openhab_client_args;

/**
 * Creates a client and checks whether openHAB is reachable (like the Python constructor).
 *
 *   openhab_client_t* c = openhab_client_new("http://127.0.0.1:8080", .token = token);
 *
 * Returns NULL only if memory runs out. Free with openhab_client_destroy().
 */
#define openhab_client_new(url, ...) \
    openhab_client_new_((url), (openhab_client_args){ ._ = 0, __VA_ARGS__ })
OPENHAB_API openhab_client_t* openhab_client_new_(const char* url, openhab_client_args args);

/** Version 1.x constructor, kept for compatibility. */
OPENHAB_API openhab_client_t* openhab_client_create(const char* url, const char* username,
                                                    const char* password, const char* token);

/** Frees the client (Python: close()). */
OPENHAB_API void openhab_client_destroy(openhab_client_t* client);

/** Repeats the reachability check of the constructor; returns isLoggedIn. */
OPENHAB_API int openhab_client_login(openhab_client_t* client);

/** 1 if openHAB was reachable and accepted the credentials (Python: isLoggedIn). */
OPENHAB_API int openhab_client_is_logged_in(const openhab_client_t* client);

/** 1 for myopenHAB (Python: isCloud). */
OPENHAB_API int openhab_client_is_cloud(const openhab_client_t* client);

/** Base URL without trailing slash (owned by the client). */
OPENHAB_API const char* openhab_client_base_url(const openhab_client_t* client);

/** Why the last login failed, or NULL (owned by the client). */
OPENHAB_API const char* openhab_client_last_error(const openhab_client_t* client);

/* ── Low-level requests (Python: client.get/post/put/delete) ──────────────── */

/**
 * Sends a request to a resource path ("/items", "/rest/items" or a full URL).
 * headers and params are cJSON objects or NULL; data is a cJSON value or NULL
 * (strings are sent as they are, everything else as JSON).
 *
 * Returns the decoded JSON, the text as cJSON string, or for empty bodies the
 * StatusResponse {"status": 200[, "location": ...]}. HTTP errors (4xx/5xx) and
 * connection errors return {"error": "..."}.
 */
OPENHAB_API cJSON* openhab_client_get(openhab_client_t* client, const char* endpoint,
                                      const cJSON* headers, const cJSON* params);
OPENHAB_API cJSON* openhab_client_post(openhab_client_t* client, const char* endpoint,
                                       const cJSON* headers, const cJSON* data,
                                       const cJSON* params);
OPENHAB_API cJSON* openhab_client_put(openhab_client_t* client, const char* endpoint,
                                      const cJSON* headers, const cJSON* data,
                                      const cJSON* params);
OPENHAB_API cJSON* openhab_client_delete(openhab_client_t* client, const char* endpoint,
                                         const cJSON* headers, const cJSON* data,
                                         const cJSON* params);

/* ── Results ───────────────────────────────────────────────────────────────── */

/** 1 if result is an error object {"error": ...} (or NULL). */
OPENHAB_API int openhab_is_error(const cJSON* result);

/** The error message of an error object, otherwise NULL (owned by result). */
OPENHAB_API const char* openhab_error(const cJSON* result);

/** 1 if result is a StatusResponse (empty answer with HTTP status). */
OPENHAB_API int openhab_is_status(const cJSON* result);

/**
 * Walks a path through objects and arrays: "payload.value", "0.label",
 * "members.2.name" (numbers index arrays). Returns NULL if a part is missing.
 */
OPENHAB_API cJSON* openhab_json_get(const cJSON* value, const char* path);

/** String at path (NULL if missing or not a string). Owned by value. */
OPENHAB_API const char* openhab_json_str(const cJSON* value, const char* path);

/** Number at path, or fallback. */
OPENHAB_API double openhab_json_num(const cJSON* value, const char* path, double fallback);

/** Compact JSON text of a value; free with openhab_free(). */
OPENHAB_API char* openhab_json_print(const cJSON* value);

/** Frees strings returned by this library. */
OPENHAB_API void openhab_free(void* p);

/* ── Server-Sent Events ────────────────────────────────────────────────────── */

/** An open event stream (returned by the *Events functions). */
typedef struct openhab_sse openhab_sse_t;

/**
 * Next event with decoded payload – Python: next(iterSSEEvents(stream)).
 * Waits at most timeout_ms milliseconds (-1 = no limit). Returns NULL on timeout,
 * at the end of the stream, after openhab_sse_interrupt() and on errors;
 * openhab_sse_is_open() tells whether more can come. Free the event with cJSON_Delete().
 * ALIVE messages ({"type": "ALIVE"}) are only returned with include_alive = 1.
 */
OPENHAB_API cJSON* openhab_sse_next_event(openhab_sse_t* stream, int timeout_ms,
                                          int include_alive);

/** Next raw line of the stream (Python: iterSSELines); free with openhab_free(). */
OPENHAB_API char* openhab_sse_next_line(openhab_sse_t* stream, int timeout_ms);

/** Decodes one "data:" line (Python: parseSSEData); NULL for other lines. */
OPENHAB_API cJSON* openhab_sse_parse_data(const char* line);

/** 1 while the stream is connected and not interrupted. */
OPENHAB_API int openhab_sse_is_open(const openhab_sse_t* stream);

/** 1 if the stream could not be opened (or failed later). */
OPENHAB_API int openhab_sse_is_error(const openhab_sse_t* stream);

/** Error message, or NULL (owned by the stream). */
OPENHAB_API const char* openhab_sse_error(const openhab_sse_t* stream);

/** The error as result object {"error": ...} or NULL; free with cJSON_Delete(). */
OPENHAB_API cJSON* openhab_sse_error_result(const openhab_sse_t* stream);

/**
 * Wakes up a waiting openhab_sse_next_*() and ends the stream. Safe to call from
 * another thread or a signal handler.
 */
OPENHAB_API void openhab_sse_interrupt(openhab_sse_t* stream);

/** Closes the connection and frees the stream (NULL is ignored). */
OPENHAB_API void openhab_sse_close(openhab_sse_t* stream);

#ifdef __cplusplus
}
#endif

#endif /* OPENHAB_CLIENT_H */
