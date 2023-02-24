# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "======= 用 cmake_parse_arguments 解析参数 =======")

#[[
用 cmake_parse_arguments 解析参数
    我们一般用 cmake_parse_arguments 命令来解析函数或宏的参数。用 cmake_parse_arguments 命令，可以解析复杂的参数形式。

cmake_parse_arguments 有两种形式，语法如下：
    cmake_parse_arguments(<prefix> <options> <one_value_keywords>
                        <multi_value_keywords> <args>...)
    cmake_parse_arguments(PARSE_ARGV <N> <prefix> <options>
                        <one_value_keywords> <multi_value_keywords>)
]]

#[[
我们以 cmake_parse_arguments 的第一种形式为例。
在设计时，有三种参数，
    第一种参数是 <options> 表示可选关键词列表，如果传入参数包含此变量名，则为 TRUE，反之为 FALSE。
    第二种参数是 <one_value_keywords> 表示单值关键词列表，每个关键词仅对应一个值。
    第三种参数是 <multi_value_keywords> 表示多值关键词列表，每个关键词可对应多个值。

要解析的参数 <args>...，我们一般传入为 ${ARGN} 即可，一般定义的函数或宏是无参的，除非第一个参数不是关键词，那么有多少非关键词变量，定义多少形参。
我们将参数 ${ARGN} 根据 <options>, <one_value_keywords>, <multi_value_keywords> 规则进行解析，解析出来的新变量名根据 <prefix> 前缀，按照 prefix_参数名 的形式。
可选参数，我们用 if 语句来实现。
]]

#[[ 案例1，我们想定义一个类似 install 命令，用于安装目标到指定的目录。目前案例仅仅是分析传参，下一个案例是功能的实现框架。
要实现的命令形式，如下：
my_install(TARGETS <target>... 
	[LIBRARY|RUNTIME|OBJECTS] 
	[CONFIGURATIONS [Debug|Release|...]]
#[[	DESTINATION <dir> 
	[COMPONENT <component>] 
	[RENAME <name>] 
	[OPTIONAL]
)

我们知道 TARGETS 为多值关键词，LIBRARY,RUNTIME,OBJECTS 为可选关键词，CONFIGURATIONS,DESTINATION,COMPONENT,RENAME 为单值关键词，OPTIONAL 为可选关键词。
#]]
# 代码如下：
macro(my_install)
    set(options LIBRARY RUNTIME OBJECTS OPTIONAL)
    set(oneValueArgs DESTINATION COMPONENT RENAME)
    set(multiValueArgs TARGETS CONFIGURATIONS)
    cmake_parse_arguments(MY_INSTALL "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # 多值关键词
    message("MY_INSTALL_TARGETS: ${MY_INSTALL_TARGETS}")

    # 可选关键词
    message("MY_INSTALL_LIBRARY: ${MY_INSTALL_LIBRARY}")
    message("MY_INSTALL_RUNTIME: ${MY_INSTALL_RUNTIME}")
    message("MY_INSTALL_OBJECTS: ${MY_INSTALL_OBJECTS}")

    # 多值关键词
    message("MY_INSTALL_CONFIGURATIONS: ${MY_INSTALL_CONFIGURATIONS}")

    # 单值关键词
    message("MY_INSTALL_DESTINATION: ${MY_INSTALL_DESTINATION}")
    message("MY_INSTALL_COMPONENT: ${MY_INSTALL_COMPONENT}")
    message("MY_INSTALL_RENAME: ${MY_INSTALL_RENAME}")

    # 可选关键词
    message("MY_INSTALL_OPTIONAL: ${MY_INSTALL_OPTIONAL}")

    # 特殊变量
    # 未解析的参数
    message("MY_INSTALL_UNPARSED_ARGUMENTS: ${MY_INSTALL_UNPARSED_ARGUMENTS}")

    # 关键字缺失值的参数
    message("MY_INSTALL_KEYWORDS_MISSING_VALUES: ${MY_INSTALL_KEYWORDS_MISSING_VALUES}")
endmacro()

# my_install() 被调用:
my_install(TARGETS foo bar LIBRARY CONFIGURATIONS DESTINATION bin OPTIONAL blub)

#[[
在 cmake_parse_arguments 调用之后，将设置以下变量
MY_INSTALL_TARGETS: foo;bar
MY_INSTALL_LIBRARY: TRUE
MY_INSTALL_RUNTIME: FALSE
MY_INSTALL_OBJECTS: FALSE
MY_INSTALL_CONFIGURATIONS:
MY_INSTALL_DESTINATION: bin
MY_INSTALL_COMPONENT:
MY_INSTALL_RENAME:
MY_INSTALL_OPTIONAL: TRUE
MY_INSTALL_UNPARSED_ARGUMENTS: blub
MY_INSTALL_KEYWORDS_MISSING_VALUES: CONFIGURATIONS

TARGETS 为多值关键词，传入值为 foo;bar。
LIBRARY,RUNTIME,OBJECTS 为可选关键词，因为仅传入 LIBRARY，LIBRARY 被设置为 TRUE，其他都设置为 FALSE。
CONFIGURATIONS 仅传入关键字，并未传入值，所以值也为空。
COMPONENT,RENAME 为单值关键词，未被传入，所以值为空。
DESTINATION 为单值关键词，传入值为 bin。
OPTIONAL 为可选关键词，被设置为 TRUE。

有两种特殊的变量，
第一个 <prefix>_UNPARSED_ARGUMENTS 表示未解析的参数，表示传入的参数并不符合 cmake_parse_arguments 命令解析规则，所以有 blub。
第二个 <prefix>_KEYWORDS_MISSING_VALUES 表示关键字缺失值的参数，表示单值关键词或多值关键词，仅传入关键字，并未传入值，所以有 CONFIGURATIONS。
]]
message(STATUS "=============== 实现 [LIBRARY|RUNTIME|OBJECTS]，可选值，或者三个选一个 ===============")

