# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 项目名称为 Sample
project(MathSdkSample)
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

message(STATUS "=============== cmake中add_definitions的用法 ========================")

# add_definitions的功能和C/C++中的#define是一样的
# option(USE_FFMPEG "use ffmpeg " ON)
option(USE_FFMPEG "use ffmpeg " OFF)
message(STATUS "USE_FFMPEG:${USE_FFMPEG}")

if(USE_FFMPEG)
    message(STATUS "USE_FFMPEG IS ${USE_FFMPEG}")
    add_definitions(-DUSE_FFMPEG)
endif()

# 查找源文件
aux_source_directory(. SAMPLE_SRC)
message(STATUS "SAMPLE_SRC:${SAMPLE_SRC}")

# 添加依赖头文件
message(STATUS "SDK_INSTALL_PATH:${SDK_INSTALL_PATH}")
include_directories("${SDK_INSTALL_PATH}/include/math")

# include_directories(./math)

# # 生成可执行文件
add_executable(${PROJECT_NAME} ${SAMPLE_SRC})

# 添加依赖库,并链接
# set(DEP_LIBS
# ${SDK_INSTALL_PATH}/lib/math/libMathFunctions.so
# )
# target_link_libraries(${PROJECT_NAME} ${DEP_LIBS})

# 查找链接库文件
set(CMAKE_LIBRARY_PATH "${SDK_INSTALL_PATH}/lib/math")
find_library(MyMathFunctions MathFunctions) # 使用默认搜索路径
message(STATUS "MyMathFunctions:${MyMathFunctions}")

# 连接依赖库
target_link_libraries(${PROJECT_NAME} ${MyMathFunctions})

# # 安装生成文件到指定目录
install(TARGETS ${PROJECT_NAME} DESTINATION bin)