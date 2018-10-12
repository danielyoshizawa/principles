cmake_minimum_required(VERSION 3.8)

project(Mediator CXX)

set(SOURCE colleague.cpp mediator.cpp)

add_executable(Mediator ${SOURCE} main.cpp)

set_property(TARGET Mediator PROPERTY CXX_STANDARD 14)

target_include_directories(Mediator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
