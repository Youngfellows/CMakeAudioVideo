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

#[[
三、示例说明
      if语句分为基本表达式、逻辑操作、存在性判断、文件操作、变量比较、版本号比较、变量展开几大类判定，下面依次以示例来介绍：
]]

#[[
3.1 基本表达式
    if(<constant>)
    如果constant是1, ON, YES, TRUE, Y或非0值时为真；
    如果constant是0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, 空字符串, 以NOTFOUND为后缀时为假；
    注意constant是大小写不敏感的，如果constant不是上述值，则会被当成变量或者字符串。
]]
message(STATUS "=============== if表达式,布尔常量 ===============")

if("YES")
    message(STATUS "YES")
else()
    message(STATUS "NOT YES")
endif()

if("TRUE")
    message(STATUS "TRUE")
else()
    message(STATUS "NOT TRUE")
endif()

if("FALSE")
    message(STATUS "FALSE")
else()
    message(STATUS "NOT FALSE")
endif()

if(NOT "NO")
    message(STATUS "NOT NO")
endif()

message(STATUS "=============== if表达式,变量有定义 ===============")

#[[
    if(<variable>)
    如果给定的变量有定义，且值不是0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, 空字符串, 以NOTFOUND为后缀时为真；
    其他情况该判断为假；
    注意：宏参数和环境变量不能这样判断，例如if(ENV{var})肯定为假；
]]
if(test)
    message(STATUS "变量test有定义了,其值是:${test}")
else()
    message(STATUS "变量test没有定义")
endif()

set(test 100) # 定义变量test

if(test)
    message(STATUS "变量test有定义了,其值是:${test}")
else()
    message(STATUS "变量test没有定义")
endif()

if(date)
    message(STATUS "变量date定义了,它的值是:${date}")
else()
    message(STATUS "变量date没有定义")
endif()

message(STATUS "=============== if表达式,string为双引号括起来的字符串 ===============")

#[[
    if(<string>)
    string为双引号括起来的字符串，除了以下两种情况外，其他情况均为假：
    当string的值为1, ON, YES, TRUE, Y或非0值时为真
    当CMP0054策略设置为OLD，则双引号括起来的字符串会当成变量解引用为变量的值（字符串对应的变量已经定义的情况下），之后再判定表达式的真假；
    当CMP0054策略设置为NEW，双引号括起来的字符串仅仅是作为字符串
]]
set(test "YES")
set(stest "test")
cmake_policy(SET CMP0054 NEW) # 设置策略CMP0054为NEW

if("Y")
    message(STATUS "Y IS TRUE")
endif()

if("test") # test被当成字符串，非constant的真值，因此判定为假
else()
    message(STATUS "字符串 'test' 的结果是: false")
    message(STATUS "test被当成字符串，非constant的真值，因此判定为假")
endif()

if("${stest}") # stest变量值为test，test被当成字符串，非constant的真值，因此判定为假
else()
    message("string $stest dereference value ${stest} result false")
    message(STATUS "stest变量值为test，test被当成字符串，非constant的真值，因此判定为假")
endif()

cmake_policy(SET CMP0054 OLD) # 设置策略CMP0054为OLD

if("test") # test被当成变量，解引用后值为YES，为constant真值
    message(STATUS "var test dereference value ${test}, result true")
    message(STATUS "test被当成变量，解引用后值为YES，为constant真值")
endif()

if("${stest}") # stest先解析为test，test被当成变量，解引用后值为YES，为constant真值
    message(STATUS "string $stest dereference value ${stest} then $test dereference value ${test} result true")
    message(STATUS "stest先解析为test，test被当成变量，解引用后值为YES，为constant真值")
endif()

message(STATUS "=============== if表达式,逻辑操作 ================")

#[[
3.2 逻辑操作
    if(NOT <condition>)：逻辑非操作
    if(<cond1> AND <cond2>)：逻辑与操作
    if(<cond1> OR <cond2>)：逻辑或操作
]]
# 逻辑非操作
if(NOT OFF)
    message(STATUS "NOT OFF IS TRUE")
else()
    message(STATUS "NOT OFF IS FALSE")
