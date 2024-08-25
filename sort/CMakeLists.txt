cmake_minimum_required(VERSION 3.15)

project(Sort)

set (SRC
    sort.h
    utility.h
    compile_test.cpp
    main.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})