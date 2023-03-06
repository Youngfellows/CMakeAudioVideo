# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)

message(STATUS "================= make命令之find_library介绍 ===================")

#[[
一、命令格式
  该命令用于查找库（动态库或者静态库），当构建依赖于第三方库/系统库，可以使用该命令来查找并使用库（Cmake中有另外一个命令find_package，
能获取库的更多信息，具体可以参考Cmake命令之find_package介绍）

简洁的格式
    find_library (<VAR> name [path1 path2 ...])
]]

# 通用的格式
# find_library ( <VAR> name | NAMES name1 [name2 ...] [NAMES_PER_DIR] [HINTS [path | ENV var]... ]
# [PATHS [path | ENV var]... ] [PATH_SUFFIXES suffix1 [suffix2 ...]]
# [DOC "cache documentation string"] [NO_CACHE] [REQUIRED] [NO_DEFAULT_PATH]
# [NO_PACKAGE_ROOT_PATH] [NO_CMAKE_PATH] [NO_CMAKE_ENVIRONMENT_PATH] [NO_SYSTEM_ENVIRONMENT_PATH]
# [NO_CMAKE_SYSTEM_PATH] [CMAKE_FIND_ROOT_PATH_BOTH | ONLY_CMAKE_FIND_ROOT_PATH | NO_CMAKE_FIND_ROOT_PATH] )

#[[
几个基本参数的解析：
    <var>用于存储该命令执行的结果，也就是找到的库的全路径（包含库名）:
     1. <var>可以是普通变量（需要指定NO_CACHE选项），也可以是缓存条目（意味着会存放在CMakeCache.txt中，不删除该文件或者用set重新设置该变量，其存储的值不会再刷新）；
     2. 当库能被找到，<var>会被存放正常的库路径，当库未被找到，<var>中存放的值为"<var>-NOTFOUND"。只要<var>中的值不是"<var>-NOTFOUND"，那么即使多次调用find_library，<var>也不会再刷新;
    name用于指定待查找的库名称，库名称可以使用全称，例如libmymath.a（优先会当成全名搜索）；也可以不带前缀（例如前缀lib）和后缀（例如Linux中的.so、.a，Mac中的.dylib等），直接使用mymath；
    path用于指定库的查找的路径；
]]

#[[
二、库的搜索路径
  库的搜索路径分为两大类：默认搜索路径和附加搜索路径。
  默认搜索路径包含cmake定义的以CMAKE开头的一些变量（例如CMAKE_LIBRARY_ARCHITECTURE、CMAKE_PREFIX_PATH、CMAKE_LIBRARY_PATH、
  CMAKE_FRAMEWORK_PATH）、标准的系统环境变量（例如系统环境变量LIB和PATH定义的路径）、系统的默认的库安装路径（例如/usr、/usr/lib等）；
  附加搜索路径即find_library命令中通过HINTS或PATHS指定的路径；
  
1.当指定NO_DEFAULT_PATH选项时，默认搜索路径不会生效，只会用到附加搜索路径。修改顶层的CMakeLists.txt，在find_library中指定选项NO_DEFAULT_PATH，
  可以看到即使指定了CMAKE_XXX_PATH的值，也会被忽略，下面的代码执行cmake .（建议在执行之前rm CMakeCache.txt删除）会提示错误，而去除NO_DEFAULT_PATH选项后能正常找到库的路径。

2.当未指定NO_DEFAULT_PATH选项时，搜索路径按照优先级从高到低依次是：
 1） 通过命令行使用-D指定的CMAKE_XXX_PATH变量，也就是形如cmake . -DCMAKE_XXX_PATH=paths的格式。其中CMAKE_XXX_PATH包含如下几个：
  CMAKE_PREFIX_PATH:指定搜索目录的前缀，如果前缀有多个，需要以分号分割的列表方式提供，该变量默认为空，一旦该变量非空，那么会搜索该变量提供的目录，以及${CMAKE_PREFIX_PATH}/lib;例如CMAKE_PREFIX_PATH=A;B，那么find_library会从A、B以及A/lib、B/lib中搜索库是否存在；
  CMAKE_LIBRARY_ARCHITECTURE:如果该变量被设置，那么会搜索目录${CMAKE_PREFIX_PATH}/lib/${CMAKE_LIBRARY_ARCHITECTURE};
  CMAKE_LIBRARY_PATH:指定find_library的库查找目录，默认值为空，多个值时需要以分号分割列表指定；
  CMAKE_FRAMEWORK_PATH*:指定macOS的框架作为搜索路径。
]]
#[[
// 顶层CMakeLists.txt
  make_minimum_required (VERSION 3.21)
  project (fl)
  find_library (libvar mymath)
  if (${libvar} STREQUAL "libvar-NOTFOUND")
      message (FATAL_ERROR "required mymath library but not found!")
  else()
      message (STATUS "mymath library found in ${libvar}")
  endif()

