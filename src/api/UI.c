/* Generated from UI.py of python-openhab-rest-client by tools/py2c.py – do not edit. */
#include "../py_rt.h"
#include "openhab/openhab_api.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static cJSON* ui_getUIComponents_impl(py_ctx* X, cJSON* v_namespace, cJSON* v_summary);
static cJSON* ui_addUIComponent_impl(py_ctx* X, cJSON* v_namespace, cJSON* v_componentData);
static cJSON* ui_getUIComponent_impl(py_ctx* X, cJSON* v_namespace, cJSON* v_componentUID);
static cJSON* ui_updateUIComponent_impl(py_ctx* X, cJSON* v_namespace, cJSON* v_componentUID, cJSON* v_componentData);
static cJSON* ui_deleteUIComponent_impl(py_ctx* X, cJSON* v_namespace, cJSON* v_componentUID);
static cJSON* ui_getUITiles_impl(py_ctx* X);

static cJSON* ui_getUIComponents_impl(py_ctx* X, cJSON* v_namespace, cJSON* v_summary) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 2, py_s(X, "/ui/components/"), v_namespace), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, (py_truthy(v_summary) ? py_dict(X, 1, "summary", v_summary) : py_dict(X, 0)));
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

cJSON* openhab_ui_getUIComponents_(openhab_client_t* client, const char* namespace, openhab_ui_getUIComponents_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = ui_getUIComponents_impl(X, py_s(X, namespace), py_arg_flag(X, a.summary, py_bool(X, 0)));
    return py_finish(X, r);
}

static cJSON* ui_addUIComponent_impl(py_ctx* X, cJSON* v_namespace, cJSON* v_componentData) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "post", py_cat(X, 2, py_s(X, "/ui/components/"), v_namespace), py_dict(X, 2, "Content-Type", py_s(X, "application/json"), "Accept", py_s(X, "application/json")), py_dumps(X, v_componentData), NULL);
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

cJSON* openhab_ui_addUIComponent(openhab_client_t* client, const char* namespace, const cJSON* componentData) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = ui_addUIComponent_impl(X, py_s(X, namespace), py_arg_json(X, componentData));
    return py_finish(X, r);
}

static cJSON* ui_getUIComponent_impl(py_ctx* X, cJSON* v_namespace, cJSON* v_componentUID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 4, py_s(X, "/ui/components/"), v_namespace, py_s(X, "/"), v_componentUID), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Component not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Component not found."));
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

cJSON* openhab_ui_getUIComponent(openhab_client_t* client, const char* namespace, const char* componentUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = ui_getUIComponent_impl(X, py_s(X, namespace), py_s(X, componentUID));
    return py_finish(X, r);
}

static cJSON* ui_updateUIComponent_impl(py_ctx* X, cJSON* v_namespace, cJSON* v_componentUID, cJSON* v_componentData) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "put", py_cat(X, 4, py_s(X, "/ui/components/"), v_namespace, py_s(X, "/"), v_componentUID), py_dict(X, 2, "Content-Type", py_s(X, "application/json"), "Accept", py_s(X, "application/json")), py_dumps(X, v_componentData), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Component not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Component not found."));
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

cJSON* openhab_ui_updateUIComponent(openhab_client_t* client, const char* namespace, const char* componentUID, const cJSON* componentData) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = ui_updateUIComponent_impl(X, py_s(X, namespace), py_s(X, componentUID), py_arg_json(X, componentData));
    return py_finish(X, r);
}

static cJSON* ui_deleteUIComponent_impl(py_ctx* X, cJSON* v_namespace, cJSON* v_componentUID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "delete", py_cat(X, 4, py_s(X, "/ui/components/"), v_namespace, py_s(X, "/"), v_componentUID), NULL, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Component not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Component not found."));
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

cJSON* openhab_ui_deleteUIComponent(openhab_client_t* client, const char* namespace, const char* componentUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = ui_deleteUIComponent_impl(X, py_s(X, namespace), py_s(X, componentUID));
    return py_finish(X, r);
}

static cJSON* ui_getUITiles_impl(py_ctx* X) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_s(X, "/ui/tiles"), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
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

cJSON* openhab_ui_getUITiles(openhab_client_t* client) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = ui_getUITiles_impl(X);
    return py_finish(X, r);
}
