cmake_minimum_required(VERSION 3.8)

project(DiamondCXX)

add_executable(Diamond main.cpp)

set_property(TARGET Diamond PROPERTY CXX_STANDARD 17)

target_include_directories(Diamond PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Virtual virtual.cpp)