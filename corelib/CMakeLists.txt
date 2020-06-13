
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(corelib CXX)

SET(corelib-Source
        newcore.cpp
        newcore.h
        array_runtime_api.cpp
        array_runtime_api.h
        string_runtime_api.cpp
        string_runtime_api.h
        struct_runtime_api.cpp struct_runtime_api.h)

ADD_LIBRARY(corelib STATIC
        ${corelib-Source}
        )

file(COPY "corelib.txt" DESTINATION "${CMAKE_INCLUDE_OUTPUT_DIRECTORY}")

INSTALL(FILES
        corelib.txt
        DESTINATION include/rex
        )
INSTALL(TARGETS
        corelib
        DESTINATION lib/rex
        )
