# cmake 要求最低版本
cmake_minimum_required(VERSION 3.15.0)

# 设置C++编译支持，C++11
set(CMAKE_CXX_STANDARD 11)

# 设置项目名称
project(Sample)
message(STATUS "start build,project:${PROJECT_NAME}")

# 查询源文件
aux_source_directory(. SAMPLE_SRC_LIST)
aux_source_directory(./src BMP_SRC_LIST)
message(STATUS "SAMPLE_SRC_LIST:${SAMPLE_SRC_LIST}")
message(STATUS "BMP_SRC_LIST:${BMP_SRC_LIST}")

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SAMPLE_SRC_LIST} ${BMP_SRC_LIST})

# 设置搜索头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/bitmap)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/bmpstruct)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/rainbow)

# 安装生成目标到指定目录
message(STATUS "install,${CMAKE_INSTALL_PREFIX}")
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
