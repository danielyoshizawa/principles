cmake_minimum_required(VERSION 3.8)

project(Template_Method CXX)

set(SOURCE abstract.cpp implementation.cpp)

add_executable(Template_Method ${SOURCE} main.cpp)

set_property(TARGET Template_Method PROPERTY CXX_STANDARD 14)

target_include_directories(Template_Method PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
