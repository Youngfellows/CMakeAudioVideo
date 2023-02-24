# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.25.1)

message(STATUS "============== CMake 项目、目标、子目录 ================")
message(STATUS "============== CMake 路径和版本 =============")

# 1. CMake 工具：路径和版本
#[[
CMake 路径
    CMAKE_SOURCE_DIR 为 顶级 CMakeLists.txt 文件所在路径，CMAKE_BINARY_DIR 为 构建输出所在路径，
    这两个变量与子目录中的 CMakeLists.txt 文件无关。
]]
message(STATUS "CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")

#[[
CMake 版本
    CMAKE_VERSION 为 CMake 的版本，由 MAJOR.MINOR.PATCH.TWEAK 组成。CMAKE_MAJOR_VERSION 为 主要版本, CMAKE_MINOR_VERSION 为 次要版本,
    CMAKE_PATCH_VERSION 为 补丁版本, CMAKE_TWEAK_VERSION 为微调版本。
]]
message(STATUS "CMAKE_MAJOR_VERSION:${CMAKE_MAJOR_VERSION}")
message(STATUS "CMAKE_MAJOR_VERSION:${CMAKE_MINOR_VERSION}")
message(STATUS "CMAKE_PATCH_VERSION:${CMAKE_PATCH_VERSION}")
message(STATUS "CMAKE_TWEAK_VERSION:${CMAKE_TWEAK_VERSION}")

#[[
当前执行 CMakeLists.txt 文件
CMAKE_* 与 CMAKE_CURRENT_* 区别在于，CMAKE_* 表示顶级 CMakeLists.txt 文件，CMAKE_CRRUENT_* 表示当前 CMakeLists.txt 文件。

CMAKE_CURRENT_SOURCE_DIR 为当前 CMakeLists.txt 文件所在目录。
CMAKE_CURRENT_BINARY_DIR 为当前 CMakeLists.txt 构建输出所在的目录。
CMAKE_CURRENT_LIST_DIR 为当前执行 CMakeLists.txt 文件所在目录，
CMAKE_CURRENT_LIST_FILE 为当前执行 CMakeLists.txt 文件所在路径，CMAKE_CURRENT_LIST_LINE 为 当前执行 CMakeLists.txt 文件所在行号。
]]
message(STATUS "CMAKE_CURRENT_SOURCE_DIR:${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_MAJOR_VERSION:${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR:${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_FILE:${CMAKE_CURRENT_LIST_FILE}")

message(STATUS "===============  CMake 项目：名称、版本、语言、路径 ==================")

# 2. CMake 项目：名称、版本、语言、路径
#[[
project(<PROJECT-NAME> [<language-name>...])
project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]] # ]]
#[[     [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])

我们使用 <PROJECT-NAME> 设置项目名称。
我们通过 DESCRIPTION 设置项目描述。
我们通过 VERSION 设置项目版本。
我们通过 HOMEPAGE_URL 设置项目网站。
我们通过 LANGUAGES 设置项目语言。
]]

#[[
CMake 项目名称、描述、网站
    <PROJECT-NAME>
    DESCRIPTION <project-description-string>
    HOMEPAGE_URL <url-string>

CMAKE_PROJECT_XXX	        PROJECT_XXX	                <PROJECT-NAME>_XXX	                        说明
顶级 CMakeLists.txt         调用 project() 命令	         当前 CMakeLists.txt 调用 project() 命令	  指定项目	
CMAKE_PROJECT_NAME	        PROJECT_NAME		        项目名
CMAKE_PROJECT_DESCRIPTION	PROJECT_DESCRIPTION	        <PROJECT-NAME>_DESCRIPTION	                项目描述
CMAKE_PROJECT_HOMEPAGE_URL	PROJECT_HOMEPAGE_URL	    <PROJECT-NAME>_HOMEPAGE_URL	                项目网站
]]

#[[
CMake 项目路径
    XXX_SOURCE_DIR: 为 CMakeLists.txt 所在路径，例如 CMake/src。
    XXX_BINARY_DIR: 为 CMakeLists.txt 构建输出所在路径，例如 CMake/src/build。

PROJECT_XXX	                                    <PROJECT-NAME>_XXX
当前 CMakeLists.txt 调用 project() 命令	         指定项目
PROJECT_SOURCE_DIR	                            <PROJECT-NAME>_SOURCE_DIR
PROJECT_BINARY_DIR	                            <PROJECT-NAME>_BINARY_DIR
]]

#[[
CMake 项目版本
    VERSION <version>
除非策略 CMP0048 设置为 NEW，否者不得使用。
版本 <version> 的组成，即 <major>[.<minor>[.<patch>[.<tweak>]] # ]。

#[[
CMAKE_PROJECT_XXX	            PROJECT_XXX	                                                <PROJECT-NAME>_XXX	            说明
顶级 CMakeLists.txt 调用         project() 命令	当前 CMakeLists.txt 调用 project() 命令	      指定项目	
CMAKE_PROJECT_VERSION	        PROJECT_VERSION	                                            <PROJECT-NAME>_VERSION	        版本
CMAKE_PROJECT_VERSION_MAJOR	    PROJECT_VERSION_MAJOR                                       <PROJECT-NAME>_VERSION_MAJOR	主要版本
CMAKE_PROJECT_VERSION_MINOR	    PROJECT_VERSION_MINOR                                       <PROJECT-NAME>_VERSION_MINOR	次要版本
CMAKE_PROJECT_VERSION_PATCH	    PROJECT_VERSION_PATCH                                       <PROJECT-NAME>_VERSION_PATCH	补丁版本
CMAKE_PROJECT_VERSION_TWEAK	    PROJECT_VERSION_TWEAK                                       <PROJECT-NAME>_VERSION_TWEAK	微调版本
]]

