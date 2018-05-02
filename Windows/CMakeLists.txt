cmake_minimum_required(VERSION 2.6)

project(daemon_windows)

set(CMAKE_CXX_STANDARD 14)

include(FindProtobuf)
find_package(Protobuf REQUIRED)

set(DEAMON_WINDOWS_SOURCE_FILES
        Sources/ContextAgent.cpp
        Sources/AfkListener.cpp

        Headers/ContextAgent.hpp
        Headers/AfkListener.hpp
        )

set(MAIN_FILES
        main.cpp
        )

include_directories(Headers ../Shared/Interfaces ../Shared/Headers ../Library ../Shared/Proto/ProtoCompiled ${PROTOBUF_INCLUDE_DIR})

add_library(daemon_windows_lib STATIC ${DEAMON_WINDOWS_SOURCE_FILES})

add_executable(daemon_windows ${MAIN_FILES})

target_link_libraries(daemon_windows daemon_windows_lib daemon_shared_lib Psapi ${PROTOBUF_LIBRARY})

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF (MSVC)
    add_test(NAME daemon_windows_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_windows_tests.exe)
ELSE ()
    add_test(NAME daemon_windows_tests COMMAND daemon_windows_tests)
ENDIF ()

####INSTALL####

install(TARGETS daemon_windows DESTINATION bin)