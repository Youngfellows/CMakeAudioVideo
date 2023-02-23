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
    string(TIMESTAMP <out-var> [<format string>] [UTC])
    string(TIMESTAMP <output_variable> [<format_string>] [UTC])
    UTC 表示采用协调世界时(UTC)，而不是本地时间

    <format_string> 表示格式化日期和时间，格式符说明：
    %%        A literal percent sign (%).
    %d        The day of the current month (01-31).
    %H        The hour on a 24-hour clock (00-23).
    %I        The hour on a 12-hour clock (01-12).
    %j        The day of the current year (001-366).
    %m        The month of the current year (01-12).
    %b        Abbreviated month name (e.g. Oct).
    %B        Full month name (e.g. October).
    %M        The minute of the current hour (00-59).
    %s        Seconds since midnight (UTC) 1-Jan-1970 (UNIX time).
    %S        The second of the current minute. 60 represents a leap second. (00-60)
    %U        The week number of the current year (00-53).
    %w        The day of the current week. 0 is Sunday. (0-6)
    %a        Abbreviated weekday name (e.g. Fri).
    %A        Full weekday name (e.g. Friday).
    %y        The last two digits of the current year (00-99)
    %Y        The current year.

    如果未给出明确的 <format_string>，它将默认为：
    %Y-%m-%dT%H:%M:%S    for local time.
    %Y-%m-%dT%H:%M:%SZ   for UTC.
]]
message(STATUS "========== 当前日期和时间的字符串 ===========")
string(TIMESTAMP currTime)
message(STATUS "currTime:${currTime}")

string(TIMESTAMP currTime UTC)
message(STATUS "currTime:${currTime}")

string(TIMESTAMP currTime "%Y-%m-%d %H:%M:%S %j %B %U %w %A")
message(STATUS "currTime:${currTime}")

#[[
7.根据 RFC4122，基于 <namespace> 和 <name> 的组合值的哈希运算，并创建一个通用唯一标识符(UUID 又名为 GUID)。
    string(UUID <out-var> ...)
    string(UUID <output_variable> NAMESPACE <namespace> NAME <name> TYPE <MD5|SHA1> [UPPER])
   
    哈希算法是 MD5(版本 3 UUID) 或 SHA1(版本 5 UUID)。
    UUID 格式为 xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx，其中每个 x 代表一个小写十六进制字符。
    UPPER 表示用大写表示。
]]
# 例子，运行单元测试 Uuid.cmake(https://github.com/Kitware/CMake/blob/master/Tests/RunCMake/string/Uuid.cmake)
message(STATUS "============= 唯一标识符(UUID)  ===============")
set(UUID_DNS_NAMESPACE 6ba7b810-9dad-11d1-80b4-00c04fd430c8)
string(
    UUID WWW_EXAMPLE_COM_MD5_UUID
    NAMESPACE ${UUID_DNS_NAMESPACE}
    NAME "www.example.com"
    TYPE MD5
)
string(
    UUID WWW_EXAMPLE_COM_SHA1_UUID
    NAMESPACE ${UUID_DNS_NAMESPACE}
    NAME "www.example.com"
    TYPE SHA1 UPPER
)
message(STATUS "WWW_EXAMPLE_COM_MD5_UUID: ${WWW_EXAMPLE_COM_MD5_UUID}")
message(STATUS "WWW_EXAMPLE_COM_SHA1_UUID: ${WWW_EXAMPLE_COM_SHA1_UUID}")

#[[
8.JSON 字符串
    8.1 查询 JSON 字符串的功能。
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
            GET <json-string> <member|index> [<member|index> ...])
        string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
            GET <json-string> <member|index> [<member|index> ...])

        获取 JSON 字符串的元素。
        Array 和 object 元素将返回 JSON 字符串。
        Boolean 元素将返回 ON 或 OFF。
        Null 元素返回一个空字符串。
        Number 和 string 返回一个字符串。     
    
    8.2 获取 JSON 字符串的元素的类型
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                TYPE <json-string> <member|index> [<member|index> ...])
        string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
                TYPE <json-string> <member|index> [<member|index> ...])
        输出的类型 <out-var> 为 NULL, NUMBER, STRING, BOOLEAN, ARRAY, 或 OBJECT.

    8.3 获取 JSON 字符串指定索引的成员名称。
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                MEMBER <json-string> [<member|index> ...] <index>)
        string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
                MEMBER <json-string> [<member|index> ...] <index>)

    8.4 获取 JSON 字符串元素的长度。
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                LENGTH <json-string> <member|index> [<member|index> ...])
        string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
                LENGTH <json-string> <member|index> [<member|index> ...])

    8.5 从 JSON 字符串中删除一个元素。
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                REMOVE <json-string> <member|index> [<member|index> ...])
        string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
                REMOVE <json-string> <member|index> [<member|index> ...])

    8.6 设置 JSON 字符串中元素的值。
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                SET <json-string> <member|index> [<member|index> ...] <value>)
        string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
                SET <json-string> <member|index> [<member|index> ...] <value>)

    8.7 比较两个 JSON 对象是否相等。
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
            EQUAL <json-string1> <json-string2>)
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
            EQUAL <json-string1> <json-string2>)
]]