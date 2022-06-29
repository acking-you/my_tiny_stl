cmake_minimum_required(VERSION 3.16)
#你的项目名称
project(my_tiny_stl)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/Clib)

add_subdirectory(src/Data_struct_tool)

add_subdirectory(src/Practical_algorithms)

add_subdirectory(src/Socket_tool)

add_subdirectory(src/Template_tool)