# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
aux_source_directory(. SRC_LISTS)
message(STATUS "SRC_LISTS: ${SRC_LISTS}")
add_subdirectory(math)
include_directories(${PROJECT_SOURCE_DIR}/math)
add_executable(${PROJECT_NAME} ${SRC_LISTS})
target_link_libraries(${PROJECT_NAME} MathFunctions)