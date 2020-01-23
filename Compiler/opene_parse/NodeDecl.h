//
// Created by rex on 2020/1/3.
//

#ifndef OPENELANGUAGE_NODEDECL_H
#define OPENELANGUAGE_NODEDECL_H

#include <vector>
#include <string>
#include <map>
#include <ctime>

#include "ASTContext.h"
#include "TString.h"
#include "TypeDescription.h"

namespace opene {
    // Base
    typedef struct Node* NodePtr;
    // Project
    typedef struct TranslateUnit* TranslateUnitPtr;
    // File
    typedef struct SourceFile* SourceFilePtr;
    typedef struct ProgramSetFile* ProgramSetFilePtr;
    typedef struct GlobalVariableFile* GlobalVariableFilePtr;
    typedef struct DataStructureFile* DataStructureFilePtr;
    typedef struct DllDefineFile* DllDefineFilePtr;
    // Declare
    typedef struct Decl* DeclPtr;
    typedef struct TagDecl* TagDeclPtr;
    typedef struct GlobalVariableDecl* GlobalVariableDeclPtr;
    typedef struct VariableDecl* VariableDeclPtr;
    typedef struct ParameterDecl* ParameterDeclPtr;
    typedef struct StructureDecl* StructureDeclPtr;
    typedef struct SubProgDecl* SubProgDeclPtr;
    typedef struct ProgSetDecl* ProgSetDeclPtr;
    typedef struct DllCommandDecl* DllCommandDeclPtr;
    // Statement
    typedef struct Statement* StatementPtr;
    typedef struct IfStmt* IfStmtPtr;
    typedef struct StatementList* StatementListPtr;
    typedef struct WhileStmt* WhileStmtPtr;
    typedef struct RangeForStmt* RangeForStmtPtr;
    typedef struct ForStmt* ForStmtPtr;
    typedef struct DoWhileStmt* DoWhileStmtPtr;
    typedef struct AssignStmt* AssignStmtPtr;
    // Expression
    typedef struct Expression* ExpressionPtr;
    typedef struct HierarchyIdentifier* HierarchyIdentifierPtr;
    typedef struct NameComponent* NameComponentPtr;
    typedef struct FunctionCall* FunctionCallPtr;
    typedef struct UnaryExpression* UnaryExpressionPtr;
    typedef struct BinaryExpression* BinaryExpressionPtr;
    typedef struct _OperatorExpression* _OperatorExpressionPtr;
    // Value
    typedef struct Value* ValuePtr;
    typedef struct ValueOfDataSet* ValueOfDataSetPtr;
    typedef struct ValueOfDatetime* ValueOfDatetimePtr;
    typedef struct FuncAddrExpression* FuncAddrExpressionPtr;
    typedef struct ResourceRefExpression* ResourceRefExpressionPtr;
    typedef struct ValueOfBool* ValueOfBoolPtr;
    typedef struct ValueOfDecimal* ValueOfDecimalPtr;
    typedef struct ValueOfString* ValueOfStringPtr;

    typedef enum class NodeType {
        kNTyBadType,
        kNTyTranslateUnit,
        kNTySourceFile,
        kNTyProgramSetFile,
        kNTyGlobalVariableFile,
        kNTyDataStructureFile,
        kNTyDllDefineFile,
        kNTyDecl,
        kNTyTagDecl,
        kNTyGlobalVariableDecl,
        kNTyVariableDecl,
        kNTyParameterDecl,
        kNTyStructureDecl,
        kNTySubProgDecl,
        kNTyProgSetDecl,
        kNTyDllCommandDecl,
        kNTyStatement,
        kNTyIfStmt,
        kNTyStatementList,
        kNTyWhileStmt,
        kNTyRangeForStmt,
        kNTyForStmt,
        kNTyDoWhileStmt,
        kNTyAssignStmt,
        kNTyExpression,
        kNTyHierarchyIdentifier,
        kNTyNameComponent,
        kNTyFunctionCall,
        kNTyUnaryExpression,
        kNTyBinaryExpression,
        kNTy_OperatorExpression,
        kNTyValue,
        kNTyValueOfDataSet,
        kNTyValueOfDatetime,
        kNTyFuncAddrExpression,
        kNTyResourceRefExpression,
        kNTyValueOfBool,
        kNTyValueOfDecimal,
        kNTyValueOfString,
    } NodeType;

