cmake_minimum_required(VERSION 2.6)

project(daemon_mac)

set(CMAKE_CXX_STANDARD 14)

include(FindProtobuf)
find_package(Protobuf REQUIRED)

find_library(CARBON_LIBRARY Carbon)

set(DEAMON_MAC_SOURCE_FILES
        Sources/ContextAgent.cpp
        Sources/AfkListener.cpp

        Headers/ContextAgent.hpp
        Headers/AfkListener.hpp
        )

set(MAIN_FILES
        main.cpp
        )

include_directories(Headers ../Shared/Interfaces ../Shared/Headers ../Library ../Shared/Proto/ProtoCompiled ${PROTOBUF_INCLUDE_DIR})

add_library(daemon_mac_lib STATIC ${DEAMON_MAC_SOURCE_FILES})

add_executable(daemon_mac MACOSX_BUNDLE ${MAIN_FILES})
set_target_properties(daemon_mac PROPERTIES OUTPUT_NAME "focus-daemon")

target_link_libraries(daemon_mac daemon_mac_lib daemon_shared_lib ${PROTOBUF_LIBRARY} ${CARBON_LIBRARY})

add_custom_command(TARGET daemon_mac POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/MacOs/printAppTitle.scpt" "$<TARGET_FILE_DIR:daemon_mac>")

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF (MSVC)
    add_test(NAME daemon_mac_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_mac_tests.exe)
ELSE ()
    add_test(NAME daemon_mac_tests COMMAND daemon_mac_tests)
ENDIF ()

####INSTALL####

install(TARGETS daemon_mac DESTINATION .)

####PACKAGE####

set(CPACK_GENERATOR "DragNDrop") # Setup package version

set (CPACK PACKAGE VERSION MAJOR 0)
set (CPACK PACKAGE VERSION MINOR 1)
set (CPACK PACKAGE VERSION PATCH 0)
include (CPack)
