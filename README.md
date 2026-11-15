# c-openhab-rest-client

A C client for the openHAB REST API – for system tools, gateways, embedded Linux,
Raspberry Pi and every program where C is the language of choice.

It is part of a family of libraries with **the same classes, methods, parameters and
results** in every language: [Python](https://github.com/Michdo93/python-openhab-rest-client)
(the reference), [JavaScript](https://github.com/Michdo93/js-openhab-rest-client),
[Node.js](https://github.com/Michdo93/nodejs-openhab-rest-client),
[Java](https://github.com/Michdo93/java-openhab-rest-client),
[Android/Kotlin](https://github.com/Michdo93/android-openhab-rest-client),
[C++](https://github.com/Michdo93/cpp-openhab-rest-client),
[C#](https://github.com/Michdo93/csharp-openhab-rest-client) and C.
Tests for openHAB installations: [c-openhab-test-suite](https://github.com/Michdo93/c-openhab-test-suite).

```c
#include <openhab/openhab.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    openhab_client_t* c = openhab_client_new("http://127.0.0.1:8080",
                                             .token = getenv("OPENHAB_TOKEN"));

    cJSON* r = openhab_items_sendCommand(c, "Wohnzimmer_Licht", "ON");
    if (openhab_is_error(r)) fprintf(stderr, "%s\n", openhab_error(r));
    cJSON_Delete(r);

    cJSON* lights = openhab_items_getItems(c, .tags = "Light", .fields = "name,state");
    cJSON* item;
    cJSON_ArrayForEach(item, lights)
        printf("%s = %s\n", openhab_json_str(item, "name"), openhab_json_str(item, "state"));
    cJSON_Delete(lights);

    openhab_client_destroy(c);
    return 0;
}
```

## What is new in 2.0.0

Version 2.0.0 is a rewrite. The REST functions are generated from python-openhab-rest-client
(`tools/py2c.py`), statement by statement – same endpoints, headers, query parameters,
error messages and results. A differential test with 79 calls against openHAB 5 gives
identical results for Python and C.

- all 178 methods of the Python library (1.0.0: 121, several with different names)
- results as [cJSON](https://github.com/DaveGamble/cJSON) values instead of raw strings;
  errors as `{"error": "..."}`, empty successes as `{"message": "OK"}` – no more `NULL`
  plus a per-client "last error"
- optional parameters as named arguments: `openhab_items_getItem(c, name, .recursive = OPENHAB_FALSE)`
- event streams that you read with a timeout, interrupt from another thread and close at any time
- `#` in channel and action UIDs is escaped, the persistence service is sent, thread-safe requests

Migrating from 1.x: every function now returns `cJSON*` (free with `cJSON_Delete()`), optional
arguments are named, and the stream functions return an `openhab_sse_t*` instead of taking a
callback. `openhab_client_create(url, user, password, token)` still works.

## Requirements

- C11 compiler: GCC, Clang, MSVC 2019+ or MinGW-w64
- CMake 3.16+
- [libcurl](https://curl.se/libcurl/) and [cJSON](https://github.com/DaveGamble/cJSON)
  (cJSON is downloaded automatically if it is not installed)

| System | Packages |
|---|---|
| Debian, Ubuntu, Raspberry Pi OS | `sudo apt install build-essential cmake libcurl4-openssl-dev libcjson-dev` |
| Fedora | `sudo dnf install gcc cmake libcurl-devel cjson-devel` |
| macOS (Homebrew) | `brew install cmake curl cjson` |
| Windows (vcpkg) | `vcpkg install curl cjson` |
| Windows (MSYS2 MinGW) | `pacman -S mingw-w64-x86_64-{gcc,cmake,curl,cjson}` |

## Using the library

### CMake FetchContent (recommended)

```cmake
cmake_minimum_required(VERSION 3.16)
project(myapp C)
include(FetchContent)
FetchContent_Declare(c_openhab_rest_client
  GIT_REPOSITORY https://github.com/Michdo93/c-openhab-rest-client.git
  GIT_TAG 2.0.0)
set(OPENHAB_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(c_openhab_rest_client)

add_executable(myapp main.c)
target_link_libraries(myapp PRIVATE openhab::rest_client)
```

### Installed library

```bash
git clone https://github.com/Michdo93/c-openhab-rest-client.git
cmake -S c-openhab-rest-client -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
sudo cmake --install build
```

```cmake
find_package(OpenHABRestClient 2 REQUIRED)
target_link_libraries(myapp PRIVATE openhab::openhab_rest_client)
```

or without CMake: `gcc main.c $(pkg-config --cflags --libs openhab_rest_client)`.

## Concepts

### Client

```c
openhab_client_t* c = openhab_client_new("http://127.0.0.1:8080", .token = token);
openhab_client_t* cloud = openhab_client_new("https://myopenhab.org",
                                             .username = "me@example.com", .password = pw);
openhab_client_t* slow = openhab_client_new(url, .token = token, .timeout = 30);

openhab_client_is_logged_in(c);   /* was openHAB reachable? (Python: isLoggedIn) */
openhab_client_last_error(c);     /* why not */
openhab_client_destroy(c);
```

A client may be used from several threads at the same time.

### Functions and arguments

`Items.getItems()` of the Python library is `openhab_items_getItems()`, `ThingTypes.getThingType()`
is `openhab_thing_types_getThingType()`. Required parameters are positional, optional ones are
named (C99 designated initializers behind a macro – C++ calls the function with the trailing
underscore and an args struct):

```c
openhab_items_getItem(c, "Wohnzimmer_Licht");
openhab_items_getItem(c, "Wohnzimmer_Licht", .metadata = "semantics", .recursive = OPENHAB_FALSE);
openhab_persistence_getItemPersistenceData(c, "Temp", .serviceID = "rrd4j",
                                           .startTime = "2026-11-01T00:00:00.000Z");
```

Optional booleans are `openhab_flag` (`OPENHAB_TRUE`, `OPENHAB_FALSE`; unset = the default of the
Python library). Dictionaries and lists are passed as `cJSON*`.

From C++ (C++20) the same calls look like this – the headers contain no C++ keywords and are
wrapped in `extern "C"`:

```cpp
openhab_client_t* c = openhab_client_new_("http://127.0.0.1:8080", {.token = token});
cJSON* lights = openhab_items_getItems_(c, {.tags = "Light", .fields = "name,state"});
```

### Results

Every REST function returns a `cJSON*` that you free with `cJSON_Delete()`:

| Response | Result |
|---|---|
| JSON | object or array |
| text (e.g. an item state) | string: `r->valuestring` |
| empty success | `{"message": "OK"}` (or the status object, where Python returns it) |
| error | `{"error": "Item not found."}` – test with `openhab_is_error(r)`, read with `openhab_error(r)` |

Helpers: `openhab_json_get(v, "payload.value")`, `openhab_json_str(v, "0.name")`,
`openhab_json_num(v, "state", 0)`, `openhab_json_print(v)`.

### Event streams (Server-Sent Events)

```c
openhab_sse_t* s = openhab_item_events_ItemStateChangedEvent(c, "Wohnzimmer_Licht");
if (openhab_sse_is_error(s)) fprintf(stderr, "%s\n", openhab_sse_error(s));
cJSON* ev;
while (openhab_sse_is_open(s)) {
    ev = openhab_sse_next_event(s, 1000, 0);        /* wait at most 1 s */
    if (!ev) continue;                               /* timeout: do other work */
    printf("%s\n", openhab_json_str(ev, "payload.value"));
    cJSON_Delete(ev);
}
openhab_sse_close(s);
```

`openhab_sse_interrupt(s)` (from another thread or a signal handler) ends a waiting call at once.
`openhab_sse_next_line()` returns the raw lines, `openhab_sse_parse_data()` decodes a `data:` line.

### Low-level requests

`openhab_client_get/post/put/delete(c, "/items", headers, data, params)` reach any endpoint.

## Development

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure      # unit tests with a local HTTP server
OPENHAB_URL=http://127.0.0.1:8080 OPENHAB_TOKEN=oh.xxx ctest --test-dir build   # + integration

# regenerate the REST functions from python-openhab-rest-client
python3 tools/py2c.py ../python-openhab-rest-client/openhab .
```

## Functions

### Actions

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_actions_getActions` | thingUID | .language | `cJSON*` |
| `openhab_actions_executeAction` | thingUID, actionUID, actionInputs | .language | `cJSON*` |

### Addons

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_addons_getAddons` |  | .serviceID, .language | `cJSON*` |
| `openhab_addons_getAddon` | addonID | .serviceID, .language | `cJSON*` |
| `openhab_addons_getAddonConfig` | addonID | .serviceID | `cJSON*` |
| `openhab_addons_updateAddonConfig` | addonID, configData | .serviceID | `cJSON*` |
| `openhab_addons_installAddon` | addonID | .serviceID | `cJSON*` |
| `openhab_addons_uninstallAddon` | addonID | .serviceID | `cJSON*` |
| `openhab_addons_getAddonServices` |  | .language | `cJSON*` |
| `openhab_addons_getAddonSuggestions` |  | .language | `cJSON*` |
| `openhab_addons_getAddonTypes` |  | .serviceID, .language | `cJSON*` |
| `openhab_addons_installAddonFromUrl` | url |  | `cJSON*` |

### Audio

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_audio_getDefaultSink` |  | .language | `cJSON*` |
| `openhab_audio_getDefaultSource` |  | .language | `cJSON*` |
| `openhab_audio_getSinks` |  | .language | `cJSON*` |
| `openhab_audio_getSources` |  | .language | `cJSON*` |

### Auth

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_auth_getAPITokens` |  |  | `cJSON*` |
| `openhab_auth_revokeAPIToken` | tokenName |  | `cJSON*` |
| `openhab_auth_logout` | refreshToken, sessionID |  | `cJSON*` |
| `openhab_auth_getSessions` |  |  | `cJSON*` |
| `openhab_auth_getToken` |  | .useCookie, .grantType, .code, .redirectURI, .clientID, .refreshToken, .codeVerifier | `cJSON*` |

### ChannelEvents

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_channel_events_ChannelDescriptionChangedEvent` |  | .channelUID | `openhab_sse_t*` |
| `openhab_channel_events_ChannelTriggeredEvent` |  | .channelUID | `openhab_sse_t*` |

### ChannelTypes

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_channel_types_getChannelTypes` |  | .prefixes, .language | `cJSON*` |
| `openhab_channel_types_getChannelType` | channelTypeUID | .language | `cJSON*` |
| `openhab_channel_types_getLinkableItemTypes` | channelTypeUID |  | `cJSON*` |

### ConfigDescriptions

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_config_descriptions_getConfigDescriptions` |  | .scheme, .language | `cJSON*` |
| `openhab_config_descriptions_getConfigDescription` | uri | .language | `cJSON*` |

### Discovery

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_discovery_getDiscoveryBindings` |  |  | `cJSON*` |
| `openhab_discovery_getBindingInfo` | bindingID | .language | `cJSON*` |
| `openhab_discovery_startBindingScan` | bindingID | .input | `cJSON*` |

### Events

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_events_getEvents` |  | .topics | `openhab_sse_t*` |
| `openhab_events_initiateStateTracker` |  |  | `openhab_sse_t*` |
| `openhab_events_updateSSEConnectionItems` | connectionID, items |  | `cJSON*` |

### Iconsets

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_iconsets_getIconsets` |  | .language | `cJSON*` |

### Inbox

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_inbox_getDiscoveredThings` |  | .includeIgnored | `cJSON*` |
| `openhab_inbox_removeDiscoveryResult` | thingUID |  | `cJSON*` |
| `openhab_inbox_approveDiscoveryResult` | thingUID, thingLabel | .newThingID, .language | `cJSON*` |
| `openhab_inbox_ignoreDiscoveryResult` | thingUID |  | `cJSON*` |
| `openhab_inbox_unignoreDiscoveryResult` | thingUID |  | `cJSON*` |

### InboxEvents

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_inbox_events_InboxAddedEvent` |  | .thingUID | `openhab_sse_t*` |
| `openhab_inbox_events_InboxRemovedEvent` |  | .thingUID | `openhab_sse_t*` |
| `openhab_inbox_events_InboxUpdatedEvent` |  | .thingUID | `openhab_sse_t*` |

### ItemEvents

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_item_events_ItemEvent` |  |  | `openhab_sse_t*` |
| `openhab_item_events_ItemAddedEvent` |  | .itemName | `openhab_sse_t*` |
| `openhab_item_events_ItemRemovedEvent` |  | .itemName | `openhab_sse_t*` |
| `openhab_item_events_ItemUpdatedEvent` |  | .itemName | `openhab_sse_t*` |
| `openhab_item_events_ItemCommandEvent` |  | .itemName | `openhab_sse_t*` |
| `openhab_item_events_ItemStateEvent` |  | .itemName | `openhab_sse_t*` |
| `openhab_item_events_ItemStatePredictedEvent` |  | .itemName | `openhab_sse_t*` |
| `openhab_item_events_ItemStateChangedEvent` |  | .itemName | `openhab_sse_t*` |
| `openhab_item_events_GroupItemStateChangedEvent` |  | .itemName, .memberName | `openhab_sse_t*` |

### Items

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_items_getItems` |  | .type, .tags, .metadata, .recursive, .fields, .staticDataOnly, .language, .parents | `cJSON*` |
| `openhab_items_addOrUpdateItems` | items |  | `cJSON*` |
| `openhab_items_getItem` | itemName | .metadata, .recursive, .language, .parents | `cJSON*` |
| `openhab_items_addOrUpdateItem` | itemName, itemData | .language | `cJSON*` |
| `openhab_items_sendCommand` | itemName, command | .source | `cJSON*` |
| `openhab_items_postUpdate` | itemName, state | .source | `cJSON*` |
| `openhab_items_deleteItem` | itemName |  | `cJSON*` |
| `openhab_items_addGroupMember` | itemName, memberItemName |  | `cJSON*` |
| `openhab_items_removeGroupMember` | itemName, memberItemName |  | `cJSON*` |
| `openhab_items_addMetadata` | itemName, namespace, metadata |  | `cJSON*` |
| `openhab_items_removeMetadata` | itemName, namespace |  | `cJSON*` |
| `openhab_items_getMetadataNamespaces` | itemName | .language | `cJSON*` |
| `openhab_items_getSemanticItem` | itemName, semanticClass | .language | `cJSON*` |
| `openhab_items_getItemState` | itemName |  | `cJSON*` |
| `openhab_items_updateItemState` | itemName, state | .language, .source | `cJSON*` |
| `openhab_items_addTag` | itemName, tag |  | `cJSON*` |
| `openhab_items_removeTag` | itemName, tag |  | `cJSON*` |
| `openhab_items_purgeOrphanedMetadata` |  |  | `cJSON*` |

### LinkEvents

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_link_events_ItemChannelLinkAddedEvent` |  | .itemName, .channelUID | `openhab_sse_t*` |
| `openhab_link_events_ItemChannelLinkRemovedEvent` |  | .itemName, .channelUID | `openhab_sse_t*` |

### Links

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_links_getLinks` |  | .channelUID, .itemName | `cJSON*` |
| `openhab_links_getLink` | itemName, channelUID |  | `cJSON*` |
| `openhab_links_linkItemToChannel` | itemName, channelUID, configuration |  | `cJSON*` |
| `openhab_links_unlinkItemFromChannel` | itemName, channelUID |  | `cJSON*` |
| `openhab_links_deleteAllLinks` | object |  | `cJSON*` |
| `openhab_links_getOrphanLinks` |  |  | `cJSON*` |
| `openhab_links_purgeUnusedLinks` |  |  | `cJSON*` |

### Logging

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_logging_getLoggers` |  |  | `cJSON*` |
| `openhab_logging_getLogger` | loggerName |  | `cJSON*` |
| `openhab_logging_modifyOrAddLogger` | loggerName, level |  | `cJSON*` |
| `openhab_logging_removeLogger` | loggerName |  | `cJSON*` |

### ModuleTypes

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_module_types_getModuleTypes` |  | .tags, .typeFilter, .language | `cJSON*` |
| `openhab_module_types_getModuleType` | moduleTypeUID | .language | `cJSON*` |

### Persistence

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_persistence_getServices` |  | .language | `cJSON*` |
| `openhab_persistence_getServiceConfiguration` | serviceID |  | `cJSON*` |
| `openhab_persistence_setServiceConfiguration` | serviceID, config |  | `cJSON*` |
| `openhab_persistence_deleteServiceConfiguration` | serviceID |  | `cJSON*` |
| `openhab_persistence_getItemsFromService` |  | .serviceID, .itemName | `cJSON*` |
| `openhab_persistence_getItemPersistenceData` | itemName | .serviceID, .startTime, .endTime, .page, .pageLength, .boundary, .itemState, .displayState, .language | `cJSON*` |
| `openhab_persistence_storeItemData` | itemName, time, state | .serviceID | `cJSON*` |
| `openhab_persistence_deleteItemData` | itemName, startTime, endTime, serviceID |  | `cJSON*` |

### ProfileTypes

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_profile_types_getProfileTypes` |  | .channelTypeUID, .itemType, .language | `cJSON*` |

### Rules

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_rules_getRules` |  | .prefix, .tags, .summary, .staticDataOnly | `cJSON*` |
| `openhab_rules_createRule` | ruleData |  | `cJSON*` |
| `openhab_rules_getRule` | ruleUID |  | `cJSON*` |
| `openhab_rules_updateRule` | ruleUID, ruleData |  | `cJSON*` |
| `openhab_rules_deleteRule` | ruleUID |  | `cJSON*` |
| `openhab_rules_getModule` | ruleUID, moduleCategory, moduleID |  | `cJSON*` |
| `openhab_rules_getModuleConfig` | ruleUID, moduleCategory, moduleID |  | `cJSON*` |
| `openhab_rules_getModuleConfigParam` | ruleUID, moduleCategory, moduleID, param |  | `cJSON*` |
| `openhab_rules_setModuleConfigParam` | ruleUID, moduleCategory, moduleID, param, value |  | `cJSON*` |
| `openhab_rules_getActions` | ruleUID |  | `cJSON*` |
| `openhab_rules_getConditions` | ruleUID |  | `cJSON*` |
| `openhab_rules_getConfiguration` | ruleUID |  | `cJSON*` |
| `openhab_rules_updateConfiguration` | ruleUID, configData |  | `cJSON*` |
| `openhab_rules_setRuleState` | ruleUID, enable |  | `cJSON*` |
| `openhab_rules_enable` | ruleUID |  | `cJSON*` |
| `openhab_rules_disable` | ruleUID |  | `cJSON*` |
| `openhab_rules_runNow` | ruleUID | .contextData | `cJSON*` |
| `openhab_rules_getTriggers` | ruleUID |  | `cJSON*` |
| `openhab_rules_simulateSchedule` | fromTime, untilTime |  | `cJSON*` |

### Services

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_services_getServices` |  | .language | `cJSON*` |
| `openhab_services_getService` | serviceID | .language | `cJSON*` |
| `openhab_services_getServiceConfig` | serviceID |  | `cJSON*` |
| `openhab_services_updateServiceConfig` | serviceID, configData | .language | `cJSON*` |
| `openhab_services_deleteServiceConfig` | serviceID |  | `cJSON*` |
| `openhab_services_getServiceContexts` | serviceID | .language | `cJSON*` |

### Sitemaps

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_sitemaps_getSitemaps` |  |  | `cJSON*` |
| `openhab_sitemaps_getSitemap` | sitemapName | .type, .jsonCallback, .includeHidden, .language | `cJSON*` |
| `openhab_sitemaps_getSitemapPage` | sitemapName, pageID | .subscriptionID, .includeHidden, .language | `cJSON*` |
| `openhab_sitemaps_getFullSitemap` | sitemapName | .subscriptionID, .includeHidden, .language | `cJSON*` |
| `openhab_sitemaps_getSitemapEvents` | subscriptionID | .sitemapName, .pageID | `openhab_sse_t*` |
| `openhab_sitemaps_getFullSitemapEvents` | subscriptionID | .sitemapName | `openhab_sse_t*` |
| `openhab_sitemaps_subscribeToSitemapEvents` |  |  | `cJSON*` |

### Systeminfo

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_systeminfo_getSystemInfo` |  |  | `cJSON*` |
| `openhab_systeminfo_getUoMInfo` |  |  | `cJSON*` |

### Tags

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_tags_getTags` |  | .language | `cJSON*` |
| `openhab_tags_createTag` | tagData | .language | `cJSON*` |
| `openhab_tags_getTag` | tagID | .language | `cJSON*` |
| `openhab_tags_updateTag` | tagID, tagData | .language | `cJSON*` |
| `openhab_tags_deleteTag` | tagID | .language | `cJSON*` |

### Templates

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_templates_getTemplates` |  | .language | `cJSON*` |
| `openhab_templates_getTemplate` | templateUID | .language | `cJSON*` |

### ThingEvents

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_thing_events_ThingAddedEvent` |  | .thingUID | `openhab_sse_t*` |
| `openhab_thing_events_ThingRemovedEvent` |  | .thingUID | `openhab_sse_t*` |
| `openhab_thing_events_ThingUpdatedEvent` |  | .thingUID | `openhab_sse_t*` |
| `openhab_thing_events_ThingStatusInfoEvent` |  | .thingUID | `openhab_sse_t*` |
| `openhab_thing_events_ThingStatusInfoChangedEvent` |  | .thingUID | `openhab_sse_t*` |

### Things

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_things_getThings` |  | .summary, .staticDataOnly, .language | `cJSON*` |
| `openhab_things_createThing` | thingData | .language | `cJSON*` |
| `openhab_things_getThing` | thingUID | .language | `cJSON*` |
| `openhab_things_updateThing` | thingUID, thingData | .language | `cJSON*` |
| `openhab_things_deleteThing` | thingUID | .force, .language | `cJSON*` |
| `openhab_things_updateThingConfiguration` | thingUID, configurationData | .language | `cJSON*` |
| `openhab_things_getThingConfigStatus` | thingUID | .language | `cJSON*` |
| `openhab_things_setThingStatus` | thingUID, enabled | .language | `cJSON*` |
| `openhab_things_enableThing` | thingUID |  | `cJSON*` |
| `openhab_things_disableThing` | thingUID |  | `cJSON*` |
| `openhab_things_updateThingFirmware` | thingUID, firmwareVersion | .language | `cJSON*` |
| `openhab_things_getThingFirmwareStatus` | thingUID | .language | `cJSON*` |
| `openhab_things_getThingFirmwares` | thingUID | .language | `cJSON*` |
| `openhab_things_getThingStatus` | thingUID | .language | `cJSON*` |

### ThingTypes

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_thing_types_getThingTypes` |  | .bindingID, .language | `cJSON*` |
| `openhab_thing_types_getThingType` | thingTypeUID | .language | `cJSON*` |

### Transformations

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_transformations_getTransformations` |  |  | `cJSON*` |
| `openhab_transformations_getTransformation` | transformationUID |  | `cJSON*` |
| `openhab_transformations_updateTransformation` | transformationUID, transformationData |  | `cJSON*` |
| `openhab_transformations_deleteTransformation` | transformationUID |  | `cJSON*` |
| `openhab_transformations_getTransformationServices` |  |  | `cJSON*` |

### UI

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_ui_getUIComponents` | namespace | .summary | `cJSON*` |
| `openhab_ui_addUIComponent` | namespace, componentData |  | `cJSON*` |
| `openhab_ui_getUIComponent` | namespace, componentUID |  | `cJSON*` |
| `openhab_ui_updateUIComponent` | namespace, componentUID, componentData |  | `cJSON*` |
| `openhab_ui_deleteUIComponent` | namespace, componentUID |  | `cJSON*` |
| `openhab_ui_getUITiles` |  |  | `cJSON*` |

### UUID

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_uuid_getUUID` |  |  | `cJSON*` |

### Voice

| Function | Parameters | Named arguments | Returns |
|---|---|---|---|
| `openhab_voice_getDefaultVoice` |  | .language | `cJSON*` |
| `openhab_voice_startDialog` | sourceID | .ksID, .sttID, .ttsID, .voiceID, .hliIDs, .sinkID, .keyword, .listeningItem, .language | `cJSON*` |
| `openhab_voice_stopDialog` | sourceID |  | `cJSON*` |
| `openhab_voice_getInterpreters` |  | .language | `cJSON*` |
| `openhab_voice_interpretText` | text | .language | `cJSON*` |
| `openhab_voice_getInterpreter` | interpreterID | .language | `cJSON*` |
| `openhab_voice_interpretTextBatch` | text, IDs | .language | `cJSON*` |
| `openhab_voice_listenAndAnswer` | sourceID, sttID, ttsID, voiceID, hliIDs, sinkID, listeningItem | .language | `cJSON*` |
| `openhab_voice_sayText` | text, voiceID, sinkID | .volume | `cJSON*` |
| `openhab_voice_getVoices` |  | .language | `cJSON*` |


## License

MIT – see [LICENSE](LICENSE).
