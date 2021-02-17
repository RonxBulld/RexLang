
// Generated from /mnt/d/Project/RexLang/Compiler/rexlang_compiler/rexLang.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "rexLangVisitor.h"


namespace rexlang {

/**
 * This class provides an empty implementation of rexLangVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  rexLangBaseVisitor : public rexLangVisitor {
public:

  virtual antlrcpp::Any visitRexlang_src(rexLangParser::Rexlang_srcContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSrc_content(rexLangParser::Src_contentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProgram_set_file(rexLangParser::Program_set_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitData_structure_file(rexLangParser::Data_structure_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_variable_file(rexLangParser::Global_variable_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitApi_define_file(rexLangParser::Api_define_fileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDll_command(rexLangParser::Dll_commandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLib_command(rexLangParser::Lib_commandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_variable_list(rexLangParser::Global_variable_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_variable_item(rexLangParser::Global_variable_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdition_spec(rexLangParser::Edition_specContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStruct_declare(rexLangParser::Struct_declareContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTable_comment(rexLangParser::Table_commentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg_set(rexLangParser::Prog_setContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable_decl(rexLangParser::Variable_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMember_vari_decl(rexLangParser::Member_vari_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFile_vari_decl(rexLangParser::File_vari_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSub_program(rexLangParser::Sub_programContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocal_variable_decl(rexLangParser::Local_variable_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameter_decl_list(rexLangParser::Parameter_decl_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameter_decl(rexLangParser::Parameter_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVari_parameter_decl(rexLangParser::Vari_parameter_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement_list(rexLangParser::Statement_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConditionStatement(rexLangParser::ConditionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignStatement(rexLangParser::AssignStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressionStatement(rexLangParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoopStatement(rexLangParser::LoopStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSwitchStatement(rexLangParser::SwitchStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitControlStatement(rexLangParser::ControlStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSwitch_statement(rexLangParser::Switch_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhile(rexLangParser::WhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRangeFor(rexLangParser::RangeForContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor(rexLangParser::ForContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDoWhile(rexLangParser::DoWhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfStmt(rexLangParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfTrueStmt(rexLangParser::IfTrueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitContinueStmt(rexLangParser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBreakStmt(rexLangParser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturnStmt(rexLangParser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExitStmt(rexLangParser::ExitStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncCall(rexLangParser::FuncCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHierarchy(rexLangParser::HierarchyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifier(rexLangParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayIndex(rexLangParser::ArrayIndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBracket(rexLangParser::BracketContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElement(rexLangParser::OptElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBinaryExpr(rexLangParser::BinaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpr(rexLangParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitData_set_value(rexLangParser::Data_set_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetime_value(rexLangParser::Datetime_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimePureNumber(rexLangParser::DatetimePureNumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimeSeparateByChinese(rexLangParser::DatetimeSeparateByChineseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimeSeparateBySlash(rexLangParser::DatetimeSeparateBySlashContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimeSeparateBySlashColon(rexLangParser::DatetimeSeparateBySlashColonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimeSeparateByBar(rexLangParser::DatetimeSeparateByBarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatetimeSeparateByBarColon(rexLangParser::DatetimeSeparateByBarColonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMacro_value(rexLangParser::Macro_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunc_ptr(rexLangParser::Func_ptrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBoolValueTrue(rexLangParser::BoolValueTrueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBoolValueFalse(rexLangParser::BoolValueFalseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInt(rexLangParser::IntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFloat(rexLangParser::FloatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitString_value(rexLangParser::String_valueContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace rexlang
