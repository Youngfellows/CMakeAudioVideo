# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "=============== CMake 宏 =================")

# 1. CMake 宏
#[[
1.1 CMake 宏 的定义
宏: macro, endmacro，支持语法如下：
    # macro
    macro(<name> [<arg1> ...])
    # endmacro
    endmacro([<name>])

概要
    macro(<name> [<arg1> ...])
    <commands>
    endmacro()

定义个名为 <name> 的宏，该宏接收名为 <arg1> … 的参数，<commands> 表示宏定义的功能，在调用宏之前不会被执行。

有关宏内部策略的行为，请参阅 cmake_policy()。
https://cmake.org/cmake/help/v3.19/command/cmake_policy.html
]]

#[[
1.2 CMake 宏调用(Invocation)
宏调用名也不区分大小写。
与函数的案例一样，定义一个名为 “foo” 的宏，调用时也可以用 “foo”, “Foo”, “FOO”，也可以使用 cmake_language(CALL ...) 子命令调用宏。
宏也建议，宏名全部使用小写。

参数(Arguments)
    调用宏时的参数定义和使用，也与函数一样。
    用 形参 引用参数
    用 ARGC 变量 和 ARGVn 变量 引用参数，用 ARGV 变量 引用所有参数
    用 ARGN 变量引用预期之外的参数
]]
macro(myFoo1 x1 x2 x3)
    math(EXPR value "${x1} + ${x2} + ${x3}")
    message(STATUS "x1:${x1},x2:${x2},x3:${x3},sum:${value}")
endmacro()

myFoo1(10 20 30)

macro(myFoo2 x1 x2 x3)
    math(EXPR value "${x1} + ${x2} + ${x3}")
    message(STATUS "x1:${x1},x2:${x2},x3:${x3},sum:${value}")
    message(STATUS "ARGC:${ARGC},ARGV0:${ARGV0},ARGV1:${ARGV1},ARGV2:${ARGV2}")
endmacro()

myFoo2(10 20 30)

macro(myFoo3 x1 x2 x3)
    math(EXPR value "${x1} + ${x2} + ${x3}")
    message(STATUS "ARGV:${ARGV}")

    foreach(arg ${ARGV})
        message(STATUS "${arg}")
    endforeach()
endmacro()

myFoo3(33 44 55)

macro(myFoo4 x1 x2 x3)
    math(EXPR value "${x1} + ${x2} + ${x3}")
    message(STATUS "ARGV:${ARGV}")
    message(STATUS "ARGN:${ARGN}")

    foreach(arg ${ARGN})
        message(STATUS "${arg}")
    endforeach()
endmacro()

myFoo4(11 22 33 66 77 88)

message(STATUS "=============== 函数与宏的区别 =================")

#[[
2. 函数与宏的区别
    macro() 与 function() 非常相似。尽管如此，还有一些重要的区别。
在函数中，ARGN, ARGC, ARGV and ARGV0, ARGV1, … 是 CMake 意义上的变量。在宏中，它们不是，它们是字符串替换，就像 C 预处理器 对 宏 所做的一样。这会产生许多后果，如下面的 “参数警告” 部分所述。
宏和函数之间的另一个区别是控制流。函数的执行 通过将控制权从调用语句转移到函数体。宏的执行 就像将宏主题粘贴到调用语句的位置一样。
这导致宏体中的 return() 不仅终止宏的执行；相反，控制权是从宏调用的范围内返回的。为了避免混淆，建议在宏中完全避免 return()。
]]

# 案例，在函数仅仅用 return 将控制权返回给函数的调用者
function(select option)
    if(${option} EQUAL 1)
        message(STATUS "选择选项1")
        return()
    elseif(${option} EQUAL 2)
        message(STATUS "选择选项2")
        return()
    elseif(${option} EQUAL 3)
        message(STATUS "选择选项3")
        return()
    else()
        message(STATUS "未知选项")
    endif()

    message(STATUS "继续执行")
endfunction()

select(1)
select(2)
select(0)

# 案例，如果函数返回返回值，并不是使用 return，而是通过参数
function(foo x1 x2 x3 out_var)
    math(EXPR value "${x1} + ${x2} + ${x3}")
    message(STATUS "x1:${x1}, x2:${x2}, x3:${x3}")
    set(${out_var} ${value} PARENT_SCOPE)
endfunction()

foo(10 20 30 RET)
message(STATUS "sum:${RET}")

#[[
注意，形参原本的作用域在函数内，只能在函数内使用，但是通过 set(... PARENT_SCOPE) 将变量的作用域设置为当前作用域之外，你可以使用父作用域，也就是作用于函数之外。
注意，如果在函数内部通过 PARENT_SCOPE 设置变量，该变量可以在函数之外使用。

与函数不同，CMAKE_CURRENT_FUNCTION, CMAKE_CURRENT_FUNCTION_LIST_DIR, CMAKE_CURRENT_FUNCTION_LIST_FILE, CMAKE_CURRENT_FUNCTION_LIST_LINE 变量，不是为宏设置的。
]]

# 例如，在函数内部设置变量 out_var 的值为 100，在函数外部输出也为 100。
function(foo)
    set(out_var 100 PARENT_SCOPE)
endfunction()

foo()
message(STATUS "out_var:${out_var}")

message(STATUS "============== 宏参数警告(Argument Caveats) ================")

#[[
3. 参数警告(Argument Caveats)
宏与函数在调用时，参数处理方面的不同。
由于 ARGN, ARGC, ARGV, ARGV0 等，不是变量，因此你无法使用，诸如以下语句：
if(ARGV1) # ARGV1 is not a variable
if(DEFINED ARGV2) # ARGV2 is not a variable
if(ARGC GREATER 2) # ARGC is not a variable
foreach(loop_var IN LISTS ARGN) # ARGN is not a variable

在第一种情况下，你可以使用 if(${ARGV1})。
在第二种和第三种情况下，检查是否将可选变量传递给宏的正确方法是使用 if(${ARGC} GREATER 2)。
在最后一种情况下，你可以使用 foreach(loop_var ${ARGN})
如果需要包含它们，可以使用
set(list_var "${ARGN}")
foreach(loop_var IN LISTS list_var)
]]

# 函数的ARGN
function(foo x1 x2 x3)
    message(STATUS "函数的ARGN")

    foreach(loop_var IN LISTS ARGN)
        message(STATUS "${loop_var}")
    endforeach()
endfunction()

foo(11 22 33 44 55 66 77 88)

# 宏的ARGN
macro(foo x1 x2 x3)
    message(STATUS "宏的ARGN")

    foreach(loop_var ${ARGN})
        message(STATUS "${loop_var}")
    endforeach()
endmacro()

foo(11 22 33 44 55 66 77 88)

# 注意：如果在调用宏的范围内有一个同名的变量，则使用未引用的名称，将使用现有变量而不是参数。例如：
macro(bar)
    foreach(arg IN LISTS ARGN)
        message(STATUS "${arg}")
    endforeach()
endmacro()

function(foo)
    bar(x y z)
endfunction()

foo(a b c)

# 将遍历 a;b;c，而不是预期那样遍历 x;y;z。原因是，bar 会在 foo 中展开，所以 ARGN 称为 foo 中的变量。
