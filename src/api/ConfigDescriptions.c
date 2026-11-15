/* Generated from ConfigDescriptions.py of python-openhab-rest-client by tools/py2c.py – do not edit. */
#include "../py_rt.h"
#include "openhab/openhab_api.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static cJSON* config_descriptions_getConfigDescriptions_impl(py_ctx* X, cJSON* v_scheme, cJSON* v_language);
static cJSON* config_descriptions_getConfigDescription_impl(py_ctx* X, cJSON* v_uri, cJSON* v_language);

static cJSON* config_descriptions_getConfigDescriptions_impl(py_ctx* X, cJSON* v_scheme, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_params = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_headers = py_dict(X, 1, "Accept", py_s(X, "application/json"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    v_params = py_dict(X, 0);
    if (X->exc) return NULL;
    if (py_truthy(v_scheme)) {
        py_set(X, v_params, py_s(X, "scheme"), v_scheme);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "get", py_s(X, "/config-descriptions"), v_headers, NULL, v_params);
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

cJSON* openhab_config_descriptions_getConfigDescriptions_(openhab_client_t* client, openhab_config_descriptions_getConfigDescriptions_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = config_descriptions_getConfigDescriptions_impl(X, (a.scheme ? py_s(X, a.scheme) : py_none(X)), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* config_descriptions_getConfigDescription_impl(py_ctx* X, cJSON* v_uri, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_headers = py_dict(X, 1, "Accept", py_s(X, "application/json"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "get", py_cat(X, 2, py_s(X, "/config-descriptions/"), v_uri), v_headers, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid URI syntax."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid URI syntax."));
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

cJSON* openhab_config_descriptions_getConfigDescription_(openhab_client_t* client, const char* uri, openhab_config_descriptions_getConfigDescription_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = config_descriptions_getConfigDescription_impl(X, py_s(X, uri), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}
