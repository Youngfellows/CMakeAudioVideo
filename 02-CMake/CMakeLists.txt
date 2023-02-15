# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# cmake打印
message(VERSION: ${VERSION})

# 项目名称为 Sample
project(Sample)
message("Project: " ${PROJECT_NAME})

# 将当前目录中的源文件名称赋值给变量 SRC_LIST
set(SRC_LIST main.cpp MathFunctions.cpp)
# aux_source_directory(. SRC_LIST)
message("SRC_LIST: " ${SRC_LIST})

# 指示变量 SRC_LIST 中的源文件需要编译成一个名称为 Sample 的可执行文件
# add_executable(Sample ${SRC_LIST})
add_executable(${PROJECT_NAME} ${SRC_LIST})