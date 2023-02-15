# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# cmake打印
message(VERSION: ${VERSION})

# 项目名称为 Sample
project(Sample)
message("Project: " ${PROJECT_NAME})

# 查找当前目录下的所有源文件，并将名称保存到 SRC_LIST 变量
# set(SRC_LIST main.cpp MathFunctions.cpp)
aux_source_directory(. SRC_LIST)
message("SRC_LIST: " ${SRC_LIST})

# 查找 math 目录下的所有源文件，并将名称保存到 MATH_SRC_LIST 变量
# aux_source_directory(${PROJECT_SOURCE_DIR}/math MATH_SRC_LIST)
# message("MATH_SRC_LIST: " ${MATH_SRC_LIST})

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
