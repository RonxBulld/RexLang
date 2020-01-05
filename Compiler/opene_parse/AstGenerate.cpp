//
// Created by Administrator on 2019/12/13.
//

#include <ANTLRFileStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>

#include "AstGenerate.h"
#include "Diagnostic.h"
#include "gen/openeLangLexer.h"
#include "gen/openeLangParser.h"
#include "gen/openeLangVisitor.h"

#include "node_decl.h"

namespace opene {
    class ASTBuilder : public openeLangVisitor {
    private:
        std::string GetTextIfExist(const antlr4::Token *token, const std::string &hint = "") const {
            if (token) {
                return token->getText();
            } else {
                return hint;
            }
        }

        std::vector<std::string> GetTextVecIfExist(const std::vector<antlr4::Token *> tokens, const std::string &hint = "") const {
            std::vector<std::string> tokens_str_vec;
            for (auto *tk : tokens) {
                tokens_str_vec.emplace_back(GetTextIfExist(tk, hint));
            }
            return tokens_str_vec;
        }

        template<typename T>
        T GetFromCtxIfExist(antlr4::ParserRuleContext *ctx, const T &hint = T()) {
            if (ctx) {
                auto ret = visit(ctx);
                if (ret.is<T>()) {
                    return ret.as<T>();
                }
            }
            return hint;
        }

    public:
        antlrcpp::Any visitOpene_src(openeLangParser::Opene_srcContext *context) override {
            TranslateUnitPtr translate_unit = new TranslateUnit;
            // 分析版本号
            translate_unit->edition_ = GetFromCtxIfExist<unsigned int>(context->edition_spec(), 2);
            // 分析文件具体内容
            auto content_ret = visit(context->src_content());
            // TODO: 将文件内容加入翻译单元
            return translate_unit;
        }

        antlrcpp::Any visitSrc_content(openeLangParser::Src_contentContext *context) override {
            if (openeLangParser::Program_set_fileContext* program_set_file_ctx = context->program_set_file()) {
                return visit(program_set_file_ctx);
            } else if (openeLangParser::Data_structure_fileContext *data_structure_file_ctx = context->data_structure_file()) {
                return visit(data_structure_file_ctx);
            } else if (openeLangParser::Global_variable_fileContext *global_variable_file_ctx = context->global_variable_file()) {
                return visit(global_variable_file_ctx);
            } else if (openeLangParser::Dll_define_fileContext *dll_define_file_ctx = context->dll_define_file()) {
                return visit(dll_define_file_ctx);
            } else {
                // TODO: ERROR.
            }
            return antlrcpp::Any();
        }

        antlrcpp::Any visitProgram_set_file(openeLangParser::Program_set_fileContext *context) override {
            std::vector<antlr4::Token *> support_libraries = context->libraries;
            ProgramUnitPtr program_unit = new ProgramUnit;
            for (antlr4::Token *token : support_libraries) {
                program_unit->libraries_.push_back(GetTextIfExist(token));
            }
            auto progs = visit(context->prog_set());
            // TODO: 设置程序定义
            return program_unit;
        }

        antlrcpp::Any visitData_structure_file(openeLangParser::Data_structure_fileContext *context) override {
            for (auto *struct_decl_ctx : context->struct_declare()) {
                visit(struct_decl_ctx);
                // TODO: 将结构体定义结果加入到结果集中
            }
            // TODO: 返回结果集
            return antlrcpp::Any();
        }

        antlrcpp::Any visitGlobal_variable_file(openeLangParser::Global_variable_fileContext *context) override {
            if (context->global_variable_list()) {
                return visit(context->global_variable_list());
            } else {
                return antlrcpp::Any();
            }
        }

        antlrcpp::Any visitDll_define_file(openeLangParser::Dll_define_fileContext *context) override {
            for (auto *dll_cmd_decl_ctx : context->dll_command()) {
                visit(dll_cmd_decl_ctx);
                // TODO: 将DLL接口定义结果加入到结果集中
            }
            // TODO: 返回结果集
            return antlrcpp::Any();
        }

        antlrcpp::Any visitDll_command(openeLangParser::Dll_commandContext *context) override {
            DllCommandDeclPtr dll_command_decl = new DllCommandDecl;
            dll_command_decl->api_name_ = GetTextIfExist(context->name);
            dll_command_decl->type_ = GetTextIfExist(context->type);
            dll_command_decl->file_ = GetTextIfExist(context->file);
            dll_command_decl->dll_api_name_ = GetTextIfExist(context->cmd);
            if (context->table_comment()) {
                auto comment_ret = visit(context->table_comment());
                // TODO: 设置注释内容
            }
            for (openeLangParser::Parameter_declContext *param : context->parameter_decl()) {
                auto param_ret = visit(param);
                // TODO: 将参数定义加入到参数列表中
            }
            return dll_command_decl;
        }

