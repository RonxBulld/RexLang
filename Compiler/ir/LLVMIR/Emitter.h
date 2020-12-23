//
// Created by Administrator on 2020/6/11.
//

#ifndef REXLANG_EMITTER_H
#define REXLANG_EMITTER_H

#include <stack>
#include <llvm/IR/DIBuilder.h>

#include "LLVMRTIRBuilder.h"
#include "DebugInfoMgr.h"

namespace rexlang {

    class IREmit {
    private:
        // 可控结构
        class ControlableStructure {
        private:
            // continue
            llvm::BasicBlock *head_bb   = nullptr;
            llvm::BasicBlock *true_bb   = nullptr;
            llvm::BasicBlock *false_bb  = nullptr;
            llvm::BasicBlock *tail_bb   = nullptr;
        public:
            ControlableStructure(llvm::BasicBlock *headBB, llvm::BasicBlock *trueBB, llvm::BasicBlock *falseBB, llvm::BasicBlock *tailBB);

        public:
            llvm::BasicBlock *  getHeadBB   () const;
            llvm::BasicBlock *  getTrueBB   () const;
            llvm::BasicBlock *  getFalseBB  () const;
            llvm::BasicBlock *  getTailBB   () const;
            void                setHeadBB   (llvm::BasicBlock *headBB);
            void                setTrueBb   (llvm::BasicBlock *trueBB);
            void                setFalseBb  (llvm::BasicBlock *falseBB);
            void                setTailBB   (llvm::BasicBlock *tailBB);
        };

    private:
        llvm::LLVMContext   TheContext          ;               /* 当前上下文(LLVM) */
        llvm::Module *      TheModule           = nullptr;      /* 当前模块(LLVM) */
        llvm::IRBuilder<>   Builder             ;               /* IR构造器 */
        LLVMRTIRBuilder     RTBuilder           ;               /* 运行时IR构造器 */
        llvm::DIBuilder     DebInfoBuilder      ;               /* 调试信息构造器 */
        llvm::Function *    TheFunction         = nullptr;      /* 当前函数(LLVM) */
        llvm::Function *    SysEntryFunc        = nullptr;      /* 系统入口函数 */
        llvm::Function *    InitFunc            = nullptr;      /* 初始化函数 */
        ProgSetDecl *       TheProgramSet       = nullptr;      /* 当前程序集 */
        FunctionDecl *      TheASTFunction      = nullptr;      /* 当前函数 */

    private:
        DebugInfoMgr RexDbgMgr;

        /*************************************************************************
         * 变量表
         * 当从中引用的时候需要注意，取回的是一个引用对象，作为左值使用时需要解引用
         *************************************************************************/
        std::map<BaseVariDecl*, llvm::Value*>           variable_object_pool_;

        std::map<TypeDecl*, llvm::Type*>                type_object_pool_;
        std::map<FunctorDecl*, llvm::Function*>         function_object_pool_;
        std::map<llvm::Function*, llvm::Value*>         function_retptr_map_;
        std::map<llvm::Function*, llvm::BasicBlock*>    function_retbb_map_;
        std::stack<ControlableStructure>                controlable_struct_stack_;

    private:

        /*************************************************************************
         * IR发射事件
         *************************************************************************/

        int OnEmitBegin (Node *astNode);
        int OnEmitEnd   (Node *astNode);

    private:
        llvm::Type *        GetType                     (TypeDecl *typeDecl);
        llvm::Function *    GetFunction                 (const std::string &function_name);
        void                RegistVariableIR            (BaseVariDecl *variable, llvm::Value *variable_ir);
        llvm::Value *       GetVariableIRIFExist        (BaseVariDecl *variable);

    private:
        bool                DefineMainEntryAndInitFunc  ();
        bool                CreateEntryAndInit          (TranslateUnit *translateUnit, llvm::Function *userEntry);
        llvm::BasicBlock *  CreateInitBlock             (const std::string &blockName = "");
        bool                AddInitBlocks               (llvm::BasicBlock *beginBlock, llvm::BasicBlock *endBlock);
        bool                FinishInitBlockInsert       ();

        /*************************************************************************
         * 获取值/变量的正确类型
         *************************************************************************/
        llvm::Type *        GetTrustType        (llvm::Value *value);
        llvm::Type *        GetParameterType    (ParameterDecl *parameterDecl);

        /*************************************************************************
         * 根据请求的变量不同执行不同的操作
         * 注意引用类型的变量的加载需要在函数外处理
         * 参数 - 直接
         * 全局变量 - Builder.CreateLoad
         * 局部变量 - Builder.CreateLoad
         *************************************************************************/
        llvm::Value *       LoadVariable(llvm::Value *variable);

