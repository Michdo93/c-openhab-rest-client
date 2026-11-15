/* Generated from Addons.py of python-openhab-rest-client by tools/py2c.py – do not edit. */
#include "../py_rt.h"
#include "openhab/openhab_api.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static cJSON* addons_getAddons_impl(py_ctx* X, cJSON* v_serviceID, cJSON* v_language);
static cJSON* addons_getAddon_impl(py_ctx* X, cJSON* v_addonID, cJSON* v_serviceID, cJSON* v_language);
static cJSON* addons_getAddonConfig_impl(py_ctx* X, cJSON* v_addonID, cJSON* v_serviceID);
static cJSON* addons_updateAddonConfig_impl(py_ctx* X, cJSON* v_addonID, cJSON* v_configData, cJSON* v_serviceID);
static cJSON* addons_installAddon_impl(py_ctx* X, cJSON* v_addonID, cJSON* v_serviceID);
static cJSON* addons_uninstallAddon_impl(py_ctx* X, cJSON* v_addonID, cJSON* v_serviceID);
static cJSON* addons_getAddonServices_impl(py_ctx* X, cJSON* v_language);
static cJSON* addons_getAddonSuggestions_impl(py_ctx* X, cJSON* v_language);
static cJSON* addons_getAddonTypes_impl(py_ctx* X, cJSON* v_serviceID, cJSON* v_language);
static cJSON* addons_installAddonFromUrl_impl(py_ctx* X, cJSON* v_url);

