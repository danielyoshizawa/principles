cmake_minimum_required(VERSION 3.8)

project(Visitor CXX)

set(SOURCE element_one.cpp element_two.cpp visitor_one.cpp visitor_two.cpp)

add_executable(Visitor ${SOURCE} main.cpp)

set_property(TARGET Visitor PROPERTY CXX_STANDARD 14)

target_include_directories(Visitor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
