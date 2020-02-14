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
#include "../opene_compiler/NodeDecl.h"

namespace opene {

    class IREmit {
    private:
        llvm::LLVMContext TheContext;
        llvm::IRBuilder<> Builder;
        llvm::Module * TheModule = nullptr;
        llvm::Function * TheFunction = nullptr;
        ProgSetDecl *TheProgramSet = nullptr;
        FunctionDecl *TheASTFunction = nullptr;
        std::map<BaseVariDecl*, llvm::Value*> variable_object_pool_;
        std::map<TypeDecl*, llvm::Type*> type_object_pool_;
        std::map<FunctionDecl*, llvm::Function*> function_object_pool_;

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

    private:
        void InitBuiltStructure() {
            // TODO: 初始化字节集结构和字符串结构
            // TODO: 初始化数组运行时
        }

        /*
         * 根据请求的变量不同执行不同的操作
         * 参数 - 直接
         * 全局变量 - Builder.CreateLoad
         */
        llvm::Value *UseVariable(llvm::Value *variable) {
            if (llvm::GlobalVariable *global_variable = llvm::dyn_cast<llvm::GlobalVariable>(variable)) {
                return Builder.CreateLoad(global_variable->getValueType(), variable);
            } else if (llvm::Argument *argument = llvm::dyn_cast<llvm::Argument>(variable)) {
                return argument;
            } else if (llvm::LoadInst *load_inst = llvm::dyn_cast<llvm::LoadInst>(variable)) {
                return load_inst;
            } else {
                assert(false);
                return variable;
            }
        }

        template <size_t bits = 32>
        llvm::ConstantInt *CreateInt(int intValue) {
            return llvm::ConstantInt::get(TheContext, llvm::APInt(bits, intValue));
        }

    public:
        bool Emit(TranslateUnit *translateUnit) {
            TheModule = new llvm::Module("a.ll", TheContext);
            InitBuiltStructure();
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
            return gvari;
        }

        llvm::GlobalVariable *Emit(GlobalVariableDecl *globalVariableDecl) {
            return CreateGlobalVariable(globalVariableDecl->type_decl_ptr_, globalVariableDecl->name_.string_.str());
        }

        llvm::Value *Emit(ParameterDecl *parameterDecl);

