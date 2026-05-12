cmake_minimum_required(VERSION 3.10)

project(hello_cmake C CXX)
add_executable(hello_c main.c)
add_executable(hello_cpp main.cpp)

set_target_properties(hello_c PROPERTIES OUTPUT_NAME hello_c.elf)
set_target_properties(hello_cpp PROPERTIES OUTPUT_NAME hello_cpp.elf)

add_custom_target(test_c
    USES_TERMINAL
    COMMAND ${PS5_DEPLOY} hello_c.elf
    DEPENDS hello_c
)

add_custom_target(test_cpp
    USES_TERMINAL
    COMMAND ${PS5_DEPLOY} hello_cpp.elf
    DEPENDS hello_cpp
)
