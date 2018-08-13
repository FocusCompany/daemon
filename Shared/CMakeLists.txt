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
        Sources/FocusUI.cpp

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
        Headers/FocusUI.hpp

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

add_library(webview INTERFACE)

IF(MSVC)
    target_link_libraries(webview INTERFACE ole32 comctl32 oleaut32 uuid)
    target_link_libraries(daemon_shared_lib wsock32 ws2_32 webview)
ELSEIF(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(WEBKIT_LIBRARY WebKit)
    target_compile_options(webview INTERFACE "-x" "objective-c++")
    target_link_libraries(webview INTERFACE ${COCOA_LIBRARY} ${WEBKIT_LIBRARY})
    target_link_libraries(daemon_shared_lib webview pthread)
ELSEIF(UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    pkg_check_modules(WEBKIT REQUIRED webkitgtk-3.0)
    target_include_directories(webview INTERFACE ${GTK3_INCLUDE_DIRS} ${WEBKIT_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
    target_link_libraries(webview INTERFACE ${GTK3_LIBRARIES} ${WEBKIT_LIBRARIES})
    target_link_libraries(daemon_shared_lib webview pthread)
ENDIF()

target_compile_options(daemon_shared_lib PRIVATE "${COMPILE_FLAGS}")

add_custom_command(TARGET daemon_shared_lib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/assets/login.html" "$<TARGET_FILE_DIR:daemon_shared_lib>/login.html")

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