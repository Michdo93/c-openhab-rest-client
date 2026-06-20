#ifndef OPENHAB_API_H
#define OPENHAB_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "openhab_client.h"

/*
 * All functions return a heap-allocated JSON string that the caller must free().
 * Returns NULL on error; call openhab_last_error() for details.
 */

/* ── UUID ──────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_uuid_getUUID(openhab_client_t* c);

/* ── Systeminfo ────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_systeminfo_getSystemInfo(openhab_client_t* c);
OPENHAB_API char* openhab_systeminfo_getUoMInfo(openhab_client_t* c);

/* ── Items ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_items_getItems(openhab_client_t* c,
    const char* type, const char* tags, const char* metadata,
    int recursive, const char* fields, int static_only, const char* language);
OPENHAB_API char* openhab_items_addOrUpdateItems(openhab_client_t* c, const char* items_json);
OPENHAB_API char* openhab_items_getItem(openhab_client_t* c, const char* name,
    const char* metadata, int recursive, const char* language);
OPENHAB_API char* openhab_items_addOrUpdateItem(openhab_client_t* c, const char* name,
    const char* item_json, const char* language);
OPENHAB_API char* openhab_items_sendCommand(openhab_client_t* c, const char* name, const char* cmd);
OPENHAB_API char* openhab_items_postUpdate(openhab_client_t* c, const char* name, const char* state);
OPENHAB_API char* openhab_items_deleteItem(openhab_client_t* c, const char* name);
OPENHAB_API char* openhab_items_addGroupMember(openhab_client_t* c, const char* name, const char* member);
OPENHAB_API char* openhab_items_removeGroupMember(openhab_client_t* c, const char* name, const char* member);
OPENHAB_API char* openhab_items_addMetadata(openhab_client_t* c, const char* name, const char* ns, const char* json);
OPENHAB_API char* openhab_items_removeMetadata(openhab_client_t* c, const char* name, const char* ns);
OPENHAB_API char* openhab_items_getMetadataNamespaces(openhab_client_t* c, const char* name, const char* language);
OPENHAB_API char* openhab_items_getSemanticItem(openhab_client_t* c, const char* name, const char* sem_class, const char* language);
OPENHAB_API char* openhab_items_getItemState(openhab_client_t* c, const char* name);
OPENHAB_API char* openhab_items_updateItemState(openhab_client_t* c, const char* name, const char* state, const char* language);
OPENHAB_API char* openhab_items_addTag(openhab_client_t* c, const char* name, const char* tag);
OPENHAB_API char* openhab_items_removeTag(openhab_client_t* c, const char* name, const char* tag);
OPENHAB_API char* openhab_items_purgeOrphanedMetadata(openhab_client_t* c);

/* ── Things ────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_things_getThings(openhab_client_t* c, int summary, int static_only, const char* language);
OPENHAB_API char* openhab_things_createThing(openhab_client_t* c, const char* json, const char* language);
OPENHAB_API char* openhab_things_getThing(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_things_updateThing(openhab_client_t* c, const char* uid, const char* json, const char* language);
OPENHAB_API char* openhab_things_deleteThing(openhab_client_t* c, const char* uid, int force, const char* language);
OPENHAB_API char* openhab_things_updateThingConfiguration(openhab_client_t* c, const char* uid, const char* json, const char* language);
OPENHAB_API char* openhab_things_getThingConfigStatus(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_things_setThingStatus(openhab_client_t* c, const char* uid, int enabled, const char* language);
OPENHAB_API char* openhab_things_getThingStatus(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_things_getThingFirmwareStatus(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_things_getThingFirmwares(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_things_updateThingFirmware(openhab_client_t* c, const char* uid, const char* version, const char* language);

/* ── Rules ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_rules_getRules(openhab_client_t* c, const char* prefix, const char* tags, int summary, int static_only);
OPENHAB_API char* openhab_rules_createRule(openhab_client_t* c, const char* json);
OPENHAB_API char* openhab_rules_getRule(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_updateRule(openhab_client_t* c, const char* uid, const char* json);
OPENHAB_API char* openhab_rules_deleteRule(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_getActions(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_getConditions(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_getTriggers(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_getConfiguration(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_updateConfiguration(openhab_client_t* c, const char* uid, const char* json);
OPENHAB_API char* openhab_rules_setRuleState(openhab_client_t* c, const char* uid, int enable);
OPENHAB_API char* openhab_rules_runNow(openhab_client_t* c, const char* uid, const char* context_json);

/* ── Actions ───────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_actions_getActions(openhab_client_t* c);
OPENHAB_API char* openhab_actions_getThingActions(openhab_client_t* c, const char* thing_uid);
OPENHAB_API char* openhab_actions_executeThingAction(openhab_client_t* c, const char* thing_uid, const char* action_uid, const char* input_json);

/* ── Addons ────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_addons_getAddons(openhab_client_t* c, const char* service_id, const char* language);
OPENHAB_API char* openhab_addons_getAddon(openhab_client_t* c, const char* id, const char* service_id, const char* language);
OPENHAB_API char* openhab_addons_installAddon(openhab_client_t* c, const char* id, const char* service_id);
OPENHAB_API char* openhab_addons_uninstallAddon(openhab_client_t* c, const char* id, const char* service_id);
OPENHAB_API char* openhab_addons_getAddonTypes(openhab_client_t* c, const char* language);
OPENHAB_API char* openhab_addons_getAddonSuggestions(openhab_client_t* c, const char* language);
OPENHAB_API char* openhab_addons_getAddonServices(openhab_client_t* c, const char* language);

/* ── Audio ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_audio_getDefaultSink(openhab_client_t* c);
OPENHAB_API char* openhab_audio_getDefaultSource(openhab_client_t* c);
OPENHAB_API char* openhab_audio_getSinks(openhab_client_t* c);
OPENHAB_API char* openhab_audio_getSources(openhab_client_t* c);

/* ── Auth ──────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_auth_getAPITokens(openhab_client_t* c);
OPENHAB_API char* openhab_auth_createAPIToken(openhab_client_t* c, const char* name, const char* scope);
OPENHAB_API char* openhab_auth_deleteAPIToken(openhab_client_t* c, const char* name);
OPENHAB_API char* openhab_auth_getSessions(openhab_client_t* c);
OPENHAB_API char* openhab_auth_deleteSession(openhab_client_t* c, const char* session_id);

/* ── ChannelTypes ──────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_channel_types_getChannelTypes(openhab_client_t* c, const char* binding_id, const char* language);
OPENHAB_API char* openhab_channel_types_getChannelType(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_channel_types_getLinkableItemTypes(openhab_client_t* c, const char* uid);

/* ── ConfigDescriptions ────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_config_descriptions_getConfigDescriptions(openhab_client_t* c, const char* scheme, const char* language);
OPENHAB_API char* openhab_config_descriptions_getConfigDescription(openhab_client_t* c, const char* uri, const char* language);

/* ── Discovery ─────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_discovery_getDiscoveryBindings(openhab_client_t* c);
OPENHAB_API char* openhab_discovery_startBindingScan(openhab_client_t* c, const char* binding_id);

/* ── Iconsets ──────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_iconsets_getIconsets(openhab_client_t* c, const char* language);

/* ── Inbox ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_inbox_getDiscoveredThings(openhab_client_t* c);
OPENHAB_API char* openhab_inbox_approveDiscoveryResult(openhab_client_t* c, const char* uid, const char* label, const char* new_thing_id);
OPENHAB_API char* openhab_inbox_removeDiscoveryResult(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_inbox_ignoreDiscoveryResult(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_inbox_unignoreDiscoveryResult(openhab_client_t* c, const char* uid);

/* ── Links ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_links_getLinks(openhab_client_t* c, const char* item_name, const char* channel_uid);
OPENHAB_API char* openhab_links_getLink(openhab_client_t* c, const char* item_name, const char* channel_uid);
OPENHAB_API char* openhab_links_linkItemToChannel(openhab_client_t* c, const char* item_name, const char* channel_uid, const char* json);
OPENHAB_API char* openhab_links_unlinkItemFromChannel(openhab_client_t* c, const char* item_name, const char* channel_uid);
OPENHAB_API char* openhab_links_getOrphanLinks(openhab_client_t* c);
OPENHAB_API char* openhab_links_purgeUnusedLinks(openhab_client_t* c);

/* ── Logging ───────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_logging_getLoggers(openhab_client_t* c);
OPENHAB_API char* openhab_logging_getLogger(openhab_client_t* c, const char* name);
OPENHAB_API char* openhab_logging_modifyOrAddLogger(openhab_client_t* c, const char* name, const char* level);
OPENHAB_API char* openhab_logging_removeLogger(openhab_client_t* c, const char* name);

/* ── ModuleTypes ───────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_module_types_getModuleTypes(openhab_client_t* c, const char* type, const char* language);
OPENHAB_API char* openhab_module_types_getModuleType(openhab_client_t* c, const char* uid, const char* language);

/* ── Persistence ───────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_persistence_getServices(openhab_client_t* c);
OPENHAB_API char* openhab_persistence_getItemsFromService(openhab_client_t* c, const char* service_id);
OPENHAB_API char* openhab_persistence_getItemPersistenceData(openhab_client_t* c, const char* name,
    const char* service_id, const char* start_time, const char* end_time,
    int page, int page_length, int boundary);
OPENHAB_API char* openhab_persistence_storeItemPersistenceData(openhab_client_t* c, const char* name,
    const char* time, const char* state, const char* service_id);
OPENHAB_API char* openhab_persistence_deleteItemPersistenceData(openhab_client_t* c, const char* name,
    const char* start_time, const char* end_time, const char* service_id);

/* ── ProfileTypes ──────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_profile_types_getProfileTypes(openhab_client_t* c, const char* channel_type_uid,
    const char* item_type, const char* language);

/* ── Services ──────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_services_getServices(openhab_client_t* c, const char* language);
OPENHAB_API char* openhab_services_getService(openhab_client_t* c, const char* id, const char* language);
OPENHAB_API char* openhab_services_getServiceConfig(openhab_client_t* c, const char* id);
OPENHAB_API char* openhab_services_updateServiceConfig(openhab_client_t* c, const char* id, const char* json);
OPENHAB_API char* openhab_services_deleteServiceConfig(openhab_client_t* c, const char* id);

/* ── Sitemaps ──────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_sitemaps_getSitemaps(openhab_client_t* c);
OPENHAB_API char* openhab_sitemaps_getSitemap(openhab_client_t* c, const char* name, const char* type,
    int jsonsupport, const char* language);
OPENHAB_API char* openhab_sitemaps_getSitemapPage(openhab_client_t* c, const char* name, const char* page_id,
    const char* subscription_id, int include_hidden, const char* language);
OPENHAB_API char* openhab_sitemaps_createSubscription(openhab_client_t* c);

/* ── Tags ──────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_tags_getTags(openhab_client_t* c, const char* language, const char* type);
OPENHAB_API char* openhab_tags_getTag(openhab_client_t* c, const char* id, const char* language);
OPENHAB_API char* openhab_tags_createTag(openhab_client_t* c, const char* json);
OPENHAB_API char* openhab_tags_updateTag(openhab_client_t* c, const char* id, const char* json);
OPENHAB_API char* openhab_tags_deleteTag(openhab_client_t* c, const char* id);

/* ── Templates ─────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_templates_getTemplates(openhab_client_t* c, const char* language);
OPENHAB_API char* openhab_templates_getTemplate(openhab_client_t* c, const char* uid, const char* language);

/* ── ThingTypes ────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_thing_types_getThingTypes(openhab_client_t* c, const char* binding_id, const char* language);
OPENHAB_API char* openhab_thing_types_getThingType(openhab_client_t* c, const char* uid, const char* language);

/* ── Transformations ───────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_transformations_getTransformations(openhab_client_t* c);
OPENHAB_API char* openhab_transformations_getTransformation(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_transformations_updateTransformation(openhab_client_t* c, const char* uid, const char* json);
OPENHAB_API char* openhab_transformations_deleteTransformation(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_transformations_getTransformationServices(openhab_client_t* c);

/* ── UI ────────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_ui_getUITiles(openhab_client_t* c);
OPENHAB_API char* openhab_ui_getUITile(openhab_client_t* c, const char* id);
OPENHAB_API char* openhab_ui_addUITile(openhab_client_t* c, const char* id, const char* json);
OPENHAB_API char* openhab_ui_removeUITile(openhab_client_t* c, const char* id);
OPENHAB_API char* openhab_ui_getUIComponents(openhab_client_t* c, const char* ns);
OPENHAB_API char* openhab_ui_getUIComponent(openhab_client_t* c, const char* ns, const char* uid);
OPENHAB_API char* openhab_ui_addUIComponent(openhab_client_t* c, const char* ns, const char* json);
OPENHAB_API char* openhab_ui_updateUIComponent(openhab_client_t* c, const char* ns, const char* uid, const char* json);
OPENHAB_API char* openhab_ui_removeUIComponent(openhab_client_t* c, const char* ns, const char* uid);

/* ── Voice ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_voice_getVoices(openhab_client_t* c);
OPENHAB_API char* openhab_voice_getDefaultVoice(openhab_client_t* c);
OPENHAB_API char* openhab_voice_sayText(openhab_client_t* c, const char* text,
    const char* voice_id, const char* sink_id, int volume);
OPENHAB_API char* openhab_voice_getInterpreters(openhab_client_t* c, const char* language);
OPENHAB_API char* openhab_voice_getInterpreter(openhab_client_t* c, const char* id, const char* language);
OPENHAB_API char* openhab_voice_interpret(openhab_client_t* c, const char* text, const char* hli_ids, const char* language);

/* ── Events (SSE) ──────────────────────────────────────────────────────────── */
OPENHAB_API void openhab_events_getEvents(openhab_client_t* c, const char* topics,
    openhab_sse_callback_t cb, void* userdata);
OPENHAB_API void openhab_events_getItemStateChangedEvent(openhab_client_t* c, const char* item_name,
    openhab_sse_callback_t cb, void* userdata);
OPENHAB_API void openhab_events_getItemCommandEvent(openhab_client_t* c, const char* item_name,
    openhab_sse_callback_t cb, void* userdata);
OPENHAB_API void openhab_events_getThingStatusEvent(openhab_client_t* c, const char* thing_uid,
    openhab_sse_callback_t cb, void* userdata);

#ifdef __cplusplus
}
#endif

#endif /* OPENHAB_API_H */
