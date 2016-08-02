cmake_minimum_required(VERSION 3.5)
project(TemplateCpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        exercises/test.hpp
        exercises/chapter2/chapter2.hpp
        exercises/chapter2/2-0.hpp
        exercises/chapter2/2-1.hpp
        exercises/chapter2/2-2.hpp
        exercises/chapter2/2-3_4.hpp
        exercises/chapter3/lambda.hpp
        exercises/chapter3/3_0.hpp exercises/chapter3/3_1_2.hpp)

add_executable(TemplateCpp ${SOURCE_FILES})

target_link_libraries(TemplateCpp
        /usr/src/gtest/libgtest.a
        pthread)