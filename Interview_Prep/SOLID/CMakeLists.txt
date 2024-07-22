cmake_minimum_required(VERSION 3.8)

project(SOLID CXX)

add_executable(Single single.cpp)

set_property(TARGET Single PROPERTY CXX_STANDARD 20)

add_executable(OpenClose open_close.cpp)

set_property(TARGET OpenClose PROPERTY CXX_STANDARD 20)

add_executable(Liskov liskov.cpp)

set_property(TARGET Liskov PROPERTY CXX_STANDARD 20)

add_executable(Interface interface.cpp)

set_property(TARGET Interface PROPERTY CXX_STANDARD 20)

add_executable(Dependency dependency.cpp)

set_property(TARGET Dependency PROPERTY CXX_STANDARD 20)
