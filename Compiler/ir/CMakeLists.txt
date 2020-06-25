
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(IR CXX)

INCLUDE(ref_llvm_pkg)

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

MAP_LLVM_COMPONENTS(LLVM-Libs support core irreader X86)
target_link_libraries(IR ${LLVM-Libs})