static cJSON* addons_getAddons_impl(py_ctx* X, cJSON* v_serviceID, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_params = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_params = (py_truthy(v_serviceID) ? py_dict(X, 1, "serviceId", v_serviceID) : py_dict(X, 0));
    if (X->exc) return NULL;
    v_headers = py_dict(X, 1, "Accept", py_s(X, "application/json"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "get", py_s(X, "/addons"), v_headers, NULL, v_params);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Service not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Service not found."));
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

cJSON* openhab_addons_getAddons_(openhab_client_t* client, openhab_addons_getAddons_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = addons_getAddons_impl(X, (a.serviceID ? py_s(X, a.serviceID) : py_none(X)), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* addons_getAddon_impl(py_ctx* X, cJSON* v_addonID, cJSON* v_serviceID, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_params = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_params = (py_truthy(v_serviceID) ? py_dict(X, 1, "serviceId", v_serviceID) : py_dict(X, 0));
    if (X->exc) return NULL;
    v_headers = py_dict(X, 1, "Accept", py_s(X, "application/json"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "get", py_cat(X, 2, py_s(X, "/addons/"), v_addonID), v_headers, NULL, v_params);
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
    }
    {
        cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Unexpected response: "), v_status_code));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_addons_getAddon_(openhab_client_t* client, const char* addonID, openhab_addons_getAddon_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = addons_getAddon_impl(X, py_s(X, addonID), (a.serviceID ? py_s(X, a.serviceID) : py_none(X)), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* addons_getAddonConfig_impl(py_ctx* X, cJSON* v_addonID, cJSON* v_serviceID) {
    cJSON* v_params = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_params = (py_truthy(v_serviceID) ? py_dict(X, 1, "serviceId", v_serviceID) : py_dict(X, 0));
    if (X->exc) return NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/addons/"), v_addonID, py_s(X, "/config")), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, v_params);
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
        if (py_eq(v_status_code, py_num(X, 500))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Configuration can not be read due to internal error."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Add-on does not exist."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Add-on does not exist."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 500))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Configuration can not be read due to internal error."));
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

cJSON* openhab_addons_getAddonConfig_(openhab_client_t* client, const char* addonID, openhab_addons_getAddonConfig_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = addons_getAddonConfig_impl(X, py_s(X, addonID), (a.serviceID ? py_s(X, a.serviceID) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* addons_updateAddonConfig_impl(py_ctx* X, cJSON* v_addonID, cJSON* v_configData, cJSON* v_serviceID) {
    cJSON* v_data = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_data = py_copy(X, v_configData);
    if (X->exc) return NULL;
    /* try */
    v_response = py_http(X, "put", py_cat(X, 3, py_s(X, "/addons/"), v_addonID, py_s(X, "/config")), py_dict(X, 2, "Content-Type", py_s(X, "application/json"), "Accept", py_s(X, "application/json")), py_dumps(X, v_data), py_dict(X, 1, "serviceId", v_serviceID));
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
        if (py_eq(v_status_code, py_num(X, 500))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Configuration can not be updated due to internal error."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Add-on does not exist."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Add-on does not exist."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 500))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Configuration can not be updated due to internal error."));
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

cJSON* openhab_addons_updateAddonConfig_(openhab_client_t* client, const char* addonID, const cJSON* configData, openhab_addons_updateAddonConfig_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = addons_updateAddonConfig_impl(X, py_s(X, addonID), py_arg_json(X, configData), (a.serviceID ? py_s(X, a.serviceID) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* addons_installAddon_impl(py_ctx* X, cJSON* v_addonID, cJSON* v_serviceID) {
    cJSON* v_data = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_data = (py_truthy(v_serviceID) ? py_dict(X, 1, "serviceId", v_serviceID) : py_dict(X, 0));
    if (X->exc) return NULL;
    /* try */
    v_response = py_http(X, "post", py_cat(X, 3, py_s(X, "/addons/"), v_addonID, py_s(X, "/install")), NULL, NULL, v_data);
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
    }
    {
        cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Unexpected response: "), v_status_code));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_addons_installAddon_(openhab_client_t* client, const char* addonID, openhab_addons_installAddon_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = addons_installAddon_impl(X, py_s(X, addonID), (a.serviceID ? py_s(X, a.serviceID) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* addons_uninstallAddon_impl(py_ctx* X, cJSON* v_addonID, cJSON* v_serviceID) {
    cJSON* v_data = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_data = (py_truthy(v_serviceID) ? py_dict(X, 1, "serviceId", v_serviceID) : py_dict(X, 0));
    if (X->exc) return NULL;
    /* try */
    v_response = py_http(X, "post", py_cat(X, 3, py_s(X, "/addons/"), v_addonID, py_s(X, "/uninstall")), NULL, NULL, v_data);
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
    }
    {
        cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Unexpected response: "), v_status_code));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_addons_uninstallAddon_(openhab_client_t* client, const char* addonID, openhab_addons_uninstallAddon_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = addons_uninstallAddon_impl(X, py_s(X, addonID), (a.serviceID ? py_s(X, a.serviceID) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* addons_getAddonServices_impl(py_ctx* X, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_s(X, "/addons/services"), v_headers, NULL, py_none(X));
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

cJSON* openhab_addons_getAddonServices_(openhab_client_t* client, openhab_addons_getAddonServices_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = addons_getAddonServices_impl(X, (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* addons_getAddonSuggestions_impl(py_ctx* X, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_s(X, "/addons/suggestions"), v_headers, NULL, py_none(X));
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

cJSON* openhab_addons_getAddonSuggestions_(openhab_client_t* client, openhab_addons_getAddonSuggestions_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = addons_getAddonSuggestions_impl(X, (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* addons_getAddonTypes_impl(py_ctx* X, cJSON* v_serviceID, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_params = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_params = (py_truthy(v_serviceID) ? py_dict(X, 1, "serviceId", v_serviceID) : py_dict(X, 0));
    if (X->exc) return NULL;
    v_headers = py_dict(X, 1, "Accept", py_s(X, "application/json"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "get", py_s(X, "/addons/types"), v_headers, NULL, v_params);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Service not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Service not found."));
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

cJSON* openhab_addons_getAddonTypes_(openhab_client_t* client, openhab_addons_getAddonTypes_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = addons_getAddonTypes_impl(X, (a.serviceID ? py_s(X, a.serviceID) : py_none(X)), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* addons_installAddonFromUrl_impl(py_ctx* X, cJSON* v_url) {
    cJSON* v_encoded_url = NULL;
    cJSON* v_endpoint = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_encoded_url = py_quote(X, v_url, "");
    if (X->exc) return NULL;
    v_endpoint = py_cat(X, 3, py_s(X, "/addons/url/"), v_encoded_url, py_s(X, "/install"));
    if (X->exc) return NULL;
    /* try */
    v_response = py_http(X, "post", v_endpoint, NULL, py_none(X), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "The given URL is malformed or not valid."));
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
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "The given URL is malformed or not valid."));
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

cJSON* openhab_addons_installAddonFromUrl(openhab_client_t* client, const char* url) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = addons_installAddonFromUrl_impl(X, py_s(X, url));
    return py_finish(X, r);
}