> cmake . -DCMAKE_LIBRARY_PATH=./mylib
-- mymath library found in /XXX/mylib/libmymath.a
]]

#[[
  2） 通过在环境变量中指定CMAKE_XXX_PATH变量，例如在window的环境变量中增加CMAKE_XXX_PATH(以;分割多个路径)、Linux中shell配置文件中添加（以:分割多个路径）。用法和cmake -D指定类似，例如在我的机器中（macOS）,在.zshrc（我的命令行配置文件）中增加export CMAKE_LIBRARY_PATH="/XXX/……/mylib"，即可在将该目录加入到搜索路径中。
  3） HINTS选项指定的路径。
  4） 系统环境变量指定的目录，默认是LIB和PATH指定的路径。例如在PATH中指定库搜索目录；
]]

#[[
// 顶层CMakeLists.txt
  make_minimum_required (VERSION 3.21)
  project (fl)
  find_library (libvar mymath)
  if (${libvar} STREQUAL "libvar-NOTFOUND")
      message (FATAL_ERROR "required mymath library but not found!")
  else()
      message (STATUS "mymath library found in ${libvar}")
  endif()

  // 命令行中执行
  export PATH=$PATH:./mylib
  cmake .

  // 执行结果
  -- mymath library found in /XXX/mylib/libmymath.a
]]

#[[
也可以通过find_library中的PATHS ENV 环境变量名称（cmake中使用环境变量名称的格式为$ENV{环境变量名称}）来指定从哪个环境变量名称中获取路径，
例如定义一个TESTPATH环境变量并赋值为./mylib，并在find_library命令中指定使用该环境变量：

  // 顶层CMakeLists.txt
  make_minimum_required (VERSION 3.21)
  project (fl)
  find_library (libvar mymath PATHS ENV TESTPATH)
  if (${libvar} STREQUAL "libvar-NOTFOUND")
      message (FATAL_ERROR "required mymath library but not found!")
  else()
      message (STATUS "mymath library found in ${libvar}")
  endif()

  // 命令行中执行
  export TESTPATH=./mylib
  cmake .

  // 执行结果
  -- mymath library found in /XXX/mylib/libmymath.a
]]

#[[
  5）跟当前系统相关的平台文件路径，一般来说指的是当前系统安装软件的标准目录，不同的操作系统对应的路径有所不同。camke中find_library与此相关的也有如下几个，CMAKE_SYSTEM_XXX_PATH变量，这些：
    CMAKE_SYSTEM_PREFIX_PATH:指定安装目录的前缀，例如在Windows下的/XXXX/Program Files，Linux下的/usr或/usr/local等。find_library命令会搜索这些前缀目录，也会以这些目录加上lib进行搜索，例如搜索/usr/local/lib；
    CMAKE_SYSTEM_LIBRARY_PATH:默认是当前系统的标准目录，不建议修改它；例如在我的系统，这个变量的值是/usr/lib/X11；
    CMAKE_SYSTEM_FRAMEWORK_PATH:macOS框架路径，默认是当前系统的标准目录，不建议修改它；例如在我的系统，这个变量的值包含了路径/Library/Frameworks；
  6）PATHS选项指定的路径。
]]

# 三、find_library命令中的部分选项
#[[
1.PATH_SUFFIXES：为每个搜索目录添加变量PATH_SUFFIXES指定的后缀目录，假设当前搜索的目录为/A;/C/D，PATH_SUFFIXES指定的后缀目录为PS(当前可以指定多个，以分号分割开即可)，那么除了/A;/C/D之外，/A/PS;/C/D/PS也会被搜索。

  // 顶层CMakeLists.txt
  make_minimum_required (VERSION 3.21)
  project (fl)
  find_library (libvar mymath PATHS ./ PATH_SUFFIXES mylib) # 会从./以及./mylib中搜索指定的mymath库是否存在
  if (${libvar} STREQUAL "libvar-NOTFOUND")
      message (FATAL_ERROR "required mymath library but not found!")
  else()
      message (STATUS "mymath library found in ${libvar}")
  endif()
  // 命令行中执行
  cmake .

  // 执行结果
  -- mymath library found in /XXX/mylib/libmymath.a
]]

