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

    llvm::Module *NewEmitter::Gen(ProjectDB &projectDB) {
        return Emit(projectDB.getTranslateUnit());
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

    /*
     * 声明主入口函数
     * int main(int argc, char **argv) ;
     */
    bool NewEmitter::DefineMainEntry() {

        std::vector<llvm::Type *> parameters_type = {Builder.getInt32Ty(), Builder.getInt8PtrTy()->getPointerTo()};
        llvm::FunctionType *main_fn_ty = llvm::FunctionType::get(Builder.getInt32Ty(), parameters_type, false);

        SysEntryFunc = llvm::Function::Create(main_fn_ty, llvm::Function::ExternalLinkage, "main", TheModule);
        (SysEntryFunc->arg_begin() + 0)->setName("argc");
        (SysEntryFunc->arg_begin() + 1)->setName("argv");
        SysEntryFunc->setDSOLocal(true);

        return true;
    }

    /*
     * 根据指定的类型和名称，创建全局变量
     */
    llvm::GlobalVariable *NewEmitter::CreateGlobalVariable(VariTypeDecl *type, const std::string &name) {
        llvm::Type *_vari_type = Emit(type);
        llvm::GlobalVariable *gvari = new llvm::GlobalVariable(
                /* Module */                    *TheModule,
                /* Type */                      _vari_type,
                /* isConstant */                false,
                /* Linkage */                   llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                /* Initializer */               nullptr,
                /* Name */                      name,
                /* InsertBefore */              nullptr,
                /* ThreadLocalMode */           llvm::GlobalVariable::ThreadLocalMode::NotThreadLocal,
                /* AddressSpace */              0,
                /* isExternallyInitialized */   false
        );
        gvari->setAlignment(4);
        return gvari;
    }

    template<typename RetTy, typename BaseTy>
    RetTy NewEmitter::EmitNavigate(BaseTy *node) {
        return RetTy{};
    }

    template<typename RetTy, typename BaseTy, typename AlternativeTy, typename ... AlternativesTy>
    RetTy NewEmitter::EmitNavigate(BaseTy *node) {
        static_assert(std::is_base_of<BaseTy, AlternativeTy>::value, "The alternative type is not a derived type of the base class.");
        if (AlternativeTy *p = rtti::dyn_cast<AlternativeTy>(node)) {
            return Emit(p);
        } else {
            return EmitNavigate<RetTy, BaseTy, AlternativesTy...>(node);
        }
    }

    llvm::Module *NewEmitter::impl_EmitTranslateUnit(TranslateUnit *TU) {
        RexDbgMgr.GetOrCreateDICompileUnit(TU->getFileName());
        DefineMainEntry();

        // 声明全局变量

        for (GlobalVariableDecl *gvari : TU->getGlobalVariableList()) {
            llvm::GlobalVariable *llvm_gvari = Emit(gvari);
            variable_map_[gvari] = llvm_gvari;
        }

        // 声明文件变量

        for (FileVariableDecl *fvari : TU->getFileVariableList()) {
            llvm::GlobalVariable *llvm_fvari = Emit(fvari);
            variable_map_[fvari] = llvm_fvari;
        }

        // 声明函数

        for (FunctorDecl *decl : TU->getFunctorList()) {
            llvm::FunctionType *func_ty = Emit(decl);
            functor_map_[decl] = func_ty;
        }

        // 定义函数

        for (FunctionDecl *func : TU->getFunctionList()) {
            llvm::Function *llvm_func = Emit(func);
            function_map_[func] = llvm_func;
        }

        DebInfoBuilder.finalize();

        // 检查所有函数

        for (auto &functor_object : function_map_) {
            llvm::Function *function = functor_object.second;
            if (llvm::verifyFunction(*function, &llvm::outs())) {
                llvm::outs() << "\n\n";
                TheModule->print(llvm::outs(), nullptr);
                assert(false);
                function->eraseFromParent();
            }
        }

        if (llvm::verifyModule(*TheModule)) {
            llvm::outs() << "\n\n";
            assert(false);
        }

        return TheModule;
    }

    llvm::GlobalVariable *NewEmitter::impl_EmitGlobalVariableDecl(GlobalVariableDecl *globalVariDecl) {
        llvm::GlobalVariable *gvari = CreateGlobalVariable(globalVariDecl->type(), globalVariDecl->getNameRef().str());
        return gvari;
    }

    llvm::GlobalVariable *NewEmitter::impl_EmitFileVariableDecl(FileVariableDecl *fileVariableDecl) {
        llvm::GlobalVariable *fvari = CreateGlobalVariable(fileVariableDecl->type(), fileVariableDecl->getMangling().str()); // 这里需要注意命名冲突问题
        return fvari;
    }

    llvm::Type *NewEmitter::impl_EmitVariTypeDecl(VariTypeDecl *type) {
        llvm::Type *ty = EmitNavigate<
                llvm::Type *
                , VariTypeDecl
                , BuiltinVoidType
                , BuiltinCommonType
                , BuiltinCharType
                , BuiltinIntegerType
                , BuiltinFloatType
                , BuiltinBoolType
                , BuiltinStringType
                , BuiltinDataSetType
                , BuiltinShortType
                , BuiltinLongType
                , BuiltinDatetimeType
                , BuiltinFuncPtrType
                , BuiltinDoubleType
                , ReferenceType
                , StructureDecl
                , ArrayType
                >(type);
        return ty;
    }

    llvm::Type *NewEmitter::impl_EmitBuiltinVoidType    (BuiltinVoidType     *builtinVoidType    ) {                return Builder.getVoidTy  ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinCommonType  (BuiltinCommonType   *builtinCommonType  ) { assert(false); return Builder.getInt64Ty ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinCharType    (BuiltinCharType     *builtinCharType    ) {                return Builder.getInt8Ty  ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinIntegerType (BuiltinIntegerType  *builtinIntegerType ) {                return Builder.getInt32Ty ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinFloatType   (BuiltinFloatType    *builtinFloatType   ) {                return Builder.getFloatTy ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinBoolType    (BuiltinBoolType     *builtinBoolType    ) {                return Builder.getInt1Ty  ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinStringType  (BuiltinStringType   *builtinStringType  ) { assert(false); return Builder.getInt64Ty ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinDataSetType (BuiltinDataSetType  *builtinDataSetType ) { assert(false); return Builder.getInt64Ty ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinShortType   (BuiltinShortType    *builtinShortType   ) {                return Builder.getInt16Ty ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinLongType    (BuiltinLongType     *builtinLongType    ) {                return Builder.getInt64Ty ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinDatetimeType(BuiltinDatetimeType *builtinDatetimeType) {                return Builder.getInt64Ty ()                ; }
    llvm::Type *NewEmitter::impl_EmitBuiltinFuncPtrType (BuiltinFuncPtrType  *builtinFuncPtrType ) {                return Builder.getVoidTy  ()->getPointerTo(); }
    llvm::Type *NewEmitter::impl_EmitBuiltinDoubleType  (BuiltinDoubleType   *builtinDoubleType  ) {                return Builder.getDoubleTy()                ; }
    llvm::Type *NewEmitter::impl_EmitStructureDecl      (StructureDecl       *structureDecl      ) { assert(false); return Builder.getInt64Ty ()                ; }
    llvm::Type *NewEmitter::impl_EmitArrayType          (ArrayType           *arrayType          ) { assert(false); return Builder.getInt64Ty ()                ; }

    llvm::Type *NewEmitter::impl_EmitReferenceType(ReferenceType *referenceType) {
        VariTypeDecl *vari_ty = rtti::dyn_cast<VariTypeDecl>(referenceType->getPointee());
        assert(vari_ty);
        return Emit(vari_ty)->getPointerTo();
    }

}
