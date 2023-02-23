# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "================ 文件系统(Filesystem) ================")
message(STATUS "================ 搜索文件 ================")

#[[
1.1 搜索文件
    file(GLOB <variable>
        [LIST_DIRECTORIES true|false] [RELATIVE <path>] [CONFIGURE_DEPENDS]
        [<globbing-expressions>...])
    file(GLOB_RECURSE <variable> [FOLLOW_SYMLINKS]
        [LIST_DIRECTORIES true|false] [RELATIVE <path>] [CONFIGURE_DEPENDS]
        [<globbing-expressions>...])

GLOB 模式仅搜索当前目录，而 GLOB_RECURSE 模式会递归搜索目录或所有子目录。只有在给定 FOLLOW_SYMLINKS 或策略 CMP0009 未设置为 NEW 时，才会遍历作为符号链接的子目录。
搜索文件，根据 <globbing-expressions> glob 表达式 匹配文件名，并将文件列表存储在变量 <variable>。
如果指定 RELATIVE 标志，结果作为该路径的相对路径返回。
如果指定了 CONFIGURE_DEPENDS 标志，CMake 将向主构建系统检查目标添加逻辑，以在构建时重新运行标记的 GLOB 命令。 如果任何输出发生变化，CMake 将重新生成构建系统。
默认情况下会列出目录，如果指定 LIST_DIRECTORIES 设置为 false，则搜索的结果并不输出。

请注意，不建议使用 GLOB 收集源文件列表。如果添加或删除源文件时，并没有在 CMakeLists.txt 文件更改，则生成的构建系统无法直到何时要求 CMake 重新生成。
CONFIGURE_DEPENDS 标志可能无法在所有生成器上可靠地工作，或者如果将来添加了不能支持它的新生成器，使用它的项目将被卡住。 
即使 CONFIGURE_DEPENDS 工作可靠，在每次重建时执行检查仍然存在成本。

<globbing-expressions> glob 表达式，包括：
*.cxx      - match all files with extension cxx
*.vt?      - match all files with extension vta,...,vtz
f[3-5].txt - match files f3.txt, f4.txt, f5.txt
The GLOB_RECURSE mode will traverse all the subdirectories of the matched directory and match the files. Subdirectories that are symlinks are only traversed if FOLLOW_SYMLINKS is given or policy CMP0009 is not set to NEW.

