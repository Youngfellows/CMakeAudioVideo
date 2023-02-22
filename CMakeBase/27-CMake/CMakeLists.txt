# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message("PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "============= CMake 列表操作 ================")

#[[
概要(Synopsis)
    Reading
        list(LENGTH <list> <out-var>)
        list(GET <list> <element index> [<index> ...] <out-var>)
        list(JOIN <list> <glue> <out-var>)
        list(SUBLIST <list> <begin> <length> <out-var>)

    Search
        list(FIND <list> <value> <out-var>)

    Modification
        list(APPEND <list> [<element>...])
        list(FILTER <list> {INCLUDE | EXCLUDE} REGEX <regex>)
        list(INSERT <list> <index> [<element>...])
        list(POP_BACK <list> [<out-var>...])
        list(POP_FRONT <list> [<out-var>...])
        list(PREPEND <list> [<element>...])
        list(REMOVE_ITEM <list> <value>...)
        list(REMOVE_AT <list> <index>...)
        list(REMOVE_DUPLICATES <list>)
        list(TRANSFORM <list> <ACTION> [...])

    Ordering
        list(REVERSE <list>)
        list(SORT <list> [...])
    
    注意: <list> 是列表变量。
]]

#[[
CMake列表介绍(Introduction)
    列表适用于简单的任务，例如 文件列表，而不是应用于复杂的数据处理任务。
    列表的 修改的子命令(包括 APPEND, FILTER, INSERT, POP_BACK, POP_FRONT, PREPEND, REMOVE_ITEM, REMOVE_AT, 
    REMOVE_DUPLICATES，不包括 TRANSFORM) 和 排序的子命令(包括 REVERSE, SORT) 
]]
message(STATUS "=============== 创建列表 ==================")

# 1. 为列表创建新值
set(CITYS ShenZhen GuangZhou ShangHai WuHan)
message(STATUS "CITYS:${CITYS}")
list(APPEND CITYS TianJing GuiYang)
message(STATUS "CITYS:${CITYS}")

# 与 set() 命令类似，list 命令在当前作用域创建新值，表示在函数内部使用 list 命令，并不会影响函数外的变量。
# 定义函数
function(testListAppend animals animal)
    list(APPEND ${animals} ${animal})
    message(STATUS "Append,ANIMALS:${ANIMALS}")
endfunction()

set(ANIMALS "加菲猫;牧羊犬;大熊猫;海豚")
message(STATUS "Before,ANIMALS:${ANIMALS}")
testListAppend(ANIMALS 北极熊)
message(STATUS "After,ANIMALS:${ANIMALS}")

#[[
如何影响函数外的变量，表示要影响父作用域，需要向上传播这些操作结果，可以将 set() 与 PARENT_SCOPE 一起使用，
或 set() 与 CACHE INTERNAL 一起使用，或 使用其他的值传播方式。
]]
function(testListAppendRef animals animal)
    list(APPEND ${animals} ${animal})
    set(${animals} ${${animals}} PARENT_SCOPE)
    message(STATUS "Append,ANIMALS:${ANIMALS}")
endfunction()

set(ANIMALS "狮子;加菲猫;牧羊犬;大熊猫;海豚")
message(STATUS "Before,ANIMALS:${ANIMALS}")
testListAppendRef(ANIMALS 北极熊)
message(STATUS "After,ANIMALS:${ANIMALS}")

#[[尽管 CMake 所有值都存储为字符串，包括布尔值和路径。但是在某些情况中，字符串可能会被视为列表。在这种情况下，字符串通过 ; 
符号分割列表中的每个元素。

要创建列表，可以使用 set 命令，例如，set(srcs a.c b.c c.c) 创建一个包含 a.c;b.c;c.c 的列表，
而 set(srcs "a.c b.c c.c") 创建一个字符串或一个包含一个元素的列表。
]]
# 下面构建列表的形式都是相同的:
set(srcs "a.c;b.c;c.c")
message(STATUS "${srcs}")
set(srcs a.c b.c c.c)
message(STATUS "${srcs}")
set(srcs a.c "b.c;c.c")
message(STATUS "${srcs}")

set(NAMES 杨过;小龙女;郭靖;黄蓉;乔峰;)
message(STATUS "${NAMES}")
set(NAMES "杨过;小龙女;郭靖;黄蓉;乔峰;")
message(STATUS "${NAMES}")

