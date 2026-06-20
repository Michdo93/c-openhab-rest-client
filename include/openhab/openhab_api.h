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
OPENHAB_API char* openhab_uuid_get(openhab_client_t* c);

/* ── Systeminfo ────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_systeminfo_get(openhab_client_t* c);
OPENHAB_API char* openhab_systeminfo_uom(openhab_client_t* c);

/* ── Items ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_items_get_all(openhab_client_t* c,
    const char* type, const char* tags, const char* metadata,
    int recursive, const char* fields, int static_only, const char* language);
OPENHAB_API char* openhab_items_add_or_update_many(openhab_client_t* c, const char* items_json);
OPENHAB_API char* openhab_items_get(openhab_client_t* c, const char* name,
    const char* metadata, int recursive, const char* language);
OPENHAB_API char* openhab_items_add_or_update(openhab_client_t* c, const char* name,
    const char* item_json, const char* language);
OPENHAB_API char* openhab_items_send_command(openhab_client_t* c, const char* name, const char* cmd);
OPENHAB_API char* openhab_items_post_update(openhab_client_t* c, const char* name, const char* state);
OPENHAB_API char* openhab_items_delete(openhab_client_t* c, const char* name);
OPENHAB_API char* openhab_items_add_group_member(openhab_client_t* c, const char* name, const char* member);
OPENHAB_API char* openhab_items_remove_group_member(openhab_client_t* c, const char* name, const char* member);
OPENHAB_API char* openhab_items_add_metadata(openhab_client_t* c, const char* name, const char* ns, const char* json);
OPENHAB_API char* openhab_items_remove_metadata(openhab_client_t* c, const char* name, const char* ns);
OPENHAB_API char* openhab_items_get_metadata_namespaces(openhab_client_t* c, const char* name, const char* language);
OPENHAB_API char* openhab_items_get_semantic(openhab_client_t* c, const char* name, const char* sem_class, const char* language);
OPENHAB_API char* openhab_items_get_state(openhab_client_t* c, const char* name);
OPENHAB_API char* openhab_items_update_state(openhab_client_t* c, const char* name, const char* state, const char* language);
OPENHAB_API char* openhab_items_add_tag(openhab_client_t* c, const char* name, const char* tag);
OPENHAB_API char* openhab_items_remove_tag(openhab_client_t* c, const char* name, const char* tag);
OPENHAB_API char* openhab_items_purge_metadata(openhab_client_t* c);

/* ── Things ────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_things_get_all(openhab_client_t* c, int summary, int static_only, const char* language);
OPENHAB_API char* openhab_things_create(openhab_client_t* c, const char* json, const char* language);
OPENHAB_API char* openhab_things_get(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_things_update(openhab_client_t* c, const char* uid, const char* json, const char* language);
OPENHAB_API char* openhab_things_delete(openhab_client_t* c, const char* uid, int force, const char* language);
OPENHAB_API char* openhab_things_update_config(openhab_client_t* c, const char* uid, const char* json, const char* language);
OPENHAB_API char* openhab_things_get_config_status(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_things_set_enabled(openhab_client_t* c, const char* uid, int enabled, const char* language);
OPENHAB_API char* openhab_things_get_status(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_things_get_firmware_status(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_things_get_firmwares(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_things_update_firmware(openhab_client_t* c, const char* uid, const char* version, const char* language);

/* ── Rules ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_rules_get_all(openhab_client_t* c, const char* prefix, const char* tags, int summary, int static_only);
OPENHAB_API char* openhab_rules_create(openhab_client_t* c, const char* json);
OPENHAB_API char* openhab_rules_get(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_update(openhab_client_t* c, const char* uid, const char* json);
OPENHAB_API char* openhab_rules_delete(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_get_actions(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_get_conditions(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_get_triggers(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_get_config(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_rules_update_config(openhab_client_t* c, const char* uid, const char* json);
OPENHAB_API char* openhab_rules_set_state(openhab_client_t* c, const char* uid, int enable);
OPENHAB_API char* openhab_rules_run_now(openhab_client_t* c, const char* uid, const char* context_json);

/* ── Actions ───────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_actions_get_all(openhab_client_t* c);
OPENHAB_API char* openhab_actions_get(openhab_client_t* c, const char* thing_uid);
OPENHAB_API char* openhab_actions_execute(openhab_client_t* c, const char* thing_uid, const char* action_uid, const char* input_json);

/* ── Addons ────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_addons_get_all(openhab_client_t* c, const char* service_id, const char* language);
OPENHAB_API char* openhab_addons_get(openhab_client_t* c, const char* id, const char* service_id, const char* language);
OPENHAB_API char* openhab_addons_install(openhab_client_t* c, const char* id, const char* service_id);
OPENHAB_API char* openhab_addons_uninstall(openhab_client_t* c, const char* id, const char* service_id);
OPENHAB_API char* openhab_addons_get_types(openhab_client_t* c, const char* language);
OPENHAB_API char* openhab_addons_get_suggestions(openhab_client_t* c, const char* language);
OPENHAB_API char* openhab_addons_get_services(openhab_client_t* c, const char* language);

/* ── Audio ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_audio_get_default_sink(openhab_client_t* c);
OPENHAB_API char* openhab_audio_get_default_source(openhab_client_t* c);
OPENHAB_API char* openhab_audio_get_sinks(openhab_client_t* c);
OPENHAB_API char* openhab_audio_get_sources(openhab_client_t* c);

/* ── Auth ──────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_auth_get_tokens(openhab_client_t* c);
OPENHAB_API char* openhab_auth_create_token(openhab_client_t* c, const char* name, const char* scope);
OPENHAB_API char* openhab_auth_delete_token(openhab_client_t* c, const char* name);
OPENHAB_API char* openhab_auth_get_sessions(openhab_client_t* c);
OPENHAB_API char* openhab_auth_delete_session(openhab_client_t* c, const char* session_id);

/* ── ChannelTypes ──────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_channel_types_get_all(openhab_client_t* c, const char* binding_id, const char* language);
OPENHAB_API char* openhab_channel_types_get(openhab_client_t* c, const char* uid, const char* language);
OPENHAB_API char* openhab_channel_types_get_linkable_item_types(openhab_client_t* c, const char* uid);

/* ── ConfigDescriptions ────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_config_descriptions_get_all(openhab_client_t* c, const char* scheme, const char* language);
OPENHAB_API char* openhab_config_descriptions_get(openhab_client_t* c, const char* uri, const char* language);

/* ── Discovery ─────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_discovery_get_bindings(openhab_client_t* c);
OPENHAB_API char* openhab_discovery_scan(openhab_client_t* c, const char* binding_id);

/* ── Iconsets ──────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_iconsets_get_all(openhab_client_t* c, const char* language);

/* ── Inbox ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_inbox_get_all(openhab_client_t* c);
OPENHAB_API char* openhab_inbox_approve(openhab_client_t* c, const char* uid, const char* label, const char* new_thing_id);
OPENHAB_API char* openhab_inbox_delete(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_inbox_ignore(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_inbox_unignore(openhab_client_t* c, const char* uid);

/* ── Links ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_links_get_all(openhab_client_t* c, const char* item_name, const char* channel_uid);
OPENHAB_API char* openhab_links_get(openhab_client_t* c, const char* item_name, const char* channel_uid);
OPENHAB_API char* openhab_links_link(openhab_client_t* c, const char* item_name, const char* channel_uid, const char* json);
OPENHAB_API char* openhab_links_unlink(openhab_client_t* c, const char* item_name, const char* channel_uid);
OPENHAB_API char* openhab_links_get_orphan(openhab_client_t* c);
OPENHAB_API char* openhab_links_purge(openhab_client_t* c);

/* ── Logging ───────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_logging_get_all(openhab_client_t* c);
OPENHAB_API char* openhab_logging_get(openhab_client_t* c, const char* name);
OPENHAB_API char* openhab_logging_set(openhab_client_t* c, const char* name, const char* level);
OPENHAB_API char* openhab_logging_delete(openhab_client_t* c, const char* name);

/* ── ModuleTypes ───────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_module_types_get_all(openhab_client_t* c, const char* type, const char* language);
OPENHAB_API char* openhab_module_types_get(openhab_client_t* c, const char* uid, const char* language);

/* ── Persistence ───────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_persistence_get_services(openhab_client_t* c);
OPENHAB_API char* openhab_persistence_get_items(openhab_client_t* c, const char* service_id);
OPENHAB_API char* openhab_persistence_get_item_data(openhab_client_t* c, const char* name,
    const char* service_id, const char* start_time, const char* end_time,
    int page, int page_length, int boundary);
OPENHAB_API char* openhab_persistence_store_item_data(openhab_client_t* c, const char* name,
    const char* time, const char* state, const char* service_id);
OPENHAB_API char* openhab_persistence_delete_item_data(openhab_client_t* c, const char* name,
    const char* start_time, const char* end_time, const char* service_id);

/* ── ProfileTypes ──────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_profile_types_get_all(openhab_client_t* c, const char* channel_type_uid,
    const char* item_type, const char* language);

/* ── Services ──────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_services_get_all(openhab_client_t* c, const char* language);
OPENHAB_API char* openhab_services_get(openhab_client_t* c, const char* id, const char* language);
OPENHAB_API char* openhab_services_get_config(openhab_client_t* c, const char* id);
OPENHAB_API char* openhab_services_update_config(openhab_client_t* c, const char* id, const char* json);
OPENHAB_API char* openhab_services_delete_config(openhab_client_t* c, const char* id);

/* ── Sitemaps ──────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_sitemaps_get_all(openhab_client_t* c);
OPENHAB_API char* openhab_sitemaps_get(openhab_client_t* c, const char* name, const char* type,
    int jsonsupport, const char* language);
OPENHAB_API char* openhab_sitemaps_get_page(openhab_client_t* c, const char* name, const char* page_id,
    const char* subscription_id, int include_hidden, const char* language);
OPENHAB_API char* openhab_sitemaps_create_subscription(openhab_client_t* c);

/* ── Tags ──────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_tags_get_all(openhab_client_t* c, const char* language, const char* type);
OPENHAB_API char* openhab_tags_get(openhab_client_t* c, const char* id, const char* language);
OPENHAB_API char* openhab_tags_create(openhab_client_t* c, const char* json);
OPENHAB_API char* openhab_tags_update(openhab_client_t* c, const char* id, const char* json);
OPENHAB_API char* openhab_tags_delete(openhab_client_t* c, const char* id);

/* ── Templates ─────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_templates_get_all(openhab_client_t* c, const char* language);
OPENHAB_API char* openhab_templates_get(openhab_client_t* c, const char* uid, const char* language);

/* ── ThingTypes ────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_thing_types_get_all(openhab_client_t* c, const char* binding_id, const char* language);
OPENHAB_API char* openhab_thing_types_get(openhab_client_t* c, const char* uid, const char* language);

/* ── Transformations ───────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_transformations_get_all(openhab_client_t* c);
OPENHAB_API char* openhab_transformations_get(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_transformations_update(openhab_client_t* c, const char* uid, const char* json);
OPENHAB_API char* openhab_transformations_delete(openhab_client_t* c, const char* uid);
OPENHAB_API char* openhab_transformations_get_services(openhab_client_t* c);

/* ── UI ────────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_ui_get_tiles(openhab_client_t* c);
OPENHAB_API char* openhab_ui_get_tile(openhab_client_t* c, const char* id);
OPENHAB_API char* openhab_ui_add_tile(openhab_client_t* c, const char* id, const char* json);
OPENHAB_API char* openhab_ui_remove_tile(openhab_client_t* c, const char* id);
OPENHAB_API char* openhab_ui_get_components(openhab_client_t* c, const char* ns);
OPENHAB_API char* openhab_ui_get_component(openhab_client_t* c, const char* ns, const char* uid);
OPENHAB_API char* openhab_ui_add_component(openhab_client_t* c, const char* ns, const char* json);
OPENHAB_API char* openhab_ui_update_component(openhab_client_t* c, const char* ns, const char* uid, const char* json);
OPENHAB_API char* openhab_ui_remove_component(openhab_client_t* c, const char* ns, const char* uid);

/* ── Voice ─────────────────────────────────────────────────────────────────── */
OPENHAB_API char* openhab_voice_get_voices(openhab_client_t* c);
OPENHAB_API char* openhab_voice_get_default_voice(openhab_client_t* c);
OPENHAB_API char* openhab_voice_say(openhab_client_t* c, const char* text,
    const char* voice_id, const char* sink_id, int volume);
OPENHAB_API char* openhab_voice_get_interpreters(openhab_client_t* c, const char* language);
OPENHAB_API char* openhab_voice_get_interpreter(openhab_client_t* c, const char* id, const char* language);
OPENHAB_API char* openhab_voice_interpret(openhab_client_t* c, const char* text, const char* hli_ids, const char* language);

/* ── Events (SSE) ──────────────────────────────────────────────────────────── */
OPENHAB_API void openhab_events_listen(openhab_client_t* c, const char* topics,
    openhab_sse_callback_t cb, void* userdata);
OPENHAB_API void openhab_events_item_state_changed(openhab_client_t* c, const char* item_name,
    openhab_sse_callback_t cb, void* userdata);
OPENHAB_API void openhab_events_item_command(openhab_client_t* c, const char* item_name,
    openhab_sse_callback_t cb, void* userdata);
OPENHAB_API void openhab_events_thing_status(openhab_client_t* c, const char* thing_uid,
    openhab_sse_callback_t cb, void* userdata);

#ifdef __cplusplus
}
#endif

#endif /* OPENHAB_API_H */
