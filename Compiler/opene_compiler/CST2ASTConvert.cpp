//
// Created by rex on 2020/1/23.
//

#include <cstring>

#include "gen/openeLangLexer.h"
#include "gen/openeLangParser.h"
#include "gen/openeLangVisitor.h"

#include "CST2ASTConvert.h"
#include "NodeDecl.h"
#include "ASTContext.h"

namespace opene {
    void CST2ASTConvert::RemoveRoundQuotes(TString &tString) const {
        if (!tString.string_.empty()&& tString.string_.str().front() == '"' && tString.string_.str().back() == '"') {
            std::string _string = tString.string_.str();
            _string = _string.substr(1, _string.length() - 2);
            tString.string_ = this->ast_context_->CreateString(_string);
        }
    }

    TString CST2ASTConvert::GetTextIfExist(const antlr4::Token *token, const std::string &hint) const {
        TString t_string;
        if (token) {
            t_string.string_ = this->ast_context_->CreateString(token->getText());
            antlr4::TokenSource *ts = token->getTokenSource();
            t_string.location_ = this->ast_context_->CreateLocation(ts->getSourceName(), ts->getLine(), ts->getCharPositionInLine());
        } else {
            t_string.string_ = this->ast_context_->CreateString(hint);
        }
        return t_string;
    }

    long CST2ASTConvert::GetLongIfExist(const antlr4::Token *token, int hint) const {
        if (token) {
            std::string __v = token->getText();
            return strtol(__v.c_str(), nullptr, 10);
        } else {
            return hint;
        }
    }

    float CST2ASTConvert::GetFloatIfExist(const antlr4::Token *token, float hint) const {
        if (token) {
            std::string __v = token->getText();
            return strtof(__v.c_str(), nullptr);
        } else {
            return hint;
        }
    }

    std::vector<TString> CST2ASTConvert::GetTextVecIfExist(const std::vector<antlr4::Token *> tokens, const std::string &hint) const {
        std::vector<TString> tokens_str_vec;
        for (auto *tk : tokens) {
            tokens_str_vec.emplace_back(GetTextIfExist(tk, hint));
        }
        return tokens_str_vec;
    }

    template<typename T, bool must_valid, typename, typename>
    T CST2ASTConvert::GetFromCtxIfExist(antlr4::ParserRuleContext *ctx, const T &hint) {
        if (ctx) {
            antlrcpp::Any ret = visit(ctx);
            if (ret.is<NodeWarp>()) {
                NodeWarp node_warp = ret.as<NodeWarp>();
                if (T _vp = node_warp.node_->as<typename std::remove_pointer_t<T>>()) {
                    return _vp;
                }
            }
            assert(!must_valid);
        }
        assert(!must_valid);
        return hint;
    }

    template<typename T, bool must_valid, typename>
    T CST2ASTConvert::GetFromCtxIfExist(antlr4::ParserRuleContext *ctx, const T &hint) {
        if (ctx) {
            antlrcpp::Any ret = visit(ctx);
            if (ret.is<T>()) {
                return ret.as<T>();
            }
            assert(!must_valid);
        }
        assert(!must_valid);
        return hint;
    }

    template<typename NodeTy, typename ... Args, typename>
    NodeTy *CST2ASTConvert::CreateNode(antlr4::Token *start_token, antlr4::Token *end_token, Args ... args) {
        NodeTy *node = opene::CreateNode<NodeTy>(this->ast_context_, args...);
        Node *base_node = node;
        antlr4::TokenSource *sts = start_token->getTokenSource();
        base_node->location_start_ = this->ast_context_->CreateLocation(sts->getSourceName(), sts->getLine(), sts->getCharPositionInLine());
        antlr4::TokenSource *ets = end_token->getTokenSource();
        base_node->location_end_ = this->ast_context_->CreateLocation(ets->getSourceName(), ets->getLine(), ets->getCharPositionInLine());
        return node;
    }

    antlrcpp::Any CST2ASTConvert::visitOpene_src(openeLangParser::Opene_srcContext *context) {
        TranslateUnitPtr translate_unit = CreateNode<TranslateUnit>(context->getStart(), context->getStop());
        // 分析版本号
        translate_unit->edition_ = GetFromCtxIfExist<unsigned int, true>(context->edition_spec(), 2);
        // 分析文件具体内容
        auto *src_ctx = context->src_content();
        translate_unit->source_file_ = { GetFromCtxIfExist<SourceFilePtr, true>(src_ctx) };
        return NodeWarp(translate_unit);
    }

