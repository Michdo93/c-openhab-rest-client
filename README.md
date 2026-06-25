# c-openhab-rest-client

A C client for the openHAB REST API. This library enables interaction with the openHAB REST API from pure C applications — embedded systems, firmware, system tools, or any environment where C is the language of choice.

It mirrors the [python-openhab-rest-client](https://github.com/Michdo93/python-openhab-rest-client) method-naming convention: `openhab_<class>_<methodName>()`.

**Dependencies:**
- [libcurl](https://curl.se/libcurl/) — HTTP communication (the only runtime dependency)

All API functions return heap-allocated JSON strings. The caller is responsible for calling `free()` on every returned string.

## Features

Supports the following openHAB REST API endpoints:

- Actions
- Addons
- Audio
- Auth
- ChannelTypes
- ConfigDescriptions
- Discovery
- Events (SSE — ItemStateChanged, ItemCommand, ThingStatus, generic)
- Iconsets
- Inbox
- Items
- Links
- Logging
- ModuleTypes
- Persistence
- ProfileTypes
- Rules
- Services
- Sitemaps
- Systeminfo
- Tags
- Templates
- ThingTypes
- Things
- Transformations
- UI
- UUID
- Voice

Server-Sent Events (SSE) are supported via a callback function (`openhab_sse_callback_t`).

## Requirements

- **C11** or later
- **CMake 3.16** or later
- **libcurl** development headers
- A C compiler: GCC 5+, Clang 3.6+, MSVC 2019+, or MinGW-w64

---

## Building the Library

The library uses CMake and produces both a **shared library** and a **static library**.

---

### Linux / macOS

#### 1. Install dependencies

**Ubuntu / Debian:**
```bash
sudo apt-get update
sudo apt-get install -y libcurl4-openssl-dev cmake build-essential
```

**Fedora / RHEL / CentOS:**
```bash
sudo dnf install -y libcurl-devel cmake gcc make
```

**Arch Linux:**
```bash
sudo pacman -S curl cmake base-devel
```

**macOS (Homebrew):**
```bash
brew install curl cmake
```

#### 2. Clone and build

```bash
git clone https://github.com/Michdo93/c-openhab-rest-client.git
cd c-openhab-rest-client
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j$(nproc)
```

This produces:
- `build/libopenhab_rest_client.so` + `build/libopenhab_rest_client.so.1` (shared, versioned)
- `build/libopenhab_rest_client.a` (static)
- `build/openhab_test` (test executable)

#### 3. Install system-wide (optional)

```bash
sudo cmake --install .
# Installs to /usr/local/lib/ and /usr/local/include/openhab/
```

Custom prefix:
```bash
cmake --install . --prefix /opt/openhab-c-client
```

---

### Windows (MinGW-w64 / MSYS2)

```bash
pacman -S mingw-w64-x86_64-curl mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

The CMake build links `ws2_32`, `crypt32`, `bcrypt`, `wldap32`, and `normaliz` automatically on Windows.

Produces `openhab_rest_client.dll` and `libopenhab_rest_client.a`.

---

### Windows (MSVC + vcpkg)

```powershell
vcpkg install curl --triplet x64-windows
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release `
    -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_INSTALLATION_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build . --config Release
```

Produces `Release/openhab_rest_client.dll` and `Release/openhab_rest_client.lib`.

#### Visual Studio

1. Open Visual Studio and choose **Open a local folder**.
2. Select the `c-openhab-rest-client` directory.
3. Visual Studio detects `CMakeLists.txt` automatically.
4. Configure the CMake toolchain file if using vcpkg under **Project → CMake Settings**.
5. **Build → Build All**.

---

### Raspberry Pi / ARM / Embedded Linux

Same steps as Linux:

```bash
sudo apt-get install -y libcurl4-openssl-dev cmake build-essential
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j4
```

Cross-compilation for AArch64 (from x86-64 host), using the included toolchain file:

```bash
sudo apt-get install -y gcc-aarch64-linux-gnu
mkdir build && cd build
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=../cmake/linux-aarch64.cmake \
    -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

---

### Cross-compilation for Windows from Linux (MinGW)

```bash
sudo apt-get install -y gcc-mingw-w64-x86-64
mkdir build && cd build
cmake .. -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
         -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

---

## Adding the Library to Your Project

### Option 1: CMake `find_package` (after system install)

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyApp LANGUAGES C)
set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)

