cmake_minimum_required(VERSION 3.15.0)

project(MathFunctions)

# 查找当前目录下的所有源文件，并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

#[[
同时编译静态库与动态库
同样使用上面的指令，我们在支持动态库的基础上再为工程添加一个静态库，按照一般的习
惯，静态库名字跟动态库名字应该是一致的，只不过后缀是.a 罢了。

下面我们用这个指令再来添加静态库：
    add_library(mymath STATIC mymath.cc)
然后再在 build 目录进行外部编译，我们会发现，静态库根本没有被构建，仍然只生成了
一个动态库。因为mymath 作为一个 target 是不能重名的，所以，静态库构建指令无效。

如果我们把上面的 mymath 修改为 mymath _static:
    add_library(mymath_static STATIC mymath.cc)
就可以构建一个 libmymath_static.a 的静态库了。

这种结果显示不是我们想要的，我们需要的是名字相同的静态库和动态库，因为 target 名
称是唯一的，所以，我们肯定不能通过 ADD_LIBRARY 指令来实现了。这时候我们需要用到
另外一个指令：
SET_TARGET_PROPERTIES，其基本语法是：
    SET_TARGET_PROPERTIES(target1 target2 ...
    PROPERTIES prop1 value1
    prop2 value2 ...)
这条指令可以用来设置输出的名称，对于动态库，还可以用来指定动态库版本和 API 版本

]]

# 生成链接库 - 同时编译静态库与动态库
add_library(${PROJECT_NAME} SHARED ${DIR_LIB_SRCS})

# VERSION 指代动态库版本，SOVERSION 指代 API 版本
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION 1.2 SOVERSION 1)

message(STATUS "CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")

# 指定动态库依赖的头文件,这样在main.cpp中就不用引用全路径了:"include/MathFunctions.h",只需要"MathFunctions.h"
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/include/MathFunctions.h)

# 如果同时要生成静态库
add_library(my_math_static STATIC ${DIR_LIB_SRCS})
SET_TARGET_PROPERTIES(my_math_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
