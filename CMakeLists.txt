cmake_minimum_required(VERSION 3.16)
project(my_tiny_stl)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32)
add_executable(my_tiny_stl main.cpp)