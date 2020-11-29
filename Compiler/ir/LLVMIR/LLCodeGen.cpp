//
// Created by rex on 2020/3/20.
//

#include <iostream>

#include "LLCodeGen.h"
#include "EmitLLVMIR.h"

#include <llvm/IR/Module.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/LegacyPassManager.h>

namespace rexlang {

    LLCodeGen::LLCodeGen(EmitLLVMIR &llvmIREmitter) : emitter_(llvmIREmitter) {
    }

    int LLCodeGen::WriteOutBitCode(const std::string &bc_filename) {

        std::error_code EC;
        llvm::raw_fd_ostream bc_file(bc_filename, EC);
        llvm::WriteBitcodeToFile(*emitter_.GetModule(), bc_file);

        if (EC.value() != 0) {
            std::cerr << EC.message() << std::endl;
        }

        return EC.value();
    }

    int LLCodeGen::WriteOutObject(const std::string &obj_filename) {

        // 获得目标机器三元组

        auto TargetTriple = llvm::sys::getDefaultTargetTriple();

        std::string Error;
        auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

        if (!Target) {
            llvm::errs() << Error;
            assert(false);
            return 1;
        }

        // 目标机器设定

        auto CPU = "generic";
        auto Features = "";

        llvm::TargetOptions opt;
        auto RM = llvm::Optional<llvm::Reloc::Model>();
        auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

        // 指定模块的数据布局和目标机器，以便于优化代码

        llvm::Module *TheModule = emitter_.GetModule();
        TheModule->setDataLayout(TargetMachine->createDataLayout());
        TheModule->setTargetTriple(TargetTriple);

        // 定义文件流

        std::error_code EC;
        llvm::raw_fd_ostream dest(obj_filename, EC, llvm::sys::fs::F_None);

        if (EC) {
            llvm::errs() << "Could not open file: " << EC.message();
            return 1;
        }

        // 代码写入流中

        llvm::legacy::PassManager pass;
        llvm::TargetMachine::CodeGenFileType FileType = llvm::TargetMachine::CGFT_ObjectFile;

        if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
            llvm::errs() << "TheTargetMachine can't emit a file of this type";
            return 1;
        }

        pass.run(*TheModule);

        // 完成并清除流

        dest.flush();
        dest.close();

        return 0;
    }
}