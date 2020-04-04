
// Generated from /home/rexfield/Rex/OpenELanguage/Compiler/opene_compiler/openeLang.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "openeLangVisitor.h"


namespace opene {

/**
 * This class provides an empty implementation of openeLangVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  openeLangBaseVisitor : public openeLangVisitor {
public:

  virtual antlrcpp::Any visitOpene_src(openeLangParser::Opene_srcContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSrc_content(openeLangParser::Src_contentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProgram_set_file(openeLangParser::Program_set_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitData_structure_file(openeLangParser::Data_structure_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_variable_file(openeLangParser::Global_variable_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDll_define_file(openeLangParser::Dll_define_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDll_command(openeLangParser::Dll_commandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLib_command(openeLangParser::Lib_commandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_variable_list(openeLangParser::Global_variable_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_variable_item(openeLangParser::Global_variable_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdition_spec(openeLangParser::Edition_specContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStruct_declare(openeLangParser::Struct_declareContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTable_comment(openeLangParser::Table_commentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg_set(openeLangParser::Prog_setContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable_decl(openeLangParser::Variable_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMember_vari_decl(openeLangParser::Member_vari_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFile_vari_decl(openeLangParser::File_vari_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSub_program(openeLangParser::Sub_programContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocal_variable_decl(openeLangParser::Local_variable_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameter_decl_list(openeLangParser::Parameter_decl_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameter_decl(openeLangParser::Parameter_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVari_parameter_decl(openeLangParser::Vari_parameter_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement_list(openeLangParser::Statement_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConditionStatement(openeLangParser::ConditionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignStatement(openeLangParser::AssignStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressionStatement(openeLangParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoopStatement(openeLangParser::LoopStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSwitchStatement(openeLangParser::SwitchStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitControlStatement(openeLangParser::ControlStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSwitch_statement(openeLangParser::Switch_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhile(openeLangParser::WhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRangeFor(openeLangParser::RangeForContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor(openeLangParser::ForContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDoWhile(openeLangParser::DoWhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfStmt(openeLangParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfTrueStmt(openeLangParser::IfTrueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitContinueStmt(openeLangParser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBreakStmt(openeLangParser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturnStmt(openeLangParser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExitStmt(openeLangParser::ExitStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHierarchy_identifier(openeLangParser::Hierarchy_identifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncCall(openeLangParser::FuncCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifier(openeLangParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayIndex(openeLangParser::ArrayIndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBracket(openeLangParser::BracketContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElement(openeLangParser::OptElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBinaryExpr(openeLangParser::BinaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpr(openeLangParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitData_set_value(openeLangParser::Data_set_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetime_value(openeLangParser::Datetime_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimePureNumber(openeLangParser::DatetimePureNumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimeSeparateByChinese(openeLangParser::DatetimeSeparateByChineseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimeSeparateBySlash(openeLangParser::DatetimeSeparateBySlashContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimeSeparateBySlashColon(openeLangParser::DatetimeSeparateBySlashColonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimeSeparateByBar(openeLangParser::DatetimeSeparateByBarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimeSeparateByBarColon(openeLangParser::DatetimeSeparateByBarColonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMacro_value(openeLangParser::Macro_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunc_ptr(openeLangParser::Func_ptrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBoolValueTrue(openeLangParser::BoolValueTrueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBoolValueFalse(openeLangParser::BoolValueFalseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInt(openeLangParser::IntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFloat(openeLangParser::FloatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitString_value(openeLangParser::String_valueContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace opene
