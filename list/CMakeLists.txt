cmake_minimum_required(VERSION 3.15)

project(List)

set(SRC
    list_node.h
    list.h
    utility.h
    compile_test.cpp
	main.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})


