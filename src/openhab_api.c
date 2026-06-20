#include "openhab/openhab_api.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ── Internal shorthand ──────────────────────────────────────────────────────*/
#define GET(ep)           openhab_get(c, ep, "application/json", NULL)
#define GET_Q(ep, q)      openhab_get(c, ep, "application/json", q)
#define GET_T(ep, ct)     openhab_get(c, ep, ct, NULL)
#define POST(ep, b)       openhab_post(c, ep, b, "application/json")
#define POST_TXT(ep, b)   openhab_post(c, ep, b, "text/plain")
#define PUT(ep, b)        openhab_put(c, ep, b, "application/json")
#define PUT_TXT(ep, b)    openhab_put(c, ep, b, "text/plain")
#define DEL(ep)           openhab_delete(c, ep)

/* ── path builder ───────────────────────────────────────────────────────────*/
static char path_buf[2048];
#define PATH(fmt, ...) (snprintf(path_buf, sizeof(path_buf), fmt, __VA_ARGS__), path_buf)

/* ── query builder ───────────────────────────────────────────────────────────*/
static char query_buf[1024];

static void qappend(char* buf, size_t sz, const char* key, const char* val) {
    if (!val || !val[0]) return;
    size_t used = strlen(buf);
    snprintf(buf + used, sz - used, "%s%s=%s", used ? "&" : "", key, val);
}

/* ── UUID ────────────────────────────────────────────────────────────────────*/
char* openhab_uuid_get(openhab_client_t* c) {
    return openhab_get(c, "/uuid", "text/plain", NULL);
}

/* ── Systeminfo ──────────────────────────────────────────────────────────────*/
char* openhab_systeminfo_get(openhab_client_t* c)  { return GET("/systeminfo"); }
char* openhab_systeminfo_uom(openhab_client_t* c)  { return GET("/systeminfo/uom"); }

/* ── Items ───────────────────────────────────────────────────────────────────*/
char* openhab_items_get_all(openhab_client_t* c,
    const char* type, const char* tags, const char* metadata,
    int recursive, const char* fields, int static_only, const char* language) {
    query_buf[0] = '\0';
    qappend(query_buf, sizeof(query_buf), "type",         type);
    qappend(query_buf, sizeof(query_buf), "tags",         tags);
    qappend(query_buf, sizeof(query_buf), "metadata",     metadata ? metadata : ".*");
    qappend(query_buf, sizeof(query_buf), "recursive",    recursive ? "true" : "false");
    qappend(query_buf, sizeof(query_buf), "fields",       fields);
    qappend(query_buf, sizeof(query_buf), "staticDataOnly", static_only ? "true" : "false");
    return GET_Q("/items", query_buf);
}
char* openhab_items_add_or_update_many(openhab_client_t* c, const char* j) { return PUT("/items", j); }
char* openhab_items_get(openhab_client_t* c, const char* n, const char* meta, int rec, const char* lang) {
    query_buf[0] = '\0';
    qappend(query_buf, sizeof(query_buf), "metadata",  meta ? meta : ".*");
    qappend(query_buf, sizeof(query_buf), "recursive", rec ? "true" : "false");
    return GET_Q(PATH("/items/%s", n), query_buf);
}
char* openhab_items_add_or_update(openhab_client_t* c, const char* n, const char* j, const char* l) {
    (void)l; return PUT(PATH("/items/%s", n), j);
}
char* openhab_items_send_command(openhab_client_t* c, const char* n, const char* cmd) {
    return POST_TXT(PATH("/items/%s", n), cmd);
}
char* openhab_items_post_update(openhab_client_t* c, const char* n, const char* s) {
    return openhab_items_update_state(c, n, s, NULL);
}
char* openhab_items_delete(openhab_client_t* c, const char* n) { return DEL(PATH("/items/%s", n)); }
char* openhab_items_add_group_member(openhab_client_t* c, const char* n, const char* m) {
    return PUT(PATH("/items/%s/members/%s", n, m), NULL);
}
char* openhab_items_remove_group_member(openhab_client_t* c, const char* n, const char* m) {
    return DEL(PATH("/items/%s/members/%s", n, m));
}
char* openhab_items_add_metadata(openhab_client_t* c, const char* n, const char* ns, const char* j) {
    return PUT(PATH("/items/%s/metadata/%s", n, ns), j);
}
char* openhab_items_remove_metadata(openhab_client_t* c, const char* n, const char* ns) {
    return DEL(PATH("/items/%s/metadata/%s", n, ns));
}
char* openhab_items_get_metadata_namespaces(openhab_client_t* c, const char* n, const char* l) {
    (void)l; return GET(PATH("/items/%s/metadata/namespaces", n));
}
char* openhab_items_get_semantic(openhab_client_t* c, const char* n, const char* sc, const char* l) {
    (void)l; return GET(PATH("/items/%s/semantic/%s", n, sc));
}
char* openhab_items_get_state(openhab_client_t* c, const char* n) {
    return openhab_get(c, PATH("/items/%s/state", n), "text/plain", NULL);
}
char* openhab_items_update_state(openhab_client_t* c, const char* n, const char* s, const char* l) {
    (void)l; return PUT_TXT(PATH("/items/%s/state", n), s);
}
char* openhab_items_add_tag(openhab_client_t* c, const char* n, const char* t) {
    return PUT(PATH("/items/%s/tags/%s", n, t), NULL);
}
char* openhab_items_remove_tag(openhab_client_t* c, const char* n, const char* t) {
    return DEL(PATH("/items/%s/tags/%s", n, t));
}
char* openhab_items_purge_metadata(openhab_client_t* c) { return POST("/items/metadata/purge", NULL); }

