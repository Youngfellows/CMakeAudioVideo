# 查找当前目录下的所有源文件，并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library(MathFunctions ${DIR_LIB_SRCS})

function(bar)
    message("CMAKE_CURRENT_FUNCTION ${CMAKE_CURRENT_FUNCTION}")
    message("CMAKE_CURRENT_FUNCTION_LIST_DIR ${CMAKE_CURRENT_FUNCTION_LIST_DIR}")
    message("CMAKE_CURRENT_FUNCTION_LIST_FILE ${CMAKE_CURRENT_FUNCTION_LIST_FILE}")
    message("CMAKE_CURRENT_FUNCTION_LIST_LINE ${CMAKE_CURRENT_FUNCTION_LIST_LINE}")
endfunction()