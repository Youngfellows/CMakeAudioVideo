#/cmake/mul_div/mul
AUX_SOURCE_DIRECTORY(./src MUL_SRC_LIST)

ADD_LIBRARY(mul_oper STATIC
	${MUL_SRC_LIST}
	)

INSTALL(DIRECTORY ./src/
	DESTINATION include/mul_div/mul
	FILES_MATCHING PATTERN "*.h"
	)

INSTALL(TARGETS mul_oper
	DESTINATION lib
	)