/* ── Things ──────────────────────────────────────────────────────────────────*/
char* openhab_things_get_all(openhab_client_t* c, int sum, int sta, const char* l) {
    (void)l;
    query_buf[0] = '\0';
    qappend(query_buf, sizeof(query_buf), "summary",       sum ? "true" : "false");
    qappend(query_buf, sizeof(query_buf), "staticDataOnly", sta ? "true" : "false");
    return GET_Q("/things", query_buf);
}
char* openhab_things_create(openhab_client_t* c, const char* j, const char* l)  { (void)l; return POST("/things", j); }
char* openhab_things_get(openhab_client_t* c, const char* uid, const char* l)   { (void)l; return GET(PATH("/things/%s", uid)); }
char* openhab_things_update(openhab_client_t* c, const char* uid, const char* j, const char* l) { (void)l; return PUT(PATH("/things/%s", uid), j); }
char* openhab_things_delete(openhab_client_t* c, const char* uid, int force, const char* l) {
    (void)l;
    query_buf[0] = '\0';
    qappend(query_buf, sizeof(query_buf), "force", force ? "true" : "false");
    /* DELETE with query – build full path */
    char ep[256]; snprintf(ep, sizeof(ep), "/things/%s?%s", uid, query_buf);
    return openhab_delete(c, ep);
}
char* openhab_things_update_config(openhab_client_t* c, const char* uid, const char* j, const char* l) { (void)l; return PUT(PATH("/things/%s/config", uid), j); }
char* openhab_things_get_config_status(openhab_client_t* c, const char* uid, const char* l) { (void)l; return GET(PATH("/things/%s/config/status", uid)); }
char* openhab_things_set_enabled(openhab_client_t* c, const char* uid, int en, const char* l) { (void)l; return PUT_TXT(PATH("/things/%s/enable", uid), en ? "true" : "false"); }
char* openhab_things_get_status(openhab_client_t* c, const char* uid, const char* l)           { (void)l; return GET(PATH("/things/%s/status", uid)); }
char* openhab_things_get_firmware_status(openhab_client_t* c, const char* uid, const char* l)  { (void)l; return GET(PATH("/things/%s/firmware/status", uid)); }
char* openhab_things_get_firmwares(openhab_client_t* c, const char* uid, const char* l)        { (void)l; return GET(PATH("/things/%s/firmwares", uid)); }
char* openhab_things_update_firmware(openhab_client_t* c, const char* uid, const char* ver, const char* l) { (void)l; return PUT(PATH("/things/%s/firmware/%s", uid, ver), NULL); }

