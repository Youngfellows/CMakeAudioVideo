# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)

message(STATUS "================= make命令之find_library介绍 ===================")
#[[
一、命令格式
  该命令用于查找库（动态库或者静态库），当构建依赖于第三方库/系统库，可以使用该命令来查找并使用库（Cmake中有另外一个命令find_package，
能获取库的更多信息，具体可以参考Cmake命令之find_package介绍）

简洁的格式
    find_library (<VAR> name [path1 path2 ...])
]]

# 通用的格式
#    find_library ( <VAR> name | NAMES name1 [name2 ...] [NAMES_PER_DIR] [HINTS [path | ENV var]... ]
#     [PATHS [path | ENV var]... ] [PATH_SUFFIXES suffix1 [suffix2 ...]] 
#     [DOC "cache documentation string"] [NO_CACHE] [REQUIRED] [NO_DEFAULT_PATH] 
#     [NO_PACKAGE_ROOT_PATH] [NO_CMAKE_PATH] [NO_CMAKE_ENVIRONMENT_PATH] [NO_SYSTEM_ENVIRONMENT_PATH] 
#     [NO_CMAKE_SYSTEM_PATH] [CMAKE_FIND_ROOT_PATH_BOTH | ONLY_CMAKE_FIND_ROOT_PATH | NO_CMAKE_FIND_ROOT_PATH] )

#[[
几个基本参数的解析：
    <var>用于存储该命令执行的结果，也就是找到的库的全路径（包含库名）:
     1. <var>可以是普通变量（需要指定NO_CACHE选项），也可以是缓存条目（意味着会存放在CMakeCache.txt中，不删除该文件或者用set重新设置该变量，其存储的值不会再刷新）；
     2. 当库能被找到，<var>会被存放正常的库路径，当库未被找到，<var>中存放的值为"<var>-NOTFOUND"。只要<var>中的值不是"<var>-NOTFOUND"，那么即使多次调用find_library，<var>也不会再刷新;
    name用于指定待查找的库名称，库名称可以使用全称，例如libmymath.a（优先会当成全名搜索）；也可以不带前缀（例如前缀lib）和后缀（例如Linux中的.so、.a，Mac中的.dylib等），直接使用mymath；
    path用于指定库的查找的路径；
]]


# 设置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output)

# 添加包含子目录
add_subdirectory(math)

# 查找原文件
aux_source_directory(. SRC_LISTS)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LISTS})

# 添加头文件目录
# include_directories(${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 查找链接库MathFunctions
#set (CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/math/lib")
set (CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/lib")
# find_library(MyMathFunctions NAMES MathFunctions PATHS ${CMAKE_LIBRARY_PATH})
# find_library(MyShape NAMES Shape PATHS ${CMAKE_LIBRARY_PATH})
find_library(MyMathFunctions NAMES MathFunctions HINTS ${CMAKE_LIBRARY_PATH})
find_library(MyShape NAMES Shape HINTS ${CMAKE_LIBRARY_PATH})

# 链接对象库 - 动态库
target_link_libraries(${PROJECT_NAME} ${MyMathFunctions} ${MyShape})

