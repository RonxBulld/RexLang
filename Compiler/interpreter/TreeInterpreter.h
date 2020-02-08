//
// Created by rex on 2020/2/7.
//

#ifndef OPENELANGUAGE_TREEINTERPRETER_H
#define OPENELANGUAGE_TREEINTERPRETER_H

#include "../opene_compiler/NodeDecl.h"
#include "../opene_compiler/common_rt/ErrOr.h"

namespace opene {

    class TIValue {
    public: // 值分类断言
        bool isNormalValue() const;
        bool isStructureValue() const;

    public: // 内置类型取值
        ErrOr<char>                 getAsChar() const;
        ErrOr<int>                  getAsInteger() const;
        ErrOr<float>                getAsFloat() const;
        ErrOr<bool>                 getAsBool() const;
        ErrOr<std::string>          getAsString() const;
        ErrOr<std::vector<char>>    getAsDataSet() const;
        ErrOr<short>                getAsShort() const;
        ErrOr<long>                 getAsLong() const;
        ErrOr<time_t>               getAsDatetime() const;
        ErrOr<FunctionDecl *>       getAsFuncPtr() const;
        ErrOr<double>               getAsDouble() const;

    public: // 数组对象操作

    public: // 结构体取值
        bool hadMember(const std::string &member_name) const;
        ErrOr<TIValue &> getMember(const std::string &member_name);

    public: // 参数对象操作
        bool isNullObject() const;
    };

    class TIVariable {
    private:
        TIValue value_;
    public:
        TIVariable(VariableDecl *variableDecl);
    };

    class RuntimeContext {
    private:
        std::set<TIVariable *> object_pool_;
        class ContextFragment {
            std::map<BaseVariDecl *, TIVariable *> variable_;
            Statement *execute_ptr_ = nullptr;
        };
        std::vector<ContextFragment> dyn_symbol_table_;
    private:
    public:
        bool AddVariable(BaseVariDecl *variableDecl);
        bool PushStack(TranslateUnit *translateUnit);
        bool PushStack(FunctionDecl *functionDecl);
        bool PopStack();
        TIVariable * QueryVariableObjectFromDynSymbolTable(BaseVariDecl *variableDecl);
        void SetValue(BaseVariDecl *variableDecl, TIValue tiValue);

    public:
        void SetLatestReturnValue(TIValue tiValue);
        TIValue GetLatestReturnValue();

    public:
        void SetExecutePtr(Statement *statement);
        Statement *GetExecutePtr();
    };

    class TreeInterpreter {
    private:
        RuntimeContext runtime_context_;
        TranslateUnit *translate_unit_ = nullptr;
        Statement *execute_statement_ptr_ = nullptr;

    private:    // 变量加载

        bool LoadFunctionFragment(FunctionDecl *functionDecl);

    private:    // 表达式执行
        TIValue CallFunction(FunctorDecl *functorDecl, std::vector<TIValue*> arguments);
        TIValue EvaluateExpression(Expression *expression);

    private:    // 语句执行
        enum class ExecFlag { kSequence, kBreak, kContinue, kReturn, kExit };
        bool ExecAssign(AssignStmt *assignStmt);
        bool ExecLoop(LoopStatement *loopStatement);
        bool ExecControl(ControlStmt *controlStmt);
        bool ExecIf(IfStmt *ifStmt);
        bool ExecStmtBlock(StatementBlock *statementBlock);
        bool ExecStatement(Statement *statement);

    private:
        bool ExecuteCore();

    public:
        /*
         * 加载翻译单元并做初始化
         */
        bool LoadAST(TranslateUnit *translateUnit);

        /*
         * 卸载翻译单元并释放资源
         */
        bool UnloadAST();

        /*
         * 开始执行
         */
        bool Run();
    };

}

#endif //OPENELANGUAGE_TREEINTERPRETER_H