/* ── Rules ───────────────────────────────────────────────────────────────────*/
char* openhab_rules_get_all(openhab_client_t* c, const char* prefix, const char* tags, int sum, int sta) {
    query_buf[0] = '\0';
    qappend(query_buf, sizeof(query_buf), "prefix",        prefix);
    qappend(query_buf, sizeof(query_buf), "tags",          tags);
    qappend(query_buf, sizeof(query_buf), "summary",       sum ? "true" : "false");
    qappend(query_buf, sizeof(query_buf), "staticDataOnly", sta ? "true" : "false");
    return GET_Q("/rules", query_buf);
}
char* openhab_rules_create(openhab_client_t* c, const char* j)          { return POST("/rules", j); }
char* openhab_rules_get(openhab_client_t* c, const char* uid)            { return GET(PATH("/rules/%s", uid)); }
char* openhab_rules_update(openhab_client_t* c, const char* uid, const char* j) { return PUT(PATH("/rules/%s", uid), j); }
char* openhab_rules_delete(openhab_client_t* c, const char* uid)         { return DEL(PATH("/rules/%s", uid)); }
char* openhab_rules_get_actions(openhab_client_t* c, const char* uid)    { return GET(PATH("/rules/%s/actions", uid)); }
char* openhab_rules_get_conditions(openhab_client_t* c, const char* uid) { return GET(PATH("/rules/%s/conditions", uid)); }
char* openhab_rules_get_triggers(openhab_client_t* c, const char* uid)   { return GET(PATH("/rules/%s/triggers", uid)); }
char* openhab_rules_get_config(openhab_client_t* c, const char* uid)     { return GET(PATH("/rules/%s/config", uid)); }
char* openhab_rules_update_config(openhab_client_t* c, const char* uid, const char* j) { return PUT(PATH("/rules/%s/config", uid), j); }
char* openhab_rules_set_state(openhab_client_t* c, const char* uid, int en) {
    return POST_TXT(PATH("/rules/%s/enable", uid), en ? "true" : "false");
}
char* openhab_rules_run_now(openhab_client_t* c, const char* uid, const char* ctx) {
    return ctx ? POST(PATH("/rules/%s/runnow", uid), ctx)
               : POST(PATH("/rules/%s/runnow", uid), NULL);
}

/* ── Actions ─────────────────────────────────────────────────────────────────*/
char* openhab_actions_get_all(openhab_client_t* c)                            { return GET("/actions"); }
char* openhab_actions_get(openhab_client_t* c, const char* uid)               { return GET(PATH("/actions/%s", uid)); }
char* openhab_actions_execute(openhab_client_t* c, const char* uid, const char* aid, const char* j) {
    return POST(PATH("/actions/%s/%s", uid, aid), j);
}

/* ── Addons ──────────────────────────────────────────────────────────────────*/
char* openhab_addons_get_all(openhab_client_t* c, const char* svc, const char* l) {
    (void)l; query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"serviceId",svc);
    return GET_Q("/addons", query_buf);
}
char* openhab_addons_get(openhab_client_t* c, const char* id, const char* svc, const char* l) {
    (void)l; query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"serviceId",svc);
    return GET_Q(PATH("/addons/%s",id), query_buf);
}
char* openhab_addons_install(openhab_client_t* c, const char* id, const char* svc) {
    (void)svc; return POST(PATH("/addons/%s/install",id), NULL);
}
char* openhab_addons_uninstall(openhab_client_t* c, const char* id, const char* svc) {
    (void)svc; return DEL(PATH("/addons/%s/uninstall",id));
}
char* openhab_addons_get_types(openhab_client_t* c, const char* l)       { (void)l; return GET("/addons/types"); }
char* openhab_addons_get_suggestions(openhab_client_t* c, const char* l) { (void)l; return GET("/addons/suggestions"); }
char* openhab_addons_get_services(openhab_client_t* c, const char* l)    { (void)l; return GET("/addons/services"); }

/* ── Audio ───────────────────────────────────────────────────────────────────*/
char* openhab_audio_get_default_sink(openhab_client_t* c)   { return GET("/audio/defaultsink"); }
char* openhab_audio_get_default_source(openhab_client_t* c) { return GET("/audio/defaultsource"); }
char* openhab_audio_get_sinks(openhab_client_t* c)          { return GET("/audio/sinks"); }
char* openhab_audio_get_sources(openhab_client_t* c)        { return GET("/audio/sources"); }

