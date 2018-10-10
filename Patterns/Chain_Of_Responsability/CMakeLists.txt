cmake_minimum_required(VERSION 3.8)

project(Chain_Of_Responsability CXX)

set(SOURCE responsability_one.cpp responsability_two.cpp responsability_three.cpp)

add_executable(Chain_Of_Responsability ${SOURCE} main.cpp)

set_property(TARGET Chain_Of_Responsability PROPERTY CXX_STANDARD 14)

target_include_directories(Chain_Of_Responsability PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
