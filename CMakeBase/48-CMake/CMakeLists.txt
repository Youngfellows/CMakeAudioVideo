# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME:${PROJECT_NAME}")

message(STATUS "============ Cmake命令之add_executable  ===============")

#[[
命令格式
    add_executable (<name> [WIN32] [MACOSX_BUNDLE]
          [EXCLUDE_FROM_ALL]
          [source1] [source2 ...])
    add_executable (<name> IMPORTED [GLOBAL])
    add_executable (<name> ALIAS <target>)
    使用指定的源文件来生成目标可执行文件。这里的目标可执行文件分为三类：普通可执行目标文件、导入可执行目标文件、别名可执行目标文件。
    分别对应上面的三种命令格式。
]]

#[[
1.导入可执行目标文件
    add_executable (<name> IMPORTED [GLOBAL])
将工程外部的可执行目标文件导入进来，不会有任何构建可执行目标文件的动作发生。如果不指定GLOBAL，则可执行目标文件的范围为文件创建的目录及子目录；指定GLOBAL则会将范围扩大到整个工程。
IMPORTED选项指定后，属性IMPORTED会被置为TRUE，在工程内构建的可执行目标文件的属性IMPORTED会被置为FALSE。
]]

# 例如，将外部的git导入到当前工程中：
set(GIT_EXECUTABLE "/usr/local/bin/git")
add_executable(Git::Git IMPORTED)
set_property(TARGET Git::Git PROPERTY IMPORTED_LOCATION "${GIT_EXECUTABLE}")
get_target_property(git_location Git::Git IMPORTED_LOCATION)
get_target_property(git_imported Git::Git IMPORTED)
message(">>> git location: ${git_location}, ${git_imported}")