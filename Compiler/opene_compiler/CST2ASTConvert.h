//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_CST2ASTCONVERT_H
#define OPENELANGUAGE_CST2ASTCONVERT_H

#include "gen/openeLangLexer.h"
#include "gen/openeLangParser.h"
#include "gen/openeLangVisitor.h"

#include "NodeDecl.h"
#include "utilities/Diagnostic.h"
#include "ASTContext.h"

namespace opene {
    class CST2ASTConvert : public openeLangVisitor {
    private:
        ASTContext *ast_context_ = nullptr;

    private:
        TString GetTextIfExist(const antlr4::Token *token, const std::string &hint = "") const;

        long GetLongIfExist(const antlr4::Token *token, int hint = 0) const;

        float GetFloatIfExist(const antlr4::Token *token, float hint = 0.0f) const;

        std::vector<TString> GetTextVecIfExist(const std::vector<antlr4::Token *> tokens, const std::string &hint = "") const;

        template<
                typename T,
                bool must_valid = false,
                typename = typename std::enable_if_t<std::is_pointer_v<T>>,
                typename = typename std::enable_if_t<std::is_base_of_v<Node, typename std::remove_pointer_t<T>>>
        >
        T GetFromCtxIfExist(antlr4::ParserRuleContext *ctx, const T &hint = T());

        template<typename T, bool must_valid = false, typename = typename std::enable_if_t<!std::is_pointer_v<T>>>
        T GetFromCtxIfExist(antlr4::ParserRuleContext *ctx, const T &hint = T());

        template<typename NodeTy, typename ... Args, typename = typename std::enable_if_t<std::is_base_of_v<Node, NodeTy>>>
        NodeTy *CreateNode(antlr4::Token *start_token, antlr4::Token *end_token, Args ... args);

    public:
        antlrcpp::Any visitOpene_src(openeLangParser::Opene_srcContext *context) override;

        antlrcpp::Any visitSrc_content(openeLangParser::Src_contentContext *context) override;

        antlrcpp::Any visitProgram_set_file(openeLangParser::Program_set_fileContext *context) override;

        antlrcpp::Any visitData_structure_file(openeLangParser::Data_structure_fileContext *context) override;

        antlrcpp::Any visitGlobal_variable_file(openeLangParser::Global_variable_fileContext *context) override;

        antlrcpp::Any visitDll_define_file(openeLangParser::Dll_define_fileContext *context) override;

        antlrcpp::Any visitDll_command(openeLangParser::Dll_commandContext *context) override;

        antlrcpp::Any visitGlobal_variable_list(openeLangParser::Global_variable_listContext *context) override;

        antlrcpp::Any visitGlobal_variable_item(openeLangParser::Global_variable_itemContext *context) override;

        antlrcpp::Any visitEdition_spec(openeLangParser::Edition_specContext *context) override;

        antlrcpp::Any visitStruct_declare(openeLangParser::Struct_declareContext *context) override;

        antlrcpp::Any visitTable_comment(openeLangParser::Table_commentContext *context) override;

        antlrcpp::Any visitProg_set(openeLangParser::Prog_setContext *context) override;

        antlrcpp::Any visitVariable_decl(openeLangParser::Variable_declContext *context) override;

        antlrcpp::Any visitSub_program(openeLangParser::Sub_programContext *context) override;

        antlrcpp::Any visitParameter_decl(openeLangParser::Parameter_declContext *context) override;

        antlrcpp::Any visitStatement_list(openeLangParser::Statement_listContext *context) override;

        antlrcpp::Any visitConditionStatement(openeLangParser::ConditionStatementContext *context) override;

        antlrcpp::Any visitAssignStatement(openeLangParser::AssignStatementContext *context) override;

        antlrcpp::Any visitExpressionStatement(openeLangParser::ExpressionStatementContext *context) override;

        antlrcpp::Any visitLoopStatement(openeLangParser::LoopStatementContext *context) override;

        antlrcpp::Any visitSwitchStatement(openeLangParser::SwitchStatementContext *context) override;

        antlrcpp::Any visitSwitch_statement(openeLangParser::Switch_statementContext *context) override;

        antlrcpp::Any visitWhile(openeLangParser::WhileContext *context) override;

        antlrcpp::Any visitRangeFor(openeLangParser::RangeForContext *context) override;

        antlrcpp::Any visitFor(openeLangParser::ForContext *context) override;

