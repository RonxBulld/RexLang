
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(CodeGen)

FIND_PACKAGE(LLVM 9 REQUIRED CONFIG PATHS /mnt/d/DevCol/ NO_DEFAULT_PATH)
MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

SET(CodeGen-Source
        LLCodeGen.cpp
        LLCodeGen.h
        )

ADD_LIBRARY(CodeGen SHARED
        ${CodeGen-Source}
        )

llvm_map_components_to_libnames(LLVM bitwriter)
target_link_libraries(CodeGen LLVM)
