# 设置项目名称(库名称)
project(Shape)

# 查找当前目录下的所有源文件
aux_source_directory(./src SHAPE_SRC_LIST)

# 生成动态库
add_library(${PROJECT_NAME} SHARED ${SHAPE_SRC_LIST})

# 头文件安装路径
install(DIRECTORY ./src/ 
    DESTINATION include/sdk/shape 
    FILES_MATCHING PATTERN "*.h"
)

# 动态库安装路径
install(TARGETS ${PROJECT_NAME} 
    DESTINATION lib)