        llvm::Value *Emit(MemberVariableDecl *memberVariableDecl);

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
                llvm::AllocaInst *lvari = Builder.CreateAlloca(vari_type, nullptr, vari_name);
                lvari->setAlignment(4);
                return lvari;
            } else {
                // 在静态变量前增加名字修饰以免冲突
                vari_name = TheASTFunction->super_set_->name_.string_.str() + "." + TheASTFunction->name_.string_.str() + "." + vari_name;
                llvm::GlobalVariable *static_vari = CreateGlobalVariable(localVariableDecl->type_decl_ptr_, vari_name);
                static_vari->setLinkage(llvm::GlobalValue::LinkageTypes::InternalLinkage);
                return static_vari;
            }
        }

        llvm::Type *Emit(TypeDecl *typeDecl);
        llvm::Value *Emit(BuiltinTypeDecl *builtinTypeDecl);
        llvm::Value *Emit(ArrayDecl *arrayDecl);
        llvm::Value *Emit(StructureDecl *structureDecl);

        /*
         * 可调用对象声明
         * 仅声明原型不定义内容
         */
        llvm::Function *Emit(FunctorDecl *functorDecl) {
            // 构建形参声明
            std::vector<llvm::Type*> parameter_types;
            for (ParameterDecl *parameter_decl : functorDecl->parameters_) {
                llvm::Type *parameter_type = Emit(parameter_decl->type_decl_ptr_);
                parameter_types.push_back(parameter_type);
            }
            // 构建返回值类型
            llvm::Type *return_type = Emit(functorDecl->return_type_);
            // 构建函数原型
            llvm::FunctionType *function_type = llvm::FunctionType::get(return_type, parameter_types, false);
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
            function_object_pool_[functionDecl] = function;

            // 开始创建函数体
            llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(TheContext, "entry", function);
            Builder.SetInsertPoint(basic_block);
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

        llvm::Function *Emit(DllCommandDecl *dllCommandDecl) {
            std::string dll_name = dllCommandDecl->name_.string_.str();
            llvm::Function *function = TheModule->getFunction(dll_name);
            if (!function) {
                return Emit(dllCommandDecl->as<FunctorDecl>());
            } else {
                return function;
            }
        }

        llvm::Value *Emit(Statement *statement);

        llvm::Value *Emit(IfStmt *ifStmt) {
            assert(ifStmt->switches_.size() == 1);

            Expression *condition_expr = ifStmt->switches_.front().first;
            Statement *then_stmt = ifStmt->switches_.front().second;

            llvm::Value *condition = Emit(condition_expr);    // 这里的条件变量应该是1位的布尔值了
            assert(condition);
            assert(condition->getType()->getPrimitiveSizeInBits() == 1);

            // 创建块
            llvm::BasicBlock *then_block = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
            llvm::BasicBlock *else_block = llvm::BasicBlock::Create(TheContext, "else", TheFunction);
            llvm::BasicBlock *merge_block = llvm::BasicBlock::Create(TheContext, "ifcont");
            llvm::BranchInst *branch_inst = Builder.CreateCondBr(condition, then_block, else_block);

            // 处理Then块
            Builder.SetInsertPoint(then_block);
            llvm::Value *then_value = Emit(then_stmt);
            assert(then_value);
            Builder.CreateBr(merge_block);
            // 在生成Then块的内容时可能会改变当前块，所以这里需要更新
            then_block = Builder.GetInsertBlock();

            // 处理Else块
            TheFunction->getBasicBlockList().push_back(else_block);
            Builder.SetInsertPoint(else_block);
            llvm::Value *else_value = Emit(ifStmt->default_statement_);
            assert(else_value);
            Builder.CreateBr(merge_block);
            // 更新
            else_block = Builder.GetInsertBlock();

            // 处理Merge块
            TheFunction->getBasicBlockList().push_back(merge_block);
            Builder.SetInsertPoint(merge_block);
            llvm::PHINode *PN = Builder.CreatePHI(llvm::Type::getInt1Ty(TheContext), 2, "iftmp");
            PN->addIncoming(then_value, then_block);
            PN->addIncoming(else_value, else_block);

            return PN;
        }

        void Emit(StatementBlock *statementBlock) {
            for (Statement *statement : statementBlock->statements_) {
                Emit(statement);
            }
        }

        bool Emit(LoopStatement *loopStatement) {
            if (WhileStmt *whileStmt = loopStatement->as<WhileStmt>()) {
                return Emit(whileStmt);
            } else if (RangeForStmt *rangeForStmt = loopStatement->as<RangeForStmt>()) {
                return Emit(rangeForStmt);
            } else if (ForStmt *forStmt = loopStatement->as<ForStmt>()) {
                return Emit(forStmt);
            } else if (DoWhileStmt *doWhileStmt = loopStatement->as<DoWhileStmt>()) {
                return Emit(doWhileStmt);
            } else {
                assert(false);
                return false;
            }
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
            // 开始生成循环体
            Builder.SetInsertPoint(loop_block);
            Emit(whileStmt->loop_body_);
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

            // === 开始为循环体生成代码 ===
            Builder.SetInsertPoint(loop_body_block);
            if (loopVari) {
                // 更新循环值到名义循环变量
                Builder.CreateAlignedStore(Builder.CreateAlignedLoad(llvm::Type::getInt32Ty(TheContext), real_loop_vari, 4), loopVari, 4);
            }
            Emit(loopBody);
            Builder.CreateBr(step_block);

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
            Builder.SetInsertPoint(loop_block);
            // 循环体
            Emit(doWhileStmt->loop_body_);
            // 循环块下一个块
            llvm::BasicBlock *after_block = llvm::BasicBlock::Create(TheContext, "$.afterloop", TheFunction);
            // 条件判定，分支选择跳转
            llvm::Value *loop_condition = Emit(doWhileStmt->conditon_);
            Builder.CreateCondBr(loop_condition, loop_block, after_block);
            // 转到新的块中
            Builder.SetInsertPoint(after_block);
            return true;
        }

        llvm::Value *Emit(AssignStmt *assignStmt);
        llvm::Value *Emit(ControlStmt *controlStmt);
        llvm::Value *Emit(LoopControlStmt *loopControlStmt);
        llvm::Value *Emit(ContinueStmt *continueStmt);
        llvm::Value *Emit(BreakStmt *breakStmt);

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
        llvm::Value *Emit(HierarchyIdentifier *hierarchyIdentifier);
        llvm::Value *Emit(NameComponent *nameComponent);
        llvm::Value *Emit(Identifier *identifier);

        llvm::Value *Emit(ArrayIndex *arrayIndex) {
            llvm::Value *base = Emit(arrayIndex->base_);
            llvm::Value *index = Emit(arrayIndex->index_);
            // TODO: 需要运行时支持
            assert(false);
            return nullptr;
        }

        llvm::Value *Emit(FunctionCall *functionCall) {
            llvm::Function *callee = TheModule->getFunction(functionCall->functor_declare_->name_.string_.str());
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
            return Builder.CreateCall(callee, arguments, "calltmp");
        }

        llvm::Value *Emit(UnaryExpression *unaryExpression) {
            llvm::Value *V = Emit(unaryExpression->operand_value_);
            if (!V) {
                assert(false);
                return nullptr;
            }
            switch (unaryExpression->operator_type_) {
                case _OperatorExpression::OperatorType::kOptSub: {
                    return Builder.CreateNeg(V, "neg");
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
                    return Builder.CreateAdd(L, R, "addtmp");
                }
                case _OperatorExpression::OperatorType::kOptSub: {
                    return Builder.CreateSub(L, R, "subtmp");
                }
                case _OperatorExpression::OperatorType::kOptMul: {
                    return Builder.CreateMul(L, R, "multmp");
                }
                case _OperatorExpression::OperatorType::kOptDiv: {
                    return Builder.CreateFDiv(L, R, "divtmp");
                }
                case _OperatorExpression::OperatorType::kOptFullDiv: {
                    llvm::Value *div_res = Builder.CreateSDiv(L, R, "fulldivtmp");
                    return Builder.CreateFPToSI(div_res, llvm::Type::getInt64Ty(TheContext), "fp2si");
                }
                case _OperatorExpression::OperatorType::kOptMod: {
                    // TODO:
                    return nullptr;
                }
                // *** 比较系列 ***
                case _OperatorExpression::OperatorType::kOptEqual: {
                    return Builder.CreateICmpEQ(L, R, "eq");
                }
                case _OperatorExpression::OperatorType::kOptNotEqual: {
                    return Builder.CreateICmpNE(L, R, "ne");
                }
                case _OperatorExpression::OperatorType::kOptGreatThan: {
                    return Builder.CreateICmpSGT(L, R, "gt");
                }
                case _OperatorExpression::OperatorType::kOptLessThan: {
                    return Builder.CreateICmpSLT(L, R, "lt");
                }
                case _OperatorExpression::OperatorType::kOptGreatEqual: {
                    return Builder.CreateICmpSGE(L, R, "ge");
                }
                case _OperatorExpression::OperatorType::kOptLessEqual: {
                    return Builder.CreateICmpSLE(L, R, "le");
                }
                case _OperatorExpression::OperatorType::kOptLikeEqual: {
                    // TODO:
                    assert(false);
                    return nullptr;
                }
                // *** 逻辑系列 ***
                case _OperatorExpression::OperatorType::kOptAnd: {
                    return Builder.CreateAnd(L, R, "and");
                }
                case _OperatorExpression::OperatorType::kOptOr: {
                    return Builder.CreateOr(L, R, "or");
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
                return Emit(resource_ref_expr);
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

        llvm::Value *Emit(ValueOfDataSet *valueOfDataSet);
        llvm::Value *Emit(ValueOfDatetime *valueOfDatetime);
        llvm::Value *Emit(FuncAddrExpression *funcAddrExpression);
        llvm::Value *Emit(ResourceRefExpression *resourceRefExpression);

        llvm::Value *Emit(ValueOfBool *valueOfBool) {
            return llvm::ConstantInt::get(TheContext, llvm::APInt(1, (int)valueOfBool->value_, false));
        }

        llvm::Value *Emit(ValueOfDecimal *valueOfDecimal) {
            switch (valueOfDecimal->type_) {
                case ValueOfDecimal::type::kInt: {
                    return llvm::ConstantInt::get(TheContext, llvm::APInt(64, valueOfDecimal->int_val_, true));
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

        llvm::Value *Emit(ValueOfString *valueOfString);

    public:
        IREmit() : Builder(llvm::IRBuilder<>(TheContext)) {
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
