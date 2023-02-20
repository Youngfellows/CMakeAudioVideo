# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

#[[
CMake 字符串操作
概要(Synopsis)
    Search and Replace
        string(FIND <string> <substring> <out-var> [...])
        string(REPLACE <match-string> <replace-string> <out-var> <input>...)
        string(REGEX MATCH <match-regex> <out-var> <input>...)
        string(REGEX MATCHALL <match-regex> <out-var> <input>...)
        string(REGEX REPLACE <match-regex> <replace-expr> <out-var> <input>...)

    Manipulation
        string(APPEND <string-var> [<input>...])
        string(PREPEND <string-var> [<input>...])
        string(CONCAT <out-var> [<input>...])
        string(JOIN <glue> <out-var> [<input>...])
        string(TOLOWER <string> <out-var>)
        string(TOUPPER <string> <out-var>)
        string(LENGTH <string> <out-var>)
        string(SUBSTRING <string> <begin> <length> <out-var>)
        string(STRIP <string> <out-var>)
        string(GENEX_STRIP <string> <out-var>)
        string(REPEAT <string> <count> <out-var>)

    Comparison
        string(COMPARE <op> <string1> <string2> <out-var>)

    Hashing
        string(<HASH> <out-var> <input>)

    Generation
        string(ASCII <number>... <out-var>)
        string(HEX <string> <out-var>)
        string(CONFIGURE <string> <out-var> [...])
        string(MAKE_C_IDENTIFIER <string> <out-var>)
        string(RANDOM [<option>...] <out-var>)
        string(TIMESTAMP <out-var> [<format string>] [UTC])
        string(UUID <out-var> ...)

    JSON
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                {GET | TYPE | LENGTH | REMOVE}
                <json-string> <member|index> [<member|index> ...])
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                MEMBER <json-string>
                [<member|index> ...] <index>)
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                SET <json-string>
                <member|index> [<member|index> ...] <value>)
        string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                EQUAL <json-string1> <json-string2>)

    注意: <string> 不是字符串变量，而是字符串值。
    注意: <string-var> 是字符串变量。
]]
set(text "Pride and Prejudice is kind of a literary Rosetta Stone, the inspiration, basis, and model for so many modern novels. \
You’re probably more familiar with its plot and characters than you think. \
For a book written in the early 19th century, it’s modernity is surprising only until you realize that this is the novel that in many ways defined what a modern novel is.
")
message(STATUS "text: ${text}")

#[[ 
一、搜索和替换 (Search and Replace)
1、用纯字符串搜索和替换 (Search and Replace With Plain Strings)
        string(FIND <string> <substring> <out-var> [...])
        string(FIND <string> <substring> <output_variable> [REVERSE])
    查找字符串的子串位置。
    返回字符串 <string> 中给定 子串 <substring> 的第一次出现的位置。
    如果使用了 REVERSE 标志，逆向搜索，表示最后一次出现子串的位置。
    如果未找到子串 <substring>，则返回 -1。
    string(FIND) 子命令将所有字符串视为 ASCII 字符。
    <output_variable> 将结果索引存储在该变量中。
]]
# 例如，string(FIND ${S} "in" S_index) 查找子串 in 所在索引，并且将索引值保存在 S_index 变量中。
string(FIND ${text} "in" searchIndex)
message(STATUS "searchIndex:${searchIndex}")

#[[
    string(REPLACE <match-string> <replace-string> <out-var> <input>...)
    string(REPLACE <match_string> <replace_string> <output_variable> <input> [<input>...])
    将输入字符串 <input> 中所有出现的 <match-string> 替换为 <replace_string>，并将结果存储在 <output_variable> 中。   
]]
# 例如，string(REPLACE "in" "out" S_out_var ${S}) 将字符串中的所有字符 in 替换为 out。
string(REPLACE "in" "out" newText ${text})
message(STATUS "newText: ${newText}")

#[[
2.用正则表达式搜索和替换 (Search and Replace With Regular Expressions)
    string(REGEX MATCH <match-regex> <out-var> <input>...)
    string(REGEX MATCH <regular_expression> <output_variable> <input> [<input>...])

    根据正则表达式匹配一次。
    将所有输入字符串 <input> 在匹配之前都连接在一起，然后根据正则表达式 <regular_expression> 匹配一次，将该结果存储在 <output_variable>。
]]

