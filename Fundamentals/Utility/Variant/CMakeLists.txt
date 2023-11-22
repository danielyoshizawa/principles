cmake_minimum_required(VERSION 3.8)

set(NAME "Variant")

project("${NAME}" CXX)

add_executable("${NAME}" main.cpp)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 20)

add_executable(visit visit.cpp)
set_property(TARGET visit PROPERTY CXX_STANDARD 20)