# 案例2，对案例1，增加功能的实现框架。
# 实现 [LIBRARY|RUNTIME|OBJECTS]，可选值，或者三个选一个。
macro(my_install)
    set(options LIBRARY RUNTIME OBJECTS OPTIONAL)
    set(oneValueArgs DESTINATION COMPONENT RENAME)
    set(multiValueArgs TARGETS CONFIGURATIONS)
    cmake_parse_arguments(MY_INSTALL "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # 实现 [LIBRARY|RUNTIME|OBJECTS]，可选值，或者三个选一个。
    set(nBool 0)

    if(MY_INSTALL_LIBRARY)
        math(EXPR nBool "${nBool} + 1")
    endif()

    if(MY_INSTALL_RUNTIME)
        math(EXPR nBool "${nBool} + 1")
    endif()

    if(MY_INSTALL_OBJECTS)
        math(EXPR nBool "${nBool} + 1")
    endif()

    if(${nBool} EQUAL 1)
        if(${MY_INSTALL_LIBRARY})
            message("TODO LIBRARY...")
        elseif(${MY_INSTALL_RUNTIME})
            message("TODO RUNTIME...")
        elseif(${MY_INSTALL_OBJECTS})
            message("TODO OBJECTS...")
        endif()
    elseif(nBool EQUAL 0)
        message("[LIBRARY|RUNTIME|OBJECTS] NOTHING...")
    else()
        message("参数错误: [LIBRARY|RUNTIME|OBJECTS]")
    endif()

    message("MY_INSTALL_LIBRARY: ${MY_INSTALL_LIBRARY}")
    message("MY_INSTALL_RUNTIME: ${MY_INSTALL_RUNTIME}")
    message("MY_INSTALL_OBJECTS: ${MY_INSTALL_OBJECTS}")
endmacro()

# 调用形式
my_install()
my_install(LIBRARY)
my_install(OBJECTS)
my_install(LIBRARY RUNTIME)
my_install(OBJECTS RUNTIME)
my_install(LIBRARY OBJECTS RUNTIME)

message(STATUS "=============== 实现 [CONFIGURATIONS [Debug|Release|MinSizeRel|RelWithDebInfo]] 参数为多值关键词，但是值为某些固定选项。 ===============")

# 实现 [CONFIGURATIONS [Debug|Release|MinSizeRel|RelWithDebInfo]] 参数为多值关键词，但是值为某些固定选项。
macro(my_install)
    set(options LIBRARY RUNTIME OBJECTS OPTIONAL)
    set(oneValueArgs DESTINATION COMPONENT RENAME)
    set(multiValueArgs TARGETS CONFIGURATIONS)
    cmake_parse_arguments(MY_INSTALL "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # 实现 `[CONFIGURATIONS [Debug|Release|MinSizeRel|RelWithDebInfo]]` 参数为多值关键词，但是值为某些固定选项。
    message("MY_INSTALL_CONFIGURATIONS: ${MY_INSTALL_CONFIGURATIONS}")

    if(MY_INSTALL_CONFIGURATIONS)
        foreach(loop_var IN LISTS MY_INSTALL_CONFIGURATIONS)
            string(STRIP ${loop_var} loop_var)
            string(TOUPPER ${loop_var} loop_var)

            # message("loop_var: ${loop_var}")
            if(${loop_var} STREQUAL "DEBUG")
                message("TODO DEBUG...")
            elseif(${loop_var} STREQUAL "RELEASE")
                message("TODO RELEASE...")
            elseif(${loop_var} STREQUAL "MINSIZEREL")
                message("TODO MINSIZEREL...")
            elseif(${loop_var} STREQUAL "RELWITHDEBINFO")
                message("TODO RELWITHDEBINFO...")
            else()
                message("参数错误: [CONFIGURATIONS [Debug|Release|MinSizeRel|RelWithDebInfo]]")
            endif()
        endforeach()
    endif()
endmacro()

# 调用形式
my_install()
my_install(CONFIGURATIONS Debug)
my_install(CONFIGURATIONS Release)
my_install(CONFIGURATIONS Debug Release)
my_install(CONFIGURATIONS Debug Release RelWithDebInfo)
my_install(CONFIGURATIONS Debug Release MinSizeRel RelWithDebInfo SizeRel)

message(STATUS "============ 用 foreach 语句 来处理参数 =============")

# 我们有时会用 foreach 语句 来处理参数。
function(foo STATUS)
    message(STATUS "foo(STATUS <message>...)")
    set(_message "STATUS:${STATUS}")
    list(LENGTH ARGN _message_len)
    message(STATUS "_message_len:${_message_len}")

    if(${_message_len} EQUAL 1)
        string(APPEND _message ", <message>:${message}")
    elseif(${_message_len} GREATER 2)
        set(i 0)

        foreach(loop_var IN LISTS ARGN)
            string(APPEND _message ", <message_${i}>:${loop_var}")
            math(EXPR i "${i} + 1")
        endforeach()
    endif()

    message(STATUS "${_message}")
endfunction()

# 调用形式
foo(STATUS "Hello World")
foo(STATUS "Hello" " World" "!!!")