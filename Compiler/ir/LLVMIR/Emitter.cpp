//
// Created by Administrator on 2020/6/11.
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

#include "Emitter.h"

#include "LLVMRTIRBuilder.h"
#include "../../rexlang_compiler/NodeDecl.h"
#include "../../rexlang_compiler/ASTUtility.h"
#include "../../support/ProjectDB.h"
#include "../../rexlang_compiler/TypeAssert.h"
#include "../SimpleRTTI_ArguType.h"

namespace rexlang {

    IREmit::ControlableStructure::ControlableStructure(llvm::BasicBlock *headBB, llvm::BasicBlock *trueBB, llvm::BasicBlock *falseBB, llvm::BasicBlock *tailBB)
            : head_bb(headBB), true_bb(trueBB), false_bb(falseBB), tail_bb(tailBB) {
    }

    llvm::BasicBlock *  IREmit::ControlableStructure::getHeadBB ()                          const   { return head_bb;     }
    llvm::BasicBlock *  IREmit::ControlableStructure::getTrueBB ()                          const   { return true_bb;     }
    llvm::BasicBlock *  IREmit::ControlableStructure::getFalseBB()                          const   { return false_bb;    }
    llvm::BasicBlock *  IREmit::ControlableStructure::getTailBB ()                          const   { return tail_bb;     }
    void                IREmit::ControlableStructure::setHeadBB (llvm::BasicBlock *headBB)          { head_bb = headBB;   }
    void                IREmit::ControlableStructure::setTrueBb (llvm::BasicBlock *trueBB)          { true_bb = trueBB;   }
    void                IREmit::ControlableStructure::setFalseBb(llvm::BasicBlock *falseBB)         { false_bb = falseBB; }
    void                IREmit::ControlableStructure::setTailBB (llvm::BasicBlock *tailBB)          { tail_bb = tailBB;   }

    int IREmit::OnEmitBegin(Node *astNode) {
        RexDbgMgr.OnEmitBegin(astNode);
        return 0;
    }

    int IREmit::OnEmitEnd(Node *astNode) {
        RexDbgMgr.OnEmitEnd(astNode);
        return 0;
    }

    llvm::Type *IREmit::GetType(TypeDecl *typeDecl) {
        auto found = type_object_pool_.find(typeDecl);
        if (found != type_object_pool_.end()) {
            return found->second;
        } else {
            llvm::Type *type_obj = Emit(typeDecl);
            type_object_pool_[typeDecl] = type_obj;
            return type_obj;
        }
    }

    llvm::Function *IREmit::GetFunction(const std::string &function_name) {
        for (auto &functor_item : function_object_pool_) {
            if (functor_item.first->name_.string_.str() == function_name) {
                return functor_item.second;
            }
        }
        return nullptr;
    }

    void IREmit::RegistVariableIR(BaseVariDecl *variable, llvm::Value *variable_ir) {
        if (variable_object_pool_.find(variable) != variable_object_pool_.end()) {
            assert(false);
        }
        variable_object_pool_[variable] = variable_ir;
    }

    llvm::Value *IREmit::GetVariableIRIFExist(BaseVariDecl *variable) {
        auto ir_found = variable_object_pool_.find(variable);
        if (ir_found != variable_object_pool_.end()) {
            return ir_found->second;
        } else {
            return nullptr;
        }
    }

    bool IREmit::DefineMainEntryAndInitFunc() {

        // 声明初始化函数

        InitFunc = llvm::Function::Create(llvm::FunctionType::get(Builder.getVoidTy(), false), llvm::Function::InternalLinkage, "#init", TheModule);
        assert(InitFunc);
        llvm::BasicBlock::Create(TheContext, "entry", InitFunc);

        // 声明主入口函数

        std::vector<llvm::Type *> parameters_type = {Builder.getInt32Ty(), Builder.getInt8PtrTy()->getPointerTo()};
        llvm::FunctionType *main_fn_ty = llvm::FunctionType::get(Builder.getInt32Ty(), parameters_type, false);
        SysEntryFunc = llvm::Function::Create(main_fn_ty, llvm::Function::ExternalLinkage, "main", TheModule);
        (SysEntryFunc->arg_begin() + 0)->setName("argc");
        (SysEntryFunc->arg_begin() + 1)->setName("argv");
        SysEntryFunc->setDSOLocal(true);

        return true;
    }

    bool IREmit::CreateEntryAndInit(TranslateUnit *translateUnit, llvm::Function *userEntry) {

        // 入口块

        llvm::BasicBlock *entry_block = llvm::BasicBlock::Create(TheContext, "entry", SysEntryFunc);
        Builder.SetInsertPoint(entry_block);

        // 返回值空间

        llvm::AllocaInst *return_alloca = Builder.CreateAlloca(Builder.getInt32Ty(), nullptr, "$ret");

        // 参数空间

        llvm::AllocaInst *argc_alloca = Builder.CreateAlloca(SysEntryFunc->getFunctionType()->getParamType(0), nullptr, "$argc_alloca");
        llvm::AllocaInst *argv_alloca = Builder.CreateAlloca(SysEntryFunc->getFunctionType()->getParamType(1), nullptr, "$argv_alloca");
        llvm::Value *argc = Builder.CreateStore((SysEntryFunc->arg_begin() + 0), argc_alloca);
        llvm::Value *argv = Builder.CreateStore((SysEntryFunc->arg_begin() + 1), argv_alloca);

        // 初始化块

        llvm::BasicBlock *init_block = llvm::BasicBlock::Create(TheContext, "init_block", SysEntryFunc);
        Builder.CreateBr(init_block);
        Builder.SetInsertPoint(init_block);
        Builder.CreateCall(InitFunc);

        // 用户入口进入块

        llvm::BasicBlock *user_entry_block = llvm::BasicBlock::Create(TheContext, "call_user_func", SysEntryFunc);
        Builder.CreateBr(user_entry_block);
        Builder.SetInsertPoint(user_entry_block);
        llvm::CallInst *call_user_entry = Builder.CreateCall(userEntry);
        assert(call_user_entry);
        llvm::ReturnInst *ret_sys = Builder.CreateRet(call_user_entry);
        assert(ret_sys);

        return true;
    }

    llvm::BasicBlock *IREmit::CreateInitBlock(const std::string &blockName) {
        llvm::BasicBlock *pre_head = Builder.GetInsertBlock();

        auto &block_list = InitFunc->getBasicBlockList();
        llvm::BasicBlock *latest_init_block = &block_list.back();
        Builder.SetInsertPoint(latest_init_block);
        llvm::BasicBlock *init_bb = llvm::BasicBlock::Create(TheContext, blockName, InitFunc);
        Builder.CreateBr(init_bb);
        Builder.SetInsertPoint(pre_head);

        return init_bb;
    }

    bool IREmit::AddInitBlocks(llvm::BasicBlock *beginBlock, llvm::BasicBlock *endBlock) {
        /*llvm::BasicBlock *pre_head = Builder.GetInsertBlock();

        auto &block_list = InitFunc->getBasicBlockList();
        if (block_list.empty()) {

        } else {
            llvm::BasicBlock *latest_init_block = &block_list.back();
            Builder.SetInsertPoint(latest_init_block);
            Builder.CreateBr(beginBlock);
        }

        Builder.SetInsertPoint(pre_head);*/
        return true;
    }

    bool IREmit::FinishInitBlockInsert() {
        auto &block_list = InitFunc->getBasicBlockList();
        llvm::BasicBlock *latest_init_block = &block_list.back();
        Builder.SetInsertPoint(latest_init_block);
        Builder.CreateRetVoid();
        if (llvm::verifyFunction(*InitFunc, &llvm::outs())) {
            TheModule->print(llvm::outs(), nullptr);
            assert(false);
            return false;
        } else {
            return true;
        }
    }

