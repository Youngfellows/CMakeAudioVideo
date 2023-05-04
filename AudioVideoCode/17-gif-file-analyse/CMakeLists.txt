# 设置cmake最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(gif-file-analyse)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 设置依赖和头文件查找
aux_source_directory(lzw/src LZW_SRC)
include_directories(lzw)

# 生成可执行文件
add_executable(17-gif-file-analyse gif-file-analyse.c ${LZW_SRC})

# 安装到指定目录
install(TARGETS 17-gif-file-analyse DESTINATION bin)