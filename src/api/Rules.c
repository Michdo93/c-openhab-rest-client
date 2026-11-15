/* Generated from Rules.py of python-openhab-rest-client by tools/py2c.py – do not edit. */
#include "../py_rt.h"
#include "openhab/openhab_api.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static cJSON* rules_getRules_impl(py_ctx* X, cJSON* v_prefix, cJSON* v_tags, cJSON* v_summary, cJSON* v_staticDataOnly);
static cJSON* rules_createRule_impl(py_ctx* X, cJSON* v_ruleData);
static cJSON* rules_getRule_impl(py_ctx* X, cJSON* v_ruleUID);
static cJSON* rules_updateRule_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_ruleData);
static cJSON* rules_deleteRule_impl(py_ctx* X, cJSON* v_ruleUID);
static cJSON* rules_getModule_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_moduleCategory, cJSON* v_moduleID);
static cJSON* rules_getModuleConfig_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_moduleCategory, cJSON* v_moduleID);
static cJSON* rules_getModuleConfigParam_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_moduleCategory, cJSON* v_moduleID, cJSON* v_param);
static cJSON* rules_setModuleConfigParam_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_moduleCategory, cJSON* v_moduleID, cJSON* v_param, cJSON* v_value);
static cJSON* rules_getActions_impl(py_ctx* X, cJSON* v_ruleUID);
static cJSON* rules_getConditions_impl(py_ctx* X, cJSON* v_ruleUID);
static cJSON* rules_getConfiguration_impl(py_ctx* X, cJSON* v_ruleUID);
static cJSON* rules_updateConfiguration_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_configData);
static cJSON* rules_setRuleState_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_enable);
static cJSON* rules_enable_impl(py_ctx* X, cJSON* v_ruleUID);
static cJSON* rules_disable_impl(py_ctx* X, cJSON* v_ruleUID);
static cJSON* rules_runNow_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_contextData);
static cJSON* rules_getTriggers_impl(py_ctx* X, cJSON* v_ruleUID);
static cJSON* rules_simulateSchedule_impl(py_ctx* X, cJSON* v_fromTime, cJSON* v_untilTime);

static cJSON* rules_getRules_impl(py_ctx* X, cJSON* v_prefix, cJSON* v_tags, cJSON* v_summary, cJSON* v_staticDataOnly) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_s(X, "/rules"), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, py_dict(X, 4, "prefix", v_prefix, "tags", v_tags, "summary", v_summary, "staticDataOnly", v_staticDataOnly));
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

cJSON* openhab_rules_getRules_(openhab_client_t* client, openhab_rules_getRules_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = rules_getRules_impl(X, (a.prefix ? py_s(X, a.prefix) : py_none(X)), (a.tags ? py_s(X, a.tags) : py_none(X)), py_arg_flag(X, a.summary, py_bool(X, 0)), py_arg_flag(X, a.staticDataOnly, py_bool(X, 0)));
    return py_finish(X, r);
}

static cJSON* rules_createRule_impl(py_ctx* X, cJSON* v_ruleData) {
    cJSON* v_location = NULL;
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "post", py_s(X, "/rules"), py_dict(X, 1, "Content-Type", py_s(X, "application/json")), py_dumps(X, v_ruleData), NULL);
    if (X->exc) goto exc_1;
    if (py_isstatus(v_response)) {
        v_status_code = py_get(X, v_response, py_s(X, "status"));
        if (X->exc) goto exc_1;
        v_location = py_getor(X, v_response, py_s(X, "location"), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Creation refused: Missing required parameter."));
                if (X->exc) return NULL;
                return r_;
            }
        } else if (py_eq(v_status_code, py_num(X, 409))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Creation refused: Rule with the same UID already exists."));
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
            cJSON* r_ = py_dict(X, 2, "message", py_s(X, "Rule successfully created."), "location", (py_truthy(v_location) ? v_location : py_s(X, "No Location headers provided.")));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 400))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Creation refused: Missing required parameter."));
            if (X->exc) return NULL;
            return r_;
        }
    } else if (py_eq(v_status_code, py_num(X, 409))) {
        {
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Creation refused: Rule with the same UID already exists."));
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

cJSON* openhab_rules_createRule(openhab_client_t* client, const cJSON* ruleData) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_createRule_impl(X, py_arg_json(X, ruleData));
    return py_finish(X, r);
}

static cJSON* rules_getRule_impl(py_ctx* X, cJSON* v_ruleUID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 2, py_s(X, "/rules/"), v_ruleUID), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule not found."));
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

cJSON* openhab_rules_getRule(openhab_client_t* client, const char* ruleUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_getRule_impl(X, py_s(X, ruleUID));
    return py_finish(X, r);
}

static cJSON* rules_updateRule_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_ruleData) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "put", py_cat(X, 2, py_s(X, "/rules/"), v_ruleUID), py_dict(X, 1, "Content-Type", py_s(X, "application/json")), py_dumps(X, v_ruleData), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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

