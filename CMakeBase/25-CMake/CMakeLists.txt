# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "============ 字符串的产生 ===========")
#[[
1.将所有数字转换为响应的 ASCII 字符
    string(ASCII <number>... <out-var>)
    string(ASCII <number> [<number> ...] <output_variable>)

]]
string(ASCII 123 assciiResult)
message(STATUS "assciiResult:${assciiResult}")

string(ASCII 65 assciiResult)
message(STATUS "assciiResult:${assciiResult}")

#[[
2.将字符串中每个字节转换为十六进制表示
    string(HEX <string> <out-var>)
    string(HEX <string> <output_variable>)
]]
string(HEX "shenzhen price 22 33 abc" hexResult)
message(STATUS "hexResult:${hexResult}")

#[[
3.像 configure_file() 一样的规则转换 <string>
    string(CONFIGURE <string> <out-var> [...])
    string(CONFIGURE <string> <output_variable> [@ONLY] [ESCAPE_QUOTES])
]]
# 例子，将 configure 字符串根据规则替换
set(VAR 1)
string(CONFIGURE "#cmakedefine VAR @VAR@" S_out)
message(STATUS "S_out: ${S_out}")


#[[
4.将字符串转换为标识符。将字符串中的每个非字母数字字符转换为下划线。
    string(MAKE_C_IDENTIFIER <string> <out-var>)
    string(MAKE_C_IDENTIFIER <string> <output_variable>)
]]
string(MAKE_C_IDENTIFIER "abc123def#G@163.COM" identifierResult)
message(STATUS "identifierResult:${identifierResult}")

#[[
5.给定字符组 <alphabet> 和 长度 <length> 产生随机的字符串。默认长度为 5，默认字符组为所有数字和大小写字母。
  如果给出整数 RANDOM_SEED，则其值将用于为随机数生成器提供种子。
    string(RANDOM [<option>...] <out-var>)
    string(RANDOM [LENGTH <length>] [ALPHABET <alphabet>] [RANDOM_SEED <seed>] <output_variable>)
]]
# 例子，产生长度为 12 的随机字符串
set(CHARs "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#@!")
string(RANDOM LENGTH 12 ALPHABET ${CHARs} S_out)
message(STATUS "S_out: ${S_out}")

#[[
6.将当前日期和时间的字符串，存储到变量 <output_variable>
UTC 表示采用协调世界时(UTC)，而不是本地时间
    <format_string> 表示格式化日期和时间，格式符说明：
    string(TIMESTAMP <out-var> [<format string>] [UTC])
    string(TIMESTAMP <output_variable> [<format_string>] [UTC])
]]