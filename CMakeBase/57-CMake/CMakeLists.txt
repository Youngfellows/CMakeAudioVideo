# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "========== CMake的add_library与target_link_libraries ============")

# CMake的add_library与target_link_libraries
#[[
一、add_library介绍
使用该命令可以在Linux下生成（静态/动态）库so或者.a文件，Windows下就是dll与lib文件，它有两种命令格式

1.1 第一种格式 ：
Normal Libraries，add_library命令的格式为
    add_library(<name> [STATIC | SHARED | MODULE]
                [EXCLUDE_FROM_ALL]
                [<source>...])
生成一个名为 < name > 的library，注意以下规则：

< name > 应该保证在一个项目中的唯一性。
实际生成的library文件名是基于平台的约定规则，比如linux下的lib< name >.a， Windows下的< name >.lib等
    STATIC,SHARED,MODULE用于指定创建的library类型。
    STATIC库：生成obj文件后，将其链接成静态库，用于链接到其他targets。
    SHARED库：生成obj文件后，将其链接成动态库，用于运行时加载。
    MODULE库：不能链接到其他targets，但是可以用dlopen之类的方法在运行时动态加载。
    如果没有明确指定要生成的library的类型到底是STATIC,SHARED还是MODULE。则查看BUILD_SHARED_LIBS变量，如果值为ON，则默认是SHARED，否则默认STATIC。
    对于SHARED和MODULE类型的库，POSITION_INDEPENDENT_CODE属性自动置为ON。
    EXCLUDE_FROM_ALL：表明该target是否从默认构建target中排除。
    source参数可以使用generator表达式（$ <…>）。
 
1.2 第二种格式 ：
生成一个obj文件对象，该对象库只编译源文件，但不链接。
    add_library(<name> OBJECT [<source>...])
由add_library()或 add_executable()创建的目标可以使用$<TARGET_OBJECTS:name>这样的表达式作为源引用对象，其中，name是对象库的名称。格式如下:
add_library(... $<TARGET_OBJECTS:name> ...)
add_executable(... $<TARGET_OBJECTS:name> ...)
]]

#[[
二、target_link_libraries的介绍
指定链接给定目标和/或其依赖项时要使用的库。命名的<tartget>必须是由add_executable()或add_library()之类的命令创建的。一般与 link_directories连用（添加外部库的搜索路径 ）

target_link_libraries命令的格式
    target_link_libraries(<target> ... <item>... ...)
]]
# 添加包含子目录
add_subdirectory(math)

# 查找原文件
aux_source_directory(. SRC_LISTS)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LISTS})

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 链接对象库 - 动态库
target_link_libraries(${PROJECT_NAME} MathFunctions)
