cmake_minimum_required(VERSION 3.8)

project(Strategy CXX)

set(SOURCE context.cpp strategy_plus_one.cpp strategy_plus_ten.cpp)

add_executable(Strategy ${SOURCE} main.cpp)

set_property(TARGET Strategy PROPERTY CXX_STANDARD 14)

target_include_directories(Strategy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
