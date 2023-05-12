# 设置cmake最小版本
cmake_minimum_required(VERSION 3.14)

# 设置项目名称
project(gif-decoder-encoder)

# 设置C++语言支持
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找父目录3rd
message(STATUS "CMAKE_CURRENT_SOURCE_DIR::${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(VAR_PARENT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
message(STATUS "parent dir::${VAR_PARENT}")

# 设置头文件查找目录
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/include/")

# 将包含目录添加到构建中
include_directories(pthread/include)

# 设置C++源文件
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/ GIF_SRC)
set(GIF_DECODER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/AndroidGifDecoder.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/GifDecoder.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/DataBlock.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/BitmapIterator.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/GifFrame.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/SampleGifDecoder.cpp;")
# message(STATUS "GIF_DECODER_SRC:: ${GIF_DECODER_SRC}")

set(GIF_ENCODER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/SimpleGCTEncoder.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/GifEncoder.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/BaseGifEncoder.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/BitWritingBlock.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/GCTGifEncoder.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/LCTGifEncoder.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/gif-library/cpp/FastGifEncoder.cpp;\
${CMAKE_CURRENT_SOURCE_DIR}/src/SampleGifEncoder.cpp;")
# message(STATUS "GIF_ENCODER_SRC:: ${GIF_ENCODER_SRC}")

# 生成可执行文件
add_executable(21-gif-decoder ${GIF_DECODER_SRC})
add_executable(21-gif-encoder ${GIF_ENCODER_SRC})

# 查找thread库
find_library(pthread_lib NAMES pthread PATHS ./pthread)
message(STATUS "pthread_lib:${pthread_lib}")

# 添加math依赖库
find_library(PTHREAD_LIB pthread) # 使用默认搜索路
message(STATUS "PTHREAD_LIB:${PTHREAD_LIB}")

# 将pthread_lib 这个变量设置在THIRDPARTY_LIBRARIES 中
set(THIRDPARTY_LIBRARIES ${pthread_lib})

# 连接依赖库
target_link_libraries(21-gif-decoder ${THIRDPARTY_LIBRARIES})
target_link_libraries(21-gif-encoder ${THIRDPARTY_LIBRARIES})

# 安装到指定目录
install(TARGETS 21-gif-decoder DESTINATION bin)
install(TARGETS 21-gif-encoder DESTINATION bin)
