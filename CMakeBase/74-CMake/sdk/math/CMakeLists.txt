# 设置项目名称(库名称)
project(MathFunctions)

# 查找当前目录下的所有源文件
aux_source_directory(./src MATH_SRC_LIST)

# 生成动态库
add_library(${PROJECT_NAME} SHARED ${MATH_SRC_LIST})

# 头文件安装路径
install(DIRECTORY ./src/ 
    DESTINATION include/sdk/math 
    FILES_MATCHING PATTERN "*.h"
)

# 动态库安装路径
install(TARGETS ${PROJECT_NAME} 
    DESTINATION lib)