add_executable(myapp main.c)
target_include_directories(myapp PRIVATE /usr/local/include)
target_link_libraries(myapp PRIVATE openhab_rest_client ${CURL_LIBRARIES})
```

---

### Option 2: CMake `add_subdirectory`

```bash
git clone https://github.com/Michdo93/c-openhab-rest-client.git libs/openhab
```

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyApp LANGUAGES C)
set(CMAKE_C_STANDARD 11)

add_subdirectory(libs/openhab)
find_package(CURL REQUIRED)

add_executable(myapp main.c)
target_link_libraries(myapp PRIVATE
    openhab_rest_client_static
    ${CURL_LIBRARIES})
```

---

### Option 3: CMake `FetchContent`

```cmake
include(FetchContent)
FetchContent_Declare(
    c_openhab_rest_client
    GIT_REPOSITORY https://github.com/Michdo93/c-openhab-rest-client.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(c_openhab_rest_client)

find_package(CURL REQUIRED)

add_executable(myapp main.c)
target_link_libraries(myapp PRIVATE
    openhab_rest_client_static ${CURL_LIBRARIES})
```

---

### Option 4: Manual compilation (no CMake)

**Linux / macOS:**
```bash
gcc -std=c11 -O2 \
    -I/path/to/c-openhab-rest-client/include \
    c-openhab-rest-client/src/openhab_client.c \
    c-openhab-rest-client/src/openhab_api.c \
    main.c \
    -lcurl -lpthread -o myapp
```

**Windows (MinGW):**
```bash
gcc -std=c11 -O2 -Iinclude \
    src/openhab_client.c src/openhab_api.c main.c \
    -lcurl -lws2_32 -lcrypt32 -lbcrypt -o myapp.exe
```

**Windows (MSVC):**
```cmd
cl /std:c11 /O2 /I"include" ^
    src\openhab_client.c src\openhab_api.c main.c ^
    /link libcurl.lib ws2_32.lib /out:myapp.exe
```

---

### Option 5: Link against pre-built library

**Linux (static):**
```bash
gcc -std=c11 main.c \
    -I/usr/local/include \
    /usr/local/lib/libopenhab_rest_client.a \
    -lcurl -lpthread -o myapp
```

**Linux (shared):**
```bash
gcc -std=c11 main.c \
    -I/usr/local/include \
    -L/usr/local/lib -lopenhab_rest_client \
    -Wl,-rpath,/usr/local/lib -lcurl -o myapp
```

**Windows DLL:**
```cmd
cl /std:c11 main.c /I"include" /link openhab_rest_client.lib libcurl.lib /out:myapp.exe
```
Copy `openhab_rest_client.dll` next to the executable.

---

## Static library macro (`OPENHAB_STATIC`)

When linking against the **static** library, define `OPENHAB_STATIC` to suppress `__declspec(dllimport)` on Windows:

```c
#define OPENHAB_STATIC
#include <openhab/openhab.h>
```

With CMake `add_subdirectory` or `FetchContent` this is handled automatically — `openhab_rest_client_static` sets `OPENHAB_STATIC` as a public compile definition.

---

## Include

Single convenience header:

```c
#include <openhab/openhab.h>
```

Or individual headers:

```c
#include <openhab/openhab_client.h>   /* client, SSE, low-level HTTP */
#include <openhab/openhab_api.h>      /* all openhab_<class>_<method> functions */
```

---

## Memory Management

**Every API function that returns `char*` returns a heap-allocated string that the caller must `free()`.**

```c
char* result = openhab_items_getItems(c, NULL, NULL, NULL, 0, NULL, 0, NULL);
if (result) {
    printf("%s\n", result);
    free(result);   /* always free! */
}
```

Functions returning `void` (all SSE functions) allocate nothing — no `free()` needed.

---

## Usage

### Authentication

