# cmake要求最低版本
cmake_minimum_required(VERSION 3.12.1)

# 项目名称
project(Sample)
message(STATUS "start build,project name:${PROJECT_NAME}")

# 启动对C++14标准的支持
set(CMAKE_CXX_STANDARD 14)

# 显式要求指明支持C++标准
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 启动对C11标准的支持
set(CMAKE_C_STANDARD 11)

# 显式要求指明支持C标准
set(CMAKE_C_STANDARD_REQUIRED True)

# 依赖头文件
include_directories(${CMAKE_SOURCE_DIR}/include/array)

# 库文件链接路径
message(STATUS "link_directories:${CMAKE_INSTALL_PREFIX}")

# link_directories(${CMAKE_INSTALL_PREFIX}/lib)
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dist/lib)

# 查找源文件
aux_source_directory(. EXAMPLE_SRC_LIST)

# aux_source_directory(./src/array ARRAY_SRC_LIST)

# 生成可执行文件
# add_executable(${PROJECT_NAME} ${EXAMPLE_SRC_LIST} ${ARRAY_SRC_LIST})
add_executable(${PROJECT_NAME} ${EXAMPLE_SRC_LIST})

# 查找链接库easyarray并连接
set(EASY_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dist/lib)
find_library(lib-easyarray NAMES easyarray PATHS ${EASY_LIB_PATH})
message(STATUS "easyarray,path:${lib-easyarray}")

target_link_libraries(${PROJECT_NAME} ${lib-easyarray})

# 指定可执行文件安装路径
install(TARGETS ${PROJECT_NAME} DESTINATION bin)