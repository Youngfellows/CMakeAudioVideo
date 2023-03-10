# 设置cmake 最新版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(rgb-to-bmp)

# 设置C++编译支持，C++11
set(CMAKE_CXX_STANDARD 11)

# 生成可执行文件
#add_executable(05-rgb-to-bmp-with-easybmp-test EasyBMPsample.cpp EasyBMP/EasyBMP.cpp)
add_executable(05-rgb-to-bmp-with-easybmp 05-rgb-to-bmp-with-easybmp.cpp EasyBMP/EasyBMP.cpp)
add_executable(05-rgb-to-bmp-with-bitmap 05-rgb-to-bmp-with-bitmap.cpp)

# 可执行文件安装到指定目录
install(TARGETS 05-rgb-to-bmp-with-easybmp DESTINATION bin)
install(TARGETS 05-rgb-to-bmp-with-bitmap DESTINATION bin)