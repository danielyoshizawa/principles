cmake_minimum_required(VERSION 3.8)

project(Smart_Pointers CXX)

add_executable(Unique unique.cpp)

set_property(TARGET Unique PROPERTY CXX_STANDARD 20)

add_executable(Shared shared.cpp)

set_property(TARGET Shared PROPERTY CXX_STANDARD 20)

add_executable(Weak weak.cpp)

set_property(TARGET Weak PROPERTY CXX_STANDARD 20)