```c
#include <openhab/openhab.h>

/* Basic Authentication */
openhab_client_t* c = openhab_client_create(
    "http://127.0.0.1:8080", "openhab", "habopen", NULL);

/* Token Authentication */
openhab_client_t* c = openhab_client_create(
    "http://127.0.0.1:8080", NULL, NULL, "oh.openhab.xxxx");

/* myopenhab.org Cloud */
openhab_client_t* c = openhab_client_create(
    "https://myopenhab.org", "your@email.com", "yourpassword", NULL);
```

Check connectivity after creation:

```c
if (!c || !openhab_client_is_logged_in(c)) {
    fprintf(stderr, "Connection failed: %s\n",
            c ? openhab_last_error(c) : "allocation error");
    openhab_client_destroy(c);
    return 1;
}
```

Always destroy the client when done:

```c
openhab_client_destroy(c);
```

### Sending Commands

```c
char* r = openhab_items_sendCommand(c, "MyLightSwitch", "ON");
if (r) { printf("%s\n", r); free(r); }
else   { fprintf(stderr, "Error %d: %s\n",
                 openhab_last_status(c), openhab_last_error(c)); }
```

### Reading JSON Responses

Responses are raw JSON strings. Parse with any C JSON library:

```c
#include <cjson/cJSON.h>

char* json_str = openhab_items_getItem(c, "MyLightSwitch", NULL, 1, NULL);
if (json_str) {
    cJSON* obj = cJSON_Parse(json_str);
    if (obj) {
        cJSON* state = cJSON_GetObjectItemCaseSensitive(obj, "state");
        if (cJSON_IsString(state))
            printf("State: %s\n", state->valuestring);
        cJSON_Delete(obj);
    }
    free(json_str);
}
```

### Server-Sent Events (SSE)

The callback receives each `data:` payload. Return `1` to continue, `0` to stop:

```c
static int on_event(const char* data, void* userdata) {
    printf("Event: %s\n", data);
    int* count = (int*)userdata;
    return ++(*count) < 5;   /* stop after 5 events */
}

int count = 0;
openhab_events_getItemStateChangedEvent(c, "*", on_event, &count);
```

### Error Handling

```c
char* result = openhab_items_getItem(c, "NonExistent", NULL, 1, NULL);
if (!result) {
    fprintf(stderr, "HTTP %d: %s\n",
            openhab_last_status(c), openhab_last_error(c));
}
```

### Running the Test Application

Edit `URL`, `USERNAME`, `PASSWORD` at the top of `test/test.c`, then:

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
./openhab_test
```

---

## Full List of Functions

All API functions follow the naming convention:
```
openhab_<class>_<methodName>(openhab_client_t* c, ...)
```

**Return value:** `char*` — heap-allocated JSON string. Caller must `free()`. Returns `NULL` on error.

**Exceptions:** SSE functions return `void` and use a callback.

Optional string parameters should be passed as `NULL`. Boolean parameters use `int` (`0` = false, `1` = true).

---

### Client

```c
openhab_client_t* openhab_client_create(const char* url,
    const char* username, const char* password, const char* token);
void        openhab_client_destroy(openhab_client_t* client);
int         openhab_client_is_logged_in(const openhab_client_t* client);
int         openhab_client_is_cloud(const openhab_client_t* client);
const char* openhab_client_base_url(const openhab_client_t* client);
const char* openhab_last_error(const openhab_client_t* client);
int         openhab_last_status(const openhab_client_t* client);
```

The strings returned by `openhab_client_base_url()` and `openhab_last_error()` are owned by the client — do **not** `free()` them.

---

### Low-level HTTP

```c
char* openhab_get(openhab_client_t* c, const char* endpoint,
                  const char* accept, const char* query);
char* openhab_post(openhab_client_t* c, const char* endpoint,
                   const char* body, const char* content_type);
char* openhab_put(openhab_client_t* c, const char* endpoint,
                  const char* body, const char* content_type);
char* openhab_delete(openhab_client_t* c, const char* endpoint);
```

Use these directly only for custom endpoints not covered by the API layer.

---

### SSE

```c
typedef int (*openhab_sse_callback_t)(const char* data, void* userdata);

