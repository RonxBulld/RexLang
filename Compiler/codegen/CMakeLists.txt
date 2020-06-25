
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(CodeGen CXX)

INCLUDE(ref_llvm_pkg)

SET(CodeGen-Source
        LLCodeGen.cpp
        LLCodeGen.h
        )

ADD_LIBRARY(CodeGen
        ${CodeGen-Source}
        )

MAP_LLVM_COMPONENTS(LLVM-Libs bitwriter)
target_link_libraries(CodeGen ${LLVM-Libs})
