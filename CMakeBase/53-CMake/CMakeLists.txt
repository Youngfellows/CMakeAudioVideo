# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

#[[
1. 查找在某个路径下的所有源文件
    格式：
    aux_source_directory(< dir > < variable >)
    
搜集所有在指定路径下的源文件的文件名，并将输出结果列表储存在指定的变量中。 
]]

# 查找当前目录下的所有源文件,并将名称保存到 SRC_LISTS变量
aux_source_directory(. SRC_LISTS)

# 查找math目录下的所有源文件,并将名称保存到 MATH_SRC_LISTS变量
aux_source_directory(math MATH_SRC_LISTS)
message(STATUS "SRC_LISTS:${SRC_LISTS}")
message(STATUS "MATH_SRC_LISTS:${MATH_SRC_LISTS}")

#[[
2、其他
aux_source_directory(. SRC_LIST)：表示是把当前目录下的所有源文件都添加到源列表变量里面去，最后用add_executable(main ${SRC_LIST})把所有的源文件加工成目标文件main。
不过这方法也有它的缺点，就是把当前目录下的源文件都添加到变量SRC_LIST了。如果我们不需要一些文件，可以进行这样操作：
set(SRC_LIST
        ./main.cpp
        ./test1.cpp
        ./test2.cpp
         )

add_executable(${PROJECT_NAME} ${SRC_LIST})
]]
include_directories(math)
add_executable(${PROJECT_NAME} ${SRC_LISTS} ${MATH_SRC_LISTS})