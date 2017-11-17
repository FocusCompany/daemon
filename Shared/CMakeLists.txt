cmake_minimum_required(VERSION 2.6)

project(daemon_shared_lib)

set(CMAKE_CXX_STANDARD 11)

set(DEAMON_SHARED_SOURCE_FILES
        Sources/FocusDaemon.cpp
        Sources/FocusEventManager.cpp
        Sources/FocusEventEmitter.cpp
        Sources/FocusEventListener.cpp
		Sources/FocusNetworkManager.cpp
		Sources/FocusKeyLogger.cpp
        )

include_directories(Headers Interfaces)

IF(MSVC)
	include_directories(../Windows/Headers)
ELSE()
	include_directories(../Unix/Headers)
ENDIF()

add_library(daemon_shared_lib STATIC ${DEAMON_SHARED_SOURCE_FILES})

target_link_libraries(daemon_shared_lib nanomsg)

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF(MSVC)
    add_test(NAME daemon_shared_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_shared_tests.exe)
ELSE()
    add_test(NAME daemon_shared_tests COMMAND daemon_shared_tests)
ENDIF()