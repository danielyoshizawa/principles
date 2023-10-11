cmake_minimum_required(VERSION 3.8)

set(NAME "Lambdas")

project("${NAME}" CXX)

add_executable("${NAME}" main.cpp)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD_REQUIRED 23)
