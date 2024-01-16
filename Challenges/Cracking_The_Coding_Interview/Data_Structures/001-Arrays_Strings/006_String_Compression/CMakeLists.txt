cmake_minimum_required(VERSION 3.8)

set(NAME "006_String_Compression")

project("${NAME}" CXX)

add_executable("${NAME}" main.cpp)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 20)
