
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

#####################################################
# RexStartup
#####################################################

PROJECT(rex_startup_kit C)

ADD_LIBRARY(${PROJECT_NAME} STATIC
        rex_startup.c
        )

INSTALL(TARGETS
        ${PROJECT_NAME}
        DESTINATION lib/rex
        )

#####################################################
# CoreLib
#####################################################

PROJECT(corelib CXX)

SET(${PROJECT_NAME}-Source
        newcore.cpp
        newcore.h
        array_runtime_api.cpp
        array_runtime_api.h
        string_runtime_api.cpp
        string_runtime_api.h
        struct_runtime_api.cpp
        struct_runtime_api.h
        )

ADD_LIBRARY(${PROJECT_NAME} STATIC
        ${${PROJECT_NAME}-Source}
        )

file(COPY "${PROJECT_NAME}.txt" DESTINATION "${CMAKE_INCLUDE_OUTPUT_DIRECTORY}")

INSTALL(FILES
        ${PROJECT_NAME}.txt
        DESTINATION include/rex
        )
INSTALL(TARGETS
        ${PROJECT_NAME}
        DESTINATION lib/rex
        )
