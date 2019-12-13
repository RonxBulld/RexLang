
// Generated from openeParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime/antlr4-runtime.h"
#include "openeParserVisitor.h"


namespace opene {

/**
 * This class provides an empty implementation of openeParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  openeParserBaseVisitor : public openeParserVisitor {
public:

  virtual antlrcpp::Any visitOpene_src(openeParser::Opene_srcContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSrc_content(openeParser::Src_contentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProgram_set_file(openeParser::Program_set_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitData_structure_file(openeParser::Data_structure_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_variable_file(openeParser::Global_variable_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDll_define_file(openeParser::Dll_define_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDll_command(openeParser::Dll_commandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_variable_list(openeParser::Global_variable_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_variable_item(openeParser::Global_variable_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdition_spec(openeParser::Edition_specContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStruct_declare(openeParser::Struct_declareContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTable_comment(openeParser::Table_commentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMember_list(openeParser::Member_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMember_item(openeParser::Member_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLibrary_list_opt(openeParser::Library_list_optContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLibrary_spec(openeParser::Library_specContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg_set(openeParser::Prog_setContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg_set_variable_decl_opt(openeParser::Prog_set_variable_decl_optContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg_set_variable_decl(openeParser::Prog_set_variable_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable_decl(openeParser::Variable_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable_comment(openeParser::Variable_commentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable_comment_element(openeParser::Variable_comment_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable_name(openeParser::Variable_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable_type(openeParser::Variable_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDimension_decl(openeParser::Dimension_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSub_program_opt(openeParser::Sub_program_optContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSub_program(openeParser::Sub_programContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameter_decl_list(openeParser::Parameter_decl_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameter_decl(openeParser::Parameter_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocal_variable_decl(openeParser::Local_variable_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement_list(openeParser::Statement_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConditionStatement(openeParser::ConditionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignStatement(openeParser::AssignStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressionStatement(openeParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoopStatement(openeParser::LoopStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhile(openeParser::WhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor(openeParser::ForContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfStmt(openeParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfTrueStmt(openeParser::IfTrueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCondition_statement_else(openeParser::Condition_statement_elseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHierarchy_identifier(openeParser::Hierarchy_identifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifier(openeParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncCallWithArgu(openeParser::FuncCallWithArguContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncCallWithoutArgu(openeParser::FuncCallWithoutArguContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayIndex(openeParser::ArrayIndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBracket(openeParser::BracketContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElement(openeParser::OptElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBinaryExpr(openeParser::BinaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpr(openeParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMacro_value(openeParser::Macro_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunc_ptr(openeParser::Func_ptrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBool_value(openeParser::Bool_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInt(openeParser::IntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFloat(openeParser::FloatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitString_value(openeParser::String_valueContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace opene
