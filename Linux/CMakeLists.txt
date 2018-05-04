cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_STANDARD 14)

include(FindProtobuf)
find_package(Protobuf REQUIRED)

find_package(PkgConfig)
pkg_check_modules(X11 REQUIRED x11)
pkg_check_modules(XMU REQUIRED xmu)

find_library(XSS_LIBRARIES Xss)
if(NOT XSS_LIBRARIES)
    message(FATAL_ERROR "Xss library not found")
else()
    message(STATUS "Xss library found")
endif()

set(DEAMON_LINUX_SOURCE_FILES
        Sources/ContextAgent.cpp
        Sources/AfkListener.cpp

        Headers/ContextAgent.hpp
        Headers/AfkListener.hpp
        )

set(MAIN_FILES
        main.cpp
        )

include_directories(Headers ../Shared/Interfaces ../Shared/Headers ../Library ../Shared/Proto/ProtoCompiled ${PROTOBUF_INCLUDE_DIR} ${X11_INCLUDE_DIRS} ${XMU_INCLUDE_DIRS})

add_library(daemon_linux_lib STATIC ${DEAMON_LINUX_SOURCE_FILES})

add_executable(daemon_linux ${MAIN_FILES})
set_target_properties(daemon_linux PROPERTIES OUTPUT_NAME "focus-daemon")

target_link_libraries(daemon_linux daemon_linux_lib daemon_shared_lib ${X11_LIBRARIES} ${XSS_LIBRARIES} ${XMU_LIBRARIES})

link_directories(${X11_LIBRARY_DIRS} ${XMU_LIBRARY_DIRS})

####TESTS####

add_subdirectory(UnitTests)

enable_testing()
IF (MSVC)
    add_test(NAME daemon_linux_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_linux_tests.exe)
ELSE ()
    add_test(NAME daemon_linux_tests COMMAND daemon_linux_tests)
ENDIF ()

####INSTALL####

install(TARGETS daemon_linux DESTINATION bin)

####PACKAGE####

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS TRUE)
set(CPACK_GENERATOR RPM DEB) # Setup package version
include (CPack)
