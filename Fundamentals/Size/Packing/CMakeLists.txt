cmake_minimum_required(VERSION 3.8)

project(Packing CXX)

add_executable(Packing main.cpp)

set_property(TARGET Packing PROPERTY CXX_STANDARD 17)

target_include_directories(Packing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
