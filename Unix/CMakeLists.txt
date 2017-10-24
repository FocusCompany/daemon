cmake_minimum_required(VERSION 2.6)

project(daemon_unix)

set(CMAKE_CXX_STANDARD 11)

set(DEAMON_UNIX_SOURCE_FILES
        TestUnix.cpp
        TestUnix.hpp
        )

set(MAIN_FILES
        main.cpp
        )

add_library(daemon_unix_lib STATIC ${DEAMON_UNIX_SOURCE_FILES})

add_executable(daemon_unix ${MAIN_FILES})

target_link_libraries(daemon_unix daemon_unix_lib nanomsg)

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF (MSVC)
    add_test(NAME daemon_unix_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_unix_tests.exe)
ELSE ()
    add_test(NAME daemon_unix_tests COMMAND daemon_unix_tests)
ENDIF ()