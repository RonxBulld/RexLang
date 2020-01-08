//
// Created by Administrator on 2019/12/13.
//

#include <cstring>
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

        long GetLongIfExist(const antlr4::Token *token, int hint = 0) const {
            if (token) {
                std::string __v = token->getText();
                return strtol(__v.c_str(), nullptr, 10);
            } else {
                return hint;
            }
        }

        float GetFloatIfExist(const antlr4::Token *token, float hint = 0.0f) const {
            if (token) {
                std::string __v = token->getText();
                return strtof(__v.c_str(), nullptr);
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

        template<typename T, bool must_valid = false>
        T GetFromCtxIfExist(antlr4::ParserRuleContext *ctx, const T &hint = T()) {
            if (ctx) {
                auto ret = visit(ctx);
                if (ret.is<T>()) {
                    return ret.as<T>();
                }
                assert(!must_valid);
            }
            assert(!must_valid);
            return hint;
        }

    public:
        antlrcpp::Any visitOpene_src(openeLangParser::Opene_srcContext *context) override {
            TranslateUnitPtr translate_unit = new TranslateUnit;
            // 分析版本号
            translate_unit->edition_ = GetFromCtxIfExist<unsigned int, true>(context->edition_spec(), 2);
            // 分析文件具体内容
            translate_unit->source_file_ = GetFromCtxIfExist<SourceFilePtr, true>(context->src_content());
            return translate_unit;
        }

        antlrcpp::Any visitSrc_content(openeLangParser::Src_contentContext *context) override {
            if (openeLangParser::Program_set_fileContext* program_set_file_ctx = context->program_set_file()) {
                return GetFromCtxIfExist<ProgramSetFilePtr, true>(program_set_file_ctx);
            } else if (openeLangParser::Data_structure_fileContext *data_structure_file_ctx = context->data_structure_file()) {
                return GetFromCtxIfExist<DataStructureFilePtr, true>(data_structure_file_ctx);
            } else if (openeLangParser::Global_variable_fileContext *global_variable_file_ctx = context->global_variable_file()) {
                return GetFromCtxIfExist<GlobalVariableFilePtr, true>(global_variable_file_ctx);
            } else if (openeLangParser::Dll_define_fileContext *dll_define_file_ctx = context->dll_define_file()) {
                return GetFromCtxIfExist<DllDefineFilePtr, true>(dll_define_file_ctx);
            } else {
                // TODO: ERROR.
                return antlrcpp::Any();
            }
        }

        antlrcpp::Any visitProgram_set_file(openeLangParser::Program_set_fileContext *context) override {
            ProgramSetFilePtr program_set_file = new ProgramSetFile;
            for (antlr4::Token *token : context->libraries) {
                program_set_file->libraries_.push_back(GetTextIfExist(token));
            }
            program_set_file->program_set_declares_ = GetFromCtxIfExist<ProgSetDeclPtr>(context->prog_set());
            program_set_file->file_type_ = SourceFile::FileType::kProgramSetFile;
            return program_set_file;
        }

        antlrcpp::Any visitData_structure_file(openeLangParser::Data_structure_fileContext *context) override {
            DataStructureFilePtr data_structure_file = new DataStructureFile;
            for (auto *struct_decl_ctx : context->struct_declare()) {
                 StructureDeclPtr structure_decl = GetFromCtxIfExist<StructureDeclPtr>(struct_decl_ctx);
                 data_structure_file->structure_decl_map_[structure_decl->name_] = structure_decl;
            }
            data_structure_file->file_type_ = SourceFile::FileType::kDataStructureFile;
            return data_structure_file;
        }

        antlrcpp::Any visitGlobal_variable_file(openeLangParser::Global_variable_fileContext *context) override {
            GlobalVariableFilePtr global_variable_file = new GlobalVariableFile;
            global_variable_file->global_variable_map_ = GetFromCtxIfExist<decltype(GlobalVariableFile::global_variable_map_)>(context->global_variable_list());
            global_variable_file->file_type_ = SourceFile::FileType::kGlobalVariableFile;
            return global_variable_file;
        }

        antlrcpp::Any visitDll_define_file(openeLangParser::Dll_define_fileContext *context) override {
            DllDefineFilePtr dll_define_file = new DllDefineFile;
            for (auto *dll_cmd_decl_ctx : context->dll_command()) {
                DllCommandDeclPtr dll_command_decl = GetFromCtxIfExist<DllCommandDeclPtr>(dll_cmd_decl_ctx);
                dll_define_file->dll_declares_[dll_command_decl->name_] = dll_command_decl;
            }
            dll_define_file->file_type_ = SourceFile::FileType::kDllDefineFile;
            return dll_define_file;
        }

        antlrcpp::Any visitDll_command(openeLangParser::Dll_commandContext *context) override {
            DllCommandDeclPtr dll_command_decl = new DllCommandDecl;
            dll_command_decl->name_ = GetTextIfExist(context->name);
            dll_command_decl->type_ = GetTextIfExist(context->type);
            dll_command_decl->file_ = GetTextIfExist(context->file);
            dll_command_decl->api_name_ = GetTextIfExist(context->cmd);
            dll_command_decl->comment_ = GetFromCtxIfExist<std::string>(context->table_comment());
            for (openeLangParser::Parameter_declContext *param : context->parameter_decl()) {
                ParameterDeclPtr parameter_decl = GetFromCtxIfExist<ParameterDeclPtr>(param);
                dll_command_decl->parameters_[parameter_decl->name_] = parameter_decl;
            }
            return dll_command_decl;
        }

        antlrcpp::Any visitGlobal_variable_list(openeLangParser::Global_variable_listContext *context) override {
            decltype(GlobalVariableFile::global_variable_map_) global_variable_decl_map;
            for (auto *global_vari_decl_ctx : context->global_variable_item()) {
                GlobalVariableDeclPtr global_variable_decl = GetFromCtxIfExist<GlobalVariableDeclPtr>(global_vari_decl_ctx);
                global_variable_decl_map[global_variable_decl->name_] = global_variable_decl;
            }
            return global_variable_decl_map;
        }

        antlrcpp::Any visitGlobal_variable_item(openeLangParser::Global_variable_itemContext *context) override {
            GlobalVariableDeclPtr global_variable_decl = new GlobalVariableDecl;
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
                VariableDeclPtr member = GetFromCtxIfExist<VariableDeclPtr>(mem_ctx);
                structure_decl->members_[member->name_] = member;
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
                VariableDeclPtr vari_decl = GetFromCtxIfExist<VariableDeclPtr>(vari_ctx);
                prog_set_decl->file_static_variables_[vari_decl->name_] = vari_decl;
            }
            for (auto *func_ctx : context->functions) {
                SubProgDeclPtr sub_prog_decl = GetFromCtxIfExist<SubProgDeclPtr>(func_ctx);
                prog_set_decl->function_decls_[sub_prog_decl->name_] = sub_prog_decl;
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
                ParameterDeclPtr parameter_decl = GetFromCtxIfExist<ParameterDeclPtr>(param_vari_ctx);
                sub_prog_decl->parameters_.emplace_back(parameter_decl);
            }
            for (auto *local_vari_ctx : context->local_vari) {
                VariableDeclPtr local_vari = GetFromCtxIfExist<VariableDeclPtr>(local_vari_ctx);
                sub_prog_decl->local_vari_[local_vari->name_] = local_vari;
            }
            sub_prog_decl->statement_list_ = GetFromCtxIfExist<StatementListPtr>(context->statement_list());
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
            StatementListPtr statement_list = new StatementList;
            for (auto *stmt_ctx : context->stmts) {
                statement_list->statements_.push_back(GetFromCtxIfExist<StatementPtr>(stmt_ctx));
            }
            return statement_list;
        }

        antlrcpp::Any visitConditionStatement(openeLangParser::ConditionStatementContext *context) override {
            return GetFromCtxIfExist<StatementPtr>(context->condition_statement());
        }

        antlrcpp::Any visitAssignStatement(openeLangParser::AssignStatementContext *context) override {
            AssignStmtPtr assign_stmt = new AssignStmt;
            assign_stmt->lhs_ = GetFromCtxIfExist<HierarchyIdentifierPtr>(context->hierarchy_identifier());
            assign_stmt->rhs_ = GetFromCtxIfExist<ExpressionPtr>(context->expression());
            return assign_stmt;
        }

        antlrcpp::Any visitExpressionStatement(openeLangParser::ExpressionStatementContext *context) override {
            return GetFromCtxIfExist<StatementPtr>(context->expression());
        }

        antlrcpp::Any visitLoopStatement(openeLangParser::LoopStatementContext *context) override {
            return GetFromCtxIfExist<StatementPtr>(context->loop_statement());
        }

        antlrcpp::Any visitSwitchStatement(openeLangParser::SwitchStatementContext *context) override {
            return GetFromCtxIfExist<StatementPtr>(context->switch_statement());
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
            FunctionCallPtr function_call = new FunctionCall;
            function_call->function_name_ = GetFromCtxIfExist<NameComponentPtr>(context->name_component());
            for (auto *arg_ctx : context->arguments) {
                ExpressionPtr arg_expr = GetFromCtxIfExist<ExpressionPtr>(arg_ctx);
                function_call->arguments_.push_back(arg_expr);
            }
            return function_call;
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
            return GetFromCtxIfExist<ExpressionPtr>(context->expression());
        }

        antlrcpp::Any visitOptElement(openeLangParser::OptElementContext *context) override {
            return GetFromCtxIfExist<ExpressionPtr>(context->getRuleContext<antlr4::ParserRuleContext>(0));
        }

        antlrcpp::Any visitBinaryExpr(openeLangParser::BinaryExprContext *context) override {
            BinaryExpressionPtr binary_expression = new BinaryExpression;
            binary_expression->operator_ = GetTextIfExist(context->opt);
            binary_expression->lhs_ = GetFromCtxIfExist<ExpressionPtr>(context->lval);
            binary_expression->rhs_ = GetFromCtxIfExist<ExpressionPtr>(context->rval);
            return binary_expression;
        }

        antlrcpp::Any visitUnaryExpr(openeLangParser::UnaryExprContext *context) override {
            UnaryExpressionPtr unary_expression = new UnaryExpression;
            unary_expression->operator_ = GetTextIfExist(context->opt);
            unary_expression->op_value_ = GetFromCtxIfExist<ExpressionPtr>(context->expression());
            return unary_expression;
        }

        antlrcpp::Any visitData_set_value(openeLangParser::Data_set_valueContext *context) override {
            ValueOfDataSetPtr value_of_data_set = new ValueOfDataSet;
            for (auto *elem_ctx : context->elems) {
                value_of_data_set->elements_.push_back(GetFromCtxIfExist<ExpressionPtr>(elem_ctx));
            }
            return value_of_data_set;
        }

        antlrcpp::Any visitDatetime_value(openeLangParser::Datetime_valueContext *context) override {
            return GetFromCtxIfExist<ValueOfDatetimePtr>(context->datetime_value_core());
        }

        ValueOfDatetimePtr TimeNodeBuilder(time_t time) {
            ValueOfDatetimePtr value_of_datetime = new ValueOfDatetime;
            value_of_datetime->time_ = time;
            return value_of_datetime;
        }

        antlrcpp::Any visitDatetimePureNumber(openeLangParser::DatetimePureNumberContext *context) override {
            std::string time_str = GetTextIfExist(context->time);
            return TimeNodeBuilder(strtoul(time_str.c_str(), nullptr, 10));
        }

        tm TimeBuilder(unsigned year, unsigned month, unsigned day, unsigned hour, unsigned minute, unsigned second) {
            tm new_time;
            memset(&new_time, '\0', sizeof(tm));
            new_time.tm_year = year;
            new_time.tm_mon = month;
            new_time.tm_mday = day;
            new_time.tm_hour = hour;
            new_time.tm_min = minute;
            new_time.tm_sec = second;
            return new_time;
        }

        ValueOfDatetimePtr TimeNodeBuilder(tm && stm) {
            return TimeNodeBuilder(mktime(&stm));
        }

        antlrcpp::Any visitDatetimeSeparateByChinese(openeLangParser::DatetimeSeparateByChineseContext *context) override {
            ValueOfDatetimePtr new_time = TimeNodeBuilder(TimeBuilder(
                    GetLongIfExist(context->year),
                    GetLongIfExist(context->month),
                    GetLongIfExist(context->day),
                    GetLongIfExist(context->hour),
                    GetLongIfExist(context->minute),
                    GetLongIfExist(context->second)
            ));
            return new_time;
        }

        antlrcpp::Any visitDatetimeSeparateBySlash(openeLangParser::DatetimeSeparateBySlashContext *context) override {
            ValueOfDatetimePtr new_time = TimeNodeBuilder(TimeBuilder(
                    GetLongIfExist(context->year),
                    GetLongIfExist(context->month),
                    GetLongIfExist(context->day),
                    GetLongIfExist(context->hour),
                    GetLongIfExist(context->minute),
                    GetLongIfExist(context->second)
            ));
            return new_time;
        }

        antlrcpp::Any visitDatetimeSeparateBySlashColon(openeLangParser::DatetimeSeparateBySlashColonContext *context) override {
            ValueOfDatetimePtr new_time = TimeNodeBuilder(TimeBuilder(
                    GetLongIfExist(context->year),
                    GetLongIfExist(context->month),
                    GetLongIfExist(context->day),
                    GetLongIfExist(context->hour),
                    GetLongIfExist(context->minute),
                    GetLongIfExist(context->second)
            ));
            return new_time;
        }

        antlrcpp::Any visitDatetimeSeparateByBar(openeLangParser::DatetimeSeparateByBarContext *context) override {
            ValueOfDatetimePtr new_time = TimeNodeBuilder(TimeBuilder(
                    GetLongIfExist(context->year),
                    GetLongIfExist(context->month),
                    GetLongIfExist(context->day),
                    GetLongIfExist(context->hour),
                    GetLongIfExist(context->minute),
                    GetLongIfExist(context->second)
            ));
            return new_time;
        }

        antlrcpp::Any visitDatetimeSeparateByBarColon(openeLangParser::DatetimeSeparateByBarColonContext *context) override {
            ValueOfDatetimePtr new_time = TimeNodeBuilder(TimeBuilder(
                    GetLongIfExist(context->year),
                    GetLongIfExist(context->month),
                    GetLongIfExist(context->day),
                    GetLongIfExist(context->hour),
                    GetLongIfExist(context->minute),
                    GetLongIfExist(context->second)
            ));
            return new_time;
        }

        antlrcpp::Any visitMacro_value(openeLangParser::Macro_valueContext *context) override {
            ResourceRefExpressionPtr resource_ref_expression = new ResourceRefExpression;
            resource_ref_expression->resource_name_ = GetTextIfExist(context->IDENTIFIER()->getSymbol());
            return resource_ref_expression;
        }

        antlrcpp::Any visitFunc_ptr(openeLangParser::Func_ptrContext *context) override {
            FuncAddrExpressionPtr func_addr_expression = new FuncAddrExpression;
            func_addr_expression->function_name_ = GetTextIfExist(context->IDENTIFIER()->getSymbol());
            return func_addr_expression;
        }

        antlrcpp::Any visitBoolValueTrue(openeLangParser::BoolValueTrueContext *context) override {
            ValueOfBoolPtr value_of_bool = new ValueOfBool;
            value_of_bool->value_ = true;
            return value_of_bool;
        }

        antlrcpp::Any visitBoolValueFalse(openeLangParser::BoolValueFalseContext *context) override {
            ValueOfBoolPtr value_of_bool = new ValueOfBool;
            value_of_bool->value_ = false;
            return value_of_bool;
        }

        antlrcpp::Any visitInt(openeLangParser::IntContext *context) override {
            ValueOfDecimalPtr value_of_decimal = new ValueOfDecimal;
            value_of_decimal->int_val_ = GetLongIfExist(context->INTEGER_LITERAL()->getSymbol());
            value_of_decimal->type_ = ValueOfDecimal::type::kInt;
            return value_of_decimal;
        }

        antlrcpp::Any visitFloat(openeLangParser::FloatContext *context) override {
            ValueOfDecimalPtr value_of_decimal = new ValueOfDecimal;
            value_of_decimal->float_val_ = GetFloatIfExist(context->FLOAT_LITERAL()->getSymbol());
            value_of_decimal->type_ = ValueOfDecimal::type::kFloat;
            return value_of_decimal;
        }

        antlrcpp::Any visitString_value(openeLangParser::String_valueContext *context) override {
            ValueOfStringPtr value_of_string = new ValueOfString;
            value_of_string->string_literal_ = GetTextIfExist(context->STRING_LITERAL()->getSymbol());
            return value_of_string;
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