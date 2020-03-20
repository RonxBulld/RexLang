//
// Created by rex on 2020/3/20.
//

#include "LLCodeGen.h"
#include "../ir/EmitLLVMIR.h"

#include <llvm/IR/Module.h>
#include <llvm/Bitcode/BitcodeWriter.h>

namespace opene {

    LLCodeGen::LLCodeGen(EmitLLVMIR &llvmIREmitter) : emitter_(llvmIREmitter) {
    }

    void LLCodeGen::WriteOutBC(const std::string &bc_filename) {

        std::error_code EC;
        llvm::raw_fd_ostream bc_file(bc_filename, EC);
        llvm::WriteBitcodeToFile(*emitter_.GetModule(), bc_file);

    }
}