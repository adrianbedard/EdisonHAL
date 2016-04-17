IF(NOT EDISON_HARDWARE_CMAKE)
SET(EDISON_HARDWARE_CMAKE 1)

INCLUDE(${GLOBAL_DIR}/EdisonHAL/CMakeLists.txt)

MESSAGE(STATUS )
MESSAGE(STATUS ========= Hardware Main ==========)
MESSAGE(STATUS )

SET(CUR_SRC ${GLOBAL_DIR}/EdisonHAL/HardwareTest)
INCLUDE_DIRECTORIES(${CUR_SRC})

SET(SRC_H
	${CUR_SRC}/helloWorldMraa.h
	${CUR_SRC}/motorController.h
)
SET(SRC_CPP
	${CUR_SRC}/helloWorldMraa.cpp
	${CUR_SRC}/hardwareEntry.cpp
	${CUR_SRC}/motorController.cpp
)

ADD_EXECUTABLE( HardwareTest ${SRC_CPP} ${SRC_H})

IF( WIN32 )
ELSEIF( APPLE )
	SET(OS_DEF -std=c++11 -c -w)
ELSE()
	SET(OS_LIBS pthread )
	SET(OS_DEF -std=c++11 -c -w)
ENDIF()

ADD_DEFINITIONS(${OS_DEF})
TARGET_LINK_LIBRARIES( HardwareTest
	${OS_LIBS}
	${EXE_LIBS}
)

ENDIF(NOT EDISON_HARDWARE_CMAKE)