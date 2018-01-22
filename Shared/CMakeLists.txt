cmake_minimum_required(VERSION 2.6)

project(daemon_shared_lib)

set(CMAKE_CXX_STANDARD 14)

include(FindOpenSSL)
find_package(OpenSSL REQUIRED)

include(FindProtobuf)
find_package(Protobuf REQUIRED)

include(FindZeroMQ)
find_package(ZeroMQ REQUIRED)

include(FindJWTCPP)
find_package(JWTCPP REQUIRED)

file(GLOB PROTO_SRC "Proto/ProtoCompiled/*.pb.cc")
file(GLOB PROTO_HEADER "Proto/ProtoCompiled/*.pb.h")

set(DEAMON_SHARED_SOURCE_FILES
        Sources/FocusDaemon.cpp
        Sources/FocusEventManager.cpp
        Sources/FocusEventEmitter.cpp
        Sources/FocusNetworkManager.cpp
        Sources/FocusKeyLogger.cpp
        Sources/FocusSerializer.cpp
        Sources/FocusAuthenticator.cpp
        Sources/FocusSocket.cpp

        Headers/FocusDaemon.hpp
        Headers/FocusEventManager.hpp
        Headers/FocusEventEmitter.hpp
        Headers/FocusEventListener.hpp
        Headers/FocusNetworkManager.hpp
        Headers/FocusKeyLogger.hpp
        Headers/FocusSerializer.hpp
        Headers/FocusAuthenticator.hpp
        Headers/FocusSocket.hpp
        Headers/FocusSecureSocket.hpp

        Interfaces/IContextAgent.hpp
        Interfaces/IFocusSocket.hpp)

include_directories(Headers Interfaces ../Library ${PROTOBUF_INCLUDE_DIR} Proto/ProtoCompiled ${OPENSSL_INCLUDE_DIR} ${ZeroMQ_INCLUDE_DIR} ${JWTCPP_INCLUDE_DIRS})

IF (MSVC)
    include_directories(../Windows/Headers)
ELSEIF (APPLE)
    include_directories(../MacOs/Headers)
ELSEIF (UNIX)
    include_directories(../Linux/Headers)
ENDIF ()

add_library(daemon_shared_lib STATIC ${DEAMON_SHARED_SOURCE_FILES} ${PROTO_SRC} ${PROTO_HEADER})

target_link_libraries(daemon_shared_lib pthread ${ZeroMQ_LIBRARIES} ${PROTOBUF_LIBRARY} ${JWTCPP_LIBRARIES} ${OPENSSL_LIBRARIES})

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF (MSVC)
    add_test(NAME daemon_shared_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_shared_tests.exe)
ELSE ()
    add_test(NAME daemon_shared_tests COMMAND daemon_shared_tests)
ENDIF ()