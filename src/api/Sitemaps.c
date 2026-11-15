/* Generated from Sitemaps.py of python-openhab-rest-client by tools/py2c.py – do not edit. */
#include "../py_rt.h"
#include "openhab/openhab_api.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static openhab_sse_t* sitemaps_openEventStream_impl(py_ctx* X, cJSON* v_path, cJSON* v_params, cJSON* v_errors);
static cJSON* sitemaps_getSitemaps_impl(py_ctx* X);
static cJSON* sitemaps_getSitemap_impl(py_ctx* X, cJSON* v_sitemapName, cJSON* v_type, cJSON* v_jsonCallback, cJSON* v_includeHidden, cJSON* v_language);
static cJSON* sitemaps_getSitemapPage_impl(py_ctx* X, cJSON* v_sitemapName, cJSON* v_pageID, cJSON* v_subscriptionID, cJSON* v_includeHidden, cJSON* v_language);
static cJSON* sitemaps_getFullSitemap_impl(py_ctx* X, cJSON* v_sitemapName, cJSON* v_subscriptionID, cJSON* v_includeHidden, cJSON* v_language);
static openhab_sse_t* sitemaps_getSitemapEvents_impl(py_ctx* X, cJSON* v_subscriptionID, cJSON* v_sitemapName, cJSON* v_pageID);
static openhab_sse_t* sitemaps_getFullSitemapEvents_impl(py_ctx* X, cJSON* v_subscriptionID, cJSON* v_sitemapName);
static cJSON* sitemaps_subscribeToSitemapEvents_impl(py_ctx* X);

static openhab_sse_t* sitemaps_openEventStream_impl(py_ctx* X, cJSON* v_path, cJSON* v_params, cJSON* v_errors) {
    cJSON* v_statusCode = NULL;
    /* try */
    {
        openhab_sse_t* r_ = py_sse(X, v_path, NULL, v_params);
        if (X->exc) goto exc_1;
        return r_;
    }
exc_1:
    if (X->exc == 1) {
        py_clear_exc(X);
        v_statusCode = py_exc_status(X);
        if (X->exc) return NULL;
        if (py_contains(v_errors, v_statusCode)) {
            {
                openhab_sse_t* r_ = py_as_stream(X, py_dict(X, 1, "error", py_get(X, v_errors, v_statusCode)));
                if (X->exc) return NULL;
                return r_;
            }
        }
        {
            openhab_sse_t* r_ = py_as_stream(X, py_dict(X, 1, "error", py_cat(X, 4, py_s(X, "HTTP error "), v_statusCode, py_s(X, ": "), py_exc_str(X))));
            if (X->exc) return NULL;
            return r_;
        }
    }
    if (X->exc != 0) {
        py_clear_exc(X);
        {
            openhab_sse_t* r_ = py_as_stream(X, py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Request error: "), py_exc_str(X))));
            if (X->exc) return NULL;
            return r_;
        }
    }
    return NULL;
end_1:;
}

static cJSON* sitemaps_getSitemaps_impl(py_ctx* X) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_s(X, "/sitemaps"), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
    if (X->exc) goto exc_1;
    if (py_isstatus(v_response)) {
        v_status_code = py_get(X, v_response, py_s(X, "status"));
        if (X->exc) goto exc_1;
    } else {
        {
            cJSON* r_ = v_response;
            if (X->exc) goto exc_1;
            return r_;
        }
    }
    goto end_1;
exc_1:
    if (X->exc == 1) {
        py_clear_exc(X);
        v_status_code = py_exc_status(X);
        if (X->exc) return NULL;
        if (!py_eq(v_status_code, py_num(X, 200))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 4, py_s(X, "HTTP error "), v_status_code, py_s(X, ": "), py_exc_str(X)));
                if (X->exc) return NULL;
                return r_;
            }
        }
        goto end_1;
    }
    if (X->exc != 0) {
        py_clear_exc(X);
        {
            cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Request error: "), py_exc_str(X)));
            if (X->exc) return NULL;
            return r_;
        }
    }
    return NULL;
end_1:;
    if (py_eq(v_status_code, py_num(X, 200))) {
        {
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "OK"));
            if (X->exc) return NULL;
            return r_;
        }
    }
    {
        cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Unexpected response: "), v_status_code));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_sitemaps_getSitemaps(openhab_client_t* client) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = sitemaps_getSitemaps_impl(X);
    return py_finish(X, r);
}

