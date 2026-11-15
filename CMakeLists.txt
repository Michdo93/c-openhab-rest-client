cmake_minimum_required(VERSION 3.16)
project(OpenHABRestClient VERSION 2.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

option(OPENHAB_BUILD_TESTS "Build the tests" ON)

# ── libcurl ───────────────────────────────────────────────────────────────────
find_package(CURL REQUIRED)

# ── cJSON: installed package (apt libcjson-dev, vcpkg cjson, brew cjson) or download ──
find_package(cJSON CONFIG QUIET)
set(OPENHAB_CJSON_SOURCES "")
if(cJSON_FOUND)
  if(TARGET cjson)
    set(OPENHAB_CJSON_LIB cjson)
  else()
    set(OPENHAB_CJSON_LIB ${CJSON_LIBRARIES})
  endif()
  get_filename_component(OPENHAB_CJSON_INC "${CJSON_INCLUDE_DIRS}" DIRECTORY)
  message(STATUS "cJSON: installed (${CJSON_INCLUDE_DIRS})")
else()
  include(FetchContent)
  FetchContent_Declare(cjson_src
    GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
    GIT_TAG acc76239bee01d8e9c858ae2cab296704e52d916   # v1.7.18
    GIT_SHALLOW FALSE)
  FetchContent_GetProperties(cjson_src)
  if(NOT cjson_src_POPULATED)
    FetchContent_Populate(cjson_src)
  endif()
  # <cjson/cJSON.h> like the packages of the distributions
  file(COPY ${cjson_src_SOURCE_DIR}/cJSON.h DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/cjson-include/cjson)
  set(OPENHAB_CJSON_INC ${CMAKE_CURRENT_BINARY_DIR}/cjson-include)
  set(OPENHAB_CJSON_SOURCES ${cjson_src_SOURCE_DIR}/cJSON.c)
  set(OPENHAB_CJSON_LIB "")
  message(STATUS "cJSON: built from source (v1.7.18)")
endif()

# ── Sources ───────────────────────────────────────────────────────────────────
file(GLOB OPENHAB_API_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/api/*.c)
set(LIB_SOURCES
  src/openhab_client.c
  src/openhab_sse.c
  src/py_rt.c
  ${OPENHAB_API_SOURCES}
  ${OPENHAB_CJSON_SOURCES})

set(PLATFORM_LIBS "")
if(WIN32)
  list(APPEND PLATFORM_LIBS ws2_32)
else()
  find_package(Threads REQUIRED)
  list(APPEND PLATFORM_LIBS Threads::Threads m)
endif()

function(openhab_setup target)
  target_include_directories(${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${OPENHAB_CJSON_INC}>
    $<INSTALL_INTERFACE:include>)
  target_link_libraries(${target} PUBLIC CURL::libcurl ${OPENHAB_CJSON_LIB} ${PLATFORM_LIBS})
  if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wno-unused-parameter)
  endif()
endfunction()

# ── Shared and static library ────────────────────────────────────────────────
add_library(openhab_rest_client SHARED ${LIB_SOURCES})
openhab_setup(openhab_rest_client)
target_compile_definitions(openhab_rest_client PRIVATE OPENHAB_BUILDING_DLL)
set_target_properties(openhab_rest_client PROPERTIES
  VERSION ${PROJECT_VERSION} SOVERSION 2 C_VISIBILITY_PRESET hidden)
if(WIN32)
  set_target_properties(openhab_rest_client PROPERTIES PREFIX "")
endif()

add_library(openhab_rest_client_static STATIC ${LIB_SOURCES})
openhab_setup(openhab_rest_client_static)
target_compile_definitions(openhab_rest_client_static PUBLIC OPENHAB_STATIC)
if(NOT WIN32)
  set_target_properties(openhab_rest_client_static PROPERTIES OUTPUT_NAME openhab_rest_client)
endif()
set_target_properties(openhab_rest_client_static PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(openhab::rest_client ALIAS openhab_rest_client_static)
add_library(openhab::rest_client_shared ALIAS openhab_rest_client)

# ── Tests ─────────────────────────────────────────────────────────────────────
if(OPENHAB_BUILD_TESTS AND NOT CMAKE_CROSSCOMPILING)
  enable_testing()
  add_executable(openhab_unit_test test/unit_test.c)
  target_link_libraries(openhab_unit_test PRIVATE openhab_rest_client_static)
  add_test(NAME unit COMMAND openhab_unit_test)
  add_executable(openhab_integration_test test/integration_test.c)
  target_link_libraries(openhab_integration_test PRIVATE openhab_rest_client_static)
  add_test(NAME integration COMMAND openhab_integration_test)
  set_tests_properties(integration PROPERTIES SKIP_RETURN_CODE 77)
  # the headers must stay usable from C++ (C++20 for named arguments)
  include(CheckLanguage)
  check_language(CXX)
  if(CMAKE_CXX_COMPILER)
    enable_language(CXX)
    add_executable(openhab_cpp_test test/cpp_test.cpp)
    set_target_properties(openhab_cpp_test PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
    target_link_libraries(openhab_cpp_test PRIVATE openhab_rest_client_static)
    add_test(NAME cpp COMMAND openhab_cpp_test)
  endif()
endif()

# ── Install (find_package(OpenHABRestClient) and pkg-config) ─────────────────
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
install(TARGETS openhab_rest_client openhab_rest_client_static
  EXPORT OpenHABRestClientTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
if(OPENHAB_CJSON_SOURCES)
  install(DIRECTORY ${OPENHAB_CJSON_INC}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()
install(EXPORT OpenHABRestClientTargets NAMESPACE openhab::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OpenHABRestClient)
if(OPENHAB_CJSON_SOURCES)
  set(OPENHAB_CJSON_DEP "")
else()
  set(OPENHAB_CJSON_DEP "find_dependency(cJSON CONFIG)")
endif()
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientConfig.cmake
"include(CMakeFindDependencyMacro)
find_dependency(CURL)
${OPENHAB_CJSON_DEP}
if(NOT WIN32)
  find_dependency(Threads)
endif()
include(\${CMAKE_CURRENT_LIST_DIR}/OpenHABRestClientTargets.cmake)
")
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientConfigVersion.cmake
  COMPATIBILITY SameMajorVersion)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/OpenHABRestClientConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OpenHABRestClient)
configure_file(cmake/openhab_rest_client.pc.in openhab_rest_client.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/openhab_rest_client.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

message(STATUS "c-openhab-rest-client ${PROJECT_VERSION}")
