cmake_minimum_required(VERSION 3.8)

project(Memento CXX)

set(SOURCE memento.cpp originator.cpp)

add_executable(Memento ${SOURCE} main.cpp)

set_property(TARGET Memento PROPERTY CXX_STANDARD 14)

target_include_directories(Memento PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
