# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "=============== Cmake命令之set介绍 ========================")

#[[
命令格式
    set(<variable> <value>... [PARENT_SCOPE]) #设置普通变量
    set(<variable> <value>... CACHE <type> <docstring> [FORCE]) #设置缓存条目
    set(ENV{<variable>} [<value>]) #设置环境变量

set命令可以设置普通变量、缓存条目、环境变量三种变量的值，分别对应上述三种命令格式。
set的值<value>...表示可以给变量设置0个或者多个值，当设置多个值时（大于2个），多个值会通过分号连接符连接成一个真实的值赋值给变量，当设置0个值时，实际上是把变量变为未设置状态，相当于调用unset命令。
]]

#[[
一. 设置普通变量
  命令格式：set(<variable> <value>... [PARENT_SCOPE])
  命令含义：将变量variable设置为值<value>...，变量variable的作用域为调用set命令的函数或者当前目录，如果使用了PARENT_SCOPE选项，意味着该变量的作用域会传递到上一层
（也就是上一层目录或者当前函数的调用者，如果是函数则传递到函数的调用者，如果是目录则传递到上一层目录），并且在当前作用域该变量不受带PARENT_SCOPE选项的set命令的影响
（如果变量之前没有定义，那么在当前作用域仍然是无定义的；如果之前有定义值，那么值和之前定义的值保持一致）。
  关于变量的作用域：每一个新的目录或者函数都会创建一个新的作用域，普通变量的作用域，如果不使用PARENT_SCOPE选项，只能从外层往内层传递。
]]

#1、先来看最常用的用法，设置变量为一个给定的值
set(WEATHER snow)
message(STATUS "WEATHER:${WEATHER}")

#2、设置变量为多个给定的值
set(CITYS 深圳 北京 上海 武汉 广州)
set(SECTS "华山派;武当派;少林寺;峨嵋派;嵩山派")
message(STATUS "CITYS:${CITYS}")
message(STATUS "SECTS:${SECTS}")

#3、设置变量为空
set(FLOWER "玫瑰花")
set(NAME 乔峰)
set(HEROS 杨过 小龙女 郭靖 黄蓉)
message(STATUS "FLOWER:${FLOWER}")
message(STATUS "NAME:${NAME}")
message(STATUS "HEROS:${HEROS}")
unset(FLOWER)
set(NAME "")
set(HEROS "")
message(STATUS "FLOWER:${FLOWER}")
message(STATUS "NAME:${NAME}")
message(STATUS "HEROS:${HEROS}")

message(STATUS "============================================================")

#4、在函数内使用选项PARENT_SCOPE，对应的作用域只能传递到调用它的函数。
#[[
场景1：在函数内使用选项PARENT_SCOPE定义变量，在函数定义的文件中（非另一个函数中）使用该变量。
结果：变量无定义。
结论：函数内定义的变量，在函数定义的文件中调用，找不到变量的定义。
]]

function(testFunction1 arg1)
    set(PHONE ${arg1} PARENT_SCOPE)
    message(STATUS "in function,PHONE:${PHONE}")
endfunction()
message(STATUS "in directory,PHONE:${PHONE}")
testFunction1("IPhone 6s Plus")
message(STATUS "in directory,PHONE:${PHONE}")

message(STATUS "============================================================")

#[[
场景2：在函数内使用选项PARENT_SCOPE定义变量，在函数内使用该变量。
结果：变量无定义。
结论：函数内使用选项PARENT_SCOPE定义的变量，在函数内也是无定义的。
]]
function(testFunction2 arg1)
    set(CAR ${arg1} PARENT_SCOPE)
    message(STATUS "in function,CAR:${CAR}")
endfunction()
message(STATUS "in directory,CAR:${CAR}")
testFunction2("Jeep")
message(STATUS "in directory,CAR:${CAR}")

message(STATUS "============================================================")
#[[
场景3：在函数内使用选项PARENT_SCOPE定义变量，在函数内使用该变量，并且使用set命令不带PARENT_SCOPE选项定义过该变量。
结果：函数内的变量值为不带PARENT_SCOPE选项的set命令所定义的。
结论：选项PARENT_SCOPE定义的变量作用域在上一层函数，当前函数的变量必须使用不带选项PARENT_SCOPE定义。
]]
function(testFunction3 arg1)
    set(TV 长虹)
    set(TV ${arg1} PARENT_SCOPE)
    message(STATUS "in function,TV:${TV}")
endfunction()
message(STATUS "in directory,TV:${TV}")
testFunction3(创维)
message(STATUS "in directory,TV:${TV}")

message(STATUS "============================================================")

#[[
场景4：在函数（示例中为test_fn）内使用选项PARENT_SCOPE定义变量，在另一个函数（调用者，示例中为test_fn_parent）内调用该函数。
结果：调用者函数内有该变量的定义。
结论：选项PARENT_SCOPE将变量传递到上一层调用函数。
]]
function(testFunction4 arg1)
    set(ROAD "深南大道")
    set(ROAD ${arg1} PARENT_SCOPE)
    message(STATUS "in function,ROAD:${ROAD}")
endfunction()

function(testFunction arg1)
    testFunction4(${arg1})
    message(STATUS "in parent function,ROAD:${ROAD}")
endfunction()
message(STATUS "in directory,ROAD:${ROAD}")
testFunction("北环大道")

message(STATUS "============================================================")

#[[
5、在目录内使用选项PARENT_SCOPE，对应的作用域只能传递到上层目录，变量的传递过程与4）中函数的场景类似，不再赘述。
注意一点：本例在test和test/sub下分别创建一个CMakeLists.txt文件。
]]
add_subdirectory(math)
message(STATUS "in top level,COMPUTER:${COMPUTER}")

