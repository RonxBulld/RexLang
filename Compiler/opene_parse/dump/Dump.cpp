//
// Created by rex on 2020/1/22.
//

#include "Dump.h"

namespace opene {

    struct DumpToken {
        std::string node_name;
        void *node_ptr = nullptr;
        size_t line = 0, column = 0;
        std::map<std::string, std::string> attributes;
        std::string comment;
    };

    std::vector<std::string> DumpTranslateUnit(TranslateUnitPtr *translateUnitPtr, const DumpStyle &dumpStyle) {
        DumpToken dump_token;
        dump_token.node_name = "TranslateUnit";
        dump_token.node_ptr = translateUnitPtr;
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpSourceFile(SourceFilePtr *sourceFilePtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpProgramSetFile(ProgramSetFilePtr *programSetFilePtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpGlobalVariableFile(GlobalVariableFilePtr *globalVariableFilePtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpDataStructureFile(DataStructureFilePtr *dataStructureFilePtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpDllDefineFile(DllDefineFilePtr *dllDefineFilePtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpDecl(DeclPtr *declPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpTagDecl(TagDeclPtr *tagDeclPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpGlobalVariableDecl(GlobalVariableDeclPtr *globalVariableDeclPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpVariableDecl(VariableDeclPtr *variableDeclPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpParameterDecl(ParameterDeclPtr *parameterDeclPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpStructureDecl(StructureDeclPtr *structureDeclPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpSubProgDecl(FunctionDeclPtr *subProgDeclPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpProgSetDecl(ProgSetDeclPtr *progSetDeclPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpDllCommandDecl(DllCommandDeclPtr *dllCommandDeclPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpStatement(StatementPtr *statementPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpIfStmt(IfStmtPtr *ifStmtPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpStatementList(StatementListPtr *statementListPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpWhileStmt(WhileStmtPtr *whileStmtPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpRangeForStmt(RangeForStmtPtr *rangeForStmtPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpForStmt(ForStmtPtr *forStmtPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpDoWhileStmt(DoWhileStmtPtr *doWhileStmtPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpAssignStmt(AssignStmtPtr *assignStmtPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpExpression(ExpressionPtr *expressionPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpHierarchyIdentifier(HierarchyIdentifierPtr *hierarchyIdentifierPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpNameComponent(NameComponentPtr *nameComponentPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpFunctionCall(FunctionCallPtr *functionCallPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpUnaryExpression(UnaryExpressionPtr *unaryExpressionPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpBinaryExpression(BinaryExpressionPtr *binaryExpressionPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> Dump_OperatorExpression(_OperatorExpressionPtr *operatorExpressionPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpValue(ValuePtr *valuePtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpValueOfDataSet(ValueOfDataSetPtr *valueOfDataSetPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpValueOfDatetime(ValueOfDatetimePtr *valueOfDatetimePtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpFuncAddrExpression(FuncAddrExpressionPtr *funcAddrExpressionPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpResourceRefExpression(ResourceRefExpressionPtr *resourceRefExpressionPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpValueOfBool(ValueOfBoolPtr *valueOfBoolPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpValueOfDecimal(ValueOfDecimalPtr *valueOfDecimalPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }

    std::vector<std::string> DumpValueOfString(ValueOfStringPtr *valueOfStringPtr, const DumpStyle &dumpStyle) {
        return std::vector<std::string>();
    }
}