
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(newcore)

SET(newcore-Source
        newcore.cpp
        newcore.h array_runtime_api.cpp array_runtime_api.h string_runtime_api.cpp string_runtime_api.h)

ADD_LIBRARY(newcore STATIC
        ${newcore-Source}
        )

file(COPY "corelib.txt" DESTINATION "${INSTALLROOT}/include/")
