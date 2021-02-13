
PROJECT(GenLLIR)

ADD_LIBRARY(${PROJECT_NAME} OBJECT
        GenLLIRPass.cpp

        EmitLLVMIR.cpp
        EmitLLVMIR.h
#        LLVMRTIRBuilder.cpp
#        LLVMRTIRBuilder.h
        NewEmitter.cpp
        NewEmitter.h
        DebugInfoMgr.cpp
        DebugInfoMgr.h
        LLCodeGen.cpp
        LLCodeGen.h
        LowAST.cpp
        LowAST.h
)

target_link_libraries(${PROJECT_NAME} LLVM)
