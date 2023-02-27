cmake_minimum_required(VERSION 3.15.0)

project(MathFunctions)

# 查找当前目录下的所有源文件，并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库 - 动态库
add_library(${PROJECT_NAME} SHARED ${DIR_LIB_SRCS})

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

message(STATUS "CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")