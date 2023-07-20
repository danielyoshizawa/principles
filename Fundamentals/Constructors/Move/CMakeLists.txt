cmake_minimum_required(VERSION 3.8)

project(Move CXX)

add_executable(Move main.cpp)
add_executable(Delete deleteMove.cpp)
add_executable(Vector vector.cpp)
add_executable(Performance performance.cpp)

set_property(TARGET Move PROPERTY CXX_STANDARD 17)
set_property(TARGET Delete PROPERTY CXX_STANDARD_17)
set_property(TARGET Vector PROPERTY CXX_STANDARD_17)
set_property(TARGET Performance PROPERTY CXX_STANDARD_17)

target_include_directories(Performance PUBLIC ${CMAKE_SOURCE_DIR}/../../../Utils)
