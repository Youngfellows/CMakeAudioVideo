#/cmake/add_sub_sub
AUX_SOURCE_DIRECTORY(./src SUB_SRC_LIST)

ADD_LIBRARY(sub_oper STATIC
	${SUB_SRC_LIST}
	)

INSTALL(DIRECTORY ./src/
	DESTINATION include/add_sub/sub
	FILES_MATCHING PATTERN "*.h"
	)

INSTALL(TARGETS sub_oper
	DESTINATION lib
	)
