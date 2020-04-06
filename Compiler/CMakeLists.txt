
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(oel CXX)

INCLUDE_DIRECTORIES(/usr/local/include/antlr4-runtime)
LINK_DIRECTORIES(/usr/local/lib)

ADD_SUBDIRECTORY(opene_compiler)
ADD_SUBDIRECTORY(ir)
ADD_SUBDIRECTORY(codegen)
ADD_SUBDIRECTORY(link)
ADD_SUBDIRECTORY(support)
#ADD_SUBDIRECTORY(interpreter)

IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    ADD_DEFINITIONS(-DMS_UTF8_REQUEST)
    ADD_DEFINITIONS(-DWIN_STYLE_EXEC)
ENDIF()

ADD_EXECUTABLE(oel
        oe_driver.cpp
        oe_driver.h
        main_entity.cpp
        )

TARGET_LINK_LIBRARIES(oel
        OECompilerParse
        IR
        antlr4-runtime
        CodeGen
        lite_util
        Link
        Support
        )