/* ── Auth ────────────────────────────────────────────────────────────────────*/
char* openhab_auth_get_tokens(openhab_client_t* c)  { return GET("/auth/apitokens"); }
char* openhab_auth_create_token(openhab_client_t* c, const char* name, const char* scope) {
    query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"tokenName",name);
    qappend(query_buf,sizeof(query_buf),"scope",scope);
    return openhab_post(c, PATH("/auth/apitokens?%s",query_buf), NULL, "application/json");
}
char* openhab_auth_delete_token(openhab_client_t* c, const char* name)       { return DEL(PATH("/auth/apitokens/%s",name)); }
char* openhab_auth_get_sessions(openhab_client_t* c)                          { return GET("/auth/sessions"); }
char* openhab_auth_delete_session(openhab_client_t* c, const char* sid)       { return DEL(PATH("/auth/sessions/%s",sid)); }

/* ── ChannelTypes ────────────────────────────────────────────────────────────*/
char* openhab_channel_types_get_all(openhab_client_t* c, const char* bid, const char* l) {
    (void)l; query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"bindingId",bid);
    return GET_Q("/channel-types", query_buf);
}
char* openhab_channel_types_get(openhab_client_t* c, const char* uid, const char* l) { (void)l; return GET(PATH("/channel-types/%s",uid)); }
char* openhab_channel_types_get_linkable_item_types(openhab_client_t* c, const char* uid) { return GET(PATH("/channel-types/%s/linkableItemTypes",uid)); }

/* ── ConfigDescriptions ──────────────────────────────────────────────────────*/
char* openhab_config_descriptions_get_all(openhab_client_t* c, const char* scheme, const char* l) {
    (void)l; query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"scheme",scheme);
    return GET_Q("/config-descriptions", query_buf);
}
char* openhab_config_descriptions_get(openhab_client_t* c, const char* uri, const char* l) {
    (void)l; return GET(PATH("/config-descriptions/%s",uri));
}

/* ── Discovery ───────────────────────────────────────────────────────────────*/
char* openhab_discovery_get_bindings(openhab_client_t* c)            { return GET("/discovery"); }
char* openhab_discovery_scan(openhab_client_t* c, const char* bid)   { return POST(PATH("/discovery/bindings/%s/scan",bid), NULL); }

/* ── Iconsets ────────────────────────────────────────────────────────────────*/
char* openhab_iconsets_get_all(openhab_client_t* c, const char* l) { (void)l; return GET("/iconsets"); }

/* ── Inbox ───────────────────────────────────────────────────────────────────*/
char* openhab_inbox_get_all(openhab_client_t* c)                           { return GET("/inbox"); }
char* openhab_inbox_approve(openhab_client_t* c, const char* uid, const char* label, const char* nid) {
    (void)nid; return POST_TXT(PATH("/inbox/%s/approve",uid), label);
}
char* openhab_inbox_delete(openhab_client_t* c, const char* uid)           { return DEL(PATH("/inbox/%s",uid)); }
char* openhab_inbox_ignore(openhab_client_t* c, const char* uid)           { return POST(PATH("/inbox/%s/ignore",uid), NULL); }
char* openhab_inbox_unignore(openhab_client_t* c, const char* uid)         { return POST(PATH("/inbox/%s/unignore",uid), NULL); }

/* ── Links ───────────────────────────────────────────────────────────────────*/
char* openhab_links_get_all(openhab_client_t* c, const char* item, const char* ch) {
    query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"itemName",item);
    qappend(query_buf,sizeof(query_buf),"channelUID",ch);
    return GET_Q("/links", query_buf);
}
char* openhab_links_get(openhab_client_t* c, const char* item, const char* ch) {
    return GET(PATH("/links/%s/%s",item,ch));
}
char* openhab_links_link(openhab_client_t* c, const char* item, const char* ch, const char* j) {
    return PUT(PATH("/links/%s/%s",item,ch), j ? j : "{\"configuration\":{}}");
}
char* openhab_links_unlink(openhab_client_t* c, const char* item, const char* ch) {
    return DEL(PATH("/links/%s/%s",item,ch));
}
char* openhab_links_get_orphan(openhab_client_t* c) { return GET("/links/orphan"); }
char* openhab_links_purge(openhab_client_t* c)      { return DEL("/links/purge"); }

