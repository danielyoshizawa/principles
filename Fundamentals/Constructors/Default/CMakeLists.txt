cmake_minimum_required(VERSION 3.8)

project(Default CXX)

add_executable(Default main.cpp)

set_property(TARGET Default PROPERTY CXX_STANDARD 17)
