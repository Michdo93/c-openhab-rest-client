/* Generated from Things.py of python-openhab-rest-client by tools/py2c.py – do not edit. */
#include "../py_rt.h"
#include "openhab/openhab_api.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static cJSON* things_getThings_impl(py_ctx* X, cJSON* v_summary, cJSON* v_staticDataOnly, cJSON* v_language);
static cJSON* things_createThing_impl(py_ctx* X, cJSON* v_thingData, cJSON* v_language);
static cJSON* things_getThing_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language);
static cJSON* things_updateThing_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_thingData, cJSON* v_language);
static cJSON* things_deleteThing_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_force, cJSON* v_language);
static cJSON* things_updateThingConfiguration_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_configurationData, cJSON* v_language);
static cJSON* things_getThingConfigStatus_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language);
static cJSON* things_setThingStatus_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_enabled, cJSON* v_language);
static cJSON* things_enableThing_impl(py_ctx* X, cJSON* v_thingUID);
static cJSON* things_disableThing_impl(py_ctx* X, cJSON* v_thingUID);
static cJSON* things_updateThingFirmware_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_firmwareVersion, cJSON* v_language);
static cJSON* things_getThingFirmwareStatus_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language);
static cJSON* things_getThingFirmwares_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language);
static cJSON* things_getThingStatus_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language);

static cJSON* things_getThings_impl(py_ctx* X, cJSON* v_summary, cJSON* v_staticDataOnly, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_s(X, "/things"), v_headers, NULL, py_dict(X, 2, "summary", v_summary, "staticDataOnly", v_staticDataOnly));
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

cJSON* openhab_things_getThings_(openhab_client_t* client, openhab_things_getThings_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_getThings_impl(X, py_arg_flag(X, a.summary, py_bool(X, 0)), py_arg_flag(X, a.staticDataOnly, py_bool(X, 0)), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_createThing_impl(py_ctx* X, cJSON* v_thingData, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_headers = py_dict(X, 2, "Content-Type", py_s(X, "application/json"), "Accept", py_s(X, "*/*"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "post", py_s(X, "/things"), v_headers, py_dumps(X, v_thingData), NULL);
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
        if (py_eq(v_status_code, py_num(X, 409))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "A thing with the same uid already exists."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 400))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "A uid must be provided, if no binding can create a thing of this type."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "A uid must be provided, if no binding can create a thing of this type."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 409))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "A thing with the same uid already exists."));
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

cJSON* openhab_things_createThing_(openhab_client_t* client, const cJSON* thingData, openhab_things_createThing_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_createThing_impl(X, py_arg_json(X, thingData), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_getThing_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_cat(X, 2, py_s(X, "/things/"), v_thingUID), v_headers, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "THing not found."));
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

cJSON* openhab_things_getThing_(openhab_client_t* client, const char* thingUID, openhab_things_getThing_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_getThing_impl(X, py_s(X, thingUID), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_updateThing_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_thingData, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_headers = py_dict(X, 2, "Content-Type", py_s(X, "application/json"), "Accept", py_s(X, "*/*"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "put", py_cat(X, 2, py_s(X, "/things/"), v_thingUID), v_headers, py_dumps(X, v_thingData), NULL);
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
        if (py_eq(v_status_code, py_num(X, 409))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing could not be updated as it is not editable."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 409))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing could not be updated as it is not editable."));
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

cJSON* openhab_things_updateThing_(openhab_client_t* client, const char* thingUID, const cJSON* thingData, openhab_things_updateThing_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_updateThing_impl(X, py_s(X, thingUID), py_arg_json(X, thingData), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_deleteThing_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_force, cJSON* v_language) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "delete", py_cat(X, 2, py_s(X, "/things/"), v_thingUID), (py_truthy(v_language) ? py_dict(X, 1, "Accept-Language", v_language) : py_dict(X, 0)), NULL, py_dict(X, 1, "force", v_force));
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
        if (py_eq(v_status_code, py_num(X, 409))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing could not be deleted because it's not editable."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
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
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "OK, was deleted."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 202))) {
        {
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "ACCEPTED for asynchronous deletion."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 404))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 409))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing could not be deleted because it's not editable."));
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

