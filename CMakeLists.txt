cmake_minimum_required(VERSION 3.23.2)
project(nai)

set(CMAKE_CXX_STANDARD 14)

include_directories(lab1, lab2)

add_executable(nai
        lab1/main.cpp
        lab2/lab2.cpp
        lab3/lab3.cpp lab3/lab3.h)

add_executable(lab1_main lab1/main.cpp lab3/lab3.cpp lab3/lab3.h lab4/lab4.cpp lab4/lab4.h)
add_executable(lab2_lab2 lab2/lab2.cpp)
add_executable(main lab1/main.cpp)
add_executable(lab2 lab2/lab2.cpp)
add_executable(lab3 lab3/lab3.cpp)
add_executable(lab4 lab4/lab4.cpp)