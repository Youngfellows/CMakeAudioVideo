# 查找当前目录下的所有源文件，并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成动态链接库
add_library(MathFunctions SHARED ${DIR_LIB_SRCS})

# 安装动态链接库到指定目录
install(TARGETS MathFunctions DESTINATION lib/math)

# 安装头文件到指定路径CMAKE_INSTALL_PREFIX/include/math
message(STATUS "SDK,CMAKE_INSTALL_PREFIX:${CMAKE_INSTALL_PREFIX}")
install(DIRECTORY .
    DESTINATION include/math
    FILES_MATCHING PATTERN "*.h"
)