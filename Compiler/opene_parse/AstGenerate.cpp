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
    public:
        antlrcpp::Any visitOpene_src(openeLangParser::Opene_srcContext *context) override {
            TranslateUnit translate_unit{0};
            // 分析版本号
            if (context->edition_spec()) {
                auto edition_spec_ret = visit(context->edition_spec());
                unsigned int edition_number = edition_spec_ret.as<unsigned int>();
                translate_unit.edition_ = edition_number;
            } else {
                // TODO: ERROR.
            }
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
            ProgramUnit program_unit;
            for (antlr4::Token *token : support_libraries) {
                program_unit.libraries_.push_back(token->getText());
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
            DllCommandDecl dll_command_decl;
            dll_command_decl.api_name_ = context->name->getText();
            dll_command_decl.type_ = context->type->getText();
            dll_command_decl.file_ = context->file->getText();
            dll_command_decl.dll_api_name_ = context->cmd->getText();
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
            GlobalVariableDecl global_variable_decl;
            global_variable_decl.name_ = context->name->getText();
            if (context->type) {
                global_variable_decl.type_ = context->type->getText();
            }
            if (context->dimension) {
                global_variable_decl.dimension_ = context->dimension->getText();
            }
            if (context->access) {
                global_variable_decl.access_ = context->access->getText();
            }
            if (context->table_comment()) {
                global_variable_decl.comment_ = context->table_comment()->getText();
            }
            return global_variable_decl;
        }

        antlrcpp::Any visitEdition_spec(openeLangParser::Edition_specContext *context) override {
            return (unsigned int)strtoul(context->INTEGER_LITERAL()->getText().c_str(), nullptr, 10);;
        }

        antlrcpp::Any visitStruct_declare(openeLangParser::Struct_declareContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitTable_comment(openeLangParser::Table_commentContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitProg_set(openeLangParser::Prog_setContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitVariable_decl(openeLangParser::Variable_declContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitSub_program(openeLangParser::Sub_programContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitParameter_decl(openeLangParser::Parameter_declContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitStatement_list(openeLangParser::Statement_listContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitConditionStatement(openeLangParser::ConditionStatementContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitAssignStatement(openeLangParser::AssignStatementContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitExpressionStatement(openeLangParser::ExpressionStatementContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitLoopStatement(openeLangParser::LoopStatementContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitSwitchStatement(openeLangParser::SwitchStatementContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitSwitch_statement(openeLangParser::Switch_statementContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitWhile(openeLangParser::WhileContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitRangeFor(openeLangParser::RangeForContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitFor(openeLangParser::ForContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitDoWhile(openeLangParser::DoWhileContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitIfStmt(openeLangParser::IfStmtContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitIfTrueStmt(openeLangParser::IfTrueStmtContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitHierarchy_identifier(openeLangParser::Hierarchy_identifierContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitFuncCall(openeLangParser::FuncCallContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitIdentifier(openeLangParser::IdentifierContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
        }

        antlrcpp::Any visitArrayIndex(openeLangParser::ArrayIndexContext *context) override {
            // TODO: 需要实现
            return antlrcpp::Any();
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