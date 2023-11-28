cmake_minimum_required(VERSION 3.8)

set(NAME "Exception")

project("${NAME}" CXX)

add_executable("${NAME}" main.cpp)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 20)
set_property(TARGET "${NAME}" PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)