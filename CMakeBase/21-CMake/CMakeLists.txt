# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME:  ${PROJECT_NAME}")

#[[
变量比较操作
    比较操作可以分为三大类：1）正则表达式匹配；2）按数值大小；3)按字典序。
]]
message(STATUS "==============   正则表达式比较 ==================")

#[[ 
1.正则表达式比较
    if(<variable|string> MATCHES regex)：正则表达式regex的格式可以参考这里。
]]
set(msg "&young@my name is shenzhen, wellcom to china")

# 匹配任何字符
if(msg MATCHES .*)
    message(STATUS "msg 匹配任何字符")
else()
    message(STATUS "msg 不匹配任何字符")
endif()

if(msg MATCHES "^[A-Za-z0-9]+")
    message(STATUS "msg 是数字或者字母开头的字符串")
else()
    message(STATUS "msg 不是数字或者字母开头的字符串")
endif()

set(msg "young@my name is shenzhen, wellcom to china")

if(msg MATCHES "^[A-Za-z0-9]+")
    message(STATUS "msg 是数字或者字母开头的字符串")
else()
    message(STATUS "msg 不是数字或者字母开头的字符串")
endif()

message(STATUS "==============   数值比较 ==================")

#[[
2.数值比较
  数值比较有小于（LESS）、大于（GREATER)、等于（EQUAL）、大于等于（GREATER_EQUAL）、小于等于（LESS_EQUAL）五种。
  需要注意：比较的两个变量是有效的数值，例如100、200这些是有效数值，"100"、"200"也是有效数值，但是"a100"、"200c"就不是有效数值。
  如果任意一个不是有效数值，会返回false。
]]
if("a100" GREATER 50)
else()
    message(STATUS "unvalid number a100")
endif()

if("100" GREATER "50")
    message(STATUS "GREATER")
endif()

if("2" LESS "3")
    message(STATUS "LESS")
endif()

if(5 EQUAL 5)
    message(STATUS "EQUAL")
endif()

if(5 LESS_EQUAL 5)
    message(STATUS "LESS_EQUAL - actual equal")
endif()

if(5 LESS_EQUAL 6)
    message(STATUS "LESS_EQUAL")
endif()

if(5 GREATER_EQUAL 5)
    message(STATUS "GREATER_EQUAL - actual equal")
endif()

if("7" GREATER_EQUAL 6)
    message(STATUS "GREATER_EQUAL")
endif()

message(STATUS "=============  字典序比较 ==============")

#[[
3.字典序比较
  数值比较有小于（STRLESS）、大于（STRGREATER)、等于（STREQUAL）、大于等于（STRGREATER_EQUAL）、
  小于等于（STRLESS_EQUAL）五种，注意不管是数还是字符串，都是按照字典序进行比较。
]]
if(21 STRLESS 3)
    message(STATUS "STRLESS - number")
endif()

if("21" STRLESS "3")
    message(STATUS "STRLESS - string")
endif()

if("abc" STREQUAL "abc")
    message(STATUS "STREQUAL")
endif()

if(5 STRGREATER 200000)
    message(STATUS "STRGREATER - number")
endif()

if("5" STRGREATER "200000")
    message(STATUS "STRGREATER - string")
endif()

if("abc" STRLESS_EQUAL "abc")
    message("STRLESS_EQUAL - actual equal")
endif()

if("abc" STRLESS_EQUAL "b")
    message(STATUS "STRLESS_EQUAL")
endif()

if("abc" STRGREATER_EQUAL "abc")
    message(STATUS "STRGREATER_EQUAL - actual equal")
endif()

if("abc" STRGREATER_EQUAL "abb")
    message(STATUS "STRGREATER_EQUAL")
endif()

message(STATUS "===============  版本号比较 ================")

# 6.版本号比较
# 版本号比较也有VERSION_LESS、VERSION_GREATER、VERSION_EQUAL、VERSION_LESS_EQUAL、VERSION_GREATER_EQUAL五种，需要注意两点：
# 版本号的格式为major[.minor[.patch[.tweak]]]的四段点分格式，每部分都是一个整数值；
# 如果版本号不是一个有效的整数，那么会从非数字的地方到尾部全部截断。例如1.2a22.3.4会截断成1.2，a后的部分全部被丢弃。
# 如果最开始就是非数字，那么版本号被当成0。
if(1.2.3.4 VERSION_GREATER 1.2a.3.5)
    message(STATUS "VERSION_GREATER - truncate")
endif()

if(1.2.3.4 VERSION_LESS 1.2.3.5)
    message(STATUS "VERSION_LESS")
endif()

if(1.2.3.4 VERSION_GREATER 1.1)
    message(STATUS "VERSION_GREATER")
endif()

if(1.2.3.4 VERSION_EQUAL 1.2.3.4)
    message(STATUS "VERSION_EQUAL")
endif()

if(1.2.3.4 VERSION_LESS_EQUAL 1.2.3.4)
    message(STATUS "VERSION_LESS_EQUAL - actual equal")
endif()

if(1.2.3.4 VERSION_LESS_EQUAL 1.2.3.5)
    message(STATUS "VERSION_LESS_EQUAL")
endif()

if(1.2.3.4 VERSION_GREATER_EQUAL 1.2.3.4)
    message(STATUS "VERSION_GREATER_EQUAL - actual equal")
endif()

if(1.2.3.4 VERSION_GREATER_EQUAL 1.2.3.2)
    message(STATUS "VERSION_GREATER_EQUAL")
endif()

message(STATUS "===============  变量展开 ================")

#[[
7.变量展开
  对于if(${var})这种形式，很容易理解是要将变量var的值放到if中进行判断。但是由于在CMake中，if表达式出现的比${}要早，
  因此早期对于if(var)这种形式，var到底是按照变量还是值/字符串来解析？CMake的做法是：首先看var是否是一个已经定义的变量，如果是，则需要将他的值替换到if中，否则就直把var当成一个字符串/值。
]]
# 来看一个例子:
set(var "NO")

if(var)
    message(STATUS "true for ${var}")
else()
    message(STATUS "false for ${var}")
endif()

#[[
    此处的var是一个已经定义好的变量，因此if判断转化为if("NO")，它会按照if(<constant>)最终的判定结果是false，因此上面的执行结果输出false for NO。
    如果没有set(var "NO")这句定义，那么if判断转为if(<variable>)，因为变量不存在而判定为false
]]

# 来看一个稍微复杂一点的例子
set(var "NO")
set(var2 "var")

if(${var2}) # 首先会解析${var2}，因此等价于if(var)，进而等价于if("NO")
    message(STATUS "true for ${var2}")
else()
    message(STATUS "false for ${var2}")
endif()

#[[
在if命令执行之前，${var2}首先会执行，会替换成变量var2的值，因此变成if(var)，然后仍然会先去判断var是否是一个已经定义好的变量。
因此后续的执行过程与上个例子一样。if判断转化为if("NO")，它会按照if(<constant>)最终的判定结果是false，输出false for NO。
如果没有set(var "NO")这句赋值，那么if判断转为if(<variable>)，因为变量不存在而判定为false。
当然，如果把if(${var2})替换成if(var2)，会转化成if("var")，那么if判断转为if(<string>)，字符串结果判定为true.
]]
set(var "NO")
set(var2 "var")

if(var2) # var2是变量，因此等价于if("var")，此时"var"会当成字符串而不是变量
    message(STATUS "true for ${var2}")
else()
    message(STATUS "false for ${var2}")
endif()