set(KUNGFUS 六脉神剑 独孤九剑 化骨绵掌 一阳指 凌波微步)
message(STATUS "${KUNGFUS}")
set(KUNGFUS 六脉神剑 独孤九剑 "化骨绵掌;一阳指;凌波微步")
message(STATUS "${KUNGFUS}")

message(STATUS "================ 列表读取(Reading) ===============")

# 2. 列表读取(Reading)
#[[
返回列表的长度
    list(LENGTH <list> <out-var>)

例如，list(LENGTH A A_len) 获取列表 A 的长度 A_len
]]
list(APPEND KUNGFUS 寒冰神掌 蛤蟆功)
message(STATUS "KUNGFUS:${KUNGFUS}")
list(LENGTH KUNGFUS kongfuLen)
message(STATUS "kongfuLen:${kongfuLen}")

#[[
返回列表的元素，由索引指定，可以一次获得多个元素值。
    list(GET <list> <element index> [<index> ...] <out-var>)

    例如，list(GET A 2 A_new) 获取索引为 2 的元素，并且保存在新列表 A_new 中
    例如，list(GET A 2 4 A_new) 获取索引为 2, 4 的元素，并且保存在新列表 A_new 中
    例如，list(GET A 2 4 3 A_new) 获取索引为 2, 4, 3 的元素，并且保存在新列表 A_new 中
]]
set(CITYS "北京;武汉;大连;深圳;长沙;贵阳;太原;拉萨;乌鲁木齐")
message(STATUS "CITYS:${CITYS}")
list(GET CITYS 2 city)
message(STATUS "city:${city}")
list(GET CITYS 2 4 subCitys)
message(STATUS "subCitys:${subCitys}")
list(GET CITYS 2 4 7 subCitys)
message(STATUS "subCitys:${subCitys}")

#[[
返回连接列表的字符串。将列表中所有元素连接为一个字符串。
    list(JOIN <list> <glue> <out-var>)

例如，list(JOIN A " " A_new) 连接列表字符串，并替换分隔符分号 ; 为 空格 。如果列表值为 a;b;c，替换后为 a b c
]]
set(KUNGFUS "一阳指;乾坤大挪移;六脉神剑;九阴白骨掌;独孤九剑;吸星大法;玄铁剑法")
message(STATUS "KUNGFUS:${KUNGFUS}")
list(JOIN KUNGFUS " " kongfuString)
message(STATUS "kongfuString:${kongfuString}")
list(JOIN KUNGFUS "xx" kongfuString)
message(STATUS "kongfuString:${kongfuString}")

#[[
返回列表的子列表。
    list(SUBLIST <list> <begin> <length> <out-var>)

例如，list(SUBLIST A 1 4 A_new)) 从列表 A 中，截取索引为 1 的 4 个元素，保存在新列表 A_new 中。
]]
list(SUBLIST KUNGFUS 1 4 subKongfus)
message(STATUS "subKongfus:${subKongfus}")

message(STATUS "============= 列表搜索(Search) ==============")

# 2.列表搜索(Search)
#[[
返回列表指定元素的索引，如果未找到返回 -1。
    list(FIND <list> <value> <out-var>)

例如，list(FIND A e A_out_var) 从列表中搜索元素 e，并返回索引。
注意，如果列表中有多个相同的搜索元素，则返回从左开始的第一个搜索的元素索引。
]]
set(KUNGFUS "一阳指;乾坤大挪移;六脉神剑;九阴白骨掌;独孤九剑;吸星大法;玄铁剑法")
set(FIND_KUNGFU "九阴白骨掌")
list(FIND KUNGFUS ${FIND_KUNGFU} findIndex)
message(STATUS "${FIND_KUNGFU}:${findIndex}")

set(FIND_KUNGFU "辟邪剑法")
list(FIND KUNGFUS ${FIND_KUNGFU} findIndex)
message(STATUS "${FIND_KUNGFU}:${findIndex}")

message(STATUS "============= 列表修改(Modification) ===============")

# 3.列表修改(Modification)
#[[
将元素追加到列表中。
    list(APPEND <list> [<element>...])

例如，list(APPEND A a b c)
]]
list(APPEND FLOWERS "玫瑰" "月季" "水仙")
message(STATUS "FLOWERS:${FLOWERS}")

