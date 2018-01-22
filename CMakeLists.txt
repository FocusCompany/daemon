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
	set(CMAKE_INCLUDE_PATH "C:/Program Files/protobuf/include;C:/Program Files/jwt-cpp/include")
	set(CMAKE_LIBRARY_PATH "C:/Program Files/protobuf/lib;C:/Program Files/jwt-cpp/lib")
elseif(APPLE)
    add_definitions(-DAPPLE)
    set(CMAKE_INCLUDE_PATH "/usr/local/opt/openssl@1.1/include")
    set(CMAKE_LIBRARY_PATH "/usr/local/opt/openssl@1.1/lib")
elseif(UNIX)
    add_definitions(-DUNIX)
endif()

link_directories(${CMAKE_LIBRARY_PATH})

### Adding GoogleTest for unit testing and enable testing for ctest command.
enable_testing()
add_subdirectory(UnitTests)

### Subdirectory
add_subdirectory(Shared)
if(MSVC)
    add_subdirectory(Windows)
elseif(APPLE)
    add_subdirectory(MacOs)
elseif(UNIX)
    add_subdirectory(Linux)
endif()