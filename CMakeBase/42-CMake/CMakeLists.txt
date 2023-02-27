# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "============= Cmake命令之configure_file介绍 =============")

# 指定C++标准，示例为指定C++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

message(STATUS "PROJECT_BINARY_DIR:${PROJECT_BINARY_DIR}")

#[[
一、命令格式
configure_file(input output options)
  将一个文件(由input参数指定)拷贝到指定位置(由output参数指定)，并根据options修改其内容。

二、命令解析
  configure_file命令一般用于自定义编译选项或者自定义宏的场景。configure_file命令会根据options指定的规则，自动对input文件中cmakedefine关键字及其内容进行转换。
  具体来说，会做如下几个替换：
  1. 将input文件中的@var@或者${var}替换成cmake中指定的值。
  2. 将input文件中的#cmakedefine var关键字替换成#define var或者#undef var，取决于cmake是否定义了var。
]]

#[[
三、举例说明
  需要准备2个文件，config.h.in（input）、CMakeLists.txt，（output是自动生成的
]]
option(var1 "use var1 ..." ON) # 定义var1，也可以使用cmake -Dvar1=ON替代
set(var2 13) # 指定var2的值
set(var3 "var3string") # 指定var3的值
set(var4 "VARTEST4")
set(var5 "VARTEST5")
configure_file(config.h.in config.h)

#[[
四、更多细节
1.参数详解
input - 输入文件的路径，它是一个相对路径，以CMAKE_CURRENT_SOURCE_DIR为路径前缀。此外，。
output - 输出文件或目录，它也是一个相对路径，以CMAKE_CURRENT_BINARY_DIR为前缀。如果output的名称与已存在的目录名称相同，则会在该目录下生成一个与input文件名相同的文件。举个例子：如果input的文件名是inputfile，output是一个目录currentdir，那么生成的文件为currentdir/inputfile。

options - 参数选项
    COPYONLY：简单的把input文件拷贝到output，不做任何替换。注意，NEWLINE_STYLE。
    ESCAPE_QUOTES：忽略反斜杠（C语言风格）的转义。
    举个例子，不加ESCAPE_QUOTES的情况，也就是默认会对反斜杠进行转义：
        config.h.in文件：
        #define @var@

        CMakeLists.txt文件：
        set (var "\"VAR\"")
        configure_file (config.h.in config.h)

        生成的config.h文件：
        #define "VAR"
    加ESCAPE_QUOTES的情况，不对反斜杠进行转义：
        config.h.in文件：
        #define @var@

        CMakeLists.txt文件：
        set (var "\"VAR\"")
        configure_file (config.h.in config.h ESCAPE_QUOTES)

        生成的config.h文件：
        #define \"VAR\"

    @ONLY：只替换@var@，不替换${var}。${var}在脚本语言中有语义含义（替换会导致含义发生变化），因此在处理这类文件的时候，该选项很有用。
    NEWLINE_STYLE：指定output文件的换行风格，例如linux以\n作为换行，windows以\r\n作为换行。该参数后面要指明换行的规则，如UNIX|DOS|WIN32|LF|CRLF。


2.cmakedefine01命令
  #cmakedefine01 var
  如果var有定义，则实际生成的效果为：#define var 1；如果var未定义，生成的效果为：#define var 0。
    config.h.in文件：
    #cmakedefine01 var

    CMakeLists.txt文件：
    option(var "use var..." ON) # 实际也可以用cmake -Dvar=ON或者cmake -Dvar=OFF来定义或者不定义
    #set (var XXX) # 用set来定义var也可以，验证发现XXX为0的时候相当于var未定义，XXX为非0的时候效果相当于var有定义

    生成的config.h文件：
    #define var 1 # 当var有定义
    #define var 0 # 当var未定义

3.其他注意事项
对于#cmakedefine var @var@或#cmakedefine var ${var}，@@之间或${}内的变量名称要与cmakedefine后的变量名称一样，否则替换不成功。
configure_file要放在变量定义之后（验证发现OPTION定义的变量可以在configure_file之后）。
]]