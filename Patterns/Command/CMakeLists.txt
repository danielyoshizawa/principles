cmake_minimum_required(VERSION 3.8)

project(Command CXX)

set(SOURCE command.cpp other_command.cpp manager.cpp)

add_executable(Command ${SOURCE} main.cpp)

set_property(TARGET Command PROPERTY CXX_STANDARD 14)

target_include_directories(Command PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
