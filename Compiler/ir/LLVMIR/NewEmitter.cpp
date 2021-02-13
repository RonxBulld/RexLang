//
// Created by Rexfield on 2021/2/12.
//

#include <iostream>
#include <filesystem>
#include <assert.h>

#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/CFG.h>

#include "NewEmitter.h"

//#include "LLVMRTIRBuilder.h"
#include "../../rexlang_compiler/NodeDecl.h"
#include "../../rexlang_compiler/ASTUtility.h"
#include "../../support/ProjectDB.h"
#include "../SimpleRTTI_ArguType.h"

namespace rexlang {

    NewEmitter::NewEmitter()
    : TheModule(new llvm::Module("a.ll", TheContext))
    , Builder(llvm::IRBuilder<>(TheContext))
    , DebInfoBuilder(*TheModule)
    , RexDbgMgr(Builder, DebInfoBuilder)
    {

        // 初始化发出目标代码的所有目标
        // TODO: 如需增加平台支持则修改此处

        LLVMInitializeX86TargetInfo();
        LLVMInitializeX86Target();
        LLVMInitializeX86TargetMC();
        LLVMInitializeX86AsmParser();
        LLVMInitializeX86AsmPrinter();

        // 设置目标三元组

        auto TargetTriple = llvm::sys::getDefaultTargetTriple();
        TheModule->setTargetTriple(TargetTriple);

        // 设置模块属性

        TheModule->addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);
        if (llvm::Triple(llvm::sys::getProcessTriple()).isOSDarwin()) {
            TheModule->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2);
        }
    }

    NewEmitter::~NewEmitter() {
        delete TheModule;
    }

    llvm::Module *NewEmitter::GetModule() const {
        return TheModule;
    }

    llvm::Module *NewEmitter::TakeModule() {
        llvm::Module *tmp = TheModule;
        TheModule = nullptr;
        return tmp;
    }

    int NewEmitter::OnEmitBegin(Node *astNode) {
        RexDbgMgr.OnEmitBegin(astNode);
        return 0;
    }

    int NewEmitter::OnEmitEnd(Node *astNode) {
        RexDbgMgr.OnEmitEnd(astNode);
        return 0;
    }

    bool NewEmitter::DefineMainEntryAndInitFunc() {

        // 声明主入口函数
        // int main(int argc, char **argv) ;

        std::vector<llvm::Type *> parameters_type = {Builder.getInt32Ty(), Builder.getInt8PtrTy()->getPointerTo()};
        llvm::FunctionType *main_fn_ty = llvm::FunctionType::get(Builder.getInt32Ty(), parameters_type, false);
        SysEntryFunc = llvm::Function::Create(main_fn_ty, llvm::Function::ExternalLinkage, "main", TheModule);
        (SysEntryFunc->arg_begin() + 0)->setName("argc");
        (SysEntryFunc->arg_begin() + 1)->setName("argv");
        SysEntryFunc->setDSOLocal(true);

        return true;
    }

    llvm::Module *NewEmitter::impl_EmitTranslateUnit(TranslateUnit *TU) {
        RexDbgMgr.GetOrCreateDICompileUnit(TU->getFileName());
        DefineMainEntryAndInitFunc();

        // 全局变量

        for (GlobalVariableDecl *gvari : TU->getGlobalVariableList()) {
            Emit(gvari);
        }

        // TODO: 文件变量
        // TODO: 函数声明
        // TODO: 函数定义


        DebInfoBuilder.finalize();

        // 检查所有函数

        for (auto &functor_object : functor_map_) {
            llvm::Function *function = functor_object.second;
            if (llvm::verifyFunction(*function, &llvm::outs())) {
                llvm::outs() << "\n\n";
                TheModule->print(llvm::outs(), nullptr);
                assert(false);
                function->eraseFromParent();
            }
        }

        return 0;
    }
}
