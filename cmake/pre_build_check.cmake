

######################################
# 检查GCC版本是否符合要求
######################################
SET(GCC_EXPECTED_VERSION 9.2.0)
IF(CMAKE_CXX_COMPILER_VERSION VERSION_LESS GCC_EXPECTED_VERSION)
    MESSAGE(FATAL_ERROR "GCC: REXLang requires version ${GCC_EXPECTED_VERSION} to build but found ${CMAKE_CXX_COMPILER_VERSION}")
ENDIF()

######################################
# 检查是否在64位平台上使用64位工具链
######################################
IF (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    MESSAGE(FATAL_ERROR "Must be built using 64-bit tools on 64-bit systems.[sizeof(void*)=${CMAKE_SIZEOF_VOID_P}]")
ENDIF()
