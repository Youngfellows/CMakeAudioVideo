# 设置cmake 支持最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(sample-rgb-to-jpeg)

# 设置C语言支持
set(CMAKE_C_STANDARD 99)

# 设置依赖源文件目录
aux_source_directory(tool TOOL_SRC)

# 设置查找头文件目录
include_directories(tool)

# 生成可执行文件
add_executable(15-rgb-to-jpeg rgb-to-jpeg.c ${TOOL_SRC})

# 查找依赖math库
find_library(LIB_MATH m)
message(STATUS "LIB_MATH:${LIB_MATH}")

# 链接依赖库
target_link_libraries(15-rgb-to-jpeg ${LIB_MATH})

# 安装可执行文件到指定目录
install(TARGETS 15-rgb-to-jpeg DESTINATION bin)