cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(pointcloud_segmentation)

find_package(PCL 1.7 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (crophull_filter src/crophull_filter.cpp)
target_link_libraries (crophull_filter ${PCL_LIBRARIES})
