cmake_minimum_required(VERSION 3.8)

project(DynamicCast CXX)

add_executable(DynamicCast main.cpp)

set_property(TARGET DynamicCast PROPERTY CXX_STANDARD 17)

target_include_directories(DynamicCast PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