#[[
根据正则表达式的模式串，从列表中包含或删除元素。REGEX 表示，匹配正则表达式。
    list(FILTER <list> {INCLUDE | EXCLUDE} REGEX <regex>)

例如，list(FILTER A EXCLUDE REGEX Hello_*) 根据正则表达式，排除列表 a Hello_b c Hello_d e Hello_f g e，中符合 Hello_* 的元素。
例如，list(FILTER A INCLUDE REGEX Hello_*) 根据正则表达式，筛选出列表 a Hello_b c Hello_d e Hello_f g e，中符合 Hello_* 的元素。
]]
list(APPEND LISTA a Hello_b c Hello_d e Hello_f g e)
message(STATUS "LISTA:${LISTA}")
list(FILTER LISTA INCLUDE REGEX Hello_*)
message(STATUS "LISTA:${LISTA}")

set(LISTA a Hello_b c Hello_d e Hello_f g e)
list(FILTER LISTA EXCLUDE REGEX Hello_*)
message(STATUS "LISTA:${LISTA}")

#[[
将元素插入到列表中的指定位置。
    list(INSERT <list> <index> [<element>...])

例如，list(INSERT A 3 x y z) 在列表索引为 3 的位置，插入元素 x;y;z
]]
set(CITYS "深圳;武汉;北京;上海;大连;天津")
list(INSERT CITYS 2 "广州" "南京" "济南")
message(STATUS "CITYS:${CITYS}")

#[[
利用弹出，删除列表的元素。
POP_BACK 从最后一个元素开始删除，POP_FRONT 从第一个元素开始删除。
如果给出变量名，将删除的元素赋值给变量。如果有多个变量，那么会删除多个变量。

例如，list(POP_BACK A) 从列表 a b c d e f g e 中，删除最后一个元素 e
例如，list(POP_FRONT A) 从列表 a b c d e f g e 中，删除第一个元素 a
例如，list(POP_BACK A A1 A2 A3) 从列表 a b c d e f g e 中，删除元素，A1 为 e，A2 为 g，A3 为 f
]]
list(POP_BACK CITYS)
message(STATUS "CITYS:${CITYS}")
list(POP_FRONT CITYS)
message(STATUS "CITYS:${CITYS}")
list(POP_BACK CITYS city1 city2 city3)
message(STATUS "CITYS:${CITYS}")
message(STATUS "city1:${city1},city2:${city2},city3:${city3}")

#[[
将元素插入到列表中的第 0 个位置。
    list(PREPEND <list> [<element>...])

例如，list(PREPEND A x y z) 在列表开头，插入元素 x;y;z
]]
list(PREPEND CITYS "贵阳" "成都" "昆明")
message(STATUS "CITYS:${CITYS}")

#[[
从列表中删除给定元素值的元素。
    list(REMOVE_ITEM <list> <value>...)

例如，list(REMOVE_ITEM A b d f) 从列表 a b c d e f g e 中，删除元素 b d f
]]
list(REMOVE_ITEM CITYS "贵阳" "广州")
message(STATUS "CITYS:${CITYS}")

#[[
从列表中删除给定索引的元素。
    list(REMOVE_AT <list> <index>...)

例如，list(REMOVE_AT A 2 4 7) 从列表 a b c d e f g e 中，结果为 a;b;d;f;g
]]
set(KUNGFUS "一阳指;乾坤大挪移;六脉神剑;九阴白骨掌;独孤九剑;吸星大法;玄铁剑法")
message(STATUS "KUNGFUS:${KUNGFUS}")
list(REMOVE_AT KUNGFUS 2 4 5)
message(STATUS "KUNGFUS:${KUNGFUS}")

#[[
删除列表中的重复项。保留相对顺序。
    list(REMOVE_DUPLICATES <list>)

例如，list(REMOVE_DUPLICATES A) 从列表 a b c b a d c e f a g e 中删除重复项，结果为 a;b;c;d;e;f;g
]]
set(KUNGFUS "一阳指;乾坤大挪移;六脉神剑;一阳指;九阴白骨掌;独孤九剑;吸星大法;六脉神剑;玄铁剑法;独孤九剑;")
message(STATUS "KUNGFUS:${KUNGFUS}")
list(REMOVE_DUPLICATES KUNGFUS)
message(STATUS "KUNGFUS:${KUNGFUS}")

