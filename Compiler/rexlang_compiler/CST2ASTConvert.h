//
// Created by rex on 2020/1/23.
//

#ifndef REXLANG_CST2ASTCONVERT_H
#define REXLANG_CST2ASTCONVERT_H

#include "gen/rexLangLexer.h"
#include "gen/rexLangParser.h"
#include "gen/rexLangVisitor.h"

#include "NodeDecl.h"
#include "utilities/Diagnostic.h"
#include "ASTContext.h"

namespace rexlang {

    class REXCompilerInstance;

    class CST2ASTConvert : public rexLangVisitor {
    private:
        ASTContext *ast_context_ = nullptr;
        REXCompilerInstance *compiler_instance_ = nullptr;
        /*
         * 待处理文件缓存
         */
        std::set<rexLangParser::Src_contentContext *> source_cache_;

    private:
        TString              GetTextIfExist   (const antlr4::Token *token, const std::string &hint = "") const;
        long                 GetLongIfExist   (const antlr4::Token *token, int hint = 0) const;
        float                GetFloatIfExist  (const antlr4::Token *token, float hint = 0.0f) const;
        std::vector<TString> GetTextVecIfExist(const std::vector<antlr4::Token *> &tokens, const std::string &hint = "") const;

        template<
                typename T,
                bool must_valid = false,
                typename = typename std::enable_if_t<std::is_pointer_v<T>>,
                typename = typename std::enable_if_t<std::is_base_of_v<Node, typename std::remove_pointer_t<T>>>
        >
        T GetFromCtxIfExist(antlr4::ParserRuleContext *ctx, const T &hint = T());

        template<typename T, bool must_valid = false, typename = typename std::enable_if_t<!std::is_pointer_v<T>>>
        T GetFromCtxIfExist(antlr4::ParserRuleContext *ctx, const T &hint = T());

    private:
        template<typename NodeTy, typename ... Args, typename = typename std::enable_if_t<std::is_base_of_v<Node, NodeTy>>>
        NodeTy *CreateNode(antlr4::Token *start_token, antlr4::Token *end_token, Args && ... args);

        template<typename NodeTy, typename ... Args, typename = typename std::enable_if_t<std::is_base_of_v<Node, NodeTy>>>
        NodeTy *CreateNode(antlr4::ParserRuleContext *parserRuleContext, Args && ... args);

    private:
        ValueOfDatetime* TimeNodeBuilder(time_t ntm, antlr4::ParserRuleContext *parserRuleContext);
        tm TimeBuilder(unsigned year, unsigned month, unsigned day, unsigned hour, unsigned minute, unsigned second);

    private:
        template <typename T, typename = typename std::enable_if_t<std::is_base_of_v<antlr4::ParserRuleContext, T>>>
        std::vector<T *> filterSources() ;

        /*===----------------------------------------------------===*
         * 从 ParseTree 森林中构建唯一的翻译单元，并提取资源内容
         */
        bool buildTranslateUnitAndFetchSrc(const std::vector<antlr4::tree::ParseTree *> &trees);

        /*===----------------------------------------------------===*
         * 导入依赖库文件
         */
        bool importLibraries();

        /*===----------------------------------------------------===*
         * 从资源缓存中分析结构体定义
         */
        bool parseDataStructFiles();

