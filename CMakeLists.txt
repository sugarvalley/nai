cmake_minimum_required(VERSION 3.23.2)
project(nai)

set(CMAKE_CXX_STANDARD 14)

include_directories(lab1)

add_executable(nai
        lab1/main.cpp
        )

add_executable(lab1_main lab1/main.cpp)
add_executable(main lab1/main.cpp)