static cJSON* sitemaps_getSitemap_impl(py_ctx* X, cJSON* v_sitemapName, cJSON* v_type, cJSON* v_jsonCallback, cJSON* v_includeHidden, cJSON* v_language) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    if (py_truthy(v_includeHidden)) {
        v_includeHidden = py_s(X, "true");
        if (X->exc) return NULL;
    } else {
        v_includeHidden = py_s(X, "false");
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "get", py_cat(X, 2, py_s(X, "/sitemaps/"), v_sitemapName), (py_truthy(v_language) ? py_dict(X, 1, "Accept-Language", v_language) : py_dict(X, 0)), NULL, py_dict(X, 3, "type", v_type, "jsoncallback", v_jsonCallback, "includeHidden", v_includeHidden));
    if (X->exc) goto exc_1;
    if (py_isstatus(v_response)) {
        v_status_code = py_get(X, v_response, py_s(X, "status"));
        if (X->exc) goto exc_1;
    } else {
        {
            cJSON* r_ = v_response;
            if (X->exc) goto exc_1;
            return r_;
        }
    }
    goto end_1;
exc_1:
    if (X->exc == 1) {
        py_clear_exc(X);
        v_status_code = py_exc_status(X);
        if (X->exc) return NULL;
        if (!py_eq(v_status_code, py_num(X, 200))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 4, py_s(X, "HTTP error "), v_status_code, py_s(X, ": "), py_exc_str(X)));
                if (X->exc) return NULL;
                return r_;
            }
        }
        goto end_1;
    }
    if (X->exc != 0) {
        py_clear_exc(X);
        {
            cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Request error: "), py_exc_str(X)));
            if (X->exc) return NULL;
            return r_;
        }
    }
    return NULL;
end_1:;
    if (py_eq(v_status_code, py_num(X, 200))) {
        {
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "OK"));
            if (X->exc) return NULL;
            return r_;
        }
    }
    {
        cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Unexpected response: "), v_status_code));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_sitemaps_getSitemap_(openhab_client_t* client, const char* sitemapName, openhab_sitemaps_getSitemap_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = sitemaps_getSitemap_impl(X, py_s(X, sitemapName), (a.type ? py_s(X, a.type) : py_none(X)), (a.jsonCallback ? py_s(X, a.jsonCallback) : py_none(X)), py_arg_flag(X, a.includeHidden, py_bool(X, 0)), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* sitemaps_getSitemapPage_impl(py_ctx* X, cJSON* v_sitemapName, cJSON* v_pageID, cJSON* v_subscriptionID, cJSON* v_includeHidden, cJSON* v_language) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    if (py_truthy(v_includeHidden)) {
        v_includeHidden = py_s(X, "true");
        if (X->exc) return NULL;
    } else {
        v_includeHidden = py_s(X, "false");
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "get", py_cat(X, 4, py_s(X, "/sitemaps/"), v_sitemapName, py_s(X, "/"), v_pageID), (py_truthy(v_language) ? py_dict(X, 1, "Accept-Language", v_language) : py_dict(X, 0)), NULL, py_dict(X, 2, "subscriptionid", v_subscriptionID, "includeHidden", v_includeHidden));
    if (X->exc) goto exc_1;
    if (py_isstatus(v_response)) {
        v_status_code = py_get(X, v_response, py_s(X, "status"));
        if (X->exc) goto exc_1;
    } else {
        {
            cJSON* r_ = v_response;
            if (X->exc) goto exc_1;
            return r_;
        }
    }
    goto end_1;
exc_1:
    if (X->exc == 1) {
        py_clear_exc(X);
        v_status_code = py_exc_status(X);
        if (X->exc) return NULL;
        if (py_eq(v_status_code, py_num(X, 400))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid subscription id has been provided."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Sitemap with requested name does not exist or page does not exist, or page refers to a non-linkable widget."));
                if (X->exc) return NULL;
                return r_;
            }
        } else {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 4, py_s(X, "HTTP error "), v_status_code, py_s(X, ": "), py_exc_str(X)));
                if (X->exc) return NULL;
                return r_;
            }
        }
    }
    if (X->exc != 0) {
        py_clear_exc(X);
        {
            cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Request error: "), py_exc_str(X)));
            if (X->exc) return NULL;
            return r_;
        }
    }
    return NULL;
