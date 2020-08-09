cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(new_point_type)

find_package(PCL 1.7 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (new_point_type src/new_point_type.cpp)
target_link_libraries (new_point_type ${PCL_LIBRARIES})
