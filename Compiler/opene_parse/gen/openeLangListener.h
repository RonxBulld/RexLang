
// Generated from /mnt/d/Project/OpenELanguage/Compiler/opene_parse/openeLang.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "openeLangParser.h"


namespace opene {

/**
 * This interface defines an abstract listener for a parse tree produced by openeLangParser.
 */
class  openeLangListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterOpene_src(openeLangParser::Opene_srcContext *ctx) = 0;
  virtual void exitOpene_src(openeLangParser::Opene_srcContext *ctx) = 0;

  virtual void enterSrc_content(openeLangParser::Src_contentContext *ctx) = 0;
  virtual void exitSrc_content(openeLangParser::Src_contentContext *ctx) = 0;

  virtual void enterProgram_set_file(openeLangParser::Program_set_fileContext *ctx) = 0;
  virtual void exitProgram_set_file(openeLangParser::Program_set_fileContext *ctx) = 0;

  virtual void enterData_structure_file(openeLangParser::Data_structure_fileContext *ctx) = 0;
  virtual void exitData_structure_file(openeLangParser::Data_structure_fileContext *ctx) = 0;

  virtual void enterGlobal_variable_file(openeLangParser::Global_variable_fileContext *ctx) = 0;
  virtual void exitGlobal_variable_file(openeLangParser::Global_variable_fileContext *ctx) = 0;

  virtual void enterDll_define_file(openeLangParser::Dll_define_fileContext *ctx) = 0;
  virtual void exitDll_define_file(openeLangParser::Dll_define_fileContext *ctx) = 0;

  virtual void enterDll_command(openeLangParser::Dll_commandContext *ctx) = 0;
  virtual void exitDll_command(openeLangParser::Dll_commandContext *ctx) = 0;

  virtual void enterGlobal_variable_list(openeLangParser::Global_variable_listContext *ctx) = 0;
  virtual void exitGlobal_variable_list(openeLangParser::Global_variable_listContext *ctx) = 0;

  virtual void enterGlobal_variable_item(openeLangParser::Global_variable_itemContext *ctx) = 0;
  virtual void exitGlobal_variable_item(openeLangParser::Global_variable_itemContext *ctx) = 0;

  virtual void enterEdition_spec(openeLangParser::Edition_specContext *ctx) = 0;
  virtual void exitEdition_spec(openeLangParser::Edition_specContext *ctx) = 0;

  virtual void enterStruct_declare(openeLangParser::Struct_declareContext *ctx) = 0;
  virtual void exitStruct_declare(openeLangParser::Struct_declareContext *ctx) = 0;

  virtual void enterTable_comment(openeLangParser::Table_commentContext *ctx) = 0;
  virtual void exitTable_comment(openeLangParser::Table_commentContext *ctx) = 0;

  virtual void enterProg_set(openeLangParser::Prog_setContext *ctx) = 0;
  virtual void exitProg_set(openeLangParser::Prog_setContext *ctx) = 0;

  virtual void enterVariable_decl(openeLangParser::Variable_declContext *ctx) = 0;
  virtual void exitVariable_decl(openeLangParser::Variable_declContext *ctx) = 0;

  virtual void enterSub_program(openeLangParser::Sub_programContext *ctx) = 0;
  virtual void exitSub_program(openeLangParser::Sub_programContext *ctx) = 0;

  virtual void enterParameter_decl(openeLangParser::Parameter_declContext *ctx) = 0;
  virtual void exitParameter_decl(openeLangParser::Parameter_declContext *ctx) = 0;

  virtual void enterStatement_list(openeLangParser::Statement_listContext *ctx) = 0;
  virtual void exitStatement_list(openeLangParser::Statement_listContext *ctx) = 0;

  virtual void enterConditionStatement(openeLangParser::ConditionStatementContext *ctx) = 0;
  virtual void exitConditionStatement(openeLangParser::ConditionStatementContext *ctx) = 0;

  virtual void enterAssignStatement(openeLangParser::AssignStatementContext *ctx) = 0;
  virtual void exitAssignStatement(openeLangParser::AssignStatementContext *ctx) = 0;

