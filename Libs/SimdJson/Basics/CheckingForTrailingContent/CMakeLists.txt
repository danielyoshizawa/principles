cmake_minimum_required(VERSION 3.14)

set(NAME "CheckTrailingContent")

project("${NAME}" CXX)
set(CMAKE_BUILD_TYPE Debug)

# Using FetchContent to get simdjson lib
# include(FetchContent)

# FetchContent_Declare(
#     simdjson
#     GIT_REPOSITORY https://github.com/simdjson/simdjson.git
#     GIT_TAG tags/v3.6.3
#     GIT_SHALLOW true
# )

# FetchContent_MakeAvailable(simdjson)

# Using system installed simdjson
find_package(simdjson REQUIRED)

add_executable("${NAME}" main.cpp)
target_link_libraries("${NAME}" simdjson)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD 20)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD_REQUIRED YES)

# Move test.json file to the build
# add_custom_command(TARGET "${NAME}" POST_BUILD 
#                     COMMAND ${CMAKE_COMMAND} -E copy
#                             ${CMAKE_SOURCE_DIR}/test.json
#                             ${CMAKE_CURRENT_BINARY_DIR}/test.json
#                     )