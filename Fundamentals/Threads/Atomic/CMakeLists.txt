cmake_minimum_required(VERSION 3.8)

set(NAME "Atomic")

project("${NAME}" CXX)

add_executable("${NAME}" main.cpp)

set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")