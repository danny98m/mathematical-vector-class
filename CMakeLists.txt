cmake_minimum_required(VERSION 3.8)
project(a4)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES vect.cpp vect.h realVectorProblem.cpp)
add_executable(a4 ${SOURCE_FILES})