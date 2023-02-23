# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "============== CMake 文件操作 =================")

#[[
文件操作命令。
    这个命令专用于需要访问文件系统的文件操作 和 简单的路径转换操作。

概要
    Reading
        file(READ <filename> <out-var> [...])
        file(STRINGS <filename> <out-var> [...])
        file(<HASH> <filename> <out-var>)
        file(TIMESTAMP <filename> <out-var> [...])
        file(GET_RUNTIME_DEPENDENCIES [...])

    Writing
        file({WRITE | APPEND} <filename> <content>...)
        file({TOUCH | TOUCH_NOCREATE} [<file>...])
        file(GENERATE OUTPUT <output-file> [...])
        file(CONFIGURE OUTPUT <output-file> CONTENT <content> [...])

    Filesystem
        file({GLOB | GLOB_RECURSE} <out-var> [...] [<globbing-expr>...])
        file(RENAME <oldname> <newname>)
        file({REMOVE | REMOVE_RECURSE } [<files>...])
        file(MAKE_DIRECTORY [<dir>...])
        file({COPY | INSTALL} <file>... DESTINATION <dir> [...])
        file(SIZE <filename> <out-var>)
        file(READ_SYMLINK <linkname> <out-var>)
        file(CREATE_LINK <original> <linkname> [...])
        file(CHMOD <files>... <directories>... PERMISSIONS <permissions>... [...])
        file(CHMOD_RECURSE <files>... <directories>... PERMISSIONS <permissions>... [...])

    Path Conversion
        file(REAL_PATH <path> <out-var> [BASE_DIRECTORY <dir>])
        file(RELATIVE_PATH <out-var> <directory> <file>)
        file({TO_CMAKE_PATH | TO_NATIVE_PATH} <path> <out-var>)

    Transfer
        file(DOWNLOAD <url> [<file>] [...])
        file(UPLOAD <file> <url> [...])

    Locking
        file(LOCK <path> [...])

    Archiving
        file(ARCHIVE_CREATE OUTPUT <archive> PATHS <paths>... [...])
        file(ARCHIVE_EXTRACT INPUT <archive> [...])
]]
message(STATUS "================ 读文件(Reading) ==================")
message(STATUS "================ 读取文本文件和二进制文件 ==================")

# 1. 读文件(Reading)
#[[
1.1 读取文本文件和二进制文件
    file(READ <filename> <variable> [OFFSET <offset>] [LIMIT <max-in>] [HEX])

从 <filename> 文件中读取内容，并将其存储在 <variable> 变量中。<offset> 表示从该文件的偏移位置开始，<max-in> 表示最多读取的字节数。HEX 将文件内容作为十六进制读取，输出字母 a 到 f 为小写。
]]
set(fileName "file/kungfu.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)

if(EXISTS ${fileName})
    message(STATUS "文件存在:${fileName}")
else()
    message(STATUS "文件不存在:${fileName}")
endif()

set(fileName "${CMAKE_CURRENT_SOURCE_DIR}/file/kungfu.txt")

if(EXISTS ${fileName})
    # message(STATUS "文件存在:${fileName}")
    file(READ ${fileName} texts)
    message(STATUS "texts:${texts}")
else()
    message(STATUS "文件不存在:${fileName}")
endif()

message(STATUS "============= 读取文件作为 ASCII 字符串列表 =============")

#[[
1.2 读取文件作为 ASCII 字符串列表
    file(STRINGS <filename> <variable> [<options>...])

从 <filename> 文件解析 ASCII 字符串列表，并将其存储在 <variable> 中。忽略文件中的二进制数据，忽略回车符(\r, CR)。
每行字符串为列表中一个元素。

<options> 选项包括：
    LENGTH_MAXIMUM <max-len>: 只考虑不超过给定长度的字符串。
    LENGTH_MINIMUM <min-len>: 只考虑不少于给定长度的字符串。
    LIMIT_COUNT <max-num>: 限制要提取的不同字符串的数量。
    LIMIT_INPUT <max-in>: 限制从文件中读取的输入字节数。
    LIMIT_OUTPUT <max-out>: 限制 <variable> 中存储的总字节数。
    NEWLINE_CONSUME: 将换行符(\n, LF)作为字符串内容的一部分，而不是终止于它们。
    NO_HEX_CONVERSION: 除非给出此选项，否则读取时 Intel Hex 和 Motorola S-record 文件会自动转换为二进制文件。
    REGEX <regex>: 只考虑匹配给定正则表达式的字符串，如 string(REGEX) 所述。如果匹配成功，包括该行。
    ENCODING <encoding-type>: 考虑给定编码的字符串。目前支持的编码有：UTF-8、UTF-16LE、UTF-16BE、UTF-32LE、UTF-32BE。如果没有提供编码选项，并且文件具有字节顺序标记，则默认情况下，编码选项将遵循字节顺序标记。

例如，
    file(STRINGS "data.txt" VAR)
从文件 “data.txt” 文件解析为字符串列表，其中每一个元素为文件的一行。

例如，
    file(STRINGS "data.txt" VAR REGEX "Pride")
如果文件行包含 “Pride” 字符串，则保留该行。
]]
set(fileName "${CMAKE_CURRENT_SOURCE_DIR}/file/kouyu.txt")

