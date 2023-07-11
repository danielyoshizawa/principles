cmake_minimum_required(VERSION 3.8)

project(BasicTypes CXX)

add_executable(BasicTypes main.cpp)

set_property(TARGET BasicTypes PROPERTY CXX_STANDARD 14)

target_include_directories(BasicTypes PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
