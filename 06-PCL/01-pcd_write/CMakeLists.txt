cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#name of the project 
project(pcd_write)

#only one component
#find_package(PCL 1.8 REQUIRED io)
#several components
#find_package(PCL 1.8 REQUIRED io common)
#all existing
find_package(PCL 1.8 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (pcd_write src/pcd_write.cpp)
target_link_libraries (pcd_write ${PCL_LIBRARIES})