cJSON* openhab_rules_updateRule(openhab_client_t* client, const char* ruleUID, const cJSON* ruleData) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_updateRule_impl(X, py_s(X, ruleUID), py_arg_json(X, ruleData));
    return py_finish(X, r);
}

static cJSON* rules_deleteRule_impl(py_ctx* X, cJSON* v_ruleUID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "delete", py_cat(X, 2, py_s(X, "/rules/"), v_ruleUID), NULL, NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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

cJSON* openhab_rules_deleteRule(openhab_client_t* client, const char* ruleUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_deleteRule_impl(X, py_s(X, ruleUID));
    return py_finish(X, r);
}

static cJSON* rules_getModule_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_moduleCategory, cJSON* v_moduleID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 6, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/"), v_moduleCategory, py_s(X, "/"), v_moduleID), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found or does not have a module with such Category and ID."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found or does not have a module with such Category and ID."));
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

cJSON* openhab_rules_getModule(openhab_client_t* client, const char* ruleUID, const char* moduleCategory, const char* moduleID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_getModule_impl(X, py_s(X, ruleUID), py_s(X, moduleCategory), py_s(X, moduleID));
    return py_finish(X, r);
}

static cJSON* rules_getModuleConfig_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_moduleCategory, cJSON* v_moduleID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 7, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/"), v_moduleCategory, py_s(X, "/"), v_moduleID, py_s(X, "/config")), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found or does not have a module with such Category and ID."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found or does not have a module with such Category and ID."));
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

cJSON* openhab_rules_getModuleConfig(openhab_client_t* client, const char* ruleUID, const char* moduleCategory, const char* moduleID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_getModuleConfig_impl(X, py_s(X, ruleUID), py_s(X, moduleCategory), py_s(X, moduleID));
    return py_finish(X, r);
}

static cJSON* rules_getModuleConfigParam_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_moduleCategory, cJSON* v_moduleID, cJSON* v_param) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 8, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/"), v_moduleCategory, py_s(X, "/"), v_moduleID, py_s(X, "/config/"), v_param), py_dict(X, 1, "Accept", py_s(X, "text/plain")), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found or does not have a module with such Category and ID."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found or does not have a module with such Category and ID."));
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

cJSON* openhab_rules_getModuleConfigParam(openhab_client_t* client, const char* ruleUID, const char* moduleCategory, const char* moduleID, const char* param) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_getModuleConfigParam_impl(X, py_s(X, ruleUID), py_s(X, moduleCategory), py_s(X, moduleID), py_s(X, param));
    return py_finish(X, r);
}

static cJSON* rules_setModuleConfigParam_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_moduleCategory, cJSON* v_moduleID, cJSON* v_param, cJSON* v_value) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "put", py_cat(X, 8, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/"), v_moduleCategory, py_s(X, "/"), v_moduleID, py_s(X, "/config/"), v_param), py_dict(X, 1, "Content-Type", py_s(X, "text/plain")), py_str(X, v_value), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found or does not have a module with such Category and ID."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found or does not have a module with such Category and ID."));
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

cJSON* openhab_rules_setModuleConfigParam(openhab_client_t* client, const char* ruleUID, const char* moduleCategory, const char* moduleID, const char* param, const char* value) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_setModuleConfigParam_impl(X, py_s(X, ruleUID), py_s(X, moduleCategory), py_s(X, moduleID), py_s(X, param), py_s(X, value));
    return py_finish(X, r);
}

