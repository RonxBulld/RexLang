
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(GenIR CXX)

INCLUDE(ref_llvm_pkg)

ADD_SUBDIRECTORY(LLVMIR)

ADD_LIBRARY(${PROJECT_NAME}
        SimpleRTTI_ArguType.h
        GenIRPass.cpp
        )

target_link_libraries(${PROJECT_NAME}
        GenLLIR
        )
