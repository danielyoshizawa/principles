cmake_minimum_required(VERSION 3.8)

project(ReinterpretCast CXX)

add_executable(ReinterpretCast main.cpp)

set_property(TARGET ReinterpretCast PROPERTY CXX_STANDARD 17)

target_include_directories(ReinterpretCast PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PrivateDataAccess private.cpp)

set_property(TARGET PrivateDataAccess PROPERTY CXX_STANDARD 17)