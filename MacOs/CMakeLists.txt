cmake_minimum_required(VERSION 2.6)

project(daemon_mac)

set(CMAKE_CXX_STANDARD 14)

include(FindProtobuf)
find_package(Protobuf REQUIRED)

FIND_LIBRARY(CARBON_LIBRARY Carbon)
FIND_LIBRARY(COCOA_LIBRARY Cocoa)

set(DEAMON_MAC_SOURCE_FILES
        Sources/ContextAgent.cpp
        Sources/KeyListener.cpp
        Sources/MouseListener.cpp

        Headers/ContextAgent.hpp
        Headers/KeyListener.hpp
        Headers/MouseListener.hpp
        )

set(MAIN_FILES
        main.cpp
        )

include_directories(Headers ../Shared/Interfaces ../Shared/Headers ../Library ../Shared/Proto/ProtoCompiled ${PROTOBUF_INCLUDE_DIR})

add_library(daemon_mac_lib STATIC ${DEAMON_MAC_SOURCE_FILES})

add_executable(daemon_mac ${MAIN_FILES})

target_link_libraries(daemon_mac daemon_mac_lib daemon_shared_lib ${PROTOBUF_LIBRARY} ${CARBON_LIBRARY} ${COCOA_LIBRARY})

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF (MSVC)
    add_test(NAME daemon_mac_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_mac_tests.exe)
ELSE ()
    add_test(NAME daemon_mac_tests COMMAND daemon_mac_tests)
ENDIF ()