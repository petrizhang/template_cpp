cmake_minimum_required(VERSION 3.5)
project(TemplateCpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        )

add_executable(TemplateCpp ${SOURCE_FILES})

target_link_libraries(TemplateCpp
        /usr/src/gtest/libgtest.a
        pthread)