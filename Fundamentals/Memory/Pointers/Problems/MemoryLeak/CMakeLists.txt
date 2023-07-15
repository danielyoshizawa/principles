cmake_minimum_required(VERSION 3.8)

project(MemoryLeak CXX)

add_executable(MemoryLeak main.cpp)

set_property(TARGET MemoryLeak PROPERTY CXX_STANDARD 17)
