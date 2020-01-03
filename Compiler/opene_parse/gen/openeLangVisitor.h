
// Generated from /mnt/d/Project/OpenELanguage/Compiler/opene_parse/openeLang.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "openeLangParser.h"


namespace opene {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by openeLangParser.
 */
class  openeLangVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by openeLangParser.
   */
    virtual antlrcpp::Any visitOpene_src(openeLangParser::Opene_srcContext *context) = 0;

    virtual antlrcpp::Any visitSrc_content(openeLangParser::Src_contentContext *context) = 0;

    virtual antlrcpp::Any visitProgram_set_file(openeLangParser::Program_set_fileContext *context) = 0;

    virtual antlrcpp::Any visitData_structure_file(openeLangParser::Data_structure_fileContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_variable_file(openeLangParser::Global_variable_fileContext *context) = 0;

    virtual antlrcpp::Any visitDll_define_file(openeLangParser::Dll_define_fileContext *context) = 0;

    virtual antlrcpp::Any visitDll_command(openeLangParser::Dll_commandContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_variable_list(openeLangParser::Global_variable_listContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_variable_item(openeLangParser::Global_variable_itemContext *context) = 0;

    virtual antlrcpp::Any visitEdition_spec(openeLangParser::Edition_specContext *context) = 0;

    virtual antlrcpp::Any visitStruct_declare(openeLangParser::Struct_declareContext *context) = 0;

    virtual antlrcpp::Any visitTable_comment(openeLangParser::Table_commentContext *context) = 0;

    virtual antlrcpp::Any visitProg_set(openeLangParser::Prog_setContext *context) = 0;

    virtual antlrcpp::Any visitVariable_decl(openeLangParser::Variable_declContext *context) = 0;

    virtual antlrcpp::Any visitSub_program(openeLangParser::Sub_programContext *context) = 0;

    virtual antlrcpp::Any visitParameter_decl(openeLangParser::Parameter_declContext *context) = 0;

    virtual antlrcpp::Any visitStatement_list(openeLangParser::Statement_listContext *context) = 0;

    virtual antlrcpp::Any visitConditionStatement(openeLangParser::ConditionStatementContext *context) = 0;

    virtual antlrcpp::Any visitAssignStatement(openeLangParser::AssignStatementContext *context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(openeLangParser::ExpressionStatementContext *context) = 0;

    virtual antlrcpp::Any visitLoopStatement(openeLangParser::LoopStatementContext *context) = 0;

    virtual antlrcpp::Any visitSwitchStatement(openeLangParser::SwitchStatementContext *context) = 0;

    virtual antlrcpp::Any visitSwitch_statement(openeLangParser::Switch_statementContext *context) = 0;

    virtual antlrcpp::Any visitWhile(openeLangParser::WhileContext *context) = 0;

    virtual antlrcpp::Any visitRangeFor(openeLangParser::RangeForContext *context) = 0;

    virtual antlrcpp::Any visitFor(openeLangParser::ForContext *context) = 0;

    virtual antlrcpp::Any visitDoWhile(openeLangParser::DoWhileContext *context) = 0;

    virtual antlrcpp::Any visitIfStmt(openeLangParser::IfStmtContext *context) = 0;

    virtual antlrcpp::Any visitIfTrueStmt(openeLangParser::IfTrueStmtContext *context) = 0;

    virtual antlrcpp::Any visitHierarchy_identifier(openeLangParser::Hierarchy_identifierContext *context) = 0;

    virtual antlrcpp::Any visitFuncCall(openeLangParser::FuncCallContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(openeLangParser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitArrayIndex(openeLangParser::ArrayIndexContext *context) = 0;

    virtual antlrcpp::Any visitBracket(openeLangParser::BracketContext *context) = 0;

    virtual antlrcpp::Any visitOptElement(openeLangParser::OptElementContext *context) = 0;

    virtual antlrcpp::Any visitBinaryExpr(openeLangParser::BinaryExprContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpr(openeLangParser::UnaryExprContext *context) = 0;

    virtual antlrcpp::Any visitData_set_value(openeLangParser::Data_set_valueContext *context) = 0;

    virtual antlrcpp::Any visitDatetime_value(openeLangParser::Datetime_valueContext *context) = 0;

    virtual antlrcpp::Any visitDatetimePureNumber(openeLangParser::DatetimePureNumberContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSeparateByChinese(openeLangParser::DatetimeSeparateByChineseContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSeparateBySlash(openeLangParser::DatetimeSeparateBySlashContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSeparateBySlashColon(openeLangParser::DatetimeSeparateBySlashColonContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSeparateByBar(openeLangParser::DatetimeSeparateByBarContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSeparateByBarColon(openeLangParser::DatetimeSeparateByBarColonContext *context) = 0;

    virtual antlrcpp::Any visitMacro_value(openeLangParser::Macro_valueContext *context) = 0;

    virtual antlrcpp::Any visitFunc_ptr(openeLangParser::Func_ptrContext *context) = 0;

    virtual antlrcpp::Any visitBool_value(openeLangParser::Bool_valueContext *context) = 0;

    virtual antlrcpp::Any visitInt(openeLangParser::IntContext *context) = 0;

    virtual antlrcpp::Any visitFloat(openeLangParser::FloatContext *context) = 0;

    virtual antlrcpp::Any visitString_value(openeLangParser::String_valueContext *context) = 0;


};

}  // namespace opene
