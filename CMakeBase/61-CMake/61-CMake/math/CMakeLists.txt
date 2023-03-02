
cmake_minimum_required(VERSION 3.15.0)

project(MathFunctions)


# 查找当前目录下的所有源文件，并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库,不链接
add_library(${PROJECT_NAME} SHARED ${DIR_LIB_SRCS})
# add_library(${PROJECT_NAME} SHARED ${DIR_LIB_SRCS})
 
# 安装Obj文件，有设置目录,输出到Output目录下
#install(TARGETS ${PROJECT_NAME} OBJECTS DESTINATION ${CMAKE_CURRENT_SOURCE}/output)
 
# 安装Obj文件，没有设置目录，直接输出到路径
#install(FILES $<TARGET_OBJECTS:${PROJECT_NAME}> DESTINATION ${CMAKE_CURRENT_SOURCE}/output)

#生成文件到指定位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#install 安装文件到指定位置
#install(TARGETS hello_shared LIBRARY DESTINATION /usr/local/lib)
#install(FILES ${PROJECT_SOURCE_DIR}/include/libHelloSLAM.h DESTINATION /usr/local/include)
