
// Generated from openeParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "openeParser.h"


namespace opene {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by openeParser.
 */
class  openeParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by openeParser.
   */
    virtual antlrcpp::Any visitOpene_src(openeParser::Opene_srcContext *context) = 0;

    virtual antlrcpp::Any visitSrc_content(openeParser::Src_contentContext *context) = 0;

    virtual antlrcpp::Any visitProgram_set_file(openeParser::Program_set_fileContext *context) = 0;

    virtual antlrcpp::Any visitData_structure_file(openeParser::Data_structure_fileContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_variable_file(openeParser::Global_variable_fileContext *context) = 0;

    virtual antlrcpp::Any visitDll_define_file(openeParser::Dll_define_fileContext *context) = 0;

    virtual antlrcpp::Any visitDll_command(openeParser::Dll_commandContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_variable_list(openeParser::Global_variable_listContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_variable_item(openeParser::Global_variable_itemContext *context) = 0;

    virtual antlrcpp::Any visitEdition_spec(openeParser::Edition_specContext *context) = 0;

    virtual antlrcpp::Any visitStruct_declare(openeParser::Struct_declareContext *context) = 0;

    virtual antlrcpp::Any visitTable_comment(openeParser::Table_commentContext *context) = 0;

    virtual antlrcpp::Any visitMember_list(openeParser::Member_listContext *context) = 0;

    virtual antlrcpp::Any visitMember_item(openeParser::Member_itemContext *context) = 0;

    virtual antlrcpp::Any visitLibrary_list_opt(openeParser::Library_list_optContext *context) = 0;

    virtual antlrcpp::Any visitLibrary_spec(openeParser::Library_specContext *context) = 0;

    virtual antlrcpp::Any visitProg_set(openeParser::Prog_setContext *context) = 0;

    virtual antlrcpp::Any visitProg_set_variable_decl_opt(openeParser::Prog_set_variable_decl_optContext *context) = 0;

    virtual antlrcpp::Any visitProg_set_variable_decl(openeParser::Prog_set_variable_declContext *context) = 0;

    virtual antlrcpp::Any visitVariable_decl(openeParser::Variable_declContext *context) = 0;

    virtual antlrcpp::Any visitVariable_comment(openeParser::Variable_commentContext *context) = 0;

    virtual antlrcpp::Any visitVariable_comment_element(openeParser::Variable_comment_elementContext *context) = 0;

    virtual antlrcpp::Any visitVariable_name(openeParser::Variable_nameContext *context) = 0;

    virtual antlrcpp::Any visitVariable_type(openeParser::Variable_typeContext *context) = 0;

    virtual antlrcpp::Any visitDimension_decl(openeParser::Dimension_declContext *context) = 0;

    virtual antlrcpp::Any visitSub_program_opt(openeParser::Sub_program_optContext *context) = 0;

    virtual antlrcpp::Any visitSub_program(openeParser::Sub_programContext *context) = 0;

    virtual antlrcpp::Any visitParameter_decl_list(openeParser::Parameter_decl_listContext *context) = 0;

    virtual antlrcpp::Any visitParameter_decl(openeParser::Parameter_declContext *context) = 0;

    virtual antlrcpp::Any visitLocal_variable_decl(openeParser::Local_variable_declContext *context) = 0;

    virtual antlrcpp::Any visitStatement_list(openeParser::Statement_listContext *context) = 0;

    virtual antlrcpp::Any visitConditionStatement(openeParser::ConditionStatementContext *context) = 0;

    virtual antlrcpp::Any visitAssignStatement(openeParser::AssignStatementContext *context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(openeParser::ExpressionStatementContext *context) = 0;

    virtual antlrcpp::Any visitLoopStatement(openeParser::LoopStatementContext *context) = 0;

    virtual antlrcpp::Any visitWhile(openeParser::WhileContext *context) = 0;

    virtual antlrcpp::Any visitFor(openeParser::ForContext *context) = 0;

    virtual antlrcpp::Any visitIfStmt(openeParser::IfStmtContext *context) = 0;

    virtual antlrcpp::Any visitIfTrueStmt(openeParser::IfTrueStmtContext *context) = 0;

    virtual antlrcpp::Any visitCondition_statement_else(openeParser::Condition_statement_elseContext *context) = 0;

    virtual antlrcpp::Any visitHierarchy_identifier(openeParser::Hierarchy_identifierContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(openeParser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitFuncCallWithArgu(openeParser::FuncCallWithArguContext *context) = 0;

    virtual antlrcpp::Any visitFuncCallWithoutArgu(openeParser::FuncCallWithoutArguContext *context) = 0;

    virtual antlrcpp::Any visitArrayIndex(openeParser::ArrayIndexContext *context) = 0;

    virtual antlrcpp::Any visitBracket(openeParser::BracketContext *context) = 0;

    virtual antlrcpp::Any visitOptElement(openeParser::OptElementContext *context) = 0;

    virtual antlrcpp::Any visitBinaryExpr(openeParser::BinaryExprContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpr(openeParser::UnaryExprContext *context) = 0;

    virtual antlrcpp::Any visitMacro_value(openeParser::Macro_valueContext *context) = 0;

    virtual antlrcpp::Any visitFunc_ptr(openeParser::Func_ptrContext *context) = 0;

    virtual antlrcpp::Any visitBool_value(openeParser::Bool_valueContext *context) = 0;

    virtual antlrcpp::Any visitInt(openeParser::IntContext *context) = 0;

    virtual antlrcpp::Any visitFloat(openeParser::FloatContext *context) = 0;

    virtual antlrcpp::Any visitString_value(openeParser::String_valueContext *context) = 0;


};

}  // namespace opene
