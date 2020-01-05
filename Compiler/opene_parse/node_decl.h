//
// Created by rex on 2020/1/3.
//

#ifndef OPENELANGUAGE_NODE_DECL_H
#define OPENELANGUAGE_NODE_DECL_H

#include <vector>
#include <string>
#include <map>

namespace opene {
    typedef struct TranslateUnit* TranslateUnitPtr;
    typedef struct GlobalVariableDecl* GlobalVariableDeclPtr;
    typedef struct VariableDecl* VariableDeclPtr;
    typedef struct ParameterDecl* ParameterDeclPtr;
    typedef struct StructureDecl* StructureDeclPtr;
    typedef struct SubProgDecl* SubProgDeclPtr;
    typedef struct ProgSetDecl* ProgSetDeclPtr;
    typedef struct DllCommandDecl* DllCommandDeclPtr;
    typedef struct ProgramUnit* ProgramUnitPtr;
    typedef struct Statement* StatementPtr;
    typedef struct IfStmt* IfStmtPtr;
    typedef struct StatementList* StatementListPtr;
    typedef struct WhileStmt* WhileStmtPtr;
    typedef struct Expression* ExpressionPtr;
    typedef struct RangeForStmt* RangeForStmtPtr;
    typedef struct ForStmt* ForStmtPtr;
    typedef struct DoWhileStmt* DoWhileStmtPtr;
    typedef struct HierarchyIdentifier* HierarchyIdentifierPtr;
    typedef struct NameComponent* NameComponentPtr;
    typedef struct FunctionCall* FunctionCallPtr;

    struct TranslateUnit {
        unsigned int edition_ = 0;
    };

    struct GlobalVariableDecl {
        std::string name_;
        std::string type_;
        std::string access_;
        std::string dimension_;
        std::string comment_;
    };

    struct VariableDecl {
        std::string name_;
        std::string type_;
        std::string dimension_;
        std::string comment_;
    };

    struct ParameterDecl {
        std::string name_;
        std::string type_;
        std::vector<std::string> attributes_;
        std::string comment_;
    };

    struct StructureDecl {
        std::string name_;
        std::string access_;
        std::string comment_;
        // TODO: 成员变量定义
    };

    struct Statement {
    };

    struct IfStmt : public Statement {
        std::vector<std::pair<ExpressionPtr, StatementPtr>> switches_;
        StatementPtr default_statement_ = nullptr;
    };

    struct WhileStmt : public Statement {
        ExpressionPtr condition_ = nullptr;
        StatementPtr loop_body_ = nullptr;
    };

    struct RangeForStmt : public Statement {
        ExpressionPtr range_size_ = nullptr;
        std::string loop_vari_;
        StatementPtr loop_body_ = nullptr;
    };

    struct ForStmt : public Statement {
        ExpressionPtr start_value_ = nullptr;
        ExpressionPtr stop_value_ = nullptr;
        ExpressionPtr step_value_ = nullptr;
        HierarchyIdentifierPtr loop_vari_ = nullptr;
    };

    struct DoWhileStmt : public Statement {
        ExpressionPtr conditon_ = nullptr;
        StatementPtr loop_body_ = nullptr;
    };

    struct StatementList : public Statement {
        std::vector<StatementPtr> statements_;
    };

    struct Expression {
    };

    struct HierarchyIdentifier : public Expression {
        std::vector<NameComponentPtr> name_components_;
    };

    struct NameComponent : public Expression {
        std::string name_;
        NameComponentPtr base_ = nullptr;
        ExpressionPtr index_ = nullptr;
    };

    struct FunctionCall : public Expression {
        NameComponentPtr function_name_ = nullptr;
        std::vector<ExpressionPtr> arguments_;
    };

    struct SubProgDecl {
        std::string name_;
        std::string type_;
        std::string access_;
        std::string comment_;
        std::vector<ParameterDeclPtr> parameters_;
        std::map<std::string, VariableDeclPtr> local_vari_;
        // TODO: 语句和表达式列表
    };

    struct ProgSetDecl {
        std::string name_;
        std::string base_;
        std::string access_;
        std::string comment_;
        // TODO: 程序集变量定义
        // TODO: 子程序集定义
    };

    struct DllCommandDecl {
        std::string api_name_;
        std::string type_;
        std::string file_;
        std::string dll_api_name_;
        std::string comment_;
    };

    struct ProgramUnit {
        std::vector<std::string> libraries_;
    };
}

#endif //OPENELANGUAGE_NODE_DECL_H
