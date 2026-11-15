/* Generated from Items.py of python-openhab-rest-client by tools/py2c.py – do not edit. */
#include "../py_rt.h"
#include "openhab/openhab_api.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static cJSON* items_getItems_impl(py_ctx* X, cJSON* v_type, cJSON* v_tags, cJSON* v_metadata, cJSON* v_recursive, cJSON* v_fields, cJSON* v_staticDataOnly, cJSON* v_language, cJSON* v_parents);
static cJSON* items_addOrUpdateItems_impl(py_ctx* X, cJSON* v_items);
static cJSON* items_getItem_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_metadata, cJSON* v_recursive, cJSON* v_language, cJSON* v_parents);
static cJSON* items_addOrUpdateItem_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_itemData, cJSON* v_language);
static cJSON* items_sendCommand_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_command, cJSON* v_source);
static cJSON* items_postUpdate_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_state, cJSON* v_source);
static cJSON* items_deleteItem_impl(py_ctx* X, cJSON* v_itemName);
static cJSON* items_addGroupMember_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_memberItemName);
static cJSON* items_removeGroupMember_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_memberItemName);
static cJSON* items_addMetadata_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_namespace, cJSON* v_metadata);
static cJSON* items_removeMetadata_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_namespace);
static cJSON* items_getMetadataNamespaces_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_language);
static cJSON* items_getSemanticItem_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_semanticClass, cJSON* v_language);
static cJSON* items_getItemState_impl(py_ctx* X, cJSON* v_itemName);
static cJSON* items_updateItemState_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_state, cJSON* v_language, cJSON* v_source);
static cJSON* items_addTag_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_tag);
static cJSON* items_removeTag_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_tag);
static cJSON* items_purgeOrphanedMetadata_impl(py_ctx* X);

static cJSON* items_getItems_impl(py_ctx* X, cJSON* v_type, cJSON* v_tags, cJSON* v_metadata, cJSON* v_recursive, cJSON* v_fields, cJSON* v_staticDataOnly, cJSON* v_language, cJSON* v_parents) {
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
    v_params = py_dict(X, 7, "type", v_type, "tags", v_tags, "metadata", v_metadata, "recursive", py_lower(X, py_str(X, v_recursive)), "fields", v_fields, "staticDataOnly", py_lower(X, py_str(X, v_staticDataOnly)), "parents", v_parents);
    if (X->exc) return NULL;
    v_params = py_without_none(X, v_params);
    if (X->exc) return NULL;
    /* try */
    v_response = py_http(X, "get", py_s(X, "/items"), v_headers, NULL, v_params);
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

cJSON* openhab_items_getItems_(openhab_client_t* client, openhab_items_getItems_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = items_getItems_impl(X, (a.type ? py_s(X, a.type) : py_none(X)), (a.tags ? py_s(X, a.tags) : py_none(X)), (a.metadata ? py_s(X, a.metadata) : py_s(X, ".*")), py_arg_flag(X, a.recursive, py_bool(X, 0)), (a.fields ? py_s(X, a.fields) : py_none(X)), py_arg_flag(X, a.staticDataOnly, py_bool(X, 0)), (a.language ? py_s(X, a.language) : py_none(X)), py_arg_flag(X, a.parents, py_none(X)));
    return py_finish(X, r);
}

static cJSON* items_addOrUpdateItems_impl(py_ctx* X, cJSON* v_items) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "put", py_s(X, "/items"), py_dict(X, 2, "Content-Type", py_s(X, "application/json"), "Accept", py_s(X, "*/*")), py_dumps(X, v_items), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Payload is invalid."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Payload is invalid."));
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

cJSON* openhab_items_addOrUpdateItems(openhab_client_t* client, const cJSON* items) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = items_addOrUpdateItems_impl(X, py_arg_json(X, items));
    return py_finish(X, r);
}

static cJSON* items_getItem_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_metadata, cJSON* v_recursive, cJSON* v_language, cJSON* v_parents) {
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
    v_params = py_dict(X, 3, "metadata", v_metadata, "recursive", py_lower(X, py_str(X, v_recursive)), "parents", v_parents);
    if (X->exc) return NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 2, py_s(X, "/items/"), v_itemName), v_headers, NULL, v_params);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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

cJSON* openhab_items_getItem_(openhab_client_t* client, const char* itemName, openhab_items_getItem_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = items_getItem_impl(X, py_s(X, itemName), (a.metadata ? py_s(X, a.metadata) : py_s(X, ".*")), py_arg_flag(X, a.recursive, py_bool(X, 1)), (a.language ? py_s(X, a.language) : py_none(X)), py_arg_flag(X, a.parents, py_none(X)));
    return py_finish(X, r);
}

