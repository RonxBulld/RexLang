
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(lite_util CXX)

ADD_LIBRARY(lite_util
        StringUtil.cpp
        StringUtil.h
        ContainerUtil.cpp
        ContainerUtil.h
        Defer.h
        Command.cpp
        Command.h
        EventSlot.cpp
        EventSlot.h
        StringRef.cpp
        StringRef.h
        TString.cpp
        TString.h
        ErrOr.cpp
        ErrOr.h
        ordered_map/ordered_hash.h
        ordered_map/ordered_map.h
        ordered_map/ordered_set.h
        )
