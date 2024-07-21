cmake_minimum_required(VERSION 3.8)

project(Advanced_Object-Oriented_Programming CXX)

add_executable(Multiple multiple.cpp)

set_property(TARGET Multiple PROPERTY CXX_STANDARD 20)

target_include_directories(Multiple PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Diamond diamond.cpp)

set_property(TARGET Diamond PROPERTY CXX_STANDARD 20)

target_include_directories(Diamond PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Diamond_Solution diamond_solution.cpp)

set_property(TARGET Diamond_Solution PROPERTY CXX_STANDARD 17)

target_include_directories(Diamond_Solution PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