if(EXISTS ${fileName})
    # message(STATUS "文件存在:${fileName}")
    file(STRINGS ${fileName} texts)

    # message(STATUS "${texts}")
    foreach(line ${texts})
        message(STATUS "${line}")
    endforeach()
else()
    message(STATUS "文件不存在:${fileName}")
endif()

message(STATUS "============= 计算文件的哈希值 ==============")

#[[
1.3 计算文件的哈希值
    file(<HASH> <filename> <variable>)

计算 <filename> 文件的内容为哈希值，并将其存储在 <variable> 变量中。支持的 <HASH> 算法名称由 string(<HASH>) 命令列出。
https://cmake.org/cmake/help/v3.19/command/string.html#supported-hash-algorithms

注意，文件名 <filename> 需要是绝对路径。

例如，
    get_filename_component(FILE_NAME file.dat ABSOLUTE)
    message("FILE_NAME: ${FILE_NAME}")
    file(SHA256 ${FILE_NAME} CHECKSUM_VARIABLE)
    message("CHECKSUM_VARIABLE: ${CHECKSUM_VARIABLE}")

先将文件路径，转换为绝对路径，然后计算文件的哈希值。
]]
set(fileName "file/kouyu.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)
file(SHA256 ${fileName} hashSha256)
message(STATUS "hashSha256:${hashSha256}")
file(MD5 ${fileName} hashMd5)
message(STATUS "hashMd5:${hashMd5}")
file(SHA1 ${fileName} hashSha1)
message(STATUS "hashSha1:${hashSha1}")

message(STATUS "============== 获取文件的修改时间 =============")

#[[
1.4 获取文件的修改时间
    file(TIMESTAMP <filename> <variable> [<format>] [UTC])

计算文件 <filename> 修改时间的字符串表示，并将其存储在变量 <variable> 中。 如果该命令无法获得时间戳变量将被设置为空字符串（""）。
例，file(TIMESTAMP ${FILE_NAME} TIME_DATE)。

注意: 文件名 <filename> 需要为绝对路径。
有关 <format> 和 UTC 选项的文档，请参阅 string(TIMESTAMP) 命令。
]]
set(fileName "${CMAKE_CURRENT_SOURCE_DIR}/file/kungfu.txt")
file(TIMESTAMP ${fileName} updateTime)
message(STATUS "updateTime:${updateTime}")

set(FORMAT "%Y-%m-%d %H:%M:%S %j %B %U %w %A")
file(TIMESTAMP ${fileName} updateTime ${FORMAT})
message(STATUS "updateTime:${updateTime}")

# 1.5 依赖项查找
# file(GET_RUNTIME_DEPENDENCIES
# [RESOLVED_DEPENDENCIES_VAR <deps_var>]
# [UNRESOLVED_DEPENDENCIES_VAR <unresolved_deps_var>]
# [CONFLICTING_DEPENDENCIES_PREFIX <conflicting_deps_prefix>]
# [EXECUTABLES [<executable_files>...]]
# [LIBRARIES [<library_files>...]]
# [MODULES [<module_files>...]]
# [DIRECTORIES [<directories>...]]
# [BUNDLE_EXECUTABLE <bundle_executable_file>]
# [PRE_INCLUDE_REGEXES [<regexes>...]]
# [PRE_EXCLUDE_REGEXES [<regexes>...]]
# [POST_INCLUDE_REGEXES [<regexes>...]]
# [POST_EXCLUDE_REGEXES [<regexes>...]]
# )

# 递归获取给定文件依赖的库列表。
# 请注意，此子命令不适用于项目模式。相反，在 install(CODE) 或 install(SCRIPT) 块中使用它。 例如：

# install(CODE [[
# file(GET_RUNTIME_DEPENDENCIES
# # ...
# )
# ]])