void openhab_sse_listen(openhab_client_t* client, const char* url,
                        openhab_sse_callback_t callback, void* userdata);
```

---

### UUID

```c
char* openhab_uuid_getUUID(openhab_client_t* c);
```

---

### Systeminfo

```c
char* openhab_systeminfo_getSystemInfo(openhab_client_t* c);
char* openhab_systeminfo_getUoMInfo(openhab_client_t* c);
```

---

### Items

```c
char* openhab_items_getItems(openhab_client_t* c,
    const char* type, const char* tags, const char* metadata,
    int recursive, const char* fields, int static_only, const char* language);
char* openhab_items_addOrUpdateItems(openhab_client_t* c, const char* items_json);
char* openhab_items_getItem(openhab_client_t* c, const char* name,
    const char* metadata, int recursive, const char* language);
char* openhab_items_addOrUpdateItem(openhab_client_t* c, const char* name,
    const char* item_json, const char* language);
char* openhab_items_sendCommand(openhab_client_t* c, const char* name, const char* cmd);
char* openhab_items_postUpdate(openhab_client_t* c, const char* name, const char* state);
char* openhab_items_deleteItem(openhab_client_t* c, const char* name);
char* openhab_items_addGroupMember(openhab_client_t* c, const char* name, const char* member);
char* openhab_items_removeGroupMember(openhab_client_t* c, const char* name, const char* member);
char* openhab_items_addMetadata(openhab_client_t* c, const char* name, const char* ns, const char* json);
char* openhab_items_removeMetadata(openhab_client_t* c, const char* name, const char* ns);
char* openhab_items_getMetadataNamespaces(openhab_client_t* c, const char* name, const char* language);
char* openhab_items_getSemanticItem(openhab_client_t* c, const char* name,
    const char* sem_class, const char* language);
char* openhab_items_getItemState(openhab_client_t* c, const char* name);
char* openhab_items_updateItemState(openhab_client_t* c, const char* name,
    const char* state, const char* language);
char* openhab_items_addTag(openhab_client_t* c, const char* name, const char* tag);
char* openhab_items_removeTag(openhab_client_t* c, const char* name, const char* tag);
char* openhab_items_purgeOrphanedMetadata(openhab_client_t* c);
```

---

### Things

```c
char* openhab_things_getThings(openhab_client_t* c, int summary, int static_only, const char* language);
char* openhab_things_createThing(openhab_client_t* c, const char* json, const char* language);
char* openhab_things_getThing(openhab_client_t* c, const char* uid, const char* language);
char* openhab_things_updateThing(openhab_client_t* c, const char* uid, const char* json, const char* language);
char* openhab_things_deleteThing(openhab_client_t* c, const char* uid, int force, const char* language);
char* openhab_things_updateThingConfiguration(openhab_client_t* c, const char* uid, const char* json, const char* language);
char* openhab_things_getThingConfigStatus(openhab_client_t* c, const char* uid, const char* language);
char* openhab_things_setThingStatus(openhab_client_t* c, const char* uid, int enabled, const char* language);
char* openhab_things_getThingStatus(openhab_client_t* c, const char* uid, const char* language);
char* openhab_things_getThingFirmwareStatus(openhab_client_t* c, const char* uid, const char* language);
char* openhab_things_getThingFirmwares(openhab_client_t* c, const char* uid, const char* language);
char* openhab_things_updateThingFirmware(openhab_client_t* c, const char* uid, const char* version, const char* language);
```

Enable/disable a thing with `openhab_things_setThingStatus(c, uid, 1, NULL)` / `openhab_things_setThingStatus(c, uid, 0, NULL)`.

---

### Rules

```c
char* openhab_rules_getRules(openhab_client_t* c, const char* prefix, const char* tags, int summary, int static_only);
char* openhab_rules_createRule(openhab_client_t* c, const char* json);
char* openhab_rules_getRule(openhab_client_t* c, const char* uid);
char* openhab_rules_updateRule(openhab_client_t* c, const char* uid, const char* json);
char* openhab_rules_deleteRule(openhab_client_t* c, const char* uid);
char* openhab_rules_getActions(openhab_client_t* c, const char* uid);
char* openhab_rules_getConditions(openhab_client_t* c, const char* uid);
char* openhab_rules_getTriggers(openhab_client_t* c, const char* uid);
char* openhab_rules_getConfiguration(openhab_client_t* c, const char* uid);
char* openhab_rules_updateConfiguration(openhab_client_t* c, const char* uid, const char* json);
char* openhab_rules_setRuleState(openhab_client_t* c, const char* uid, int enable);
char* openhab_rules_runNow(openhab_client_t* c, const char* uid, const char* context_json);
```

---

### Actions

```c
char* openhab_actions_getActions(openhab_client_t* c);
char* openhab_actions_getThingActions(openhab_client_t* c, const char* thing_uid);
char* openhab_actions_executeThingAction(openhab_client_t* c,
    const char* thing_uid, const char* action_uid, const char* input_json);