#[[
2.NO_CACHE：该选项将<var>变量当成一个普通变量而不是一个缓存条目，需要cmake 3.21及以上的版本支持。
默认find_library命令最终存储结果的变量<var>是一个缓存条目（可以理解为全局变量，且会写入CMakeCache.txt文件，在不清除CMakeCache.txt文件的情况下，
每次执行cmake都会先从CMakeCache.txt载入该变量的值），而且find_library命令只要检查到<var>有值（<var>不为空且<var>不为<var>-NOTFOUND），
是不会执行实际查找库的动作。因此多次对同一个变量<var>执行find_library命令，在第一次<var>被赋值后，后续的find_library命令不会被执行。
结合缓存条目变量，那么只要找到一个<var>，后续每次执行cmake命令得到的<var>都是首次找到的<var>值（除非清除CMakeCache.txt文件）
因此NO_CACHE选项要谨慎使用，它会使得每次cmake命令都会重新调用find_library查找，增加cmake的开销。

  // 顶层CMakeLists.txt
  make_minimum_required (VERSION 3.21)
  project (fl)
  find_library (libvar mymath PATHS ./mylib NO_CACHE)
  find_library (libvar mymath PATHS ./lib NO_CACHE) # 即使./lib中也存在mymath库，由于在上一步的./mylib中已经找到，因此本条命令不会执行查找
  if (${libvar} STREQUAL "libvar-NOTFOUND")
      message (FATAL_ERROR "required mymath library but not found!")
  else()
      message (STATUS "mymath library found in ${libvar}")
  endif()

  // 命令行中执行
  cmake .

  // 执行结果
  -- mymath library found in /XXX/mylib/libmymath.a

  // 顶层CMakeLists.txt
  make_minimum_required (VERSION 3.21)
  project (fl)
  find_library (libvar mymath PATHS ./mylib) # libvar是缓存条目，会存入`CMakeCache.txt`，后续即使把PATHS ./mylib改成PATHS ./mylib2（不存在库mymath），也不会保存，因为libvar变量已经从缓存中载入
  if (${libvar} STREQUAL "libvar-NOTFOUND")
      message (FATAL_ERROR "required mymath library but not found!")
  else()
      message (STATUS "mymath library found in ${libvar}")
  endif()

  // 命令行中执行
  cmake .

  // 执行结果
  -- mymath library found in /XXX/mylib/libmymath.a

  // 可以在CMakeCache.txt中找到libvar，命令行中执行cat命令查看一下
  > cat CMakeCache.txt | grep "libvar"
  libvar:FILEPATH=/XXX/mylib/libmymath.a

  // 即使此时把顶层CMakeLists.txt中的PATHS修改为不包含mymath库的路径，执行结果也能找到
  find_library (libvar mymath PATHS ./mylib2)

  // cmake .执行结果
  -- mymath library found in /XXX/mylib/libmymath.a
]]

#[[
3.REQUIRED：指定该选项后，当找不到库，会输出一条错误信息并终止cmake处理过程；未指定REQUIRED选项，当find_library未找到库时，
后续find_library有针对<var>的调用会继续查找。该选项需要cmake 3.18及以上的版本支持。

  // 顶层CMakeLists.txt
  make_minimum_required (VERSION 3.21)
  project (fl)
  find_library (libvar mymath PATHS ./mylib REQUIRED)
  if (${libvar} STREQUAL "libvar-NOTFOUND")
      message (FATAL_ERROR "required mymath library but not found!")
  else()
      message (STATUS "mymath library found in ${libvar}")
  endif()

  // 命令行中执行
  cmake .

  // 执行结果
  CMake Error at CMakeLists.txt:4 (find_library):
    Could not find libvar using the following names: mymath
  -- Configuring incomplete, errors occurred!


  // 顶层CMakeLists.txt
  cmake_minimum_required (VERSION 3.21)
  project (fl)

  find_library (libvar mymath PATHS ./mylib2) # 没有指定REQUIRED选项，即使当时没有找到，会继续往下执行
  find_library (libvar mymath PATHS ./mylib)
  if (${libvar} STREQUAL "libvar-NOTFOUND")
      message (FATAL_ERROR "required mymath library but not found!")
  else()
      message (STATUS "mymath library found in ${libvar}")
  endif()

  // 命令行中执行
  cmake .

  // 执行结果
  -- mymath library found in /XXX/mylib/libmymath.a
]]

