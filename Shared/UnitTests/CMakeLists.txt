cmake_minimum_required(VERSION 2.6)

add_executable(daemon_shared_tests DummyTest.cpp)

target_include_directories(daemon_shared_tests PUBLIC ../ ${CMAKE_SOURCE_DIR}/UnitTests/gtest/googletest ${CMAKE_SOURCE_DIR}/UnitTests/gtest/googletest/include)

target_link_libraries(daemon_shared_tests daemon_shared_lib gtest gtest_main)

IF(MSVC)
    # Creates a folder "executables" and adds target
    # project (app.vcproj) under it
    set_property(TARGET daemon_shared_tests PROPERTY FOLDER "executables")

    # Properties->General->Output Directory
    set_target_properties(daemon_shared_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

    # Adds logic to INSTALL.vcproj to copy daemon-windows-tests.exe to destination directory
    install (TARGETS daemon_shared_tests RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)
ENDIF()