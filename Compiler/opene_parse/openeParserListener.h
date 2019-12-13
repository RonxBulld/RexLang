
// Generated from openeParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime/antlr4-runtime.h"
#include "openeParser.h"


namespace opene {

/**
 * This interface defines an abstract listener for a parse tree produced by openeParser.
 */
class  openeParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterOpene_src(openeParser::Opene_srcContext *ctx) = 0;
  virtual void exitOpene_src(openeParser::Opene_srcContext *ctx) = 0;

  virtual void enterSrc_content(openeParser::Src_contentContext *ctx) = 0;
  virtual void exitSrc_content(openeParser::Src_contentContext *ctx) = 0;

  virtual void enterProgram_set_file(openeParser::Program_set_fileContext *ctx) = 0;
  virtual void exitProgram_set_file(openeParser::Program_set_fileContext *ctx) = 0;

  virtual void enterData_structure_file(openeParser::Data_structure_fileContext *ctx) = 0;
  virtual void exitData_structure_file(openeParser::Data_structure_fileContext *ctx) = 0;

  virtual void enterGlobal_variable_file(openeParser::Global_variable_fileContext *ctx) = 0;
  virtual void exitGlobal_variable_file(openeParser::Global_variable_fileContext *ctx) = 0;

  virtual void enterDll_define_file(openeParser::Dll_define_fileContext *ctx) = 0;
  virtual void exitDll_define_file(openeParser::Dll_define_fileContext *ctx) = 0;

  virtual void enterDll_command(openeParser::Dll_commandContext *ctx) = 0;
  virtual void exitDll_command(openeParser::Dll_commandContext *ctx) = 0;

  virtual void enterGlobal_variable_list(openeParser::Global_variable_listContext *ctx) = 0;
  virtual void exitGlobal_variable_list(openeParser::Global_variable_listContext *ctx) = 0;

  virtual void enterGlobal_variable_item(openeParser::Global_variable_itemContext *ctx) = 0;
  virtual void exitGlobal_variable_item(openeParser::Global_variable_itemContext *ctx) = 0;

  virtual void enterEdition_spec(openeParser::Edition_specContext *ctx) = 0;
  virtual void exitEdition_spec(openeParser::Edition_specContext *ctx) = 0;

  virtual void enterStruct_declare(openeParser::Struct_declareContext *ctx) = 0;
  virtual void exitStruct_declare(openeParser::Struct_declareContext *ctx) = 0;

  virtual void enterTable_comment(openeParser::Table_commentContext *ctx) = 0;
  virtual void exitTable_comment(openeParser::Table_commentContext *ctx) = 0;

  virtual void enterMember_list(openeParser::Member_listContext *ctx) = 0;
  virtual void exitMember_list(openeParser::Member_listContext *ctx) = 0;

  virtual void enterMember_item(openeParser::Member_itemContext *ctx) = 0;
  virtual void exitMember_item(openeParser::Member_itemContext *ctx) = 0;

  virtual void enterLibrary_list_opt(openeParser::Library_list_optContext *ctx) = 0;
  virtual void exitLibrary_list_opt(openeParser::Library_list_optContext *ctx) = 0;

  virtual void enterLibrary_spec(openeParser::Library_specContext *ctx) = 0;
  virtual void exitLibrary_spec(openeParser::Library_specContext *ctx) = 0;

  virtual void enterProg_set(openeParser::Prog_setContext *ctx) = 0;
  virtual void exitProg_set(openeParser::Prog_setContext *ctx) = 0;

  virtual void enterProg_set_variable_decl_opt(openeParser::Prog_set_variable_decl_optContext *ctx) = 0;
  virtual void exitProg_set_variable_decl_opt(openeParser::Prog_set_variable_decl_optContext *ctx) = 0;

  virtual void enterProg_set_variable_decl(openeParser::Prog_set_variable_declContext *ctx) = 0;
  virtual void exitProg_set_variable_decl(openeParser::Prog_set_variable_declContext *ctx) = 0;

  virtual void enterVariable_decl(openeParser::Variable_declContext *ctx) = 0;
  virtual void exitVariable_decl(openeParser::Variable_declContext *ctx) = 0;

  virtual void enterVariable_comment(openeParser::Variable_commentContext *ctx) = 0;
  virtual void exitVariable_comment(openeParser::Variable_commentContext *ctx) = 0;

  virtual void enterVariable_comment_element(openeParser::Variable_comment_elementContext *ctx) = 0;
  virtual void exitVariable_comment_element(openeParser::Variable_comment_elementContext *ctx) = 0;

  virtual void enterVariable_name(openeParser::Variable_nameContext *ctx) = 0;
  virtual void exitVariable_name(openeParser::Variable_nameContext *ctx) = 0;

  virtual void enterVariable_type(openeParser::Variable_typeContext *ctx) = 0;
  virtual void exitVariable_type(openeParser::Variable_typeContext *ctx) = 0;

  virtual void enterDimension_decl(openeParser::Dimension_declContext *ctx) = 0;
  virtual void exitDimension_decl(openeParser::Dimension_declContext *ctx) = 0;

