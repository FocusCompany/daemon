include(GNUInstallDirs)

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

include_directories(Headers ../Shared/Interfaces ../Shared/Headers ../Library ../Shared/Proto/ProtoCompiled ${X11_INCLUDE_DIRS} ${XMU_INCLUDE_DIRS})

add_library(daemon_linux_lib STATIC ${DEAMON_LINUX_SOURCE_FILES})

add_executable(daemon_linux ${MAIN_FILES})
set_target_properties(daemon_linux PROPERTIES OUTPUT_NAME "focus-daemon")

target_link_libraries(daemon_linux daemon_linux_lib daemon_shared_lib ${X11_LIBRARIES} ${XSS_LIBRARIES} ${XMU_LIBRARIES})

link_directories(${X11_LIBRARY_DIRS} ${XMU_LIBRARY_DIRS})

include_target_dependency_in_target_package(daemon_shared_lib daemon_linux)

target_compile_options(daemon_linux_lib PRIVATE "${COMPILE_FLAGS}")
target_compile_options(daemon_linux PRIVATE "${COMPILE_FLAGS}")

####TESTS####

if (ENABLE_TESTING)
    add_subdirectory(UnitTests)

    enable_testing()
    IF (MSVC)
        add_test(NAME daemon_linux_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_linux_tests.exe)
    ELSE ()
        add_test(NAME daemon_linux_tests COMMAND daemon_linux_tests)
    ENDIF ()
endif()

####INSTALL####

install(DIRECTORY ${CMAKE_BINARY_DIR}/BUILD/lib/ DESTINATION lib/focus)
install(FILES "$<TARGET_FILE_DIR:daemon_shared_lib>/app.html" DESTINATION bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/focus-daemon.desktop DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
install(FILES ${PROJECT_SOURCE_DIR}/assets/icon_daemon.svg DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps/ RENAME focus.svg)
install(TARGETS daemon_linux DESTINATION bin)

####PACKAGE####

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS TRUE)
set(CPACK_GENERATOR RPM DEB) # Setup package version
include (CPack)
