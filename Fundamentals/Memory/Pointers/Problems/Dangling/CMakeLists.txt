cmake_minimum_required(VERSION 3.8)

project(Dangling CXX)

add_executable(Dangling main.cpp)

set_property(TARGET Dangling PROPERTY CXX_STANDARD 17)
