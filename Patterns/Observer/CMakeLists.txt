cmake_minimum_required(VERSION 3.8)

project(Observer CXX)

set(SOURCE observer_one.cpp observer_two.cpp subject.cpp)

add_executable(Observer ${SOURCE} main.cpp)

set_property(TARGET Observer PROPERTY CXX_STANDARD 14)

target_include_directories(Observer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
