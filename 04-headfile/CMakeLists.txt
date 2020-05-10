# cmake minimum required version
cmake_minimum_required(VERSION 3.0)

# project name 
project(headfile-example)

# include 
include_directories( include )

# auto contruct source 
aux_source_directory( src DIR_SRCS )

# executable target 
add_executable (headfile-example ${DIR_SRCS})

# link libraries
#target_link_libraries()
