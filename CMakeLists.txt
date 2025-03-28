cmake_minimum_required(VERSION 3.10)

project(lock_free_playground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(queue/include)
find_library(ATOMIC_LIBRARY NAMES atomic)

add_executable(lock_free_playground
        queue/include/ubqueue.h
        queue/src/main.cpp
        queue/src/ubqueue.cpp
)

if (ATOMIC_LIBRARY)
    target_link_libraries(lock_free_playground ${ATOMIC_LIBRARY})
else()
    message(WARNING "libatomic not found, linking may fail")
endif()