#[[
file(GET_RUNTIME_DEPENDENCIES) 参数，说明如下:
    RESOLVED_DEPENDENCIES_VAR<deps_var>: 存储已解析依赖项列表的变量的名称。
    UNRESOLVED_DEPENDENCIES_VAR<unresolved_deps_var>: 用于存储未解析依赖项列表的变量的名称。如果未指定此变量，并且存在任何未解析的依赖项，则会发出错误。
    CONFLICTING_DEPENDENCIES_PREFIX<conflicting_deps_prefix>: 存储冲突依赖信息的变量前缀。如果在两个不同目录中找到两个同名文件，则依赖项会发生冲突。冲突的文件名列表存储在 <conflicting_deps_prefix>_FILENAMES 中。对于每个文件名，为该文件名找到的路径列表存储在 <conflicting_deps_prefix>_<filename> 中。
    EXECUTABLES<executable_files>: 要读取依赖项的可执行文件列表。这些是通常使用 add_executable() 创建的可执行文件，但它们不必由 CMake 创建。在 Apple 平台上，这些文件的路径决定了递归解析库时 @executable_path 的值。在此处指定任何类型的库（STATIC、MODULE 或 SHARED）都将导致未定义的行为。
    LIBRARIES<library_files>: 要读取依赖项的库文件列表。这些是通常使用 add_library(SHARED) 创建的库，但它们不必由 CMake 创建。在此处指定 STATIC 库、MODULE 库或可执行文件将导致未定义的行为。
    MODULES<module_files>: 要读取依赖项的可加载模块文件列表。这些是通常使用 add_library(MODULE) 创建的模块，但它们不必由 CMake 创建。它们通常通过在运行时调用 dlopen() 来使用，而不是在链接时使用 ld -l 链接。在此处指定 STATIC 库、SHARED 库或可执行文件将导致未定义的行为。
    DIRECTORIES<directories>: 用于搜索依赖项的其他目录列表。在 Linux 平台上，如果在任何其他常用路径中找不到依赖项，则会搜索这些目录。如果在这样的目录中找到它，则会发出警告，因为这意味着该文件不完整（它没有列出包含其依赖项的所有目录）。在 Windows 平台上，如果在任何其他搜索路径中找不到依赖项，则会搜索这些目录，但不会发出警告，因为搜索其他路径是 Windows 依赖项解析的正常部分。在 Apple 平台上，此参数无效。
    BUNDLE_EXECUTABLE<bundle_executable_file>: 解析库时，可执行文件被视为 “捆绑可执行文件”。在 Apple 平台上，此参数在递归解析 LIBRARIES 和 MODULES 文件的库时确定 @executable_path 的值。它对 EXECUTABLES 文件没有影响。在其他平台上，它没有影响。这通常（但不总是）是 EXECUTABLES 参数中的可执行文件之一，它指定包的 “主要” 可执行文件。

这些参数，用正则表达式要包含或排除的过滤器，在解析依赖项时，排除不需要的系统库，或包含特定的库。如下说明：
    PRE_INCLUDE_REGEXES[<regexes>...]: 预包含。
    PRE_EXCLUDE_REGEXES[<regexes>...]: 预排除。
    POST_INCLUDE_REGEXES[<regexes>...]: 后包含。
    POST_EXCLUDE_REGEXES[<regexes>...]: 后排除。

例，因为 Windows DLL 名称不区分大小写，我们想实现这种不区分大小写动态库文件查找，查找 “mylibrary.dll” 或 “MYLIBRARY.DLL”:
    file(GET_RUNTIME_DEPENDENCIES
        # ...
        PRE_INCLUDE_REGEXES "^[Mm][Yy][Ll][Ii][Bb][Rr][Aa][Rr][Yy]\\.[Dd][Ll][Ll]$"
    )

将 DLL 名称转换为小写允许正则表达式只匹配小写名称，从而简化了正则表达式。 例如：
file(GET_RUNTIME_DEPENDENCIES
    # ...
    PRE_INCLUDE_REGEXES "^mylibrary\\.dll$"
)

此函数接受多个变量，以确定用于依赖项解析的工具：
    CMAKE_GET_RUNTIME_DEPENDENCIES_PLATFORM: 确定文件为哪种操作系统和可执行文件格式。选择值为: linux+elf, windows+pe, macos+macho
    CMAKE_GET_RUNTIME_DEPENDENCIES_TOOL: 确定用于解析依赖库的工具，根据 CMAKE_GET_RUNTIME_DEPENDENCIES_PLATFORM 变量值来确定。
    linux+elf 对应 objdump
    windows+pe 对应 dumpbin
    windows+pe 对应 objdump
    macos+macho 对应 otool
    CMAKE_GET_RUNTIME_DEPENDENCIES_COMMAND: 确定用于依赖项解析的工具的路径。这是 objdump, dumpbin 或 otool 的实际路径。
]]
