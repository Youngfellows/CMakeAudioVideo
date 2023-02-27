# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "======= CMakeLists编译动态库 ========")

# 生成静态库
add_subdirectory(math)

# 查找源文件
aux_source_directory(. SRC_LISTS)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LISTS})

# 添加链接库文件
target_link_libraries(${PROJECT_NAME} MathFunctions)

# 指定可执行文件依赖的头文件
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
