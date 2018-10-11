cmake_minimum_required(VERSION 3.8)

project(State CXX)

set(SOURCE context.cpp state_one.cpp state_two.cpp)

add_executable(State ${SOURCE} main.cpp)

set_property(TARGET State PROPERTY CXX_STANDARD 14)

target_include_directories(State PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