    llvm::Type *IREmit::GetTrustType(llvm::Value *value) {
        if (llvm::GlobalVariable *global_variable = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
            return global_variable->getType()->getPointerElementType();
        } else if (llvm::AllocaInst *alloca_inst = llvm::dyn_cast<llvm::AllocaInst>(value)) {
            return alloca_inst->getType()->getPointerElementType();
        } else if (llvm::Argument *argument = llvm::dyn_cast<llvm::Argument>(value)) {
            return argument->getType();
        } else if (llvm::LoadInst *load_inst = llvm::dyn_cast<llvm::LoadInst>(value)) {
            return load_inst->getType();
        } else if (llvm::Constant *constant = llvm::dyn_cast<llvm::Constant>(value)) {
            return constant->getType();
        } else {
            return value->getType();
        }
    }

    llvm::Type *IREmit::GetParameterType(ParameterDecl *parameterDecl) {
        llvm::Type *param_type = GetType(parameterDecl->vari_type_decl_);
        if (parameterDecl->is_reference_ && !param_type->isPointerTy()) {
            param_type = param_type->getPointerTo();
        }
        return param_type;
    }

    llvm::Value *IREmit::LoadVariable(llvm::Value *variable) {
        if (llvm::GlobalVariable *global_variable = llvm::dyn_cast<llvm::GlobalVariable>(variable)) {
            return Builder.CreateLoad(global_variable->getValueType(), global_variable);

        } else if (llvm::AllocaInst *alloca_inst = llvm::dyn_cast<llvm::AllocaInst>(variable)) {
            return Builder.CreateLoad(alloca_inst->getAllocatedType(), alloca_inst);

        } else if (llvm::Argument *argument = llvm::dyn_cast<llvm::Argument>(variable)) {
            return argument;

        } else if (llvm::LoadInst *load_inst = llvm::dyn_cast<llvm::LoadInst>(variable)) {
            return load_inst;

        } else if (llvm::Constant *constant = llvm::dyn_cast<llvm::Constant>(variable)) {
            return constant;

        } else if (RTBuilder.isArrayType(variable->getType())) {
            return variable;

        } else if (RTBuilder.isStructureType(variable->getType())) {
            return variable;

        } else if (RTBuilder.isStringType(variable->getType())) {
            return variable;

        } else if (variable->getType()->isPointerTy()) {
            return Builder.CreateLoad(variable->getType()->getPointerElementType(), variable);

        } else {
            return variable;

        }
    }

    bool IREmit::StoreVariable(llvm::Value *value, llvm::Value *variable) {
        value = LoadVariable(value);
        if (llvm::GlobalVariable *global_variable = llvm::dyn_cast<llvm::GlobalVariable>(variable)) {
            Builder.CreateStore(value, global_variable);
            return true;
        } else if (llvm::AllocaInst *alloca_inst = llvm::dyn_cast<llvm::AllocaInst>(variable)) {
            Builder.CreateStore(value, alloca_inst);
            return true;
        } else if (GetTrustType(variable)->isPointerTy()) {
            Builder.CreateStore(value, variable);
            return true;
        } else {
            assert(false);
            return false;
        }
    }

    llvm::ConstantInt *IREmit::CreateInt(int intValue, unsigned int nBits, bool isSigned) {
        return llvm::ConstantInt::get(TheContext, llvm::APInt(nBits, intValue, isSigned));
    }

    bool IREmit::_EmitImpl_(TranslateUnit *translateUnit) {

        RexDbgMgr.GetOrCreateDICompileUnit(
                translateUnit->ast_context_->GetFileFromLocate(
                        translateUnit->location_start_).c_str()
                        );
        DefineMainEntryAndInitFunc();

        // 全局变量

        for (auto &global_vari_item : translateUnit->global_variables_) {
//            RexDbgMgr.GetOrCreateDICompileUnit(global_vari_item.second);
            llvm::GlobalVariable *gvari = Emit(global_vari_item.second);
            assert(gvari);
        }

        // 文件变量

        for (auto &file_item : translateUnit->source_file_) {
            if (ProgramSetFile *program_set_file = file_item->as<ProgramSetFile>()) {
//                RexDbgMgr.GetOrCreateDICompileUnit(program_set_file);
                for (auto &prog_vari_item : program_set_file->program_set_declares_->file_static_variables_) {
                    FileVariableDecl *file_variable_decl = prog_vari_item.second;
                    llvm::GlobalVariable *fvari = Emit(file_variable_decl);
                    assert(fvari);
                    RegistVariableIR(prog_vari_item.second, fvari);
                }
            }
        }

        // 函数声明

        for (auto &functor_decl_item : translateUnit->functor_declares_) {
//            RexDbgMgr.GetOrCreateDICompileUnit(functor_decl_item.second);
            llvm::Function *functor_decl = Emit(functor_decl_item.second);
        }

        // 函数定义

        for (auto &function_def_item : translateUnit->function_decls_) {
//            RexDbgMgr.GetOrCreateDICompileUnit(function_def_item.second);
            this->TheProgramSet = function_def_item.second->parent_node_->as<ProgSetDecl>();
            llvm::Function *function_def = Emit(function_def_item.second);
            this->TheProgramSet = nullptr;
        }

        llvm::Function *user_entry = function_object_pool_[translateUnit->main_entry_];
        assert(user_entry);
        CreateEntryAndInit(translateUnit, user_entry);

        FinishInitBlockInsert();
        DebInfoBuilder.finalize();

        // 检查所有函数

        for (auto &function_object : function_object_pool_) {
            llvm::Function *function = function_object.second;
            if (llvm::verifyFunction(*function, &llvm::outs())) {
                llvm::outs() << "\n\n";
                TheModule->print(llvm::outs(), nullptr);
                assert(false);
                function->eraseFromParent();
            }
        }

        return true;
    }

//        llvm::Value *IREmit::_EmitImpl_(SourceFile *sourceFile);
//        llvm::Value *IREmit::_EmitImpl_(ProgramSetFile *programSetFile);
//        llvm::Value *IREmit::_EmitImpl_(GlobalVariableFile *globalVariableFile);
//        llvm::Value *IREmit::_EmitImpl_(DataStructureFile *dataStructureFile);
//        llvm::Value *IREmit::_EmitImpl_(DllDefineFile *dllDefineFile);
//        llvm::Value *IREmit::_EmitImpl_(Decl *decl);
//        llvm::Value *IREmit::_EmitImpl_(TagDecl *tagDecl);
//        llvm::Value *IREmit::_EmitImpl_(VariableDecl *variableDecl);
//        llvm::Value *IREmit::_EmitImpl_(BaseVariDecl *baseVariDecl);

    void IREmit::CreateVariableInitialization(llvm::Value *variable) {
        if (llvm::GlobalVariable *gvari = llvm::dyn_cast<llvm::GlobalVariable>(variable)) {

            llvm::BasicBlock *pre_head = Builder.GetInsertBlock();

            llvm::BasicBlock *init_bb = CreateInitBlock();
            Builder.SetInsertPoint(init_bb);
            llvm::Value *init_val = RTBuilder.CreateInitializeValue(GetTrustType(gvari));
            StoreVariable(init_val, gvari);
            AddInitBlocks(init_bb, init_bb);

            Builder.SetInsertPoint(pre_head);

        } else if (llvm::AllocaInst *lvari = llvm::dyn_cast<llvm::AllocaInst>(variable)) {

            llvm::Value *init_val = RTBuilder.CreateInitializeValue(GetTrustType(lvari));
            StoreVariable(init_val, lvari);

        } else {
            assert(false);
        }
    }

