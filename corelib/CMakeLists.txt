
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(newcore)

SET(newcore-Source
        newcore.cpp
        newcore.h runtime_api.cpp runtime_api.h)

ADD_LIBRARY(newcore STATIC
        ${newcore-Source}
        )

target_link_libraries(newcore ${llvm_libs})

file(COPY "corelib.txt" DESTINATION "${INSTALLROOT}/include/")
