cmake_minimum_required(VERSION 3.14)

set(NAME "curl_easy_cleanup")

project("${NAME}" CXX)
set(CMAKE_BUILD_TYPE Debug)

find_package(CURL REQUIRED)

add_executable("${NAME}" main.cpp)
target_link_libraries("${NAME}" CURL::libcurl)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 20)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD_REQUIRED YES)