# 4. 转换(Transforms)
#[[
转换列表中的元素，<ACTION> 表示转换规则，<SELECTOR> 表示选定的元素，OUTPUT_VARIABLE 表示存储的结果，
如果指定 OUTPUT_VARIABLE 那么不会修改原列表，修改后的列表存储在 <output variable> 变量中。
    list(TRANSFORM <list> <ACTION> [<SELECTOR>] [OUTPUT_VARIABLE <output variable>])

例如，list(TRANSFORM A APPEND "x" FOR 2 5 1 OUTPUT_VARIABLE A_out)，结果存储在 A_out 变量中。
]]
set(KUNGFUS "一阳指;乾坤大挪移;六脉神剑;九阴白骨掌;独孤九剑;吸星大法;玄铁剑法")
list(TRANSFORM KUNGFUS APPEND "abc" FOR 2 5 1 OUTPUT_VARIABLE transformKunghu)
message(STATUS "KUNGFUS:${KUNGFUS}")
message(STATUS "transformKunghu:${transformKunghu}")
list(TRANSFORM KUNGFUS PREPEND "def" FOR 2 6 2 OUTPUT_VARIABLE transformKunghu)
message(STATUS "KUNGFUS:${KUNGFUS}")
message(STATUS "transformKunghu:${transformKunghu}")

#[[
注意，TRANSFORM 子命令不会更改列表中的元素数。如果指定了 <SELECTOR>，则只会更改某些元素，其他元素将保持与转换前相同。
<ACTION>: 指定应用于列表元素的操作。这些操作与 string() 命令的子命令具有完全相同的语义，<ACTION> 必须是以下之一:
APPEND, PREPEND: 将指定值连接到列表的每个元素。APPEND 表示后缀，PREPEND 表示前缀。

list(TRANSFORM <list> <APPEND|PREPEND> <value> ...)
    例如，list(TRANSFORM A APPEND "x") 列表 a b c d e 每个元素都添加后缀 x，结果为 ax;bx;cx;dx;ex
    例如，list(TRANSFORM A PREPEND "x") 列表 a b c d e 每个元素都添加前缀 x，结果为 xa;xb;xc;xd;xe
]]
set(CITYS "武汉;北京;深圳;广州;南京;昆明;成都;东莞;惠州;潮州")
message(STATUS "CITYS:${CITYS}")
list(TRANSFORM CITYS APPEND "123")
message(STATUS "CITYS:${CITYS}")
list(TRANSFORM CITYS PREPEND "adc")
message(STATUS "CITYS:${CITYS}")

#[[
TOUPPER, TOLOWER: 将列表中每个元素转换为 大写，小写 字符。
    list(TRANSFORM <list> <TOLOWER|TOUPPER> ...)

例如，list(TRANSFORM A TOLOWER) 列表 a B c D e 转换为小写，结果为 a;b;c;d;e
例如，list(TRANSFORM A TOUPPER) 列表 a B c D e 转换为大写，结果为 A;B;C;D;E
]]
list(TRANSFORM CITYS TOUPPER)
message(STATUS "CITYS:${CITYS}")
list(TRANSFORM CITYS TOLOWER)
message(STATUS "CITYS:${CITYS}")

#[[
STRIP: 删除列表中每个元素中的前导和尾随空格。
    list(TRANSFORM <list> STRIP ...)

例如，list(TRANSFORM A STRIP)
]]
set(CITYS "武汉 ;   北京;深圳;  广州        ;南京;昆明; 成都;   东莞;惠州;  潮州")
message(STATUS "CITYS:${CITYS}")
list(TRANSFORM CITYS STRIP)
message(STATUS "CITYS:${CITYS}")

#[[
GENEX_STRIP: Strip any generator expressions from each element of the list.
https://cmake.org/cmake/help/v3.19/manual/cmake-generator-expressions.7.html

list(TRANSFORM <list> GENEX_STRIP ...)
]]
# set(CITYS "武汉;北京;深圳;广州;南京;昆明;成都;东莞;惠州;潮州")
# message(STATUS "CITYS:${CITYS}")
# list(TRANSFORM CITYS GENEX_STRIP 2)
# message(STATUS "CITYS:${CITYS}")

