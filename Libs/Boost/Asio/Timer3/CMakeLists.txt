cmake_minimum_required(VERSION 3.8)

set(NAME "Timer3")

project("${NAME}" CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_package(Boost REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable("${NAME}" main.cpp) 
    set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 14)
    target_link_libraries("${NAME}" ${Boost_LIBRARIES})
endif()