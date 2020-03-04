//
// Created by rex on 2020/2/4.
//

#include <iostream>
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

#include "EmitLLVMIR.h"
#include "LLVMRTIRBuilder.h"
#include "../opene_compiler/NodeDecl.h"
#include "../opene_compiler/ASTUtility.h"

namespace opene {

    class IREmit {
    private:
        // 可控结构
        class ControlableStructure {
        private:
            llvm::BasicBlock *head_bb = nullptr;
            llvm::BasicBlock *true_bb = nullptr;
            llvm::BasicBlock *false_bb = nullptr;
            llvm::BasicBlock *tail_bb = nullptr;
        public:
            ControlableStructure(
                    llvm::BasicBlock *headBB,
                    llvm::BasicBlock *trueBB,
                    llvm::BasicBlock *falseBB,
                    llvm::BasicBlock *tailBB
                    )
                    : head_bb(headBB), true_bb(trueBB), false_bb(falseBB), tail_bb(tailBB) {
            }

        public:
            llvm::BasicBlock *getHeadBB() const {
                return head_bb;
            }

            void setHeadBB(llvm::BasicBlock *headBB) {
                head_bb = headBB;
            }

            llvm::BasicBlock *getTrueBB() const {
                return true_bb;
            }

            void setTrueBb(llvm::BasicBlock *trueBB) {
                true_bb = trueBB;
            }

            llvm::BasicBlock *getFalseBB() const {
                return false_bb;
            }

            void setFalseBb(llvm::BasicBlock *falseBB) {
                false_bb = falseBB;
            }

            llvm::BasicBlock *getTailBB() const {
                return tail_bb;
            }

            void setTailBB(llvm::BasicBlock *tailBB) {
                tail_bb = tailBB;
            }
        };

    private:
        // 当前上下文(LLVM)
        llvm::LLVMContext TheContext;
        // IR构造器
        llvm::IRBuilder<> Builder;
        // 当前模块(LLVM)
        llvm::Module * TheModule = nullptr;
        // 当前函数(LLVM)
        llvm::Function * TheFunction = nullptr;
        LLVMRTIRBuilder RTBuilder;
        llvm::Function *SysEntryFunc = nullptr;
        llvm::Function *InitFunc = nullptr;
        ProgSetDecl *TheProgramSet = nullptr;
        FunctionDecl *TheASTFunction = nullptr;
        std::map<BaseVariDecl*, llvm::Value*> variable_object_pool_;
        std::map<TypeDecl*, llvm::Type*> type_object_pool_;
        std::map<FunctorDecl*, llvm::Function*> function_object_pool_;
        std::stack<ControlableStructure> controlable_struct_stack_;

    private:
        llvm::Type *GetType(TypeDecl *typeDecl) {
            auto found = type_object_pool_.find(typeDecl);
            if (found != type_object_pool_.end()) {
                return found->second;
            } else {
                llvm::Type *type_obj = Emit(typeDecl);
                type_object_pool_[typeDecl] = type_obj;
                return type_obj;
            }
        }

        llvm::Function *GetFunction(const std::string &function_name) {
            for (auto &functor_item : function_object_pool_) {
                if (functor_item.first->name_.string_.str() == function_name) {
                    return functor_item.second;
                }
            }
            return nullptr;
        }

    private:
        bool DeclareMainEntry() {
            std::vector<llvm::Type*> parameters_type = { Builder.getInt32Ty(), Builder.getInt8PtrTy()->getPointerTo() };
            llvm::FunctionType *main_fn_ty = llvm::FunctionType::get(Builder.getInt32Ty(), parameters_type, false);
            SysEntryFunc = llvm::Function::Create(main_fn_ty, llvm::Function::ExternalLinkage, "main", TheModule);
            (SysEntryFunc->arg_begin() + 0)->setName("argc");
            (SysEntryFunc->arg_begin() + 1)->setName("argv");

            return true;
        }

