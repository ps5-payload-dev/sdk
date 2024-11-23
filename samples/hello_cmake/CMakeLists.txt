cmake_minimum_required(VERSION 3.5)

project(hello_cmake C CXX)
add_executable(hello_c main.c)
add_executable(hello_cpp main.cpp)

set_target_properties(hello_c PROPERTIES OUTPUT_NAME hello_c.elf)
set_target_properties(hello_cpp PROPERTIES OUTPUT_NAME hello_cpp.elf)