    struct Node {
        ASTContext *ast_context_ = nullptr;
        NodeType node_type_ = NodeType::kNTyBadType;
        size_t location_start_ = 0, location_end_ = 0;

        template<typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        const Ty *as() const {
            return dynamic_cast<const Ty *>(this);
        }

        template<typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        Ty *as() {
            return dynamic_cast<Ty *>(this);
        }

        virtual ~Node() {
        }
    };

    struct SourceFile : public Node {
        static const NodeType node_type = NodeType::kNTySourceFile;
        enum FileType {kProgramSetFile, kGlobalVariableFile, kDataStructureFile, kDllDefineFile} file_type_;
    };

    struct ProgramSetFile : public SourceFile {
        static const NodeType node_type = NodeType::kNTyProgramSetFile;
        std::vector<TString> libraries_;
        ProgSetDeclPtr program_set_declares_ = nullptr;
    };

    struct GlobalVariableFile : public SourceFile {
        static const NodeType node_type = NodeType::kNTyGlobalVariableFile;
        std::map<TString, GlobalVariableDeclPtr> global_variable_map_;
    };

    struct DataStructureFile : public SourceFile {
        typedef std::map<TString, StructureDeclPtr> ClassureDeclContainerType;
        static const NodeType node_type = NodeType::kNTyDataStructureFile;
        ClassureDeclContainerType structure_decl_map_;
    };

    struct DllDefineFile : public SourceFile {
        static const NodeType node_type = NodeType::kNTyDllDefineFile;
        std::map<TString, DllCommandDeclPtr> dll_declares_;
    };

    struct Decl : public Node {
        static const NodeType node_type = NodeType::kNTyDecl;
    };

    struct TagDecl : public Decl {
        static const NodeType node_type = NodeType::kNTyTagDecl;
        TString name_;
    };

    struct VariableDecl : public TagDecl {
        static const NodeType node_type = NodeType::kNTyVariableDecl;
        TString type_;
        TString dimension_;
        TString comment_;
    };

    struct GlobalVariableDecl : public VariableDecl {
        static const NodeType node_type = NodeType::kNTyGlobalVariableDecl;
        TString access_;
    };

    struct ParameterDecl : public TagDecl  {
        static const NodeType node_type = NodeType::kNTyParameterDecl;
        TString type_;
        std::vector<TString> attributes_;
        TString comment_;
    };

    struct StructureDecl : public TagDecl {
        static const NodeType node_type = NodeType::kNTyStructureDecl;
        TString access_;
        TString comment_;
        std::map<TString, VariableDeclPtr> members_;
    };

    struct SubProgDecl : public TagDecl {
        static const NodeType node_type = NodeType::kNTySubProgDecl;
        TString type_;
        TString access_;
        TString comment_;
        std::vector<ParameterDeclPtr> parameters_;
        std::map<TString, VariableDeclPtr> local_vari_;
        StatementListPtr statement_list_ = nullptr;
    };

    struct ProgSetDecl : public TagDecl {
        static const NodeType node_type = NodeType::kNTyProgSetDecl;
        TString base_;
        TString access_;
        TString comment_;
        std::map<TString, VariableDeclPtr> file_static_variables_;
        std::map<TString, SubProgDeclPtr> function_decls_;
    };

    struct DllCommandDecl : public TagDecl {
        static const NodeType node_type = NodeType::kNTyDllCommandDecl;
        TString type_;
        TString file_;
        TString api_name_;
        std::map<TString, ParameterDeclPtr> parameters_;
        TString comment_;
    };

    struct Statement : public Node {
        static const NodeType node_type = NodeType::kNTyStatement;
    };

    struct AssignStmt : public Statement {
        static const NodeType node_type = NodeType::kNTyAssignStmt;
        HierarchyIdentifierPtr lhs_ = nullptr;
        ExpressionPtr rhs_ = nullptr;
    };

    struct IfStmt : public Statement {
        static const NodeType node_type = NodeType::kNTyIfStmt;
        std::vector<std::pair<ExpressionPtr, StatementPtr>> switches_;
        StatementPtr default_statement_ = nullptr;
    };

    struct WhileStmt : public Statement {
        static const NodeType node_type = NodeType::kNTyWhileStmt;
        ExpressionPtr condition_ = nullptr;
        StatementPtr loop_body_ = nullptr;
    };

