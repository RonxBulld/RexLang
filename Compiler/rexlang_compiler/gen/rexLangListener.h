
// Generated from /home/rexfield/RexLang/Compiler/rexlang_compiler/rexLang.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "rexLangParser.h"


namespace rexlang {

/**
 * This interface defines an abstract listener for a parse tree produced by rexLangParser.
 */
class  rexLangListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterRexlang_src(rexLangParser::Rexlang_srcContext *ctx) = 0;
  virtual void exitRexlang_src(rexLangParser::Rexlang_srcContext *ctx) = 0;

  virtual void enterSrc_content(rexLangParser::Src_contentContext *ctx) = 0;
  virtual void exitSrc_content(rexLangParser::Src_contentContext *ctx) = 0;

  virtual void enterProgram_set_file(rexLangParser::Program_set_fileContext *ctx) = 0;
  virtual void exitProgram_set_file(rexLangParser::Program_set_fileContext *ctx) = 0;

  virtual void enterData_structure_file(rexLangParser::Data_structure_fileContext *ctx) = 0;
  virtual void exitData_structure_file(rexLangParser::Data_structure_fileContext *ctx) = 0;

  virtual void enterGlobal_variable_file(rexLangParser::Global_variable_fileContext *ctx) = 0;
  virtual void exitGlobal_variable_file(rexLangParser::Global_variable_fileContext *ctx) = 0;

  virtual void enterApi_define_file(rexLangParser::Api_define_fileContext *ctx) = 0;
  virtual void exitApi_define_file(rexLangParser::Api_define_fileContext *ctx) = 0;

  virtual void enterDll_command(rexLangParser::Dll_commandContext *ctx) = 0;
  virtual void exitDll_command(rexLangParser::Dll_commandContext *ctx) = 0;

  virtual void enterLib_command(rexLangParser::Lib_commandContext *ctx) = 0;
  virtual void exitLib_command(rexLangParser::Lib_commandContext *ctx) = 0;

  virtual void enterGlobal_variable_list(rexLangParser::Global_variable_listContext *ctx) = 0;
  virtual void exitGlobal_variable_list(rexLangParser::Global_variable_listContext *ctx) = 0;

  virtual void enterGlobal_variable_item(rexLangParser::Global_variable_itemContext *ctx) = 0;
  virtual void exitGlobal_variable_item(rexLangParser::Global_variable_itemContext *ctx) = 0;

  virtual void enterEdition_spec(rexLangParser::Edition_specContext *ctx) = 0;
  virtual void exitEdition_spec(rexLangParser::Edition_specContext *ctx) = 0;

  virtual void enterStruct_declare(rexLangParser::Struct_declareContext *ctx) = 0;
  virtual void exitStruct_declare(rexLangParser::Struct_declareContext *ctx) = 0;

  virtual void enterTable_comment(rexLangParser::Table_commentContext *ctx) = 0;
  virtual void exitTable_comment(rexLangParser::Table_commentContext *ctx) = 0;

  virtual void enterProg_set(rexLangParser::Prog_setContext *ctx) = 0;
  virtual void exitProg_set(rexLangParser::Prog_setContext *ctx) = 0;

  virtual void enterVariable_decl(rexLangParser::Variable_declContext *ctx) = 0;
  virtual void exitVariable_decl(rexLangParser::Variable_declContext *ctx) = 0;

  virtual void enterMember_vari_decl(rexLangParser::Member_vari_declContext *ctx) = 0;
  virtual void exitMember_vari_decl(rexLangParser::Member_vari_declContext *ctx) = 0;

  virtual void enterFile_vari_decl(rexLangParser::File_vari_declContext *ctx) = 0;
  virtual void exitFile_vari_decl(rexLangParser::File_vari_declContext *ctx) = 0;

  virtual void enterSub_program(rexLangParser::Sub_programContext *ctx) = 0;
  virtual void exitSub_program(rexLangParser::Sub_programContext *ctx) = 0;

  virtual void enterLocal_variable_decl(rexLangParser::Local_variable_declContext *ctx) = 0;
  virtual void exitLocal_variable_decl(rexLangParser::Local_variable_declContext *ctx) = 0;

  virtual void enterParameter_decl_list(rexLangParser::Parameter_decl_listContext *ctx) = 0;
  virtual void exitParameter_decl_list(rexLangParser::Parameter_decl_listContext *ctx) = 0;