```

---

### Addons

```c
char* openhab_addons_getAddons(openhab_client_t* c, const char* service_id, const char* language);
char* openhab_addons_getAddon(openhab_client_t* c, const char* id, const char* service_id, const char* language);
char* openhab_addons_installAddon(openhab_client_t* c, const char* id, const char* service_id);
char* openhab_addons_uninstallAddon(openhab_client_t* c, const char* id, const char* service_id);
char* openhab_addons_getAddonTypes(openhab_client_t* c, const char* language);
char* openhab_addons_getAddonSuggestions(openhab_client_t* c, const char* language);
char* openhab_addons_getAddonServices(openhab_client_t* c, const char* language);
```

---

### Audio

```c
char* openhab_audio_getDefaultSink(openhab_client_t* c);
char* openhab_audio_getDefaultSource(openhab_client_t* c);
char* openhab_audio_getSinks(openhab_client_t* c);
char* openhab_audio_getSources(openhab_client_t* c);
```

---

### Auth

```c
char* openhab_auth_getAPITokens(openhab_client_t* c);
char* openhab_auth_createAPIToken(openhab_client_t* c, const char* name, const char* scope);
char* openhab_auth_deleteAPIToken(openhab_client_t* c, const char* name);
char* openhab_auth_getSessions(openhab_client_t* c);
char* openhab_auth_deleteSession(openhab_client_t* c, const char* session_id);
```

---

### ChannelTypes

```c
char* openhab_channel_types_getChannelTypes(openhab_client_t* c, const char* binding_id, const char* language);
char* openhab_channel_types_getChannelType(openhab_client_t* c, const char* uid, const char* language);
char* openhab_channel_types_getLinkableItemTypes(openhab_client_t* c, const char* uid);
```

---

### ConfigDescriptions

```c
char* openhab_config_descriptions_getConfigDescriptions(openhab_client_t* c, const char* scheme, const char* language);
char* openhab_config_descriptions_getConfigDescription(openhab_client_t* c, const char* uri, const char* language);
```

---

### Discovery

```c
char* openhab_discovery_getDiscoveryBindings(openhab_client_t* c);
char* openhab_discovery_startBindingScan(openhab_client_t* c, const char* binding_id);
```

---

### Events (SSE)

All event functions block until the callback returns `0` or the stream ends. They return `void`.

```c
void openhab_events_getEvents(openhab_client_t* c, const char* topics,
    openhab_sse_callback_t cb, void* userdata);

void openhab_events_getItemStateChangedEvent(openhab_client_t* c, const char* item_name,
    openhab_sse_callback_t cb, void* userdata);

void openhab_events_getItemCommandEvent(openhab_client_t* c, const char* item_name,
    openhab_sse_callback_t cb, void* userdata);

void openhab_events_getThingStatusEvent(openhab_client_t* c, const char* thing_uid,
    openhab_sse_callback_t cb, void* userdata);
```

Pass `"*"` for `item_name` or `thing_uid` to receive events for all items or things.

---

### Iconsets

```c
char* openhab_iconsets_getIconsets(openhab_client_t* c, const char* language);
```

---

### Inbox

```c
char* openhab_inbox_getDiscoveredThings(openhab_client_t* c);
char* openhab_inbox_approveDiscoveryResult(openhab_client_t* c, const char* uid,
    const char* label, const char* new_thing_id);
