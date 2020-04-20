
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(Support CXX)

LINK_DIRECTORIES(/usr/local/lib)

ADD_LIBRARY(Support
        ProjectDB.h
        ProjectDB.cpp
        ProgramDB.cpp
        ProgramDB.h
        )

TARGET_LINK_LIBRARIES(Support lite_util)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    TARGET_LINK_LIBRARIES(Support stdc++fs)
endif ()