  virtual void enterSub_program_opt(openeParser::Sub_program_optContext *ctx) = 0;
  virtual void exitSub_program_opt(openeParser::Sub_program_optContext *ctx) = 0;

  virtual void enterSub_program(openeParser::Sub_programContext *ctx) = 0;
  virtual void exitSub_program(openeParser::Sub_programContext *ctx) = 0;

  virtual void enterParameter_decl_list(openeParser::Parameter_decl_listContext *ctx) = 0;
  virtual void exitParameter_decl_list(openeParser::Parameter_decl_listContext *ctx) = 0;

  virtual void enterParameter_decl(openeParser::Parameter_declContext *ctx) = 0;
  virtual void exitParameter_decl(openeParser::Parameter_declContext *ctx) = 0;

  virtual void enterLocal_variable_decl(openeParser::Local_variable_declContext *ctx) = 0;
  virtual void exitLocal_variable_decl(openeParser::Local_variable_declContext *ctx) = 0;

  virtual void enterStatement_list(openeParser::Statement_listContext *ctx) = 0;
  virtual void exitStatement_list(openeParser::Statement_listContext *ctx) = 0;

  virtual void enterConditionStatement(openeParser::ConditionStatementContext *ctx) = 0;
  virtual void exitConditionStatement(openeParser::ConditionStatementContext *ctx) = 0;

  virtual void enterAssignStatement(openeParser::AssignStatementContext *ctx) = 0;
  virtual void exitAssignStatement(openeParser::AssignStatementContext *ctx) = 0;

  virtual void enterExpressionStatement(openeParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(openeParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterLoopStatement(openeParser::LoopStatementContext *ctx) = 0;
  virtual void exitLoopStatement(openeParser::LoopStatementContext *ctx) = 0;

  virtual void enterWhile(openeParser::WhileContext *ctx) = 0;
  virtual void exitWhile(openeParser::WhileContext *ctx) = 0;

  virtual void enterFor(openeParser::ForContext *ctx) = 0;
  virtual void exitFor(openeParser::ForContext *ctx) = 0;

  virtual void enterIfStmt(openeParser::IfStmtContext *ctx) = 0;
  virtual void exitIfStmt(openeParser::IfStmtContext *ctx) = 0;

  virtual void enterIfTrueStmt(openeParser::IfTrueStmtContext *ctx) = 0;
  virtual void exitIfTrueStmt(openeParser::IfTrueStmtContext *ctx) = 0;

  virtual void enterCondition_statement_else(openeParser::Condition_statement_elseContext *ctx) = 0;
  virtual void exitCondition_statement_else(openeParser::Condition_statement_elseContext *ctx) = 0;

  virtual void enterHierarchy_identifier(openeParser::Hierarchy_identifierContext *ctx) = 0;
  virtual void exitHierarchy_identifier(openeParser::Hierarchy_identifierContext *ctx) = 0;

  virtual void enterIdentifier(openeParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(openeParser::IdentifierContext *ctx) = 0;

  virtual void enterFuncCallWithArgu(openeParser::FuncCallWithArguContext *ctx) = 0;
  virtual void exitFuncCallWithArgu(openeParser::FuncCallWithArguContext *ctx) = 0;

  virtual void enterFuncCallWithoutArgu(openeParser::FuncCallWithoutArguContext *ctx) = 0;
  virtual void exitFuncCallWithoutArgu(openeParser::FuncCallWithoutArguContext *ctx) = 0;

  virtual void enterArrayIndex(openeParser::ArrayIndexContext *ctx) = 0;
  virtual void exitArrayIndex(openeParser::ArrayIndexContext *ctx) = 0;

  virtual void enterBracket(openeParser::BracketContext *ctx) = 0;
  virtual void exitBracket(openeParser::BracketContext *ctx) = 0;

  virtual void enterOptElement(openeParser::OptElementContext *ctx) = 0;
  virtual void exitOptElement(openeParser::OptElementContext *ctx) = 0;

  virtual void enterBinaryExpr(openeParser::BinaryExprContext *ctx) = 0;
  virtual void exitBinaryExpr(openeParser::BinaryExprContext *ctx) = 0;

  virtual void enterUnaryExpr(openeParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(openeParser::UnaryExprContext *ctx) = 0;

  virtual void enterMacro_value(openeParser::Macro_valueContext *ctx) = 0;
  virtual void exitMacro_value(openeParser::Macro_valueContext *ctx) = 0;

  virtual void enterFunc_ptr(openeParser::Func_ptrContext *ctx) = 0;
  virtual void exitFunc_ptr(openeParser::Func_ptrContext *ctx) = 0;

  virtual void enterBool_value(openeParser::Bool_valueContext *ctx) = 0;
  virtual void exitBool_value(openeParser::Bool_valueContext *ctx) = 0;

  virtual void enterInt(openeParser::IntContext *ctx) = 0;
  virtual void exitInt(openeParser::IntContext *ctx) = 0;

  virtual void enterFloat(openeParser::FloatContext *ctx) = 0;
  virtual void exitFloat(openeParser::FloatContext *ctx) = 0;

  virtual void enterString_value(openeParser::String_valueContext *ctx) = 0;
  virtual void exitString_value(openeParser::String_valueContext *ctx) = 0;


};

}  // namespace opene
