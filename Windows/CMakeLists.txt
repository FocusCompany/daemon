cmake_minimum_required(VERSION 2.6)

project(daemon_windows)

set(CMAKE_CXX_STANDARD 11)

set(DEAMON_WINDOWS_SOURCE_FILES
        Sources/FocusDaemon.cpp
        Sources/FocusEventManager.cpp
		Sources/FocusKeyLogger.cpp
		Sources/FocusNetworkManager.cpp
		Sources/WindowsContextAgent.cpp
        )

set(MAIN_FILES
        main.cpp
        )

include_directories(Headers Interfaces ../Shared/Interfaces)

add_library(daemon_windows_lib STATIC ${DEAMON_WINDOWS_SOURCE_FILES})

add_executable(daemon_windows ${MAIN_FILES})

target_link_libraries(daemon_windows daemon_windows_lib nanomsg Psapi)

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF (MSVC)
    add_test(NAME daemon_windows_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_windows_tests.exe)
ELSE ()
    add_test(NAME daemon_windows_tests COMMAND daemon_windows_tests)
ENDIF ()