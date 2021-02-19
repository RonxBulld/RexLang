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

    /*****************************************************************************************************************/

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

    /*****************************************************************************************************************/

    int NewEmitter::OnEmitBegin(Node *astNode) {
        RexDbgMgr.OnEmitBegin(astNode);
        return 0;
    }

    int NewEmitter::OnEmitEnd(Node *astNode) {
        RexDbgMgr.OnEmitEnd(astNode);
        return 0;
    }

    /*****************************************************************************************************************/

    /*
     * 根据指定的类型和名称，创建全局变量
     */
    llvm::GlobalVariable *NewEmitter::CreateGlobalVariable(VariTypeDecl *type, const std::string &name) {
        llvm::Type *vari_type = varitype_map_[type];
        assert(vari_type);
        llvm::GlobalVariable *gvari = new llvm::GlobalVariable(
                /* Module */                    *TheModule,
                /* Type */                      vari_type,
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

    bool NewEmitter::RequestLoadBeforeRead(llvm::Value *value) const {
        if (llvm::dyn_cast<llvm::GlobalVariable>(value)) {      // 全局变量
            return true;
        }
        else if (llvm::dyn_cast<llvm::AllocaInst>(value)) {     // 局部变量
            return true;
        }
        else if (llvm::dyn_cast<llvm::Argument>(value)) {       // 参数值
            // 在函数体中使用时，参数当然表示调用函数时使用的实际参数的值。
            // 但是不应当走到这个分支，因为在函数开始的时候就已经被加载到局部变量了。
            assert(false);
            return false;
        }
        else if (llvm::dyn_cast<llvm::LoadInst>(value)) {       // 已加载对象
            return false;
        }
        else if (llvm::dyn_cast<llvm::Constant>(value)) {       // 常量
            return false;
        }
        else {
            assert(false);
            return false;
        }
    }

    llvm::ConstantInt *NewEmitter::CreateInt(uint64_t intValue, unsigned int nBits, bool isSigned) {
        return llvm::ConstantInt::get(TheContext, llvm::APInt(nBits, intValue, isSigned));
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

    /*****************************************************************************************************************/
    // region 全局部分

    llvm::Module *NewEmitter::impl_EmitTranslateUnit(TranslateUnit *TU) {
        RexDbgMgr.GetOrCreateDICompileUnit(TU->getFileName());

        // 声明类型

        for (VariTypeDecl *vari_type : TU->getVariTypeList()) {
            assert(varitype_map_[vari_type] == nullptr);
            llvm::Type *llvm_varitype = Emit(vari_type);
            varitype_map_[vari_type] = llvm_varitype;
        }

        // 声明全局变量

        for (GlobalVariableDecl *gvari : TU->getGlobalVariableList()) {
            assert(variable_map_[gvari] == nullptr);
            llvm::GlobalVariable *llvm_gvari = Emit(gvari);
            variable_map_[gvari] = llvm_gvari;
        }

        // 声明文件变量

        for (FileVariableDecl *fvari : TU->getFileVariableList()) {
            assert(variable_map_[fvari] == nullptr);
            llvm::GlobalVariable *llvm_fvari = Emit(fvari);
            variable_map_[fvari] = llvm_fvari;
        }

        // 声明函数

        for (FunctorDecl *decl : TU->getFunctorList()) {
            assert(functor_map_[decl] == nullptr);
            llvm::Function *llvm_func = Emit(decl);
            function_map_[decl] = llvm_func;
            functor_map_[decl] = llvm_func->getFunctionType();
        }

        // 定义函数

        for (FunctionDecl *func : TU->getFunctionList()) {
            llvm::Function *llvm_func = Emit(func);
        }

        DebInfoBuilder.finalize();

        // 检查所有函数

        for (auto &item : function_map_) {
            llvm::Function *llvm_function = item.second;
            if (llvm::verifyFunction(*llvm_function, &llvm::outs())) {
                llvm::outs() << "\n\n";
                TheModule->print(llvm::outs(), nullptr);
                assert(false);
                llvm_function->eraseFromParent();
            }
        }

        // 检查整个模块

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

    // endregion
    /*****************************************************************************************************************/
    // region 函数相关

    llvm::Function *NewEmitter::impl_EmitFunctorDecl(FunctorDecl *functorDecl) {

        // 构建形参声明

        bool is_vari_arg = false;
        std::vector<ParameterDecl *> parameters = functorDecl->getParameters();
        if (!parameters.empty() && parameters.back()->isVariParam()) {
            is_vari_arg = true;
            parameters.pop_back();
        }

        std::vector<llvm::Type *> parameter_lltypes;
        for (ParameterDecl *parameter_decl : parameters) {
            llvm::Type *parameter_type = varitype_map_[parameter_decl->type()];
            assert(parameter_type);
            parameter_lltypes.push_back(parameter_type);
        }

        // 构建返回值类型

        llvm::Type *return_type = varitype_map_[functorDecl->getReturnType()];
        assert(return_type);

        // 构建函数原型

        llvm::FunctionType *prototype = llvm::FunctionType::get(return_type, parameter_lltypes, is_vari_arg);
        assert(prototype);

        // 构建函数声明

        const std::string &function_name = functorDecl->getMangling().str();
        llvm::Function *llvm_function = llvm::Function::Create(prototype, llvm::Function::ExternalLinkage, function_name, TheModule);

        // 设置参数名

        unsigned idx = 0;
        for (auto &param : llvm_function->args()) {
            ParameterDecl *parameter = functorDecl->getParameterAt(idx);
            assert(parameter);
            param.setName(parameter->getNameRef().str());
            idx++;
        }

        return llvm_function;

    }

    llvm::AllocaInst *NewEmitter::impl_EmitParameterDecl(ParameterDecl *parameterDecl) {
        llvm::Type *param_type = varitype_map_[parameterDecl->type()];
        assert(param_type);

        // 创建参数在栈内的空间

        llvm::AllocaInst *alloca_param = Builder.CreateAlloca(param_type, nullptr, parameterDecl->getNameRef().str());

        // 将参数值加载到栈内存中

        llvm::Argument *argument = TheFunction->arg_begin() + parameterDecl->getParamIndex();
        Builder.CreateStore(argument, alloca_param);

        return alloca_param;
    }

    llvm::Value *NewEmitter::impl_EmitLocalVariableDecl(LocalVariableDecl *localVariableDecl) {
        llvm::Type *local_vari_type = varitype_map_[localVariableDecl->type()];
        assert(local_vari_type);
        const std::string &name = localVariableDecl->getMangling().str();

        if (!localVariableDecl->isStatic()) {

            // 非静态变量在栈上创建

            llvm::AllocaInst *llvm_local_vari = Builder.CreateAlloca(local_vari_type, nullptr, name);
            llvm_local_vari->setAlignment(4);
            return llvm_local_vari;

        } else {

            // 静态变量作为全局变量创建

            llvm::GlobalVariable *llvm_static_local_vari = CreateGlobalVariable(localVariableDecl->type(), name);
            llvm_static_local_vari->setLinkage(llvm::GlobalValue::LinkageTypes::InternalLinkage);
            return llvm_static_local_vari;

        }
    }

    llvm::Function *NewEmitter::impl_EmitFunctionDecl(FunctionDecl *functionDecl) {
        const std::string &function_name = functionDecl->getMangling().str();
        std::cout << "生成函数：" << function_name << std::endl;

        llvm::Function *llvm_function = function_map_[functionDecl];
        assert(llvm_function);

        // 进入函数体

        TheFunction = llvm_function;
        TheASTFunction = functionDecl;
        llvm::DISubprogram *subprogram_di = RexDbgMgr.CreateFunctionDI(functionDecl, llvm_function);
        llvm_function->setSubprogram(subprogram_di);
        RexDbgMgr.PushLexicalScope(subprogram_di);

        // 开始创建函数体

        llvm::BasicBlock *entry_bb = llvm::BasicBlock::Create(TheContext, "entry", llvm_function);
        Builder.SetInsertPoint(entry_bb);

        // 创建返回值

        llvm::BasicBlock *ret_bb = llvm::BasicBlock::Create(TheContext, "return", llvm_function);
        TheReturnBB = ret_bb;
        llvm::Value *return_value_ptr = nullptr;
        if (!functionDecl->getReturnType()->isVoidType()) {
            llvm::Type *ret_type = varitype_map_[functionDecl->getReturnType()];
            assert(ret_type);
            return_value_ptr = Builder.CreateAlloca(ret_type, nullptr, "ret");
        }
        TheReturnValue = return_value_ptr;

        // 创建参数变量

        for (ParameterDecl *param_vari_item : functionDecl->getParameters()) {
            assert(variable_map_[param_vari_item] == nullptr);
            llvm::Value *param_var = Emit(param_vari_item);
            variable_map_[param_vari_item] = param_var;
        }

        // 创建局部变量

        for (auto &local_vari_item : functionDecl->getLocalVariables()) {
            assert(variable_map_[local_vari_item] == nullptr);
            llvm::Value *local_var = Emit(local_vari_item);
            variable_map_[local_vari_item] = local_var;
        }

        // 处理语句

        BasicBlockRange bb_range = Emit(functionDecl->getFunctionBody());
        assert(bb_range.head && bb_range.tail);

        Builder.SetInsertPoint(entry_bb);
        Builder.CreateBr(bb_range.head);

        // 尾块跳转到返回块

        Builder.SetInsertPoint(bb_range.tail);
        Builder.CreateBr(ret_bb);

        // 检查分支是否收束

        for (llvm::BasicBlock &bb : llvm_function->getBasicBlockList()) {
            if (llvm::succ_size(&bb) == 0 && &bb != ret_bb) {

                // 基本块后继数量为0且不为返回块，表示这是一个悬空的分支尾块，一般情况下是不允许出现的，这会导致CFG错误

                assert(false);
            }
        }

        // 创建返回语句

        Builder.SetInsertPoint(ret_bb);
        if (!functionDecl->getReturnType()->isVoidType()) {
            llvm::Value *return_value = Builder.CreateLoad(return_value_ptr);
            Builder.CreateRet(return_value);
        } else {
            Builder.CreateRetVoid();
        }

        // 离开函数体

        DebInfoBuilder.finalizeSubprogram(subprogram_di);

        // 清理上下文

        TheASTFunction  = nullptr ;
        TheFunction     = nullptr ;
        TheReturnBB     = nullptr ;
        TheReturnValue  = nullptr ;

        RexDbgMgr.PopLexicalScope();

        return llvm_function;
    }

    // endregion
    /*****************************************************************************************************************/
    // region 语句相关

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitStatement(Statement *statement) {
        BasicBlockRange bb_range = EmitNavigate<
                BasicBlockRange
                , Statement
                , AssignStmt
                , ContinueStmt
                , BreakStmt
                , ReturnStmt
                , ExitStmt
                , IfStmt
                , WhileStmt
                , RangeForStmt
                , ForStmt
                , DoWhileStmt
                , StatementBlock
                >(statement);
        return bb_range;
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitAssignStmt(AssignStmt *assignStmt) {
        // TODO:
        return NewEmitter::BasicBlockRange();
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitContinueStmt(ContinueStmt *continueStmt) {
        // TODO:
        return NewEmitter::BasicBlockRange();
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitBreakStmt(BreakStmt *breakStmt) {
        // TODO:
        return NewEmitter::BasicBlockRange();
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitReturnStmt(ReturnStmt *returnStmt) {
        // TODO:
        return NewEmitter::BasicBlockRange();
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitExitStmt(ExitStmt *exitStmt) {
        // TODO:
        return NewEmitter::BasicBlockRange();
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitIfStmt(IfStmt *ifStmt) {
        // TODO:
        return NewEmitter::BasicBlockRange();
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitWhileStmt(WhileStmt *whileStmt) {
        // TODO:
        return NewEmitter::BasicBlockRange();
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitRangeForStmt(RangeForStmt *rangeForStmt) {
        // TODO:
        return NewEmitter::BasicBlockRange();
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitForStmt(ForStmt *forStmt) {
        // TODO:
        return NewEmitter::BasicBlockRange();
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitDoWhileStmt(DoWhileStmt *doWhileStmt) {
        // TODO:
        return NewEmitter::BasicBlockRange();
    }

    NewEmitter::BasicBlockRange NewEmitter::impl_EmitStatementBlock(StatementBlock *statementBlock) {
        llvm::BasicBlock *bb = llvm::BasicBlock::Create(TheContext, "", TheFunction);
        // TODO:
        return NewEmitter::BasicBlockRange{bb, bb};
    }
    // endregion
    /*****************************************************************************************************************/
    // region 表达式相关

    llvm::Value *NewEmitter::impl_EmitExpression(Expression *expression) {
        llvm::Value *value = EmitNavigate<
                llvm::Value *
                , Expression
                , NameComponent
                , TypeConvert
                , UnaryExpression
                , BinaryExpression
                , ValueOfDataSet
                , ValueOfDatetime
                , ValueOfBool
                , ValueOfDecimal
                , ValueOfString
                >(expression);
        return value;
    }

    llvm::Value *NewEmitter::impl_EmitNameComponent(NameComponent *nameComponent) {
        llvm::Value *value = EmitNavigate<
                llvm::Value *
                , NameComponent
                , IdentRefer
                , ArrayIndex
                , FunctionCall
                >(nameComponent);
        return value;
    }

    llvm::Value *NewEmitter::impl_EmitIdentRefer(IdentRefer *identRefer) {
        NameComponent *forward = identRefer->prefix();
        assert(forward == nullptr);     // TODO: 先不支持结构体

        // 具名对象可能是：全局变量、文件变量、局部变量、函数

        TagDecl *decl = identRefer->def()->decl();
        assert(decl);
        if (GlobalVariableDecl *gvari = rtti::dyn_cast<GlobalVariableDecl>(decl)) {
            llvm::Value *v = variable_map_[gvari];
            assert(v);
            return v;
        }
        else if (FileVariableDecl *fvari = rtti::dyn_cast<FileVariableDecl>(decl)) {
            llvm::Value *v = variable_map_[fvari];
            assert(v);
            return v;
        }
        else if (LocalVariableDecl *lvari = rtti::dyn_cast<LocalVariableDecl>(decl)) {
            llvm::Value *v = variable_map_[lvari];
            assert(v);
            return v;
        }
        else if (MemberVariableDecl *mvari = rtti::dyn_cast<MemberVariableDecl>(decl)) {
            assert(false);
            return nullptr;
        }
        else if (ParameterDecl *pvari = rtti::dyn_cast<ParameterDecl>(decl)) {
            llvm::Value *v = variable_map_[pvari];
            assert(v);
            return v;
        }
        else if (FunctorDecl *functor = rtti::dyn_cast<FunctorDecl>(decl)) {
            llvm::Function *f = function_map_[functor];
            assert(f);
            return f;
        }
        else {
            assert(false);
        }
        return nullptr;
    }

    llvm::Value *NewEmitter::impl_EmitArrayIndex(ArrayIndex *arrayIndex) {
        assert(false);      // 这个应该在 Lowing 时被处理为 API 调用
        return nullptr;
    }

    llvm::Value *NewEmitter::impl_EmitFunctionCall(FunctionCall *functionCall) {
        NameComponent *callee = functionCall->getName();
        assert(callee);
        llvm::Value *llvm_callee = Emit(callee);
        assert(llvm_callee);

        if (llvm::Function *f = llvm::dyn_cast<llvm::Function>(llvm_callee)) {
            std::vector<llvm::Value *> arguments_ir;
            for (Expression *argument : functionCall->getArguments()) {
                llvm::Value *argument_ir = Emit(argument);
                assert(argument_ir);
                arguments_ir.push_back(argument_ir);
            }

            // TODO: 打包传参

            return Builder.CreateCall(f, arguments_ir);
        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::Value *NewEmitter::impl_EmitTypeConvert(TypeConvert *typeConvert) {
        // 由于目前没有泛型和指针
        // 类型转换主要是数值性类型之间的转换，即：
        // 1、不同长度的整数转换
        // 2、不同长度的浮点转换
        // 3、整数转浮点
        // 4、浮点转整数

        VariTypeDecl *source_ty = rtti::dyn_cast<VariTypeDecl>(typeConvert->getSourceType());
        assert(source_ty);
        llvm::Type *source_llty = varitype_map_[source_ty];
        assert(source_llty);

        VariTypeDecl *target_ty = rtti::dyn_cast<VariTypeDecl>(typeConvert->getTargetType());
        assert(target_ty);
        llvm::Type *target_llty = varitype_map_[target_ty];
        assert(target_llty);

        llvm::Value *value = Emit(typeConvert->getSourceExpr());

        if (source_ty->isNumerical() && target_ty->isNumerical()) {
            if (source_ty->isIntegerCategory() && target_ty->isIntegerCategory()) {
                return Builder.CreateIntCast(value, target_llty, true);
            }
            else if (source_ty->isIntegerCategory() && target_ty->isFloatCategory()) {
                return Builder.CreateSIToFP(value, target_llty);
            }
            else if (source_ty->isFloatCategory() && target_ty->isIntegerCategory()) {
                return Builder.CreateFPToSI(value, target_llty);
            }
            else if (source_ty->isFloatCategory() && target_ty->isFloatCategory()) {
                return Builder.CreateFPCast(value, target_llty);
            }
            else {
                assert(false);
            }
        }
        else {
            assert(false);
        }

        return nullptr;
    }

    llvm::Value *NewEmitter::impl_EmitUnaryExpression(UnaryExpression *unaryExpression) {
        // TODO:
        return nullptr;
    }

    llvm::Value *NewEmitter::impl_EmitBinaryExpression(BinaryExpression *binaryExpression) {
        // TODO:
        return nullptr;
    }

    llvm::Value *NewEmitter::impl_EmitValueOfDataSet(ValueOfDataSet *valueOfDataSet) {
        std::vector<llvm::Constant *> elements;
        for (Expression *element_expr : valueOfDataSet->elements()) {
            llvm::Constant *e = llvm::dyn_cast<llvm::Constant>(Emit(element_expr));
            assert(e->getType()->isIntegerTy(8));
            elements.push_back(e);
        }

        // 创建数组数据

        llvm::ArrayType *arr_ty = llvm::ArrayType::get(Builder.getInt8Ty(), elements.size());
        llvm::Constant *init_val = llvm::ConstantArray::get(arr_ty, elements);
        return init_val;
    }

    llvm::Value *NewEmitter::impl_EmitValueOfDatetime(ValueOfDatetime *valueOfDatetime) {
        return CreateInt(valueOfDatetime->getTime(), 64, false);
    }

    llvm::Value *NewEmitter::impl_EmitValueOfBool(ValueOfBool *valueOfBool) {
        return CreateInt((int) valueOfBool->Value(), 1, false);
    }

    llvm::Value *NewEmitter::impl_EmitValueOfDecimal(ValueOfDecimal *valueOfDecimal) {
        if (valueOfDecimal->isIntValue()) {
            return CreateInt(valueOfDecimal->getAsInt(), 32, true);
        }
        else if (valueOfDecimal->isFloatValue()) {
            return llvm::ConstantFP::get(TheContext, llvm::APFloat(valueOfDecimal->getAsFloat()));
        }
        else {
            assert(false);
            return nullptr;
        }
    }

    llvm::Value *NewEmitter::impl_EmitValueOfString(ValueOfString *valueOfString) {

        // 创建指向字符串常量值的对象，就不需要Load了

        return Builder.CreateGlobalStringPtr(valueOfString->Value().string_.str(), "$.pstr");
    }

    // endregion
    /*****************************************************************************************************************/
    // region 类型相关
    llvm::Type *NewEmitter::impl_EmitVariTypeDecl(VariTypeDecl *type) {
        llvm::Type *ty = EmitNavigate<
                llvm::Type *
                , VariTypeDecl
                , BuiltinVoidType
//                , BuiltinCommonType
                , BuiltinCharType
                , BuiltinIntegerType
                , BuiltinFloatType
                , BuiltinBoolType
//                , BuiltinStringType
//                , BuiltinDataSetType
                , BuiltinShortType
                , BuiltinLongType
                , BuiltinDatetimeType
                , BuiltinFuncPtrType
                , BuiltinDoubleType
                , ReferenceType
//                , StructureDecl
//                , ArrayType
                >(type);
        return ty;
    }

    llvm::Type *NewEmitter::impl_EmitBuiltinVoidType    (BuiltinVoidType     *builtinVoidType    ) {                return Builder.getVoidTy   (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinCommonType  (BuiltinCommonType   *builtinCommonType  ) { assert(false); return Builder.getInt64Ty  (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinCharType    (BuiltinCharType     *builtinCharType    ) {                return Builder.getInt8Ty   (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinIntegerType (BuiltinIntegerType  *builtinIntegerType ) {                return Builder.getInt32Ty  (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinFloatType   (BuiltinFloatType    *builtinFloatType   ) {                return Builder.getFloatTy  (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinBoolType    (BuiltinBoolType     *builtinBoolType    ) {                return Builder.getInt1Ty   (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinStringType  (BuiltinStringType   *builtinStringType  ) { assert(false); return Builder.getInt64Ty  (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinDataSetType (BuiltinDataSetType  *builtinDataSetType ) { assert(false); return Builder.getInt64Ty  (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinShortType   (BuiltinShortType    *builtinShortType   ) {                return Builder.getInt16Ty  (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinLongType    (BuiltinLongType     *builtinLongType    ) {                return Builder.getInt64Ty  (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinDatetimeType(BuiltinDatetimeType *builtinDatetimeType) {                return Builder.getInt64Ty  (); }
    llvm::Type *NewEmitter::impl_EmitBuiltinFuncPtrType (BuiltinFuncPtrType  *builtinFuncPtrType ) {                return Builder.getInt8PtrTy(); }
    llvm::Type *NewEmitter::impl_EmitBuiltinDoubleType  (BuiltinDoubleType   *builtinDoubleType  ) {                return Builder.getDoubleTy (); }
    llvm::Type *NewEmitter::impl_EmitStructureDecl      (StructureDecl       *structureDecl      ) { assert(false); return Builder.getInt64Ty  (); }
    llvm::Type *NewEmitter::impl_EmitArrayType          (ArrayType           *arrayType          ) { assert(false); return Builder.getInt64Ty  (); }

    llvm::Type *NewEmitter::impl_EmitReferenceType(ReferenceType *referenceType) {
        VariTypeDecl *vari_ty = rtti::dyn_cast<VariTypeDecl>(referenceType->getPointee());
        assert(vari_ty);
        return Emit(vari_ty)->getPointerTo();
    }

    // endregion
    /*****************************************************************************************************************/
}
