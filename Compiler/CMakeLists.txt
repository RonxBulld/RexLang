
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(${COMPILER_EXECUTE_NAME} CXX)

INCLUDE_DIRECTORIES(/usr/local/include/antlr4-runtime)
LINK_DIRECTORIES(/usr/local/lib)

OPTION(ENABLE_GENIR "Enable generate IR." ON)
OPTION(ENABLE_LINK  "Enable link module files to executable file." OFF)

SET(ADDITION_LIBRARIES )

ADD_SUBDIRECTORY(rexlang_compiler)
IF (${ENABLE_GENIR})
    ADD_SUBDIRECTORY(ir)
    ADD_SUBDIRECTORY(codegen)
    LIST(APPEND ADDITION_LIBRARIES GenIR;CodeGen)
    IF (${ENABLE_LINK})
        ADD_SUBDIRECTORY(link)
        LIST(APPEND ADDITION_LIBRARIES LinkerAPI)
    ENDIF()
ENDIF()
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
        antlr4-runtime

        -Wl,-whole-archive
        REXCompilerParse
        ${ADDITION_LIBRARIES}
        -Wl,-no-whole-archive

        lite_util
        Support
        )

INSTALL(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${COMPILER_EXECUTE_NAME}
        DESTINATION bin
        )
