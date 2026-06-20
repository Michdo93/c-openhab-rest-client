cmake_minimum_required(VERSION 3.16)
project(OpenHABRestClient VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# ── Platform detection ────────────────────────────────────────────────────────
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(OPENHAB_WINDOWS ON)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(OPENHAB_LINUX ON)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(OPENHAB_MACOS ON)
endif()

message(STATUS "System: ${CMAKE_SYSTEM_NAME} / ${CMAKE_SYSTEM_PROCESSOR}")

# ── libcurl ───────────────────────────────────────────────────────────────────
find_package(CURL QUIET)
if(NOT CURL_FOUND)
  find_library(CURL_LIBRARIES NAMES curl libcurl libcurl_static)
  find_path(CURL_INCLUDE_DIRS curl/curl.h
    PATHS /usr/include /usr/local/include
          /usr/x86_64-w64-mingw32/include
          /usr/aarch64-linux-gnu/include)
endif()
message(STATUS "curl: ${CURL_LIBRARIES}")

# ── Platform libs ─────────────────────────────────────────────────────────────
set(PLATFORM_LIBS "")
if(OPENHAB_WINDOWS)
  list(APPEND PLATFORM_LIBS ws2_32 crypt32 bcrypt)
  if(MINGW)
    list(APPEND PLATFORM_LIBS wldap32 normaliz)
  endif()
elseif(OPENHAB_LINUX)
  find_package(Threads REQUIRED)
  list(APPEND PLATFORM_LIBS Threads::Threads)
elseif(OPENHAB_MACOS)
  find_library(SEC Security)
  find_library(CF  CoreFoundation)
  list(APPEND PLATFORM_LIBS ${SEC} ${CF})
endif()

# ── Sources ───────────────────────────────────────────────────────────────────
set(LIB_SOURCES
  src/openhab_client.c
  src/openhab_api.c
)

# ── Shared library ────────────────────────────────────────────────────────────
add_library(openhab_rest_client SHARED ${LIB_SOURCES})
target_include_directories(openhab_rest_client PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE ${CURL_INCLUDE_DIRS})
target_compile_definitions(openhab_rest_client PRIVATE OPENHAB_BUILDING_DLL)
if(OPENHAB_WINDOWS)
  set_target_properties(openhab_rest_client PROPERTIES OUTPUT_NAME "openhab_rest_client" PREFIX "")
endif()
target_link_libraries(openhab_rest_client PRIVATE ${CURL_LIBRARIES} ${PLATFORM_LIBS})
set_target_properties(openhab_rest_client PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1)

# ── Static library ────────────────────────────────────────────────────────────
add_library(openhab_rest_client_static STATIC ${LIB_SOURCES})
set_target_properties(openhab_rest_client_static PROPERTIES OUTPUT_NAME openhab_rest_client)
target_include_directories(openhab_rest_client_static PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE ${CURL_INCLUDE_DIRS})
target_compile_definitions(openhab_rest_client_static PUBLIC OPENHAB_STATIC)
target_link_libraries(openhab_rest_client_static PRIVATE ${CURL_LIBRARIES} ${PLATFORM_LIBS})

# ── Test executable ───────────────────────────────────────────────────────────
add_executable(openhab_test test/test.c)
target_link_libraries(openhab_test PRIVATE
  openhab_rest_client_static ${CURL_LIBRARIES} ${PLATFORM_LIBS})
if(OPENHAB_WINDOWS AND MINGW)
  target_link_options(openhab_test PRIVATE -static-libgcc -static)
endif()

# ── Install ───────────────────────────────────────────────────────────────────
include(GNUInstallDirs)
install(TARGETS openhab_rest_client openhab_rest_client_static
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

message(STATUS "──────────────────────────────────────────────────────────")
message(STATUS " c-openhab-rest-client ${PROJECT_VERSION}")
message(STATUS " CURL: ${CURL_LIBRARIES}")
message(STATUS "──────────────────────────────────────────────────────────")