    antlrcpp::Any CST2ASTConvert::visitSrc_content(openeLangParser::Src_contentContext *context) {
        if (openeLangParser::Program_set_fileContext *program_set_file_ctx = context->program_set_file()) {
            return NodeWarp(GetFromCtxIfExist<ProgramSetFilePtr, true>(program_set_file_ctx));
        } else if (openeLangParser::Data_structure_fileContext *data_structure_file_ctx = context->data_structure_file()) {
            return NodeWarp(GetFromCtxIfExist<DataStructureFilePtr, true>(data_structure_file_ctx));
        } else if (openeLangParser::Global_variable_fileContext *global_variable_file_ctx = context->global_variable_file()) {
            return NodeWarp(GetFromCtxIfExist<GlobalVariableFilePtr, true>(global_variable_file_ctx));
        } else if (openeLangParser::Dll_define_fileContext *dll_define_file_ctx = context->dll_define_file()) {
            return NodeWarp(GetFromCtxIfExist<DllDefineFilePtr, true>(dll_define_file_ctx));
        } else {
            return NodeWarp(nullptr);
        }
    }

    antlrcpp::Any CST2ASTConvert::visitProgram_set_file(openeLangParser::Program_set_fileContext *context) {
        auto program_set_file = CreateNode<ProgramSetFile>(context->getStart(), context->getStop());
        for (antlr4::Token *token : context->libraries) {
            program_set_file->libraries_.push_back(GetTextIfExist(token));
        }
        program_set_file->program_set_declares_ = GetFromCtxIfExist<ProgSetDeclPtr>(context->prog_set());
        program_set_file->file_type_ = SourceFile::FileType::kProgramSetFile;
        return NodeWarp(program_set_file);
    }

    antlrcpp::Any CST2ASTConvert::visitData_structure_file(openeLangParser::Data_structure_fileContext *context) {
        DataStructureFilePtr data_structure_file = CreateNode<DataStructureFile>(context->getStart(), context->getStop());
        for (auto *struct_decl_ctx : context->struct_declare()) {
            StructureDeclPtr structure_decl = GetFromCtxIfExist<StructureDeclPtr>(struct_decl_ctx);
            data_structure_file->structure_decl_map_[structure_decl->name_.string_] = structure_decl;
        }
        data_structure_file->file_type_ = SourceFile::FileType::kDataStructureFile;
        return NodeWarp(data_structure_file);
    }

    antlrcpp::Any CST2ASTConvert::visitGlobal_variable_file(openeLangParser::Global_variable_fileContext *context) {
        GlobalVariableFilePtr global_variable_file = CreateNode<GlobalVariableFile>(context->getStart(), context->getStop());
        global_variable_file->global_variable_map_ = GetFromCtxIfExist<decltype(GlobalVariableFile::global_variable_map_)>(context->global_variable_list());
        global_variable_file->file_type_ = SourceFile::FileType::kGlobalVariableFile;
        return NodeWarp(global_variable_file);
    }

    antlrcpp::Any CST2ASTConvert::visitDll_define_file(openeLangParser::Dll_define_fileContext *context) {
        DllDefineFilePtr dll_define_file = CreateNode<DllDefineFile>(context->getStart(), context->getStop());
        for (auto *dll_cmd_decl_ctx : context->dll_command()) {
            APICommandDeclPtr dll_command_decl = GetFromCtxIfExist<APICommandDeclPtr>(dll_cmd_decl_ctx);
            dll_define_file->dll_declares_[dll_command_decl->name_.string_] = dll_command_decl;
        }
        for (auto *dll_cmd_decl_ctx : context->lib_command()) {
            APICommandDeclPtr dll_command_decl = GetFromCtxIfExist<APICommandDeclPtr>(dll_cmd_decl_ctx);
            dll_define_file->dll_declares_[dll_command_decl->name_.string_] = dll_command_decl;
        }
        dll_define_file->file_type_ = SourceFile::FileType::kDllDefineFile;
        return NodeWarp(dll_define_file);
    }

