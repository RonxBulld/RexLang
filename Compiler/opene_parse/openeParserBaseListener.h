
// Generated from openeParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime/antlr4-runtime.h"
#include "openeParserListener.h"


namespace opene {

/**
 * This class provides an empty implementation of openeParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  openeParserBaseListener : public openeParserListener {
public:

  virtual void enterOpene_src(openeParser::Opene_srcContext * /*ctx*/) override { }
  virtual void exitOpene_src(openeParser::Opene_srcContext * /*ctx*/) override { }

  virtual void enterSrc_content(openeParser::Src_contentContext * /*ctx*/) override { }
  virtual void exitSrc_content(openeParser::Src_contentContext * /*ctx*/) override { }

  virtual void enterProgram_set_file(openeParser::Program_set_fileContext * /*ctx*/) override { }
  virtual void exitProgram_set_file(openeParser::Program_set_fileContext * /*ctx*/) override { }

  virtual void enterData_structure_file(openeParser::Data_structure_fileContext * /*ctx*/) override { }
  virtual void exitData_structure_file(openeParser::Data_structure_fileContext * /*ctx*/) override { }

  virtual void enterGlobal_variable_file(openeParser::Global_variable_fileContext * /*ctx*/) override { }
  virtual void exitGlobal_variable_file(openeParser::Global_variable_fileContext * /*ctx*/) override { }

  virtual void enterDll_define_file(openeParser::Dll_define_fileContext * /*ctx*/) override { }
  virtual void exitDll_define_file(openeParser::Dll_define_fileContext * /*ctx*/) override { }

  virtual void enterDll_command(openeParser::Dll_commandContext * /*ctx*/) override { }
  virtual void exitDll_command(openeParser::Dll_commandContext * /*ctx*/) override { }

  virtual void enterGlobal_variable_list(openeParser::Global_variable_listContext * /*ctx*/) override { }
  virtual void exitGlobal_variable_list(openeParser::Global_variable_listContext * /*ctx*/) override { }

  virtual void enterGlobal_variable_item(openeParser::Global_variable_itemContext * /*ctx*/) override { }
  virtual void exitGlobal_variable_item(openeParser::Global_variable_itemContext * /*ctx*/) override { }

  virtual void enterEdition_spec(openeParser::Edition_specContext * /*ctx*/) override { }
  virtual void exitEdition_spec(openeParser::Edition_specContext * /*ctx*/) override { }

  virtual void enterStruct_declare(openeParser::Struct_declareContext * /*ctx*/) override { }
  virtual void exitStruct_declare(openeParser::Struct_declareContext * /*ctx*/) override { }

  virtual void enterTable_comment(openeParser::Table_commentContext * /*ctx*/) override { }
  virtual void exitTable_comment(openeParser::Table_commentContext * /*ctx*/) override { }

  virtual void enterMember_list(openeParser::Member_listContext * /*ctx*/) override { }
  virtual void exitMember_list(openeParser::Member_listContext * /*ctx*/) override { }

  virtual void enterMember_item(openeParser::Member_itemContext * /*ctx*/) override { }
  virtual void exitMember_item(openeParser::Member_itemContext * /*ctx*/) override { }

  virtual void enterLibrary_list_opt(openeParser::Library_list_optContext * /*ctx*/) override { }
  virtual void exitLibrary_list_opt(openeParser::Library_list_optContext * /*ctx*/) override { }

  virtual void enterLibrary_spec(openeParser::Library_specContext * /*ctx*/) override { }
  virtual void exitLibrary_spec(openeParser::Library_specContext * /*ctx*/) override { }

  virtual void enterProg_set(openeParser::Prog_setContext * /*ctx*/) override { }
  virtual void exitProg_set(openeParser::Prog_setContext * /*ctx*/) override { }

  virtual void enterProg_set_variable_decl_opt(openeParser::Prog_set_variable_decl_optContext * /*ctx*/) override { }
  virtual void exitProg_set_variable_decl_opt(openeParser::Prog_set_variable_decl_optContext * /*ctx*/) override { }

  virtual void enterProg_set_variable_decl(openeParser::Prog_set_variable_declContext * /*ctx*/) override { }
  virtual void exitProg_set_variable_decl(openeParser::Prog_set_variable_declContext * /*ctx*/) override { }

  virtual void enterVariable_decl(openeParser::Variable_declContext * /*ctx*/) override { }
  virtual void exitVariable_decl(openeParser::Variable_declContext * /*ctx*/) override { }

  virtual void enterVariable_comment(openeParser::Variable_commentContext * /*ctx*/) override { }
  virtual void exitVariable_comment(openeParser::Variable_commentContext * /*ctx*/) override { }

  virtual void enterVariable_comment_element(openeParser::Variable_comment_elementContext * /*ctx*/) override { }
  virtual void exitVariable_comment_element(openeParser::Variable_comment_elementContext * /*ctx*/) override { }

  virtual void enterVariable_name(openeParser::Variable_nameContext * /*ctx*/) override { }
  virtual void exitVariable_name(openeParser::Variable_nameContext * /*ctx*/) override { }

  virtual void enterVariable_type(openeParser::Variable_typeContext * /*ctx*/) override { }
  virtual void exitVariable_type(openeParser::Variable_typeContext * /*ctx*/) override { }

  virtual void enterDimension_decl(openeParser::Dimension_declContext * /*ctx*/) override { }
  virtual void exitDimension_decl(openeParser::Dimension_declContext * /*ctx*/) override { }

  virtual void enterSub_program_opt(openeParser::Sub_program_optContext * /*ctx*/) override { }
  virtual void exitSub_program_opt(openeParser::Sub_program_optContext * /*ctx*/) override { }

  virtual void enterSub_program(openeParser::Sub_programContext * /*ctx*/) override { }
  virtual void exitSub_program(openeParser::Sub_programContext * /*ctx*/) override { }

  virtual void enterParameter_decl_list(openeParser::Parameter_decl_listContext * /*ctx*/) override { }
  virtual void exitParameter_decl_list(openeParser::Parameter_decl_listContext * /*ctx*/) override { }

  virtual void enterParameter_decl(openeParser::Parameter_declContext * /*ctx*/) override { }
  virtual void exitParameter_decl(openeParser::Parameter_declContext * /*ctx*/) override { }

  virtual void enterLocal_variable_decl(openeParser::Local_variable_declContext * /*ctx*/) override { }
  virtual void exitLocal_variable_decl(openeParser::Local_variable_declContext * /*ctx*/) override { }

  virtual void enterStatement_list(openeParser::Statement_listContext * /*ctx*/) override { }
  virtual void exitStatement_list(openeParser::Statement_listContext * /*ctx*/) override { }

  virtual void enterConditionStatement(openeParser::ConditionStatementContext * /*ctx*/) override { }
  virtual void exitConditionStatement(openeParser::ConditionStatementContext * /*ctx*/) override { }

  virtual void enterAssignStatement(openeParser::AssignStatementContext * /*ctx*/) override { }
  virtual void exitAssignStatement(openeParser::AssignStatementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(openeParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(openeParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterLoopStatement(openeParser::LoopStatementContext * /*ctx*/) override { }
  virtual void exitLoopStatement(openeParser::LoopStatementContext * /*ctx*/) override { }

  virtual void enterWhile(openeParser::WhileContext * /*ctx*/) override { }
  virtual void exitWhile(openeParser::WhileContext * /*ctx*/) override { }

  virtual void enterFor(openeParser::ForContext * /*ctx*/) override { }
  virtual void exitFor(openeParser::ForContext * /*ctx*/) override { }

  virtual void enterIfStmt(openeParser::IfStmtContext * /*ctx*/) override { }
  virtual void exitIfStmt(openeParser::IfStmtContext * /*ctx*/) override { }

  virtual void enterIfTrueStmt(openeParser::IfTrueStmtContext * /*ctx*/) override { }
  virtual void exitIfTrueStmt(openeParser::IfTrueStmtContext * /*ctx*/) override { }

  virtual void enterCondition_statement_else(openeParser::Condition_statement_elseContext * /*ctx*/) override { }
  virtual void exitCondition_statement_else(openeParser::Condition_statement_elseContext * /*ctx*/) override { }

  virtual void enterHierarchy_identifier(openeParser::Hierarchy_identifierContext * /*ctx*/) override { }
  virtual void exitHierarchy_identifier(openeParser::Hierarchy_identifierContext * /*ctx*/) override { }

  virtual void enterIdentifier(openeParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(openeParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterFuncCallWithArgu(openeParser::FuncCallWithArguContext * /*ctx*/) override { }
  virtual void exitFuncCallWithArgu(openeParser::FuncCallWithArguContext * /*ctx*/) override { }

  virtual void enterFuncCallWithoutArgu(openeParser::FuncCallWithoutArguContext * /*ctx*/) override { }
  virtual void exitFuncCallWithoutArgu(openeParser::FuncCallWithoutArguContext * /*ctx*/) override { }

  virtual void enterArrayIndex(openeParser::ArrayIndexContext * /*ctx*/) override { }
  virtual void exitArrayIndex(openeParser::ArrayIndexContext * /*ctx*/) override { }

  virtual void enterBracket(openeParser::BracketContext * /*ctx*/) override { }
  virtual void exitBracket(openeParser::BracketContext * /*ctx*/) override { }

  virtual void enterOptElement(openeParser::OptElementContext * /*ctx*/) override { }
  virtual void exitOptElement(openeParser::OptElementContext * /*ctx*/) override { }

  virtual void enterBinaryExpr(openeParser::BinaryExprContext * /*ctx*/) override { }
  virtual void exitBinaryExpr(openeParser::BinaryExprContext * /*ctx*/) override { }

  virtual void enterUnaryExpr(openeParser::UnaryExprContext * /*ctx*/) override { }
  virtual void exitUnaryExpr(openeParser::UnaryExprContext * /*ctx*/) override { }

  virtual void enterMacro_value(openeParser::Macro_valueContext * /*ctx*/) override { }
  virtual void exitMacro_value(openeParser::Macro_valueContext * /*ctx*/) override { }

  virtual void enterFunc_ptr(openeParser::Func_ptrContext * /*ctx*/) override { }
  virtual void exitFunc_ptr(openeParser::Func_ptrContext * /*ctx*/) override { }

  virtual void enterBool_value(openeParser::Bool_valueContext * /*ctx*/) override { }
  virtual void exitBool_value(openeParser::Bool_valueContext * /*ctx*/) override { }

  virtual void enterInt(openeParser::IntContext * /*ctx*/) override { }
  virtual void exitInt(openeParser::IntContext * /*ctx*/) override { }

  virtual void enterFloat(openeParser::FloatContext * /*ctx*/) override { }
  virtual void exitFloat(openeParser::FloatContext * /*ctx*/) override { }

  virtual void enterString_value(openeParser::String_valueContext * /*ctx*/) override { }
  virtual void exitString_value(openeParser::String_valueContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace opene