    public:
        antlrcpp::Any visitRexlang_src                  (rexLangParser::Rexlang_srcContext *                  context) override;
        antlrcpp::Any visitSrc_content                  (rexLangParser::Src_contentContext *                  context) override;
        antlrcpp::Any visitProgram_set_file             (rexLangParser::Program_set_fileContext *             context) override;
        antlrcpp::Any visitData_structure_file          (rexLangParser::Data_structure_fileContext *          context) override;
        antlrcpp::Any visitGlobal_variable_file         (rexLangParser::Global_variable_fileContext *         context) override;
        antlrcpp::Any visitDll_define_file              (rexLangParser::Dll_define_fileContext *              context) override;
        antlrcpp::Any visitDll_command                  (rexLangParser::Dll_commandContext *                  context) override;
        antlrcpp::Any visitLib_command                  (rexLangParser::Lib_commandContext *                  context) override;
        antlrcpp::Any visitGlobal_variable_list         (rexLangParser::Global_variable_listContext *         context) override;
        antlrcpp::Any visitGlobal_variable_item         (rexLangParser::Global_variable_itemContext *         context) override;
        antlrcpp::Any visitEdition_spec                 (rexLangParser::Edition_specContext *                 context) override;
        antlrcpp::Any visitStruct_declare               (rexLangParser::Struct_declareContext *               context) override;
        antlrcpp::Any visitTable_comment                (rexLangParser::Table_commentContext *                context) override;
        antlrcpp::Any visitProg_set                     (rexLangParser::Prog_setContext *                     context) override;
        antlrcpp::Any visitVariable_decl                (rexLangParser::Variable_declContext *                context) override;
        antlrcpp::Any visitSub_program                  (rexLangParser::Sub_programContext *                  context) override;
        antlrcpp::Any visitParameter_decl               (rexLangParser::Parameter_declContext *               context) override;
        antlrcpp::Any visitStatement_list               (rexLangParser::Statement_listContext *               context) override;
        antlrcpp::Any visitConditionStatement           (rexLangParser::ConditionStatementContext *           context) override;
        antlrcpp::Any visitAssignStatement              (rexLangParser::AssignStatementContext *              context) override;
        antlrcpp::Any visitExpressionStatement          (rexLangParser::ExpressionStatementContext *          context) override;
        antlrcpp::Any visitLoopStatement                (rexLangParser::LoopStatementContext *                context) override;
        antlrcpp::Any visitSwitchStatement              (rexLangParser::SwitchStatementContext *              context) override;
        antlrcpp::Any visitSwitch_statement             (rexLangParser::Switch_statementContext *             context) override;
        antlrcpp::Any visitWhile                        (rexLangParser::WhileContext *                        context) override;
        antlrcpp::Any visitRangeFor                     (rexLangParser::RangeForContext *                     context) override;
        antlrcpp::Any visitFor                          (rexLangParser::ForContext *                          context) override;
        antlrcpp::Any visitDoWhile                      (rexLangParser::DoWhileContext *                      context) override;
        antlrcpp::Any visitIfStmt                       (rexLangParser::IfStmtContext *                       context) override;
        antlrcpp::Any visitIfTrueStmt                   (rexLangParser::IfTrueStmtContext *                   context) override;
        antlrcpp::Any visitHierarchy_identifier         (rexLangParser::Hierarchy_identifierContext *         context) override;
        antlrcpp::Any visitFuncCall                     (rexLangParser::FuncCallContext *                     context) override;
        antlrcpp::Any visitIdentifier                   (rexLangParser::IdentifierContext *                   context) override;
        antlrcpp::Any visitArrayIndex                   (rexLangParser::ArrayIndexContext *                   context) override;
        antlrcpp::Any visitBracket                      (rexLangParser::BracketContext *                      context) override;
        antlrcpp::Any visitOptElement                   (rexLangParser::OptElementContext *                   context) override;
        antlrcpp::Any visitBinaryExpr                   (rexLangParser::BinaryExprContext *                   context) override;
        antlrcpp::Any visitUnaryExpr                    (rexLangParser::UnaryExprContext *                    context) override;
        antlrcpp::Any visitData_set_value               (rexLangParser::Data_set_valueContext *               context) override;
        antlrcpp::Any visitDatetime_value               (rexLangParser::Datetime_valueContext *               context) override;
        antlrcpp::Any visitDatetimePureNumber           (rexLangParser::DatetimePureNumberContext *           context) override;
        antlrcpp::Any visitDatetimeSeparateByChinese    (rexLangParser::DatetimeSeparateByChineseContext *    context) override;
        antlrcpp::Any visitDatetimeSeparateBySlash      (rexLangParser::DatetimeSeparateBySlashContext *      context) override;
        antlrcpp::Any visitDatetimeSeparateBySlashColon (rexLangParser::DatetimeSeparateBySlashColonContext * context) override;
        antlrcpp::Any visitDatetimeSeparateByBar        (rexLangParser::DatetimeSeparateByBarContext *        context) override;
        antlrcpp::Any visitDatetimeSeparateByBarColon   (rexLangParser::DatetimeSeparateByBarColonContext *   context) override;
        antlrcpp::Any visitMacro_value                  (rexLangParser::Macro_valueContext *                  context) override;
        antlrcpp::Any visitFunc_ptr                     (rexLangParser::Func_ptrContext *                     context) override;
        antlrcpp::Any visitBoolValueTrue                (rexLangParser::BoolValueTrueContext *                context) override;
        antlrcpp::Any visitBoolValueFalse               (rexLangParser::BoolValueFalseContext *               context) override;
        antlrcpp::Any visitInt                          (rexLangParser::IntContext *                          context) override;
        antlrcpp::Any visitFloat                        (rexLangParser::FloatContext *                        context) override;
        antlrcpp::Any visitString_value                 (rexLangParser::String_valueContext *                 context) override;
        antlrcpp::Any visitLocal_variable_decl          (rexLangParser::Local_variable_declContext *          context) override;
        antlrcpp::Any visitParameter_decl_list          (rexLangParser::Parameter_decl_listContext *          context) override;
        antlrcpp::Any visitVari_parameter_decl          (rexLangParser::Vari_parameter_declContext *          context) override;
        antlrcpp::Any visitMember_vari_decl             (rexLangParser::Member_vari_declContext *             context) override;
        antlrcpp::Any visitFile_vari_decl               (rexLangParser::File_vari_declContext *               context) override;
        antlrcpp::Any visitControlStatement             (rexLangParser::ControlStatementContext *             context) override;
        antlrcpp::Any visitContinueStmt                 (rexLangParser::ContinueStmtContext *                 context) override;
        antlrcpp::Any visitBreakStmt                    (rexLangParser::BreakStmtContext *                    context) override;
        antlrcpp::Any visitReturnStmt                   (rexLangParser::ReturnStmtContext *                   context) override;
        antlrcpp::Any visitExitStmt                     (rexLangParser::ExitStmtContext *                     context) override;
    public:
        CST2ASTConvert(ASTContext *ast_context, Diagnostic *diagnostic, REXCompilerInstance *compiler_instance);

        /*===---------------------------------------------===*
         * 从CST森林中构建AST
         */
        TranslateUnit * buildTUFromParseTrees(const std::vector<antlr4::tree::ParseTree *> &trees);
    };
}

#endif //REXLANG_CST2ASTCONVERT_H