#[[
REPLACE: 用正则表达式替换列表的每个元素。(与 string 命令 的 REGEX REPLACE 语义相同)
    list(TRANSFORM <list> REPLACE <regular_expression> <replace_expression> ...)

例如，list(TRANSFORM A REPLACE Hello_* Out_) 将列表 a Hello_b c Hello_d e Hello_f g e，
中符合 Hello_* 的元素替换为 Out_，结果为 a;Out_b;c;Out_d;e;Out_f;g;e。
]]
set(LISTA a Hello_b c Hello_d e Hello_f g e)
message(STATUS "LISTA:${LISTA}")
list(TRANSFORM LISTA REPLACE Hello_* 223344)
message(STATUS "LISTA:${LISTA}")

#[[
<SELECTOR>: 选择将转换列表的哪些元素。一次只能指定一种类型的选择器。当给出时，<SELECTOR> 必须是以下之一:
AT: 指定列表的索引的元素
    list(TRANSFORM <list> <ACTION> AT <index> [<index> ...] ...)
例如，list(TRANSFORM A APPEND "x" AT 2 4) 列表 a b c d e f g e 转换为 a;b;cx;d;ex;f;g;e

FOR: 指定列表的索引范围的元素
    list(TRANSFORM <list> <ACTION> FOR <start> <stop> [<step>] ...)

例如，list(TRANSFORM A APPEND "x" FOR 2 5 1) 列表 a b c d e f g e 转换为 a;b;cx;dx;ex;fx;g;e

REGEX: 指定正则表达式。仅匹配正则表达式的元素菜被转换。
    list(TRANSFORM <list> <ACTION> REGEX <regular_expression> ...)

例如，list(TRANSFORM A APPEND "x" REGEX "Hello_*") 列表 a Hello_b c Hello_d e Hello_f g e 转换为 a;Hello_bx;c;Hello_dx;e;Hello_fx;g;e
]]
set(CITYS "武汉;北京;深圳;广州;南京;昆明;成都;东莞;惠州;潮州;台北;高雄;厦门;南昌")
message(STATUS "CITYS:${CITYS}")
list(TRANSFORM CITYS APPEND "mmm" AT 2 4)
message(STATUS "CITYS:${CITYS}")

list(TRANSFORM CITYS PREPEND "hhhh" FOR 2 8 2)
message(STATUS "CITYS:${CITYS}")

set(LISTA a Hello_b c Hello_d e Hello_f g e)
message(STATUS "LISTA:${LISTA}")
list(TRANSFORM LISTA APPEND "x" REGEX "Hello_*")
message(STATUS "LISTA:${LISTA}")

message(STATUS "============ 列表排序(Ordering) ==============")

# 4. 列表排序(Ordering)
#[[
逆序本列表。
    list(REVERSE <list>)
]]
set(CITYS "武汉;北京;深圳;广州;南京;昆明;成都;东莞;惠州;潮州")
message(STATUS "CITYS:${CITYS}")
list(REVERSE CITYS)
message(STATUS "CITYS:${CITYS}")

#[[
排序列表。
    list(SORT <list> [COMPARE <compare>] [CASE <case>] [ORDER <order>])

    COMPARE 选择排序方法，<compare> 选择以下之一:
        STRING: 默认，按字母顺序对字符串进行排序。
        FILE_BASENAME: 按文件路径的基本名称进行排序。
        NATURAL: 按数值大小进行排序。
    CASE 选择排序时是否区分大小写。<case> 选择以下之一:
        SENSITIVE: 默认，对大小写敏感，区分大小写
        INSENSITIVE: 对大小写不敏感，不区分大小写
    ORDER 用于控制排序。<orde> 选择以下之一:
        ASCENDING: 默认，升序排序。
        DESCENDING: 降序排序。
]]
set(CITYS "A武汉;北b京;c深圳;广d州;南D京;昆e明;成都f;东g莞;H惠州;a潮州")
message(STATUS "CITYS:${CITYS}")
list(SORT CITYS)
message(STATUS "CITYS:${CITYS}")
list(SORT CITYS COMPARE FILE_BASENAME CASE INSENSITIVE ORDER DESCENDING)
message(STATUS "CITYS:${CITYS}")

list(SORT CITYS COMPARE FILE_BASENAME CASE INSENSITIVE ORDER ASCENDING)
message(STATUS "CITYS:${CITYS}")
