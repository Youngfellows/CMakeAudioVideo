# 设置cmake最低版本要求
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(rgb-to-bmp)

# 设置C++ 11编译选项
set(CMAKE_CXX_STANDARD 11)

# 生成可执行文件
add_executable(06-drawing-time-maze draw-maze.cpp)
add_executable(06-drawing-time-fireballs draw-fireballs.cpp)
add_executable(06-drawing-time-sierpinski-triangle draw-sierpinski-triangle.cpp)
add_executable(06-drawing-time-circles-equilateral-riangles draw-circles-equilateral-riangles.cpp)
add_executable(06-drawing-time-archimedean-spirals draw-archimedean-spirals.cpp)
add_executable(06-drawing-time-image-huffle draw-image-huffle.cpp)
add_executable(06-drawing-time-phyllotaxis-spiral draw-phyllotaxis-spiral.cpp)
add_executable(06-drawing-time-pointillism-effect draw-pointillism-effect.cpp)

# 安装可执行文件到指定目录
install(TARGETS 06-drawing-time-maze DESTINATION bin)
install(TARGETS 06-drawing-time-fireballs DESTINATION bin)
install(TARGETS 06-drawing-time-sierpinski-triangle DESTINATION bin)
install(TARGETS 06-drawing-time-circles-equilateral-riangles DESTINATION bin)
install(TARGETS 06-drawing-time-archimedean-spirals DESTINATION bin)
install(TARGETS 06-drawing-time-image-huffle DESTINATION bin)
install(TARGETS 06-drawing-time-phyllotaxis-spiral DESTINATION bin)
install(TARGETS 06-drawing-time-pointillism-effect DESTINATION bin)