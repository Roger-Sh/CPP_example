CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)
PROJECT(image-encode-decode)

add_compile_options(-std=c++11)

find_package(OpenCV 3.0 REQUIRED)

#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

INCLUDE_DIRECTORIES(
    include
    ${OpenCV_INCLUDE_DIRS}
)

ADD_EXECUTABLE(image-encode-decode src/image-encode-decode.cpp)
TARGET_LINK_LIBRARIES(image-encode-decode ${OpenCV_LIBRARIES}) 

