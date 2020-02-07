
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(oel)

INCLUDE_DIRECTORIES(/usr/local/include/antlr4-runtime)
LINK_DIRECTORIES(/usr/local/lib)

ADD_SUBDIRECTORY(opene_compiler)
ADD_SUBDIRECTORY(ir)
ADD_SUBDIRECTORY(interpreter)

ADD_EXECUTABLE(oel
        oe_driver.cpp
        oe_driver.h
        main_entity.cpp
        )

TARGET_LINK_LIBRARIES(oel
        OECompilerParse
        antlr4-runtime
        IR
        )
