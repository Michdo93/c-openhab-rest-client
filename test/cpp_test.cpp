// The headers can be used from C++ (C++20 for named arguments): no C++ keywords as
// parameter names, extern "C", optional arguments as designated initializers.
#include <openhab/openhab.h>

#include <cstdio>
#include <cstring>

int main() {
    // nobody listens on port 9 – every call must return an error object, no crash
    openhab_client_t* c = openhab_client_new_("http://127.0.0.1:9", {.token = "oh.test",
                                                                    .timeout = 2});
    int failures = 0;
    cJSON* items = openhab_items_getItems_(c, {.tags = "Light", .fields = "name"});
    if (!openhab_is_error(items)) failures++;
    cJSON_Delete(items);
    cJSON* meta = openhab_items_addMetadata(c, "Licht", "homekit", nullptr);
    if (!openhab_is_error(meta)) failures++;
    cJSON_Delete(meta);
    cJSON* ui = openhab_ui_getUIComponents_(c, "ui:page", {.summary = OPENHAB_TRUE});
    if (!openhab_is_error(ui)) failures++;
    cJSON_Delete(ui);
    openhab_client_destroy(c);
    std::printf("C++: %d failed\n", failures);
    return failures ? 1 : 0;
}
