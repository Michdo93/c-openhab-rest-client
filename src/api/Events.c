/* Generated from Events.py of python-openhab-rest-client by tools/py2c.py – do not edit. */
#include "../py_rt.h"
#include "openhab/openhab_api.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static openhab_sse_t* events_getEvents_impl(py_ctx* X, cJSON* v_topics);
static openhab_sse_t* events_initiateStateTracker_impl(py_ctx* X);
static cJSON* events_updateSSEConnectionItems_impl(py_ctx* X, cJSON* v_connectionID, cJSON* v_items);

static openhab_sse_t* events_getEvents_impl(py_ctx* X, cJSON* v_topics) {
    {
        openhab_sse_t* r_ = py_open_stream(X, v_topics, NULL, NULL, py_dict(X, 1, "400", py_s(X, "Topic is empty or contains invalid characters.")));
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_events_getEvents_(openhab_client_t* client, openhab_events_getEvents_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = events_getEvents_impl(X, (a.topics ? py_s(X, a.topics) : py_none(X)));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* events_initiateStateTracker_impl(py_ctx* X) {
    {
        openhab_sse_t* r_ = py_open_stream(X, NULL, py_s(X, "/rest/events/states"), py_dict(X, 1, "Accept", py_s(X, "*/*")), NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_events_initiateStateTracker(openhab_client_t* client) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    openhab_sse_t* s = events_initiateStateTracker_impl(X);
    return py_finish_stream(X, s, NULL);
}

static cJSON* events_updateSSEConnectionItems_impl(py_ctx* X, cJSON* v_connectionID, cJSON* v_items) {
    cJSON* v_response = NULL;
    cJSON* v_statusCode = NULL;
    /* try */
    v_response = py_http(X, "post", py_cat(X, 2, py_s(X, "/events/states/"), v_connectionID), py_dict(X, 1, "Content-Type", py_s(X, "application/json")), py_dumps(X, v_items), NULL);
    if (X->exc) goto exc_1;
    if (py_isstatus(v_response)) {
        v_statusCode = py_get(X, v_response, py_s(X, "status"));
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
        v_statusCode = py_exc_status(X);
        if (X->exc) return NULL;
        if (py_eq(v_statusCode, py_num(X, 404))) {
            {
                cJSON* r_ = py_dict(X, 1, "error", py_s(X, "Unknown connectionID."));
                if (X->exc) return NULL;
                return r_;
            }
        }
        {
            cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 4, py_s(X, "HTTP error "), v_statusCode, py_s(X, ": "), py_exc_str(X)));
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
    if (py_eq(v_statusCode, py_num(X, 200))) {
        {
            cJSON* r_ = py_dict(X, 1, "message", py_s(X, "OK"));
            if (X->exc) return NULL;
            return r_;
        }
    }
    {
        cJSON* r_ = py_dict(X, 1, "error", py_cat(X, 2, py_s(X, "Unexpected response: "), v_statusCode));
        if (X->exc) return NULL;
        return r_;
    }
}

cJSON* openhab_events_updateSSEConnectionItems(openhab_client_t* client, const char* connectionID, const cJSON* items) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    cJSON* r = events_updateSSEConnectionItems_impl(X, py_s(X, connectionID), py_arg_json(X, items));
    return py_finish(X, r);
}

static openhab_sse_t* item_events_ItemEvent_impl(py_ctx* X);
static openhab_sse_t* item_events_ItemAddedEvent_impl(py_ctx* X, cJSON* v_itemName);
static openhab_sse_t* item_events_ItemRemovedEvent_impl(py_ctx* X, cJSON* v_itemName);
static openhab_sse_t* item_events_ItemUpdatedEvent_impl(py_ctx* X, cJSON* v_itemName);
static openhab_sse_t* item_events_ItemCommandEvent_impl(py_ctx* X, cJSON* v_itemName);
static openhab_sse_t* item_events_ItemStateEvent_impl(py_ctx* X, cJSON* v_itemName);
static openhab_sse_t* item_events_ItemStatePredictedEvent_impl(py_ctx* X, cJSON* v_itemName);
static openhab_sse_t* item_events_ItemStateChangedEvent_impl(py_ctx* X, cJSON* v_itemName);
static openhab_sse_t* item_events_GroupItemStateChangedEvent_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_memberName);

static openhab_sse_t* item_events_ItemEvent_impl(py_ctx* X) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_s(X, "openhab/items/*"), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_item_events_ItemEvent(openhab_client_t* client) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    openhab_sse_t* s = item_events_ItemEvent_impl(X);
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* item_events_ItemAddedEvent_impl(py_ctx* X, cJSON* v_itemName) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/items/"), v_itemName, py_s(X, "/added")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_item_events_ItemAddedEvent_(openhab_client_t* client, openhab_item_events_ItemAddedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = item_events_ItemAddedEvent_impl(X, (a.itemName ? py_s(X, a.itemName) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* item_events_ItemRemovedEvent_impl(py_ctx* X, cJSON* v_itemName) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/items/"), v_itemName, py_s(X, "/removed")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_item_events_ItemRemovedEvent_(openhab_client_t* client, openhab_item_events_ItemRemovedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = item_events_ItemRemovedEvent_impl(X, (a.itemName ? py_s(X, a.itemName) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* item_events_ItemUpdatedEvent_impl(py_ctx* X, cJSON* v_itemName) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/items/"), v_itemName, py_s(X, "/updated")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_item_events_ItemUpdatedEvent_(openhab_client_t* client, openhab_item_events_ItemUpdatedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = item_events_ItemUpdatedEvent_impl(X, (a.itemName ? py_s(X, a.itemName) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* item_events_ItemCommandEvent_impl(py_ctx* X, cJSON* v_itemName) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/items/"), v_itemName, py_s(X, "/command")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_item_events_ItemCommandEvent_(openhab_client_t* client, openhab_item_events_ItemCommandEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = item_events_ItemCommandEvent_impl(X, (a.itemName ? py_s(X, a.itemName) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* item_events_ItemStateEvent_impl(py_ctx* X, cJSON* v_itemName) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/items/"), v_itemName, py_s(X, "/state")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_item_events_ItemStateEvent_(openhab_client_t* client, openhab_item_events_ItemStateEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = item_events_ItemStateEvent_impl(X, (a.itemName ? py_s(X, a.itemName) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* item_events_ItemStatePredictedEvent_impl(py_ctx* X, cJSON* v_itemName) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/items/"), v_itemName, py_s(X, "/statepredicted")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_item_events_ItemStatePredictedEvent_(openhab_client_t* client, openhab_item_events_ItemStatePredictedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = item_events_ItemStatePredictedEvent_impl(X, (a.itemName ? py_s(X, a.itemName) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* item_events_ItemStateChangedEvent_impl(py_ctx* X, cJSON* v_itemName) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/items/"), v_itemName, py_s(X, "/statechanged")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_item_events_ItemStateChangedEvent_(openhab_client_t* client, openhab_item_events_ItemStateChangedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = item_events_ItemStateChangedEvent_impl(X, (a.itemName ? py_s(X, a.itemName) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* item_events_GroupItemStateChangedEvent_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_memberName) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 5, py_s(X, "openhab/items/"), v_itemName, py_s(X, "/"), v_memberName, py_s(X, "/statechanged")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_item_events_GroupItemStateChangedEvent_(openhab_client_t* client, openhab_item_events_GroupItemStateChangedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = item_events_GroupItemStateChangedEvent_impl(X, (a.itemName ? py_s(X, a.itemName) : py_s(X, "*")), (a.memberName ? py_s(X, a.memberName) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* thing_events_ThingAddedEvent_impl(py_ctx* X, cJSON* v_thingUID);
static openhab_sse_t* thing_events_ThingRemovedEvent_impl(py_ctx* X, cJSON* v_thingUID);
static openhab_sse_t* thing_events_ThingUpdatedEvent_impl(py_ctx* X, cJSON* v_thingUID);
static openhab_sse_t* thing_events_ThingStatusInfoEvent_impl(py_ctx* X, cJSON* v_thingUID);
static openhab_sse_t* thing_events_ThingStatusInfoChangedEvent_impl(py_ctx* X, cJSON* v_thingUID);

static openhab_sse_t* thing_events_ThingAddedEvent_impl(py_ctx* X, cJSON* v_thingUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/things/"), v_thingUID, py_s(X, "/added")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_thing_events_ThingAddedEvent_(openhab_client_t* client, openhab_thing_events_ThingAddedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = thing_events_ThingAddedEvent_impl(X, (a.thingUID ? py_s(X, a.thingUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* thing_events_ThingRemovedEvent_impl(py_ctx* X, cJSON* v_thingUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/things/"), v_thingUID, py_s(X, "/removed")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_thing_events_ThingRemovedEvent_(openhab_client_t* client, openhab_thing_events_ThingRemovedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = thing_events_ThingRemovedEvent_impl(X, (a.thingUID ? py_s(X, a.thingUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* thing_events_ThingUpdatedEvent_impl(py_ctx* X, cJSON* v_thingUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/things/"), v_thingUID, py_s(X, "/updated")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_thing_events_ThingUpdatedEvent_(openhab_client_t* client, openhab_thing_events_ThingUpdatedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = thing_events_ThingUpdatedEvent_impl(X, (a.thingUID ? py_s(X, a.thingUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* thing_events_ThingStatusInfoEvent_impl(py_ctx* X, cJSON* v_thingUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/things/"), v_thingUID, py_s(X, "/status")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_thing_events_ThingStatusInfoEvent_(openhab_client_t* client, openhab_thing_events_ThingStatusInfoEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = thing_events_ThingStatusInfoEvent_impl(X, (a.thingUID ? py_s(X, a.thingUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* thing_events_ThingStatusInfoChangedEvent_impl(py_ctx* X, cJSON* v_thingUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/things/"), v_thingUID, py_s(X, "/statuschanged")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_thing_events_ThingStatusInfoChangedEvent_(openhab_client_t* client, openhab_thing_events_ThingStatusInfoChangedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = thing_events_ThingStatusInfoChangedEvent_impl(X, (a.thingUID ? py_s(X, a.thingUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* inbox_events_InboxAddedEvent_impl(py_ctx* X, cJSON* v_thingUID);
static openhab_sse_t* inbox_events_InboxRemovedEvent_impl(py_ctx* X, cJSON* v_thingUID);
static openhab_sse_t* inbox_events_InboxUpdatedEvent_impl(py_ctx* X, cJSON* v_thingUID);

static openhab_sse_t* inbox_events_InboxAddedEvent_impl(py_ctx* X, cJSON* v_thingUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/inbox/"), v_thingUID, py_s(X, "/added")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_inbox_events_InboxAddedEvent_(openhab_client_t* client, openhab_inbox_events_InboxAddedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = inbox_events_InboxAddedEvent_impl(X, (a.thingUID ? py_s(X, a.thingUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* inbox_events_InboxRemovedEvent_impl(py_ctx* X, cJSON* v_thingUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/inbox/"), v_thingUID, py_s(X, "/removed")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_inbox_events_InboxRemovedEvent_(openhab_client_t* client, openhab_inbox_events_InboxRemovedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = inbox_events_InboxRemovedEvent_impl(X, (a.thingUID ? py_s(X, a.thingUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* inbox_events_InboxUpdatedEvent_impl(py_ctx* X, cJSON* v_thingUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/inbox/"), v_thingUID, py_s(X, "/updated")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_inbox_events_InboxUpdatedEvent_(openhab_client_t* client, openhab_inbox_events_InboxUpdatedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = inbox_events_InboxUpdatedEvent_impl(X, (a.thingUID ? py_s(X, a.thingUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* link_events_ItemChannelLinkAddedEvent_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_channelUID);
static openhab_sse_t* link_events_ItemChannelLinkRemovedEvent_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_channelUID);

static openhab_sse_t* link_events_ItemChannelLinkAddedEvent_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_channelUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 5, py_s(X, "openhab/links/"), v_itemName, py_s(X, "-"), v_channelUID, py_s(X, "/added")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_link_events_ItemChannelLinkAddedEvent_(openhab_client_t* client, openhab_link_events_ItemChannelLinkAddedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = link_events_ItemChannelLinkAddedEvent_impl(X, (a.itemName ? py_s(X, a.itemName) : py_s(X, "*")), (a.channelUID ? py_s(X, a.channelUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* link_events_ItemChannelLinkRemovedEvent_impl(py_ctx* X, cJSON* v_itemName, cJSON* v_channelUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 5, py_s(X, "openhab/links/"), v_itemName, py_s(X, "-"), v_channelUID, py_s(X, "/removed")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_link_events_ItemChannelLinkRemovedEvent_(openhab_client_t* client, openhab_link_events_ItemChannelLinkRemovedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = link_events_ItemChannelLinkRemovedEvent_impl(X, (a.itemName ? py_s(X, a.itemName) : py_s(X, "*")), (a.channelUID ? py_s(X, a.channelUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* channel_events_ChannelDescriptionChangedEvent_impl(py_ctx* X, cJSON* v_channelUID);
static openhab_sse_t* channel_events_ChannelTriggeredEvent_impl(py_ctx* X, cJSON* v_channelUID);

static openhab_sse_t* channel_events_ChannelDescriptionChangedEvent_impl(py_ctx* X, cJSON* v_channelUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/channels/"), v_channelUID, py_s(X, "/descriptionchanged")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_channel_events_ChannelDescriptionChangedEvent_(openhab_client_t* client, openhab_channel_events_ChannelDescriptionChangedEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = channel_events_ChannelDescriptionChangedEvent_impl(X, (a.channelUID ? py_s(X, a.channelUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}

static openhab_sse_t* channel_events_ChannelTriggeredEvent_impl(py_ctx* X, cJSON* v_channelUID) {
    {
        openhab_sse_t* r_ = py_open_stream(X, py_cat(X, 3, py_s(X, "openhab/channels/"), v_channelUID, py_s(X, "/triggered")), NULL, NULL, NULL);
        if (X->exc) return NULL;
        return r_;
    }
}

openhab_sse_t* openhab_channel_events_ChannelTriggeredEvent_(openhab_client_t* client, openhab_channel_events_ChannelTriggeredEvent_args a) {
    py_ctx X_;
    py_ctx* X = &X_;
    py_init(X, client);
    (void)a._;
    openhab_sse_t* s = channel_events_ChannelTriggeredEvent_impl(X, (a.channelUID ? py_s(X, a.channelUID) : py_s(X, "*")));
    return py_finish_stream(X, s, NULL);
}
