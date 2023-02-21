# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "=============== 字符串比较 (Comparison) ==============")

#[[
字符串比较 (Comparison)
    string(COMPARE <op> <string1> <string2> <out-var>)
    string(COMPARE LESS <string1> <string2> <output_variable>)
    string(COMPARE GREATER <string1> <string2> <output_variable>)
    string(COMPARE EQUAL <string1> <string2> <output_variable>)
    string(COMPARE NOTEQUAL <string1> <string2> <output_variable>)
    string(COMPARE LESS_EQUAL <string1> <string2> <output_variable>)
    string(COMPARE GREATER_EQUAL <string1> <string2> <output_variable>)

比较字符串，并将结果 true 或 false 存储在变量 <output_variable> 中。
注意：比较大小写敏感。
]]
# 例如，string(COMPARE LESS "Hello" "hello" S_out) 字符串 Hello 比 hello 小。
string(COMPARE LESS "Hello" "hello" ret)
message(STATUS "LESS result:${ret}")

string(COMPARE GREATER "phone" "apple" ret)
message(STATUS "GREATER result:${ret}")

string(COMPARE EQUAL "shenzhen" "ShenZhen" ret)
message(STATUS "EQUAL result:${ret}")

string(COMPARE NOTEQUAL "BeiJing" "ShangHai" ret)
message(STATUS "NOTEQUAL result:${ret}")

string(COMPARE LESS_EQUAL "BeiJing" "ShangHai" ret)
message(STATUS "LESS_EQUAL result:${ret}")

string(COMPARE GREATER_EQUAL "BeiJing" "ShangHai" ret)
message(STATUS "GREATER_EQUAL result:${ret}")

message(STATUS "=============== 字符串哈希 (Hashing) ==============")

#[[
哈希 (Hashing)
    string(<HASH> <out-var> <input>)
    string(<HASH> <output_variable> <input>)

计算字符串 <input> 的哈希值。支持 <HASH> 算法的名称是：
    MD5: 消息摘要算法(Message-Digest Algorithm) 5, RFC 1321.
    SHA1: 美国安全散列算法(US Secure Hash Algorithm) 1, RFC 3174.
    SHA224: US Secure Hash Algorithms, RFC 4634.
    SHA256: US Secure Hash Algorithms, RFC 4634.
    SHA384: US Secure Hash Algorithms, RFC 4634.
    SHA512: US Secure Hash Algorithms, RFC 4634.
    SHA3_224: Keccak SHA-3.
    SHA3_256: Keccak SHA-3.
    SHA3_384: Keccak SHA-3.
    SHA3_512: Keccak SHA-3.

例如，简单用一些哈希算法计算文本的哈希值。
    set(S "Hello World")
    string(MD5 S_md5 ${S})
    message("S_md5: ${S_md5}")
    string(SHA1 S_sha1 ${S})
    message("S_sha1: ${S_sha1}")
    string(SHA256 S_sha256 ${S})
    message("S_sha256: ${S_sha256}")
]]

# 例如，简单用一些哈希算法计算文本的哈希值。
set(TEXT "Hello World,Study CMake")
string(MD5 md5Value ${TEXT})
message(STATUS "MD5:${md5Value}")
string(SHA1 sha1Value ${TEXT})
message(STATUS "SHA1:${sha1Value}")
string(SHA256 sha256Value ${TEXT})
message(STATUS "SHA256:${sha256Value}")