    llvm::GlobalVariable *IREmit::CreateGlobalVariableAndInit(TypeDecl *vari_type, const std::string &vari_name) {
        llvm::Type *_vari_type = GetType(vari_type);
        llvm::GlobalVariable *gvari = new llvm::GlobalVariable(
                /* Module */                    *TheModule,
                /* Type */                      _vari_type,
                /* isConstant */                  false,
                /* Linkage */                   llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                /* Initializer */               nullptr,
                /* Name */                      vari_name,
                /* InsertBefore */              nullptr,
                /* ThreadLocalMode */           llvm::GlobalVariable::ThreadLocalMode::NotThreadLocal,
                /* AddressSpace */              0,
                /* isExternallyInitialized */   false
        );
        gvari->setAlignment(4);
        CreateVariableInitialization(gvari);
        return gvari;
    }

    llvm::GlobalVariable *IREmit::_EmitImpl_(GlobalVariableDecl *globalVariableDecl) {
        llvm::GlobalVariable *global_variable = CreateGlobalVariableAndInit(globalVariableDecl->vari_type_decl_, globalVariableDecl->name_.string_.str());
        RegistVariableIR(globalVariableDecl, global_variable);
        return global_variable;
    }

    llvm::Value *IREmit::_EmitImpl_(ParameterDecl *parameterDecl) {
        llvm::Type *param_type = GetParameterType(parameterDecl);

        // 创建参数在栈内的空间

        llvm::AllocaInst *alloca_param = Builder.CreateAlloca(param_type, nullptr, parameterDecl->name_.string_.str());
        RegistVariableIR(parameterDecl, alloca_param);

        // 将参数值加载到栈内存中

        llvm::Argument *argument = TheFunction->arg_begin() + parameterDecl->index_;
        StoreVariable(argument, alloca_param);

        return alloca_param;
    }

    llvm::GlobalVariable *IREmit::_EmitImpl_(FileVariableDecl *fileVariableDecl) {
        // 文件变量需要重命名以免名称冲突
        std::string vari_name = fileVariableDecl->name_.string_.str();
        vari_name = TheProgramSet->name_.string_.str() + "." + vari_name;

        llvm::GlobalVariable *file_vari = CreateGlobalVariableAndInit(fileVariableDecl->vari_type_decl_, vari_name);
        file_vari->setLinkage(llvm::GlobalValue::LinkageTypes::InternalLinkage);
        RegistVariableIR(fileVariableDecl, file_vari);
        return file_vari;
    }

    llvm::Value *IREmit::_EmitImpl_(LocalVariableDecl *localVariableDecl) {
        llvm::Type *vari_type = GetType(localVariableDecl->vari_type_decl_);
        std::string vari_name = localVariableDecl->name_.string_.str();
        if (!localVariableDecl->is_static_) {

            // 非静态变量在栈上创建

            llvm::AllocaInst *local_vari = Builder.CreateAlloca(vari_type, nullptr, vari_name);
            local_vari->setAlignment(4);
            CreateVariableInitialization(local_vari);
            RegistVariableIR(localVariableDecl, local_vari);
            return local_vari;

        } else {

            // 在静态变量前增加名字修饰以免冲突

            vari_name = TheASTFunction->super_set_->name_.string_.str() + "." + TheASTFunction->name_.string_.str() + "." + vari_name;
            llvm::GlobalVariable *static_vari = CreateGlobalVariableAndInit(localVariableDecl->vari_type_decl_, vari_name);
            static_vari->setLinkage(llvm::GlobalValue::LinkageTypes::InternalLinkage);
            RegistVariableIR(localVariableDecl, static_vari);
            return static_vari;

        }
    }

