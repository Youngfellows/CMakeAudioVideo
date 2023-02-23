# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "============== CMake 文件操作 =================")
message(STATUS "============== 写文件(Writing) ================")

#[[
1.1 写入文件内容
    file(WRITE <filename> <content>...)
    file(APPEND <filename> <content>...)

将内容 <content> 写入 <filename> 文件中。 如果文件不存在，它将被创建。如果文件已经存在，WRITE 模式将覆盖它，APPEND 模式将附加到末尾。

例，file(WRITE "data.txt" "Hello World")。

若 <filename> 文件名中的路径不存在，那么会创建这些不存在的目录。
如果文件是构建输入，则使用 configure_file() 命令仅在其内容更改时更新文件。
]]
set(fileName "file/kungfu1.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)
set(context "六脉神剑,独孤九剑,太极剑,玄铁剑法")
file(WRITE ${fileName} ${context})

set(fileName "file/kungfu2.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)
set(context "六脉神剑;独孤九剑;太极剑;玄铁剑法")
file(WRITE ${fileName} ${context})

set(fileName "file/kungfu1.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)
set(context "七弦无形剑,夺命连环三仙剑,雨打飞花剑")
file(APPEND ${fileName} ${context})

message(STATUS "============== 创建空文件 ================")

#[[
1.2 创建空文件
    file(TOUCH [<files>...])
    file(TOUCH_NOCREATE [<files>...])

创建一个空文件，若文件已存在，不会修改现有文件的内容，仅更新访问和修改时间。

使用 TOUCH_NOCREATE 并不创建文件，仅用来更新访问和修改时间。
]]
set(fileName "file/kungfu1.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)
file(TOUCH ${fileName})

set(FORMAT "%Y-%m-%d %H:%M:%S %j %B %U %w %A")
file(TIMESTAMP ${fileName} updateTime ${FORMAT})
message(STATUS "updateTime:${updateTime}")

set(fileName "file/kungfu3.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)
file(TOUCH ${fileName})

set(fileName "file/kungfu4.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)
file(TOUCH_NOCREATE ${fileName})

set(fileName "file/kungfu1.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)
file(TOUCH_NOCREATE ${fileName})

set(FORMAT "%Y-%m-%d %H:%M:%S %j %B %U %w %A")
file(TIMESTAMP ${fileName} updateTime ${FORMAT})
message(STATUS "updateTime:${updateTime}")

message(STATUS "============== 在构建目标时，生成输出文件 ================")

#[[
1.3 在构建目标时，生成输出文件
file(GENERATE OUTPUT output-file
     <INPUT input-file|CONTENT content>
     [CONDITION expression] [TARGET target])

在构建目标时，生成输出文件。

为当前 CMake 生成器支持的每个构建配置生成一个输出文件。从输入内容评估生成器表达式以生成输出内容。选项是：
    CONDITION <condition>: 仅当条件为真时才为特定配置生成输出文件。计算生成器表达式后，条件必须为 0 或 1。
    CONTENT <content>: 使用明确给出的内容作为输入。
    INPUT <input-file>: 使用给定文件中的内容作为输入。相对路径根据 CMAKE_CURRENT_SOURCE_DIR 的值进行处理。请参阅政策 CMP0070。
    OUTPUT <output-file>: 指定要生成的输出文件名。使用诸如 $<CONFIG> 之类的生成器表达式来指定特定于配置的输出文件名。只有生成的内容相同，多个配置才能生成相同的输出文件。否则， <output-file> 必须评估为每个配置的唯一名称。相对路径（在评估生成器表达式之后）根据 CMAKE_CURRENT_BINARY_DIR 的值进行处理。请参阅政策 CMP0070。
    TARGET <target>: 指定在评估需要评估目标的生成器表达式时使用哪个目标（例如 $<COMPILE_FEATURES:...>, $<TARGET_PROPERTY:prop>）。
必须只给出一个 CONTENT 或 INPUT 选项。 一个特定的 OUTPUT 文件最多可以通过调用一次 file(GENERATE) 来命名。 生成的文件会被修改，并且只有当它们的内容发生更改时，它们的时间戳才会在后续 cmake 运行时更新。

还要注意 file(GENERATE) 直到生成阶段才创建输出文件。 当 file(GENERATE) 命令返回时，输出文件尚未写入，只有在处理完项目的所有 CMakeLists.txt 文件后才会写入。

例，在执行 CMakeLists.txt 时，构建 hello 目录时，将内容 “Hello World” 输出到文件 “out.txt”
    add_executable(hello main.cpp)
    file(GENERATE OUTPUT "out.txt" CONTENT "Hello World" TARGET hello)
]]

# 查找当前目录下的所有源文件，并将名称保存到 SRC_LIST 变量
aux_source_directory(. SRC_LIST)

# 添加 math 子目录 (math 目录里必须有 CMakeLists.txt)，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处
add_subdirectory(math)

# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/math)

# 指示变量 SRC_LIST 中的源文件需要编译成一个名称为 Sample 的可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST} ${MATH_SRC_LIST})

# 添加链接库
target_link_libraries(${PROJECT_NAME} MathFunctions)

# 在构建目标时，生成输出文件
set(content "这是输出的版本信息")
set(fileName "file/appinfo.txt")
get_filename_component(fileName ${fileName} ABSOLUTE)
file(GENERATE OUTPUT ${fileName} CONTENT ${content} TARGET ${PROJECT_NAME})

#[[
1.4 输出配置文件
file(CONFIGURE OUTPUT output-file
     CONTENT content
     [ESCAPE_QUOTES] [@ONLY]
     [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])

与 configure_file() 命令替换规则相同，CONTENT 文件内容 类似于 xxx.in 文件，替换其中包含的引用为 @VAR@ 或 ${VAR} 的变量值，输出文件名为 OUTPUT

参数说明:
    ESCAPE_QUOTES: 使用反斜杠 C 样式 转义任何替换的引号。
    @ONLY: 将变量替换限制为 @VAR@ 形式的引用。这对于配置使用 ${VAR} 语法的脚本很有用。
    NEWLINE_STYLE <style>: 指定输出文件的换行样式。 指定 UNIX/LF 为 \n 换行符，或 指定 DOS/WIN32/CRLF 为 \r\n 换行符。

]]