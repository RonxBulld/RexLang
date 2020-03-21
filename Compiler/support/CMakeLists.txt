
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(Support)

LINK_DIRECTORIES(/usr/local/lib)

ADD_LIBRARY(Support SHARED
        ProjectDB.h
        ProjectDB.cpp
        Command.cpp Command.h)
