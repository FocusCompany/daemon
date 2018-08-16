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
set_target_properties(daemon_windows PROPERTIES OUTPUT_NAME "focus-daemon")

target_link_libraries(daemon_windows daemon_windows_lib daemon_shared_lib Psapi)

target_compile_options(daemon_windows_lib PRIVATE "${COMPILE_FLAGS}")
target_compile_options(daemon_windows PRIVATE "${COMPILE_FLAGS}")

####TESTS####

if (ENABLE_TESTING)
    add_subdirectory(UnitTests)

    enable_testing()
    IF (MSVC)
        add_test(NAME daemon_windows_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_windows_tests.exe)
    ELSE ()
        add_test(NAME daemon_windows_tests COMMAND daemon_windows_tests)
    ENDIF ()
endif()

####INSTALL####

include(InstallRequiredSystemLibraries)
install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION bin COMPONENT Libraries)
install(DIRECTORY ${CMAKE_BINARY_DIR}/BUILD/ DESTINATION bin FILES_MATCHING PATTERN "*.dll")
install(TARGETS daemon_windows DESTINATION bin)

####PACKAGE####

SET(CPACK_GENERATOR NSIS)
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/assets/icon_daemon.ico")
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/assets/icon_uninstall.ico")
set(CPACK_NSIS_DISPLAY_NAME "Focus-daemon")
set(CPACK_NSIS_PACKAGE_NAME "Focus-${VERSION}-Win")
set(CPACK_NSIS_MENU_LINKS "bin/focus-daemon" "Focus-daemon")
include(CPack)