static cJSON* items_addOrUpdateItem_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_itemData, cJSON* v_language) {
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
    v_response = py_http(X, "put", py_cat(X, 2, py_s(X, "/items/"), v_itemName), v_headers, py_dumps(X, v_itemData), NULL);
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
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found or name in path invalid."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 405))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not editable."));
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
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "Item created."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Payload invalid."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 404))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found or name in path invalid."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 405))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not editable."));
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

cJSON* openhab_items_addOrUpdateItem_(openhab_client_t* client, const char* itemName, const cJSON* itemData, openhab_items_addOrUpdateItem_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = items_addOrUpdateItem_impl(X, py_s(X, itemName), py_arg_json(X, itemData), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* items_sendCommand_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_command, cJSON* v_source) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "post", py_cat(X, 2, py_s(X, "/items/"), v_itemName), py_dict(X, 1, "Content-Type", py_s(X, "text/plain")), py_str(X, v_command), py_dict(X, 1, "source", v_source));
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid command for this item."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid command for this item."));
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

cJSON* openhab_items_sendCommand_(openhab_client_t* client, const char* itemName, const char* command, openhab_items_sendCommand_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = items_sendCommand_impl(X, py_s(X, itemName), py_s(X, command), (a.source ? py_s(X, a.source) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* items_postUpdate_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_state, cJSON* v_source) {
    {
        cJSON* r_ = items_updateItemState_impl(X, v_itemName, v_state, py_none(X), v_source);
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_items_postUpdate_(openhab_client_t* client, const char* itemName, const char* state, openhab_items_postUpdate_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = items_postUpdate_impl(X, py_s(X, itemName), py_s(X, state), (a.source ? py_s(X, a.source) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* items_deleteItem_impl(py_ctx* X, cJSON* v_itemName) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "delete", py_cat(X, 2, py_s(X, "/items/"), v_itemName), NULL, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found or item is not editable."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found or item is not editable."));
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

cJSON* openhab_items_deleteItem(openhab_client_t* client, const char* itemName) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = items_deleteItem_impl(X, py_s(X, itemName));
    return py_finish(X, r);
}

static cJSON* items_addGroupMember_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_memberItemName) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "put", py_cat(X, 4, py_s(X, "/items/"), v_itemName, py_s(X, "/members/"), v_memberItemName), NULL, NULL, NULL);
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
        if (py_eq(v_status_code, py_num(X, 405))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Member item is not editable."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item or member item not found or item is not of type group item."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item or member item not found or item is not of type group item."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 405))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Member item is not editable."));
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

cJSON* openhab_items_addGroupMember(openhab_client_t* client, const char* itemName, const char* memberItemName) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = items_addGroupMember_impl(X, py_s(X, itemName), py_s(X, memberItemName));
    return py_finish(X, r);
}

static cJSON* items_removeGroupMember_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_memberItemName) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "delete", py_cat(X, 4, py_s(X, "/items/"), v_itemName, py_s(X, "/members/"), v_memberItemName), NULL, NULL, NULL);
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
        if (py_eq(v_status_code, py_num(X, 405))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Member item is not editable."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item or member item not found or item is not of type group item."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item or member item not found or item is not of type group item."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 405))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Member item is not editable."));
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

cJSON* openhab_items_removeGroupMember(openhab_client_t* client, const char* itemName, const char* memberItemName) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = items_removeGroupMember_impl(X, py_s(X, itemName), py_s(X, memberItemName));
    return py_finish(X, r);
}

static cJSON* items_addMetadata_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_namespace, cJSON* v_metadata) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "put", py_cat(X, 4, py_s(X, "/items/"), v_itemName, py_s(X, "/metadata/"), v_namespace), py_dict(X, 1, "Content-Type", py_s(X, "application/json")), py_dumps(X, v_metadata), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Metadata value empty."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 405))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Metadata not editable."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "Created."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Metadata value empty."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 404))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 405))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Metadata not editable."));
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

cJSON* openhab_items_addMetadata(openhab_client_t* client, const char* itemName, const char* namespace_, const cJSON* metadata) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = items_addMetadata_impl(X, py_s(X, itemName), py_s(X, namespace_), py_arg_json(X, metadata));
    return py_finish(X, r);
}

