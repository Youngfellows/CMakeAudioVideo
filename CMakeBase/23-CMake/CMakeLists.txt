# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

# 操纵 (Manipulation)
#[[
    将所有字符串 <input> 附加到变量 <string_variable> 末尾。
    string(APPEND <string-var> [<input>...])
    string(APPEND <string_variable> [<input>...])
]]
# 例如，string(APPEND S " Stone") 将字符串 Stone 附加到变量 S 末尾
string(APPEND S " Stone")
message(STATUS "${S}")