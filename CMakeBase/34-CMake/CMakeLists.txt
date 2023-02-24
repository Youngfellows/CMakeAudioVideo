# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "=========== CMake 选项开关 ==============")

#[[
在执行 CMakeLists.txt 脚本时，我们如何根据不同的选项，执行不同的命令。
第一个想法是，通过 条件语句 结合 变量 来实现，但是有一个问题，每次更改选项的时候，你需要更改脚本文件。

那么如何实现，不更改脚本文件，来改变选项?
    通过使用 cmake 工具，添加 -D 选项，通过设置变量，来改变选项。
    通过使用 option 命令，设置选项的默认值，option 命令有个特殊的功能，如果变量值已经设置为普通变量或缓存变量，该命令不执行任何操作。
]]

#[[
-D 选项，语法如下：
    -D <var>[:<type>]=<value>
可以忽略 <type> 类型，-D 选项中，-D 与 <var> 变量之间，可以有空格，但是 <var> 变量之后必须有 = 等号。

以选项变量 TEST_DEBUG 为例:
    # 下面形式是相同的
    cmake -DTEST_DEBUG=ON ..
    cmake -D TEST_DEBUG=ON ..
    # 如果我们要使用选项，一般赋值为 ON。其实选项的值只要是除 OFF 之外任意的值，都算使用了该选项，一般我们不使用这种形式
    cmake -DTEST_DEBUG=ON ..
    cmake -DTEST_DEBUG=123 ..
    # 如果我们忽略使用选项，一般赋值为 OFF。其实赋值为空 或者 不出添加 -D 选项，都不会使用
    cmake -DTEST_DEBUG=OFF ..
    cmake -DTEST_DEBUG= ..
    cmake ..
]]

#[[
option 命令语法如下：
    option(<variable> "<help_text>" [value])
但是一般在使用选项变量时，我们会在脚本中定义该选项，给定说明的文本 和 默认值。在阅读 CMakeLists.txt 脚本时，我们可以很好的知道有哪些可选功能。有一点不好的是，选项的说明文本，并不会打印出来。

**例如：创建选项 `TEST_DEBUG`，如果选项被使用输出消息和预处理器定义：**
cmake_minimum_required(VERSION 3.0.0)
project(file_system)
option(TEST_DEBUG "option for debug" ON)
message("TEST_DEBUG Value: ${TEST_DEBUG}")
if(TEST_DEBUG)
	message("Select Option TEST_DEBUG")
	add_definitions(-DTEST_DEBUG")
endif()

你可以 option 命令，设置选项值 [value] 为 ON 或 OFF，如果默认是使用选项变量，设置为 ON 值。
如果我们想使用 TEST_DEBUG 功能，因为默认该功能是使用，则执行 cmake ..。如果不想使用该功能，则执行 cmake -DTEST_DEBUG=OFF ..。

test.c 源码使用 TEST_DEBUG 宏，结合 预处理器定义 和 C/C++ 条件编译
#ifdef TEST_DEBUG
...
#endif
]]
option(TEST_DEBUG "option for debug" ON)
option(TEST_RELEASE "option for release" OFF)

if(TEST_DEBUG)
    message(STATUS "TRUE,TEST_DEBUG:${TEST_DEBUG}")
    add_definitions(-DTEST_DEBUG)
else()
    message(STATUS "FALSE,TEST_DEBUG:${TEST_DEBUG}")
endif()

if(TEST_RELEASE)
    message(STATUS "TRUE,TEST_RELEASE:${TEST_RELEASE}")
    add_definitions(-DTEST_RELEASE)
else()
    message(STATUS "FALSE,TEST_RELEASE:${TEST_RELEASE}")
endif()

# 查找当前目录下的所有源文件，并将名称保存到 SRC_LIST 变量
# set(SRC_LIST main.cpp MathFunctions.cpp)
aux_source_directory(. SRC_LIST)
message(STATUS "SRC_LIST: " ${SRC_LIST})

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.in
    ${PROJECT_SOURCE_DIR}/config.h
)

# 是否使用自己的 MathFunctions 库
# 这里设置的变量 USE_MY_MATH、中间的提示文字、默认值，在 ccmake 命令中会展示
option(USE_MY_MATH "Use provided math implementation" ON)

# 是否加入 MathFunctions 库
if(USE_MY_MATH)
    # 添加头文件路径
    include_directories(${PROJECT_SOURCE_DIR}/math)

    # 添加 math 子目录 (math 目录里必须有 CMakeLists.txt)，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处
    add_subdirectory(math)
    set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MY_MATH)

# 指示变量 SRC_LIST 中的源文件需要编译成一个名称为 Sample 的可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST})

# 添加链接库
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
