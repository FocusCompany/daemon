cmake_minimum_required(VERSION 2.6)

project(daemon_shared_lib)

set(CMAKE_CXX_STANDARD 14)

include(FindOpenSSL)
find_package(OpenSSL REQUIRED)

include(FindJWTCPP)
find_package(JWTCPP REQUIRED)

include(FindProtobuf)
find_package(Protobuf REQUIRED)

include(FindZeroMQ)
find_package(ZeroMQ REQUIRED)

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
        Sources/FocusConfiguration.cpp

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
        Headers/FocusConfiguration.hpp

        Interfaces/IContextAgent.hpp
        Interfaces/IAfkListener.hpp
        )

include_directories(Headers Interfaces ${OPENSSL_INCLUDE_DIR} ${JWTCPP_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIR} Proto/ProtoCompiled ${ZeroMQ_INCLUDE_DIR})

IF (MSVC)
    include_directories(../Windows/Headers)
ELSEIF (APPLE)
    include_directories(../MacOs/Headers)
ELSEIF (UNIX)
    include_directories(../Linux/Headers)
ENDIF ()

add_library(daemon_shared_lib STATIC ${DEAMON_SHARED_SOURCE_FILES} ${PROTO_SRC} ${PROTO_HEADER})

target_link_libraries(daemon_shared_lib ${JWTCPP_LIBRARIES} ${OPENSSL_LIBRARIES} ${ZeroMQ_LIBRARIES} ${PROTOBUF_LIBRARY})

add_custom_command(TARGET daemon_shared_lib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/keys/" "$<TARGET_FILE_DIR:daemon_shared_lib>/keys")
add_custom_command(TARGET daemon_shared_lib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/logs/" "$<TARGET_FILE_DIR:daemon_shared_lib>/logs")

IF (MSVC)
    target_link_libraries(daemon_shared_lib wsock32 ws2_32)

	set(ZeroMQ_ROOT_DIR "C:/Program Files/Focus/zmq")
    file(GLOB ZMQ_DLL "${ZeroMQ_ROOT_DIR}/bin/*.dll")
	message(STATUS "ZMQ_DLL: " ${ZMQ_DLL})
	foreach(DLL ${ZMQ_DLL})
		add_custom_command(TARGET daemon_shared_lib POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL}"
            "$<TARGET_FILE_DIR:daemon_shared_lib>")
	endforeach()
ELSE ()
    target_link_libraries(daemon_shared_lib pthread)
ENDIF ()

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF (MSVC)
    add_test(NAME daemon_shared_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_shared_tests.exe)
ELSE ()
    add_test(NAME daemon_shared_tests COMMAND daemon_shared_tests)
ENDIF ()