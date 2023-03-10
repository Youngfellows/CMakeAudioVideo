# 设置cmake要求最新版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(rgb-to-bmp C)

# 设置C语言编译选项
set(CMAKE_C_STANDARD 99)

# 生成可执行文件
add_executable(05-rgb-to-bmp-with-libbmp rgb-to-bmp-with-libbmp.c libbmp/libbmp.c)
add_executable(05-rgb-to-bmp-with-bmp rgb-to-bmp-with-bmp.c)
add_executable(05-rgb-to-bmp-with-google-libbmp rgb-to-bmp-with-google-libbmp.c google/libbmp/src/bmpfile.c)
add_executable(05-rgb-to-bmp-with-qdbmp rgb-to-bmp-with-qdbmp.c qdbmp/qdbmp.c)

# 安装可执行文件到指定目录
install(TARGETS 05-rgb-to-bmp-with-libbmp DESTINATION bin)
install(TARGETS 05-rgb-to-bmp-with-bmp DESTINATION bin)
install(TARGETS 05-rgb-to-bmp-with-google-libbmp DESTINATION bin)
install(TARGETS 05-rgb-to-bmp-with-qdbmp DESTINATION bin) 