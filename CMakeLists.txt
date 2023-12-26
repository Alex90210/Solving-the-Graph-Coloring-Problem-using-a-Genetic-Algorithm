cmake_minimum_required(VERSION 3.26)
project(Homework3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Homework3 src/main.cpp
        include/generators.h
        src/generators.cpp
        include/col_operators.h
        src/col_operators.cpp
        include/GA.h
        src/GA.cpp
        include/utils.h
        src/utils.cpp
        include/ag_mutation.h
        include/ag_crossover.h
        include/ag_selection.h
        src/ag_crossover.cpp
        src/ag_mutation.cpp
        src/ag_selection.cpp
        src/ag_fitness.cpp
        include/ag_fitness.h)
