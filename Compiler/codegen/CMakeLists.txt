
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(CodeGen CXX)

FIND_PACKAGE(LLVM 9 REQUIRED QUIET CONFIG)
MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

SET(CodeGen-Source
        LLCodeGen.cpp
        LLCodeGen.h
        )

ADD_LIBRARY(CodeGen
        ${CodeGen-Source}
        )

llvm_map_components_to_libnames(LLVM bitwriter)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_link_libraries(CodeGen ${LLVM})
else()
    target_link_libraries(CodeGen LLVM)
endif()
