# 设置cmake最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(rgb-to-gif)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 依赖源码和头文件查找路径
aux_source_directory(../17-gif-file-analyse/lzw/src LZW_SRC)
include_directories(../17-gif-file-analyse/lzw)

# 生成可执行文件
add_executable(18-rgb-to-gif rgb-to-gif.c ${LZW_SRC})

# 安装可执行文件
install(TARGETS 18-rgb-to-gif DESTINATION bin)