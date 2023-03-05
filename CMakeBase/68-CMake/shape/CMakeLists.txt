
cmake_minimum_required(VERSION 3.15.0)

# 设置项目名称(库名称)
project(Shape)

# 查找当前目录下的所有源文件，并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库,不链接
add_library(${PROJECT_NAME} SHARED ${DIR_LIB_SRCS})

# 生成文件到指定位置, 静态库 lib 输出路径
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../../lib)
message(STATUS "LIBRARY_OUTPUT_PATH:${LIBRARY_OUTPUT_PATH}")
