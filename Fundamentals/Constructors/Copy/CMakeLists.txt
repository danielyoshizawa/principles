cmake_minimum_required(VERSION 3.8)

project(Copy CXX)

add_executable(Copy main.cpp)
add_executable(Shallow shallow.cpp)
add_executable(Deep deep.cpp)

set_property(TARGET Copy PROPERTY CXX_STANDARD 17)
set_property(TARGET Shallow PROPERTY CXX_STANDARD 17)
set_property(TARGET Deep PROPERTY CXX_STANDARD 17)