        antlrcpp::Any visitGlobal_variable_list(openeLangParser::Global_variable_listContext *context) override {
            for (auto *global_vari_decl_ctx : context->global_variable_item()) {
                visit(global_vari_decl_ctx);
                // TODO: 将全局变量定义加入到全局变量集中
            }
            // TODO: 返回结果集
            return antlrcpp::Any();
        }

        antlrcpp::Any visitGlobal_variable_item(openeLangParser::Global_variable_itemContext *context) override {
            GlobalVariableDeclPtr global_variable_decl;
            global_variable_decl->name_ = GetTextIfExist(context->name);
            global_variable_decl->type_ = GetTextIfExist(context->type);
            global_variable_decl->dimension_ = GetTextIfExist(context->dimension);
            global_variable_decl->access_ = GetTextIfExist(context->access);
            global_variable_decl->comment_ = GetFromCtxIfExist<std::string>(context->table_comment());
            return global_variable_decl;
        }

        antlrcpp::Any visitEdition_spec(openeLangParser::Edition_specContext *context) override {
            return (unsigned int)strtoul(context->INTEGER_LITERAL()->getText().c_str(), nullptr, 10);;
        }

        antlrcpp::Any visitStruct_declare(openeLangParser::Struct_declareContext *context) override {
            StructureDeclPtr structure_decl = new StructureDecl;
            structure_decl->name_ = GetTextIfExist(context->name);
            structure_decl->access_ = GetTextIfExist(context->access);
            structure_decl->comment_ = GetFromCtxIfExist<std::string>(context->table_comment());
            for (auto *mem_ctx : context->struct_mems) {
                // TODO: 需要添加成员实现
            }
            return structure_decl;
        }

        antlrcpp::Any visitTable_comment(openeLangParser::Table_commentContext *context) override {
            return GetTextIfExist(context->comment);
        }

        antlrcpp::Any visitProg_set(openeLangParser::Prog_setContext *context) override {
            ProgSetDeclPtr prog_set_decl = new ProgSetDecl;
            prog_set_decl->name_ = GetTextIfExist(context->name);
            prog_set_decl->base_ = GetTextIfExist(context->base);
            prog_set_decl->access_ = GetTextIfExist(context->access);
            prog_set_decl->comment_ = GetFromCtxIfExist<std::string>(context->table_comment());
            for (auto *vari_ctx : context->prog_set_varis) {
                // TODO: 需要添加程序集变量实现
            }
            for (auto *func_ctx : context->functions) {
                // TODO: 需要添加子程序实现
            }
            return prog_set_decl;
        }

        antlrcpp::Any visitVariable_decl(openeLangParser::Variable_declContext *context) override {
            VariableDeclPtr variable_decl = new VariableDecl;
            variable_decl->name_ = GetTextIfExist(context->name);
            variable_decl->type_ = GetTextIfExist(context->type);
            variable_decl->dimension_ = GetTextIfExist(context->dimension);
            variable_decl->comment_ = GetFromCtxIfExist<std::string>(context->table_comment());
            return variable_decl;
        }

        antlrcpp::Any visitSub_program(openeLangParser::Sub_programContext *context) override {
            SubProgDeclPtr sub_prog_decl = new SubProgDecl;
            sub_prog_decl->name_ = GetTextIfExist(context->name);
            sub_prog_decl->type_ = GetTextIfExist(context->type);
            sub_prog_decl->access_ = GetTextIfExist(context->access);
            sub_prog_decl->comment_ = GetFromCtxIfExist<std::string>(context->table_comment());
            for (auto *param_vari_ctx : context->params) {
                ParameterDeclPtr parameter_decl = visit(param_vari_ctx).as<ParameterDeclPtr>();
                sub_prog_decl->parameters_.emplace_back(parameter_decl);
            }
            for (auto *local_vari_ctx : context->local_vari) {
                VariableDeclPtr local_vari = visit(local_vari_ctx).as<VariableDeclPtr>();
                sub_prog_decl->local_vari_[local_vari->name_] = local_vari;
            }
            // TODO: 语句和表达式
            return sub_prog_decl;
        }

