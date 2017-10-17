cmake_minimum_required(VERSION 2.6)

project(daemon)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(cmake/ucm.cmake)
ucm_set_runtime(STATIC)

if(MSVC)
    add_definitions(-DMSVC)
elseif(APPLE)
    add_definitions(-DAPPLE)
endif()

add_subdirectory(UnitTests)
add_subdirectory(Shared)
#add_subdirectory(Linux)
#add_subdirectory(Mac)
add_subdirectory(Windows)