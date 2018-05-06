cmake_minimum_required(VERSION 3.8)

project(daemon)
include(cmake/git.cmake)
include(cmake/ucm.cmake)
include(cmake/dependency.cmake)

### Set global build version
get_git_last_commit_infos(GIT_SHA1 GIT_SHA1_ABBR GIT_DATE_YEAR GIT_DATE_MONTH GIT_DATE_DAY GIT_DESC)
set(VERSION "${GIT_DATE_YEAR}-${GIT_DATE_MONTH}-${GIT_DATE_DAY}-${GIT_SHA1_ABBR}")
message("Current version of Focus is: ${VERSION}")
add_definitions(-DFOCUS_VERSION="${VERSION}" -DFOCUS_GIT_HASH="${GIT_SHA1_ABBR}" -DFOCUS_GIT_DATE="${GIT_DATE}")

### Set Focus build options
option(ENABLE_TESTING "Build tests" OFF)

### Output everything inside of a BUILD directory to avoid issue with library linking.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/BUILD)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/BUILD)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/BUILD)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/BUILD)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/BUILD)

### Add useful cmake macros that help with compiler/linker flags especially in VS2017
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
ucm_set_runtime(STATIC)

### Turn on the ability to create folders to organize projects under VS2017
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

### Define some useful pre-processor variables
if(MSVC)
    add_definitions(-DMSVC)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
elseif(APPLE)
    add_definitions(-DAPPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl@1.1")
elseif(UNIX)
    add_definitions(-DUNIX)
endif()

### Adding CXX FLAGS
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(WARNING "The current build type is ${CMAKE_BUILD_TYPE}, optimizations are disabled")
endif()

set(CMAKE_CXX_STANDARD 14)
string(APPEND COMPILE_FLAGS
        "$<IF:$<CXX_COMPILER_ID:MSVC>,"
            "/W4;$<$<CONFIG:RELEASE>:/O2;>,"
            "-Wall;-Wextra;-Werror;-pedantic;-Wuninitialized;-Winit-self;-Weffc++;"
                "$<$<CONFIG:RELEASE>:-O3;>"
                "$<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++;>"
        ">"
)

### Include directories
include_directories(${CMAKE_INCLUDE_PATH})
include_directories(Library)

### Compiling protobuf envelops
include(FindProtobuf)
find_package(Protobuf REQUIRED)
if (NOT EXISTS ${CMAKE_SOURCE_DIR}/Shared/Proto/ProtoCompiled)
    execute_process(COMMAND git submodule update --init --recursive WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif ()
if(MSVC)
    execute_process(COMMAND generate.bat ${PROTOBUF_PROTOC_EXECUTABLE} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Shared/Proto)
else()
    execute_process(COMMAND ./generate.sh WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Shared/Proto)
endif()

### Setting global CMake variables
set(PROJECT_VERSION_MAJOR  ${GIT_DATE_YEAR})
set(PROJECT_VERSION_MINOR  ${GIT_DATE_MONTH})
set(PROJECT_VERSION_PATCH  ${GIT_DATE_DAY})
set(PROJECT_DESCRIPTION "Focus does stuff... We don't know exactly what.")
set(PROJECT_NAME "Focus")

### Setting global CPack variables
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_NAME Focus)
set(CPACK_PACKAGE_VENDOR "Focus inc.")
set(CPACK_PACKAGE_CONTACT "focus@epitechfr.onmicrosoft.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Focus does stuff... We don't know exactly what.")
set(CPACK_PACKAGE_VERSION_MAJOR ${GIT_DATE_YEAR})
set(CPACK_PACKAGE_VERSION_MINOR ${GIT_DATE_MONTH})
set(CPACK_PACKAGE_VERSION_PATCH ${GIT_DATE_DAY})

### Subdirectory

if (ENABLE_TESTING)
    message("Building tests using Google Tests")
    enable_testing()
    add_subdirectory(UnitTests)
endif()

add_subdirectory(Shared)

if(MSVC)
    add_subdirectory(Windows)
elseif(APPLE)
    add_subdirectory(MacOs)
elseif(UNIX)
    add_subdirectory(Linux)
endif()
