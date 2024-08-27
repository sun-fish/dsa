cmake_minimum_required(VERSION 3.15)

project(SkipList)

set (SRC
    skip_list.h
    quad_list_node.h
    quad_list.h
    utility.h
    compile_test.cpp
    main.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})