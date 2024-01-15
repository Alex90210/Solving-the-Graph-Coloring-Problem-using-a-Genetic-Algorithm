cmake_minimum_required(VERSION 3.26)
project(Homework3SA)

set(CMAKE_CXX_STANDARD 17)

add_executable(Homework3SA main.cpp
        include/SA.h
        src/SA.cpp
        include/utils.h
        src/utils.cpp)
