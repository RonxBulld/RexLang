
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(Support CXX)

LINK_DIRECTORIES(/usr/local/lib)

ADD_LIBRARY(Support
        ProjectDB.h
        ProjectDB.cpp
        Command.cpp
        Command.h
        ProgramDB.cpp
        ProgramDB.h
        )

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    TARGET_LINK_LIBRARIES(Support stdc++fs)
endif ()