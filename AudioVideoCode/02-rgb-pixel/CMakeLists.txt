# cmake 支持最小版本
cmake_minimum_required(VERSION 3.14)

# 项目名称和C语言支持
project(rgb-pixel C)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 生成可执行文件
add_executable(02-rgb-pixel main.c)

# 安装可执行文件到指定目录
install(TARGETS 02-rgb-pixel DESTINATION bin)