# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(Sample)

message(STATUS "==============start build test_sdk==============")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -z defs -pthread")

message(STATUS "test_sdk install dir: ${SDK_INSTALL_PATH}")

# 添加头文件搜索路径
include_directories(${SDK_INSTALL_PATH}/include/sdk/math)
include_directories(${SDK_INSTALL_PATH}/include/sdk/shape)

# 添加源文件
aux_source_directory(. TEST_SRC_LIST)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${TEST_SRC_LIST})

# 添加依赖库,并链接
#[[
set(DEP_LIBS
	${SDK_INSTALL_PATH}/lib/libMathFunctions.so
	${SDK_INSTALL_PATH}/lib/libShape.so
	)
target_link_libraries(${PROJECT_NAME} ${DEP_LIBS})
]]


# 查找链接库
# set (CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/math/lib")
set(CMAKE_LIBRARY_PATH "${SDK_INSTALL_PATH}/lib")

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

# 安装可执行文件到指定目录
install(TARGETS ${PROJECT_NAME}
    DESTINATION bin)

