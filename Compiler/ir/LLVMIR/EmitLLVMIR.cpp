//
// Created by rex on 2020/2/4.
//

#include <llvm/Support/FileSystem.h>

#include "EmitLLVMIR.h"
#include "NewEmitter.h"

namespace rexlang {

    EmitLLVMIR::EmitLLVMIR(TranslateUnit *translateUnit, ProjectDB &projectDB) {
        emitter = new NewEmitter;
        emitter->Gen(projectDB);
        llvm::Module *TheModule = GetModule();
        assert(TheModule);
    }

    void EmitLLVMIR::WriteOutIR() {
        std::error_code EC;
        llvm::raw_fd_ostream of(emitter->GetModule()->getName().str(), EC, llvm::sys::fs::F_None);
        emitter->GetModule()->print(
                of,
                nullptr,
                false,
                true
                );
    }

    llvm::Module *EmitLLVMIR::GetModule() const {
        return emitter->GetModule();
    }
}
