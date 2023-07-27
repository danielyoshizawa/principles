cmake_minimum_required(VERSION 3.8)

set(NAME "ConditionVariable")

project("${NAME}" CXX)

add_executable("${NAME}" main.cpp)
add_executable(Wait wait.cpp)

set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 20)
set_property(TARGET Wait PROPERTY CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")