        antlrcpp::Any visitDoWhile(openeLangParser::DoWhileContext *context) override;

        antlrcpp::Any visitIfStmt(openeLangParser::IfStmtContext *context) override;

        antlrcpp::Any visitIfTrueStmt(openeLangParser::IfTrueStmtContext *context) override;

        antlrcpp::Any visitHierarchy_identifier(openeLangParser::Hierarchy_identifierContext *context) override;

        antlrcpp::Any visitFuncCall(openeLangParser::FuncCallContext *context) override;

        antlrcpp::Any visitIdentifier(openeLangParser::IdentifierContext *context) override;

        antlrcpp::Any visitArrayIndex(openeLangParser::ArrayIndexContext *context) override;

        antlrcpp::Any visitBracket(openeLangParser::BracketContext *context) override;

        antlrcpp::Any visitOptElement(openeLangParser::OptElementContext *context) override;

        antlrcpp::Any visitBinaryExpr(openeLangParser::BinaryExprContext *context) override;

        antlrcpp::Any visitUnaryExpr(openeLangParser::UnaryExprContext *context) override;

        antlrcpp::Any visitData_set_value(openeLangParser::Data_set_valueContext *context) override;

        antlrcpp::Any visitDatetime_value(openeLangParser::Datetime_valueContext *context) override;

        ValueOfDatetimePtr TimeNodeBuilder(time_t time, antlr4::Token *start_token, antlr4::Token *end_token);

        antlrcpp::Any visitDatetimePureNumber(openeLangParser::DatetimePureNumberContext *context) override;

        tm TimeBuilder(unsigned year, unsigned month, unsigned day, unsigned hour, unsigned minute, unsigned second);

        ValueOfDatetimePtr TimeNodeBuilder(tm && stm, antlr4::Token *start_token, antlr4::Token *end_token);

        antlrcpp::Any visitDatetimeSeparateByChinese(openeLangParser::DatetimeSeparateByChineseContext *context) override;

        antlrcpp::Any visitDatetimeSeparateBySlash(openeLangParser::DatetimeSeparateBySlashContext *context) override;

        antlrcpp::Any visitDatetimeSeparateBySlashColon(openeLangParser::DatetimeSeparateBySlashColonContext *context) override;

        antlrcpp::Any visitDatetimeSeparateByBar(openeLangParser::DatetimeSeparateByBarContext *context) override;

        antlrcpp::Any visitDatetimeSeparateByBarColon(openeLangParser::DatetimeSeparateByBarColonContext *context) override;

        antlrcpp::Any visitMacro_value(openeLangParser::Macro_valueContext *context) override;

        antlrcpp::Any visitFunc_ptr(openeLangParser::Func_ptrContext *context) override;

        antlrcpp::Any visitBoolValueTrue(openeLangParser::BoolValueTrueContext *context) override;

        antlrcpp::Any visitBoolValueFalse(openeLangParser::BoolValueFalseContext *context) override;

        antlrcpp::Any visitInt(openeLangParser::IntContext *context) override;

        antlrcpp::Any visitFloat(openeLangParser::FloatContext *context) override;

        antlrcpp::Any visitString_value(openeLangParser::String_valueContext *context) override;

        antlrcpp::Any visitLocal_variable_decl(openeLangParser::Local_variable_declContext *context) override;

        antlrcpp::Any visitMember_vari_decl(openeLangParser::Member_vari_declContext *context) override;

        antlrcpp::Any visitFile_vari_decl(openeLangParser::File_vari_declContext *context) override;

        antlrcpp::Any visitControlStatement(openeLangParser::ControlStatementContext *context) override;

        antlrcpp::Any visitContinueStmt(openeLangParser::ContinueStmtContext *context) override;

        antlrcpp::Any visitBreakStmt(openeLangParser::BreakStmtContext *context) override;

        antlrcpp::Any visitReturnStmt(openeLangParser::ReturnStmtContext *context) override;

        antlrcpp::Any visitExitStmt(openeLangParser::ExitStmtContext *context) override;

    public:
        CST2ASTConvert(ASTContext *ast_context, Diagnostic *diagnostic);

        TranslateUnitPtr BuildTranslateUnitFromParseTree(antlr4::tree::ParseTree* tree);
    };
}

#endif //OPENELANGUAGE_CST2ASTCONVERT_H
