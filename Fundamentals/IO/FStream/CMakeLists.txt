cmake_minimum_required(VERSION 3.8)

project(FStream CXX)

add_executable(FStream main.cpp)

set_property(TARGET FStream PROPERTY CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")