#[[
4.NO_XXX_PATH：3.1节介绍了关于搜索路径的查找顺序，NO_XXX_PATH选项用于跳过指定的搜索路径。
  NO_CMAKE_PATH：指定该选项会忽略cmake -DCMAKE_XXX_PATH=paths的路径；
  NO_CMAKE_ENVIRONMENT_PATH：指定该选项会忽略环境变量指定的CMAKE_XXX_PATH路径；
  NO_SYSTEM_ENVIRONMENT_PATH：指定该选项会忽略系统标准环境变量指定的路径；
  NO_CMAKE_SYSTEM_PATH：指定该选项会忽略平台路径指定的CMAKE_SYSTEM_XXX_PATH路径；

5.CMAKE_FIND_ROOT_PATH：指定搜索的根路径。

6.CMAKE_SYSROOT：该选项的值会传递给编译器的--sysroot标记（备注：--sysroot用于指定编译搜索库和头文件的根目的，
例如编译器原本搜搜索/A/include和/A/lib，使用--sysroot=DIR后，编译器搜索的库和头文件目录变成/DIR/A/include和/DIR/A/lib）。
]]

#[[
7.FIND_LIBRARY_USE_LIB32_PATHS、FIND_LIBRARY_USE_LIBX32_PATHS、FIND_LIBRARY_USE_LIB64_PATHS：这三个属性指明了要在搜索路径中匹配到lib/后，
会为这个目录添加一个后缀，然后在添加后缀后的目录中搜索库。三个属性添加后的值为lib32/、libx32/、lib64/，这个是根据平台（32位或64位自动添加的），
例如在我的系统中，除了搜索lib/外，也会搜索lib64/：

  // 顶层CMakeLists.txt
  cmake_minimum_required (VERSION 3.21)
  project (fl)

  find_library (libvar mymath PATHS ./lib) # 假设lib目录不存在但是lib64目录存在
  if (${libvar} STREQUAL "libvar-NOTFOUND")
      message (FATAL_ERROR "required mymath library but not found!")
  else()
      message (STATUS "mymath library found in ${libvar}")
  endif()

  // 命令行中执行
  cmake .

  // 执行结果
  -- mymath library found in /XXX/lib64/libmymath.a
]]

# 设置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output)

# 添加包含子目录
add_subdirectory(math)

# 查找原文件
aux_source_directory(. SRC_LISTS)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LISTS})

# 添加头文件目录
# include_directories(${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 查找链接库MathFunctions
# set (CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/math/lib")
set(CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/lib")

# set(CMAKE_LIBRARY2_PATH "${CMAKE_SOURCE_DIR}/lib2")

# find_library(MyMathFunctions NAMES MathFunctions PATHS ${CMAKE_LIBRARY_PATH})
# find_library(MyShape NAMES Shape PATHS ${CMAKE_LIBRARY_PATH})
# find_library(MyMathFunctions NAMES MathFunctions HINTS ${CMAKE_LIBRARY_PATH})
# find_library(MyShape NAMES Shape HINTS ${CMAKE_LIBRARY_PATH})
# find_library(MyMathFunctions MathFunctions ${CMAKE_LIBRARY_PATH})
# find_library(MyShape Shape ${CMAKE_LIBRARY_PATH}) # 使用默认搜索路径

# find_library(MyMathFunctions MathFunctions "${CMAKE_SOURCE_DIR}/lib2" NO_DEFAULT_PATH) # 不使用默认搜索路径
find_library(MyMathFunctions MathFunctions) # 使用默认搜索路径
find_library(MyShape Shape) # 使用默认搜索路径
message(STATUS "MyMathFunctions:${MyMathFunctions}")
message(STATUS "MyShape:${MyShape}")

# 链接对象库 - 动态库
target_link_libraries(${PROJECT_NAME} ${MyMathFunctions} ${MyShape})
