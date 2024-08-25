cmake_minimum_required(VERSION 3.15)

project(DSA)

# 源代码文件所使用的编码
set(CMAKE_CHARSET "UTF-8") 

 # 添加UTF8编码支持, 必须在add_executable前调用
# 忽略4819警告
if (MSVC)
    add_compile_options("/utf-8")
    set(CMAKE_C_DISABLE_WARNINGS 4819)
    set(CMAKE_CXX_DISABLE_WARNINGS 4819)
endif()

add_subdirectory(array)
add_subdirectory(list)
add_subdirectory(binary_tree)
add_subdirectory(graph)
add_subdirectory(binary_search_tree)

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type")