    struct RangeForStmt : public Statement {
        static const NodeType node_type = NodeType::kNTyRangeForStmt;
        ExpressionPtr range_size_ = nullptr;
        TString loop_vari_;
        StatementPtr loop_body_ = nullptr;
    };

    struct ForStmt : public Statement {
        static const NodeType node_type = NodeType::kNTyForStmt;
        ExpressionPtr start_value_ = nullptr;
        ExpressionPtr stop_value_ = nullptr;
        ExpressionPtr step_value_ = nullptr;
        HierarchyIdentifierPtr loop_vari_ = nullptr;
    };

    struct DoWhileStmt : public Statement {
        static const NodeType node_type = NodeType::kNTyDoWhileStmt;
        ExpressionPtr conditon_ = nullptr;
        StatementPtr loop_body_ = nullptr;
    };

    struct StatementList : public Statement {
        static const NodeType node_type = NodeType::kNTyStatementList;
        std::vector<StatementPtr> statements_;
    };

    struct Expression : public Statement {
        static const NodeType node_type = NodeType::kNTyExpression;
    };

    struct HierarchyIdentifier : public Expression {
        static const NodeType node_type = NodeType::kNTyHierarchyIdentifier;
        std::vector<NameComponentPtr> name_components_;
    };

    struct NameComponent : public Expression {
        static const NodeType node_type = NodeType::kNTyNameComponent;
        TString name_;
        NameComponentPtr base_ = nullptr;
        ExpressionPtr index_ = nullptr;
    };

    struct FunctionCall : public Expression {
        static const NodeType node_type = NodeType::kNTyFunctionCall;
        NameComponentPtr function_name_ = nullptr;
        std::vector<ExpressionPtr> arguments_;
    };

    struct _OperatorExpression : public Expression {
        static const NodeType node_type = NodeType::kNTy_OperatorExpression;
        TString operator_;
    };

    struct UnaryExpression : public _OperatorExpression {
        static const NodeType node_type = NodeType::kNTyUnaryExpression;
        ExpressionPtr op_value_ = nullptr;
    };

    struct BinaryExpression : public _OperatorExpression {
        static const NodeType node_type = NodeType::kNTyBinaryExpression;
        ExpressionPtr lhs_ = nullptr;
        ExpressionPtr rhs_ = nullptr;
    };

    struct Value : public Expression {
        static const NodeType node_type = NodeType::kNTyValue;
    };

    struct ValueOfDataSet : public Value {
        static const NodeType node_type = NodeType::kNTyValueOfDataSet;
        std::vector<ExpressionPtr> elements_;
    };

    struct ValueOfDatetime : public Value {
        static const NodeType node_type = NodeType::kNTyValueOfDatetime;
        time_t time_ = 0;
    };

    struct ResourceRefExpression : public Expression {
        static const NodeType node_type = NodeType::kNTyResourceRefExpression;
        TString resource_name_;
    };

    struct FuncAddrExpression : public Expression {
        static const NodeType node_type = NodeType::kNTyFuncAddrExpression;
        TString function_name_;
    };

    struct ValueOfBool : public Value {
        static const NodeType node_type = NodeType::kNTyValueOfBool;
        bool value_ = false;
    };

    struct ValueOfDecimal : public Value {
        static const NodeType node_type = NodeType::kNTyValueOfDecimal;
        union {
            int int_val_ = 0;
            float float_val_;
        };
        enum type { kInt, kFloat } type_ = type::kInt;
    };

    struct ValueOfString : public Value {
        static const NodeType node_type = NodeType::kNTyValueOfString;
        TString string_literal_;
    };

    struct TranslateUnit : public Node {
        static const NodeType node_type = NodeType::kNTyTranslateUnit;
        unsigned int edition_ = 0;
        SourceFilePtr source_file_ = nullptr;
        // 下面是经过语义分析后的数据
        std::map<TString, type::TypeDescription*> global_type_;
    };

    struct NodeWarp {
        NodePtr node_;
        explicit NodeWarp(NodePtr node) {
            node_ = node;
        }

        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Node, T>>>
        operator T *() {
            return dynamic_cast<T *>(this->node_);
        }
    };
}

#endif //OPENELANGUAGE_NODEDECL_H