/* ── Logging ─────────────────────────────────────────────────────────────────*/
char* openhab_logging_get_all(openhab_client_t* c)                          { return GET("/logging"); }
char* openhab_logging_get(openhab_client_t* c, const char* name)            { return GET(PATH("/logging/%s",name)); }
char* openhab_logging_set(openhab_client_t* c, const char* name, const char* level) {
    char j[256]; snprintf(j,sizeof(j),"{\"loggerName\":\"%s\",\"level\":\"%s\"}",name,level);
    return PUT(PATH("/logging/%s",name), j);
}
char* openhab_logging_delete(openhab_client_t* c, const char* name)         { return DEL(PATH("/logging/%s",name)); }

/* ── ModuleTypes ─────────────────────────────────────────────────────────────*/
char* openhab_module_types_get_all(openhab_client_t* c, const char* type, const char* l) {
    (void)l; query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"type",type);
    return GET_Q("/module-types", query_buf);
}
char* openhab_module_types_get(openhab_client_t* c, const char* uid, const char* l) { (void)l; return GET(PATH("/module-types/%s",uid)); }

/* ── Persistence ─────────────────────────────────────────────────────────────*/
char* openhab_persistence_get_services(openhab_client_t* c) { return GET("/persistence"); }
char* openhab_persistence_get_items(openhab_client_t* c, const char* svc) {
    query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"serviceId",svc);
    return GET_Q("/persistence/items", query_buf);
}
char* openhab_persistence_get_item_data(openhab_client_t* c, const char* name,
    const char* svc, const char* st, const char* et, int page, int pl, int boundary) {
    char pg[16], pgl[16];
    snprintf(pg,sizeof(pg),"%d",page);
    snprintf(pgl,sizeof(pgl),"%d",pl);
    query_buf[0]='\0';
    qappend(query_buf,sizeof(query_buf),"serviceId",svc);
    qappend(query_buf,sizeof(query_buf),"starttime",st);
    qappend(query_buf,sizeof(query_buf),"endtime",et);
    if (page>0)  qappend(query_buf,sizeof(query_buf),"page",pg);
    if (pl>0)    qappend(query_buf,sizeof(query_buf),"pagelength",pgl);
    qappend(query_buf,sizeof(query_buf),"boundary",boundary?"true":"false");
    return GET_Q(PATH("/persistence/items/%s",name), query_buf);
}
char* openhab_persistence_store_item_data(openhab_client_t* c, const char* name,
    const char* time, const char* state, const char* svc) {
    (void)svc;
    char j[512]; snprintf(j,sizeof(j),"{\"time\":\"%s\",\"state\":\"%s\"}",time,state);
    return PUT(PATH("/persistence/items/%s",name), j);
}
char* openhab_persistence_delete_item_data(openhab_client_t* c, const char* name,
    const char* st, const char* et, const char* svc) {
    query_buf[0]='\0';
    qappend(query_buf,sizeof(query_buf),"serviceId",svc);
    qappend(query_buf,sizeof(query_buf),"starttime",st);
    qappend(query_buf,sizeof(query_buf),"endtime",et);
    char ep[256]; snprintf(ep,sizeof(ep),"/persistence/items/%s?%s",name,query_buf);
    return openhab_delete(c, ep);
}

/* ── ProfileTypes ────────────────────────────────────────────────────────────*/
char* openhab_profile_types_get_all(openhab_client_t* c, const char* ctu, const char* it, const char* l) {
    (void)l; query_buf[0]='\0';
    qappend(query_buf,sizeof(query_buf),"channelTypeUID",ctu);
    qappend(query_buf,sizeof(query_buf),"itemType",it);
    return GET_Q("/profile-types", query_buf);
}

/* ── Services ────────────────────────────────────────────────────────────────*/
char* openhab_services_get_all(openhab_client_t* c, const char* l)               { (void)l; return GET("/services"); }
char* openhab_services_get(openhab_client_t* c, const char* id, const char* l)   { (void)l; return GET(PATH("/services/%s",id)); }
char* openhab_services_get_config(openhab_client_t* c, const char* id)            { return GET(PATH("/services/%s/config",id)); }
char* openhab_services_update_config(openhab_client_t* c, const char* id, const char* j) { return PUT(PATH("/services/%s/config",id), j); }
char* openhab_services_delete_config(openhab_client_t* c, const char* id)         { return DEL(PATH("/services/%s/config",id)); }

