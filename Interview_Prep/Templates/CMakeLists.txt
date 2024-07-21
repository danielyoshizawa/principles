cmake_minimum_required(VERSION 3.8)

project(Templates CXX)

add_executable(Functions functions.cpp)

set_property(TARGET Functions PROPERTY CXX_STANDARD 20)

add_executable(Class class.cpp)

set_property(TARGET Class PROPERTY CXX_STANDARD 20)

add_executable(Specialization specialization.cpp)

set_property(TARGET Specialization PROPERTY CXX_STANDARD 20)

add_executable(Parameter parameter.cpp)

set_property(TARGET Parameter PROPERTY CXX_STANDARD 20)

add_executable(Variadic variadic.cpp)

set_property(TARGET Variadic PROPERTY CXX_STANDARD 20)

add_executable(SFINAE sfinae.cpp)

set_property(TARGET SFINAE PROPERTY CXX_STANDARD 20)

add_executable(Concepts concepts.cpp)

set_property(TARGET Concepts PROPERTY CXX_STANDARD 20)