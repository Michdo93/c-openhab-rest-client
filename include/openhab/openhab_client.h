#ifndef OPENHAB_CLIENT_H
#define OPENHAB_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

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

/* ── openhab_client_t ──────────────────────────────────────────────────────── */

/**
 * Opaque client handle.
 * Create with openhab_client_create(), destroy with openhab_client_destroy().
 */
typedef struct openhab_client openhab_client_t;

/**
 * Create a new client.
 *
 * @param url       Base URL, e.g. "https://myopenhab.org" or "http://127.0.0.1:8080"
 * @param username  Basic-Auth username, or NULL for token auth
 * @param password  Basic-Auth password, or NULL for token auth
 * @param token     Bearer token, or NULL for Basic auth
 * @return          Heap-allocated client, or NULL on failure.
 */
OPENHAB_API openhab_client_t* openhab_client_create(
    const char* url,
    const char* username,
    const char* password,
    const char* token);

/** Free all resources associated with the client. */
OPENHAB_API void openhab_client_destroy(openhab_client_t* client);

/** Returns 1 if the last login/connectivity check succeeded. */
OPENHAB_API int openhab_client_is_logged_in(const openhab_client_t* client);

/** Returns 1 if the server URL contains "myopenhab.org". */
OPENHAB_API int openhab_client_is_cloud(const openhab_client_t* client);

/** Returns the base URL (owned by the client, do not free). */
OPENHAB_API const char* openhab_client_base_url(const openhab_client_t* client);

/* ── HTTP helpers ──────────────────────────────────────────────────────────── */

/**
 * Perform a GET request.
 *
 * @param client     Client handle.
 * @param endpoint   REST path, e.g. "/items" or "/rest/items".
 * @param accept     Accept header value, e.g. "application/json". May be NULL.
 * @param query      URL-encoded query string without '?', e.g. "type=Switch". May be NULL.
 * @return           Heap-allocated response body (caller must free()), or NULL on error.
 */
OPENHAB_API char* openhab_get(
    openhab_client_t* client,
    const char* endpoint,
    const char* accept,
    const char* query);

/**
 * Perform a POST request.
 *
 * @param body       Request body. May be NULL.
 * @param content_type  Content-Type header. May be NULL (defaults to "application/json").
 * @return           Heap-allocated response body (caller must free()), or NULL on error.
 */
OPENHAB_API char* openhab_post(
    openhab_client_t* client,
    const char* endpoint,
    const char* body,
    const char* content_type);

/**
 * Perform a PUT request.
 */
OPENHAB_API char* openhab_put(
    openhab_client_t* client,
    const char* endpoint,
    const char* body,
    const char* content_type);

/**
 * Perform a DELETE request.
 */
OPENHAB_API char* openhab_delete(
    openhab_client_t* client,
    const char* endpoint);

/* ── Last error ────────────────────────────────────────────────────────────── */

/**
 * Returns a human-readable description of the last error, or NULL.
 * The string is owned by the client; do not free it.
 */
OPENHAB_API const char* openhab_last_error(const openhab_client_t* client);

/** Returns the HTTP status code of the last request, or 0. */
OPENHAB_API int openhab_last_status(const openhab_client_t* client);

/* ── SSE ───────────────────────────────────────────────────────────────────── */

/**
 * SSE event callback.
 * Called for each "data: ..." line received from the stream.
 * Return 1 to continue, 0 to stop.
 */
typedef int (*openhab_sse_callback_t)(const char* data, void* userdata);

/**
 * Open a Server-Sent Events stream.
 * Blocks until the stream ends or the callback returns 0.
 *
 * @param client    Client handle.
 * @param url       Full SSE URL, e.g. client's baseUrl + "/rest/events".
 * @param callback  Called for each event.
 * @param userdata  Passed through to every callback invocation.
 */
OPENHAB_API void openhab_sse_listen(
    openhab_client_t* client,
    const char* url,
    openhab_sse_callback_t callback,
    void* userdata);

#ifdef __cplusplus
}
#endif

#endif /* OPENHAB_CLIENT_H */
