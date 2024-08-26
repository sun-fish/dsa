cmake_minimum_required(VERSION 3.15)

project(Public)

set(SRC
    entry.h
    dictionary.h
    main.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})


