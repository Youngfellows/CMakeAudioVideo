# cmake 最低版本要求,不加入此行会受到警告信息
cmake_minimum_required(VERSION 3.15.0)

# 设置项目名称
project("Sample")
message("PROJECT_NAME: " ${PROJECT_NAME})

# 为了分行确定输出内容
message("************************************************")
message("1. PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message("2. PROJECT_SOURCE _DIR = ${_DIR}")
message("3. CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message("4. CMAKE_CURRRENT_BINARY_DIR = ${CMAKE_CURRRENT_BINARY_DIR}")
message("5. CMAKE_CURRENT_LIST_FILE = ${CMAKE_CURRENT_LIST_FILE}")
message("6. CMAKE_CURRENT_LIST_LINE = ${CMAKE_CURRENT_LIST_LINE}")
message("7. CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
message("8. CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("9. EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")
message("10. LIBRARY_OUTPUT_PATH = ${LIBRARY_OUTPUT_PATH}")
message("11. PROJECT_NAME = ${PROJECT_NAME}")
message("12. PROJECT_VERSION_MAJOR = ${PROJECT_VERSION_MAJOR}")
message("13. PROJECT_VERSION_MINOR = ${PROJECT_VERSION_MINOR}")
message("14. PROJECT_VERSION_PATCH = ${PROJECT_VERSION_PATCH}")
message("15. CMAKE_SYSTEM = ${CMAKE_SYSTEM}")
message("16. CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
message("17. CMAKE_SYSTEM_VERSION = ${CMAKE_SYSTEM_VERSION}")
message("18. BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
message("19. CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")
message("20. CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("21. CMAKE_SYSTEM_PROCESSOR   = ${CMAKE_SYSTEM_PROCESSOR}")
message("**************************************************")

# 输出不同级别的消息
message("======================================")
message("1. NONE")
message(NOTICE "2. NOTICE")
message(STATUS "3. STATUS")
message(WARNING "4. WARNING")
message(DEPRECATION "5. DEPRECATION")
message(AUTHOR_WARNING "6. AUTHOR_WARNING")
message(SEND_ERROR "7. SEND_ERROR")
message(FATAL_ERROR "8. FATAL_ERROR")
message(VERBOSE "9. VERBOSE")
message(DEBUG "10. DEBUG")
message(TRACE "11. TRACE")
message("======================================")