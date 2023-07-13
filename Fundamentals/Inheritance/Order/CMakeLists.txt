cmake_minimum_required(VERSION 3.8)

project(Order CXX)

add_executable(Order main.cpp)

set_property(TARGET Order PROPERTY CXX_STANDARD 17)

target_include_directories(Order PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Virtual virtual.cpp)
add_executable(VirtualFix virtualFix.cpp)