        antlrcpp::Any visitParameter_decl(openeLangParser::Parameter_declContext *context) override {
            ParameterDeclPtr parameter_decl = new ParameterDecl;
            parameter_decl->name_ = GetTextIfExist(context->name);
            parameter_decl->type_ = GetTextIfExist(context->type);
            parameter_decl->attributes_ = GetTextVecIfExist(context->attributes);
            parameter_decl->comment_ = GetFromCtxIfExist<std::string>(context->table_comment());
            return parameter_decl;
        }

        antlrcpp::Any visitStatement_list(openeLangParser::Statement_listContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitConditionStatement(openeLangParser::ConditionStatementContext *context) override {
            return visit(context->condition_statement());
        }

        antlrcpp::Any visitAssignStatement(openeLangParser::AssignStatementContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitExpressionStatement(openeLangParser::ExpressionStatementContext *context) override {
            return visit(context->expression());
        }

        antlrcpp::Any visitLoopStatement(openeLangParser::LoopStatementContext *context) override {
            return visit(context->loop_statement());
        }

        antlrcpp::Any visitSwitchStatement(openeLangParser::SwitchStatementContext *context) override {
            return visit(context->switch_statement());
        }

        antlrcpp::Any visitSwitch_statement(openeLangParser::Switch_statementContext *context) override {
            IfStmtPtr switch_stmt = new IfStmt;
            ExpressionPtr major_cond_expr = GetFromCtxIfExist<ExpressionPtr>(context->major_condition_expr);
            StatementPtr major_cond_body = GetFromCtxIfExist<StatementPtr>(context->major_cond_body);
            switch_stmt->switches_.push_back(std::pair(major_cond_expr, major_cond_body));
            assert(context->minor_condition_expr.size() == context->minor_cond_body.size());
            for (size_t idx = 0; idx < context->minor_condition_expr.size(); idx++) {
                ExpressionPtr minor_cond_expr = GetFromCtxIfExist<ExpressionPtr>(context->minor_condition_expr[idx]);
                StatementPtr minor_cond_body = GetFromCtxIfExist<StatementPtr>(context->minor_cond_body[idx]);
                switch_stmt->switches_.push_back(std::pair(minor_cond_expr, minor_cond_body));
            }
            switch_stmt->default_statement_ = GetFromCtxIfExist<StatementPtr>(context->default_body);
            return switch_stmt;
        }

        antlrcpp::Any visitWhile(openeLangParser::WhileContext *context) override {
            WhileStmtPtr while_stmt = new WhileStmt;
            while_stmt->condition_ = GetFromCtxIfExist<ExpressionPtr>(context->condition_expr);
            while_stmt->loop_body_ = GetFromCtxIfExist<StatementPtr>(context->loop_body);
            return while_stmt;
        }

        antlrcpp::Any visitRangeFor(openeLangParser::RangeForContext *context) override {
            RangeForStmtPtr range_for_stmt = new RangeForStmt;
            range_for_stmt->range_size_ = GetFromCtxIfExist<ExpressionPtr>(context->times_expr);
            range_for_stmt->loop_vari_ = GetTextIfExist(context->loop_variable);
            range_for_stmt->loop_body_ = GetFromCtxIfExist<StatementPtr>(context->loop_body);
            return range_for_stmt;
        }

        antlrcpp::Any visitFor(openeLangParser::ForContext *context) override {
            ForStmtPtr for_stmt = new ForStmt;
            for_stmt->start_value_ = GetFromCtxIfExist<ExpressionPtr>(context->loop_start);
            for_stmt->stop_value_ = GetFromCtxIfExist<ExpressionPtr>(context->loop_end);
            for_stmt->step_value_ = GetFromCtxIfExist<ExpressionPtr>(context->loop_step);
            for_stmt->loop_vari_ = GetFromCtxIfExist<HierarchyIdentifierPtr>(context->loop_variable);
            return for_stmt;
        }

        antlrcpp::Any visitDoWhile(openeLangParser::DoWhileContext *context) override {
            DoWhileStmtPtr do_while_stmt = new DoWhileStmt;
            do_while_stmt->loop_body_ = GetFromCtxIfExist<StatementPtr>(context->loop_body);
            do_while_stmt->conditon_ = GetFromCtxIfExist<ExpressionPtr>(context->condition_expr);
            return do_while_stmt;
        }

        antlrcpp::Any visitIfStmt(openeLangParser::IfStmtContext *context) override {
            IfStmtPtr if_stmt = new IfStmt;
            ExpressionPtr condition = GetFromCtxIfExist<ExpressionPtr>(context->condition_expr);
            StatementPtr true_statement = GetFromCtxIfExist<StatementPtr>(context->true_stmt_list);
            if_stmt->switches_.push_back(std::pair(condition, true_statement));
            if_stmt->default_statement_ = GetFromCtxIfExist<StatementPtr>(context->false_stmt_list);
            return if_stmt;
        }

        antlrcpp::Any visitIfTrueStmt(openeLangParser::IfTrueStmtContext *context) override {
            IfStmtPtr if_stmt = new IfStmt;
            ExpressionPtr condition = GetFromCtxIfExist<ExpressionPtr>(context->condition_expr);
            StatementPtr true_statement = GetFromCtxIfExist<StatementPtr>(context->true_stmt_list);
            if_stmt->switches_.push_back(std::pair(condition, true_statement));
            return if_stmt;
        }

        antlrcpp::Any visitHierarchy_identifier(openeLangParser::Hierarchy_identifierContext *context) override {
            HierarchyIdentifierPtr hierarchy_identifier = new HierarchyIdentifier;
            for (auto *name_component_ctx : context->components) {
                NameComponentPtr name_component = GetFromCtxIfExist<NameComponentPtr>(name_component_ctx);
                hierarchy_identifier->name_components_.push_back(name_component);
            }
            return hierarchy_identifier;
        }

        antlrcpp::Any visitFuncCall(openeLangParser::FuncCallContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitIdentifier(openeLangParser::IdentifierContext *context) override {
            NameComponentPtr name_component = new NameComponent;
            name_component->name_ = GetTextIfExist(context->IDENTIFIER()->getSymbol());
            return name_component;
        }

        antlrcpp::Any visitArrayIndex(openeLangParser::ArrayIndexContext *context) override {
            NameComponentPtr name_component = new NameComponent;
            name_component->base_ = GetFromCtxIfExist<NameComponentPtr>(context->name_component());
            name_component->index_ = GetFromCtxIfExist<ExpressionPtr>(context->expression());
            return name_component;
        }

        antlrcpp::Any visitBracket(openeLangParser::BracketContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitOptElement(openeLangParser::OptElementContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitBinaryExpr(openeLangParser::BinaryExprContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitUnaryExpr(openeLangParser::UnaryExprContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitData_set_value(openeLangParser::Data_set_valueContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitDatetime_value(openeLangParser::Datetime_valueContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitDatetimePureNumber(openeLangParser::DatetimePureNumberContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitDatetimeSeparateByChinese(openeLangParser::DatetimeSeparateByChineseContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitDatetimeSeparateBySlash(openeLangParser::DatetimeSeparateBySlashContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitDatetimeSeparateBySlashColon(openeLangParser::DatetimeSeparateBySlashColonContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitDatetimeSeparateByBar(openeLangParser::DatetimeSeparateByBarContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitDatetimeSeparateByBarColon(openeLangParser::DatetimeSeparateByBarColonContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitMacro_value(openeLangParser::Macro_valueContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitFunc_ptr(openeLangParser::Func_ptrContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitBool_value(openeLangParser::Bool_valueContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitInt(openeLangParser::IntContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitFloat(openeLangParser::FloatContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitString_value(openeLangParser::String_valueContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }


    };
}

namespace opene {
    int AstGenerate::BuildASTFromCode(const std::string &code,
                                      const std::string &filename,
                                      const std::string &toolname) {
        // 配置解析源。
        antlr4::ANTLRInputStream __input_stream(code);
        __input_stream.name = filename;
        openeLangLexer __lexer(&__input_stream);
        antlr4::CommonTokenStream __token_stream(&__lexer);
        openeLangParser __parser(&__token_stream);
        // 设置自定义诊断监听器。
        __parser.removeErrorListeners();
        __parser.addErrorListener(new Diagnostic());
        // 执行语法分析。
        antlr4::tree::ParseTree* __tree = __parser.opene_src();
        // 遍历树以生成抽象语法树。
        ASTBuilder ast_builder;
        ast_builder.visit(__tree);

        std::cout << __tree->toStringTree(&__parser) << std::endl;

        return 0;
    }

    int AstGenerate::BuildASTFromCodeWithArgs(const std::string &code,
                                              const std::vector<std::string> &args,
                                              const std::string &filename,
                                              const std::string &toolname) {
        return this->BuildASTFromCodeWithArgs(code, {}, filename, toolname);
    }
}