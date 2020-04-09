
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(lite_util CXX)

SET(lite_util-Source
        StringUtil.cpp
        StringUtil.h
        ContainerUtil.cpp
        ContainerUtil.h
        Defer.h
        )

ADD_LIBRARY(lite_util STATIC
        ${lite_util-Source}
        )