  virtual void enterParameter_decl(rexLangParser::Parameter_declContext *ctx) = 0;
  virtual void exitParameter_decl(rexLangParser::Parameter_declContext *ctx) = 0;

  virtual void enterVari_parameter_decl(rexLangParser::Vari_parameter_declContext *ctx) = 0;
  virtual void exitVari_parameter_decl(rexLangParser::Vari_parameter_declContext *ctx) = 0;

  virtual void enterStatement_list(rexLangParser::Statement_listContext *ctx) = 0;
  virtual void exitStatement_list(rexLangParser::Statement_listContext *ctx) = 0;

  virtual void enterConditionStatement(rexLangParser::ConditionStatementContext *ctx) = 0;
  virtual void exitConditionStatement(rexLangParser::ConditionStatementContext *ctx) = 0;

  virtual void enterAssignStatement(rexLangParser::AssignStatementContext *ctx) = 0;
  virtual void exitAssignStatement(rexLangParser::AssignStatementContext *ctx) = 0;

  virtual void enterExpressionStatement(rexLangParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(rexLangParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterLoopStatement(rexLangParser::LoopStatementContext *ctx) = 0;
  virtual void exitLoopStatement(rexLangParser::LoopStatementContext *ctx) = 0;

  virtual void enterSwitchStatement(rexLangParser::SwitchStatementContext *ctx) = 0;
  virtual void exitSwitchStatement(rexLangParser::SwitchStatementContext *ctx) = 0;

  virtual void enterControlStatement(rexLangParser::ControlStatementContext *ctx) = 0;
  virtual void exitControlStatement(rexLangParser::ControlStatementContext *ctx) = 0;

  virtual void enterSwitch_statement(rexLangParser::Switch_statementContext *ctx) = 0;
  virtual void exitSwitch_statement(rexLangParser::Switch_statementContext *ctx) = 0;

  virtual void enterWhile(rexLangParser::WhileContext *ctx) = 0;
  virtual void exitWhile(rexLangParser::WhileContext *ctx) = 0;

  virtual void enterRangeFor(rexLangParser::RangeForContext *ctx) = 0;
  virtual void exitRangeFor(rexLangParser::RangeForContext *ctx) = 0;

  virtual void enterFor(rexLangParser::ForContext *ctx) = 0;
  virtual void exitFor(rexLangParser::ForContext *ctx) = 0;

  virtual void enterDoWhile(rexLangParser::DoWhileContext *ctx) = 0;
  virtual void exitDoWhile(rexLangParser::DoWhileContext *ctx) = 0;

  virtual void enterIfStmt(rexLangParser::IfStmtContext *ctx) = 0;
  virtual void exitIfStmt(rexLangParser::IfStmtContext *ctx) = 0;

  virtual void enterIfTrueStmt(rexLangParser::IfTrueStmtContext *ctx) = 0;
  virtual void exitIfTrueStmt(rexLangParser::IfTrueStmtContext *ctx) = 0;

  virtual void enterContinueStmt(rexLangParser::ContinueStmtContext *ctx) = 0;
  virtual void exitContinueStmt(rexLangParser::ContinueStmtContext *ctx) = 0;

  virtual void enterBreakStmt(rexLangParser::BreakStmtContext *ctx) = 0;
  virtual void exitBreakStmt(rexLangParser::BreakStmtContext *ctx) = 0;

  virtual void enterReturnStmt(rexLangParser::ReturnStmtContext *ctx) = 0;
  virtual void exitReturnStmt(rexLangParser::ReturnStmtContext *ctx) = 0;

  virtual void enterExitStmt(rexLangParser::ExitStmtContext *ctx) = 0;
  virtual void exitExitStmt(rexLangParser::ExitStmtContext *ctx) = 0;

  virtual void enterHierarchy_identifier(rexLangParser::Hierarchy_identifierContext *ctx) = 0;
  virtual void exitHierarchy_identifier(rexLangParser::Hierarchy_identifierContext *ctx) = 0;

  virtual void enterFuncCall(rexLangParser::FuncCallContext *ctx) = 0;
  virtual void exitFuncCall(rexLangParser::FuncCallContext *ctx) = 0;

  virtual void enterIdentifier(rexLangParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(rexLangParser::IdentifierContext *ctx) = 0;

  virtual void enterArrayIndex(rexLangParser::ArrayIndexContext *ctx) = 0;
  virtual void exitArrayIndex(rexLangParser::ArrayIndexContext *ctx) = 0;

  virtual void enterBracket(rexLangParser::BracketContext *ctx) = 0;
  virtual void exitBracket(rexLangParser::BracketContext *ctx) = 0;

  virtual void enterOptElement(rexLangParser::OptElementContext *ctx) = 0;
  virtual void exitOptElement(rexLangParser::OptElementContext *ctx) = 0;

  virtual void enterBinaryExpr(rexLangParser::BinaryExprContext *ctx) = 0;
  virtual void exitBinaryExpr(rexLangParser::BinaryExprContext *ctx) = 0;

  virtual void enterUnaryExpr(rexLangParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(rexLangParser::UnaryExprContext *ctx) = 0;

  virtual void enterData_set_value(rexLangParser::Data_set_valueContext *ctx) = 0;
  virtual void exitData_set_value(rexLangParser::Data_set_valueContext *ctx) = 0;

  virtual void enterDatetime_value(rexLangParser::Datetime_valueContext *ctx) = 0;
  virtual void exitDatetime_value(rexLangParser::Datetime_valueContext *ctx) = 0;

  virtual void enterDatetimePureNumber(rexLangParser::DatetimePureNumberContext *ctx) = 0;
  virtual void exitDatetimePureNumber(rexLangParser::DatetimePureNumberContext *ctx) = 0;

  virtual void enterDatetimeSeparateByChinese(rexLangParser::DatetimeSeparateByChineseContext *ctx) = 0;
  virtual void exitDatetimeSeparateByChinese(rexLangParser::DatetimeSeparateByChineseContext *ctx) = 0;

  virtual void enterDatetimeSeparateBySlash(rexLangParser::DatetimeSeparateBySlashContext *ctx) = 0;
  virtual void exitDatetimeSeparateBySlash(rexLangParser::DatetimeSeparateBySlashContext *ctx) = 0;

  virtual void enterDatetimeSeparateBySlashColon(rexLangParser::DatetimeSeparateBySlashColonContext *ctx) = 0;
  virtual void exitDatetimeSeparateBySlashColon(rexLangParser::DatetimeSeparateBySlashColonContext *ctx) = 0;

  virtual void enterDatetimeSeparateByBar(rexLangParser::DatetimeSeparateByBarContext *ctx) = 0;
  virtual void exitDatetimeSeparateByBar(rexLangParser::DatetimeSeparateByBarContext *ctx) = 0;

  virtual void enterDatetimeSeparateByBarColon(rexLangParser::DatetimeSeparateByBarColonContext *ctx) = 0;
  virtual void exitDatetimeSeparateByBarColon(rexLangParser::DatetimeSeparateByBarColonContext *ctx) = 0;

  virtual void enterMacro_value(rexLangParser::Macro_valueContext *ctx) = 0;
  virtual void exitMacro_value(rexLangParser::Macro_valueContext *ctx) = 0;

  virtual void enterFunc_ptr(rexLangParser::Func_ptrContext *ctx) = 0;
  virtual void exitFunc_ptr(rexLangParser::Func_ptrContext *ctx) = 0;

  virtual void enterBoolValueTrue(rexLangParser::BoolValueTrueContext *ctx) = 0;
  virtual void exitBoolValueTrue(rexLangParser::BoolValueTrueContext *ctx) = 0;

  virtual void enterBoolValueFalse(rexLangParser::BoolValueFalseContext *ctx) = 0;
  virtual void exitBoolValueFalse(rexLangParser::BoolValueFalseContext *ctx) = 0;

  virtual void enterInt(rexLangParser::IntContext *ctx) = 0;
  virtual void exitInt(rexLangParser::IntContext *ctx) = 0;

  virtual void enterFloat(rexLangParser::FloatContext *ctx) = 0;
  virtual void exitFloat(rexLangParser::FloatContext *ctx) = 0;

  virtual void enterString_value(rexLangParser::String_valueContext *ctx) = 0;
  virtual void exitString_value(rexLangParser::String_valueContext *ctx) = 0;


};

}  // namespace rexlang