  virtual void enterExpressionStatement(openeLangParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(openeLangParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterLoopStatement(openeLangParser::LoopStatementContext *ctx) = 0;
  virtual void exitLoopStatement(openeLangParser::LoopStatementContext *ctx) = 0;

  virtual void enterSwitchStatement(openeLangParser::SwitchStatementContext *ctx) = 0;
  virtual void exitSwitchStatement(openeLangParser::SwitchStatementContext *ctx) = 0;

  virtual void enterSwitch_statement(openeLangParser::Switch_statementContext *ctx) = 0;
  virtual void exitSwitch_statement(openeLangParser::Switch_statementContext *ctx) = 0;

  virtual void enterWhile(openeLangParser::WhileContext *ctx) = 0;
  virtual void exitWhile(openeLangParser::WhileContext *ctx) = 0;

  virtual void enterRangeFor(openeLangParser::RangeForContext *ctx) = 0;
  virtual void exitRangeFor(openeLangParser::RangeForContext *ctx) = 0;

  virtual void enterFor(openeLangParser::ForContext *ctx) = 0;
  virtual void exitFor(openeLangParser::ForContext *ctx) = 0;

  virtual void enterDoWhile(openeLangParser::DoWhileContext *ctx) = 0;
  virtual void exitDoWhile(openeLangParser::DoWhileContext *ctx) = 0;

  virtual void enterIfStmt(openeLangParser::IfStmtContext *ctx) = 0;
  virtual void exitIfStmt(openeLangParser::IfStmtContext *ctx) = 0;

  virtual void enterIfTrueStmt(openeLangParser::IfTrueStmtContext *ctx) = 0;
  virtual void exitIfTrueStmt(openeLangParser::IfTrueStmtContext *ctx) = 0;

  virtual void enterHierarchy_identifier(openeLangParser::Hierarchy_identifierContext *ctx) = 0;
  virtual void exitHierarchy_identifier(openeLangParser::Hierarchy_identifierContext *ctx) = 0;

  virtual void enterFuncCall(openeLangParser::FuncCallContext *ctx) = 0;
  virtual void exitFuncCall(openeLangParser::FuncCallContext *ctx) = 0;

  virtual void enterIdentifier(openeLangParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(openeLangParser::IdentifierContext *ctx) = 0;

  virtual void enterArrayIndex(openeLangParser::ArrayIndexContext *ctx) = 0;
  virtual void exitArrayIndex(openeLangParser::ArrayIndexContext *ctx) = 0;

  virtual void enterBracket(openeLangParser::BracketContext *ctx) = 0;
  virtual void exitBracket(openeLangParser::BracketContext *ctx) = 0;

  virtual void enterOptElement(openeLangParser::OptElementContext *ctx) = 0;
  virtual void exitOptElement(openeLangParser::OptElementContext *ctx) = 0;

  virtual void enterBinaryExpr(openeLangParser::BinaryExprContext *ctx) = 0;
  virtual void exitBinaryExpr(openeLangParser::BinaryExprContext *ctx) = 0;

  virtual void enterUnaryExpr(openeLangParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(openeLangParser::UnaryExprContext *ctx) = 0;

  virtual void enterData_set_value(openeLangParser::Data_set_valueContext *ctx) = 0;
  virtual void exitData_set_value(openeLangParser::Data_set_valueContext *ctx) = 0;

  virtual void enterDatetime_value(openeLangParser::Datetime_valueContext *ctx) = 0;
  virtual void exitDatetime_value(openeLangParser::Datetime_valueContext *ctx) = 0;

  virtual void enterDatetimePureNumber(openeLangParser::DatetimePureNumberContext *ctx) = 0;
  virtual void exitDatetimePureNumber(openeLangParser::DatetimePureNumberContext *ctx) = 0;

  virtual void enterDatetimeSeparateByChinese(openeLangParser::DatetimeSeparateByChineseContext *ctx) = 0;
  virtual void exitDatetimeSeparateByChinese(openeLangParser::DatetimeSeparateByChineseContext *ctx) = 0;

  virtual void enterDatetimeSeparateBySlash(openeLangParser::DatetimeSeparateBySlashContext *ctx) = 0;
  virtual void exitDatetimeSeparateBySlash(openeLangParser::DatetimeSeparateBySlashContext *ctx) = 0;

  virtual void enterDatetimeSeparateBySlashColon(openeLangParser::DatetimeSeparateBySlashColonContext *ctx) = 0;
  virtual void exitDatetimeSeparateBySlashColon(openeLangParser::DatetimeSeparateBySlashColonContext *ctx) = 0;

  virtual void enterDatetimeSeparateByBar(openeLangParser::DatetimeSeparateByBarContext *ctx) = 0;
  virtual void exitDatetimeSeparateByBar(openeLangParser::DatetimeSeparateByBarContext *ctx) = 0;

  virtual void enterDatetimeSeparateByBarColon(openeLangParser::DatetimeSeparateByBarColonContext *ctx) = 0;
  virtual void exitDatetimeSeparateByBarColon(openeLangParser::DatetimeSeparateByBarColonContext *ctx) = 0;

  virtual void enterMacro_value(openeLangParser::Macro_valueContext *ctx) = 0;
  virtual void exitMacro_value(openeLangParser::Macro_valueContext *ctx) = 0;

  virtual void enterFunc_ptr(openeLangParser::Func_ptrContext *ctx) = 0;
  virtual void exitFunc_ptr(openeLangParser::Func_ptrContext *ctx) = 0;

  virtual void enterBool_value(openeLangParser::Bool_valueContext *ctx) = 0;
  virtual void exitBool_value(openeLangParser::Bool_valueContext *ctx) = 0;

  virtual void enterInt(openeLangParser::IntContext *ctx) = 0;
  virtual void exitInt(openeLangParser::IntContext *ctx) = 0;

  virtual void enterFloat(openeLangParser::FloatContext *ctx) = 0;
  virtual void exitFloat(openeLangParser::FloatContext *ctx) = 0;

  virtual void enterString_value(openeLangParser::String_valueContext *ctx) = 0;
  virtual void exitString_value(openeLangParser::String_valueContext *ctx) = 0;


};

}  // namespace opene
