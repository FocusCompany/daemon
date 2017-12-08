cmake_minimum_required(VERSION 2.6)

project(daemon_shared_lib)

set(CMAKE_CXX_STANDARD 14)

include(FindProtobuf)
find_package(Protobuf REQUIRED)

file(GLOB PROTO_SRC "Proto/ProtoCompiled/*.pb.cc")
file(GLOB PROTO_HEADER "Proto/ProtoCompiled/*.pb.h")

set(DEAMON_SHARED_SOURCE_FILES
		Sources/FocusDaemon.cpp
		Sources/FocusEventManager.cpp
		Sources/FocusEventEmitter.cpp
		Sources/FocusEventListener.cpp
		Sources/FocusNetworkManager.cpp
		Sources/FocusKeyLogger.cpp

		Headers/FocusDaemon.hpp
		Headers/FocusEventManager.hpp
		Headers/FocusEventEmitter.hpp
		Headers/FocusEventListener.hpp
		Headers/FocusNetworkManager.hpp
		Headers/FocusKeyLogger.hpp

		Interfaces/IContextAgent.hpp
		)

include_directories(Headers Interfaces ${PROTOBUF_INCLUDE_DIR} Proto/ProtoCompiled)

IF(MSVC)
	include_directories(../Windows/Headers)
ELSE()
	include_directories(../Linux/Headers)
ENDIF()

add_library(daemon_shared_lib STATIC ${DEAMON_SHARED_SOURCE_FILES} ${PROTO_SRC} ${PROTO_HEADER})

target_link_libraries(daemon_shared_lib nanomsg ${PROTOBUF_LIBRARY})

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF(MSVC)
    add_test(NAME daemon_shared_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_shared_tests.exe)
ELSE()
    add_test(NAME daemon_shared_tests COMMAND daemon_shared_tests)
ENDIF()