
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

PROJECT(oel)
PROJECT(liboel)

INCLUDE_DIRECTORIES(/usr/local/include/antlr4-runtime)
LINK_DIRECTORIES(/usr/local/lib)

ADD_SUBDIRECTORY(opene_parse)

ADD_LIBRARY(liboel
        oe_driver.cpp
        oe_driver.h
        )

TARGET_LINK_LIBRARIES(liboel
        antlr4-runtime
        )

ADD_EXECUTABLE(oel
        main_entity.cpp
        )

TARGET_LINK_LIBRARIES(oel
        OECompilerParse
        liboel
        )