char* openhab_inbox_removeDiscoveryResult(openhab_client_t* c, const char* uid);
char* openhab_inbox_ignoreDiscoveryResult(openhab_client_t* c, const char* uid);
char* openhab_inbox_unignoreDiscoveryResult(openhab_client_t* c, const char* uid);
```

---

### Links

```c
char* openhab_links_getLinks(openhab_client_t* c, const char* item_name, const char* channel_uid);
char* openhab_links_getLink(openhab_client_t* c, const char* item_name, const char* channel_uid);
char* openhab_links_linkItemToChannel(openhab_client_t* c, const char* item_name,
    const char* channel_uid, const char* json);
char* openhab_links_unlinkItemFromChannel(openhab_client_t* c, const char* item_name, const char* channel_uid);
char* openhab_links_getOrphanLinks(openhab_client_t* c);
char* openhab_links_purgeUnusedLinks(openhab_client_t* c);
```

---

### Logging

```c
char* openhab_logging_getLoggers(openhab_client_t* c);
char* openhab_logging_getLogger(openhab_client_t* c, const char* name);
char* openhab_logging_modifyOrAddLogger(openhab_client_t* c, const char* name, const char* level);
char* openhab_logging_removeLogger(openhab_client_t* c, const char* name);
```

---

### ModuleTypes

```c
char* openhab_module_types_getModuleTypes(openhab_client_t* c, const char* type, const char* language);
char* openhab_module_types_getModuleType(openhab_client_t* c, const char* uid, const char* language);
```

---

### Persistence

```c
char* openhab_persistence_getServices(openhab_client_t* c);
char* openhab_persistence_getItemsFromService(openhab_client_t* c, const char* service_id);
char* openhab_persistence_getItemPersistenceData(openhab_client_t* c,
    const char* name, const char* service_id,
    const char* start_time, const char* end_time,
    int page, int page_length, int boundary);
char* openhab_persistence_storeItemPersistenceData(openhab_client_t* c,
    const char* name, const char* time, const char* state, const char* service_id);
char* openhab_persistence_deleteItemPersistenceData(openhab_client_t* c,
    const char* name, const char* start_time, const char* end_time, const char* service_id);
```

---

### ProfileTypes

```c
char* openhab_profile_types_getProfileTypes(openhab_client_t* c,
    const char* channel_type_uid, const char* item_type, const char* language);
```

---

### Services

```c
char* openhab_services_getServices(openhab_client_t* c, const char* language);
char* openhab_services_getService(openhab_client_t* c, const char* id, const char* language);
char* openhab_services_getServiceConfig(openhab_client_t* c, const char* id);
char* openhab_services_updateServiceConfig(openhab_client_t* c, const char* id, const char* json);
char* openhab_services_deleteServiceConfig(openhab_client_t* c, const char* id);
```

---

### Sitemaps

```c
char* openhab_sitemaps_getSitemaps(openhab_client_t* c);
char* openhab_sitemaps_getSitemap(openhab_client_t* c, const char* name,
    const char* type, int jsonsupport, const char* language);
char* openhab_sitemaps_getSitemapPage(openhab_client_t* c, const char* name,
    const char* page_id, const char* subscription_id, int include_hidden, const char* language);
