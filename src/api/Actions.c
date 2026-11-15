/* Generated from Actions.py of python-openhab-rest-client by tools/py2c.py – do not edit. */
#include "../py_rt.h"
#include "openhab/openhab_api.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static cJSON* actions_getActions_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language);
static cJSON* actions_executeAction_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_actionUID, cJSON* v_actionInputs, cJSON* v_language);

static cJSON* actions_getActions_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_cat(X, 2, py_s(X, "/actions/"), v_thingUID), v_headers, NULL, NULL);
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
        if (py_eq(v_status_code, py_num(X, 204))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "No actions found."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Thing not found: "), v_thingUID));
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
    } else if (py_eq(v_status_code, py_num(X, 204))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "No actions found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 404))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Thing not found: "), v_thingUID));
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

cJSON* openhab_actions_getActions_(openhab_client_t* client, const char* thingUID, openhab_actions_getActions_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = actions_getActions_impl(X, py_s(X, thingUID), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* actions_executeAction_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_actionUID, cJSON* v_actionInputs, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_headers = py_dict(X, 2, "Content-Type", py_s(X, "application/json"), "Accept", py_s(X, "application/json"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "post", py_cat(X, 4, py_s(X, "/actions/"), v_thingUID, py_s(X, "/"), v_actionUID), v_headers, py_dumps(X, v_actionInputs), NULL);
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
        if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Action not found."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 500))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Creation of action handler or execution failed."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Action not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 500))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Creation of action handler or execution failed."));
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

cJSON* openhab_actions_executeAction_(openhab_client_t* client, const char* thingUID, const char* actionUID, const cJSON* actionInputs, openhab_actions_executeAction_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = actions_executeAction_impl(X, py_s(X, thingUID), py_s(X, actionUID), py_arg_json(X, actionInputs), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}