/* ── Sitemaps ────────────────────────────────────────────────────────────────*/
char* openhab_sitemaps_get_all(openhab_client_t* c) { return GET("/sitemaps"); }
char* openhab_sitemaps_get(openhab_client_t* c, const char* name, const char* type, int js, const char* l) {
    (void)l; query_buf[0]='\0';
    qappend(query_buf,sizeof(query_buf),"type",type);
    qappend(query_buf,sizeof(query_buf),"jsonsupport",js?"true":"false");
    return GET_Q(PATH("/sitemaps/%s",name), query_buf);
}
char* openhab_sitemaps_get_page(openhab_client_t* c, const char* name, const char* page,
    const char* sub, int hidden, const char* l) {
    (void)l; query_buf[0]='\0';
    qappend(query_buf,sizeof(query_buf),"subscriptionid",sub);
    qappend(query_buf,sizeof(query_buf),"includeHidden",hidden?"true":"false");
    return GET_Q(PATH("/sitemaps/%s/%s",name,page), query_buf);
}
char* openhab_sitemaps_create_subscription(openhab_client_t* c) { return POST("/sitemaps/subscription", NULL); }

/* ── Tags ────────────────────────────────────────────────────────────────────*/
char* openhab_tags_get_all(openhab_client_t* c, const char* l, const char* type) {
    (void)l; query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"type",type);
    return GET_Q("/tags", query_buf);
}
char* openhab_tags_get(openhab_client_t* c, const char* id, const char* l)    { (void)l; return GET(PATH("/tags/%s",id)); }
char* openhab_tags_create(openhab_client_t* c, const char* j)                  { return POST("/tags", j); }
char* openhab_tags_update(openhab_client_t* c, const char* id, const char* j)  { return PUT(PATH("/tags/%s",id), j); }
char* openhab_tags_delete(openhab_client_t* c, const char* id)                 { return DEL(PATH("/tags/%s",id)); }

/* ── Templates ───────────────────────────────────────────────────────────────*/
char* openhab_templates_get_all(openhab_client_t* c, const char* l) { (void)l; return GET("/templates"); }
char* openhab_templates_get(openhab_client_t* c, const char* uid, const char* l) { (void)l; return GET(PATH("/templates/%s",uid)); }

/* ── ThingTypes ──────────────────────────────────────────────────────────────*/
char* openhab_thing_types_get_all(openhab_client_t* c, const char* bid, const char* l) {
    (void)l; query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"bindingId",bid);
    return GET_Q("/thing-types", query_buf);
}
char* openhab_thing_types_get(openhab_client_t* c, const char* uid, const char* l) { (void)l; return GET(PATH("/thing-types/%s",uid)); }

/* ── Transformations ─────────────────────────────────────────────────────────*/
char* openhab_transformations_get_all(openhab_client_t* c)                    { return GET("/transformations"); }
char* openhab_transformations_get(openhab_client_t* c, const char* uid)       { return GET(PATH("/transformations/%s",uid)); }
char* openhab_transformations_update(openhab_client_t* c, const char* uid, const char* j) { return PUT(PATH("/transformations/%s",uid), j); }
char* openhab_transformations_delete(openhab_client_t* c, const char* uid)    { return DEL(PATH("/transformations/%s",uid)); }
char* openhab_transformations_get_services(openhab_client_t* c)               { return GET("/transformations/services"); }

