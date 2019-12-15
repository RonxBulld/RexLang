
// Generated from /mnt/d/Project/OpenELanguage/Compiler/opene_parse/openeLang.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "openeLangListener.h"


namespace opene {

/**
 * This class provides an empty implementation of openeLangListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  openeLangBaseListener : public openeLangListener {
public:

  virtual void enterOpene_src(openeLangParser::Opene_srcContext * /*ctx*/) override { }
  virtual void exitOpene_src(openeLangParser::Opene_srcContext * /*ctx*/) override { }

  virtual void enterSrc_content(openeLangParser::Src_contentContext * /*ctx*/) override { }
  virtual void exitSrc_content(openeLangParser::Src_contentContext * /*ctx*/) override { }

  virtual void enterProgram_set_file(openeLangParser::Program_set_fileContext * /*ctx*/) override { }
  virtual void exitProgram_set_file(openeLangParser::Program_set_fileContext * /*ctx*/) override { }

  virtual void enterData_structure_file(openeLangParser::Data_structure_fileContext * /*ctx*/) override { }
  virtual void exitData_structure_file(openeLangParser::Data_structure_fileContext * /*ctx*/) override { }

  virtual void enterGlobal_variable_file(openeLangParser::Global_variable_fileContext * /*ctx*/) override { }
  virtual void exitGlobal_variable_file(openeLangParser::Global_variable_fileContext * /*ctx*/) override { }

  virtual void enterDll_define_file(openeLangParser::Dll_define_fileContext * /*ctx*/) override { }
  virtual void exitDll_define_file(openeLangParser::Dll_define_fileContext * /*ctx*/) override { }

  virtual void enterDll_command(openeLangParser::Dll_commandContext * /*ctx*/) override { }
  virtual void exitDll_command(openeLangParser::Dll_commandContext * /*ctx*/) override { }

  virtual void enterGlobal_variable_list(openeLangParser::Global_variable_listContext * /*ctx*/) override { }
  virtual void exitGlobal_variable_list(openeLangParser::Global_variable_listContext * /*ctx*/) override { }

  virtual void enterGlobal_variable_item(openeLangParser::Global_variable_itemContext * /*ctx*/) override { }
  virtual void exitGlobal_variable_item(openeLangParser::Global_variable_itemContext * /*ctx*/) override { }

  virtual void enterEdition_spec(openeLangParser::Edition_specContext * /*ctx*/) override { }
  virtual void exitEdition_spec(openeLangParser::Edition_specContext * /*ctx*/) override { }

  virtual void enterStruct_declare(openeLangParser::Struct_declareContext * /*ctx*/) override { }
  virtual void exitStruct_declare(openeLangParser::Struct_declareContext * /*ctx*/) override { }

  virtual void enterTable_comment(openeLangParser::Table_commentContext * /*ctx*/) override { }
  virtual void exitTable_comment(openeLangParser::Table_commentContext * /*ctx*/) override { }

  virtual void enterMember_item(openeLangParser::Member_itemContext * /*ctx*/) override { }
  virtual void exitMember_item(openeLangParser::Member_itemContext * /*ctx*/) override { }

  virtual void enterLibrary_spec(openeLangParser::Library_specContext * /*ctx*/) override { }
  virtual void exitLibrary_spec(openeLangParser::Library_specContext * /*ctx*/) override { }

  virtual void enterProg_set(openeLangParser::Prog_setContext * /*ctx*/) override { }
  virtual void exitProg_set(openeLangParser::Prog_setContext * /*ctx*/) override { }

  virtual void enterProg_set_variable_decl_opt(openeLangParser::Prog_set_variable_decl_optContext * /*ctx*/) override { }
  virtual void exitProg_set_variable_decl_opt(openeLangParser::Prog_set_variable_decl_optContext * /*ctx*/) override { }

  virtual void enterProg_set_variable_decl(openeLangParser::Prog_set_variable_declContext * /*ctx*/) override { }
  virtual void exitProg_set_variable_decl(openeLangParser::Prog_set_variable_declContext * /*ctx*/) override { }

  virtual void enterVariable_decl(openeLangParser::Variable_declContext * /*ctx*/) override { }
  virtual void exitVariable_decl(openeLangParser::Variable_declContext * /*ctx*/) override { }

  virtual void enterSub_program_opt(openeLangParser::Sub_program_optContext * /*ctx*/) override { }
  virtual void exitSub_program_opt(openeLangParser::Sub_program_optContext * /*ctx*/) override { }

  virtual void enterSub_program(openeLangParser::Sub_programContext * /*ctx*/) override { }
  virtual void exitSub_program(openeLangParser::Sub_programContext * /*ctx*/) override { }

  virtual void enterParameter_decl(openeLangParser::Parameter_declContext * /*ctx*/) override { }
  virtual void exitParameter_decl(openeLangParser::Parameter_declContext * /*ctx*/) override { }

  virtual void enterLocal_variable_decl(openeLangParser::Local_variable_declContext * /*ctx*/) override { }
  virtual void exitLocal_variable_decl(openeLangParser::Local_variable_declContext * /*ctx*/) override { }

  virtual void enterStatement_list(openeLangParser::Statement_listContext * /*ctx*/) override { }
  virtual void exitStatement_list(openeLangParser::Statement_listContext * /*ctx*/) override { }

  virtual void enterConditionStatement(openeLangParser::ConditionStatementContext * /*ctx*/) override { }
  virtual void exitConditionStatement(openeLangParser::ConditionStatementContext * /*ctx*/) override { }

  virtual void enterAssignStatement(openeLangParser::AssignStatementContext * /*ctx*/) override { }
  virtual void exitAssignStatement(openeLangParser::AssignStatementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(openeLangParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(openeLangParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterLoopStatement(openeLangParser::LoopStatementContext * /*ctx*/) override { }
  virtual void exitLoopStatement(openeLangParser::LoopStatementContext * /*ctx*/) override { }

  virtual void enterSwitchStatement(openeLangParser::SwitchStatementContext * /*ctx*/) override { }
  virtual void exitSwitchStatement(openeLangParser::SwitchStatementContext * /*ctx*/) override { }

  virtual void enterSwitch_statement(openeLangParser::Switch_statementContext * /*ctx*/) override { }
  virtual void exitSwitch_statement(openeLangParser::Switch_statementContext * /*ctx*/) override { }

  virtual void enterWhile(openeLangParser::WhileContext * /*ctx*/) override { }
  virtual void exitWhile(openeLangParser::WhileContext * /*ctx*/) override { }

  virtual void enterRangeFor(openeLangParser::RangeForContext * /*ctx*/) override { }
  virtual void exitRangeFor(openeLangParser::RangeForContext * /*ctx*/) override { }

  virtual void enterFor(openeLangParser::ForContext * /*ctx*/) override { }
  virtual void exitFor(openeLangParser::ForContext * /*ctx*/) override { }

  virtual void enterDoWhile(openeLangParser::DoWhileContext * /*ctx*/) override { }
  virtual void exitDoWhile(openeLangParser::DoWhileContext * /*ctx*/) override { }

  virtual void enterIfStmt(openeLangParser::IfStmtContext * /*ctx*/) override { }
  virtual void exitIfStmt(openeLangParser::IfStmtContext * /*ctx*/) override { }

  virtual void enterIfTrueStmt(openeLangParser::IfTrueStmtContext * /*ctx*/) override { }
  virtual void exitIfTrueStmt(openeLangParser::IfTrueStmtContext * /*ctx*/) override { }

  virtual void enterHierarchy_identifier(openeLangParser::Hierarchy_identifierContext * /*ctx*/) override { }
  virtual void exitHierarchy_identifier(openeLangParser::Hierarchy_identifierContext * /*ctx*/) override { }

  virtual void enterFuncCall(openeLangParser::FuncCallContext * /*ctx*/) override { }
  virtual void exitFuncCall(openeLangParser::FuncCallContext * /*ctx*/) override { }

  virtual void enterIdentifier(openeLangParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(openeLangParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterArrayIndex(openeLangParser::ArrayIndexContext * /*ctx*/) override { }
  virtual void exitArrayIndex(openeLangParser::ArrayIndexContext * /*ctx*/) override { }

  virtual void enterBracket(openeLangParser::BracketContext * /*ctx*/) override { }
  virtual void exitBracket(openeLangParser::BracketContext * /*ctx*/) override { }

  virtual void enterOptElement(openeLangParser::OptElementContext * /*ctx*/) override { }
  virtual void exitOptElement(openeLangParser::OptElementContext * /*ctx*/) override { }

  virtual void enterBinaryExpr(openeLangParser::BinaryExprContext * /*ctx*/) override { }
  virtual void exitBinaryExpr(openeLangParser::BinaryExprContext * /*ctx*/) override { }

  virtual void enterUnaryExpr(openeLangParser::UnaryExprContext * /*ctx*/) override { }
  virtual void exitUnaryExpr(openeLangParser::UnaryExprContext * /*ctx*/) override { }

  virtual void enterData_set_value(openeLangParser::Data_set_valueContext * /*ctx*/) override { }
  virtual void exitData_set_value(openeLangParser::Data_set_valueContext * /*ctx*/) override { }

  virtual void enterDatetime_value(openeLangParser::Datetime_valueContext * /*ctx*/) override { }
  virtual void exitDatetime_value(openeLangParser::Datetime_valueContext * /*ctx*/) override { }

  virtual void enterDatetimePureNumber(openeLangParser::DatetimePureNumberContext * /*ctx*/) override { }
  virtual void exitDatetimePureNumber(openeLangParser::DatetimePureNumberContext * /*ctx*/) override { }

  virtual void enterDatetimeSeparateByChinese(openeLangParser::DatetimeSeparateByChineseContext * /*ctx*/) override { }
  virtual void exitDatetimeSeparateByChinese(openeLangParser::DatetimeSeparateByChineseContext * /*ctx*/) override { }

  virtual void enterDatetimeSeparateBySlash(openeLangParser::DatetimeSeparateBySlashContext * /*ctx*/) override { }
  virtual void exitDatetimeSeparateBySlash(openeLangParser::DatetimeSeparateBySlashContext * /*ctx*/) override { }

  virtual void enterDatetimeSeparateBySlashColon(openeLangParser::DatetimeSeparateBySlashColonContext * /*ctx*/) override { }
  virtual void exitDatetimeSeparateBySlashColon(openeLangParser::DatetimeSeparateBySlashColonContext * /*ctx*/) override { }

  virtual void enterDatetimeSeparateByBar(openeLangParser::DatetimeSeparateByBarContext * /*ctx*/) override { }
  virtual void exitDatetimeSeparateByBar(openeLangParser::DatetimeSeparateByBarContext * /*ctx*/) override { }

  virtual void enterDatetimeSeparateByBarColon(openeLangParser::DatetimeSeparateByBarColonContext * /*ctx*/) override { }
  virtual void exitDatetimeSeparateByBarColon(openeLangParser::DatetimeSeparateByBarColonContext * /*ctx*/) override { }

  virtual void enterMacro_value(openeLangParser::Macro_valueContext * /*ctx*/) override { }
  virtual void exitMacro_value(openeLangParser::Macro_valueContext * /*ctx*/) override { }

  virtual void enterFunc_ptr(openeLangParser::Func_ptrContext * /*ctx*/) override { }
  virtual void exitFunc_ptr(openeLangParser::Func_ptrContext * /*ctx*/) override { }

  virtual void enterBool_value(openeLangParser::Bool_valueContext * /*ctx*/) override { }
  virtual void exitBool_value(openeLangParser::Bool_valueContext * /*ctx*/) override { }

  virtual void enterInt(openeLangParser::IntContext * /*ctx*/) override { }
  virtual void exitInt(openeLangParser::IntContext * /*ctx*/) override { }

  virtual void enterFloat(openeLangParser::FloatContext * /*ctx*/) override { }
  virtual void exitFloat(openeLangParser::FloatContext * /*ctx*/) override { }

  virtual void enterString_value(openeLangParser::String_valueContext * /*ctx*/) override { }
  virtual void exitString_value(openeLangParser::String_valueContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace opene
