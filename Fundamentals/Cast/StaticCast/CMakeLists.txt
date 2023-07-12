cmake_minimum_required(VERSION 3.8)

project(StaticCast CXX)

add_executable(StaticCast main.cpp)

set_property(TARGET StaticCast PROPERTY CXX_STANDARD 17)

target_include_directories(StaticCast PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
