cmake_minimum_required(VERSION 3.15)

project(BinaryTree)

set (SRC
    binary_node.h
    compile_test.cpp
    main.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})