/* ── UI ──────────────────────────────────────────────────────────────────────*/
char* openhab_ui_get_tiles(openhab_client_t* c)                              { return GET("/ui/tiles"); }
char* openhab_ui_get_tile(openhab_client_t* c, const char* id)               { return GET(PATH("/ui/tiles/%s",id)); }
char* openhab_ui_add_tile(openhab_client_t* c, const char* id, const char* j) { return PUT(PATH("/ui/tiles/%s",id), j); }
char* openhab_ui_remove_tile(openhab_client_t* c, const char* id)            { return DEL(PATH("/ui/tiles/%s",id)); }
char* openhab_ui_get_components(openhab_client_t* c, const char* ns)         { return GET(PATH("/ui/components/%s",ns)); }
char* openhab_ui_get_component(openhab_client_t* c, const char* ns, const char* uid) { return GET(PATH("/ui/components/%s/%s",ns,uid)); }
char* openhab_ui_add_component(openhab_client_t* c, const char* ns, const char* j)   { return POST(PATH("/ui/components/%s",ns), j); }
char* openhab_ui_update_component(openhab_client_t* c, const char* ns, const char* uid, const char* j) { return PUT(PATH("/ui/components/%s/%s",ns,uid), j); }
char* openhab_ui_remove_component(openhab_client_t* c, const char* ns, const char* uid) { return DEL(PATH("/ui/components/%s/%s",ns,uid)); }

/* ── Voice ───────────────────────────────────────────────────────────────────*/
char* openhab_voice_get_voices(openhab_client_t* c)                         { return GET("/voice/voices"); }
char* openhab_voice_get_default_voice(openhab_client_t* c)                  { return GET("/voice/defaultvoice"); }
char* openhab_voice_say(openhab_client_t* c, const char* text, const char* vid, const char* sid, int vol) {
    query_buf[0]='\0';
    qappend(query_buf,sizeof(query_buf),"voiceid",vid);
    qappend(query_buf,sizeof(query_buf),"sinkid",sid);
    if (vol>=0) { char v[16]; snprintf(v,sizeof(v),"%d",vol); qappend(query_buf,sizeof(query_buf),"volume",v); }
    return openhab_post(c, PATH("/voice/say?%s",query_buf), text, "text/plain");
}
char* openhab_voice_get_interpreters(openhab_client_t* c, const char* l) { (void)l; return GET("/voice/interpreters"); }
char* openhab_voice_get_interpreter(openhab_client_t* c, const char* id, const char* l) { (void)l; return GET(PATH("/voice/interpreters/%s",id)); }
char* openhab_voice_interpret(openhab_client_t* c, const char* text, const char* ids, const char* l) {
    (void)l; query_buf[0]='\0'; qappend(query_buf,sizeof(query_buf),"ids",ids);
    return openhab_post(c, PATH("/voice/interpreters?%s",query_buf), text, "text/plain");
}

/* ── Events (SSE) ────────────────────────────────────────────────────────────*/
static void sse_listen_topic(openhab_client_t* c, const char* topic,
                              openhab_sse_callback_t cb, void* ud) {
    char url[512];
    const char* base = openhab_client_base_url(c);
    if (topic && topic[0])
        snprintf(url,sizeof(url),"%s/rest/events?topics=%s", base, topic);
    else
        snprintf(url,sizeof(url),"%s/rest/events", base);
    openhab_sse_listen(c, url, cb, ud);
}

void openhab_events_listen(openhab_client_t* c, const char* topics,
    openhab_sse_callback_t cb, void* ud) { sse_listen_topic(c, topics, cb, ud); }

void openhab_events_item_state_changed(openhab_client_t* c, const char* item,
    openhab_sse_callback_t cb, void* ud) {
    char topic[256];
    if (item && item[0]) snprintf(topic,sizeof(topic),"openhab/items/%s/statechanged",item);
    else snprintf(topic,sizeof(topic),"openhab/items/*/statechanged");
    sse_listen_topic(c, topic, cb, ud);
}

void openhab_events_item_command(openhab_client_t* c, const char* item,
    openhab_sse_callback_t cb, void* ud) {
    char topic[256];
    if (item && item[0]) snprintf(topic,sizeof(topic),"openhab/items/%s/command",item);
    else snprintf(topic,sizeof(topic),"openhab/items/*/command");
    sse_listen_topic(c, topic, cb, ud);
}

void openhab_events_thing_status(openhab_client_t* c, const char* uid,
    openhab_sse_callback_t cb, void* ud) {
    char topic[256];
    if (uid && uid[0]) snprintf(topic,sizeof(topic),"openhab/things/%s/status",uid);
    else snprintf(topic,sizeof(topic),"openhab/things/*/status");
    sse_listen_topic(c, topic, cb, ud);
}
