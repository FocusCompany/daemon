cmake_minimum_required(VERSION 2.6)

project(daemon_linux)

set(CMAKE_CXX_STANDARD 14)

include(FindProtobuf)
find_package(Protobuf REQUIRED)

set(DEAMON_LINUX_SOURCE_FILES
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

add_library(daemon_linux_lib STATIC ${DEAMON_LINUX_SOURCE_FILES})

add_executable(daemon_linux ${MAIN_FILES})

target_link_libraries(daemon_linux daemon_linux_lib daemon_shared_lib ${PROTOBUF_LIBRARY})

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF (MSVC)
    add_test(NAME daemon_linux_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_linux_tests.exe)
ELSE ()
    add_test(NAME daemon_linux_tests COMMAND daemon_linux_tests)
ENDIF ()