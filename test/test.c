#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openhab/openhab.h"

/* ── Configuration ─────────────────────────────────────────────────────────── */
#define URL      "https://home.myopenhab.org"
#define USERNAME "user@example.com"
#define PASSWORD "yourpassword"
#define TOKEN    NULL   /* set to your API token to use token auth instead */
#define TEST_ITEM "testSwitch"

/* ── Helper macros ─────────────────────────────────────────────────────────── */
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

static int passed = 0, failed = 0;

static void print_result(const char* name, char* result, openhab_client_t* c) {
    if (result) {
        printf("  " GREEN "✓" RESET " %s\n", name);
        /* print preview */
        size_t len = strlen(result);
        if (len > 80) { result[80] = '\0'; printf("    %s…\n", result); }
        else           printf("    %s\n", result);
        free(result);
        passed++;
    } else {
        const char* err = openhab_last_error(c);
        printf("  " RED "✗" RESET " %s: %s\n", name, err ? err : "unknown error");
        failed++;
    }
}

static int sse_cb(const char* data, void* userdata) {
    int* count = (int*)userdata;
    printf("  " YELLOW "⚡" RESET " SSE event: %.100s\n", data);
    (*count)++;
    return (*count < 3); /* stop after 3 events */
}

int main(void) {
    printf(BOLD "╔═══════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD "║   c-openhab-rest-client — C Testanwendung            ║\n" RESET);
    printf(BOLD "╚═══════════════════════════════════════════════════════╝\n\n" RESET);

    openhab_client_t* c = openhab_client_create(URL, USERNAME, PASSWORD, TOKEN);
    if (!c) { fprintf(stderr, "Client creation failed\n"); return 1; }

    printf("  URL: " YELLOW "%s" RESET "   Auth: %s\n\n",
           openhab_client_base_url(c),
           TOKEN ? "Token" : "Basic");

    if (openhab_client_is_logged_in(c))
        printf("  " GREEN "✓ Verbunden" RESET "  isCloud=%d  isLoggedIn=%d\n\n",
               openhab_client_is_cloud(c), openhab_client_is_logged_in(c));
    else {
        printf("  " RED "✗ Verbindung fehlgeschlagen" RESET "\n");
        openhab_client_destroy(c);
        return 1;
    }

    /* ── System ─────────────────────────────────────────────────────────── */
    printf(BOLD "── System ──────────────────────────────────────────────\n" RESET);
    print_result("getUUID",       openhab_uuid_get(c), c);
    print_result("getSystemInfo", openhab_systeminfo_get(c), c);
    print_result("getUoMInfo",    openhab_systeminfo_uom(c), c);

    /* ── Items ──────────────────────────────────────────────────────────── */
    printf(BOLD "\n── Items ───────────────────────────────────────────────\n" RESET);
    print_result("getItems",      openhab_items_get_all(c,NULL,NULL,NULL,0,NULL,0,NULL), c);
    print_result("getItem",       openhab_items_get(c, TEST_ITEM, NULL, 1, NULL), c);
    print_result("getItemState",  openhab_items_get_state(c, TEST_ITEM), c);
    print_result("sendCommand ON", openhab_items_send_command(c, TEST_ITEM, "ON"), c);
    print_result("sendCommand OFF",openhab_items_send_command(c, TEST_ITEM, "OFF"), c);
    print_result("getMetadataNS", openhab_items_get_metadata_namespaces(c, TEST_ITEM, NULL), c);

    /* ── Things ─────────────────────────────────────────────────────────── */
    printf(BOLD "\n── Things ──────────────────────────────────────────────\n" RESET);
    print_result("getThings",     openhab_things_get_all(c, 0, 0, NULL), c);

    /* ── Rules ──────────────────────────────────────────────────────────── */
    printf(BOLD "\n── Rules ───────────────────────────────────────────────\n" RESET);
    print_result("getRules",      openhab_rules_get_all(c, NULL, NULL, 0, 0), c);

    /* ── Audio ──────────────────────────────────────────────────────────── */
    printf(BOLD "\n── Audio ───────────────────────────────────────────────\n" RESET);
    print_result("getDefaultSink",   openhab_audio_get_default_sink(c), c);
    print_result("getDefaultSource", openhab_audio_get_default_source(c), c);
    print_result("getSinks",         openhab_audio_get_sinks(c), c);
    print_result("getSources",       openhab_audio_get_sources(c), c);

    /* ── Sitemaps ────────────────────────────────────────────────────────── */
    printf(BOLD "\n── Sitemaps ────────────────────────────────────────────\n" RESET);
    print_result("getSitemaps",   openhab_sitemaps_get_all(c), c);

    /* ── Tags ───────────────────────────────────────────────────────────── */
    printf(BOLD "\n── Tags ────────────────────────────────────────────────\n" RESET);
    print_result("getTags",       openhab_tags_get_all(c, NULL, NULL), c);

    /* ── Templates / ModuleTypes / ProfileTypes ─────────────────────────── */
    printf(BOLD "\n── Automation ──────────────────────────────────────────\n" RESET);
    print_result("getTemplates",    openhab_templates_get_all(c, NULL), c);
    print_result("getModuleTypes",  openhab_module_types_get_all(c, NULL, NULL), c);
    print_result("getProfileTypes", openhab_profile_types_get_all(c, NULL, NULL, NULL), c);

    /* ── UI ─────────────────────────────────────────────────────────────── */
    printf(BOLD "\n── UI ──────────────────────────────────────────────────\n" RESET);
    print_result("getUITiles",    openhab_ui_get_tiles(c), c);

    /* ── Iconsets ───────────────────────────────────────────────────────── */
    printf(BOLD "\n── Misc ────────────────────────────────────────────────\n" RESET);
    print_result("getIconsets",    openhab_iconsets_get_all(c, NULL), c);
    print_result("getThingTypes",  openhab_thing_types_get_all(c, NULL, NULL), c);
    print_result("getChannelTypes",openhab_channel_types_get_all(c, NULL, NULL), c);

    /* ── Voice ──────────────────────────────────────────────────────────── */
    printf(BOLD "\n── Voice ───────────────────────────────────────────────\n" RESET);
    print_result("getVoices",       openhab_voice_get_voices(c), c);
    print_result("getInterpreters", openhab_voice_get_interpreters(c, NULL), c);

    /* ── SSE (brief, 3 events max) ──────────────────────────────────────── */
    printf(BOLD "\n── SSE (max 3 events, dann Stop) ───────────────────────\n" RESET);
    int count = 0;
    printf("  Lausche auf openhab/items/* …\n");
    openhab_events_item_state_changed(c, NULL, sse_cb, &count);
    printf("  %d SSE-Events empfangen.\n", count);

    /* ── Summary ────────────────────────────────────────────────────────── */
    printf(BOLD "\n═══════════════════════════════════════════════════════\n" RESET);
    printf("  Ergebnis: %d Tests   " GREEN BOLD "%d" RESET " bestanden   "
           RED BOLD "%d" RESET " fehlgeschlagen\n",
           passed + failed, passed, failed);
    printf(BOLD "═══════════════════════════════════════════════════════\n\n" RESET);

    openhab_client_destroy(c);
    return failed > 0 ? 1 : 0;
}