        /*************************************************************************
         * 根据请求的变量不同执行不同的操作
         * 注意引用类型的变量的写入需要在函数外处理
         * 参数 - 直接
         * 全局变量 - Builder.CreateLoad
         * 局部变量 - Builder.CreateLoad
         *************************************************************************/
        bool                        StoreVariable                   (llvm::Value *value, llvm::Value *variable);
        llvm::ConstantInt *         CreateInt                       (int intValue, unsigned int nBits = 32, bool isSigned = false);
        void                        CreateVariableInitialization    (llvm::Value *variable);
        llvm::GlobalVariable *      CreateGlobalVariableAndInit     (TypeDecl *vari_type, const std::string &vari_name);
        llvm::BasicBlock *          BuildConditionFirstLoop         (llvm::Value *startValue, llvm::Value *stopValue, llvm::Value *stepValue, llvm::Value *loopVari, Statement *loopBody);

        /*************************************************************************
         * 从结构体或者对象池中获得变量引用或者函数引用
         *************************************************************************/
        llvm::Value *               GetFromStructOrPool             (llvm::Value *forwardInstance, NameComponent *nameComponent);

        std::vector<llvm::Value*>   EmitArgumentList(FunctionCall *functionCall);
        llvm::Constant *            MakeGlobalConstantByteSet   (const std::vector<llvm::Constant*> &elements);

    private:
        bool                    _EmitImpl_(TranslateUnit *        translateUnit);
        llvm::GlobalVariable *  _EmitImpl_(GlobalVariableDecl *   globalVariableDecl);
        llvm::Value *           _EmitImpl_(ParameterDecl *        parameterDecl);
        llvm::GlobalVariable *  _EmitImpl_(FileVariableDecl *     fileVariableDecl);
        llvm::Value *           _EmitImpl_(LocalVariableDecl *    localVariableDecl);
        llvm::Type *            _EmitImpl_(TypeDecl *             typeDecl);
        llvm::Type *            _EmitImpl_(BuiltinTypeDecl *      builtinTypeDecl);
        llvm::PointerType *     _EmitImpl_(ArrayType *            arrayType);
        llvm::PointerType *     _EmitImpl_(StructureDecl *        structureDecl);
        llvm::Function *        _EmitImpl_(FunctorDecl *          functorDecl);
        llvm::Function *        _EmitImpl_(FunctionDecl *         functionDecl);
        llvm::BasicBlock *      _EmitImpl_(Statement *            statement);
        llvm::BasicBlock *      _EmitImpl_(IfStmt *               ifStmt);
        llvm::BasicBlock *      _EmitImpl_(StatementBlock *       statementBlock);
        llvm::BasicBlock *      _EmitImpl_(LoopStatement *        loopStatement);
        llvm::BasicBlock *      _EmitImpl_(WhileStmt *            whileStmt);
        llvm::BasicBlock *      _EmitImpl_(RangeForStmt *         rangeForStmt);
        llvm::BasicBlock *      _EmitImpl_(ForStmt *              forStmt);
        llvm::BasicBlock *      _EmitImpl_(DoWhileStmt *          doWhileStmt);
        llvm::BasicBlock *      _EmitImpl_(AssignStmt *           assignStmt);
        llvm::BasicBlock *      _EmitImpl_(ControlStmt *          controlStmt);
        llvm::BasicBlock *      _EmitImpl_(LoopControlStmt *      loopControlStmt);
        llvm::BasicBlock *      _EmitImpl_(ContinueStmt *         continueStmt);
        llvm::BasicBlock *      _EmitImpl_(BreakStmt *            breakStmt);
        llvm::BasicBlock *      _EmitImpl_(ReturnStmt *           returnStmt);
        llvm::BasicBlock *      _EmitImpl_(ExitStmt *             exitStmt);
        llvm::Value *           _EmitImpl_(Expression *           expression);
        llvm::Value *           _EmitImpl_(TypeConvert *          typeConvert);
        llvm::Value *           _EmitImpl_(HierarchyIdentifier *  hierarchyIdentifier);
        llvm::Value *           _EmitImpl_(NameComponent *        nameComponent);
        llvm::Value *           _EmitImpl_(UnaryExpression *      unaryExpression);
        llvm::Value *           _EmitImpl_(BinaryExpression *     binaryExpression);
        llvm::Value *           _EmitImpl_(Value *                value);
        llvm::Value *           _EmitImpl_(ValueOfDataSet *       valueOfDataSet);
        llvm::Value *           _EmitImpl_(ValueOfDatetime *      valueOfDatetime);
        llvm::Value *           _EmitImpl_(FuncAddrExpression *   funcAddrExpression);
        llvm::Value *           _EmitImpl_(ValueOfBool *          valueOfBool);
        llvm::Value *           _EmitImpl_(ValueOfDecimal *       valueOfDecimal);
        llvm::Value *           _EmitImpl_(ValueOfString *        valueOfString);

