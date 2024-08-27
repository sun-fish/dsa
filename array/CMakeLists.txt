cmake_minimum_required(VERSION 3.15)

project(Array)

set (SRC
    array.h
    utility.h
    compile_test.cpp
    main.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})