cJSON* openhab_things_deleteThing_(openhab_client_t* client, const char* thingUID, openhab_things_deleteThing_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_deleteThing_impl(X, py_s(X, thingUID), py_arg_flag(X, a.force, py_bool(X, 0)), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_updateThingConfiguration_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_configurationData, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_headers = py_dict(X, 2, "Content-Type", py_s(X, "application/json"), "Accept", py_s(X, "*/*"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "put", py_cat(X, 3, py_s(X, "/things/"), v_thingUID, py_s(X, "/config")), v_headers, py_dumps(X, v_configurationData), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Configuration of the thing is not valid."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 409))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing could not be updated as it is not editable."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Configuration of the thing is not valid."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 404))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 409))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing could not be updated as it is not editable."));
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

cJSON* openhab_things_updateThingConfiguration_(openhab_client_t* client, const char* thingUID, const cJSON* configurationData, openhab_things_updateThingConfiguration_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_updateThingConfiguration_impl(X, py_s(X, thingUID), py_arg_json(X, configurationData), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_getThingConfigStatus_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/things/"), v_thingUID, py_s(X, "/config/status")), v_headers, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
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

cJSON* openhab_things_getThingConfigStatus_(openhab_client_t* client, const char* thingUID, openhab_things_getThingConfigStatus_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_getThingConfigStatus_impl(X, py_s(X, thingUID), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_setThingStatus_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_enabled, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_headers = py_dict(X, 2, "Content-Type", py_s(X, "text/plain"), "Accept", py_s(X, "*/*"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "put", py_cat(X, 3, py_s(X, "/things/"), v_thingUID, py_s(X, "/enable")), v_headers, (py_truthy(v_enabled) ? py_s(X, "true") : py_s(X, "false")), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
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

cJSON* openhab_things_setThingStatus_(openhab_client_t* client, const char* thingUID, int enabled, openhab_things_setThingStatus_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_setThingStatus_impl(X, py_s(X, thingUID), py_bool(X, enabled), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_enableThing_impl(py_ctx* X, cJSON* v_thingUID) {
    {
        cJSON* r_ = things_setThingStatus_impl(X, v_thingUID, py_bool(X, 1), py_none(X));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_things_enableThing(openhab_client_t* client, const char* thingUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = things_enableThing_impl(X, py_s(X, thingUID));
    return py_finish(X, r);
}

static cJSON* things_disableThing_impl(py_ctx* X, cJSON* v_thingUID) {
    {
        cJSON* r_ = things_setThingStatus_impl(X, v_thingUID, py_bool(X, 0), py_none(X));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_things_disableThing(openhab_client_t* client, const char* thingUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = things_disableThing_impl(X, py_s(X, thingUID));
    return py_finish(X, r);
}

static cJSON* things_updateThingFirmware_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_firmwareVersion, cJSON* v_language) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "put", py_cat(X, 4, py_s(X, "/things/"), v_thingUID, py_s(X, "/firmware/"), v_firmwareVersion), (py_truthy(v_language) ? py_dict(X, 1, "Accept-Language", v_language) : py_dict(X, 0)), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Firmware update preconditions not satisfied."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Firmware update preconditions not satisfied."));
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

cJSON* openhab_things_updateThingFirmware_(openhab_client_t* client, const char* thingUID, const char* firmwareVersion, openhab_things_updateThingFirmware_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_updateThingFirmware_impl(X, py_s(X, thingUID), py_s(X, firmwareVersion), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_getThingFirmwareStatus_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_headers = py_dict(X, 1, "Accept", py_s(X, "*/*"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/things/"), v_thingUID, py_s(X, "/firmware/status")), v_headers, NULL, NULL);
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
    } else if (py_eq(v_status_code, py_num(X, 204))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "No firmware status provided by this Thing."));
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

cJSON* openhab_things_getThingFirmwareStatus_(openhab_client_t* client, const char* thingUID, openhab_things_getThingFirmwareStatus_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_getThingFirmwareStatus_impl(X, py_s(X, thingUID), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_getThingFirmwares_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/things/"), v_thingUID, py_s(X, "/firmwares")), v_headers, NULL, NULL);
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
    } else if (py_eq(v_status_code, py_num(X, 204))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "No firmwares found."));
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

cJSON* openhab_things_getThingFirmwares_(openhab_client_t* client, const char* thingUID, openhab_things_getThingFirmwares_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_getThingFirmwares_impl(X, py_s(X, thingUID), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* things_getThingStatus_impl(py_ctx* X, cJSON* v_thingUID, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/things/"), v_thingUID, py_s(X, "/status")), v_headers, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Thing not found."));
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

cJSON* openhab_things_getThingStatus_(openhab_client_t* client, const char* thingUID, openhab_things_getThingStatus_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = things_getThingStatus_impl(X, py_s(X, thingUID), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}
