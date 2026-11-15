/*
 * Integration tests against a real openHAB (OPENHAB_URL, OPENHAB_TOKEN).
 * Without these variables the test is skipped (exit code 77).
 * It creates and deletes the item CTest_Switch; everything else is only read.
 */
#include <openhab/openhab.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int failures = 0, checks = 0;
#define CHECK(cond, ...) do { checks++; if (!(cond)) { failures++; \
    printf("FAIL %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); } } while (0)

static const char* json(const cJSON* v) {
    static char buf[1024];
    char* t = cJSON_PrintUnformatted(v);
    snprintf(buf, sizeof buf, "%s", t ? t : "NULL");
    free(t);
    return buf;
}

int main(void) {
    const char* url = getenv("OPENHAB_URL");
    const char* token = getenv("OPENHAB_TOKEN");
    if (!url || !*url || !token || !*token) {
        puts("OPENHAB_URL/OPENHAB_TOKEN not set – skipped");
        return 77;
    }
    openhab_client_t* c = openhab_client_new(url, .token = token);
    CHECK(openhab_client_is_logged_in(c), "login: %s", openhab_client_last_error(c));

    cJSON* r = openhab_systeminfo_getSystemInfo(c);
    CHECK(openhab_json_str(r, "systemInfo.osName") != NULL, "systeminfo %s", json(r));
    cJSON_Delete(r);

    /* create, command, state, events, delete */
    cJSON* item = cJSON_Parse("{\"type\":\"Switch\",\"name\":\"CTest_Switch\",\"label\":\"C-Test\","
                              "\"tags\":[\"Switch\"]}");
    r = openhab_items_addOrUpdateItem(c, "CTest_Switch", item);
    CHECK(!openhab_is_error(r), "create %s", json(r));
    cJSON_Delete(r);
    cJSON_Delete(item);

    r = openhab_items_postUpdate(c, "CTest_Switch", "OFF");
    cJSON_Delete(r);
    openhab_sse_t* s = openhab_item_events_ItemStateChangedEvent(c, "CTest_Switch");
    CHECK(!openhab_sse_is_error(s), "stream %s", openhab_sse_error(s));
    r = openhab_items_sendCommand(c, "CTest_Switch", "ON");
    CHECK(strcmp(json(r), "{\"message\":\"OK\"}") == 0, "command %s", json(r));
    cJSON_Delete(r);
    cJSON* ev = openhab_sse_next_event(s, 5000, 0);
    CHECK(ev && openhab_json_str(ev, "payload.value") &&
          strcmp(openhab_json_str(ev, "payload.value"), "ON") == 0, "event %s", json(ev));
    cJSON_Delete(ev);
    openhab_sse_close(s);

    r = openhab_items_getItemState(c, "CTest_Switch");
    CHECK(cJSON_IsString(r) && strcmp(r->valuestring, "ON") == 0, "state %s", json(r));
    cJSON_Delete(r);

    r = openhab_items_sendCommand(c, "CTest_Switch", "HALB");
    CHECK(openhab_is_error(r), "invalid command %s", json(r));
    cJSON_Delete(r);

    r = openhab_items_getItems(c, .tags = "Switch", .fields = "name");
    int found = 0;
    cJSON* e;
    cJSON_ArrayForEach(e, r) {
        const char* name = openhab_json_str(e, "name");
        found |= name && strcmp(name, "CTest_Switch") == 0;
    }
    CHECK(found, "getItems with tag");
    cJSON_Delete(r);

    r = openhab_items_deleteItem(c, "CTest_Switch");
    CHECK(strcmp(json(r), "{\"message\":\"OK\"}") == 0, "delete %s", json(r));
    cJSON_Delete(r);
    r = openhab_items_getItem(c, "CTest_Switch");
    CHECK(openhab_is_error(r) && strcmp(openhab_error(r), "Item not found.") == 0, "gone %s",
          json(r));
    cJSON_Delete(r);

    /* stream without events: ALIVE messages keep it open (long run: OPENHAB_LONG_SSE=seconds) */
    int seconds = getenv("OPENHAB_LONG_SSE") ? atoi(getenv("OPENHAB_LONG_SSE")) : 12;
    s = openhab_item_events_ItemStateChangedEvent(c, "Gibts_nicht_Item");
    int alive = 0;
    for (int i = 0; i < seconds; i++) {
        ev = openhab_sse_next_event(s, 1000, 1);
        if (ev) alive++;
        cJSON_Delete(ev);
    }
    CHECK(openhab_sse_is_open(s) && alive >= 1, "stream alive after %d s (%d ALIVE)", seconds, alive);
    openhab_sse_close(s);

    openhab_client_destroy(c);
    printf("%d checks, %d failed\n", checks, failures);
    return failures ? 1 : 0;
}
