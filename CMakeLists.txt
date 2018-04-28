cmake_minimum_required(VERSION 2.6)

project(daemon)

### Set Cmake to compile with CPP 14
set (CMAKE_CXX_STANDARD 14)

### Output everything inside of a BUILD directory to avoir issue with library linking.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/BUILD)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/BUILD)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/BUILD)

### Add useful cmake macros that help with compiler/linker flags especially in VS2017
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include(cmake/ucm.cmake)
ucm_set_runtime(STATIC)

### Turn on the ability to create folders to organize projects under VS2017
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

### Define some useful pre-processor for cross-compatibility
if(MSVC)
    add_definitions(-DMSVC)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	set(OPENSSL_ROOT_DIR "C:/OpenSSL-Win32")
	set(ZeroMQ_ROOT_DIR "C:/Program Files/Focus/zmq")
	set(CMAKE_INCLUDE_PATH "C:/Program Files/Focus/protobuf/include;C:/Program Files/Focus/jwt-cpp/include;C:/Program Files/Focus/zmq/include")
	set(CMAKE_LIBRARY_PATH "C:/Program Files/Focus/protobuf/lib;C:/Program Files/Focus/jwt-cpp/lib;C:/Program Files/Focus/zmq/lib")
elseif(APPLE)
    add_definitions(-DAPPLE)
    set(CMAKE_INCLUDE_PATH "/usr/local/opt/openssl@1.1/include")
    set(CMAKE_LIBRARY_PATH "/usr/local/opt/openssl@1.1/lib")
elseif(UNIX)
    add_definitions(-DUNIX)
    add_definitions(-DWNCK_I_KNOW_THIS_IS_UNSTABLE)
endif()

### Adding GoogleTest for unit testing and enable testing for ctest command.
enable_testing()
add_subdirectory(UnitTests)

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
    execute_process(COMMAND generate.bat WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Shared/Proto)
else()
    execute_process(COMMAND ./generate.sh WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Shared/Proto)
endif()

### Subdirectory
add_subdirectory(Shared)

if(MSVC)
    add_subdirectory(Windows)
elseif(APPLE)
    add_subdirectory(MacOs)
elseif(UNIX)
    add_subdirectory(Linux)
endif()