end_1:;
    if (py_eq(v_status_code, py_num(X, 200))) {
        {
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "OK"));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 404))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Sitemap with requested name does not exist or page does not exist, or page refers to a non-linkable widget."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid subscription id has been provided."));
            if (X->exc) return NULL;
            return r_;
        }
    }
    {
        cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Unexpected response: "), v_status_code));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_sitemaps_getSitemapPage_(openhab_client_t* client, const char* sitemapName, const char* pageID, openhab_sitemaps_getSitemapPage_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = sitemaps_getSitemapPage_impl(X, py_s(X, sitemapName), py_s(X, pageID), (a.subscriptionID ? py_s(X, a.subscriptionID) : py_none(X)), py_arg_flag(X, a.includeHidden, py_bool(X, 0)), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* sitemaps_getFullSitemap_impl(py_ctx* X, cJSON* v_sitemapName, cJSON* v_subscriptionID, cJSON* v_includeHidden, cJSON* v_language) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    if (py_truthy(v_includeHidden)) {
        v_includeHidden = py_s(X, "true");
        if (X->exc) return NULL;
    } else {
        v_includeHidden = py_s(X, "false");
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/sitemaps/"), v_sitemapName, py_s(X, "/*")), (py_truthy(v_language) ? py_dict(X, 1, "Accept-Language", v_language) : py_dict(X, 0)), NULL, py_dict(X, 2, "subscriptionid", v_subscriptionID, "includeHidden", v_includeHidden));
    if (X->exc) goto exc_1;
    if (py_isstatus(v_response)) {
        v_status_code = py_get(X, v_response, py_s(X, "status"));
        if (X->exc) goto exc_1;
    } else {
        {
            cJSON* r_ = v_response;
            if (X->exc) goto exc_1;
            return r_;
        }
    }
    goto end_1;
exc_1:
    if (X->exc == 1) {
        py_clear_exc(X);
        v_status_code = py_exc_status(X);
        if (X->exc) return NULL;
        if (py_eq(v_status_code, py_num(X, 400))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid subscription id has been provided."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Sitemap with requested name does not exist."));
                if (X->exc) return NULL;
                return r_;
            }
        } else {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 4, py_s(X, "HTTP error "), v_status_code, py_s(X, ": "), py_exc_str(X)));
                if (X->exc) return NULL;
                return r_;
            }
        }
    }
    if (X->exc != 0) {
        py_clear_exc(X);
        {
            cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Request error: "), py_exc_str(X)));
            if (X->exc) return NULL;
            return r_;
        }
    }
    return NULL;
end_1:;
    if (py_eq(v_status_code, py_num(X, 200))) {
        {
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "OK"));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 404))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Sitemap with requested name does not exist."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid subscription id has been provided."));
            if (X->exc) return NULL;
            return r_;
        }
    }
    {
        cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Unexpected response: "), v_status_code));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_sitemaps_getFullSitemap_(openhab_client_t* client, const char* sitemapName, openhab_sitemaps_getFullSitemap_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = sitemaps_getFullSitemap_impl(X, py_s(X, sitemapName), (a.subscriptionID ? py_s(X, a.subscriptionID) : py_none(X)), py_arg_flag(X, a.includeHidden, py_bool(X, 0)), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static openhab_sse_t* sitemaps_getSitemapEvents_impl(py_ctx* X, cJSON* v_subscriptionID, cJSON* v_sitemapName, cJSON* v_pageID) {
    {
        openhab_sse_t* r_ = sitemaps_openEventStream_impl(X, py_cat(X, 2, py_s(X, "/rest/sitemaps/events/"), v_subscriptionID), py_dict(X, 2, "sitemap", v_sitemapName, "pageid", v_pageID), py_dict(X, 2, "400", py_s(X, "Missing sitemap or page parameter, or page not linked successfully to the subscription."), "404", py_s(X, "Subscription not found.")));
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_sitemaps_getSitemapEvents_(openhab_client_t* client, const char* subscriptionID, openhab_sitemaps_getSitemapEvents_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = sitemaps_getSitemapEvents_impl(X, py_s(X, subscriptionID), (a.sitemapName ? py_s(X, a.sitemapName) : py_none(X)), (a.pageID ? py_s(X, a.pageID) : py_none(X)));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* sitemaps_getFullSitemapEvents_impl(py_ctx* X, cJSON* v_subscriptionID, cJSON* v_sitemapName) {
    {
        openhab_sse_t* r_ = sitemaps_openEventStream_impl(X, py_cat(X, 3, py_s(X, "/rest/sitemaps/events/"), v_subscriptionID, py_s(X, "/*")), py_dict(X, 1, "sitemap", v_sitemapName), py_dict(X, 2, "400", py_s(X, "Missing sitemap parameter, or sitemap not linked successfully to the subscription."), "404", py_s(X, "Subscription not found.")));
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_sitemaps_getFullSitemapEvents_(openhab_client_t* client, const char* subscriptionID, openhab_sitemaps_getFullSitemapEvents_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = sitemaps_getFullSitemapEvents_impl(X, py_s(X, subscriptionID), (a.sitemapName ? py_s(X, a.sitemapName) : py_none(X)));
    return py_finish_stream(X, s, NULL);
}

static cJSON* sitemaps_subscribeToSitemapEvents_impl(py_ctx* X) {
    cJSON* v_headers = NULL;
    cJSON* v_location = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    cJSON* v_value = NULL;
    /* try */
    v_response = py_http(X, "post", py_s(X, "/sitemaps/events/subscribe"), NULL, NULL, NULL);
    if (X->exc) goto exc_1;
    v_location = py_none(X);
    if (X->exc) goto exc_1;
    if (py_isdict(v_response)) {
        v_location = py_getor(X, v_response, py_s(X, "location"), NULL);
        if (X->exc) goto exc_1;
        if (!py_truthy(v_location)) {
            v_headers = py_or(py_getor(X, py_or(py_getor(X, v_response, py_s(X, "context"), NULL), py_dict(X, 0)), py_s(X, "headers"), NULL), py_dict(X, 0));
            if (X->exc) goto exc_1;
            v_value = py_getor(X, v_headers, py_s(X, "Location"), NULL);
            if (X->exc) goto exc_1;
            v_location = (py_truthy(py_and(py_bool(X, py_islist(v_value)), v_value)) ? py_get(X, v_value, py_num(X, 0)) : v_value);
            if (X->exc) goto exc_1;
        }
    }
    if (py_truthy(v_location)) {
        {
            cJSON* r_ = py_dict(X, 3, "message", py_s(X, "Subscription created."), "location", v_location, "subscriptionID", py_get(X, py_split(X, py_rstrip(X, v_location, py_s(X, "/")), py_s(X, "/")), py_num(X, -1)));
            if (X->exc) goto exc_1;
            return r_;
        }
    }
    if (py_isstatus(v_response)) {
        v_status_code = py_get(X, v_response, py_s(X, "status"));
        if (X->exc) goto exc_1;
    } else {
        {
            cJSON* r_ = v_response;
            if (X->exc) goto exc_1;
            return r_;
        }
    }
    goto end_1;
exc_1:
    if (X->exc == 1) {
        py_clear_exc(X);
        v_status_code = py_exc_status(X);
        if (X->exc) return NULL;
        if (py_eq(v_status_code, py_num(X, 503))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Subscriptions limit reached."));
                if (X->exc) return NULL;
                return r_;
            }
        } else {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 4, py_s(X, "HTTP error "), v_status_code, py_s(X, ": "), py_exc_str(X)));
                if (X->exc) return NULL;
                return r_;
            }
        }
    }
    if (X->exc != 0) {
        py_clear_exc(X);
        {
            cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Request error: "), py_exc_str(X)));
            if (X->exc) return NULL;
            return r_;
        }
    }
    return NULL;
end_1:;
    if (py_eq(v_status_code, py_num(X, 201))) {
        {
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "Subscription created."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 503))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Subscriptions limit reached."));
            if (X->exc) return NULL;
            return r_;
        }
    }
    {
        cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Unexpected response: "), v_status_code));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_sitemaps_subscribeToSitemapEvents(openhab_client_t* client) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = sitemaps_subscribeToSitemapEvents_impl(X);
    return py_finish(X, r);
}
