include(FindOpenSSL)
find_package(OpenSSL REQUIRED)

include(FindProtobuf)
find_package(Protobuf REQUIRED)

include(FindZeroMQ)
find_package(ZeroMQ REQUIRED)

file(GLOB PROTO_SRC "Proto/ProtoCompiled/*.pb.cc")
file(GLOB PROTO_HEADER "Proto/ProtoCompiled/*.pb.h")

if(NOT MSVC)
	set_source_files_properties(${PROTO_SRC} ${PROTO_HEADER} PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-unused-parameter")
endif()

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
        Sources/FocusPlatformFolders.cpp

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
        Headers/FocusPlatformFolders.hpp

        Interfaces/IContextAgent.hpp
        Interfaces/IAfkListener.hpp
        )

include_directories(Headers Interfaces ${OPENSSL_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} Proto/ProtoCompiled ${ZeroMQ_INCLUDE_DIR})

IF (MSVC)
    include_directories(../Windows/Headers)
ELSEIF (APPLE)
    include_directories(../MacOs/Headers)
ELSEIF (UNIX)
    include_directories(../Linux/Headers)
ENDIF ()

add_library(daemon_shared_lib STATIC ${DEAMON_SHARED_SOURCE_FILES} ${PROTO_SRC} ${PROTO_HEADER} ${OPENSSL_INCLUDE_DIR})

target_link_libraries(daemon_shared_lib ${OPENSSL_CRYPTO_LIBRARY} ${ZeroMQ_LIBRARIES} ${PROTOBUF_LIBRARY})

IF (MSVC)
    target_link_libraries(daemon_shared_lib wsock32 ws2_32)
	add_custom_command(TARGET daemon_shared_lib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "C:/Program Files/Focus/zmq/bin" "$<TARGET_FILE_DIR:daemon_shared_lib>")
	add_custom_command(TARGET daemon_shared_lib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "C:/OpenSSL-Win32/bin/" "$<TARGET_FILE_DIR:daemon_shared_lib>")
ELSE ()
    target_link_libraries(daemon_shared_lib pthread)
ENDIF ()

target_compile_options(daemon_shared_lib PRIVATE "${COMPILE_FLAGS}")

####TESTS####

if (ENABLE_TESTING)
    add_subdirectory(UnitTests)

    enable_testing()
    IF (MSVC)
        add_test(NAME daemon_shared_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_shared_tests.exe)
    ELSE ()
        add_test(NAME daemon_shared_tests COMMAND daemon_shared_tests)
    ENDIF ()
endif()