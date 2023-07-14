cmake_minimum_required(VERSION 3.8)

project(Execution CXX)

add_executable(Join join.cpp)
add_executable(Detach detach.cpp)

set_property(TARGET Join PROPERTY CXX_STANDARD 17)
set_property(TARGET Detach PROPERTY CXX_STANDARD 17)
