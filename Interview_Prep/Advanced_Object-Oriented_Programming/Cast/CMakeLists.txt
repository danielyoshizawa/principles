cmake_minimum_required(VERSION 3.8)

project(Cast CXX)

add_executable(Const const.cpp)

set_property(TARGET Const PROPERTY CXX_STANDARD 20)

add_executable(Static static.cpp)

set_property(TARGET Static PROPERTY CXX_STANDARD 20)

add_executable(Dynamic dynamic.cpp)

set_property(TARGET Dynamic PROPERTY CXX_STANDARD 20)

add_executable(Reinterpret reinterpret.cpp)

set_property(TARGET Reinterpret PROPERTY CXX_STANDARD 20)