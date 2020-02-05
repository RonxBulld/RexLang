
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(IR)

FIND_PACKAGE(LLVM 9 REQUIRED CONFIG PATHS /mnt/d/DevCol/ NO_DEFAULT_PATH)
MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

SET(IR-Source
        EmitIR.cpp
        EmitIR.h
        IR.cpp IR.h)

ADD_LIBRARY(IR SHARED
        ${IR-Source}
        )

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(IR ${llvm_libs})
