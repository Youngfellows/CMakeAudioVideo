# 设置cmake支持最新版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(rgb-to-bmp C)

# 设置C语言编译选项
set(CMAKE_C_STANDARD 99)
#set(C_FLAGS  "-Wall")
#set(CMAKE_C_FLAGS ${C_FLAGS})

# 生成可执行文件
add_executable(06-drawing-time-rainbow draw-rainbow.c)
add_executable(06-drawing-time-checkerboard draw-checkerboard.c)
add_executable(06-drawing-time-gradient draw-gradient.c)
add_executable(06-drawing-time-mandelbrot-set draw-mandelbrot-set.c)
add_executable(06-drawing-time-julia-set draw-julia-set.c)
add_executable(06-drawing-time-magnifying-glass draw-magnifying-glass.c)
add_executable(06-drawing-time-swirl-effect draw-swirl-effect.c)
add_executable(06-drawing-time-frosted-glass-effect draw-frosted-glass-effect.c)

# 添加math依赖库
find_library(LIB_MATH m) # 使用默认搜索路径
target_link_libraries(06-drawing-time-mandelbrot-set ${LIB_MATH})
target_link_libraries(06-drawing-time-magnifying-glass ${LIB_MATH})
target_link_libraries(06-drawing-time-swirl-effect ${LIB_MATH})
target_link_libraries(06-drawing-time-frosted-glass-effect ${LIB_MATH})

# 安装可执行文件到指定路径
install(TARGETS 06-drawing-time-rainbow DESTINATION bin)
install(TARGETS 06-drawing-time-checkerboard DESTINATION bin)
install(TARGETS 06-drawing-time-gradient DESTINATION bin)
install(TARGETS 06-drawing-time-mandelbrot-set DESTINATION bin)
install(TARGETS 06-drawing-time-julia-set DESTINATION bin)
install(TARGETS 06-drawing-time-magnifying-glass DESTINATION bin)
install(TARGETS 06-drawing-time-swirl-effect DESTINATION bin)
install(TARGETS 06-drawing-time-frosted-glass-effect DESTINATION bin)

