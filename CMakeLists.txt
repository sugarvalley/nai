cmake_minimum_required(VERSION 3.23)
project(nai)

set(CMAKE_CXX_STANDARD 14)

include_directories(lab1)

add_executable(nai
        lab1/main.cpp
        lab1/main.h)