# 例如，string(REGEX MATCH "[A-Za-z]*in[A-Za-z]*" S_out_var ${S}) 匹配带有字符 in 的单词
string(REGEX MATCH "[A-Za-z]*in[A-Za-z]*" matchResult ${text})
message(STATUS "matchResult:${matchResult}")

#[[
    string(REGEX MATCHALL <match-regex> <out-var> <input>...)
    string(REGEX MATCHALL <regular_expression> <output_variable> <input> [<input>...])

    根据正则表达式尽可能匹配。
    将所有输入字符串 <input> 在匹配之前都连接在一起，然后根据正则表达式 <regular_expression> 尽可能匹配，将所有结果存储在 <output_variable>。
]]

# 例如，string(REGEX MATCHALL "[A-Za-z]*in[A-Za-z]*" S_out_var ${S}) 尽可能带有字符 in 的单词。
string(REGEX MATCHALL "[A-Za-z]*in[A-Za-z]*" matchResults ${text})
message(STATUS "matchResults:${matchResults}")

#[[
    string(REGEX REPLACE <match-regex> <replace-expr> <out-var> <input>...)
    string(REGEX REPLACE <regular_expression> <replacement_expression> <output_variable> <input> [<input>...])

    根据正则表达式替换。
    将所有输入字符串 <input> 在匹配之前都连接在一起，然后尽可能匹配 <regular_expression> 并替换为 <replacement_expression>，将结果存储在 <output_variable>。
]]

# 例如，string(REGEX REPLACE "[A-Za-z]*in[A-Za-z]*" "hello" S_out_var ${S}) 尽可能带有字符 in 的单词 替换为 字符 hello。
string(REGEX REPLACE "[A-Za-z]*in[A-Za-z]*" "hello" replaceResult ${text})
message(STATUS "replaceResult:${replaceResult}")

# <replacement_expression> 可以使用 \1, \2, …, \9 来引用括号匹配子表达式。请注意，CMake 代码中需要两个反斜杠 \\1 才能通过参数解析获取反斜杠 \。

# 例如，string(REGEX REPLACE "([A-Za-z]*in[A-Za-z]*)" "\\1_hello" S_out_var ${S}) 尽可能带有字符 in 的单词，增加后缀 _hello。
string(REGEX REPLACE "([A-Za-z]*in[A-Za-z])" "\\1_hello" replaceResult ${text})
message(STATUS "replaceResult:${replaceResult}")

#[[
正则表达式规范 (Regex Specification)
特殊字符
    ^: 匹配输入开头
    $: 匹配输入结束
    .: 匹配任意单个字符
    \<char>: 匹配单字符 <char>。使用它来匹配特殊的正则表达式字符，例如 \. 表示点，\\ 表示反斜杠，\a 表示 a
    [ ]: 匹配任何在括号内的字符
    [^ ]: 匹配任何不在括号内的字符
    -: 在方括号内，指定字符的范围，例如 [a-f] 表示 [abcdef]，[0-3] 表示 [0123]，[+*/-] 表示数学运算符。
    *: 匹配前面模式的零次或多次
    +: 匹配前面模式的一次或多次
    ?: 匹配前面模式的零次或一次
    |: 匹配 | 两侧的模式
    (): 保存匹配的子表达式(模式)，可以在 REGEX REPLACE 操作中引用。此外，它由所有与正则表达式相关的命令保存，包括 例如 if(MATCHES)，在变量 CMAKE_MATCH_<n> 中 <n> 为 0..9

*, + 和 ? 具有比 | 比 串联(concatenation) 有更高的优先级。
| 比 串联(concatenation) 有更低的优先级。
这意味着，正则表达式 ^ab+d$，匹配 abbd，但不匹配 ababd。正则表达式 ^(ab|cd)$，匹配 ab，但不匹配 abd

CMake 语言转义序列 例如 \t, \r, \n, 和 \\ 可用于构造制表符, 回车符, 换行符 和 反斜杠 表示正则表达式。例如：
    带引号参数 "[ \t\r\n]" 指定匹配任何单个空白字符的正则表达式。
    带引号参数 "[/\\]" 指定匹配斜杠和反斜杠的正则表达式。
    带引号参数 "[A-Za-z0-9_]" 指定匹配 C 语言环境中任何单个"单词"字符的正则表达式。
    带引号参数 "\\(\\a\\+b\\)" 指定了一个匹配确切字符串 (a+b) 的正则表达式。
]]