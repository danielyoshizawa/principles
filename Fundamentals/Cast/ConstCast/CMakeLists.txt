cmake_minimum_required(VERSION 3.8)

project(ConstCast CXX)

add_executable(ConstCast main.cpp)

set_property(TARGET ConstCast PROPERTY CXX_STANDARD 17)

target_include_directories(ConstCast PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})