static cJSON* rules_getActions_impl(py_ctx* X, cJSON* v_ruleUID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/actions")), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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

cJSON* openhab_rules_getActions(openhab_client_t* client, const char* ruleUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_getActions_impl(X, py_s(X, ruleUID));
    return py_finish(X, r);
}

static cJSON* rules_getConditions_impl(py_ctx* X, cJSON* v_ruleUID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/conditions")), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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

cJSON* openhab_rules_getConditions(openhab_client_t* client, const char* ruleUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_getConditions_impl(X, py_s(X, ruleUID));
    return py_finish(X, r);
}

static cJSON* rules_getConfiguration_impl(py_ctx* X, cJSON* v_ruleUID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/config")), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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

cJSON* openhab_rules_getConfiguration(openhab_client_t* client, const char* ruleUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_getConfiguration_impl(X, py_s(X, ruleUID));
    return py_finish(X, r);
}

static cJSON* rules_updateConfiguration_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_configData) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "put", py_cat(X, 3, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/config")), py_dict(X, 1, "Content-Type", py_s(X, "application/json")), py_dumps(X, v_configData), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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

cJSON* openhab_rules_updateConfiguration(openhab_client_t* client, const char* ruleUID, const cJSON* configData) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_updateConfiguration_impl(X, py_s(X, ruleUID), py_arg_json(X, configData));
    return py_finish(X, r);
}

static cJSON* rules_setRuleState_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_enable) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "post", py_cat(X, 3, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/enable")), py_dict(X, 1, "Content-Type", py_s(X, "text/plain")), (py_truthy(v_enable) ? py_s(X, "true") : py_s(X, "false")), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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

cJSON* openhab_rules_setRuleState(openhab_client_t* client, const char* ruleUID, int enable) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_setRuleState_impl(X, py_s(X, ruleUID), py_bool(X, enable));
    return py_finish(X, r);
}

static cJSON* rules_enable_impl(py_ctx* X, cJSON* v_ruleUID) {
    {
        cJSON* r_ = rules_setRuleState_impl(X, v_ruleUID, py_bool(X, 1));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_rules_enable(openhab_client_t* client, const char* ruleUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_enable_impl(X, py_s(X, ruleUID));
    return py_finish(X, r);
}

static cJSON* rules_disable_impl(py_ctx* X, cJSON* v_ruleUID) {
    {
        cJSON* r_ = rules_setRuleState_impl(X, v_ruleUID, py_bool(X, 0));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_rules_disable(openhab_client_t* client, const char* ruleUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_disable_impl(X, py_s(X, ruleUID));
    return py_finish(X, r);
}

static cJSON* rules_runNow_impl(py_ctx* X, cJSON* v_ruleUID, cJSON* v_contextData) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "post", py_cat(X, 3, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/runnow")), py_dict(X, 2, "Content-Type", py_s(X, "application/json"), "Accept", py_s(X, "application/json")), py_dumps(X, py_or(v_contextData, py_dict(X, 0))), NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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

cJSON* openhab_rules_runNow_(openhab_client_t* client, const char* ruleUID, openhab_rules_runNow_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    cJSON* r = rules_runNow_impl(X, py_s(X, ruleUID), (a.contextData ? py_arg_json(X, a.contextData) : py_none(X)));
    return py_finish(X, r);
}

static cJSON* rules_getTriggers_impl(py_ctx* X, cJSON* v_ruleUID) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_cat(X, 3, py_s(X, "/rules/"), v_ruleUID, py_s(X, "/triggers")), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, NULL);
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Rule corresponding to the given UID was not found."));
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

cJSON* openhab_rules_getTriggers(openhab_client_t* client, const char* ruleUID) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_getTriggers_impl(X, py_s(X, ruleUID));
    return py_finish(X, r);
}

static cJSON* rules_simulateSchedule_impl(py_ctx* X, cJSON* v_fromTime, cJSON* v_untilTime) {
    cJSON* v_response = NULL;
    cJSON* v_status_code = NULL;
    /* try */
    v_response = py_http(X, "get", py_s(X, "/rules/schedule/simulations"), py_dict(X, 1, "Accept", py_s(X, "application/json")), NULL, py_dict(X, 2, "from", v_fromTime, "until", v_untilTime));
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
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "The max. simulation duration of 180 days is exceeded."));
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
            cJSON* r_ = py_dict(X, 1, "error", py_s(X, "The max. simulation duration of 180 days is exceeded."));
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

cJSON* openhab_rules_simulateSchedule(openhab_client_t* client, const char* fromTime, const char* untilTime) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = rules_simulateSchedule_impl(X, py_s(X, fromTime), py_s(X, untilTime));
    return py_finish(X, r);
}
