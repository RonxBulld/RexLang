
// Generated from /mnt/e/Project/RexLang/Compiler/rexlang_compiler/rexLang.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "rexLangListener.h"


namespace rexlang {

/**
 * This class provides an empty implementation of rexLangListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  rexLangBaseListener : public rexLangListener {
public:

  virtual void enterRexlang_src(rexLangParser::Rexlang_srcContext * /*ctx*/) override { }
  virtual void exitRexlang_src(rexLangParser::Rexlang_srcContext * /*ctx*/) override { }

  virtual void enterSrc_content(rexLangParser::Src_contentContext * /*ctx*/) override { }
  virtual void exitSrc_content(rexLangParser::Src_contentContext * /*ctx*/) override { }

  virtual void enterProgram_set_file(rexLangParser::Program_set_fileContext * /*ctx*/) override { }
  virtual void exitProgram_set_file(rexLangParser::Program_set_fileContext * /*ctx*/) override { }

  virtual void enterData_structure_file(rexLangParser::Data_structure_fileContext * /*ctx*/) override { }
  virtual void exitData_structure_file(rexLangParser::Data_structure_fileContext * /*ctx*/) override { }

  virtual void enterGlobal_variable_file(rexLangParser::Global_variable_fileContext * /*ctx*/) override { }
  virtual void exitGlobal_variable_file(rexLangParser::Global_variable_fileContext * /*ctx*/) override { }

  virtual void enterDll_define_file(rexLangParser::Dll_define_fileContext * /*ctx*/) override { }
  virtual void exitDll_define_file(rexLangParser::Dll_define_fileContext * /*ctx*/) override { }

  virtual void enterDll_command(rexLangParser::Dll_commandContext * /*ctx*/) override { }
  virtual void exitDll_command(rexLangParser::Dll_commandContext * /*ctx*/) override { }

  virtual void enterLib_command(rexLangParser::Lib_commandContext * /*ctx*/) override { }
  virtual void exitLib_command(rexLangParser::Lib_commandContext * /*ctx*/) override { }

  virtual void enterGlobal_variable_list(rexLangParser::Global_variable_listContext * /*ctx*/) override { }
  virtual void exitGlobal_variable_list(rexLangParser::Global_variable_listContext * /*ctx*/) override { }

  virtual void enterGlobal_variable_item(rexLangParser::Global_variable_itemContext * /*ctx*/) override { }
  virtual void exitGlobal_variable_item(rexLangParser::Global_variable_itemContext * /*ctx*/) override { }

  virtual void enterEdition_spec(rexLangParser::Edition_specContext * /*ctx*/) override { }
  virtual void exitEdition_spec(rexLangParser::Edition_specContext * /*ctx*/) override { }

  virtual void enterStruct_declare(rexLangParser::Struct_declareContext * /*ctx*/) override { }
  virtual void exitStruct_declare(rexLangParser::Struct_declareContext * /*ctx*/) override { }

  virtual void enterTable_comment(rexLangParser::Table_commentContext * /*ctx*/) override { }
  virtual void exitTable_comment(rexLangParser::Table_commentContext * /*ctx*/) override { }

  virtual void enterProg_set(rexLangParser::Prog_setContext * /*ctx*/) override { }
  virtual void exitProg_set(rexLangParser::Prog_setContext * /*ctx*/) override { }

  virtual void enterVariable_decl(rexLangParser::Variable_declContext * /*ctx*/) override { }
  virtual void exitVariable_decl(rexLangParser::Variable_declContext * /*ctx*/) override { }

  virtual void enterMember_vari_decl(rexLangParser::Member_vari_declContext * /*ctx*/) override { }
  virtual void exitMember_vari_decl(rexLangParser::Member_vari_declContext * /*ctx*/) override { }

  virtual void enterFile_vari_decl(rexLangParser::File_vari_declContext * /*ctx*/) override { }
  virtual void exitFile_vari_decl(rexLangParser::File_vari_declContext * /*ctx*/) override { }

  virtual void enterSub_program(rexLangParser::Sub_programContext * /*ctx*/) override { }
  virtual void exitSub_program(rexLangParser::Sub_programContext * /*ctx*/) override { }

  virtual void enterLocal_variable_decl(rexLangParser::Local_variable_declContext * /*ctx*/) override { }
  virtual void exitLocal_variable_decl(rexLangParser::Local_variable_declContext * /*ctx*/) override { }

  virtual void enterParameter_decl_list(rexLangParser::Parameter_decl_listContext * /*ctx*/) override { }
  virtual void exitParameter_decl_list(rexLangParser::Parameter_decl_listContext * /*ctx*/) override { }

  virtual void enterParameter_decl(rexLangParser::Parameter_declContext * /*ctx*/) override { }
  virtual void exitParameter_decl(rexLangParser::Parameter_declContext * /*ctx*/) override { }

  virtual void enterVari_parameter_decl(rexLangParser::Vari_parameter_declContext * /*ctx*/) override { }
  virtual void exitVari_parameter_decl(rexLangParser::Vari_parameter_declContext * /*ctx*/) override { }

  virtual void enterStatement_list(rexLangParser::Statement_listContext * /*ctx*/) override { }
  virtual void exitStatement_list(rexLangParser::Statement_listContext * /*ctx*/) override { }

  virtual void enterConditionStatement(rexLangParser::ConditionStatementContext * /*ctx*/) override { }
  virtual void exitConditionStatement(rexLangParser::ConditionStatementContext * /*ctx*/) override { }

  virtual void enterAssignStatement(rexLangParser::AssignStatementContext * /*ctx*/) override { }
  virtual void exitAssignStatement(rexLangParser::AssignStatementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(rexLangParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(rexLangParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterLoopStatement(rexLangParser::LoopStatementContext * /*ctx*/) override { }
  virtual void exitLoopStatement(rexLangParser::LoopStatementContext * /*ctx*/) override { }

  virtual void enterSwitchStatement(rexLangParser::SwitchStatementContext * /*ctx*/) override { }
  virtual void exitSwitchStatement(rexLangParser::SwitchStatementContext * /*ctx*/) override { }

  virtual void enterControlStatement(rexLangParser::ControlStatementContext * /*ctx*/) override { }
  virtual void exitControlStatement(rexLangParser::ControlStatementContext * /*ctx*/) override { }

  virtual void enterSwitch_statement(rexLangParser::Switch_statementContext * /*ctx*/) override { }
  virtual void exitSwitch_statement(rexLangParser::Switch_statementContext * /*ctx*/) override { }

  virtual void enterWhile(rexLangParser::WhileContext * /*ctx*/) override { }
  virtual void exitWhile(rexLangParser::WhileContext * /*ctx*/) override { }

  virtual void enterRangeFor(rexLangParser::RangeForContext * /*ctx*/) override { }
  virtual void exitRangeFor(rexLangParser::RangeForContext * /*ctx*/) override { }

  virtual void enterFor(rexLangParser::ForContext * /*ctx*/) override { }
  virtual void exitFor(rexLangParser::ForContext * /*ctx*/) override { }

  virtual void enterDoWhile(rexLangParser::DoWhileContext * /*ctx*/) override { }
  virtual void exitDoWhile(rexLangParser::DoWhileContext * /*ctx*/) override { }

  virtual void enterIfStmt(rexLangParser::IfStmtContext * /*ctx*/) override { }
  virtual void exitIfStmt(rexLangParser::IfStmtContext * /*ctx*/) override { }

  virtual void enterIfTrueStmt(rexLangParser::IfTrueStmtContext * /*ctx*/) override { }
  virtual void exitIfTrueStmt(rexLangParser::IfTrueStmtContext * /*ctx*/) override { }

  virtual void enterContinueStmt(rexLangParser::ContinueStmtContext * /*ctx*/) override { }
  virtual void exitContinueStmt(rexLangParser::ContinueStmtContext * /*ctx*/) override { }

  virtual void enterBreakStmt(rexLangParser::BreakStmtContext * /*ctx*/) override { }
  virtual void exitBreakStmt(rexLangParser::BreakStmtContext * /*ctx*/) override { }

  virtual void enterReturnStmt(rexLangParser::ReturnStmtContext * /*ctx*/) override { }
  virtual void exitReturnStmt(rexLangParser::ReturnStmtContext * /*ctx*/) override { }

  virtual void enterExitStmt(rexLangParser::ExitStmtContext * /*ctx*/) override { }
  virtual void exitExitStmt(rexLangParser::ExitStmtContext * /*ctx*/) override { }

  virtual void enterHierarchy_identifier(rexLangParser::Hierarchy_identifierContext * /*ctx*/) override { }
  virtual void exitHierarchy_identifier(rexLangParser::Hierarchy_identifierContext * /*ctx*/) override { }

  virtual void enterFuncCall(rexLangParser::FuncCallContext * /*ctx*/) override { }
  virtual void exitFuncCall(rexLangParser::FuncCallContext * /*ctx*/) override { }

  virtual void enterIdentifier(rexLangParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(rexLangParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterArrayIndex(rexLangParser::ArrayIndexContext * /*ctx*/) override { }
  virtual void exitArrayIndex(rexLangParser::ArrayIndexContext * /*ctx*/) override { }

  virtual void enterBracket(rexLangParser::BracketContext * /*ctx*/) override { }
  virtual void exitBracket(rexLangParser::BracketContext * /*ctx*/) override { }

  virtual void enterOptElement(rexLangParser::OptElementContext * /*ctx*/) override { }
  virtual void exitOptElement(rexLangParser::OptElementContext * /*ctx*/) override { }

  virtual void enterBinaryExpr(rexLangParser::BinaryExprContext * /*ctx*/) override { }
  virtual void exitBinaryExpr(rexLangParser::BinaryExprContext * /*ctx*/) override { }

  virtual void enterUnaryExpr(rexLangParser::UnaryExprContext * /*ctx*/) override { }
  virtual void exitUnaryExpr(rexLangParser::UnaryExprContext * /*ctx*/) override { }

  virtual void enterData_set_value(rexLangParser::Data_set_valueContext * /*ctx*/) override { }
  virtual void exitData_set_value(rexLangParser::Data_set_valueContext * /*ctx*/) override { }

  virtual void enterDatetime_value(rexLangParser::Datetime_valueContext * /*ctx*/) override { }
  virtual void exitDatetime_value(rexLangParser::Datetime_valueContext * /*ctx*/) override { }

  virtual void enterDatetimePureNumber(rexLangParser::DatetimePureNumberContext * /*ctx*/) override { }
  virtual void exitDatetimePureNumber(rexLangParser::DatetimePureNumberContext * /*ctx*/) override { }

  virtual void enterDatetimeSeparateByChinese(rexLangParser::DatetimeSeparateByChineseContext * /*ctx*/) override { }
  virtual void exitDatetimeSeparateByChinese(rexLangParser::DatetimeSeparateByChineseContext * /*ctx*/) override { }

  virtual void enterDatetimeSeparateBySlash(rexLangParser::DatetimeSeparateBySlashContext * /*ctx*/) override { }
  virtual void exitDatetimeSeparateBySlash(rexLangParser::DatetimeSeparateBySlashContext * /*ctx*/) override { }

  virtual void enterDatetimeSeparateBySlashColon(rexLangParser::DatetimeSeparateBySlashColonContext * /*ctx*/) override { }
  virtual void exitDatetimeSeparateBySlashColon(rexLangParser::DatetimeSeparateBySlashColonContext * /*ctx*/) override { }

  virtual void enterDatetimeSeparateByBar(rexLangParser::DatetimeSeparateByBarContext * /*ctx*/) override { }
  virtual void exitDatetimeSeparateByBar(rexLangParser::DatetimeSeparateByBarContext * /*ctx*/) override { }

  virtual void enterDatetimeSeparateByBarColon(rexLangParser::DatetimeSeparateByBarColonContext * /*ctx*/) override { }
  virtual void exitDatetimeSeparateByBarColon(rexLangParser::DatetimeSeparateByBarColonContext * /*ctx*/) override { }

  virtual void enterMacro_value(rexLangParser::Macro_valueContext * /*ctx*/) override { }
  virtual void exitMacro_value(rexLangParser::Macro_valueContext * /*ctx*/) override { }

  virtual void enterFunc_ptr(rexLangParser::Func_ptrContext * /*ctx*/) override { }
  virtual void exitFunc_ptr(rexLangParser::Func_ptrContext * /*ctx*/) override { }

  virtual void enterBoolValueTrue(rexLangParser::BoolValueTrueContext * /*ctx*/) override { }
  virtual void exitBoolValueTrue(rexLangParser::BoolValueTrueContext * /*ctx*/) override { }

  virtual void enterBoolValueFalse(rexLangParser::BoolValueFalseContext * /*ctx*/) override { }
  virtual void exitBoolValueFalse(rexLangParser::BoolValueFalseContext * /*ctx*/) override { }

  virtual void enterInt(rexLangParser::IntContext * /*ctx*/) override { }
  virtual void exitInt(rexLangParser::IntContext * /*ctx*/) override { }

  virtual void enterFloat(rexLangParser::FloatContext * /*ctx*/) override { }
  virtual void exitFloat(rexLangParser::FloatContext * /*ctx*/) override { }

  virtual void enterString_value(rexLangParser::String_valueContext * /*ctx*/) override { }
  virtual void exitString_value(rexLangParser::String_valueContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace rexlang
