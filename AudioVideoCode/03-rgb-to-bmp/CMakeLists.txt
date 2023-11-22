# 设置cmake依赖最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称和C语言支持
project(rgb-to-bmp C)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 生成可执行文件
add_executable(03-rgb-to-bmp main.c)
add_executable(03-rgb-to-bmp-test save-bmp-test.c)

# 安装可执行文件
install(TARGETS 03-rgb-to-bmp DESTINATION bin)
install(TARGETS 03-rgb-to-bmp-test DESTINATION bin)