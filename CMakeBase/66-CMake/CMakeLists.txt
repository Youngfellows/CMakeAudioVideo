# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)

# 添加包含子目录
add_subdirectory(math)

# 查找原文件
aux_source_directory(. SRC_LISTS)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LISTS})

# 添加头文件目录
# include_directories(${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 查找链接库MathFunctions
set (CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/math/lib")
find_library (MyMathFunctions NAMES MathFunctions PATHS ${CMAKE_LIBRARY_PATH})

# 链接对象库 - 动态库
target_link_libraries(${PROJECT_NAME} ${MyMathFunctions})