    public:
        bool                    Emit(TranslateUnit *        translateUnit);         //
//        llvm::Value *           Emit(SourceFile *           sourceFile);
//        llvm::Value *           Emit(ProgramSetFile *       programSetFile);
//        llvm::Value *           Emit(GlobalVariableFile *   globalVariableFile);
//        llvm::Value *           Emit(DataStructureFile *    dataStructureFile);
//        llvm::Value *           Emit(APIDeclareFile *        apiDeclareFile);
//        llvm::Value *           Emit(Decl *                 decl);
//        llvm::Value *           Emit(TagDecl *              tagDecl);
//        llvm::Value *           Emit(VariableDecl *         variableDecl);
//        llvm::Value *           Emit(BaseVariDecl *         baseVariDecl);
        llvm::GlobalVariable *  Emit(GlobalVariableDecl *   globalVariableDecl);    //
        llvm::Value *           Emit(ParameterDecl *        parameterDecl);         //
        llvm::GlobalVariable *  Emit(FileVariableDecl *     fileVariableDecl);      //
        llvm::Value *           Emit(LocalVariableDecl *    localVariableDecl);     //

        /*************************************************************************
         * 类型
         *************************************************************************/

        llvm::Type *            Emit(TypeDecl *             typeDecl);              //
        llvm::Type *            Emit(BuiltinTypeDecl *      builtinTypeDecl);       //
        llvm::PointerType *     Emit(ArrayType *            arrayType);             // 创建数组 返回数组指针类型
        llvm::PointerType *     Emit(StructureDecl *        structureDecl);         // 创建结构体定义 返回结构体指针类型
        llvm::Function *        Emit(FunctorDecl *          functorDecl);           // 可调用对象声明 仅声明原型不定义内容
        llvm::Function *        Emit(FunctionDecl *         functionDecl);          //
//        llvm::Function *        Emit(DllCommandDecl *       dllCommandDecl);        //
        llvm::BasicBlock *      Emit(Statement *            statement);             //
        llvm::BasicBlock *      Emit(IfStmt *               ifStmt);                //
        llvm::BasicBlock *      Emit(StatementBlock *       statementBlock);        //
        llvm::BasicBlock *      Emit(LoopStatement *        loopStatement);         //
        llvm::BasicBlock *      Emit(WhileStmt *            whileStmt);             //
        llvm::BasicBlock *      Emit(RangeForStmt *         rangeForStmt);          //
        llvm::BasicBlock *      Emit(ForStmt *              forStmt);               //
        llvm::BasicBlock *      Emit(DoWhileStmt *          doWhileStmt);           //
        llvm::BasicBlock *      Emit(AssignStmt *           assignStmt);            //
        llvm::BasicBlock *      Emit(ControlStmt *          controlStmt);           //
        llvm::BasicBlock *      Emit(LoopControlStmt *      loopControlStmt);       //
        llvm::BasicBlock *      Emit(ContinueStmt *         continueStmt);          //
        llvm::BasicBlock *      Emit(BreakStmt *            breakStmt);             //
        llvm::BasicBlock *      Emit(ReturnStmt *           returnStmt);            //
        llvm::BasicBlock *      Emit(ExitStmt *             exitStmt);              //
        llvm::Value *           Emit(Expression *           expression);            //
        llvm::Value *           Emit(TypeConvert *          typeConvert);           //
        llvm::Value *           Emit(HierarchyIdentifier *  hierarchyIdentifier);   //
        llvm::Value *           Emit(NameComponent *        nameComponent);         //
        llvm::Value *           Emit(UnaryExpression *      unaryExpression);       //
        llvm::Value *           Emit(BinaryExpression *     binaryExpression);      //
        llvm::Value *           Emit(Value *                value);                 //
        llvm::Value *           Emit(ValueOfDataSet *       valueOfDataSet);        //
        llvm::Value *           Emit(ValueOfDatetime *      valueOfDatetime);       //
        llvm::Value *           Emit(FuncAddrExpression *   funcAddrExpression);    //
        llvm::Value *           Emit(ValueOfBool *          valueOfBool);           //
        llvm::Value *           Emit(ValueOfDecimal *       valueOfDecimal);        //
        llvm::Value *           Emit(ValueOfString *        valueOfString);         //

    public:
        IREmit();
        ~IREmit();
        llvm::Module *GetModule();
    };

}

#endif //REXLANG_EMITTER_H
