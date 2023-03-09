# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(MyMathSdk)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "start build")

# 添加构建子目录
add_subdirectory(sdk)