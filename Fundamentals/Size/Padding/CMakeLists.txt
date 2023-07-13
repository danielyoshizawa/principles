cmake_minimum_required(VERSION 3.8)

project(Padding CXX)

add_executable(Padding main.cpp)

set_property(TARGET Padding PROPERTY CXX_STANDARD 17)

target_include_directories(Padding PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Virtual virtual.cpp)