例，按当前目录中所有的 .cpp 文件，获取绝对路径的文件列表:
    file(GLOB FILE_LISTS *.cpp)
    file(GLOB INCLUDE_FILE_LISTS include/*.h)
    file(GLOB_RECURSE SRC_FILE_LISTS src/*.cpp)
]]
file(GLOB FILE_LISTS *.cpp)
file(GLOB FILE_FILE_LISTS file/*.txt)
file(GLOB INCLUDE_FILE_LISTS math/*.h)
file(GLOB MATH_FILE_LISTS math/*.cpp)
file(GLOB_RECURSE SRC_LISTS *.cpp)
message(STATUS "FILE_LISTS:${FILE_LISTS}")
message(STATUS "FILE_FILE_LISTS:${FILE_FILE_LISTS}")
message(STATUS "INCLUDE_FILE_LISTS:${INCLUDE_FILE_LISTS}")
message(STATUS "MATH_FILE_LISTS:${MATH_FILE_LISTS}")
message(STATUS "SRC_LISTS:${SRC_LISTS}")

message(STATUS "============== 文件重命名 ==============")

#[[
1.2 文件重命名
    file(RENAME <oldname> <newname>)

重命名文件或目录。

例，将当前目录下 main.cpp 重命名为 hello.cp
    file(RENAME main.cpp hello.cpp)
]]
set(fileName1 "${PROJECT_SOURCE_DIR}/file/appinfo.txt")
set(fileName2 "${PROJECT_SOURCE_DIR}/file/newappinfo.txt")

if(EXISTS ${fileName1})
    file(RENAME ${fileName1} ${fileName2})
elseif(EXISTS ${fileName2})
    file(RENAME ${fileName2} ${fileName1})
endif()

message(STATUS "================ 删除文件和目录 ==================")

#[[
1.3 文件删除
    file(REMOVE [<files>...])
    file(REMOVE_RECURSE [<files>...])

REMOVE 模式仅删除文件，REMOVE_RECURSE 模式删除文件和目录(空目录和非空目录)。如果不存在，则不会发出错误。

例，删除当前目录下 main.cpp 文件, src 目录, include 目录
    file(REMOVE hello.cpp)
    file(REMOVE_RECURSE src)
    file(REMOVE_RECURSE include)
]]
set(fileName "file/kungfu1.txt")
file(REMOVE ${fileName})
file(REMOVE_RECURSE "file/artical")

message(STATUS "================ 创建目录 ===================")

#[[
1.4 创建目录
    file(MAKE_DIRECTORY [<directories>...])
根据需要创建给定的目录及其父目录。

例，创建目录 core 和 父目录 src
    file(MAKE_DIRECTORY src/core)
]]
set(MY_DIRECTORY src/java/com/tiffany/cmake)
file(MAKE_DIRECTORY ${MY_DIRECTORY})

message(STATUS "============== 文件复制与安装 ===============")

# 1.5 文件复制与安装
# file(<COPY|INSTALL> <files>... DESTINATION <dir>
# [FILE_PERMISSIONS <permissions>...]
# [DIRECTORY_PERMISSIONS <permissions>...]
# [NO_SOURCE_PERMISSIONS] [USE_SOURCE_PERMISSIONS]
# [FOLLOW_SYMLINK_CHAIN]
# [FILES_MATCHING]
# [[PATTERN <pattern> | REGEX <regex>]
# [EXCLUDE] [PERMISSIONS <permissions>...]] [...])
#[[
COPY 签名，将文件、目录和符号链接复制到 DESTINATION 目标文件夹。<files> 文件路径为当前目录，<dir> 输出目录为 CMAKE_BINARY_DIR 变量路径。
输出文件时间戳 和 权限都与输入文件相同。权限选项默认为 USE_SOURCE_PERMISSIONS 与源相同，NO_SOURCE_PERMISSIONS 不使用源的权限。FILE_PERMISSIONS 和 DIRECTORY_PERMISSIONS。
如果指定 FOLLOW_SYMLINK_CHAIN 选项，当遇到符号链接时，会找到真正的文件，并在目标中为遇到的每个符号链接安装相应的符号链接。

例，将所有符号链接和 libfoo.so.1.2.3 本身安装到 lib 目录中。
目录结构为
/opt/foo/lib/libfoo.so.1.2 -> libfoo.so.1.2.3
/opt/foo/lib/libfoo.so.1 -> libfoo.so.1.2
/opt/foo/lib/libfoo.so -> libfoo.so.1
然后做
file(COPY /opt/foo/lib/libfoo.so DESTINATION lib FOLLOW_SYMLINK_CHAIN)

关于 PERMISSIONS、FILES_MATCHING、PATTERN、REGEX 和 EXCLUDE 选项的文档，请参阅 install(DIRECTORY) 命令。 即使使用选项来选择文件的子集，复制目录也会保留其内容的结构。
INSTALL 签名 与 COPY 签名 略有不同：它打印状态消息（取决于 CMAKE_INSTALL_MESSAGE 变量），并且 NO_SOURCE_PERMISSIONS 是默认值。install() 命令，生成的安装脚本使用此签名（带有一些未公开的供内部使用的选项）。
]]
message(STATUS "================= 文件大小 ====================")

#[[
1.6 文件大小
    file(SIZE <filename> <variable>)

Determine the file size of the and put the result in variable. Requires that is a valid path pointing to a file and is readable.
确定 <filename> 的文件大小，将结果放入 <variable> 变量中。

注意，路径为绝对路径

例，
    file(SIZE ${CMAKE_SOURCE_DIR}/main.cpp FILE_SIZE)
]]
set(fileName "file/kungfu2.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)
file(SIZE ${fileName} fileSize)
message(STATUS "fileSize:${fileSize}")

message(STATUS "=============== 创建文件符号链接 ===============")

#[[
1.7 创建文件符号链接
    file(CREATE_LINK <original> <linkname> [RESULT <result>] [COPY_ON_ERROR] [SYMBOLIC])
创建 <original> 文件的链接 <linkname>。若成功创建将 <result> 设置为 0，否则操作失败。

默认情况下，创建的是硬链接，使用 SYMBOLIC 选项，是创建符号链接。硬链接要求 <original> 文件，为 文件，而不是 目录。
若 COPY_ON_ERROR 选项启用，如果链接创建失败，将复制文件作为后被操作。

注意，路径为绝对路径

例，创建文件 main.cpp 的硬链接，目录 src 的软链接，结果输出到 CMAKE_BINARY_DIR 变量路径
    file(CREATE_LINK ${CMAKE_SOURCE_DIR}/main.cpp main.1.cpp)
    file(CREATE_LINK ${CMAKE_SOURCE_DIR}/src src.1 SYMBOLIC)
]]
set(original "${CMAKE_SOURCE_DIR}/main.cpp")
set(linkname "${CMAKE_SOURCE_DIR}/main.1.cpp")
file(CREATE_LINK ${original} ${linkname} SYMBOLIC) # 软链接

#[[
1.8 查询文件符号链接
    file(READ_SYMLINK <linkname> <variable>)
将符号链接 <linkname> 的真实路径存储在 <variable> 中。

例，确保获得绝对路径
    set(linkname "/path/to/foo.sym")
    file(READ_SYMLINK "${linkname}" result)
    if(NOT IS_ABSOLUTE "${result}")
        get_filename_component(dir "${linkname}" DIRECTORY)
        set(result "${dir}/${result}")
    endif()
]]
set(linkname "${CMAKE_SOURCE_DIR}/main.1.cpp")
file(READ_SYMLINK "${linkname}" result)

if(NOT IS_ABSOLUTE ${result})
    get_filename_component(dir ${linkname} DIRECTORY)
    set(result "${dir}/${result}")
else()
    message(STATUS "result:${result}")
endif()

#[[
1.9 文件权限
file(CHMOD <files>... <directories>...
    [PERMISSIONS <permissions>...]
    [FILE_PERMISSIONS <permissions>...]
    [DIRECTORY_PERMISSIONS <permissions>...])
file(CHMOD_RECURSE <files>... <directories>...
    [PERMISSIONS <permissions>...]
    [FILE_PERMISSIONS <permissions>...]
    [DIRECTORY_PERMISSIONS <permissions>...])

更改 <files>... 和 <directories>... 权限。有效权限为 OWNER_READ, OWNER_WRITE, OWNER_EXECUTE, GROUP_READ, GROUP_WRITE, GROUP_EXECUTE, WORLD_READ, WORLD_WRITE, WORLD_EXECUTE。

选项有效的组合是:
    PERMISSIONS: 更改所有项。
    FILE_PERMISSIONS: 仅更改文件。
    DIRECTORY_PERMISSIONS: 仅更改目录。
    PERMISSIONS and FILE_PERMISSIONS: 文件中的权限 FILE_PERMISSIONS 覆盖 PERMISSIONS。
    PERMISSIONS and DIRECTORY_PERMISSIONS: 目录中的权限 DIRECTORY_PERMISSIONS 覆盖 PERMISSIONS。
    FILE_PERMISSIONS and DIRECTORY_PERMISSIONS: 对文件使用 FILE_PERMISSIONS，对目录使用 DIRECTORY_PERMISSIONS。
    CHMOD_RECURSE 与 CHMOD 相同，但以递归方式更改 <directories>... 中存在的文件和目录权限。

]]