# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME:${PROJECT_NAME}")

message(STATUS "=================  CMake 宏和函数 =================")

#[[
1. 函数定义
函数: function, endfunction，支持语法如下：
    # function
    function(<name> [<arg1> ...])
    # endfunction
    endfunction([<name>])

概要
    function(<name> [<arg1> ...])
    <commands>
    endfunction()

定义个名为 <name> 的函数，该函数接收名为 <arg1> … 的参数，<commands> 表示函数定义的功能，在调用函数之前不会被执行。
一个函数打开一个新的作用域，请参阅 set(var PARENT_SCOPE)。
https://cmake.org/cmake/help/v3.19/command/set.html
有关函数内部策略的行为，请参阅 cmake_policy()。
https://cmake.org/cmake/help/v3.19/command/cmake_policy.html
小写。
]]

#[[
2. 函数调用(Invocation)
    函数调用的函数名不区分大
]]

# 案例，定义一个名为 “foo” 的函数，根据不同大小写的函数名调用。
# 函数定义
function(foo)
    message(STATUS "这是不带参数的foo()函数")
endfunction()

# 函数调用,方式1
foo()
Foo()
FOO()

# 函数调用,cmake_language 函数调用,方式2
cmake_language(CALL foo)

message(STATUS "============= 函数参数(Arguments) ==============")

# 3 函数参数(Arguments)
#[[
3.1 用 形参 引用参数
    当函数被调用时，首先通过实参替换形参 ${arg1}, …，然后作为普通命令调用。
]]
# 案例，定义一个对变量求和的函数
function(foo1 x1 x2 x3)
    math(EXPR sum "${x1} + ${x2} + ${x3}")
    message(STATUS "x1:${x1},x2:${x2},x3:${x3},sum:${sum}")
endfunction()

foo1(10 20 30)

# 注意：似乎是通过 set(x1 10) 命令将实参值 10 设置到形参变量 x1 中，然后在函数内通过 ${x1} 形式引用参数值。

#[[
3.2 用 ARGC 变量 和 ARGVn 变量 引用参数
除了引用形参之外，你还可以引用 ARGC 变量 和 ARGVn 变量 来引用参数，ARGC 表示参数数量，以及 ARGV0, ARGV1, ARGV2, … 将具有传入参数的值。这有助于创建带有可选参数的函数。
]]
# 案例，定义一个函数，输出参数数量和传入的每个参数值
function(foo2 x1 x2 x3)
    message(STATUS "参数数量:${ARGC}, ARGV0:${ARGV0}, ARGV1:${ARGV1}, ARGV2:${ARGV2}")
endfunction()

foo2(10 20 30)

# 注意: 用 ARGVn 变量引用实参值，与定义的形参 x1, x2, x3 无关，只与传入的实参有关，就算函数定义是 function(main)，该函数也照样可以使用，或者说这样还更好。
# 案例，用 ARGV 变量 引用所有参数
function(foo3)
    message(STATUS "ARGV:${ARGV}")
endfunction()

foo3(10 20 30 10 10)

#[[
3.3 用 ARGN 变量引用预期之外的参数
    此外，ARGN 变量保存超过形参列表之后的参数。如果实参数量大于形参数量，用 ARGN 变量引用预期之外的参数。
]]
# 案例，用 ARGN 变量引用预期之外的参数
function(foo4 x1 x2 x3)
    message(STATUS "ARGN:${ARGN}")
endfunction()

foo4(10 20 30 40 50)

#[[
4. 形参为变量
    之前案例中形参都为值，那么变量取值的语法 ${VAR} 获取的是值。如果形参为变量的话，那么获取的值为变量，要想获取值的话使用 ${${VAR}}。
]]

# 案例，如果形参为变量的话，参数引用的就是变量
set(a1 10)
set(a2 20)
set(a3 30)

function(foo5 x1 x2 x3)
    message(STATUS "x1:${x1}, x2:${x2}, x3:${x3}")
    message(STATUS "x1:${${x1}}, x2:${${x2}}, x3:${${x3}}")
endfunction()

foo5(a1 a2 a3)