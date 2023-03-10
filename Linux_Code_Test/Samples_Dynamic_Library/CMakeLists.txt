# CMake file for Samples_Dynamic_Library

# 设定依赖的CMake版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

# 指定项目名称
PROJECT(Test_Dynamic_Library)

# 打印相关信息, CMAKE_CURRENT_SOURCE_DIR指的是当前处理的CMakeLists.txt所在的路径
MESSAGE(STATUS "current path: ${CMAKE_CURRENT_SOURCE_DIR}")

# 使CMake支持C++11特性
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu++0x")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

# 定义用户自定义变量  
SET(PATH_DYNAMIC_LIBRARY_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Dynamic_Library)
SET(PATH_TEST_DYNAMIC_LIBRARY_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Test_Dynamic_Library)
SET(PATH_DYNAMIC_LIBRARY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dynamic_Library)
#MESSAGE(STATUS "Dynamic Library cpp files path: ${PATH_DYNAMIC_LIBRARY_CPP_FILES}")
#MESSAGE(STATUS "Test Dynamic Library cpp files path: ${PATH_TEST_DYNAMIC_LIBRARY_CPP_FILES}")

# 递归查询所有匹配的文件:*.cpp
FILE(GLOB_RECURSE DYNAMIC_LIBRARY_CPP_LIST ${PATH_DYNAMIC_LIBRARY_CPP_FILES}/*.cpp)
FILE(GLOB_RECURSE TEST_DYNAMIC_LIBRARY_CPP_LIST ${PATH_TEST_DYNAMIC_LIBRARY_CPP_FILES}/*.cpp)
#MESSAGE(STATUS "Dynamic Library cpp list: ${DYNAMIC_LIBRARY_CPP_LIST}")
#MESSAGE(STATUS "Test Dynamic Library cpp list: ${TEST_DYNAMIC_LIBRARY_CPP_LIST}")

IF (BUILD_DYNAMIC_LIBRARY)
    # 添加编译参数，添加-D预编译宏定义，可以一次添加多个
    ADD_DEFINITIONS(-DFBC_EXPORT)
    # 生成动态库
    ADD_LIBRARY(Dynamic_Library SHARED ${DYNAMIC_LIBRARY_CPP_LIST})
ELSE()
    ADD_LIBRARY(Static_Library STATIC ${DYNAMIC_LIBRARY_CPP_LIST})
ENDIF()

# 指定需要包含的头文件
INCLUDE_DIRECTORIES(${PATH_DYNAMIC_LIBRARY_INCLUDE_DIR})

# 生成可执行文件Test_Dynamic_Library
ADD_EXECUTABLE(Test_Dynamic_Library ${TEST_DYNAMIC_LIBRARY_CPP_LIST})
IF (BUILD_DYNAMIC_LIBRARY)
    # 用来为target添加需要链接的共享库，指定工程所用的依赖库，包括动态库和静态库
    TARGET_LINK_LIBRARIES(Test_Dynamic_Library Dynamic_Library)
ELSE()
    TARGET_LINK_LIBRARIES(Test_Dynamic_Library Static_Library)
ENDIF()