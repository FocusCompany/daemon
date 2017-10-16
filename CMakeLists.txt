cmake_minimum_required(VERSION 2.6)

project(daemon)

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