        bool CreateEntryAndInit(TranslateUnit *translateUnit, llvm::Function *userEntry) {

            // 初始化函数

            InitFunc = llvm::Function::Create(llvm::FunctionType::get(Builder.getVoidTy(), false), llvm::Function::InternalLinkage, "#init", TheModule);
            llvm::BasicBlock::Create(TheContext, "entry", InitFunc);

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

        llvm::BasicBlock *CreateInitBlock(const std::string &blockName = "") {
            llvm::BasicBlock *init_bb = llvm::BasicBlock::Create(TheContext, blockName, InitFunc);
            return init_bb;
        }

        bool AddInitBlocks(llvm::BasicBlock *beginBlock, llvm::BasicBlock *endBlock) {
            auto &block_list = InitFunc->getBasicBlockList();
            llvm::BasicBlock *latest_init_block = &block_list.back();
            Builder.SetInsertPoint(latest_init_block);
            Builder.CreateBr(beginBlock);
            return true;
        }

        bool FinishInitBlockInsert() {
            auto &block_list = InitFunc->getBasicBlockList();
            llvm::BasicBlock *latest_init_block = &block_list.back();
            Builder.SetInsertPoint(latest_init_block);
            Builder.CreateRetVoid();
            return true;
        }

        /*
         * 根据请求的变量不同执行不同的操作
         * 参数 - 直接
         * 全局变量 - Builder.CreateLoad
         * 局部变量 - Builder.CreateLoad
         */
        llvm::Value *LoadVariable(llvm::Value *variable) {
            if (llvm::GlobalVariable *global_variable = llvm::dyn_cast<llvm::GlobalVariable>(variable)) {
                return Builder.CreateLoad(global_variable->getValueType(), global_variable);
            } else if (llvm::AllocaInst *alloca_inst = llvm::dyn_cast<llvm::AllocaInst>(variable)) {
                return Builder.CreateLoad(alloca_inst->getAllocatedType(), alloca_inst);
            } else if (llvm::Argument *argument = llvm::dyn_cast<llvm::Argument>(variable)) {
                return argument;
            } else if (llvm::LoadInst *load_inst = llvm::dyn_cast<llvm::LoadInst>(variable)) {
                return load_inst;
            } else {
                assert(false);
                return variable;
            }
        }

        bool StoreVariable(llvm::Value *value, llvm::Value *variable) {
            value = LoadVariable(value);
            if (llvm::GlobalVariable *global_variable = llvm::dyn_cast<llvm::GlobalVariable>(variable)) {
                Builder.CreateStore(value, global_variable);
                return true;
            } else if (llvm::AllocaInst *alloca_inst = llvm::dyn_cast<llvm::AllocaInst>(variable)) {
                Builder.CreateStore(value, alloca_inst);
                return true;
            } else {
                assert(false);
                return variable;
            }
        }

        llvm::ConstantInt *CreateInt(int intValue, unsigned int nBits = 32, bool isSigned = false) {
            return llvm::ConstantInt::get(TheContext, llvm::APInt(nBits, intValue, isSigned));
        }

    public:
        bool Emit(TranslateUnit *translateUnit) {
            TheModule = new llvm::Module("a.ll", TheContext);

            DeclareMainEntry();

            // 全局变量
            for (auto &global_vari_item : translateUnit->global_variables_) {
                llvm::GlobalVariable *gvari = Emit(global_vari_item.second);
                assert(gvari);
                variable_object_pool_[global_vari_item.second] = gvari;
            }
            // 文件变量
            for (auto &file_item : translateUnit->source_file_) {
                if (ProgramSetFile *program_set_file = file_item->as<ProgramSetFile>()) {
                    for (auto &prog_vari_item : program_set_file->program_set_declares_->file_static_variables_) {
                        FileVariableDecl *file_variable_decl = prog_vari_item.second;
                        llvm::GlobalVariable *fvari = Emit(file_variable_decl);
                        assert(fvari);
                        variable_object_pool_[prog_vari_item.second] = fvari;
                    }
                }
            }
            // 函数声明
            for (auto &functor_decl_item : translateUnit->functor_declares_) {
                llvm::Function *functor_decl = Emit(functor_decl_item.second);
            }
            // 函数定义
            for (auto &function_def_item : translateUnit->function_decls_) {
                this->TheProgramSet = function_def_item.second->parent_node_->as<ProgSetDecl>();
                llvm::Function *function_def = Emit(function_def_item.second);
                this->TheProgramSet = nullptr;
            }

            llvm::Function *user_entry = function_object_pool_[translateUnit->main_entry_];
            assert(user_entry);
            CreateEntryAndInit(translateUnit, user_entry);
            FinishInitBlockInsert();

            return true;
        }

//        llvm::Value *Emit(SourceFile *sourceFile);
//        llvm::Value *Emit(ProgramSetFile *programSetFile);
//        llvm::Value *Emit(GlobalVariableFile *globalVariableFile);
//        llvm::Value *Emit(DataStructureFile *dataStructureFile);
//        llvm::Value *Emit(DllDefineFile *dllDefineFile);
//        llvm::Value *Emit(Decl *decl);
//        llvm::Value *Emit(TagDecl *tagDecl);
//        llvm::Value *Emit(VariableDecl *variableDecl);
//        llvm::Value *Emit(BaseVariDecl *baseVariDecl);

        void CreateVariableInitialization(llvm::Value *variable) {
            if (llvm::GlobalVariable *gvari = llvm::dyn_cast<llvm::GlobalVariable>(variable)) {
                // TODO:
            }
        }

        llvm::GlobalVariable *CreateGlobalVariable(TypeDecl *vari_type, const std::string &vari_name) {
            llvm::Type *_vari_type = GetType(vari_type);
            llvm::GlobalVariable *gvari = new llvm::GlobalVariable(
                    /*Module*/*TheModule,
                    /*Type*/_vari_type,
                    /*Constant*/false,
                    /*Linkage*/llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                    /*Initializer*/nullptr,
                    /*Name*/vari_name,
                    /*InsertBefor*/nullptr,
                    /*ThreadLocal*/llvm::GlobalVariable::ThreadLocalMode::NotThreadLocal,
                    /*AddressSpace*/0,
                    /*ExternallyInitalized*/false
            );
            gvari->setAlignment(4);
            CreateVariableInitialization(gvari);
            return gvari;
        }

        llvm::GlobalVariable *Emit(GlobalVariableDecl *globalVariableDecl) {
            return CreateGlobalVariable(globalVariableDecl->type_decl_ptr_, globalVariableDecl->name_.string_.str());
        }

        llvm::Value *Emit(ParameterDecl *parameterDecl) {
            llvm::Type *param_type = GetType(parameterDecl->type_decl_ptr_);
            // 创建参数在栈内的空间
            llvm::AllocaInst *alloca_param = Builder.CreateAlloca(param_type, nullptr, parameterDecl->name_.string_.str());
            variable_object_pool_[parameterDecl] = alloca_param;
            // 将参数值加载到栈内存中
            llvm::Argument *argument = TheFunction->arg_begin() + parameterDecl->index_;
            StoreVariable(argument, alloca_param);
            return alloca_param;
        }

        llvm::GlobalVariable *Emit(FileVariableDecl *fileVariableDecl) {
            llvm::Type *vari_type = GetType(fileVariableDecl->type_decl_ptr_);
            std::string vari_name = fileVariableDecl->name_.string_.str();
            // 文件变量需要重命名以免名称冲突
            vari_name = TheProgramSet->name_.string_.str() + "." + vari_name;
            llvm::GlobalVariable *fvari = new llvm::GlobalVariable(
                    /*Module*/*TheModule,
                    /*Type*/vari_type,
                    /*Constant*/false,
                    /*Linkage*/llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                    /*Initializer*/nullptr,
                    /*Name*/vari_name,
                    /*InsertBefor*/nullptr,
                    /*ThreadLocal*/llvm::GlobalVariable::ThreadLocalMode::NotThreadLocal,
                    /*AddressSpace*/0,
                    /*ExternallyInitalized*/false
            );
            fvari->setAlignment(4);

            return fvari;
        }

        llvm::Value *Emit(LocalVariableDecl *localVariableDecl) {
            llvm::Type *vari_type = GetType(localVariableDecl->type_decl_ptr_);
            std::string vari_name = localVariableDecl->name_.string_.str();
            if (localVariableDecl->is_static_ == false) {
                // 非静态变量在栈上创建
                llvm::AllocaInst *lvari = Builder.CreateAlloca(vari_type, nullptr, vari_name);
                lvari->setAlignment(4);
                // TODO: 添加初始化表达式
                return lvari;
            } else {
                // 在静态变量前增加名字修饰以免冲突
                vari_name = TheASTFunction->super_set_->name_.string_.str() + "." + TheASTFunction->name_.string_.str() + "." + vari_name;
                llvm::GlobalVariable *static_vari = CreateGlobalVariable(localVariableDecl->type_decl_ptr_, vari_name);
                static_vari->setLinkage(llvm::GlobalValue::LinkageTypes::InternalLinkage);
                // TODO: 添加初始化表达式
                return static_vari;
            }
        }

        llvm::Type *Emit(TypeDecl *typeDecl) {
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

        llvm::Type *Emit(BuiltinTypeDecl *builtinTypeDecl) {
            auto type_found = type_object_pool_.find(builtinTypeDecl);
            llvm::Type *type = nullptr;
            if (type_found != type_object_pool_.end()) {
                if ((type = type_found->second)) {
                    return type;
                }
            }

            switch (builtinTypeDecl->built_in_type_) {
                case BuiltinTypeDecl::EnumOfBuiltinType::kBTypeChar:
                    type = Builder.getInt8Ty();
                    break;
                case BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger:
                    type = Builder.getInt32Ty();
                    break;
                case BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFloat:
                    type = Builder.getFloatTy();
                    break;
                case BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool:
                    type = Builder.getInt1Ty();
                    break;
                case BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString:
                    type = Builder.getVoidTy()->getPointerTo(); // 字符串对象指针
                    break;
                case BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet:
                    type = Builder.getVoidTy()->getPointerTo(); // 字节集对象指针
                    break;
                case BuiltinTypeDecl::EnumOfBuiltinType::kBTypeShort:
                    type = Builder.getInt16Ty();
                    break;
                case BuiltinTypeDecl::EnumOfBuiltinType::kBTypeLong:
                    type = Builder.getInt64Ty();
                    break;
                case BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatetime:
                    type = Builder.getInt64Ty();
                    break;
                case BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDouble:
                    type = Builder.getDoubleTy();
                    break;
                default:
                    assert(false);
                    return nullptr;
            }
            type_object_pool_[builtinTypeDecl] = type;
            return type;
        }

        /*
         * 创建数组
         * 返回数组指针类型
         */
        llvm::PointerType *Emit(ArrayDecl *arrayDecl) {
            llvm::Type *element_type = GetType(arrayDecl->base_type_);
            return RTBuilder.getArrayRT().CreateArrayType(element_type, arrayDecl->dimensions_)->getPointerTo();
        }

        /*
         * 创建结构体定义
         * 返回结构体指针类型
         */
        llvm::PointerType *Emit(StructureDecl *structureDecl) {
            llvm::StructType *structure_decl = llvm::dyn_cast<llvm::StructType>(type_object_pool_[structureDecl]);
            if (structure_decl) { return structure_decl->getPointerTo(); }
            structure_decl = llvm::StructType::create(TheContext, structureDecl->name_.string_.str());
            type_object_pool_[structureDecl] = structure_decl;
            // 依次生成成员类型
            std::vector<llvm::Type*> members_type;
            for (auto &member_item : structureDecl->members_) {
                llvm::Type *member_type = GetType(member_item.second->type_decl_ptr_);
                members_type.emplace_back(member_type);
            }
            structure_decl->setBody(members_type);
            return structure_decl->getPointerTo();
        }

        /*
         * 可调用对象声明
         * 仅声明原型不定义内容
         */
        llvm::Function *Emit(FunctorDecl *functorDecl) {
            // 构建形参声明
            std::vector<llvm::Type*> parameter_types;
            for (ParameterDecl *parameter_decl : functorDecl->parameters_) {
                llvm::Type *parameter_type = GetType(parameter_decl->type_decl_ptr_);
                parameter_types.push_back(parameter_type);
            }
            // 构建返回值类型
            llvm::Type *return_type = GetType(functorDecl->return_type_);
            // 构建函数原型
            llvm::FunctionType *function_type = llvm::FunctionType::get(return_type, parameter_types, false);   // TODO: 这里暂时设为False
            std::string function_name = functorDecl->name_.string_.str();
            // 构建函数
            llvm::Function *function = llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, function_name, TheModule);
            // 设置参数名
            unsigned idx = 0;
            for (auto &param : function->args()) {
                param.setName(functorDecl->parameters_[idx]->name_.string_.str());
                // 注册参数
                variable_object_pool_[functorDecl->parameters_[idx]] = &param;
                idx++;
            }
            // 所有函数声明都添加到查找表中
            function_object_pool_[functorDecl] = function;
            return function;
        }

        llvm::Function *Emit(FunctionDecl *functionDecl) {
            std::string function_name = functionDecl->name_.string_.str();
            llvm::Function *function = TheModule->getFunction(function_name);
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

            // 开始创建函数体
            llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(TheContext, "entry", function);
            Builder.SetInsertPoint(basic_block);
            // 创建返回值栈空间
            if (functionDecl->return_type_) {
                llvm::Type *ret_type = GetType(functionDecl->return_type_);
                Builder.CreateAlloca(ret_type, nullptr, "$.ret");
            }
            // 创建参数变量
            for (ParameterDecl *param_vari_item : functionDecl->parameters_) {
                Emit(param_vari_item);
            }
            // 创建局部变量
            for (auto &local_vari_item : functionDecl->local_vari_) {
                Emit(local_vari_item.second);
            }
            // 处理语句
            Emit(functionDecl->statement_list_);

            if (llvm::verifyFunction(*function)) {
                assert(false);
                function->eraseFromParent();
                function = nullptr;
            }

            this->TheFunction = nullptr;
            this->TheASTFunction = nullptr;
            return function;
        }

//        llvm::Function *Emit(DllCommandDecl *dllCommandDecl)；

        bool Emit(Statement *statement) {
            if (AssignStmt *assignStmt = statement->as<AssignStmt>()) {
                return Emit(assignStmt);
            } else if (ControlStmt *controlStmt = statement->as<ControlStmt>()) {
                return Emit(controlStmt);
            } else if (IfStmt *ifStmt = statement->as<IfStmt>()) {
                return Emit(ifStmt);
            } else if (LoopStatement *loopStatement = statement->as<LoopStatement>()) {
                return Emit(loopStatement);
            } else if (StatementBlock *statementBlock = statement->as<StatementBlock>()) {
                return Emit(statementBlock);
            } else {
                assert(false);
                return false;
            }
        }

        bool Emit(IfStmt *ifStmt) {
            assert(ifStmt->switches_.size() == 1);

            llvm::BasicBlock *prehead_block = Builder.GetInsertBlock();
            Expression *condition_expr = ifStmt->switches_.front().first;
            assert(condition_expr);
            Statement *then_stmt = ifStmt->switches_.front().second;
            Statement *else_stmt = ifStmt->default_statement_;

            // 生成判断条件
            llvm::Value *condition = Emit(condition_expr);
            assert(condition);
            assert(condition->getType()->getPrimitiveSizeInBits() == 1);

            // THEN块
            llvm::BasicBlock *then_block = llvm::BasicBlock::Create(TheContext, "$.then", TheFunction);
            // ELSE块
            llvm::BasicBlock *else_block = llvm::BasicBlock::Create(TheContext, "$.else", TheFunction);
            // 汇合块
            llvm::BasicBlock *merge_block = llvm::BasicBlock::Create(TheContext, "$.merge", TheFunction);

            // 分支选择跳转
            Builder.CreateCondBr(condition, then_block, else_block);

            // 生成Then块
            Builder.SetInsertPoint(then_block);
            Emit(then_stmt);
            Builder.CreateBr(merge_block);

            // 处理Else块
            Builder.SetInsertPoint(else_block);
            Emit(else_stmt);
            Builder.CreateBr(merge_block);

            // 处理Merge块
            Builder.SetInsertPoint(merge_block);

            return true;
        }

        bool Emit(StatementBlock *statementBlock) {
            bool success = true;
            for (Statement *statement : statementBlock->statements_) {
                success &= Emit(statement);
            }
            return success;
        }

        bool Emit(LoopStatement *loopStatement) {
            bool success = false;
            if (WhileStmt *whileStmt = loopStatement->as<WhileStmt>()) {
                success = Emit(whileStmt);
            } else if (RangeForStmt *rangeForStmt = loopStatement->as<RangeForStmt>()) {
                success = Emit(rangeForStmt);
            } else if (ForStmt *forStmt = loopStatement->as<ForStmt>()) {
                success = Emit(forStmt);
            } else if (DoWhileStmt *doWhileStmt = loopStatement->as<DoWhileStmt>()) {
                success = Emit(doWhileStmt);
            } else {
                assert(false);
            }
            return success;
        }

        bool Emit(WhileStmt *whileStmt) {
            // 当前块
            llvm::BasicBlock *preheader_block = Builder.GetInsertBlock();
            // 循环条件块
            llvm::BasicBlock *condition_block = llvm::BasicBlock::Create(TheContext, "$.condition", TheFunction);
            Builder.CreateBr(condition_block);
            Builder.SetInsertPoint(condition_block);
            // 循环体块
            llvm::BasicBlock *loop_block = llvm::BasicBlock::Create(TheContext, "$.loop", TheFunction);
            // 循环块下一块
            llvm::BasicBlock *after_block = llvm::BasicBlock::Create(TheContext, "$.afterloop", TheFunction);
            // 循环条件
            llvm::Value *loop_condition = Emit(whileStmt->condition_);
            Builder.CreateCondBr(loop_condition, loop_block, after_block);

            controlable_struct_stack_.push({condition_block, loop_block, after_block, after_block});
            // 开始生成循环体
            Builder.SetInsertPoint(loop_block);
            Emit(whileStmt->loop_body_);
            controlable_struct_stack_.pop();

            // 直接跳到循环条件块
            Builder.CreateBr(condition_block);
            // 转到新的块中
            Builder.SetInsertPoint(after_block);
            return true;
        }

        bool BuildRangeFor(llvm::Value *startValue, llvm::Value *stopValue, llvm::Value *stepValue, llvm::Value *loopVari, Statement *loopBody) {
            // 当前块
            llvm::BasicBlock *prehead_block = Builder.GetInsertBlock();
            // 真实循环变量
            llvm::Value *real_loop_vari = Builder.CreateAlloca(llvm::Type::getInt32Ty(TheContext), nullptr, "$.real_loop_vari");

            // 判断循环是否有效
            // Valid = ((stop - start) * step) > 0
            llvm::Value *range_distance = Builder.CreateSub(stopValue, startValue, "$.distance");
            llvm::Value *loop_valid = Builder.CreateICmpSGT(Builder.CreateMul(range_distance, stepValue), CreateInt(0), "$.valid");

            llvm::BasicBlock *loop_entry_block = llvm::BasicBlock::Create(TheContext, "$.loop_entry", TheFunction);
            Builder.SetInsertPoint(loop_entry_block);
            // 计算K值 K=(S>-S)*2-1
            llvm::Value *step_gtz = Builder.CreateICmpSGT(stepValue, Builder.CreateNeg(stepValue));
            step_gtz = Builder.CreateIntCast(step_gtz, llvm::Type::getInt32Ty(TheContext), false, "$.cast_i1_to_i32");
            llvm::Value *K = Builder.CreateSub(Builder.CreateMul(step_gtz, CreateInt(2)), CreateInt(1), "$.K");
            // 设置初始值
            Builder.CreateAlignedStore(startValue, real_loop_vari, 4);

            // === 计算循环条件并选择分支 ===
            // 循环判断块
            llvm::BasicBlock *loop_cond_block = llvm::BasicBlock::Create(TheContext, "$.loop_cond", TheFunction);
            Builder.CreateBr(loop_cond_block);
            Builder.SetInsertPoint(loop_cond_block);
            // 循环条件值 (K*i)<=(K*stop)
            llvm::Value *loop_val = Builder.CreateAlignedLoad(llvm::Type::getInt32Ty(TheContext), real_loop_vari, 4);
            llvm::Value *loop_cv = Builder.CreateICmpSLE(Builder.CreateMul(K, loop_val), Builder.CreateMul(K, stopValue));
            // 循环体块
            llvm::BasicBlock *loop_body_block = llvm::BasicBlock::Create(TheContext, "$.loop_body", TheFunction);
            // 循环步进块
            llvm::BasicBlock *step_block = llvm::BasicBlock::Create(TheContext, "$.loop_step", TheFunction);
            // 循环后块
            llvm::BasicBlock *loop_after_block = llvm::BasicBlock::Create(TheContext, "$.after_loop", TheFunction);
            // 插入循环判断分支跳转
            Builder.CreateCondBr(loop_cv, loop_body_block, loop_after_block);

            controlable_struct_stack_.push({loop_cond_block, loop_body_block, loop_after_block, loop_after_block});
            // === 开始为循环体生成代码 ===
            Builder.SetInsertPoint(loop_body_block);
            if (loopVari) {
                // 更新循环值到名义循环变量
                Builder.CreateAlignedStore(Builder.CreateAlignedLoad(llvm::Type::getInt32Ty(TheContext), real_loop_vari, 4), loopVari, 4);
            }
            Emit(loopBody);
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

            return true;
        }

        bool Emit(RangeForStmt *rangeForStmt) {
            llvm::Value *start_value = CreateInt(1);
            llvm::Value *stop_value = Emit(rangeForStmt->range_size_);
            assert(stop_value);
            llvm::Value *step_value = CreateInt(1);
            llvm::Value *loop_vari = nullptr;
            if (rangeForStmt->loop_vari_) {
                loop_vari = Emit(rangeForStmt->loop_vari_);
                assert(loop_vari);
            }
            bool build_range_success = BuildRangeFor(start_value, stop_value, step_value, loop_vari, rangeForStmt->loop_body_);
            assert(build_range_success);
            return build_range_success;
        }

        bool Emit(ForStmt *forStmt) {
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
            bool build_range_success = BuildRangeFor(start_value, stop_value, step_value, loop_vari, forStmt->loop_body_);
            assert(build_range_success);
            return build_range_success;
        }

        bool Emit(DoWhileStmt *doWhileStmt) {
            // 当前块
            llvm::BasicBlock *preheader_block = Builder.GetInsertBlock();
            // 循环体块
            llvm::BasicBlock *loop_block = llvm::BasicBlock::Create(TheContext, "$.loop", TheFunction);
            Builder.CreateBr(loop_block);
            // 条件判定块
            llvm::BasicBlock *cond_block = llvm::BasicBlock::Create(TheContext, "$.cond", TheFunction);
            // 循环块下一个块
            llvm::BasicBlock *after_block = llvm::BasicBlock::Create(TheContext, "$.afterloop", TheFunction);

            controlable_struct_stack_.push({cond_block, loop_block, after_block, after_block});
            Builder.SetInsertPoint(loop_block);
            // 循环体
            Emit(doWhileStmt->loop_body_);
            controlable_struct_stack_.pop();
            Builder.CreateBr(cond_block);

            Builder.SetInsertPoint(cond_block);
            // 条件判定，分支选择跳转
            llvm::Value *loop_condition = Emit(doWhileStmt->conditon_);
            Builder.CreateCondBr(loop_condition, loop_block, after_block);
            // 转到新的块中
            Builder.SetInsertPoint(after_block);
            return true;
        }

        llvm::Value *MakeAggregateCopy(llvm::Value *object, llvm::PointerType *aggregate_type) {
            llvm::Type *element_type = aggregate_type->getPointerElementType();
            if (element_type->isArrayTy()) {
                return RTBuilder.getArrayRT().CloneArray(object);
            } else if (element_type->isStructTy()) {
                Builder.CreateMemCpy();
            } else {
                assert(false);
            }
        }

        bool Emit(AssignStmt *assignStmt) {
            llvm::Value *lhs = Emit(assignStmt->lhs_);
            assert(lhs);
            llvm::Value *rhs = Emit(assignStmt->rhs_);
            assert(rhs);
            llvm::Type *lhs_type = lhs->getType();
            llvm::Type *rhs_type = rhs->getType();
            llvm::Value *rhs_val = nullptr;
            // 区分数组、字节集、字符串、结构体和其它类型
            if (rhs_type->isPointerTy()) {
                llvm::Type *element_type = rhs_type->getPointerElementType();
                if (element_type->isArrayTy()) {
                    rhs_val = RTBuilder.getArrayRT().CloneArray(rhs);
                } else if (element_type->isStructTy()) {
                    rhs_val = RTBuilder.getStructRT().CloneStruct(rhs);
                } else {
                    assert(false);
                }
                assert(rhs_val);
                assert(rhs_val->getType()->isPointerTy());
            } else {
                rhs_val = LoadVariable(rhs);
                assert(rhs_val);
            }
            bool assign_success = StoreVariable(rhs_val, lhs);
            assert(assign_success);
            return true;
        }

        bool Emit(ControlStmt *controlStmt) {
            if (LoopControlStmt *loopControlStmt = controlStmt->as<LoopControlStmt>()) {
                return Emit(loopControlStmt);
            } else if (ReturnStmt *returnStmt = controlStmt->as<ReturnStmt>()) {
                return Emit(returnStmt);
            } else if (ExitStmt *exitStmt = controlStmt->as<ExitStmt>()) {
                return Emit(exitStmt);
            } else {
                assert(false);
                return false;
            }
        }

        bool Emit(LoopControlStmt *loopControlStmt) {
            if (ContinueStmt *continueStmt = loopControlStmt->as<ContinueStmt>()) {
                return Emit(continueStmt);
            } else if (BreakStmt *breakStmt = loopControlStmt->as<BreakStmt>()) {
                return Emit(breakStmt);
            } else {
                assert(false);
                return false;
            }
        }

        bool Emit(ContinueStmt *continueStmt) {
            if (controlable_struct_stack_.empty()) {
                assert(false);
                return false;
            }
            if (llvm::BasicBlock *head_block = controlable_struct_stack_.top().getHeadBB()) {
                Builder.CreateBr(head_block);
                return true;
            } else {
                assert(false);
                return false;
            }
        }

        bool Emit(BreakStmt *breakStmt) {
            if (controlable_struct_stack_.empty()) {
                assert(false);
                return false;
            }
            if (llvm::BasicBlock *head_block = controlable_struct_stack_.top().getTailBB()) {
                Builder.CreateBr(head_block);
                return true;
            } else {
                assert(false);
                return false;
            }
        }

        llvm::ReturnInst *Emit(ReturnStmt *returnStmt) {
            llvm::ReturnInst *return_inst = nullptr;
            if (returnStmt->return_value_) {
                llvm::Value *RV = Emit(returnStmt->return_value_);
                return_inst = Builder.CreateRet(RV);
            } else {
                return_inst = Builder.CreateRetVoid();
            }
            assert(return_inst);
            return return_inst;
        }

        llvm::Value *Emit(ExitStmt *exitStmt);

        llvm::Value *Emit(Expression *expression);

        llvm::Value *LoadFromStructOrNot(llvm::Value *structInstance, NameComponent *nameComponent) {
            if (Identifier *identifier = nameComponent->as<Identifier>()) {    // 单名称组件

                if (structInstance) {
                    MemberVariableDecl *member_variable_decl = identifier->reference_->as<MemberVariableDecl>();
                    assert(member_variable_decl);
                    return Builder.CreateStructGEP(structInstance, member_variable_decl->index_of_struct_);
                } else {
                    if (llvm::Value *variable = variable_object_pool_[identifier->reference_]) {
                        assert(variable);
                        return variable;
                    } else if (llvm::Function *function = function_object_pool_[identifier->function_ref_]) {
                        assert(function);
                        return function;
                    } else {
                        assert(false);
                        return nullptr;
                    }
                }

            } else if (ArrayIndex *array_index = nameComponent->as<ArrayIndex>()) {

                NameComponent *base = ASTUtility::GetArrayIndexBase(array_index);
                ErrOr<std::vector<Expression *>> indexes = ASTUtility::GetArrayIndexIndexList(array_index);
                if (indexes.HadError()) {
                    assert(false);
                    return nullptr;
                }
                llvm::Value *arr_ptr = LoadFromStructOrNot(structInstance, base);
                assert(arr_ptr);
                std::vector<llvm::Value *> indexes_ir;
                for (Expression *index : indexes.Value()) {
                    llvm::Value *index_ir = Emit(index);
                    assert(index_ir);
                    indexes_ir.push_back(index_ir);
                }
                return RTBuilder.getArrayRT().GetElementPointer(arr_ptr, indexes_ir);

            } else if (FunctionCall *function_call = nameComponent->as<FunctionCall>()) {
                llvm::Function *func_ptr = llvm::dyn_cast<llvm::Function>(LoadFromStructOrNot(structInstance, function_call->function_name_));
                assert(func_ptr);
                std::vector<llvm::Value *> arguments_ir;
                for (Expression *argument : function_call->arguments_) {
                    llvm::Value *argument_ir = Emit(argument);
                    assert(argument_ir);
                    arguments_ir.push_back(argument_ir);
                }
                return Builder.CreateCall(func_ptr, arguments_ir);
            } else {
                assert(false);
                return nullptr;
            }
        }

        llvm::Value *Emit(HierarchyIdentifier *hierarchyIdentifier) {
            llvm::Value *previous_base = nullptr;
            for (NameComponent *name_component : hierarchyIdentifier->name_components_) {
                previous_base = LoadFromStructOrNot(previous_base, name_component);
            }
            return previous_base;
        }

//        llvm::Value *Emit(NameComponent *nameComponent);
//        llvm::Value *Emit(Identifier *identifier);
//        llvm::Value *Emit(ArrayIndex *arrayIndex);

        llvm::Value *Emit(FunctionCall *functionCall) {
            auto found_func = function_object_pool_.find(functionCall->functor_declare_);
            if (found_func == function_object_pool_.end()) {
                assert(false);
                return nullptr;
            }
            llvm::Function *callee = found_func->second;
            if (!callee) {
                assert(false);
                return nullptr;
            }
            std::vector<llvm::Value *> arguments;
            for (Expression *expression : functionCall->arguments_) {
                llvm::Value *argu = Emit(expression);
                if (!argu) {
                    assert(false);
                    return nullptr;
                }
                arguments.push_back(argu);
            }
            return Builder.CreateCall(callee, arguments, "$.calltmp");
        }

        llvm::Value *Emit(UnaryExpression *unaryExpression) {
            llvm::Value *V = Emit(unaryExpression->operand_value_);
            if (!V) {
                assert(false);
                return nullptr;
            }
            switch (unaryExpression->operator_type_) {
                case _OperatorExpression::OperatorType::kOptSub: {
                    return Builder.CreateNeg(V, "$.neg");
                }
                default: {
                    assert(false);
                    return nullptr;
                }
            }
        }

        llvm::Value *Emit(BinaryExpression *binaryExpression) {
            llvm::Value *L = Emit(binaryExpression->lhs_);
            llvm::Value *R = Emit(binaryExpression->rhs_);
            if (!L || !R) {
                assert(false);
                return nullptr;
            }
            switch (binaryExpression->operator_type_) {
                // *** 运算系列 ***
                case _OperatorExpression::OperatorType::kOptAdd: {
                    return Builder.CreateAdd(L, R, "$.addtmp");
                }
                case _OperatorExpression::OperatorType::kOptSub: {
                    return Builder.CreateSub(L, R, "$.subtmp");
                }
                case _OperatorExpression::OperatorType::kOptMul: {
                    return Builder.CreateMul(L, R, "$.multmp");
                }
                case _OperatorExpression::OperatorType::kOptDiv: {
                    return Builder.CreateFDiv(L, R, "$.divtmp");
                }
                case _OperatorExpression::OperatorType::kOptFullDiv: {
                    llvm::Value *div_res = Builder.CreateSDiv(L, R, "$.fulldivtmp");
                    return Builder.CreateFPToSI(div_res, llvm::Type::getInt64Ty(TheContext), "$.fp2si");
                }
                case _OperatorExpression::OperatorType::kOptMod: {
                    return Builder.CreateSRem(L, R, "$.mod");
                }
                // *** 比较系列 ***
                case _OperatorExpression::OperatorType::kOptEqual: {
                    return Builder.CreateICmpEQ(L, R, "$.eq");
                }
                case _OperatorExpression::OperatorType::kOptNotEqual: {
                    return Builder.CreateICmpNE(L, R, "$.ne");
                }
                case _OperatorExpression::OperatorType::kOptGreatThan: {
                    return Builder.CreateICmpSGT(L, R, "$.gt");
                }
                case _OperatorExpression::OperatorType::kOptLessThan: {
                    return Builder.CreateICmpSLT(L, R, "$.lt");
                }
                case _OperatorExpression::OperatorType::kOptGreatEqual: {
                    return Builder.CreateICmpSGE(L, R, "$.ge");
                }
                case _OperatorExpression::OperatorType::kOptLessEqual: {
                    return Builder.CreateICmpSLE(L, R, "$.le");
                }
                case _OperatorExpression::OperatorType::kOptLikeEqual: {
                    // TODO:
                    assert(false);
                    return nullptr;
                }
                // *** 逻辑系列 ***
                case _OperatorExpression::OperatorType::kOptAnd: {
                    return Builder.CreateAnd(L, R, "$.and");
                }
                case _OperatorExpression::OperatorType::kOptOr: {
                    return Builder.CreateOr(L, R, "$.or");
                }
                default: {
                    assert(false);
                    return nullptr;
                }
            }
        }

        llvm::Value *Emit(Value *value) {
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

        llvm::Constant *MakeGlobalConstantByteSet(const std::vector<llvm::Constant*> &elements) {

            // 创建数组数据

            llvm::ArrayType *arr_ty = llvm::ArrayType::get(Builder.getInt8Ty(), elements.size());
            llvm::Constant *init_val = llvm::ConstantArray::get(arr_ty, elements);

            return init_val;
        }

        llvm::Value *Emit(ValueOfDataSet *valueOfDataSet) {
            std::vector<llvm::Constant*> elements;
            for (Expression *element_expr : valueOfDataSet->elements_) {
                llvm::Constant *e = llvm::dyn_cast<llvm::Constant>(Emit(element_expr));
                elements.push_back(e);
            }
            return MakeGlobalConstantByteSet(elements);
        }

        llvm::Value *Emit(ValueOfDatetime *valueOfDatetime) {
            llvm::Type *type = type_object_pool_[valueOfDatetime->expression_type_];
            assert(type);
            return CreateInt(valueOfDatetime->time_, type->getScalarSizeInBits());
        }

        llvm::Value *Emit(FuncAddrExpression *funcAddrExpression) {
            llvm::Function *func = function_object_pool_[funcAddrExpression->functor_declare_];
            assert(func);
            return llvm::ConstantExpr::getPtrToInt(func, Builder.getInt32Ty());
        }

        llvm::Value *Emit(ValueOfBool *valueOfBool) {
            return CreateInt((int)valueOfBool->value_, 1, false);
        }

        llvm::Value *Emit(ValueOfDecimal *valueOfDecimal) {
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

        llvm::Value *Emit(ValueOfString *valueOfString) {
            // 创建指向字符串常量值的对象，就不需要Load了
            return Builder.CreateGlobalStringPtr(valueOfString->string_literal_.string_.str(), "$.pstr");
        }

    public:
        IREmit() : Builder(llvm::IRBuilder<>(TheContext)), RTBuilder(TheModule, Builder) {
        }

        ~IREmit() {
            delete TheModule;
        }

        llvm::Module *GetModule() {
            return TheModule;
        }
    };
}

namespace opene {

    EmitLLVMIR::EmitLLVMIR(TranslateUnit *translateUnit) {
        IREmit emitter;
        emitter.Emit(translateUnit);
        emitter.GetModule()->print(llvm::outs(), nullptr);
    }

}
