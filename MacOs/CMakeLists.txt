find_library(CARBON_LIBRARY Carbon)

set(DEAMON_MAC_SOURCE_FILES
        Sources/ContextAgent.cpp
        Sources/AfkListener.cpp
        Sources/DisturbAgent.cpp

        Headers/ContextAgent.hpp
        Headers/AfkListener.hpp
        Headers/DisturbAgent.hpp)

set(MAIN_FILES
        main.cpp
        )

include_directories(Headers ${PROTOBUF_INCLUDE_DIR} ../Shared/Interfaces ../Shared/Headers ../Library ../Shared/Proto/ProtoCompiled)

add_library(daemon_mac_lib STATIC ${DEAMON_MAC_SOURCE_FILES})

add_executable(daemon_mac ${MAIN_FILES})
set_target_properties(daemon_mac PROPERTIES OUTPUT_NAME "focus-daemon")

target_link_libraries(daemon_mac daemon_mac_lib daemon_shared_lib ${CARBON_LIBRARY})

add_custom_command(TARGET daemon_mac POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/assets/app.html" "$<TARGET_FILE_DIR:daemon_mac>/bin/app.html")
add_custom_command(TARGET daemon_mac POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/MacOs/printAppTitle.scpt" "$<TARGET_FILE_DIR:daemon_mac>/bin/printAppTitle.scpt")
add_custom_command(TARGET daemon_mac POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/MacOs/printAppTitle.scpt" "$<TARGET_FILE_DIR:daemon_mac>/printAppTitle.scpt")
add_custom_command(TARGET daemon_mac POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/MacOs/toggleDoNotDisturb.sh" "$<TARGET_FILE_DIR:daemon_mac>/bin/toggleDoNotDisturb.sh")
add_custom_command(TARGET daemon_mac POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/MacOs/toggleDoNotDisturb.sh" "$<TARGET_FILE_DIR:daemon_mac>/toggleDoNotDisturb.sh")

include_target_dependency_in_target_package(daemon_shared_lib daemon_mac)

target_compile_options(daemon_mac_lib PRIVATE "${COMPILE_FLAGS}")
target_compile_options(daemon_mac PRIVATE "${COMPILE_FLAGS}")

####TESTS####

if (ENABLE_TESTING)
    add_subdirectory(UnitTests)

    enable_testing()
    IF (MSVC)
        add_test(NAME daemon_mac_tests COMMAND ${PROJECT_BINARY_DIR}/bin/daemon_mac_tests.exe)
    ELSE ()
        add_test(NAME daemon_mac_tests COMMAND daemon_mac_tests)
    ENDIF ()
endif()

####INSTALL####

### On OSX, we need to copy dependencies to the bundle
install(DIRECTORY ${CMAKE_BINARY_DIR}/BUILD/lib DESTINATION .)
install(DIRECTORY ${CMAKE_BINARY_DIR}/BUILD/bin DESTINATION .)
install(TARGETS daemon_mac DESTINATION ./bin)

####PACKAGE####

set(CPACK_BUNDLE_NAME "Focus")
set(CPACK_PACKAGE_FILE_NAME "Focus-${VERSION}-Darwin")
set(CPACK_BUNDLE_ICON "${PROJECT_SOURCE_DIR}/assets/icon_daemon.icns")
set(CPACK_BUNDLE_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist")
set(CPACK_BUNDLE_STARTUP_COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/start-daemon-osx.sh")
set(CPACK_GENERATOR "Bundle") # Setup package version
include (CPack)
