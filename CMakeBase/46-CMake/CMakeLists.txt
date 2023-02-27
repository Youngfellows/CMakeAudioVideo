# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "============= Cmake命令之add_subdirectory ===============")

#[[
1.命令格式
    add_subdirectory (source_dir [binary_dir] [EXCLUDE_FROM_ALL])
添加一个子目录并构建该子目录。

2.命令解析
source_dir
    必选参数。该参数指定一个子目录，子目录下应该包含CMakeLists.txt文件和代码文件。子目录可以是相对路径也可以是绝对路径，如果是相对路径，则是相对当前目录的一个相对路径。
binary_dir
    可选参数。该参数指定一个目录，用于存放输出文件。可以是相对路径也可以是绝对路径，如果是相对路径，则是相对当前输出目录的一个相对路径。如果该参数没有指定，则默认的输出目录使用source_dir。
EXCLUDE_FROM_ALL
    可选参数。当指定了该参数，则子目录下的目标不会被父目录下的目标文件包含进去，父目录的CMakeLists.txt不会构建子目录的目标文件，必须在子目录下显式去构建。例外情况：当父目录的目标依赖于子目录的目标，则子目录的目标仍然会被构建出来以满足依赖关系（例如使用了target_link_libraries）。
]]

# 场景1：父目录CMakeLists.txt的add_subdirectory 只指定了source_dir
# add_subdirectory(math)
#[[
在父目录下调用cmake .构建之后，在sub目录下会出现libsub.a库，说明当不指定binary_dir，输出目标文件就会放到source_dir目录下。
]]

# 场景2：父目录CMakeLists.txt的add_subdirectory 指定了source_dir和binary_dir。
# add_subdirectory(math output)

#[[
在父目录下调用cmake .构建之后，在output目录下会出现libsub.a库，sub目录下则没有libsub.a。说明当指定binary_dir，输出目标文件就会放到binary_dir目录下
]]

# 场景3：父目录CMakeLists.txt的add_subdirectory 指定了EXCLUDE_FROM_ALL选项。
# 在父目录下调用cmake .构建之后，在output目录或sub目录下不会出现libsub.a库，说明当指定EXCLUDE_FROM_ALL选项，子目录的目标文件不会生成。

# 场景4：父目录CMakeLists.txt的add_subdirectory 指定了EXCLUDE_FROM_ALL选项，且父目录的目标文件依赖子目录的目标文件。
add_subdirectory(math output EXCLUDE_FROM_ALL)

# 在父目录下调用cmake .构建之后，在output目录会出现libsub.a库，说明即使指定EXCLUDE_FROM_ALL选项，当父目录目标文件对子目录目标文件存在依赖关系时，子目录的目标文件仍然会生成以满足依赖关系。
include_directories(math)
aux_source_directory(. SRC_LISTS)
add_executable(${PROJECT_NAME} ${SRC_LISTS})
target_link_libraries(${PROJECT_NAME} MathFunctions)