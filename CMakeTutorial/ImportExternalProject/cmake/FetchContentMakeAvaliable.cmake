# Campatible with cmake 3.11 and above.
macro(FetchContent_MakeAvailable NAME)
    message(STATUS "NAME::##${NAME}")
    FetchContent_GetProperties(${NAME})

    if(NOT ${NAME}_POPULATED)
        FetchContent_Populate(${NAME})
        add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})
    endif()
endmacro()
