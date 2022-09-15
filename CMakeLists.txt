cmake_minimum_required(VERSION 3.13)

project(templates-programming CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")

add_subdirectory(function-templates)
add_subdirectory(class-templates)
add_subdirectory(non-type-templates-args)