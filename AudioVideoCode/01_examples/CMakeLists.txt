# cmake要求最低版本
cmake_minimum_required(VERSION 3.15.0)

# 项目名称
project(Sample)
message(STATUS "start build,project name:${PROJECT_NAME}")

# 依赖头文件

# 查找源文件
aux_source_directory(. EXAMPLE_SRC_LIST)
aux_source_directory(./src ARRAY_SRC_LIST)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${EXAMPLE_SRC_LIST} ${ARRAY_SRC_LIST})

# 指定可执行文件安装路径
message(STATUS "install,${CMAKE_INSTALL_PREFIX}")
install(TARGETS ${PROJECT_NAME} DESTINATION bin)