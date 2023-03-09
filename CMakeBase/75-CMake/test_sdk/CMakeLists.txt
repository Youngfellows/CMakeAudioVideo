# 设置最低版本要求
cmake_minimum_required(VERSION 3.15.0)

# 设置项目名称
project(MathSdkSample)

# 设置依赖的头文件
message(STATUS "SDK_INSTALL_PATH:${SDK_INSTALL_PATH}")
include_directories(${SDK_INSTALL_PATH}/include/sdk/math)

# 设置源文件列表
aux_source_directory(./src TEST_SRC_LIST)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${TEST_SRC_LIST})

# 添加依赖库,并链接
#[[
set(DEP_LIBS
	${SDK_INSTALL_PATH}/lib/libMathFunctions.so
	)
target_link_libraries(${PROJECT_NAME})
]]

# 查找链接库文件
set(CMAKE_LIBRARY_PATH "${SDK_INSTALL_PATH}/lib")
find_library(MyMathFunctions MathFunctions) # 使用默认搜索路径
message(STATUS "MyMathFunctions:${MyMathFunctions}")

# 链接对象库 - 动态库
target_link_libraries(${PROJECT_NAME} ${MyMathFunctions})

# 安装可执行文件到指定目录
install(TARGETS ${PROJECT_NAME}
    DESTINATION bin)
