# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: " ${PROJECT_NAME})

# CMake 使用 # 进行行注释，可以放在任何位置。
# message("******************************")
message(STATUS "First Argument\n" # This is a line comment :)
    "Second Argument") # This is a line comment

# CMake 使用 #[[ 形式进行块注释。
#[[message(STATUS "111111111111111111111111")
message(STATUS "222222222222222222222222")
message(STATUS "333333333333333333333333")]]
message(STATUS "第一个参数\n" #[[这是块注释的内容]] "第二个参数")

# 1.括号参数
#[[ 括号参数的参数内容，是左括号 [ 跟零个或多个 = 以右括号 ] 结束。
    括号参数，不执行 转义序列 或 变量引用。]]
message([=[
This is the first line in a bracket argument with bracket length 1.
No \-escape sequences or ${variable} references are evaluated.
This is always one argument even though it contains a ; character.
The text does not end on a closing bracket of length 0 like ]].
It does end in a closing bracket of length 1.
]=])

# 2. 带引号的参数
# 带引号的参数的参数内容，在双引号 " 之间。
message("This is a quoted argument containing multiple lines.
This is always one argument even though it contains a ; character.
Both \\-escape sequences and ${variable} references are evaluated.
The text does not end on an escaped double-quote like \".
It does end in an unescaped double quote.
")

# 使用反斜杠 \，连接行
message("\
This is the first line of a quoted argument. \
In fact it is the only line but since it is long \
the source code uses line continuation.\
")

# 3. 不带引号的参数
# 参数用 空格 、分号 ;、换行 \n 分隔不同的参数，如果使用转义字符 \，并不分隔参数。
foreach(arg
    NoSpace
    Escaped\ Space
    This;Divides;Into
    Five Arguments
    Escaped\;Semicolon
)
    message("${arg}")
endforeach()

# 4. 转义序列
#[[我们通过 \ 之后跟一个字符，组成转义序列。
转义编码，包括 '\t'、'\r'、'\n'
转义符号，包括 '\;'、'\\'
转移序列作为参数的值。]]

# Bracket Argument
message("======> Bracket Argument")
message([=[
This is the first line in a bracket argument with bracket length 1.
No \-escape sequences or ${variable} references are evaluated.
This is always one argument even though it contains a ; character.
The text does not end on a closing bracket of length 0 like ]].
It does end in a closing bracket of length 1.
]=])

# Quoted Argument
message("======> Quoted Argument")
message("This is a quoted argument containing multiple lines.
This is always one argument even though it contains a ; character.
Both \\-escape sequences and ${variable} references are evaluated.
The text does not end on an escaped double-quote like \".
It does end in an unescaped double quote.
")

# Connecting line
message("======> Connecting line")
message("\
This is the first line of a quoted argument. \
In fact it is the only line but since it is long \
the source code uses line continuation.\
")

# Unquoted Argument
message("======> Unquoted Argument")

foreach(arg
    NoSpace
    Escaped\ Space
    This;Divides;Into
    Five Arguments
    Escaped\;Semicolon
)
    message("${arg}")
endforeach()

# Escape Sequences
message("======> Escape Sequences")
message("
This is the first.\r\n\tline of a quoted argument.
")
