cmake_minimum_required(VERSION 2.6)

project(daemon)

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
elseif(APPLE)
    add_definitions(-DAPPLE)
endif()

### Adding GoogleTest for unit testing and enable testing for ctest command.
enable_testing()
add_subdirectory(UnitTests)

### Linking NanoMsg library
#add_definitions(-DNN_STATIC_LIB=ON)
add_subdirectory(nanomsg)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/nanomsg/include)

### Subdirectory
add_subdirectory(Shared)
if(MSVC)
    add_subdirectory(Windows)
else()
    add_subdirectory(Unix)
endif()