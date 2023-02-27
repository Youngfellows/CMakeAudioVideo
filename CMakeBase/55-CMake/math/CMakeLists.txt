cmake_minimum_required(VERSION 3.15.0)

project(MathFunctions)

# 查找当前目录下的所有源文件，并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库 - 静态库
add_library(${PROJECT_NAME} STATIC ${DIR_LIB_SRCS})

message(STATUS "CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")

# 指定动态库依赖的头文件,这样在main.cpp中就不用引用全路径了:"include/MathFunctions.h",只需要"MathFunctions.h"
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
