cmake_minimum_required(VERSION 3.15)

project(Graph)

set (SRC
    graph.h
    graph_matrix.h
    utility.h
    compile_test.cpp
    main.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})