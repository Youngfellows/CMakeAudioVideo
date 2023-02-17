# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message("PROJECT_NAME: " ${PROJECT_NAME})

#[[ Cmake中的条件判断if/elseif/else
一、基本命令解析
    if语句用于判断条件是否成立，条件成立时执行对应的语句。完整的格式如下：
        if(<condition>)
        <commands>
        elseif(<condition>) # 可选，且可重复
        <commands>
        else() # 可选
        <commands>
        endif()

    如果if括号内的condition为真，则执行if对应的语句块；
    如果if括号内的condition为假，则判断elseif语句的condition是否为真，为真则执行elseif对应的语句块，注意：elseif是可选的，并且可以出现多次；
    如果elseif括号内的condition为假，则执行else()对应的语句块，注意：else()是可选的，else后面有一对空括号，也可以在括号里面写condition，但是必须与if对应的condition完全一致；
    最后以endif()结尾，注意：endif()的括号内也可以写condition，但是必须与if对应的condition完全一致；

二、if语句中条件(condition)的优先级
    if语句中条件(condition)的优先级从高到低如下：
    1. 圆括号()：括号的优先级最高
    2. 一元测试命令：
        EXIST：判断文件或者目录是否存在，存在时为真。需要提供全路径；如果文件或者目录是符号链接（例如软连接），则只有当链接的目标存在时返回真。格式为：if(EXISTS path-to-file-or-directory)。
        COMMAND：如果给定的名称是命令、宏或者函数这类可被调用的对象，则返回真。格式为：if(COMMAND command-name)。
        DEFINED：如果给定的变量（普通变量、缓存变量、环境变量）存在，则返回真。格式为：if(DEFINED <name>|CACHE{<name>}|ENV{<name>})，注意缓存变量前要加CACHE，环境变量前要加ENV。
    3. 二元测试命令，二元操作符有的左边和右边需要提供变量：
        EQUAL：左边两个字符串或者变量相等时为真。格式为：if(<variable|string> EQUAL <variable|string>)。
        LESS：左边小于右边时为真(数值比较)。格式为：if(<variable|string> LESS <variable|string>)。
        LESS_EQUAL：左边小于等于右边时为真(数值比较)。格式为：if(<variable|string> LESS_EQUAL <variable|string>)。
        GREATER：左边大于右边时为真(数值比较)。格式为：if(<variable|string> GREATER <variable|string>)。
        GREATER_EQUAL：左边大于等于右边时为真(数值比较)。格式为：if(<variable|string> GREATER_EQUAL <variable|string>)。
        STREQUAL：左边与右边的字典顺序相等时为真(数值比较)。格式为：if(<variable|string> STREQUAL <variable|string>)。
        STRLESS：左边的字典顺序小于右边的字典序时为真。格式为：if(<variable|string> STRLESS <variable|string>)。
        STRLESS_EQUAL：左边的字典顺序小于等于右边的字典序时为真。格式为：if(<variable|string> STRLESS_EQUAL <variable|string>)。
        STRGREATER：左边的字典顺序大于右边的字典序时为真。格式为：if(<variable|string> STRGREATER <variable|string>)。
        STRGREATER_EQUAL：左边的字典顺序大于等于右边的字典序时为真。格式为：if(<variable|string> STRGREATER_EQUAL <variable|string>)。]]
        # VERSION_EQUAL：左右两边的版本号相等时为真。左右两边的版本号格式为major[.minor[.patch[.tweak]]]，每个部分都要求是整数（省略的部分当做0），如果是非整数，从非整数的地方往后会被截断。格式为：if(<variable|string> VERSION_EQUAL <variable|string>)。
        # VERSION_LESS：左边版本号小于右边版本号时为真。左右两边的版本号格式为major[.minor[.patch[.tweak]]]，每个部分都要求是整数（省略的部分当做0）），如果是非整数，从非整数的地方往后会被截断。格式为：if(<variable|string> VERSION_LESS <variable|string>)。
        # VERSION_LESS：左边版本号小于右边版本号时为真。左右两边的版本号格式为major[.minor[.patch[.tweak]]]，每个部分都要求是整数（省略的部分当做0），如果是非整数，从非整数的地方往后会被截断。格式为：if(<variable|string> VERSION_LESS <variable|string>)。
        # VERSION_LESS_EQUAL：左边版本号小于等于右边版本号时为真。左右两边的版本号格式为major[.minor[.patch[.tweak]]]，每个部分都要求是整数（省略的部分当做0），如果是非整数，从非整数的地方往后会被截断。格式为：if(<variable|string> VERSION_LESS_EQUAL <variable|string>)。
        # VERSION_GREATER：左边版本号大于右边版本号时为真。左右两边的版本号格式为major[.minor[.patch[.tweak]]]，每个部分都要求是整数（省略的部分当做0），如果是非整数，从非整数的地方往后会被截断。格式为：if(<variable|string> VERSION_GREATER <variable|string>)。
        # VERSION_GREATER_EQUAL：左边版本号大于等于右边版本号时为真。左右两边的版本号格式为major[.minor[.patch[.tweak]]]，每个部分都要求是整数（省略的部分当做0），如果是非整数，从非整数的地方往后会被截断。格式为：if(<variable|string> VERSION_GREATER_EQUAL <variable|string>)。
        #[[MATCHES：按照正则表达式去匹配，左边是待匹配的值，右边是正则表达式，能匹配为时为真。格式为：if(<variable|string> MATCHES regex)。
    4. 一元逻辑操作符号：
        NOT：条件不满足时为真。格式为：if(NOT <condition>)。
    5. 二元逻辑操作符：
        AND：左右两边条件均成立时为真。格式为：if(<cond1> AND <cond2>)。
        OR：左右两边条件任一个成立时为真。格式为：if(<cond1> OR <cond2>)。
]]
