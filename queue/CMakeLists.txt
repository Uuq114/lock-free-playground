project(queue)

include_directories(include)

find_library(ATOMIC_LIBRARY NAMES atomic)

# 添加可执行文件
add_executable(queue
        include/ubqueue.h
        src/main.cpp
        src/ubqueue.cpp
)

# 链接 libatomic
if (ATOMIC_LIBRARY)
    target_link_libraries(queue ${ATOMIC_LIBRARY})
else()
    message(WARNING "libatomic not found, linking may fail")
endif()