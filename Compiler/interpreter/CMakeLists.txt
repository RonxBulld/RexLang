
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(TreeInterpreter)

SET(TI-Source
        TreeInterpreter.cpp
        TreeInterpreter.h
        )

ADD_EXECUTABLE(TreeInterpreter
        ${TI-Source}
)