    antlrcpp::Any CST2ASTConvert::visitDll_command(openeLangParser::Dll_commandContext *context) {
        APICommandDeclPtr dll_command_decl = CreateNode<APICommandDecl>(context->getStart(), context->getStop());
        dll_command_decl->name_ = GetTextIfExist(context->name);
        dll_command_decl->return_type_name_ = GetTextIfExist(context->type);
        dll_command_decl->library_file_ = GetTextIfExist(context->file);
        RemoveRoundQuotes(dll_command_decl->library_file_);
        dll_command_decl->library_type_ = LibraryType::kLTDynamic;
        dll_command_decl->api_name_ = GetTextIfExist(context->cmd);
        RemoveRoundQuotes(dll_command_decl->api_name_);
        dll_command_decl->comment_ = GetFromCtxIfExist<TString>(context->table_comment());
        for (openeLangParser::Parameter_declContext *param : context->parameter_decl()) {
            ParameterDeclPtr parameter_decl = GetFromCtxIfExist<ParameterDeclPtr>(param);
            dll_command_decl->parameters_.push_back(parameter_decl);
            dll_command_decl->mapping_names_.push_back(parameter_decl->name_.string_);
        }
        return NodeWarp(dll_command_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitLib_command(openeLangParser::Lib_commandContext *context) {
        APICommandDeclPtr dll_command_decl = CreateNode<APICommandDecl>(context->getStart(), context->getStop());
        dll_command_decl->name_ = GetTextIfExist(context->name);
        dll_command_decl->return_type_name_ = GetTextIfExist(context->type);
        dll_command_decl->library_file_ = GetTextIfExist(context->file);
        RemoveRoundQuotes(dll_command_decl->library_file_);
        dll_command_decl->library_type_ = LibraryType::kLTStatic;
        dll_command_decl->api_name_ = GetTextIfExist(context->cmd);
        RemoveRoundQuotes(dll_command_decl->api_name_);
        dll_command_decl->comment_ = GetFromCtxIfExist<TString>(context->table_comment());
        for (openeLangParser::Parameter_declContext *param : context->parameter_decl()) {
            ParameterDeclPtr parameter_decl = GetFromCtxIfExist<ParameterDeclPtr>(param);
            dll_command_decl->parameters_.push_back(parameter_decl);
            dll_command_decl->mapping_names_.push_back(parameter_decl->name_.string_);
        }
        return NodeWarp(dll_command_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitGlobal_variable_list(openeLangParser::Global_variable_listContext *context) {
        decltype(GlobalVariableFile::global_variable_map_) global_variable_decl_map;
        for (auto *global_vari_decl_ctx : context->global_variable_item()) {
            GlobalVariableDeclPtr global_variable_decl = GetFromCtxIfExist<GlobalVariableDeclPtr>(global_vari_decl_ctx);
            global_variable_decl_map[global_variable_decl->name_.string_] = global_variable_decl;
        }
        return global_variable_decl_map;
    }

    antlrcpp::Any CST2ASTConvert::visitGlobal_variable_item(openeLangParser::Global_variable_itemContext *context) {
        GlobalVariableDeclPtr global_variable_decl = CreateNode<GlobalVariableDecl>(context->getStart(), context->getStop());
        global_variable_decl->name_ = GetTextIfExist(context->name);
        global_variable_decl->type_name_ = GetTextIfExist(context->type);
        global_variable_decl->dimension_ = GetTextIfExist(context->dimension);
        global_variable_decl->access_ = GetTextIfExist(context->access);
        global_variable_decl->comment_ = GetFromCtxIfExist<TString>(context->table_comment());
        return NodeWarp(global_variable_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitEdition_spec(openeLangParser::Edition_specContext *context) {
        return (unsigned int) strtoul(context->INTEGER_LITERAL()->getText().c_str(), nullptr, 10);;
    }

    antlrcpp::Any CST2ASTConvert::visitStruct_declare(openeLangParser::Struct_declareContext *context) {
        StructureDeclPtr structure_decl = CreateNode<StructureDecl>(context->getStart(), context->getStop());
        structure_decl->name_ = GetTextIfExist(context->name);
        structure_decl->access_ = GetTextIfExist(context->access);
        structure_decl->comment_ = GetFromCtxIfExist<TString>(context->table_comment());
        for (auto *mem_ctx : context->struct_mems) {
            MemberVariableDeclPtr member = GetFromCtxIfExist<MemberVariableDeclPtr>(mem_ctx);
            structure_decl->members_[member->name_.string_] = member;
        }
        return NodeWarp(structure_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitTable_comment(openeLangParser::Table_commentContext *context) {
        return GetTextIfExist(context->comment);
    }

    antlrcpp::Any CST2ASTConvert::visitProg_set(openeLangParser::Prog_setContext *context) {
        ProgSetDeclPtr prog_set_decl = CreateNode<ProgSetDecl>(context->getStart(), context->getStop());
        prog_set_decl->name_ = GetTextIfExist(context->name);
        prog_set_decl->base_ = GetTextIfExist(context->base);
        prog_set_decl->access_ = GetTextIfExist(context->access);
        prog_set_decl->comment_ = GetFromCtxIfExist<TString>(context->table_comment());
        for (auto *vari_ctx : context->prog_set_varis) {
            FileVariableDeclPtr vari_decl = GetFromCtxIfExist<FileVariableDeclPtr>(vari_ctx);
            prog_set_decl->file_static_variables_[vari_decl->name_.string_] = vari_decl;
        }
        for (auto *func_ctx : context->functions) {
            FunctionDeclPtr sub_prog_decl = GetFromCtxIfExist<FunctionDeclPtr>(func_ctx);
            prog_set_decl->function_decls_[sub_prog_decl->name_.string_] = sub_prog_decl;
        }
        return NodeWarp(prog_set_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitVariable_decl(openeLangParser::Variable_declContext *context) {
        VariableDeclPtr variable_decl = CreateNode<VariableDecl>(context->getStart(), context->getStop());
        variable_decl->name_ = GetTextIfExist(context->name);
        variable_decl->type_name_ = GetTextIfExist(context->type);
        variable_decl->attributes_ = GetTextVecIfExist(context->attributes);
        variable_decl->dimension_ = GetTextIfExist(context->dimension);
        variable_decl->comment_ = GetFromCtxIfExist<TString>(context->table_comment());
        return NodeWarp(variable_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitSub_program(openeLangParser::Sub_programContext *context) {
        FunctionDeclPtr sub_prog_decl = CreateNode<FunctionDecl>(context->getStart(), context->getStop());
        sub_prog_decl->name_ = GetTextIfExist(context->name);
        sub_prog_decl->return_type_name_ = GetTextIfExist(context->type);
        sub_prog_decl->access_ = GetTextIfExist(context->access);
        sub_prog_decl->comment_ = GetFromCtxIfExist<TString>(context->table_comment());
        for (auto *param_vari_ctx : context->params) {
            ParameterDeclPtr parameter_decl = GetFromCtxIfExist<ParameterDeclPtr>(param_vari_ctx);
            sub_prog_decl->parameters_.emplace_back(parameter_decl);
        }
        for (auto *local_vari_ctx : context->local_vari) {
            LocalVariableDeclPtr local_vari = GetFromCtxIfExist<LocalVariableDeclPtr>(local_vari_ctx);
            sub_prog_decl->local_vari_[local_vari->name_.string_] = local_vari;
        }
        sub_prog_decl->statement_list_ = GetFromCtxIfExist<StatementBlockPtr>(context->statement_list());
        return NodeWarp(sub_prog_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitLocal_variable_decl(openeLangParser::Local_variable_declContext *context) {
        LocalVariableDeclPtr local_variable_decl = CreateNode<LocalVariableDecl>(context->getStart(), context->getStop());
        local_variable_decl->name_ = GetTextIfExist(context->name);
        local_variable_decl->type_name_ = GetTextIfExist(context->type);
        local_variable_decl->dimension_ = GetTextIfExist(context->dimension);
        local_variable_decl->comment_ = GetFromCtxIfExist<TString>(context->table_comment());
        return NodeWarp(local_variable_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitParameter_decl(openeLangParser::Parameter_declContext *context) {
        ParameterDeclPtr parameter_decl = CreateNode<ParameterDecl>(context->getStart(), context->getStop());
        parameter_decl->name_ = GetTextIfExist(context->name);
        parameter_decl->type_name_ = GetTextIfExist(context->type);
        parameter_decl->attributes_ = GetTextVecIfExist(context->attributes);
        parameter_decl->comment_ = GetFromCtxIfExist<TString>(context->table_comment());
        return NodeWarp(parameter_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitMember_vari_decl(openeLangParser::Member_vari_declContext *context) {
        VariableDeclPtr variable_decl = GetFromCtxIfExist<VariableDeclPtr>(context->variable_decl());
        MemberVariableDeclPtr member_variable_decl = nullptr;
        if (variable_decl) {
            member_variable_decl = CreateNode<MemberVariableDecl>(context->getStart(), context->getStop());
            member_variable_decl->dimension_ = variable_decl->dimension_;
            member_variable_decl->type_name_ = variable_decl->type_name_;
            member_variable_decl->type_decl_ptr_ = variable_decl->type_decl_ptr_;
            member_variable_decl->name_ = variable_decl->name_;
            member_variable_decl->comment_ = variable_decl->comment_;
            delete variable_decl;
        }
        return NodeWarp(member_variable_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitFile_vari_decl(openeLangParser::File_vari_declContext *context) {
        VariableDeclPtr variable_decl = GetFromCtxIfExist<VariableDeclPtr>(context->variable_decl());
        FileVariableDeclPtr file_variable_decl = nullptr;
        if (variable_decl) {
            file_variable_decl = CreateNode<FileVariableDecl>(context->getStart(), context->getStop());
            file_variable_decl->dimension_ = variable_decl->dimension_;
            file_variable_decl->type_name_ = variable_decl->type_name_;
            file_variable_decl->type_decl_ptr_ = variable_decl->type_decl_ptr_;
            file_variable_decl->name_ = variable_decl->name_;
            file_variable_decl->comment_ = variable_decl->comment_;
            delete variable_decl;
        }
        return NodeWarp(file_variable_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitStatement_list(openeLangParser::Statement_listContext *context) {
        StatementBlockPtr statement_list = CreateNode<StatementBlock>(context->getStart(), context->getStop());
        for (auto *stmt_ctx : context->stmts) {
            statement_list->statements_.push_back(GetFromCtxIfExist<StatementPtr>(stmt_ctx));
        }
        return NodeWarp(statement_list);
    }

    antlrcpp::Any CST2ASTConvert::visitConditionStatement(openeLangParser::ConditionStatementContext *context) {
        return NodeWarp(GetFromCtxIfExist<StatementPtr>(context->condition_statement()));
    }

    antlrcpp::Any CST2ASTConvert::visitAssignStatement(openeLangParser::AssignStatementContext *context) {
        AssignStmtPtr assign_stmt = CreateNode<AssignStmt>(context->getStart(), context->getStop());
        assign_stmt->lhs_ = GetFromCtxIfExist<HierarchyIdentifierPtr>(context->hierarchy_identifier());
        assign_stmt->rhs_ = GetFromCtxIfExist<ExpressionPtr>(context->expression());
        return NodeWarp(assign_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitExpressionStatement(openeLangParser::ExpressionStatementContext *context) {
        return NodeWarp(GetFromCtxIfExist<StatementPtr>(context->expression()));
    }

    antlrcpp::Any CST2ASTConvert::visitLoopStatement(openeLangParser::LoopStatementContext *context) {
        return NodeWarp(GetFromCtxIfExist<StatementPtr>(context->loop_statement()));
    }

    antlrcpp::Any CST2ASTConvert::visitSwitchStatement(openeLangParser::SwitchStatementContext *context) {
        return NodeWarp(GetFromCtxIfExist<StatementPtr>(context->switch_statement()));
    }

    antlrcpp::Any CST2ASTConvert::visitSwitch_statement(openeLangParser::Switch_statementContext *context) {
        IfStmtPtr switch_stmt = CreateNode<IfStmt>(context->getStart(), context->getStop());
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
        return NodeWarp(switch_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitWhile(openeLangParser::WhileContext *context) {
        WhileStmtPtr while_stmt = CreateNode<WhileStmt>(context->getStart(), context->getStop());
        while_stmt->condition_ = GetFromCtxIfExist<ExpressionPtr>(context->condition_expr);
        while_stmt->loop_body_ = GetFromCtxIfExist<StatementPtr>(context->loop_body);
        return NodeWarp(while_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitRangeFor(openeLangParser::RangeForContext *context) {
        RangeForStmtPtr range_for_stmt = CreateNode<RangeForStmt>(context->getStart(), context->getStop());
        range_for_stmt->range_size_ = GetFromCtxIfExist<ExpressionPtr>(context->times_expr);
        range_for_stmt->loop_vari_ = GetFromCtxIfExist<HierarchyIdentifierPtr>(context->loop_variable);
        range_for_stmt->loop_body_ = GetFromCtxIfExist<StatementPtr>(context->loop_body);
        return NodeWarp(range_for_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitFor(openeLangParser::ForContext *context) {
        ForStmtPtr for_stmt = CreateNode<ForStmt>(context->getStart(), context->getStop());
        for_stmt->start_value_ = GetFromCtxIfExist<ExpressionPtr>(context->loop_start);
        for_stmt->stop_value_ = GetFromCtxIfExist<ExpressionPtr>(context->loop_end);
        for_stmt->step_value_ = GetFromCtxIfExist<ExpressionPtr>(context->loop_step);
        for_stmt->loop_vari_ = GetFromCtxIfExist<HierarchyIdentifierPtr>(context->loop_variable);
        for_stmt->loop_body_ = GetFromCtxIfExist<StatementPtr>(context->loop_body);
        return NodeWarp(for_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitDoWhile(openeLangParser::DoWhileContext *context) {
        DoWhileStmtPtr do_while_stmt = CreateNode<DoWhileStmt>(context->getStart(), context->getStop());
        do_while_stmt->loop_body_ = GetFromCtxIfExist<StatementPtr>(context->loop_body);
        do_while_stmt->conditon_ = GetFromCtxIfExist<ExpressionPtr>(context->condition_expr);
        return NodeWarp(do_while_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitIfStmt(openeLangParser::IfStmtContext *context) {
        IfStmtPtr if_stmt = CreateNode<IfStmt>(context->getStart(), context->getStop());
        ExpressionPtr condition = GetFromCtxIfExist<ExpressionPtr>(context->condition_expr);
        StatementPtr true_statement = GetFromCtxIfExist<StatementPtr>(context->true_stmt_list);
        if_stmt->switches_.push_back(std::pair(condition, true_statement));
        if_stmt->default_statement_ = GetFromCtxIfExist<StatementPtr>(context->false_stmt_list);
        return NodeWarp(if_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitIfTrueStmt(openeLangParser::IfTrueStmtContext *context) {
        IfStmtPtr if_stmt = CreateNode<IfStmt>(context->getStart(), context->getStop());
        ExpressionPtr condition = GetFromCtxIfExist<ExpressionPtr>(context->condition_expr);
        StatementPtr true_statement = GetFromCtxIfExist<StatementPtr>(context->true_stmt_list);
        if_stmt->switches_.push_back(std::pair(condition, true_statement));
        return NodeWarp(if_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitControlStatement(openeLangParser::ControlStatementContext *context) {
        return NodeWarp(GetFromCtxIfExist<ControlStmtPtr>(context->control_statement()));
    }

    antlrcpp::Any CST2ASTConvert::visitContinueStmt(openeLangParser::ContinueStmtContext *context) {
        ContinueStmtPtr continue_stmt = CreateNode<ContinueStmt>(context->getStart(), context->getStop());
        return NodeWarp(continue_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitBreakStmt(openeLangParser::BreakStmtContext *context) {
        BreakStmtPtr break_stmt = CreateNode<BreakStmt>(context->getStart(), context->getStop());
        return NodeWarp(break_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitReturnStmt(openeLangParser::ReturnStmtContext *context) {
        ReturnStmtPtr return_stmt = CreateNode<ReturnStmt>(context->getStart(), context->getStop());
        return_stmt->return_value_ = GetFromCtxIfExist<ExpressionPtr>(context->return_expr);
        return NodeWarp(return_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitExitStmt(openeLangParser::ExitStmtContext *context) {
        ExitStmtPtr exit_stmt = CreateNode<ExitStmt>(context->getStart(), context->getStop());
        return NodeWarp(exit_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitHierarchy_identifier(openeLangParser::Hierarchy_identifierContext *context) {
        HierarchyIdentifierPtr hierarchy_identifier = CreateNode<HierarchyIdentifier>(context->getStart(), context->getStop());
        for (auto *name_component_ctx : context->components) {
            NameComponentPtr name_component = GetFromCtxIfExist<NameComponentPtr, true>(name_component_ctx);
            hierarchy_identifier->name_components_.push_back(name_component);
        }
        return NodeWarp(hierarchy_identifier);
    }

    antlrcpp::Any CST2ASTConvert::visitFuncCall(openeLangParser::FuncCallContext *context) {
        FunctionCallPtr function_call = CreateNode<FunctionCall>(context->getStart(), context->getStop());
        function_call->function_name_ = GetFromCtxIfExist<NameComponentPtr, true>(context->name_component());
        for (auto *arg_ctx : context->arguments) {
            ExpressionPtr arg_expr = GetFromCtxIfExist<ExpressionPtr>(arg_ctx);
            function_call->arguments_.push_back(arg_expr);
        }
        return NodeWarp(function_call);
    }

    antlrcpp::Any CST2ASTConvert::visitIdentifier(openeLangParser::IdentifierContext *context) {
        IdentifierPtr identifier = CreateNode<Identifier>(context->getStart(), context->getStop());
        identifier->name_ = GetTextIfExist(context->IDENTIFIER()->getSymbol());
        return NodeWarp(identifier);
    }

    antlrcpp::Any CST2ASTConvert::visitArrayIndex(openeLangParser::ArrayIndexContext *context) {
        ArrayIndexPtr array_index = CreateNode<ArrayIndex>(context->getStart(), context->getStop());
        array_index->base_ = GetFromCtxIfExist<NameComponentPtr, true>(context->name_component());
        array_index->index_ = GetFromCtxIfExist<ExpressionPtr>(context->expression());
        return NodeWarp(array_index);
    }

    antlrcpp::Any CST2ASTConvert::visitBracket(openeLangParser::BracketContext *context) {
        return NodeWarp(GetFromCtxIfExist<ExpressionPtr>(context->expression()));
    }

    antlrcpp::Any CST2ASTConvert::visitOptElement(openeLangParser::OptElementContext *context) {
        return NodeWarp(GetFromCtxIfExist<ExpressionPtr>(context->getRuleContext<antlr4::ParserRuleContext>(0)));
    }

    antlrcpp::Any CST2ASTConvert::visitBinaryExpr(openeLangParser::BinaryExprContext *context) {
        BinaryExpressionPtr binary_expression = CreateNode<BinaryExpression>(context->getStart(), context->getStop());
        binary_expression->operator_ = GetTextIfExist(context->opt);
        switch (context->opt->getType()) {
            case openeLangParser::K_ADD_OPT:        binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptAdd;        break;
            case openeLangParser::K_SUB_OPT:        binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptSub;        break;
            case openeLangParser::K_MUL_OPT:        binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptMul;        break;
            case openeLangParser::K_DIV_OPT:        binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptDiv;        break;
            case openeLangParser::K_FULL_DIV_OPT:   binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptFullDiv;    break;
            case openeLangParser::K_MOD_OPT:        binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptMod;        break;
            case openeLangParser::K_AECOM_OPT:      binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptEqual;      break;
            case openeLangParser::K_ASSIGN_OPT:     binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptEqual;      break;
            case openeLangParser::K_EQUAL_OPT:      binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptEqual;      break;
            case openeLangParser::K_NOT_EQUAL_OPT:  binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptNotEqual;   break;
            case openeLangParser::K_GREAT_OPT:      binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptGreatThan;  break;
            case openeLangParser::K_LESS_OPT:       binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptLessThan;   break;
            case openeLangParser::K_GREAT_EQU_OPT:  binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptGreatEqual; break;
            case openeLangParser::K_LESS_EQU_OPT:   binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptLessEqual;  break;
            case openeLangParser::K_LIKE_EQU_OPT:   binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptLikeEqual;  break;
            case openeLangParser::K_AND_OPT:        binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptAnd;        break;
            case openeLangParser::K_OR_OPT:         binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptOr;         break;
            default: assert(false);                 binary_expression->operator_type_ = BinaryExpression::OperatorType::kOptNone;       break;
        }
        binary_expression->lhs_ = GetFromCtxIfExist<ExpressionPtr>(context->lval);
        binary_expression->rhs_ = GetFromCtxIfExist<ExpressionPtr>(context->rval);
        return NodeWarp(binary_expression);
    }

    antlrcpp::Any CST2ASTConvert::visitUnaryExpr(openeLangParser::UnaryExprContext *context) {
        UnaryExpressionPtr unary_expression = CreateNode<UnaryExpression>(context->getStart(), context->getStop());
        unary_expression->operator_ = GetTextIfExist(context->opt);
        switch (context->opt->getType()) {
            case openeLangParser::K_SUB_OPT:    unary_expression->operator_type_ = UnaryExpression::OperatorType::kOptSub;  break;
            default: assert(false);             unary_expression->operator_type_ = UnaryExpression::OperatorType::kOptNone; break;
        }
        unary_expression->operand_value_ = GetFromCtxIfExist<ExpressionPtr>(context->expression());
        return NodeWarp(unary_expression);
    }

    antlrcpp::Any CST2ASTConvert::visitData_set_value(openeLangParser::Data_set_valueContext *context) {
        ValueOfDataSetPtr value_of_data_set = CreateNode<ValueOfDataSet>(context->getStart(), context->getStop());
        for (auto *elem_ctx : context->elems) {
            value_of_data_set->elements_.push_back(GetFromCtxIfExist<ExpressionPtr>(elem_ctx));
        }
        return NodeWarp(value_of_data_set);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetime_value(openeLangParser::Datetime_valueContext *context) {
        return NodeWarp(GetFromCtxIfExist<ValueOfDatetimePtr>(context->datetime_value_core()));
    }

    ValueOfDatetimePtr CST2ASTConvert::TimeNodeBuilder(time_t time, antlr4::Token *start_token, antlr4::Token *end_token) {
        ValueOfDatetimePtr value_of_datetime = CreateNode<ValueOfDatetime>(start_token, end_token);
        value_of_datetime->time_ = time;
        return value_of_datetime;
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimePureNumber(openeLangParser::DatetimePureNumberContext *context) {
        TString time_str = GetTextIfExist(context->time);
        return TimeNodeBuilder(strtoul(time_str.string_.c_str(), nullptr, 10), context->getStart(), context->getStop());
    }

    tm CST2ASTConvert::TimeBuilder(unsigned year, unsigned month, unsigned day, unsigned hour, unsigned minute, unsigned second) {
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

    ValueOfDatetimePtr CST2ASTConvert::TimeNodeBuilder(tm &&stm, antlr4::Token *start_token, antlr4::Token *end_token) {
        return TimeNodeBuilder(mktime(&stm), start_token, end_token);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimeSeparateByChinese(openeLangParser::DatetimeSeparateByChineseContext *context) {
        ValueOfDatetimePtr new_time = TimeNodeBuilder(TimeBuilder(
                GetLongIfExist(context->year),
                GetLongIfExist(context->month),
                GetLongIfExist(context->day),
                GetLongIfExist(context->hour),
                GetLongIfExist(context->minute),
                GetLongIfExist(context->second)
        ), context->getStart(), context->getStop());
        return NodeWarp(new_time);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimeSeparateBySlash(openeLangParser::DatetimeSeparateBySlashContext *context) {
        ValueOfDatetimePtr new_time = TimeNodeBuilder(TimeBuilder(
                GetLongIfExist(context->year),
                GetLongIfExist(context->month),
                GetLongIfExist(context->day),
                GetLongIfExist(context->hour),
                GetLongIfExist(context->minute),
                GetLongIfExist(context->second)
        ), context->getStart(), context->getStop());
        return NodeWarp(new_time);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimeSeparateBySlashColon(openeLangParser::DatetimeSeparateBySlashColonContext *context) {
        ValueOfDatetimePtr new_time = TimeNodeBuilder(TimeBuilder(
                GetLongIfExist(context->year),
                GetLongIfExist(context->month),
                GetLongIfExist(context->day),
                GetLongIfExist(context->hour),
                GetLongIfExist(context->minute),
                GetLongIfExist(context->second)
        ), context->getStart(), context->getStop());
        return NodeWarp(new_time);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimeSeparateByBar(openeLangParser::DatetimeSeparateByBarContext *context) {
        ValueOfDatetimePtr new_time = TimeNodeBuilder(TimeBuilder(
                GetLongIfExist(context->year),
                GetLongIfExist(context->month),
                GetLongIfExist(context->day),
                GetLongIfExist(context->hour),
                GetLongIfExist(context->minute),
                GetLongIfExist(context->second)
        ), context->getStart(), context->getStop());
        return NodeWarp(new_time);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimeSeparateByBarColon(openeLangParser::DatetimeSeparateByBarColonContext *context) {
        ValueOfDatetimePtr new_time = TimeNodeBuilder(TimeBuilder(
                GetLongIfExist(context->year),
                GetLongIfExist(context->month),
                GetLongIfExist(context->day),
                GetLongIfExist(context->hour),
                GetLongIfExist(context->minute),
                GetLongIfExist(context->second)
        ), context->getStart(), context->getStop());
        return NodeWarp(new_time);
    }

    antlrcpp::Any CST2ASTConvert::visitMacro_value(openeLangParser::Macro_valueContext *context) {
        ResourceRefExpressionPtr resource_ref_expression = CreateNode<ResourceRefExpression>(context->getStart(), context->getStop());
        resource_ref_expression->resource_name_ = GetTextIfExist(context->IDENTIFIER()->getSymbol());
        return NodeWarp(resource_ref_expression);
    }

    antlrcpp::Any CST2ASTConvert::visitFunc_ptr(openeLangParser::Func_ptrContext *context) {
        FuncAddrExpressionPtr func_addr_expression = CreateNode<FuncAddrExpression>(context->getStart(), context->getStop());
        func_addr_expression->function_name_ = GetTextIfExist(context->IDENTIFIER()->getSymbol());
        return NodeWarp(func_addr_expression);
    }

    antlrcpp::Any CST2ASTConvert::visitBoolValueTrue(openeLangParser::BoolValueTrueContext *context) {
        ValueOfBoolPtr value_of_bool = CreateNode<ValueOfBool>(context->getStart(), context->getStop());
        value_of_bool->value_ = true;
        return NodeWarp(value_of_bool);
    }

    antlrcpp::Any CST2ASTConvert::visitBoolValueFalse(openeLangParser::BoolValueFalseContext *context) {
        ValueOfBoolPtr value_of_bool = CreateNode<ValueOfBool>(context->getStart(), context->getStop());
        value_of_bool->value_ = false;
        return NodeWarp(value_of_bool);
    }

    antlrcpp::Any CST2ASTConvert::visitInt(openeLangParser::IntContext *context) {
        ValueOfDecimalPtr value_of_decimal = CreateNode<ValueOfDecimal>(context->getStart(), context->getStop());
        value_of_decimal->int_val_ = GetLongIfExist(context->INTEGER_LITERAL()->getSymbol());
        value_of_decimal->type_ = ValueOfDecimal::type::kInt;
        return NodeWarp(value_of_decimal);
    }

    antlrcpp::Any CST2ASTConvert::visitFloat(openeLangParser::FloatContext *context) {
        ValueOfDecimalPtr value_of_decimal = CreateNode<ValueOfDecimal>(context->getStart(), context->getStop());
        value_of_decimal->float_val_ = GetFloatIfExist(context->FLOAT_LITERAL()->getSymbol());
        value_of_decimal->type_ = ValueOfDecimal::type::kFloat;
        return NodeWarp(value_of_decimal);
    }

    antlrcpp::Any CST2ASTConvert::visitString_value(openeLangParser::String_valueContext *context) {
        ValueOfStringPtr value_of_string = CreateNode<ValueOfString>(context->getStart(), context->getStop());
        value_of_string->string_literal_ = GetTextIfExist(context->STRING_LITERAL()->getSymbol());
        return NodeWarp(value_of_string);
    }

    CST2ASTConvert::CST2ASTConvert(ASTContext *ast_context, Diagnostic *diagnostic)
        : ast_context_(ast_context) {
    }

    TranslateUnitPtr CST2ASTConvert::BuildTranslateUnitFromParseTree(antlr4::tree::ParseTree *tree) {
        antlrcpp::Any build_result = this->visit(tree);
        TranslateUnitPtr translate_unit = nullptr;
        if (build_result.is<NodeWarp>()) {
            if ((translate_unit = build_result.as<NodeWarp>())) {
                return translate_unit;
            } else {
                assert(false);
                return nullptr;
            }
        } else {
            assert(false);
            return nullptr;
        }
    }
}