endif()

if(NOT YES)
    message(STATUS "NOT YES IS TRUE")
else()
    message(STATUS "NOT YES IS FALSE")
endif()

# 逻辑与操作
if(ON AND Y)
    message(STATUS "ON AND Y IS TRUE")
else()
    message(STATUS "ON AND Y IS FALSE")
endif()

if(223 AND OFF)
    message(STATUS "223 AND OFF IS TRUE")
else()
    message(STATUS "223 AND OFF IS FALSE")
endif()

# 逻辑或操作
if(IGNORE OR NOTFOUND)
    message(STATUS "IGNORE OR NOTFOUND IS TRUE")
else()
    message(STATUS "IGNORE OR NOTFOUND IS FALSE")
endif()

if(TRUE OR FALSE)
    message(STATUS "TURE OR FALSE IS TRUE")
else()
    message(STATUS "TURE OR FALSE IS FALSE")
endif()

if(NO OR YES)
    message(STATUS "NO OR YES IS TRUE")
else()
    message(STATUS "NO OR YES IS FALSE")
endif()

# 组合逻辑
if(TRUE AND(IGNORE OR YES)) # 注意括号的优先级最高，会先计算括号内的OR逻辑的值
    message("TRUE AND (IGNORE OR YES) is true")
else()
    message("TRUE AND (IGNORE OR YES) is false")
endif()

# set(price 99)
if(DEFINED PRICE AND(PRICE GREATER 100))
    message(STATUS "PRICE:${PRICE} GREATER 100")
else()
    if(DEFINED PRICE)
        message(STATUS "DEFINED PRICE:${PRICE}")
    else()
        message(STATUS "NOT DEFINED PRICE")
    endif()
endif()

message(STATUS "=============== if表达式,存在性检查 ================")
message(STATUS "=============== if表达式,判断是否为命令 ================")

# 3.3 存在性检查
# if(COMMAND command-name)：判断是否为命令
function(average min max avg)
    math(EXPR value "(${min} + ${max}) / 2")
    set(${avg} ${value} PARENT_SCOPE)
endfunction()

if(COMMAND average)
    message(STATUS "average is function")
    set(avg 0)
    average(33 55 avg)
    message(STATUS "avg:${avg}")
else()
    message(STATUS "average not function")
endif()

if(COMMAND message)
    message(STATUS "message is command")
else()
    message(STATUS "message is not command")
endif()

if(COMMAND getaddress)
    message(STATUS "getaddress is command")
else()
    message(STATUS "getaddress is not command")
endif()

message(STATUS "=============== if表达式,判断是否为策略 ================")

# if(POLICY policy-id)：判断是否为策略，策略的格式为CMP<NNNN>
if(POLICY CMP0054)
    message(STATUS "CMP0054 is policy")
else()
    message(STATUS "CMP0054 is not policy")
endif()

set(cmp CMP0001)

if(POLICY ${cmp})
    message(STATUS "${cmp} is policy")
else()
    message(STATUS "${cmp} is not policy")
endif()

set(cmp TEST_CMP)

if(POLICY ${cmp})
    message(STATUS "${cmp} is policy")
else()
    message(STATUS "${cmp} is not policy")
endif()

message(STATUS "=============== if表达式,判断变量是否存在列表中 ===============")

# if(<variable|string> IN_LIST <variable>)：判断变量是否存在列表中。
set(citys beijing shanghai wuhan;shenzhen;dalian) # 定义列表
message(STATUS "${citys}")
set(gz "guangzhou")

if(${gz} IN_LIST citys)
    message(STATUS "${gz} in the list: ${citys}")
else()
    message(STATUS "${gz} not in the list: ${citys}")
endif()

list(APPEND books android;python;c++;java;kotlin;php;javascript;html)
set(oc "ObjectC")
set(java "java")

if(${oc} IN_LIST books)
    message(STATUS "${oc} is in the list: ${books}")
else()
    message(STATUS "${oc} not in the list: ${books}")
endif()

if(${java} IN_LIST books)
    message(STATUS "${java} is in the list: ${books}")
else()
    message(STATUS "${java} not in the list: ${books}")