#[[
CMake 项目语言
    LANGUAGES <language-name>...

选择构建项目所需的编程语言，会根据设置的编程语言查找编译器。
<language-name> 支持的语言包括 C, CXX(即 C++), CUDA, OBJC(即 Objective-C), OBJCXX, Fortran, ISPC, and ASM。
<language-name> 默认情况下，语言为 C 和 CXX。
<language-name> 指定语言为 NONE，跳过启用任何语言。
]]
project(hello VERSION 1.04.02.3 DESCRIPTION "主项目" HOMEPAGE_URL https://www.example.com LANGUAGES CXX)

message(STATUS "CMAKE_PROJECT_DESCRIPTION ${CMAKE_PROJECT_DESCRIPTION}")
message(STATUS "CMAKE_PROJECT_HOMEPAGE_URL ${CMAKE_PROJECT_HOMEPAGE_URL}")
message(STATUS "CMAKE_PROJECT_NAME ${CMAKE_PROJECT_NAME}")

message(STATUS "CMAKE_PROJECT_VERSION ${CMAKE_PROJECT_VERSION}")
message(STATUS "CMAKE_PROJECT_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR}")
message(STATUS "CMAKE_PROJECT_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR}")
message(STATUS "CMAKE_PROJECT_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH}")
message(STATUS "CMAKE_PROJECT_VERSION_TWEAK ${CMAKE_PROJECT_VERSION_TWEAK}")

message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")

message(STATUS "PROJECT_NAME ${PROJECT_NAME}")
message(STATUS "PROJECT_DESCRIPTION ${PROJECT_DESCRIPTION}")
message(STATUS "PROJECT_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL}")

message(STATUS "PROJECT_VERSION ${PROJECT_VERSION}")
message(STATUS "PROJECT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR}")
message(STATUS "PROJECT_VERSION_MINOR ${PROJECT_VERSION_MINOR}")
message(STATUS "PROJECT_VERSION_PATCH ${PROJECT_VERSION_PATCH}")
message(STATUS "PROJECT_VERSION_TWEAK ${PROJECT_VERSION_TWEAK}")

#[[
3. CMake 子目录和目标
我们会常用 add_subdirectory() 命令，将子目录的目标添加到构建中。
不管是在哪个子目录的 CMakeLists.txt 文件定义的目标，，都会被添加到顶级 CMakeLists.txt 的项目中。
实际上，应该是目标不仅仅被添加到当前项目中，也会被添加到上一级项目，或上上一级项目中。
我们使用 add_subdirectory(EXCLUDE_FROM_ALL) 命令，提供 EXCLUDE_FROM_ALL 参数，则子目录构建的目标，并不会添加到父目录的项目中。这种方式，常用于构建示例这种单独的项目，示例项目有用但不是必须的项目，通常子目录 CMakeLists.txt 应该包含自己的 project 命令，以边在子目录中生成完整的构建系统。

include 命令 与 add_subdirectory 命令的区别?
我们用 include() 命令 也可以加载 子目录中的 CMakeLists.txt 文件，例如 include(sub/CMakeLists.txt)。虽然 include() 命令与 add_subdirectory() 命令，都会加载 CMakeLists.txt 文件，但是 include() 命令是将子目录中 CMakeLists.txt 文件内容导入到父目录的源文件中，而 add_subdirectory() 命令是将子目录中 CMakeLists.txt 添加到构建中。
所以，有一个比较明显的区别，都执行 project 命令，如果使用 include() 那么项目会被覆盖，如果使用 add_subdirectory() 那么会创建子项目。

add_subdirectory 命令，子目录的变量和执行控制权
我们想在父目录中的 CMakeLists.txt 文件中，使用子目录定义的变量，该怎么办?
如果仅仅使用 add_subdirectory(sub_dir) 没有作用，你需要在子目录 CMakeLists.txt 文件使用 set(PARENT_SCOPE) 来定义变量，就算你使用 add_subdirectory(EXCLUDE_FROM_ALL) 添加子目录也没有影响。
如果直接使用 include(sub_dir/CMakeLists.txt)，在子目录 CMakeLists.txt 文件使用 set() 来定义变量，也行。因为时子目录 CMakeLists.txt 文件内容，不加载到 父目录的 CMakeLists.txt 文件中，并没有父目录和子目录的关系。
所以，通过 PARENT_SCOPE 选项，设置子目录中的变量，可以在父目录中使用。
我们也可以，在使用 add_subdirectory(sub_dir) 命令构建子目录的目标时，通过 return 命令，将控制权从子目录转移到父目录。
]]