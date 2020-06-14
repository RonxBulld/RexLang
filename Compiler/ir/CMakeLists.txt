
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(IR CXX)

FIND_PACKAGE(LLVM 9 REQUIRED QUIET CONFIG)
MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

MESSAGE(STATUS "${LLVM_INCLUDE_DIRS}")
FILE(READ_SYMLINK "${LLVM_INCLUDE_DIRS}/llvm" REAL_LLVM_INCLUDE_DIRS)
SET(REAL_LLVM_INCLUDE_DIRS "${LLVM_INCLUDE_DIRS}/${REAL_LLVM_INCLUDE_DIRS}/../")
MESSAGE(STATUS "${REAL_LLVM_INCLUDE_DIRS}")

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${REAL_LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

ADD_LIBRARY(IR
        SimpleRTTI_ArguType.h
        LLVMIR/EmitLLVMIR.cpp
        LLVMIR/EmitLLVMIR.h
        LLVMIR/LLVMRTIRBuilder.cpp
        LLVMIR/LLVMRTIRBuilder.h
        LLVMIR/Emitter.cpp
        LLVMIR/Emitter.h
        LLVMIR/DebugInfoMgr.cpp
        LLVMIR/DebugInfoMgr.h
        )

llvm_map_components_to_libnames(LLVM support core irreader X86)
target_link_libraries(IR ${LLVM})
