set(DEAMON_WINDOWS_SOURCE_FILES
        Sources/ContextAgent.cpp
        Sources/AfkListener.cpp

        Headers/ContextAgent.hpp
        Headers/AfkListener.hpp
        )

set(MAIN_FILES
        main.cpp
        )

include_directories(Headers ../Shared/Interfaces ../Shared/Headers ../Library ../Shared/Proto/ProtoCompiled)

add_library(daemon_windows_lib STATIC ${DEAMON_WINDOWS_SOURCE_FILES})

add_executable(daemon_windows ${MAIN_FILES})
set_target_properties(daemon_windows PROPERTIES OUTPUT_NAME "focus-daemon")

target_link_libraries(daemon_windows daemon_windows_lib daemon_shared_lib Psapi)

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

install(TARGETS daemon_windows DESTINATION bin)