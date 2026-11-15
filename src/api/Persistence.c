/* Generated from Persistence.py of python-openhab-rest-client by tools/py2c.py – do not edit. */
#include "../py_rt.h"
#include "openhab/openhab_api.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static cJSON* persistence_getServices_impl(py_ctx* X, cJSON* v_language);
static cJSON* persistence_getServiceConfiguration_impl(py_ctx* X, cJSON* v_serviceID);
static cJSON* persistence_setServiceConfiguration_impl(py_ctx* X, cJSON* v_serviceID, cJSON* v_config);
static cJSON* persistence_deleteServiceConfiguration_impl(py_ctx* X, cJSON* v_serviceID);
static cJSON* persistence_getItemsFromService_impl(py_ctx* X, cJSON* v_serviceID, cJSON* v_itemName);
static cJSON* persistence_getItemPersistenceData_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_serviceID, cJSON* v_startTime, cJSON* v_endTime, cJSON* v_page, cJSON* v_pageLength, cJSON* v_boundary, cJSON* v_itemState, cJSON* v_displayState, cJSON* v_language);
static cJSON* persistence_storeItemData_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_time, cJSON* v_state, cJSON* v_serviceID);
static cJSON* persistence_deleteItemData_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_startTime, cJSON* v_endTime, cJSON* v_serviceID);

static cJSON* persistence_getServices_impl(py_ctx* X, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_s(X, "/persistence"), v_headers, NULL, NULL);
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

cJSON* openhab_persistence_getServices_(openhab_client_t* client, openhab_persistence_getServices_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = persistence_getServices_impl(X, (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* persistence_getServiceConfiguration_impl(py_ctx* X, cJSON* v_serviceID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 2, py_s(X, "/persistence/"), v_serviceID), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Service configuration not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Service configuration not found."));
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

cJSON* openhab_persistence_getServiceConfiguration(openhab_client_t* client, const char* serviceID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = persistence_getServiceConfiguration_impl(X, py_s(X, serviceID));
    return py_finish(X, r);
}

static cJSON* persistence_setServiceConfiguration_impl(py_ctx* X, cJSON* v_serviceID, cJSON* v_config) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    py_set(X, v_config, py_s(X, "serviceId"), v_serviceID);
    if (X->exc) goto exc_1;
    v_response = py_http(X, "put", py_cat(X, 2, py_s(X, "/persistence/"), v_serviceID), py_dict(X, 2, "Content-Type", py_s(X, "application/json"), "Accept", py_s(X, "application/json")), py_dumps(X, v_config), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Payload invalid."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 405))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "PersistenceServiceConfiguration not editable."));
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
    } else if (py_eq(v_status_code, py_num(X, 201))) {
        {
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "PersistenceServiceConfiguration created."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Payload invalid."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 405))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "PersistenceServiceConfiguration not editable."));
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

cJSON* openhab_persistence_setServiceConfiguration(openhab_client_t* client, const char* serviceID, const cJSON* config) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = persistence_setServiceConfiguration_impl(X, py_s(X, serviceID), py_arg_json(X, config));
    return py_finish(X, r);
}

static cJSON* persistence_deleteServiceConfiguration_impl(py_ctx* X, cJSON* v_serviceID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "delete", py_cat(X, 2, py_s(X, "/persistence/"), v_serviceID), NULL, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Payload invalid."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 405))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "PersistenceServiceConfiguration not editable."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Payload invalid."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 405))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "PersistenceServiceConfiguration not editable."));
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

cJSON* openhab_persistence_deleteServiceConfiguration(openhab_client_t* client, const char* serviceID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = persistence_deleteServiceConfiguration_impl(X, py_s(X, serviceID));
    return py_finish(X, r);
}

static cJSON* persistence_getItemsFromService_impl(py_ctx* X, cJSON* v_serviceID, cJSON* v_itemName) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_s(X, "/persistence/items"), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, py_dict(X, 2, "serviceId", v_serviceID, "itemName", v_itemName));
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Unknown persistence service."));
                if (X->exc) return NULL;
                return r_;
            }
        }
        if (py_eq(v_status_code, py_num(X, 405))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "The persistence service does not provide item information."));
                if (X->exc) return NULL;
                return r_;
            }
        }
        {
            cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 4, py_s(X, "HTTP error "), v_status_code, py_s(X, ": "), py_exc_str(X)));
            if (X->exc) return NULL;
            return r_;
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
    }
    {
        cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Unexpected response: "), v_status_code));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_persistence_getItemsFromService_(openhab_client_t* client, openhab_persistence_getItemsFromService_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = persistence_getItemsFromService_impl(X, (a.serviceID ? py_s(X, a.serviceID) : py_none(X)), (a.itemName ? py_s(X, a.itemName) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* persistence_getItemPersistenceData_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_serviceID, cJSON* v_startTime, cJSON* v_endTime, cJSON* v_page, cJSON* v_pageLength, cJSON* v_boundary, cJSON* v_itemState, cJSON* v_displayState, cJSON* v_language) {
    cJSON* v_headers = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    if (py_truthy(py_and(py_bool(X, !py_isnone(v_pageLength)), py_bool(X, py_isnone(v_page))))) {
        v_page = py_num(X, 0);
        if (X->exc) return NULL;
    }
    v_headers = py_dict(X, 1, "Accept", py_s(X, "application/json"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "get", py_cat(X, 2, py_s(X, "/persistence/items/"), v_itemName), v_headers, NULL, py_dict(X, 8, "serviceId", v_serviceID, "starttime", v_startTime, "endtime", v_endTime, "page", v_page, "pagelength", v_pageLength, "boundary", v_boundary, "itemState", v_itemState, "displayState", v_displayState));
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Unknown Item or persistence service."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Unknown Item or persistence service."));
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

