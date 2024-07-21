cmake_minimum_required(VERSION 3.8)

project(Abstract_Class_And_Pure_Virtual_Functions CXX)

add_executable(Abstract_Class abstract.cpp)

set_property(TARGET Abstract_Class PROPERTY CXX_STANDARD 20)

add_executable(Virtual_Function virtual_function.cpp)

set_property(TARGET Virtual_Function PROPERTY CXX_STANDARD 20)

add_executable(Pure_Virtual_Function pure_virtual_function.cpp)

set_property(TARGET Pure_Virtual_Function PROPERTY CXX_STANDARD 20)
