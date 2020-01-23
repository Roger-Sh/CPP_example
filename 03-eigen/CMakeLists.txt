cmake_minimum_required(VERSION 3.0)

project(eigen-example)

INCLUDE_DIRECTORIES(/usr/include/eigen3)

add_executable (01-eigen-example src/01-eigen-example.cpp)
target_link_libraries (01-eigen-example)