cJSON* openhab_persistence_getItemPersistenceData_(openhab_client_t* client, const char* itemName, openhab_persistence_getItemPersistenceData_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = persistence_getItemPersistenceData_impl(X, py_s(X, itemName), (a.serviceID ? py_s(X, a.serviceID) : py_none(X)), (a.startTime ? py_s(X, a.startTime) : py_none(X)), (a.endTime ? py_s(X, a.endTime) : py_none(X)), (a.page ? py_num(X, a.page) : py_none(X)), (a.pageLength ? py_num(X, a.pageLength) : py_none(X)), py_arg_flag(X, a.boundary, py_bool(X, 0)), py_arg_flag(X, a.itemState, py_bool(X, 0)), py_arg_flag(X, a.displayState, py_none(X)), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* persistence_storeItemData_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_time, cJSON* v_state, cJSON* v_serviceID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "put", py_cat(X, 2, py_s(X, "/persistence/items/"), v_itemName), NULL, NULL, py_dict(X, 3, "serviceId", v_serviceID, "time", v_time, "state", v_state));
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Unknown Item or persistence service."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Unknown Item or persistence service."));
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

cJSON* openhab_persistence_storeItemData_(openhab_client_t* client, const char* itemName, const char* time, const char* state, openhab_persistence_storeItemData_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = persistence_storeItemData_impl(X, py_s(X, itemName), py_s(X, time), py_s(X, state), (a.serviceID ? py_s(X, a.serviceID) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* persistence_deleteItemData_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_startTime, cJSON* v_endTime, cJSON* v_serviceID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "delete", py_cat(X, 2, py_s(X, "/persistence/items/"), v_itemName), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, py_dict(X, 3, "serviceId", v_serviceID, "starttime", v_startTime, "endtime", v_endTime));
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
                cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Invalid filter parameters or service not modifiable: "), py_exc_str(X)));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Unknown persistence service."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Unknown persistence service."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid filter parameters."));
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

cJSON* openhab_persistence_deleteItemData(openhab_client_t* client, const char* itemName, const char* startTime, const char* endTime, const char* serviceID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = persistence_deleteItemData_impl(X, py_s(X, itemName), py_s(X, startTime), py_s(X, endTime), py_s(X, serviceID));
    return py_finish(X, r);
}
