cmake_minimum_required(VERSION 3.5)
project(01_Sort)

# ${CMAKE_CXX_FLAGS}:在运行CMAKE时现有的CXX标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 设置源文件变量为main.cpp
set(SOURCE_FILES main.cpp)
# 创建一个可执行文件，叫01_Sort,基于刚才的源文件设的
add_executable(SortTest ${SOURCE_FILES})