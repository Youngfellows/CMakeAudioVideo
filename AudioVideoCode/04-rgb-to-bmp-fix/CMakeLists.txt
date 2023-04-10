# 设置cmake 最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称和C语言支持
project(rgb-to-bmp C)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 生成可执行文件
add_executable(04-rgb-to-bmp-fix main.c)
add_executable(04-rgb-to-bmp-fix-test rgb-to-bmp-fix-test.c)

# 安装可执行文件
install(TARGETS 04-rgb-to-bmp-fix DESTINATION bin)
install(TARGETS 04-rgb-to-bmp-fix-test DESTINATION bin)