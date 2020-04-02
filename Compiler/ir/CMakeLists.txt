
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(IR)

FIND_PACKAGE(LLVM 9 QUIET CONFIG PATHS /mnt/d/DevCol/ NO_DEFAULT_PATH)
IF (NOT LLVM_FOUND)
    FIND_PACKAGE(LLVM 9 REQUIRED CONFIG)
ENDIF()

MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

SET(IR-Source
        EmitLLVMIR.cpp
        EmitLLVMIR.h
        EmitOEIR.cpp
        EmitOEIR.h
        LLVMRTIRBuilder.cpp
        LLVMRTIRBuilder.h
        )

ADD_LIBRARY(IR SHARED
        ${IR-Source}
        )

llvm_map_components_to_libnames(llvm_libs support core irreader bitwriter X86)
target_link_libraries(IR ${llvm_libs})
