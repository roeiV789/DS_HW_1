cmake_minimum_required(VERSION 3.10)

project(HW1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 14) # -std=c++14

# add_compile_definitions(NDEBUG) # -DNDEBUG; leave it out of CMake to run unit tests
# when running using CMake

add_compile_options(-Wall) # -Wall
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(HW1
        unit_tests.cpp
        AVLTree.h

)
