# 设置cmake最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(22-hash-library)

# 设置C++语言支持
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 该命令会查找指定目录下的所有源文件，然后将结果存进指定变量名
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/hash-library HASH_LIBRARY_SRC)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/hash-library)

# 生成可执行文件
add_executable(digest-hash-library ${HASH_LIBRARY_SRC})
list(REMOVE_ITEM HASH_LIBRARY_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/hash-library/digest.cpp")
add_executable(test-hash-library ${CMAKE_CURRENT_SOURCE_DIR}/src/hash-library/tests/tests.cpp ${HASH_LIBRARY_SRC})

# 安装到指定路径
install(TARGETS digest-hash-library DESTINATION bin)
install(TARGETS test-hash-library DESTINATION bin)
