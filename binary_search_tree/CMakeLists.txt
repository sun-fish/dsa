cmake_minimum_required(VERSION 3.15)

project(BinarySearchTree)

set (SRC
    binary_search_tree.h
    utility.h
    compile_test.cpp
    main.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})