static cJSON* items_removeMetadata_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_namespace) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "delete", py_cat(X, 4, py_s(X, "/items/"), v_itemName, py_s(X, "/metadata/"), v_namespace), NULL, NULL, NULL);
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
        if (py_eq(v_status_code, py_num(X, 405))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Meta data not editable."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 405))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Meta data not editable."));
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

cJSON* openhab_items_removeMetadata(openhab_client_t* client, const char* itemName, const char* namespace_) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = items_removeMetadata_impl(X, py_s(X, itemName), py_s(X, namespace_));
    return py_finish(X, r);
}

static cJSON* items_getMetadataNamespaces_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/items/"), v_itemName, py_s(X, "/metadata/namespaces")), v_headers, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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

cJSON* openhab_items_getMetadataNamespaces_(openhab_client_t* client, const char* itemName, openhab_items_getMetadataNamespaces_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = items_getMetadataNamespaces_impl(X, py_s(X, itemName), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* items_getSemanticItem_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_semanticClass, cJSON* v_language) {
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
    v_response = py_http(X, "get", py_cat(X, 4, py_s(X, "/items/"), v_itemName, py_s(X, "/semantic/"), v_semanticClass), v_headers, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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

cJSON* openhab_items_getSemanticItem_(openhab_client_t* client, const char* itemName, const char* semanticClass, openhab_items_getSemanticItem_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = items_getSemanticItem_impl(X, py_s(X, itemName), py_s(X, semanticClass), (a.language ? py_s(X, a.language) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* items_getItemState_impl(py_ctx* X, cJSON* v_itemName) {
    cJSON* v_headers = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_headers = py_dict(X, 1, "Accept", py_s(X, "text/plain"));
    if (X->exc) return NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/items/"), v_itemName, py_s(X, "/state")), v_headers, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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

cJSON* openhab_items_getItemState(openhab_client_t* client, const char* itemName) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = items_getItemState_impl(X, py_s(X, itemName));
    return py_finish(X, r);
}

static cJSON* items_updateItemState_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_state, cJSON* v_language, cJSON* v_source) {
    cJSON* v_headers = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    v_headers = py_dict(X, 1, "Content-Type", py_s(X, "text/plain"));
    if (X->exc) return NULL;
    if (py_truthy(v_language)) {
        py_set(X, v_headers, py_s(X, "Accept-Language"), v_language);
        if (X->exc) return NULL;
    }
    /* try */
    v_response = py_http(X, "put", py_cat(X, 3, py_s(X, "/items/"), v_itemName, py_s(X, "/state")), v_headers, py_str(X, v_state), py_dict(X, 1, "source", v_source));
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid state for this item."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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
    if (py_eq(v_status_code, py_num(X, 202))) {
        {
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "Accepted."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 404))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Invalid state for this item."));
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

cJSON* openhab_items_updateItemState_(openhab_client_t* client, const char* itemName, const char* state, openhab_items_updateItemState_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = items_updateItemState_impl(X, py_s(X, itemName), py_s(X, state), (a.language ? py_s(X, a.language) : py_none(X)), (a.source ? py_s(X, a.source) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* items_addTag_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_tag) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "put", py_cat(X, 4, py_s(X, "/items/"), v_itemName, py_s(X, "/tags/"), v_tag), NULL, NULL, NULL);
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
        if (py_eq(v_status_code, py_num(X, 405))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not editable."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 405))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not editable."));
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

cJSON* openhab_items_addTag(openhab_client_t* client, const char* itemName, const char* tag) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = items_addTag_impl(X, py_s(X, itemName), py_s(X, tag));
    return py_finish(X, r);
}

static cJSON* items_removeTag_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_tag) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "delete", py_cat(X, 4, py_s(X, "/items/"), v_itemName, py_s(X, "/tags/"), v_tag), NULL, NULL, NULL);
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
        if (py_eq(v_status_code, py_num(X, 405))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not editable."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not found."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 405))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Item not editable."));
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

cJSON* openhab_items_removeTag(openhab_client_t* client, const char* itemName, const char* tag) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = items_removeTag_impl(X, py_s(X, itemName), py_s(X, tag));
    return py_finish(X, r);
}

static cJSON* items_purgeOrphanedMetadata_impl(py_ctx* X) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "post", py_s(X, "/items/metadata/purge"), NULL, NULL, NULL);
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

cJSON* openhab_items_purgeOrphanedMetadata(openhab_client_t* client) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = items_purgeOrphanedMetadata_impl(X);
    return py_finish(X, r);
}
