cmake_minimum_required(VERSION 3.14)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src testing.cpp graphl.h graphl.cpp nodedata.cpp nodedata.h)