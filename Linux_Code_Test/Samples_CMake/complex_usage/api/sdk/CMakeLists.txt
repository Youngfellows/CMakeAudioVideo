AUX_SOURCE_DIRECTORY(. SDK_SRC_LIST)

INCLUDE_DIRECTORIES(${SDK_INSTALL_PATH}/include/add_sub)
INCLUDE_DIRECTORIES(${SDK_INSTALL_PATH}/include/mul_div)

ADD_LIBRARY(mathsdk SHARED ${SDK_SRC_LIST})

SET(DEP_LIBS
	${SDK_INSTALL_PATH}/lib/libadd_oper.a
	${SDK_INSTALL_PATH}/lib/libsub_oper.a
	${SDK_INSTALL_PATH}/lib/libmul_oper.a
	${SDK_INSTALL_PATH}/lib/libdiv_oper.a
	)

TARGET_LINK_LIBRARIES(mathsdk ${DEP_LIBS})

INSTALL(TARGETS mathsdk
	DESTINATION lib
	)
