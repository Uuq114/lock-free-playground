cmake_minimum_required(VERSION 3.26)
project(lock_free_playground)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(queue/include)

add_executable(lock_free_playground
        queue/include/ubqueue.h
        queue/src/main.cpp
        queue/src/ubqueue.cpp)
