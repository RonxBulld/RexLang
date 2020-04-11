//
// Created by rex on 2020/3/20.
//

#include <iostream>

#include "LLCodeGen.h"
#include "../ir/EmitLLVMIR.h"

#include <llvm/IR/Module.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/LegacyPassManager.h>

namespace rexlang {

    LLCodeGen::LLCodeGen(EmitLLVMIR &llvmIREmitter) : emitter_(llvmIREmitter) {
    }

    int LLCodeGen::WriteOutBC(const std::string &bc_filename) {

        std::error_code EC;
        llvm::raw_fd_ostream bc_file(bc_filename, EC);
        llvm::WriteBitcodeToFile(*emitter_.GetModule(), bc_file);

        if (EC.value() != 0) {
            std::cerr << EC.message() << std::endl;
        }

        return EC.value();
    }

    void LLCodeGen::WriteOutObject(const std::string &bc_filename) {

        auto TargetTriple = llvm::sys::getDefaultTargetTriple();
        std::string Error;
        auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

        if (!Target) {
            llvm::errs() << Error;
            assert(false);
            return;
        }

        auto CPU = "generic";
        auto Features = "";

        llvm::TargetOptions opt;
        auto RM = llvm::Optional<llvm::Reloc::Model>();

        // 将编译的机器信息录入

        auto TheTargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

        // 通过了解目标和数据布局，优化代码

        emitter_.GetModule()->setDataLayout(TheTargetMachine->createDataLayout());

        // 定义文件流

        std::error_code EC;
        llvm::raw_fd_ostream dest(bc_filename, EC, llvm::sys::fs::F_None);

        if (EC) {
            llvm::errs() << "Could not open file: " << EC.message();
            return;
        }

        // 代码写入流中

        llvm::legacy::PassManager pass;
        auto FileType = llvm::TargetMachine::CGFT_ObjectFile;

        if (TheTargetMachine->addPassesToEmitFile(pass, dest, &dest, FileType)) {
            llvm::errs() << "TheTargetMachine can't emit a file of this type";
            return;
        }

        // 完成并清除流

        dest.flush();

    }
}