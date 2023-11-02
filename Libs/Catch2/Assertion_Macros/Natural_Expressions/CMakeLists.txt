cmake_minimum_required(VERSION 3.8)

set(NAME "NaturalExpressions")

project("${NAME}" CXX)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable("${NAME}" test.cpp)
target_link_libraries("${NAME}" PRIVATE Catch2::Catch2WithMain)
set_property(TARGET "${NAME}" PROPERTY CXX_STANDARD_REQUIRED 20)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests("${NAME}")