
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(${COMPILER_EXECUTE_NAME} CXX)

INCLUDE_DIRECTORIES(/usr/local/include/antlr4-runtime)
LINK_DIRECTORIES(/usr/local/lib)

ADD_SUBDIRECTORY(rexlang_compiler)
ADD_SUBDIRECTORY(ir)
ADD_SUBDIRECTORY(codegen)
ADD_SUBDIRECTORY(link)
ADD_SUBDIRECTORY(support)

IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    ADD_DEFINITIONS(-DMS_UTF8_REQUEST)
    ADD_DEFINITIONS(-DWIN_STYLE_EXEC)
ENDIF()

ADD_EXECUTABLE(${COMPILER_EXECUTE_NAME}
        compile_driver.cpp
        compile_driver.h
        main_entity.cpp
        )

TARGET_LINK_LIBRARIES(${COMPILER_EXECUTE_NAME}
        REXCompilerParse
        IR
        antlr4-runtime
        CodeGen
        lite_util
        Link
        Support
        )

INSTALL(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${COMPILER_EXECUTE_NAME}
        DESTINATION bin
        )
