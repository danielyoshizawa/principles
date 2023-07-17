cmake_minimum_required(VERSION 3.8)

project(BufferOverflow CXX)

add_executable(BufferOverflow main.cpp)

set_property(TARGET BufferOverflow PROPERTY CXX_STANDARD 17)
