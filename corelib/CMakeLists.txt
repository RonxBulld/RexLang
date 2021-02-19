
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

SET(API_FILES corelib stdrex)
FOREACH(API_FILE ${API_FILES})
    FILE(COPY "${API_FILE}.txt" DESTINATION "${CMAKE_INCLUDE_OUTPUT_DIRECTORY}")
ENDFOREACH()

ADD_DEPENDENCIES(${PROJECT_NAME} rex_startup_kit)

FOREACH(API_FILE ${API_FILES})
INSTALL(FILES
        ${API_FILE}.txt
        DESTINATION include/rex
        )
ENDFOREACH()

INSTALL(TARGETS
        ${PROJECT_NAME}
        DESTINATION lib/rex
        )
