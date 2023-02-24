# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message("PROJECT_NAME: " ${PROJECT_NAME})

message(STATUS "=========== cmake_parse_arguments 的第二种形式 ============")

# 1. cmake_parse_arguments 的第二种形式
#[[
cmake_parse_arguments 的第二种形式，语法如下：
cmake_parse_arguments(PARSE_ARGV <N> <prefix> <options>
                      <one_value_keywords> <multi_value_keywords>)

PARSE_ARGV 仅用于函数。在这种情况下，解析的参数来自调用函数的 ARGVn。解析从第 <N> 个参数开始。

定义一个类似 add_executable 命令，要实现的命令形式，如下：

my_add_executable(<name> [WIN32] [MACOSX_BUNDLE]
	[EXCLUDE_FROM_ALL]
	[source1] [source2 ...]
)
]]

# 代码如下：
function(my_add_executable name)
    set(options WIN32 MACOSX_BUNDLE EXCLUDE_FROM_ALL)
    set(oneValueArgs)
    set(multiValueArgs)
    cmake_parse_arguments(PARSE_ARGV 1 MY "${options}" "${oneValueArgs}" "${multiValueArgs}")
    message("name: ${name}")
    message("MY_WIN32: ${MY_WIN32}")
    message("MY_MACOSX_BUNDLE: ${MY_MACOSX_BUNDLE}")
    message("MY_EXCLUDE_FROM_ALL: ${MY_EXCLUDE_FROM_ALL}")

    # 未解析的参数
    message("MY_UNPARSED_ARGUMENTS: ${MY_UNPARSED_ARGUMENTS}")

    # 关键字缺失值的参数
    message("MY_KEYWORDS_MISSING_VALUES: ${MY_KEYWORDS_MISSING_VALUES}")
endfunction()

# 调用形式
my_add_executable(myprog WIN32 main1.c main2.c main3.c)

#[[
在 cmake_parse_arguments 调用之后，将设置以下变量
name: myprog
MY_WIN32: TRUE
MY_MACOSX_BUNDLE: FALSE
MY_EXCLUDE_FROM_ALL: FALSE
MY_UNPARSED_ARGUMENTS: main1.c;main2.c;main3.c
MY_KEYWORDS_MISSING_VALUES:

# 注意，函数第一个参数，可以通过 形参获取 或者通过 ARGV0 引用。最后的不定参数，可以通过特殊变量 MY_UNPARSED_ARGUMENTS 获取，并通过 foreach 语句 解析。
]]

