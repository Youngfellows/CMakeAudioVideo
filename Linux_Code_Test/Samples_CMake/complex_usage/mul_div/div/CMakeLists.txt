#/cmake/mul_div/div
AUX_SOURCE_DIRECTORY(./src DIV_SRC_LIST)

ADD_LIBRARY(div_oper STATIC
	${DIV_SRC_LIST}
	)

INSTALL(DIRECTORY ./src/
	DESTINATION include/mul_div/div
	FILES_MATCHING PATTERN "*.h"
	)

INSTALL(TARGETS div_oper
	DESTINATION lib
	)