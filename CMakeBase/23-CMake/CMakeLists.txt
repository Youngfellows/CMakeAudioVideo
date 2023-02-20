# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

# 字符串操纵 (Manipulation)
#[[
    将所有字符串 <input> 附加到变量 <string_variable> 末尾。
    string(APPEND <string-var> [<input>...])
    string(APPEND <string_variable> [<input>...])
]]
# 例如，string(APPEND S " Stone") 将字符串 Stone 附加到变量 S 末尾
string(APPEND S " Stone")
message(STATUS "${S}")
string(APPEND S " Apple")
message(STATUS "${S}")

#[[
    将所有字符串 <input> 添加到变量 <string_variable> 首部。
    string(CONCAT <out-var> [<input>...])
    string(CONCAT <output_variable> [<input>...])
]]

# 例如，string(PREPEND S "Banana ") 将字符串 Banana 附加到变量 S 首部
string(PREPEND S "Banana ")
message(STATUS "${S}")

#[[
    将所有字符串 <input> 连接在一起，并将结果存储在变量 <output_variable>。
    string(CONCAT <out-var> [<input>...])
    string(CONCAT <output_variable> [<input>...])
]]

# 例如，string(CONCAT S_out "Rosetta" " Stone") 将字符串 Rosetta 和 Stone 连接在一起，并将结果存储在变量 S_out 中
string(CONCAT CITY "北京" " 深圳" " 广州")
message(STATUS "${CITY}")

#[[
    使用 <glue> 字符，将所有字符串 <input> 连接在一起，并将结果存储在变量 <output_variable>。
    string(JOIN <glue> <out-var> [<input>...])
    string(JOIN <glue> <output_variable> [<input>...])
]]
# 例如，string(CONCAT " " S_out "Rosetta" "Stone") 使用字符空格字符，将字符串 Rosetta 和 Stone 连接在一起，并将结果存储在变量 S_out 中
string(JOIN "-" HEROS "杨过" "乔峰" "张无忌" "郭靖")
message(STATUS "${HEROS}")

#[[
    将字符串 <string> 转换为小写的字符。
    string(TOLOWER <string> <out-var>)
    string(TOLOWER <string> <output_variable>)

    将字符串 <string> 转换为大写的字符。
    string(TOUPPER <string> <out-var>)
    string(TOUPPER <string> <output_variable>)
]]
# 例如，string(TOUPPER "Hello" S_out) 将字符串 Hello 转换为大写
# 例如，string(TOLOWER "Hello" S_out) 将字符串 Hello 转换为小写
string(TOLOWER "ShenZhen" sz)
message(STATUS "${sz}")
string(TOUPPER "BeiJing" bj)
message(STATUS "${bj}")

#[[
    计算字符串 <string> 的长度，并将结果存储到变量 <output_variable> 中
    string(LENGTH <string> <out-var>)
    string(LENGTH <string> <output_variable>)
]]

# 例如，string(LENGTH "Hello" S_len) 计算字符串 Hello 的长度
set(TEXT "My Name is ShenZhen")
string(LENGTH ${TEXT} length)
message(STATUS "length:${length}")

#[[
    将字符串 <string> 的子串存储在变量 <output_variable> 中。子串是从 begin 索引开始，长度为 <length>。
    string(SUBSTRING <string> <begin> <length> <out-var>)
    string(SUBSTRING <string> <begin> <length> <output_variable>)
]]

# 例如，string(SUBSTRING "Hello World" 2 5 S_sub) 将字符串 Hello World，获取索引 2，长度 5 的子串 llo W

set(TEXT "Pride and Prejudice is kind of a literary Rosetta Stone, the inspiration, basis, and model for so many modern novels. \
You’re probably more familiar with its plot and characters than you think. \
For a book written in the early 19th century, it’s modernity is surprising only until you realize that this is the novel that in many ways defined what a modern novel is")
string(SUBSTRING ${TEXT} 2 5 subStr)
message(STATUS ${subStr})

#[[
    删除字符串 <string> 前导和尾随空格，将结果存储在变量 <output_variable> 中。
    string(STRIP <string> <out-var>)
    string(STRIP <string> <output_variable>)
]]

# 例如，string(STRIP " Hello World " S_out) 删除字符串 Hello World 前导和尾随空格
set(msg "   Prejudice is kind   ")
message(STATUS "length:${length}")
string(LENGTH ${msg} length)
string(STRIP ${msg} msg)
string(LENGTH ${msg} length)
message(STATUS "${msg}")
message(STATUS "length:${length}")

#[[
    string(GENEX_STRIP <string> <out-var>)
    string(GENEX_STRIP <string> <output_variable>)
]]
string(GENEX_STRIP "Hello World" helloText)
message(STATUS "${helloText}")

#[[
    产生字符串 <string> 的重复次数 <count>，将结果存储在变量 <output_variable> 中。
    string(REPEAT <string> <count> <out-var>)
    string(REPEAT <string> <count> <output_variable>)
]]
# 例如，string(REPEAT "Hello" 3 S_out) 产生的字符串为 HelloHelloHello
string(REPEAT "Apple" 4 apples)
message(STATUS "${apples}")