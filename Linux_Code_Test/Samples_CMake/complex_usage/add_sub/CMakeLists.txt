ADD_SUBDIRECTORY(add)
ADD_SUBDIRECTORY(sub)

#目录的安装 
#INSTALL(DIRECTORY ./add/src/
#	DESTINATION include/add/
#	FILES_MATCHING  PATTERN "*.h" 
#	)

#INSTALL(DIRECTORY ./sub/src/
#	DESTINATION include/sub/
#	FILES_MATCHING PATTERN "*.h"
#	)