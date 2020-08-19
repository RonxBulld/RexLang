
// Generated from /mnt/d/Project/RexLang/Compiler/rexlang_compiler/rexLang.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "rexLangParser.h"


namespace rexlang {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by rexLangParser.
 */
class  rexLangVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by rexLangParser.
   */
    virtual antlrcpp::Any visitRexlang_src(rexLangParser::Rexlang_srcContext *context) = 0;

    virtual antlrcpp::Any visitSrc_content(rexLangParser::Src_contentContext *context) = 0;

    virtual antlrcpp::Any visitProgram_set_file(rexLangParser::Program_set_fileContext *context) = 0;

    virtual antlrcpp::Any visitData_structure_file(rexLangParser::Data_structure_fileContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_variable_file(rexLangParser::Global_variable_fileContext *context) = 0;

    virtual antlrcpp::Any visitDll_define_file(rexLangParser::Api_define_fileContext *context) = 0;

    virtual antlrcpp::Any visitDll_command(rexLangParser::Dll_commandContext *context) = 0;

    virtual antlrcpp::Any visitLib_command(rexLangParser::Lib_commandContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_variable_list(rexLangParser::Global_variable_listContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_variable_item(rexLangParser::Global_variable_itemContext *context) = 0;

    virtual antlrcpp::Any visitEdition_spec(rexLangParser::Edition_specContext *context) = 0;

    virtual antlrcpp::Any visitStruct_declare(rexLangParser::Struct_declareContext *context) = 0;

    virtual antlrcpp::Any visitTable_comment(rexLangParser::Table_commentContext *context) = 0;

    virtual antlrcpp::Any visitProg_set(rexLangParser::Prog_setContext *context) = 0;

    virtual antlrcpp::Any visitVariable_decl(rexLangParser::Variable_declContext *context) = 0;

    virtual antlrcpp::Any visitMember_vari_decl(rexLangParser::Member_vari_declContext *context) = 0;

    virtual antlrcpp::Any visitFile_vari_decl(rexLangParser::File_vari_declContext *context) = 0;

    virtual antlrcpp::Any visitSub_program(rexLangParser::Sub_programContext *context) = 0;

    virtual antlrcpp::Any visitLocal_variable_decl(rexLangParser::Local_variable_declContext *context) = 0;

    virtual antlrcpp::Any visitParameter_decl_list(rexLangParser::Parameter_decl_listContext *context) = 0;

    virtual antlrcpp::Any visitParameter_decl(rexLangParser::Parameter_declContext *context) = 0;

    virtual antlrcpp::Any visitVari_parameter_decl(rexLangParser::Vari_parameter_declContext *context) = 0;

    virtual antlrcpp::Any visitStatement_list(rexLangParser::Statement_listContext *context) = 0;

    virtual antlrcpp::Any visitConditionStatement(rexLangParser::ConditionStatementContext *context) = 0;

    virtual antlrcpp::Any visitAssignStatement(rexLangParser::AssignStatementContext *context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(rexLangParser::ExpressionStatementContext *context) = 0;

    virtual antlrcpp::Any visitLoopStatement(rexLangParser::LoopStatementContext *context) = 0;

    virtual antlrcpp::Any visitSwitchStatement(rexLangParser::SwitchStatementContext *context) = 0;

    virtual antlrcpp::Any visitControlStatement(rexLangParser::ControlStatementContext *context) = 0;

    virtual antlrcpp::Any visitSwitch_statement(rexLangParser::Switch_statementContext *context) = 0;

    virtual antlrcpp::Any visitWhile(rexLangParser::WhileContext *context) = 0;

    virtual antlrcpp::Any visitRangeFor(rexLangParser::RangeForContext *context) = 0;

    virtual antlrcpp::Any visitFor(rexLangParser::ForContext *context) = 0;

    virtual antlrcpp::Any visitDoWhile(rexLangParser::DoWhileContext *context) = 0;

    virtual antlrcpp::Any visitIfStmt(rexLangParser::IfStmtContext *context) = 0;

    virtual antlrcpp::Any visitIfTrueStmt(rexLangParser::IfTrueStmtContext *context) = 0;

    virtual antlrcpp::Any visitContinueStmt(rexLangParser::ContinueStmtContext *context) = 0;

    virtual antlrcpp::Any visitBreakStmt(rexLangParser::BreakStmtContext *context) = 0;

    virtual antlrcpp::Any visitReturnStmt(rexLangParser::ReturnStmtContext *context) = 0;

    virtual antlrcpp::Any visitExitStmt(rexLangParser::ExitStmtContext *context) = 0;

    virtual antlrcpp::Any visitHierarchy_identifier(rexLangParser::Hierarchy_identifierContext *context) = 0;

    virtual antlrcpp::Any visitFuncCall(rexLangParser::FuncCallContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(rexLangParser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitArrayIndex(rexLangParser::ArrayIndexContext *context) = 0;

    virtual antlrcpp::Any visitBracket(rexLangParser::BracketContext *context) = 0;

    virtual antlrcpp::Any visitOptElement(rexLangParser::OptElementContext *context) = 0;

    virtual antlrcpp::Any visitBinaryExpr(rexLangParser::BinaryExprContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpr(rexLangParser::UnaryExprContext *context) = 0;

    virtual antlrcpp::Any visitData_set_value(rexLangParser::Data_set_valueContext *context) = 0;

    virtual antlrcpp::Any visitDatetime_value(rexLangParser::Datetime_valueContext *context) = 0;

    virtual antlrcpp::Any visitDatetimePureNumber(rexLangParser::DatetimePureNumberContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSeparateByChinese(rexLangParser::DatetimeSeparateByChineseContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSeparateBySlash(rexLangParser::DatetimeSeparateBySlashContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSeparateBySlashColon(rexLangParser::DatetimeSeparateBySlashColonContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSeparateByBar(rexLangParser::DatetimeSeparateByBarContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSeparateByBarColon(rexLangParser::DatetimeSeparateByBarColonContext *context) = 0;

    virtual antlrcpp::Any visitMacro_value(rexLangParser::Macro_valueContext *context) = 0;

    virtual antlrcpp::Any visitFunc_ptr(rexLangParser::Func_ptrContext *context) = 0;

    virtual antlrcpp::Any visitBoolValueTrue(rexLangParser::BoolValueTrueContext *context) = 0;

    virtual antlrcpp::Any visitBoolValueFalse(rexLangParser::BoolValueFalseContext *context) = 0;

    virtual antlrcpp::Any visitInt(rexLangParser::IntContext *context) = 0;

    virtual antlrcpp::Any visitFloat(rexLangParser::FloatContext *context) = 0;

    virtual antlrcpp::Any visitString_value(rexLangParser::String_valueContext *context) = 0;


};

}  // namespace rexlang
