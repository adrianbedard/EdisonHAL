IF(NOT EDISONHAL_CMAKE)
SET(EDISONHAL_CMAKE 1)

INCLUDE(${GLOBAL_DIR}/osMechanics/CMakeLists.txt)

MESSAGE(STATUS )
MESSAGE(STATUS ========= Edison HAL ==========)
MESSAGE(STATUS )

SET(CUR_SRC ${GLOBAL_DIR}/EdisonHAL)
INCLUDE_DIRECTORIES(${GLOBAL_DIR})

IF(EXISTS /usr/include/mraa.h)

MESSAGE(STATUS )
MESSAGE(STATUS Using Edison HAL...)
MESSAGE(STATUS )

SET(EXE_LIBS ${EXE_LIBS} mraa)
SET( SRC_H
	${CUR_SRC}/EdisonHeaders/hardwareHeader.h
)
INCLUDE_DIRECTORIES(${CUR_SRC}/EdisonHeaders)

ELSE()

MESSAGE(STATUS )
MESSAGE(STATUS Using false HAL...)
MESSAGE(STATUS )

SET( SRC_H
	${CUR_SRC}/FalseHeaders/hardwareHeader.h
)
INCLUDE_DIRECTORIES(${CUR_SRC}/FalseHeaders)

ENDIF()

SET( SRC_H ${SRC_H}
	${CUR_SRC}/EdisonHal.h
	${CUR_SRC}/motorController.h
)

SET( SRC_CPP
	${CUR_SRC}/EdisonHalLogging.cpp
	${CUR_SRC}/motorController.cpp
)

ADD_LIBRARY( EdisonHal STATIC
	${SRC_CPP}
	${SRC_H}
)
TARGET_LINK_LIBRARIES( EdisonHal
	${OS_LIBS}
	${EXE_LIBS}
)
SET(EXE_LIBS ${EXE_LIBS} EdisonHal)
INCLUDE(${GLOBAL_DIR}/EdisonHAL/test/CMakeLists.txt)

ENDIF(NOT EDISONHAL_CMAKE)