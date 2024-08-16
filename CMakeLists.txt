cmake_minimum_required(VERSION 3.15)

project(DSA)

add_subdirectory(array)
add_subdirectory(list)
add_subdirectory(binary_tree)

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type")