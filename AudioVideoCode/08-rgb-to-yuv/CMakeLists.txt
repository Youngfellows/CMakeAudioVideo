# 设置cmake支持的最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称及C语言支持
project(rgb-to-bmp C)
set(CMAKE_C_STANDARD 99)

# 生成可执行文件
add_executable(08-rgb24-to-yuv444 rgb24-to-yuv444.c)
add_executable(08-rgb24-to-yuv420 rgb24-to-yuv420.c)
add_executable(08-yuv444-to-rgb24 yuv444-to-rgb24.c)
add_executable(08-yuv444-to-yuv420 yuv444-to-yuv420.c)
add_executable(08-yuv420-to-yuv444 yuv420-to-yuv444.c)

# 添加math依赖库
find_library(LIB_MATH m) # 使用默认搜索路径
target_link_libraries(08-rgb24-to-yuv444 ${LIB_MATH})
target_link_libraries(08-rgb24-to-yuv420 ${LIB_MATH})
target_link_libraries(08-yuv444-to-rgb24 ${LIB_MATH})
target_link_libraries(08-yuv444-to-yuv420 ${LIB_MATH})
target_link_libraries(08-yuv420-to-yuv444 ${LIB_MATH})

# 安装可执行文件到指定目录
install(TARGETS 08-rgb24-to-yuv444 DESTINATION bin)
install(TARGETS 08-rgb24-to-yuv420 DESTINATION bin)
install(TARGETS 08-yuv444-to-rgb24 DESTINATION bin)
install(TARGETS 08-yuv444-to-yuv420 DESTINATION bin)
install(TARGETS 08-yuv420-to-yuv444 DESTINATION bin)