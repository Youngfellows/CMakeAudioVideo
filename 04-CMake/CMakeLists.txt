# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# cmake打印
message(VERSION: ${VERSION})

# 项目名称为 Sample
project(Sample)
message("Project: " ${PROJECT_NAME})

# 查找当前目录下的所有源文件，并将名称保存到 SRC_LIST 变量
# set(SRC_LIST main.cpp MathFunctions.cpp)
aux_source_directory(. SRC_LIST)
message("SRC_LIST: " ${SRC_LIST})

# 查找 math 目录下的所有源文件，并将名称保存到 MATH_SRC_LIST 变量
aux_source_directory(${PROJECT_SOURCE_DIR}/math MATH_SRC_LIST)
message("MATH_SRC_LIST: " ${MATH_SRC_LIST})

# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/math)

# 指示变量 SRC_LIST 中的源文件需要编译成一个名称为 Sample 的可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST} ${MATH_SRC_LIST})