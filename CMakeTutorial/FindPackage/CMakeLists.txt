project(FindPackageTutorial)
cmake_minimum_required(VERSION 3.0)

# 查找CURL库
find_package(CURL)

if(CURL_FOUND)
    add_executable(curltest curltest.cc)
    target_include_directories(curltest PRIVATE ${CURL_INCLUDE_DIR})
    target_link_libraries(curltest ${CURL_LIBRARY})
    install(TARGETS curltest DESTINATION bin)
else(CURL_FOUND)
    # message(FATAL_ERROR "CURL library not found")
    message(WARNING "CURL library not found")
endif(CURL_FOUND)

# 查找GLOG库
find_package(GLOG)

if(GLOG_FOUND)
    add_executable(glogtest glogtest.cc)

    # 由于glog在连接时将头文件直接链接到了库里面，所以这里不用显示调用target_include_directories
    target_link_libraries(glogtest glog::glog)
    install(TARGETS glogtest DESTINATION bin)
else(GLOG_FOUND)
    # message(FATAL_ERROR "glog library not found")
    message(STATUS "glog library not found")
endif(GLOG_FOUND)

# 查找自己生成ADD库
# 将项目目录下的cmake文件夹加入到CMAKE_MODULE_PATH中，让find_pakcage能够找到我们自定义的函数库
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

find_package(ADD)

if(ADD_FOUND)
    add_executable(addtest addtest.cc)
    target_include_directories(addtest PRIVATE ${ADD_INCLUDE_DIR})
    target_link_libraries(addtest ${ADD_LIBRARY})
    install(TARGETS addtest DESTINATION bin)
else(ADD_FOUND)
    message(FATAL_ERROR "ADD library not found")
endif(ADD_FOUND)
