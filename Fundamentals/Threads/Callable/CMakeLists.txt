cmake_minimum_required(VERSION 3.8)

project(Callable CXX)

add_executable(Callable main.cpp)

set_property(TARGET Callable PROPERTY CXX_STANDARD 17)

target_include_directories(Callable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
