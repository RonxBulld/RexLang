
######################################
# 检查是否在64位平台上使用64位工具链
######################################
IF (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    MESSAGE(FATAL_ERROR "Must be built using 64-bit tools on 64-bit systems.[sizeof(void*)=${CMAKE_SIZEOF_VOID_P}]")
ENDIF()