    llvm::Type *IREmit::_EmitImpl_(TypeDecl *typeDecl) {
        if (BuiltinTypeDecl *builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return Emit(builtin_type_decl);
        } else if (ArrayDecl *array_decl = typeDecl->as<ArrayDecl>()) {
            return Emit(array_decl);
        } else if (StructureDecl *structure_decl = typeDecl->as<StructureDecl>()) {
            return Emit(structure_decl);
        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::Type *IREmit::_EmitImpl_(BuiltinTypeDecl *builtinTypeDecl) {
        auto type_found = type_object_pool_.find(builtinTypeDecl);
        llvm::Type *type = nullptr;
        if (type_found != type_object_pool_.end()) {
            if ((type = type_found->second)) {
                return type;
            }
        }


             if (builtinTypeDecl->isVoidType()) { type = Builder.getVoidTy(); }
        else if (builtinTypeDecl->isCharType()) { type = Builder.getInt8Ty(); }
        else if (builtinTypeDecl->isIntegerType()) { type = Builder.getInt32Ty(); }
        else if (builtinTypeDecl->isFloatType()) { type = Builder.getFloatTy(); }
        else if (builtinTypeDecl->isBoolType()) { type = Builder.getInt1Ty(); }
        else if (builtinTypeDecl->isStringType()) { type = RTBuilder.getStringType(); } /*字符串对象指针*/
        else if (builtinTypeDecl->isDataSetType()) { type = RTBuilder.getStringType(); } /*字节集对象指针*/
        else if (builtinTypeDecl->isShortType()) { type = Builder.getInt16Ty(); }
        else if (builtinTypeDecl->isLongType()) { type = Builder.getInt64Ty(); }
        else if (builtinTypeDecl->isDatetimeType()) { type = Builder.getInt64Ty(); }
        else if (builtinTypeDecl->isDoubleType()) { type = Builder.getDoubleTy(); }
        else if (builtinTypeDecl->isFuncPtrType()) { type = Builder.getVoidTy()->getPointerTo(); }
        else { assert(false); return nullptr; }

        type_object_pool_[builtinTypeDecl] = type;
        return type;
    }

    llvm::PointerType *IREmit::_EmitImpl_(ArrayDecl *arrayDecl) {
        llvm::Type *element_type = GetType(arrayDecl->base_type_);
        return RTBuilder.CreateArrayType(element_type, arrayDecl->dimensions_);
    }

    llvm::PointerType *IREmit::_EmitImpl_(StructureDecl *structureDecl) {
        std::vector<llvm::Type *> members_type;
        for (auto &member_item : structureDecl->members_) {
            // TODO: 需要处理引用问题
            llvm::Type *member_type = GetType(member_item.second->type_decl_ptr_);
            members_type.emplace_back(member_type);
        }
        return RTBuilder.CreateStructureType(structureDecl->name_.string_.str(), members_type);
    }

    llvm::Function *IREmit::_EmitImpl_(FunctorDecl *functorDecl) {

        // 构建形参声明

        bool is_vari_arg = false;
        if (!functorDecl->parameters_.empty() && functorDecl->parameters_.back()->name_.string_.str() == "...") {
            is_vari_arg = true;
            functorDecl->parameters_.pop_back();
        }

        std::vector<llvm::Type *> parameter_types;
        for (ParameterDecl *parameter_decl : functorDecl->parameters_) {
            llvm::Type *parameter_type = GetParameterType(parameter_decl);
            parameter_types.push_back(parameter_type);
        }

        // 构建返回值类型

        llvm::Type *return_type = GetType(functorDecl->return_type_);

        // 构建函数原型

        llvm::FunctionType *function_type = llvm::FunctionType::get(return_type, parameter_types, is_vari_arg);
        std::string function_name = functorDecl->name_.string_.str();

        // TODO: 这里可能要重新处理，这种情况下只适合静态链接库，并且会导致和源程序冲突
        if (APICommandDecl *dll_command_decl = functorDecl->as<APICommandDecl>()) {
            function_name = dll_command_decl->api_name_.string_.str();
        } else {
            function_name = "_" + function_name;
        }

        // 构建函数声明

        llvm::Function *function = llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, function_name, TheModule);

        // 设置参数名

        unsigned idx = 0;
        for (auto &param : function->args()) {
            param.setName(functorDecl->parameters_[idx]->name_.string_.str());
            // 注册参数
//                RegistVariableIR(functorDecl->parameters_[idx], &param);
            idx++;
        }

        // 所有函数声明都添加到查找表中

        function_object_pool_[functorDecl] = function;
        return function;
    }

    llvm::Function *IREmit::_EmitImpl_(FunctionDecl *functionDecl) {
        std::string function_name = functionDecl->name_.string_.str();
        std::cout << functionDecl->ast_context_->GetFileFromLocate(functionDecl->location_start_).str() << ":"
                  << functionDecl->ast_context_->GetLineFromLocate(functionDecl->location_start_) << ":"
                  << functionDecl->ast_context_->GetColumnFromLocate(functionDecl->location_start_) << " ";

        std::cout << "生成函数：" << function_name << std::endl;
        llvm::Function *function = function_object_pool_[functionDecl];
        if (!function) {
            function = Emit(functionDecl->as<FunctorDecl>());
            assert(function);
        }

        if (!function->empty()) {
            // 函数重定义
            assert(false);
            return nullptr;
        }
        this->TheFunction = function;
        this->TheASTFunction = functionDecl;
        llvm::DISubprogram *subprogram_di = RexDbgMgr.CreateFunctionDI(functionDecl, function);
        function->setSubprogram(subprogram_di);
        RexDbgMgr.PushLexicalScope(subprogram_di);

        // 开始创建函数体

        llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(TheContext, "entry", function);
        Builder.SetInsertPoint(basic_block);

        // 创建返回值栈空间

        llvm::BasicBlock *ret_bb = llvm::BasicBlock::Create(TheContext, "return", function);
        function_retbb_map_[function] = ret_bb;
        llvm::Value *return_value_ptr = nullptr;
        if (!functionDecl->return_type_->IsVoidType()) {
            llvm::Type *ret_type = GetType(functionDecl->return_type_);
            return_value_ptr = Builder.CreateAlloca(ret_type, nullptr, "ret");
        }
        function_retptr_map_[function] = return_value_ptr;

        // 创建参数变量

        for (ParameterDecl *param_vari_item : functionDecl->parameters_) {
            Emit(param_vari_item);
        }

        // 创建局部变量

        for (auto &local_vari_item : functionDecl->local_vari_) {
            Emit(local_vari_item.second);
        }

        // 处理语句

        llvm::BasicBlock *latest_block = Emit(functionDecl->statement_list_);

        // 插入真实返回语句

        for (llvm::BasicBlock &bb : function->getBasicBlockList()) {
            if (llvm::succ_size(&bb) == 0 && &bb != ret_bb) {
                Builder.SetInsertPoint(&bb);
                Builder.CreateBr(ret_bb);
            }
        }
//        if (llvm::succ_size(&function->getEntryBlock()) == 0) {
//            Builder.SetInsertPoint(&function->getEntryBlock());
//            Builder.CreateBr(ret_bb);
//        }
        Builder.SetInsertPoint(ret_bb);
        if (!functionDecl->return_type_->IsVoidType()) {
            llvm::Value *return_value = Builder.CreateLoad(return_value_ptr);
            Builder.CreateRet(return_value);
        } else {
            Builder.CreateRetVoid();
        }

        DebInfoBuilder.finalizeSubprogram(subprogram_di);

        this->TheFunction = nullptr;
        this->TheASTFunction = nullptr;
        RexDbgMgr.PopLexicalScope();
        return function;
    }

//        llvm::Function *Emit(DllCommandDecl *dllCommandDecl)；

    llvm::BasicBlock *IREmit::_EmitImpl_(Statement *statement) {
        if (AssignStmt *assign_stmt = statement->as<AssignStmt>()) {
            return Emit(assign_stmt);
        } else if (ControlStmt *control_stmt = statement->as<ControlStmt>()) {
            return Emit(control_stmt);
        } else if (IfStmt *if_stmt = statement->as<IfStmt>()) {
            return Emit(if_stmt);
        } else if (LoopStatement *loop_statement = statement->as<LoopStatement>()) {
            return Emit(loop_statement);
        } else if (StatementBlock *statement_block = statement->as<StatementBlock>()) {
            return Emit(statement_block);
        } else if (Expression *expression = statement->as<Expression>()) {
            return ((bool) Emit(expression)) ? Builder.GetInsertBlock() : nullptr;
        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(IfStmt *ifStmt) {
        assert(ifStmt->switches_.size() == 1);

        llvm::BasicBlock *prehead_block = Builder.GetInsertBlock();
        Expression *condition_expr = ifStmt->switches_.front().first;
        assert(condition_expr);
        Statement *then_stmt = ifStmt->switches_.front().second;
        Statement *else_stmt = ifStmt->default_statement_;

        // 生成判断条件
        llvm::Value *condition = Emit(condition_expr);
        assert(condition);
        assert(GetTrustType(condition)->getPrimitiveSizeInBits() == 1);

        // THEN块
        llvm::BasicBlock *then_block = llvm::BasicBlock::Create(TheContext, ".then", TheFunction);
        // ELSE块
        llvm::BasicBlock *else_block = llvm::BasicBlock::Create(TheContext, ".else", TheFunction);
        // 汇合块
        llvm::BasicBlock *merge_block = llvm::BasicBlock::Create(TheContext, ".merge", TheFunction);

        // 分支选择跳转
        Builder.CreateCondBr(condition, then_block, else_block);

        // 生成Then块
        Builder.SetInsertPoint(then_block);
        then_block = Emit(then_stmt);           // <---- 必须更新块指针
        if (llvm::succ_size(then_block) == 0) {
            Builder.SetInsertPoint(then_block);
            Builder.CreateBr(merge_block);
        }

        // 处理Else块
        Builder.SetInsertPoint(else_block);
        else_block = Emit(else_stmt);           // <---- 必须更新块指针
        if (llvm::succ_size(else_block) == 0) {
            Builder.SetInsertPoint(else_block);
            Builder.CreateBr(merge_block);
        }

        // 处理Merge块
        Builder.SetInsertPoint(merge_block);

        return merge_block;
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(StatementBlock *statementBlock) {
        llvm::BasicBlock *latest_block = Builder.GetInsertBlock();
        for (Statement *statement : statementBlock->statements_) {
            latest_block = Emit(statement);
            assert(latest_block);
        }
        return latest_block;
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(LoopStatement *loopStatement) {
        llvm::BasicBlock *latest_block = Builder.GetInsertBlock();
        if (WhileStmt *whileStmt = loopStatement->as<WhileStmt>()) {
            latest_block = Emit(whileStmt);
        } else if (RangeForStmt *rangeForStmt = loopStatement->as<RangeForStmt>()) {
            latest_block = Emit(rangeForStmt);
        } else if (ForStmt *forStmt = loopStatement->as<ForStmt>()) {
            latest_block = Emit(forStmt);
        } else if (DoWhileStmt *doWhileStmt = loopStatement->as<DoWhileStmt>()) {
            latest_block = Emit(doWhileStmt);
        } else {
            assert(false);
        }
        assert(latest_block);
        return latest_block;
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(WhileStmt *whileStmt) {
        // 当前块
        llvm::BasicBlock *preheader_block = Builder.GetInsertBlock();
        // 循环条件块
        llvm::BasicBlock *condition_block = llvm::BasicBlock::Create(TheContext, ".condition", TheFunction);
        Builder.CreateBr(condition_block);
        Builder.SetInsertPoint(condition_block);
        // 循环体块
        llvm::BasicBlock *loop_block = llvm::BasicBlock::Create(TheContext, ".loop", TheFunction);
        // 循环块下一块
        llvm::BasicBlock *after_block = llvm::BasicBlock::Create(TheContext, ".afterloop", TheFunction);
        // 循环条件
        llvm::Value *loop_condition = Emit(whileStmt->condition_);
        Builder.CreateCondBr(loop_condition, loop_block, after_block);

        controlable_struct_stack_.push({condition_block, loop_block, after_block, after_block});
        // 开始生成循环体
        Builder.SetInsertPoint(loop_block);
        loop_block = Emit(whileStmt->loop_body_);       // <---- 必须更新块指针
        controlable_struct_stack_.pop();

        // 直接跳到循环条件块
        Builder.CreateBr(condition_block);
        // 转到新的块中
        Builder.SetInsertPoint(after_block);
        return after_block;
    }

    llvm::BasicBlock *IREmit::BuildConditionFirstLoop(llvm::Value *startValue, llvm::Value *stopValue, llvm::Value *stepValue, llvm::Value *loopVari, Statement *loopBody) {
        // 当前块
        llvm::BasicBlock *prehead_block = Builder.GetInsertBlock();
        // 真实循环变量
        llvm::Value *real_loop_vari = Builder.CreateAlloca(llvm::Type::getInt32Ty(TheContext), nullptr, "$.real_loop_vari");

        // 判断循环是否有效
        // Valid = ((stop - start) * step) > 0
        llvm::Value *range_distance = Builder.CreateSub(stopValue, startValue, "$.distance");
        llvm::Value *loop_valid = Builder.CreateICmpSGT(Builder.CreateMul(range_distance, stepValue), CreateInt(0), "$.valid");

        llvm::BasicBlock *loop_entry_block = llvm::BasicBlock::Create(TheContext, ".loop_entry", TheFunction);
        Builder.SetInsertPoint(loop_entry_block);
        // 计算K值 K=(S>-S)*2-1
        llvm::Value *step_gtz = Builder.CreateICmpSGT(stepValue, Builder.CreateNeg(stepValue));
        step_gtz = Builder.CreateIntCast(step_gtz, llvm::Type::getInt32Ty(TheContext), false, "$.cast_i1_to_i32");
        llvm::Value *K = Builder.CreateSub(Builder.CreateMul(step_gtz, CreateInt(2)), CreateInt(1), "$.K");
        // 设置初始值
        Builder.CreateAlignedStore(startValue, real_loop_vari, 4);

        // === 计算循环条件并选择分支 ===
        // 循环判断块
        llvm::BasicBlock *loop_cond_block = llvm::BasicBlock::Create(TheContext, ".loop_cond", TheFunction);
        Builder.CreateBr(loop_cond_block);
        Builder.SetInsertPoint(loop_cond_block);
        // 循环条件值 (K*i)<=(K*stop)
        llvm::Value *loop_val = Builder.CreateAlignedLoad(llvm::Type::getInt32Ty(TheContext), real_loop_vari, 4);
        llvm::Value *loop_cv = Builder.CreateICmpSLE(Builder.CreateMul(K, loop_val), Builder.CreateMul(K, stopValue));
        // 循环体块
        llvm::BasicBlock *loop_body_block = llvm::BasicBlock::Create(TheContext, ".loop_body", TheFunction);
        // 循环步进块
        llvm::BasicBlock *step_block = llvm::BasicBlock::Create(TheContext, ".loop_step", TheFunction);
        // 循环后块
        llvm::BasicBlock *loop_after_block = llvm::BasicBlock::Create(TheContext, ".after_loop", TheFunction);
        // 插入循环判断分支跳转
        Builder.CreateCondBr(loop_cv, loop_body_block, loop_after_block);

        controlable_struct_stack_.push({loop_cond_block, loop_body_block, loop_after_block, loop_after_block});
        // === 开始为循环体生成代码 ===
        Builder.SetInsertPoint(loop_body_block);
        if (loopVari) {
            // 更新循环值到名义循环变量
            Builder.CreateAlignedStore(Builder.CreateAlignedLoad(llvm::Type::getInt32Ty(TheContext), real_loop_vari, 4), loopVari, 4);
        }
        loop_body_block = Emit(loopBody);       // <---- 必须更新块指针
        Builder.CreateBr(step_block);
        controlable_struct_stack_.pop();

        // === 开始处理步进 ===
        Builder.SetInsertPoint(step_block);
        // 计算步进后的值
        llvm::Value *next_var = Builder.CreateAdd(Builder.CreateAlignedLoad(llvm::Type::getInt32Ty(TheContext), real_loop_vari, 4), stepValue, "next_var");
        Builder.CreateAlignedStore(next_var, real_loop_vari, 4);
        // 跳转到头部
        Builder.CreateBr(loop_cond_block);
        // 回写循环有效判断
        Builder.SetInsertPoint(prehead_block);
        Builder.CreateCondBr(loop_valid, loop_entry_block, loop_after_block);

        // 转到新的块中
        Builder.SetInsertPoint(loop_after_block);

        return loop_after_block;
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(RangeForStmt *rangeForStmt) {
        llvm::Value *start_value = CreateInt(1);
        llvm::Value *stop_value = Emit(rangeForStmt->range_size_);
        assert(stop_value);
        llvm::Value *step_value = CreateInt(1);
        llvm::Value *loop_vari = nullptr;
        if (rangeForStmt->loop_vari_) {
            loop_vari = Emit(rangeForStmt->loop_vari_);
            assert(loop_vari);
        }
        llvm::BasicBlock *loop_after_block = BuildConditionFirstLoop(start_value, stop_value, step_value, loop_vari, rangeForStmt->loop_body_);
        assert(loop_after_block);
        return loop_after_block;
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(ForStmt *forStmt) {
        // 初始值
        llvm::Value *start_value = Emit(forStmt->start_value_);
        assert(start_value);
        // 结束值
        llvm::Value *stop_value = Emit(forStmt->stop_value_);
        assert(stop_value);
        // 步进值
        llvm::Value *step_value = Emit(forStmt->step_value_);
        assert(step_value);
        // 循环变量
        llvm::Value *loop_vari = nullptr;
        if (forStmt->loop_vari_) {
            loop_vari = Emit(forStmt->loop_vari_);
            assert(loop_vari);
        }
        llvm::BasicBlock *loop_after_block = BuildConditionFirstLoop(start_value, stop_value, step_value, loop_vari, forStmt->loop_body_);
        assert(loop_after_block);
        return loop_after_block;
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(DoWhileStmt *doWhileStmt) {
        // 当前块
        llvm::BasicBlock *preheader_block = Builder.GetInsertBlock();
        // 循环体前导块
        llvm::BasicBlock *prev_loop_block = llvm::BasicBlock::Create(TheContext, ".prev_loop", TheFunction);
        Builder.CreateBr(prev_loop_block);
        Builder.SetInsertPoint(prev_loop_block);
        // 循环体块
        llvm::BasicBlock *loop_block = llvm::BasicBlock::Create(TheContext, ".loop", TheFunction);
        Builder.CreateBr(loop_block);
        // 条件判定块
        llvm::BasicBlock *cond_block = llvm::BasicBlock::Create(TheContext, ".cond", TheFunction);
        // 循环块下一个块
        llvm::BasicBlock *after_block = llvm::BasicBlock::Create(TheContext, ".afterloop", TheFunction);

        controlable_struct_stack_.push({cond_block, prev_loop_block, after_block, after_block});
        Builder.SetInsertPoint(loop_block);
        // 循环体
        loop_block = Emit(doWhileStmt->loop_body_);     // <---- 必须更新块指针
        controlable_struct_stack_.pop();
        Builder.CreateBr(cond_block);

        Builder.SetInsertPoint(cond_block);
        // 条件判定，分支选择跳转
        llvm::Value *loop_condition = Emit(doWhileStmt->conditon_);
        Builder.CreateCondBr(loop_condition, prev_loop_block, after_block);
        // 转到新的块中
        Builder.SetInsertPoint(after_block);
        return after_block;
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(AssignStmt *assignStmt) {
        llvm::Value *rhs = Emit(assignStmt->rhs_);
        assert(rhs);
        llvm::Value *lhs = Emit(assignStmt->lhs_);
        assert(lhs);
        llvm::Type *lhs_type = GetTrustType(lhs);

        // 区分数组、字节集、字符串、结构体和其它类型

        llvm::Type *rhs_type = GetTrustType(rhs);
        assert(rhs);
        if (rhs_type->isPointerTy()) {
            if (RTBuilder.isArrayType(rhs_type)) {
                rhs = RTBuilder.CloneArray(rhs);

            } else if (RTBuilder.isStructureType(rhs_type)) {
                rhs = RTBuilder.CloneStructure(rhs);

            } else if (RTBuilder.isStringType(rhs_type)) {
                rhs = RTBuilder.CloneString(rhs);

            } else {
                assert(false);
                rhs = nullptr;
            }
            assert(rhs);
            assert(GetTrustType(rhs)->isPointerTy());
        }

        bool assign_success = StoreVariable(rhs, lhs);
        assert(assign_success);
        return Builder.GetInsertBlock();
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(ControlStmt *controlStmt) {
        if (LoopControlStmt *loopControlStmt = controlStmt->as<LoopControlStmt>()) {
            return Emit(loopControlStmt);
        } else if (ReturnStmt *returnStmt = controlStmt->as<ReturnStmt>()) {
            return Emit(returnStmt);
        } else if (ExitStmt *exitStmt = controlStmt->as<ExitStmt>()) {
            return Emit(exitStmt);
        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(LoopControlStmt *loopControlStmt) {
        if (ContinueStmt *continueStmt = loopControlStmt->as<ContinueStmt>()) {
            return Emit(continueStmt);
        } else if (BreakStmt *breakStmt = loopControlStmt->as<BreakStmt>()) {
            return Emit(breakStmt);
        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(ContinueStmt *continueStmt) {
        if (controlable_struct_stack_.empty()) {
            assert(false);
            return nullptr;
        }
        if (llvm::BasicBlock *head_block = controlable_struct_stack_.top().getHeadBB()) {
            Builder.CreateBr(head_block);
            return nullptr;
        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(BreakStmt *breakStmt) {
        if (controlable_struct_stack_.empty()) {
            assert(false);
            return nullptr;
        }
        if (llvm::BasicBlock *head_block = controlable_struct_stack_.top().getTailBB()) {
            Builder.CreateBr(head_block);
            return nullptr;
        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(ReturnStmt *returnStmt) {
        if (returnStmt->return_value_) {
            llvm::Value *RV = Emit(returnStmt->return_value_);
            Builder.CreateStore(RV, function_retptr_map_[this->TheFunction]);
            Builder.CreateBr(function_retbb_map_[this->TheFunction]);
        } else {
            Builder.CreateBr(function_retbb_map_[this->TheFunction]);
        }
        return Builder.GetInsertBlock();
    }

    llvm::BasicBlock *IREmit::_EmitImpl_(ExitStmt *exitStmt) {
        llvm::FunctionCallee exit_fn = RTBuilder.getRTAPIFunction("$exit", Builder.getVoidTy(), {});
        Builder.CreateCall(exit_fn);
        return Builder.GetInsertBlock();
    }

    llvm::Value *IREmit::_EmitImpl_(Expression *expression) {
        if (HierarchyIdentifier *hierarchy_identifier = expression->as<HierarchyIdentifier>()) {
            return Emit(hierarchy_identifier);
        } else if (NameComponent *name_component = expression->as<NameComponent>()) {
            return Emit(name_component);
        } else if (TypeConvert *type_convert = expression->as<TypeConvert>()) {
            return Emit(type_convert);
        } else if (UnaryExpression *unary_expression = expression->as<UnaryExpression>()) {
            return Emit(unary_expression);
        } else if (BinaryExpression *binary_expression = expression->as<BinaryExpression>()) {
            return Emit(binary_expression);
        } else if (Value *value = expression->as<Value>()) {
            return Emit(value);
        } else if (FuncAddrExpression *func_addr_expression = expression->as<FuncAddrExpression>()) {
            return Emit(func_addr_expression);
        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::Value *IREmit::_EmitImpl_(TypeConvert *typeConvert) {

        // TODO: 只处理了作为右值的情况

        llvm::Value *expr = Emit(typeConvert->from_expression_);
        llvm::Type *target_type = Emit(typeConvert->target_type_);
        llvm::Type *source_type = GetTrustType(expr);
        // 指针到指针
        if (target_type->isPointerTy() && source_type->isPointerTy()) {
            return Builder.CreatePointerCast(expr, target_type);
        }
            // 指针到整数
        else if (target_type->isIntegerTy() && source_type->isPointerTy()) {
            return Builder.CreatePtrToInt(expr, target_type);
        }
            // 整数到指针
        else if (target_type->isPointerTy() && source_type->isIntegerTy()) {
            return Builder.CreateIntToPtr(expr, target_type);
        }
            // 整数到浮点
        else if ((target_type->isFloatTy() || target_type->isDoubleTy()) && source_type->isIntegerTy()) {
            return Builder.CreateSIToFP(expr, target_type);
        }
            // 浮点到整数
        else if (target_type->isIntegerTy() && (source_type->isFloatTy() || source_type->isDoubleTy())) {
            return Builder.CreateFPToSI(expr, target_type);
        }
            // 整数到整数不同位宽
        else if (target_type->isIntegerTy() && source_type->isIntegerTy()) {
            return Builder.CreateSExt(expr, target_type);
        } else {
            assert(false);
            return nullptr;
        }
    }

    /*
     * 从结构体或者对象池中获得变量引用或者函数引用
     */
    llvm::Value *IREmit::GetFromStructOrPool(llvm::Value *forwardInstance, NameComponent *nameComponent) {

        llvm::Value *ref = nullptr;

        // 目标类型是单名称组件

        if (Identifier *identifier = nameComponent->as<Identifier>()) {
            if (forwardInstance) {

                // 作为成员解析

                MemberVariableDecl *member_variable_decl = identifier->reference_->as<MemberVariableDecl>();
                assert(member_variable_decl);
                ref = Builder.CreateStructGEP(forwardInstance, member_variable_decl->index_of_struct_);

            } else {

                // 作为普通变量或者函数名解析

                if (llvm::Value *variable = GetVariableIRIFExist(identifier->reference_)) {
                    assert(variable);
                    ref = variable;
                } else if (llvm::Function *function = function_object_pool_[identifier->function_ref_]) {
                    assert(function);
                    ref = function;
                } else {
                    assert(false);
                    return nullptr;
                }

            }

        }

            // 目标类型是数组索引

        else if (ArrayIndex *array_index = nameComponent->as<ArrayIndex>()) {

            // 取索引列表

            ErrOr<std::vector<Expression *>> indexes = ASTUtility::GetArrayIndexIndexList(array_index);
            if (indexes.HadError()) {
                assert(false);
                return nullptr;
            }

            // 取数组指针

            NameComponent *base = ASTUtility::GetArrayIndexBase(array_index);
            llvm::Value *arr_ptr_variable = GetFromStructOrPool(forwardInstance, base);
            assert(arr_ptr_variable);

            // 取索引列表

            std::vector<llvm::Value *> indexes_ir;
            for (Expression *index : indexes.Value()) {
                llvm::Value *index_ir = Emit(index);
                assert(index_ir);
                indexes_ir.push_back(index_ir);
            }

            // 取元素指针

            ref = RTBuilder.GetArrayElementPointer(arr_ptr_variable, indexes_ir);

        }

            // 目标类型是函数调用

        else if (FunctionCall *function_call = nameComponent->as<FunctionCall>()) {

            // 获取调用目标-计算实参-调用

            llvm::Function *func_ptr = llvm::dyn_cast<llvm::Function>(GetFromStructOrPool(forwardInstance, function_call->function_name_));
            assert(func_ptr);
            std::vector<llvm::Value *> arguments_ir = EmitArgumentList(function_call);
            ref = Builder.CreateCall(func_ptr, arguments_ir);

        } else {
            assert(false);
            return nullptr;
        }

        assert(nameComponent->identifier_usage_ != ExprUsage::kUnknown);
        if (nameComponent->identifier_usage_ == ExprUsage::kAsRightValue) {
            ref = LoadVariable(ref);
        }

        return ref;
    }

    std::vector<llvm::Value *> IREmit::EmitArgumentList(FunctionCall *functionCall) {

        // TODO: 处理引用属性和可空属性

        std::vector<llvm::Value *> arguments_ir;
        for (Expression *argument : functionCall->arguments_) {
            llvm::Value *argument_ir = Emit(argument);
            assert(argument_ir);
            arguments_ir.push_back(argument_ir);
        }

        assert(functionCall->functor_declare_);
        FunctorDecl *prototype = functionCall->functor_declare_;

        // 处理不同的参数打包方式

        if (APICommandDecl *api_command_decl = prototype->as<APICommandDecl>()) {

            ArgumentPassModel argument_pass_model = api_command_decl->argument_pass_model_;
            llvm::Value *argu_n = CreateInt(arguments_ir.size());

            if (argument_pass_model == ArgumentPassModel::kSimpleRTTIPack) {

                // 准备信息

                llvm::StructType *arg_pack_ty = llvm::StructType::get(Builder.getInt8Ty(), Builder.getInt64Ty());
                llvm::Value *arg_pack_list_ptr = Builder.CreateAlloca(arg_pack_ty, argu_n);

                // 打包参数

                for (size_t idx = 0; idx < arguments_ir.size(); ++idx) {
                    llvm::Value *argu_ir = arguments_ir[idx];
                    llvm::Value *arg_pack_ptr = Builder.CreateGEP(arg_pack_ty, arg_pack_list_ptr, CreateInt(idx));
                    llvm::Value *arg_pack_0_ptr = Builder.CreateStructGEP(arg_pack_ptr, 0);
                    llvm::Value *arg_pack_1_ptr = Builder.CreateStructGEP(arg_pack_ptr, 1);

                    // 写入类型

                    char ty = RTBuilder.GetValueRTTIType(argu_ir);
                    StoreVariable(CreateInt(ty, 8), arg_pack_0_ptr);

                    // 写入值

                    llvm::Value *write_val = nullptr;
                    if (argu_ir->getType()->isIntegerTy()) {
                        write_val = Builder.CreateIntCast(argu_ir, Builder.getInt64Ty(), true);
                    } else if (argu_ir->getType()->isFloatTy()) {
                        write_val = Builder.CreateFPCast(argu_ir, Builder.getInt64Ty());
                    } else if (argu_ir->getType()->isPointerTy()) {
                        write_val = Builder.CreatePtrToInt(argu_ir, Builder.getInt64Ty());
                    } else {
                        assert(false);
                    }
                    StoreVariable(write_val, arg_pack_1_ptr);
                }
                arguments_ir.clear();
                arguments_ir.emplace_back(argu_n);
                arguments_ir.emplace_back(arg_pack_list_ptr);
            }
        }

        return arguments_ir;
    }

    llvm::Value *IREmit::_EmitImpl_(HierarchyIdentifier *hierarchyIdentifier) {
        return Emit(hierarchyIdentifier->name_components_.back());
    }

    llvm::Value *IREmit::_EmitImpl_(NameComponent *nameComponent) {
        llvm::Value *previous_value = nullptr;
        if (nameComponent->Forward()) {
            previous_value = Emit(nameComponent->Forward());
        }
        llvm::Value *this_value = GetFromStructOrPool(previous_value, nameComponent);

        if (nameComponent->identifier_usage_ == ExprUsage::kAsRightValue) {
//            std::cout << nameComponent->ast_context_->GetLineFromLocate(nameComponent->location_start_) << std::endl;
            // 将名称组件当右值使用
            this_value = LoadVariable(this_value);
        } else if (nameComponent->identifier_usage_ == ExprUsage::kAsLeftValue) {
            // 将名称组件当左值使用
        }
        // 如果是一个引用参数则需要加载它实际的内存地址
        if (Identifier *identifier = nameComponent->as<Identifier>()) {
            if (ParameterDecl *parameter_decl = identifier->reference_->as<ParameterDecl>()) {
                if (parameter_decl->is_reference_) {
                    this_value = Builder.CreateLoad(this_value->getType()->getPointerElementType(), this_value);
                }
            }
        }
        return this_value;
    }

    llvm::Value *IREmit::_EmitImpl_(UnaryExpression *unaryExpression) {
        llvm::Value *V = Emit(unaryExpression->operand_value_);
        if (!V) {
            assert(false);
            return nullptr;
        }
        switch (unaryExpression->operator_type_) {
            case OperatorType::kOptSub: {
                return Builder.CreateNeg(V, ".neg");
            }
            default: {
                assert(false);
                return nullptr;
            }
        }
    }

    llvm::Value *IREmit::_EmitImpl_(BinaryExpression *binaryExpression) {
        llvm::Value *L = Emit(binaryExpression->lhs_);
        llvm::Value *R = Emit(binaryExpression->rhs_);
        if (!L || !R) {
            assert(false);
            return nullptr;
        }

        assert(GetTrustType(L) == GetTrustType(R));
        llvm::Type *opt_type = GetTrustType(L);

        switch (binaryExpression->operator_type_) {
            // *** 运算系列 ***
            case OperatorType::kOptAdd: {

                // 支持整数、浮点、字符串、字节集

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateAdd(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFAdd(L, R);
                } else if (RTBuilder.isStringType(opt_type)) {
                    return RTBuilder.StringConnect(L, R);
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptSub: {

                // 支持整数、浮点

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateSub(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFSub(L, R);
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptMul: {

                // 支持整数、浮点

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateMul(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFMul(L, R);
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptDiv: {

                // 支持整数、浮点

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateSDiv(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFDiv(L, R);
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptFullDiv: {

                // 支持整数、浮点

                llvm::Value *div_res = nullptr;
                if (opt_type->isIntegerTy()) {
                    div_res = Builder.CreateSDiv(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    div_res = Builder.CreateFDiv(L, R);
                } else {
                    assert(false);
                    return nullptr;
                }
                return Builder.CreateFPToSI(div_res, Builder.getInt64Ty());
            }
            case OperatorType::kOptMod: {

                // 支持整数、浮点

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateSRem(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFRem(L, R);
                } else {
                    assert(false);
                    return nullptr;
                }
            }
                // *** 比较系列 ***
            case OperatorType::kOptEqual: {

                // 支持整数、浮点、字符串、字节集

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateICmpEQ(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFCmpOEQ(L, R);     // 这里用有序比较
                } else if (RTBuilder.isStringType(opt_type)) {
                    // StrCmp(L,R)=0
                    return Builder.CreateICmpEQ(RTBuilder.StringCompare(L, R), CreateInt(0));
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptNotEqual: {

                // 支持整数、浮点、字符串、字节集

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateICmpNE(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFCmpONE(L, R);     // 这里用有序比较
                } else if (RTBuilder.isStringType(opt_type)) {
                    // StrCmp(L,R)!=0
                    return Builder.CreateICmpNE(RTBuilder.StringCompare(L, R), CreateInt(0));
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptGreatThan: {

                // 支持整数、浮点、字符串、字节集

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateICmpSGT(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFCmpOGT(L, R);     // 这里用有序比较
                } else if (RTBuilder.isStringType(opt_type)) {
                    // StrCmp(L,R)>0
                    return Builder.CreateICmpSGT(RTBuilder.StringCompare(L, R), CreateInt(0));
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptLessThan: {

                // 支持整数、浮点、字符串、字节集

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateICmpSLT(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFCmpOLT(L, R);     // 这里用有序比较
                } else if (RTBuilder.isStringType(opt_type)) {
                    // StrCmp(L,R)<0
                    return Builder.CreateICmpSLT(RTBuilder.StringCompare(L, R), CreateInt(0));
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptGreatEqual: {

                // 支持整数、浮点、字符串、字节集

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateICmpSGE(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFCmpOGE(L, R);     // 这里用有序比较
                } else if (RTBuilder.isStringType(opt_type)) {
                    // StrCmp(L,R)>=0
                    return Builder.CreateICmpSGE(RTBuilder.StringCompare(L, R), CreateInt(0));
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptLessEqual: {

                // 支持整数、浮点、字符串、字节集

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateICmpSLE(L, R);
                } else if (opt_type->isFloatTy() || opt_type->isDoubleTy()) {
                    return Builder.CreateFCmpOLE(L, R);     // 这里用有序比较
                } else if (RTBuilder.isStringType(opt_type)) {
                    // StrCmp(L,R)<=0
                    return Builder.CreateICmpSLE(RTBuilder.StringCompare(L, R), CreateInt(0));
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptLikeEqual: {

                // 支持字符串、字节集

                if (RTBuilder.isStringType(opt_type)) {
                    return RTBuilder.StringLikeEqual(L, R);
                } else {
                    assert(false);
                    return nullptr;
                }
            }
                // *** 逻辑系列 ***
            case OperatorType::kOptAnd: {

                // 支持整数

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateAnd(L, R);
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            case OperatorType::kOptOr: {

                // 支持整数

                if (opt_type->isIntegerTy()) {
                    return Builder.CreateOr(L, R);
                } else {
                    assert(false);
                    return nullptr;
                }
            }
            default: {
                assert(false);
                return nullptr;
            }
        }
    }

    llvm::Value *IREmit::_EmitImpl_(Value *value) {
        if (ValueOfDataSet *value_of_dataset = value->as<ValueOfDataSet>()) {
            return Emit(value_of_dataset);
        } else if (ValueOfDatetime *value_of_datetime = value->as<ValueOfDatetime>()) {
            return Emit(value_of_datetime);
        } else if (FuncAddrExpression *func_addr_expression = value->as<FuncAddrExpression>()) {
            return Emit(func_addr_expression);
        } else if (ResourceRefExpression *resource_ref_expr = value->as<ResourceRefExpression>()) {
            assert(false);
            return nullptr;
        } else if (ValueOfBool *value_of_bool = value->as<ValueOfBool>()) {
            return Emit(value_of_bool);
        } else if (ValueOfDecimal *value_of_decimal = value->as<ValueOfDecimal>()) {
            return Emit(value_of_decimal);
        } else if (ValueOfString *value_of_string = value->as<ValueOfString>()) {
            return Emit(value_of_string);
        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::Constant *IREmit::MakeGlobalConstantByteSet(const std::vector<llvm::Constant *> &elements) {

        // 创建数组数据

        llvm::ArrayType *arr_ty = llvm::ArrayType::get(Builder.getInt8Ty(), elements.size());
        llvm::Constant *init_val = llvm::ConstantArray::get(arr_ty, elements);

        return init_val;
    }

    llvm::Value *IREmit::_EmitImpl_(ValueOfDataSet *valueOfDataSet) {
        std::vector<llvm::Constant *> elements;
        for (Expression *element_expr : valueOfDataSet->elements_) {
            llvm::Constant *e = llvm::dyn_cast<llvm::Constant>(Emit(element_expr));
            elements.push_back(e);
        }
        return MakeGlobalConstantByteSet(elements);
    }

    llvm::Value *IREmit::_EmitImpl_(ValueOfDatetime *valueOfDatetime) {
        llvm::Type *type = type_object_pool_[valueOfDatetime->expression_type_];
        assert(type);
        return CreateInt(valueOfDatetime->time_, type->getScalarSizeInBits());
    }

    llvm::Value *IREmit::_EmitImpl_(FuncAddrExpression *funcAddrExpression) {
        llvm::Function *func = function_object_pool_[funcAddrExpression->functor_declare_];
        assert(func);
        return llvm::ConstantExpr::getPtrToInt(func, Builder.getInt32Ty());
    }

    llvm::Value *IREmit::_EmitImpl_(ValueOfBool *valueOfBool) {
        return CreateInt((int) valueOfBool->value_, 1, false);
    }

    llvm::Value *IREmit::_EmitImpl_(ValueOfDecimal *valueOfDecimal) {
        switch (valueOfDecimal->type_) {
            case ValueOfDecimal::type::kInt: {
                return CreateInt(valueOfDecimal->int_val_, 32, true);
            }
            case ValueOfDecimal::type::kFloat: {
                return llvm::ConstantFP::get(TheContext, llvm::APFloat(valueOfDecimal->float_val_));
            }
            default: {
                assert(false);
                return nullptr;
            }
        }
    }

    llvm::Value *IREmit::_EmitImpl_(ValueOfString *valueOfString) {

        // 创建指向字符串常量值的对象，就不需要Load了

        llvm::Value *strptr = Builder.CreateGlobalStringPtr(valueOfString->string_literal_.string_.str(), "$.pstr");
        llvm::Value *str_rt_val = RTBuilder.CreateString(strptr);
        return str_rt_val;
    }

    IREmit::IREmit()
            : TheModule(new llvm::Module("a.ll", TheContext)),
              Builder(llvm::IRBuilder<>(TheContext)),
              RTBuilder(TheModule, Builder),
              DebInfoBuilder(*TheModule),
              RexDbgMgr(Builder, DebInfoBuilder) {

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
    bool                    IREmit::Emit(TranslateUnit *        astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::GlobalVariable *  IREmit::Emit(GlobalVariableDecl *   astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(ParameterDecl *        astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::GlobalVariable *  IREmit::Emit(FileVariableDecl *     astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(LocalVariableDecl *    astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Type *            IREmit::Emit(TypeDecl *             astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Type *            IREmit::Emit(BuiltinTypeDecl *      astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::PointerType *     IREmit::Emit(ArrayDecl *            astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::PointerType *     IREmit::Emit(StructureDecl *        astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Function *        IREmit::Emit(FunctorDecl *          astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Function *        IREmit::Emit(FunctionDecl *         astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(Statement *            astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(IfStmt *               astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(StatementBlock *       astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(LoopStatement *        astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(WhileStmt *            astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(RangeForStmt *         astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(ForStmt *              astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(DoWhileStmt *          astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(AssignStmt *           astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(ControlStmt *          astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(LoopControlStmt *      astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(ContinueStmt *         astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(BreakStmt *            astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(ReturnStmt *           astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::BasicBlock *      IREmit::Emit(ExitStmt *             astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(Expression *           astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(TypeConvert *          astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(HierarchyIdentifier *  astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(NameComponent *        astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(UnaryExpression *      astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(BinaryExpression *     astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(Value *                astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(ValueOfDataSet *       astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(ValueOfDatetime *      astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(FuncAddrExpression *   astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(ValueOfBool *          astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(ValueOfDecimal *       astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }
    llvm::Value *           IREmit::Emit(ValueOfString *        astNode) { OnEmitBegin(astNode); auto ret = _EmitImpl_(astNode); OnEmitEnd(astNode); return ret; }

    IREmit::~IREmit() {
        delete TheModule;
    }

    llvm::Module *IREmit::GetModule() {
        return TheModule;
    }

}
