# 设置库名称
project(MathFunctions)

# 查找当前目录下的所有源文件，并将名称保存到 MATH_SRC_LIST 变量
aux_source_directory(./src MATH_SRC_LIST)

# 生成链接库
add_library(${PROJECT_NAME} SHARED ${MATH_SRC_LIST})

# 添加头文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 安装头文件到指定路径CMAKE_INSTALL_PREFIX/include/sdk/math
message(STATUS "SDK,CMAKE_INSTALL_PREFIX:${CMAKE_INSTALL_PREFIX}")
install(DIRECTORY ./include/
    DESTINATION include/sdk/math
    FILES_MATCHING PATTERN "*.h"
)

# 安装动态库文件到指定路径CMAKE_INSTALL_PREFIX/lib
install(TARGETS ${PROJECT_NAME}
    DESTINATION lib
)