char* openhab_sitemaps_createSubscription(openhab_client_t* c);
```

---

### Tags

```c
char* openhab_tags_getTags(openhab_client_t* c, const char* language, const char* type);
char* openhab_tags_getTag(openhab_client_t* c, const char* id, const char* language);
char* openhab_tags_createTag(openhab_client_t* c, const char* json);
char* openhab_tags_updateTag(openhab_client_t* c, const char* id, const char* json);
char* openhab_tags_deleteTag(openhab_client_t* c, const char* id);
```

---

### Templates

```c
char* openhab_templates_getTemplates(openhab_client_t* c, const char* language);
char* openhab_templates_getTemplate(openhab_client_t* c, const char* uid, const char* language);
```

---

### ThingTypes

```c
char* openhab_thing_types_getThingTypes(openhab_client_t* c, const char* binding_id, const char* language);
char* openhab_thing_types_getThingType(openhab_client_t* c, const char* uid, const char* language);
```

---

### Transformations

```c
char* openhab_transformations_getTransformations(openhab_client_t* c);
char* openhab_transformations_getTransformation(openhab_client_t* c, const char* uid);
char* openhab_transformations_updateTransformation(openhab_client_t* c, const char* uid, const char* json);
char* openhab_transformations_deleteTransformation(openhab_client_t* c, const char* uid);
char* openhab_transformations_getTransformationServices(openhab_client_t* c);
```

---

### UI

```c
char* openhab_ui_getUITiles(openhab_client_t* c);
char* openhab_ui_getUITile(openhab_client_t* c, const char* id);
char* openhab_ui_addUITile(openhab_client_t* c, const char* id, const char* json);
char* openhab_ui_removeUITile(openhab_client_t* c, const char* id);
char* openhab_ui_getUIComponents(openhab_client_t* c, const char* ns);
char* openhab_ui_getUIComponent(openhab_client_t* c, const char* ns, const char* uid);
char* openhab_ui_addUIComponent(openhab_client_t* c, const char* ns, const char* json);
char* openhab_ui_updateUIComponent(openhab_client_t* c, const char* ns, const char* uid, const char* json);
char* openhab_ui_removeUIComponent(openhab_client_t* c, const char* ns, const char* uid);
```

---

### Voice

```c
char* openhab_voice_getVoices(openhab_client_t* c);
char* openhab_voice_getDefaultVoice(openhab_client_t* c);
char* openhab_voice_sayText(openhab_client_t* c,
    const char* text, const char* voice_id, const char* sink_id, int volume);
char* openhab_voice_getInterpreters(openhab_client_t* c, const char* language);
char* openhab_voice_getInterpreter(openhab_client_t* c, const char* id, const char* language);
char* openhab_voice_interpret(openhab_client_t* c,
    const char* text, const char* hli_ids, const char* language);
```

**Examples:**

```c
char* r = openhab_voice_sayText(c,
    "Hello from openHAB!", "voicerss:en-us", "javasound:sink:default", 80);
if (r) free(r);

char* r2 = openhab_voice_interpret(c, "turn on the lights", NULL, NULL);
if (r2) free(r2);
```

---

## C vs. Python — Key Differences

| Topic | C | Python |
|---|---|---|
| Distribution | Source + CMake build | PyPI (`pip install`) |
| Dependency | libcurl only | `requests`, `aiohttp` |
| Include | `#include <openhab/openhab.h>` | `from openhab import Items` |
| Function naming | `openhab_items_sendCommand(c, name, cmd)` | `items.sendCommand(name, cmd)` |
| Memory | Caller must `free()` every returned `char*` | GC-managed |
| Return type | `char*` (raw JSON string) | `dict`, `list`, or `str` |
| JSON parsing | External library (cJSON, jansson, jsmn…) | Built-in `json` module |
| Error handling | Check for `NULL` + `openhab_last_error()` | `try/except requests.exceptions.*` |
| SSE | Function pointer callback + `userdata` | `response.iter_lines()` |
| Async | Use `pthread` externally for SSE | `AsyncOpenHABClient` + `aiohttp` |
| Boolean | `int` (`0`/`1`) | `bool` (`True`/`False`) |
| Optional params | `NULL` | `None` or default value |
| Static library | Define `OPENHAB_STATIC` macro | n/a |
| Platform libs | Windows: `ws2_32`, `crypt32`; macOS: `Security`, `CoreFoundation` | n/a |
| C++ compatible | `extern "C"` guards in all headers | n/a |
| Language standard | C11 | Python 3.x |

---

## Contributing

Contributions are welcome! Please create an issue or pull request to suggest changes.

### How to contribute:
1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add your feature description"
   ```
4. Push to the branch:
   ```bash
   git push origin feature/your-feature-name
   ```
5. Open a pull request.

Please ensure code compiles with C11 under GCC, Clang, and MSVC, every returned `char*` is heap-allocated and documented for the caller to `free()`, and function names follow the `openhab_<class>_<methodName>` convention.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
