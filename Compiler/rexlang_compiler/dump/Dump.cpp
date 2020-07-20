//
// Created by rex on 2020/1/22.
//

#include "Dump.h"

namespace rexlang {

    struct DumpToken {
        std::string node_name;
        void *node_ptr = nullptr;
        size_t line = 0, column = 0;
        ordered_map<std::string, std::string> attributes;
        std::string comment;
    };

    DumpToken DumpTranslateUnit(TranslateUnit *translateUnitPtr, const DumpStyle &dumpStyle) {
        DumpToken dump_token;
        dump_token.node_name = "TranslateUnit";
        dump_token.node_ptr = translateUnitPtr;
//        dump_token.line = translateUnitPtr->ast_context_->GetLineNumber(translateUnitPtr->location_start_);
        return dump_token;
    }

    DumpToken DumpSourceFile(SourceFile *sourceFilePtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpProgramSetFile(ProgramSetFile *programSetFilePtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpGlobalVariableFile(GlobalVariableFile *globalVariableFilePtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpDataStructureFile(DataStructureFile *dataStructureFilePtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpDllDefineFile(DllDefineFile *dllDefineFilePtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpDecl(Decl *declPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpTagDecl(TagDecl *tagDeclPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpGlobalVariableDecl(GlobalVariableDecl *globalVariableDeclPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpVariableDecl(VariableDecl *variableDeclPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpParameterDecl(ParameterDecl *parameterDeclPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpStructureDecl(StructureDecl *structureDeclPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpSubProgDecl(FunctionDecl *subProgDeclPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpProgSetDecl(ProgSetDecl *progSetDeclPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpDllCommandDecl(APICommandDecl *dllCommandDeclPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpStatement(Statement *statementPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpIfStmt(IfStmt *ifStmtPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpStatementList(StatementBlock *statementListPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpWhileStmt(WhileStmt *whileStmtPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpRangeForStmt(RangeForStmt *rangeForStmtPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpForStmt(ForStmt *forStmtPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpDoWhileStmt(DoWhileStmt *doWhileStmtPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpAssignStmt(AssignStmt *assignStmtPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpExpression(Expression *expressionPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpHierarchyIdentifier(HierarchyIdentifier *hierarchyIdentifierPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpNameComponent(NameComponent *nameComponentPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpFunctionCall(FunctionCall *functionCallPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpUnaryExpression(UnaryExpression *unaryExpressionPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpBinaryExpression(BinaryExpression *binaryExpressionPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken Dump_OperatorExpression(_OperatorExpression *operatorExpressionPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpValue(Value *valuePtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpValueOfDataSet(ValueOfDataSet *valueOfDataSetPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpValueOfDatetime(ValueOfDatetime *valueOfDatetimePtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpFuncAddrExpression(FuncAddrExpression *funcAddrExpressionPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpResourceRefExpression(ResourceRefExpression *resourceRefExpressionPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpValueOfBool(ValueOfBool *valueOfBoolPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpValueOfDecimal(ValueOfDecimal *valueOfDecimalPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }

    DumpToken DumpValueOfString(ValueOfString *valueOfStringPtr, const DumpStyle &dumpStyle) {
        return DumpToken();
    }
}