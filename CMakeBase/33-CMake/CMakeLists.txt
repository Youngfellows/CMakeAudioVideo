# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "============= CMake 命令行参数 =============")

# 将命令行参数解析为以分号分隔的列表。
# separate_arguments 签名
# separate_arguments(<variable> <mode> [PROGRAM [SEPARATE_ARGS]] <args>)

# 将空格分隔的字符串 <args> 解析为参数列表，并存储在 <variable> 变量中。
# 我们通过 <mode> 选项，选择参数解析规则，这些规则取决于操作系统，不同的操作系统命令行参数风格是不一样的。
# UNIX 操作系统用 UNIX_COMMAND，Windows 操作系统用 WINDOWS_COMMAND，如果按本机系统用 NATIVE_COMMAND。

# 例，将 UNIX 操作系统参数 gcc -cc main.c，分割为 gcc;-cc;main.c。
separate_arguments(argsAvr NATIVE_COMMAND "gcc -cc main.c")
message(STATUS "${argsAvr}")

separate_arguments(argsAvr WINDOWS_COMMAND "gcc -cc main.c")
message(STATUS "${argsAvr}")

#[[
若我们想获取程序的绝对路径，我们使用选项 PROGRAM，这回导致仅分割 程序路径和参数。
例 separate_arguments(ARGS_VAR UNIX_COMMAND PROGRAM "gcc -cc main.c") 会输出 /path/to/gcc 和 -c main.c。

但是想参数也分割，需要结合 SEPARATE_ARGS 选项。
例 separate_arguments(ARGS_VAR UNIX_COMMAND PROGRAM SEPARATE_ARGS "gcc -cc main.c") 会输出 /path/to/gcc;-cc;main.c。
]]
separate_arguments(argsAvr UNIX_COMMAND PROGRAM "gcc -cc main.c")
message(STATUS "${argsAvr}")

separate_arguments(argsAvr UNIX_COMMAND PROGRAM SEPARATE_ARGS "gcc -cc main.c")
message(STATUS "${argsAvr}")