endif()

message(STATUS "============== if表达式,判断变量是否被定义 ================")

#[[
if(DEFINED <name>|CACHE{<name>}|ENV{<name>})：判断变量、缓存变量、环境变量是否存在，DEFINED不关注变量具体的值。
有两点需要注意：一是宏参数不是变量；二是无法直接判断一个变量是不是非缓存变量，因为不论是缓存变量还是非缓存变量，
只要变量存在，if(DEFINED someName)都会返回true，但是可以通过if(DEFINED CACHE{someName})判断出一个缓存变量是否存在，
因此判断一个非缓存变量是否存在，可以通过if(DEFINED someName AND NOT DEFINED CACHE{someName})实现。
]]
if(DEFINED var1)
    message(STATUS "变量var1被定义了,其值是:${var1}")
else()
    message(STATUS "变量var1没有被定义过")
endif()

set(var2 "NOTFOUND")

if(DEFINED var2)
    message(STATUS "变量var2被定义了,其值是:${var2}")
else()
    message(STATUS "变量var2没有被定义过")
endif()

if(var2) # 会按照if(constant)基本表达式来判断
    message(STATUS "var2 return true, value is ${var2}")
else()
    message(STATUS "var2 return false, value is ${var2}")
endif()

set(var2 "YES")

if(var2) # 会按照if(constant)基本表达式来判断
    message(STATUS "var2 return true, value is ${var2}")
else()
    message(STATUS "var2 return false, value is ${var2}")
endif()

if(DEFINED ENV{MY_TEST_ENV_VAR})
    message(STATUS "ENV MY_TEST_ENV_VAR defined: $ENV{MY_TEST_ENV_VAR}")
else()
    message(STATUS "ENV MY_TEST_ENV_VAR not defined")
endif()

set(cacheVar "YES" CACHE INTERNAL "internal var")

if(DEFINED CACHE{cacheVar})
    message("cache cacheVar defined: ${cacheVar}")
endif()

if(DEFINED cacheVar) # 无法区分普通变量或缓存变量
    message("cacheVar defined: ${cacheVar}")
endif()

if(DEFINED var2 AND(NOT DEFINED CACHE{var2})) # 判断一个变量是否为普通变量
    message("var2 defined and is not a cache variable")
endif()

message(STATUS "================ if表达式,判断是否为目标 ================")

# if(TARGET target-name)：判断是否为通过调用add_executable()、add_library()、add_custom_target()创建的构建目标
# 查找当前目录下的所有源文件，并将名称保存到 SRC_LIST 变量
# set(SRC_LIST main.cpp MathFunctions.cpp)
aux_source_directory(. SRC_LIST)
message(STATUS "SRC_LIST: ${SRC_LIST}")

# 查找 math 目录下的所有源文件，并将名称保存到 MATH_SRC_LIST 变量
# aux_source_directory(${PROJECT_SOURCE_DIR}/math MATH_SRC_LIST)
# message(STATUS "MATH_SRC_LIST: ${MATH_SRC_LIST}")

# 添加 math 子目录 (math 目录里必须有 CMakeLists.txt)，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处
add_subdirectory(math)

# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/math)

# 指示变量 SRC_LIST 中的源文件需要编译成一个名称为 Sample 的可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST} ${MATH_SRC_LIST})

# 添加链接库
target_link_libraries(${PROJECT_NAME} MathFunctions)

set(weather "weather")

if(TARGET ${PROJECT_NAME})
    message(STATUS "${PROJECT_NAME} is a target")
else()
    message(STATUS "${PROJECT_NAME} is not a target")
endif()

if(TARGET MathFunctions)
    message(STATUS "MathFunctions is a target")
else()
    message(STATUS "MathFunctions is not a target")
endif()

if(TARGET weather)
    message(STATUS "${weather} is a target")
else()
    message(STATUS "${weather} is not a target")
endif()

# if(TEST test-name)：判断是否为通过调用add_test()创建的测试对象
add_test(NAME mytest COMMAND ${PROJECT_NAME})

if(TEST mytest)
    message(STATUS "mytest is a test")
endif()
