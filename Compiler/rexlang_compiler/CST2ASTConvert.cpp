//
// Created by rex on 2020/1/23.
//

#include <cstring>

#include "gen/rexLangLexer.h"
#include "gen/rexLangParser.h"
#include "gen/rexLangVisitor.h"

#include "CST2ASTConvert.h"
#include "NodeDecl.h"
#include "ASTContext.h"

namespace rexlang {

    static void RemoveRoundQuotes(TString &tString) {
        if (!tString.string_.empty()&& tString.string_.str().front() == '"' && tString.string_.str().back() == '"') {
            std::string _string = tString.string_.str();
            _string = _string.substr(1, _string.length() - 2);
            tString.string_ = StringPool::Create(_string);
        }
    }

    static TString RemoveRoundQuotes(const TString &tString) {
        TString __tstring = tString;
        RemoveRoundQuotes(__tstring);
        return __tstring;
    }

    TString CST2ASTConvert::GetTextIfExist(const antlr4::Token *token, const std::string &hint) const {
        TString t_string;
        if (token) {
            t_string.string_ = this->ast_context_->createString(token->getText());
            antlr4::TokenSource *ts = token->getTokenSource();
            t_string.location_ = this->ast_context_->createLocation(ts->getSourceName(), ts->getLine(), ts->getCharPositionInLine());
        } else {
            t_string.string_ = this->ast_context_->createString(hint);
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
                if (T _vp = node_warp.get<typename std::remove_pointer_t<T>>()) {
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
    NodeTy *CST2ASTConvert::CreateNode(antlr4::Token *start_token, antlr4::Token *end_token, Args && ... args) {
        NodeTy *node = rexlang::CreateNode<NodeTy, Args...>(this->ast_context_, args...);
        Node *base_node = node;
        base_node->setLocation(
                start_token->getTokenSource()->getSourceName().c_str(),
                start_token->getLine(),
                start_token->getCharPositionInLine(),
                end_token->getLine(),
                end_token->getCharPositionInLine()
                );
        return node;
    }

    template<typename NodeTy, typename ... Args, typename = typename std::enable_if_t<std::is_base_of_v<Node, NodeTy>>>
    NodeTy *CreateNode(antlr4::ParserRuleContext *parserRuleContext, Args && ... args) {
        return CreateNode<NodeTy, Args...>(parserRuleContext->getStart(), parserRuleContext->getStop(), args...);
    }

    antlrcpp::Any CST2ASTConvert::visitRexlang_src(rexLangParser::Rexlang_srcContext *context) {
        TranslateUnit * translate_unit = ast_context_->getTranslateUnit();
        if(!translate_unit) translate_unit = CreateNode<TranslateUnit>(context);

        ast_context_->cleanScopeStack();
        ast_context_->pushScope(translate_unit);

        ast_context_->setTranslateUnit(translate_unit);
        // 分析版本号
        translate_unit->setSourceEdition(GetFromCtxIfExist<unsigned int, true>(context->edition_spec(), 2));
        // 分析文件具体内容
        auto *src_ctx = context->src_content();
        translate_unit->appendSourceFile(GetFromCtxIfExist<SourceFile*, true>(src_ctx));

        ast_context_->popScope(translate_unit);
        return NodeWarp(translate_unit);
    }

    antlrcpp::Any CST2ASTConvert::visitSrc_content(rexLangParser::Src_contentContext *context) {
               if (auto *program_set_file_ctx     = context->program_set_file())     { return NodeWarp(GetFromCtxIfExist<ProgramSetFile*,     true>(program_set_file_ctx));
        } else if (auto *data_structure_file_ctx  = context->data_structure_file())  { return NodeWarp(GetFromCtxIfExist<DataStructureFile*,  true>(data_structure_file_ctx));
        } else if (auto *global_variable_file_ctx = context->global_variable_file()) { return NodeWarp(GetFromCtxIfExist<GlobalVariableFile*, true>(global_variable_file_ctx));
        } else if (auto *dll_define_file_ctx      = context->dll_define_file())      { return NodeWarp(GetFromCtxIfExist<APIDeclareFile*,     true>(dll_define_file_ctx));
        } else { return NodeWarp(nullptr); }
    }

    antlrcpp::Any CST2ASTConvert::visitProgram_set_file(rexLangParser::Program_set_fileContext *context) {
        auto program_set_file = CreateNode<ProgramSetFile>(context);
        for (antlr4::Token *token : context->libraries) {
            TString library_name = GetTextIfExist(token);
            program_set_file->appendReferenceLibName(library_name);
        }
        program_set_file->appendProgramSetDecl(GetFromCtxIfExist<ProgSetDecl*>(context->prog_set()));
        return NodeWarp(program_set_file);
    }

    antlrcpp::Any CST2ASTConvert::visitData_structure_file(rexLangParser::Data_structure_fileContext *context) {
        DataStructureFile* data_structure_file = CreateNode<DataStructureFile>(context);
        for (auto *struct_decl_ctx : context->struct_declare()) {
            StructureDecl* structure_decl = GetFromCtxIfExist<StructureDecl*>(struct_decl_ctx);
            data_structure_file->appendStructureDecl(structure_decl);
        }
        return NodeWarp(data_structure_file);
    }

    antlrcpp::Any CST2ASTConvert::visitGlobal_variable_file(rexLangParser::Global_variable_fileContext *context) {
        GlobalVariableFile* global_variable_file = CreateNode<GlobalVariableFile>(context);
        auto vari_map = GetFromCtxIfExist<GlobalVariableFile::GlobalVariMapTy>(context->global_variable_list());
        for (auto &vari_item : vari_map) {
            global_variable_file->appendGlobalVariableDecl(vari_item.second);
        }
        return NodeWarp(global_variable_file);
    }

    antlrcpp::Any CST2ASTConvert::visitDll_define_file(rexLangParser::Dll_define_fileContext *context) {
        APIDeclareFile* dll_define_file = CreateNode<APIDeclareFile>(context);
        for (auto *dll_func_decl_ctx : context->dll_command()) {
            APICommandDecl* dll_command_decl = GetFromCtxIfExist<APICommandDecl*>(dll_func_decl_ctx);
            dll_define_file->appendAPIDeclare(dll_command_decl);
        }
        for (auto *lib_func_decl_ctx : context->lib_command()) {
            APICommandDecl* dll_command_decl = GetFromCtxIfExist<APICommandDecl*>(lib_func_decl_ctx);
            dll_define_file->appendAPIDeclare(dll_command_decl);
        }
        return NodeWarp(dll_define_file);
    }

    antlrcpp::Any CST2ASTConvert::visitDll_command(rexLangParser::Dll_commandContext *context) {
        TString     library_file  = RemoveRoundQuotes(GetTextIfExist(context->file));
        TString     name          = RemoveRoundQuotes(GetTextIfExist(context->name));
        LibraryType library_type  = LibraryType::kLTDynamic;
        TString     api_name      = RemoveRoundQuotes(GetTextIfExist(context->cmd));
        TString     ret_type_name = GetTextIfExist(context->type);

        APICommandDecl* dll_api_decl = CreateNode<APICommandDecl>(context, library_file, library_type, name, api_name);

        dll_api_decl->setReturnTypeName(ret_type_name);
        dll_api_decl->setComment(GetFromCtxIfExist<TString>(context->table_comment()));
        auto parameters = GetFromCtxIfExist<std::vector<ParameterDecl*>>(context->params);
        for (auto *parameter : parameters) {
            dll_api_decl->appendParameter(parameter);
        }
        return NodeWarp(dll_api_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitLib_command(rexLangParser::Lib_commandContext *context) {
        TString     library_file  = RemoveRoundQuotes(GetTextIfExist(context->file));
        TString     name          = RemoveRoundQuotes(GetTextIfExist(context->name));
        LibraryType library_type  = LibraryType::kLTStatic;
        TString     api_name      = RemoveRoundQuotes(GetTextIfExist(context->cmd));
        TString     ret_type_name = GetTextIfExist(context->type);

        APICommandDecl* lib_api_decl = CreateNode<APICommandDecl>(context, library_file, library_type, name, api_name);

        lib_api_decl->setReturnTypeName(ret_type_name);
        lib_api_decl->setComment(GetFromCtxIfExist<TString>(context->table_comment()));
        auto parameters = GetFromCtxIfExist<std::vector<ParameterDecl*>>(context->params);
        for (auto *parameter : parameters) {
            lib_api_decl->appendParameter(parameter);
        }
        return NodeWarp(lib_api_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitGlobal_variable_list(rexLangParser::Global_variable_listContext *context) {
        GlobalVariableFile::GlobalVariMapTy global_variable_decl_map;
        for (auto *global_vari_decl_ctx : context->global_variable_item()) {
            GlobalVariableDecl* global_variable_decl = GetFromCtxIfExist<GlobalVariableDecl*>(global_vari_decl_ctx);
            global_variable_decl_map[global_variable_decl->getNameRef()] = global_variable_decl;
        }
        return global_variable_decl_map;
    }

    antlrcpp::Any CST2ASTConvert::visitGlobal_variable_item(rexLangParser::Global_variable_itemContext *context) {
        GlobalVariableDecl* global_variable_decl = CreateNode<GlobalVariableDecl>(context);
        global_variable_decl->setName          (GetTextIfExist(context->name));
        global_variable_decl->setTypeName      (GetTextIfExist(context->type));
        global_variable_decl->setDimensionsText(GetTextIfExist(context->dimension));
        global_variable_decl->applyAttribute   (GetTextIfExist(context->access));
        global_variable_decl->setComment       (GetFromCtxIfExist<TString>(context->table_comment()));
        return NodeWarp(global_variable_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitEdition_spec(rexLangParser::Edition_specContext *context) {
        return (unsigned int) strtoul(context->INTEGER_LITERAL()->getText().c_str(), nullptr, 10);
    }

    antlrcpp::Any CST2ASTConvert::visitStruct_declare(rexLangParser::Struct_declareContext *context) {
        StructureDecl* structure_decl = CreateNode<StructureDecl>(context);
        structure_decl->setName       (GetTextIfExist(context->name));
        structure_decl->applyAttribute(GetTextIfExist(context->access));
        structure_decl->setComment    (GetFromCtxIfExist<TString>(context->table_comment()));
        for (auto *mem_ctx : context->struct_mems) {
            MemberVariableDecl* member = GetFromCtxIfExist<MemberVariableDecl*>(mem_ctx);
            structure_decl->appendElement(member);
        }
        return NodeWarp(structure_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitTable_comment(rexLangParser::Table_commentContext *context) {
        return GetTextIfExist(context->comment);
    }

    antlrcpp::Any CST2ASTConvert::visitProg_set(rexLangParser::Prog_setContext *context) {
        ProgSetDecl* prog_set_decl = CreateNode<ProgSetDecl>(context);
        ast_context_->pushScope(prog_set_decl);

        prog_set_decl->setName(GetTextIfExist(context->name));
        prog_set_decl->applyAttribute(GetTextIfExist(context->access));
        prog_set_decl->setComment(GetFromCtxIfExist<TString>(context->table_comment()));
        for (auto *vari_ctx : context->prog_set_varis) {
            FileVariableDecl* vari_decl = GetFromCtxIfExist<FileVariableDecl*>(vari_ctx);
            prog_set_decl->appendFileStaticVari(vari_decl);
        }
        for (auto *func_ctx : context->functions) {
            FunctionDecl* sub_prog_decl = GetFromCtxIfExist<FunctionDecl*>(func_ctx);
            prog_set_decl->appendFunctionDecl(sub_prog_decl);
        }

        ast_context_->popScope(prog_set_decl);
        return NodeWarp(prog_set_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitVariable_decl(rexLangParser::Variable_declContext *context) {
        VariableDecl* variable_decl = CreateNode<VariableDecl>(context);
        variable_decl->setName(GetTextIfExist(context->name));
        variable_decl->setTypeName(GetTextIfExist(context->type));
        variable_decl->applyAttributes(GetTextVecIfExist(context->attributes));
        variable_decl->setDimensionsText(GetTextIfExist(context->dimension));
        variable_decl->setComment(GetFromCtxIfExist<TString>(context->table_comment()));
        return NodeWarp(variable_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitSub_program(rexLangParser::Sub_programContext *context) {
        FunctionDecl* sub_prog_decl = CreateNode<FunctionDecl>(context);
        ast_context_->pushScope(sub_prog_decl);

        sub_prog_decl->setName(GetTextIfExist(context->name));
        sub_prog_decl->setReturnTypeName(GetTextIfExist(context->type));
        sub_prog_decl->applyAttribute(GetTextIfExist(context->access));
        sub_prog_decl->setComment(GetFromCtxIfExist<TString>(context->table_comment()));
        for (ParameterDecl *parameter_decl : GetFromCtxIfExist<std::vector<ParameterDecl *>>(context->params)) {
            sub_prog_decl->appendParameter(parameter_decl);
        }
        for (auto *local_vari_ctx : context->local_vari) {
            LocalVariableDecl* local_vari = GetFromCtxIfExist<LocalVariableDecl*>(local_vari_ctx);
            sub_prog_decl->appendLocalVariable(local_vari);
        }
        sub_prog_decl->setStatementBlock(GetFromCtxIfExist<StatementBlock*>(context->statement_list()));

        ast_context_->popScope(sub_prog_decl);
        return NodeWarp(sub_prog_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitLocal_variable_decl(rexLangParser::Local_variable_declContext *context) {
        LocalVariableDecl* local_variable_decl = CreateNode<LocalVariableDecl>(context);
        local_variable_decl->setName(GetTextIfExist(context->name));
        local_variable_decl->setTypeName(GetTextIfExist(context->type));
        local_variable_decl->setDimensionsText(GetTextIfExist(context->dimension));
        local_variable_decl->setComment(GetFromCtxIfExist<TString>(context->table_comment()));
        return NodeWarp(local_variable_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitParameter_decl_list(rexLangParser::Parameter_decl_listContext *context) {
        std::vector<ParameterDecl*> params;
        for (auto *param_vari_ctx : context->parameter_decl()) {
            ParameterDecl* parameter_decl = GetFromCtxIfExist<ParameterDecl*>(param_vari_ctx);
            params.emplace_back(parameter_decl);
        }
        if (auto *vari_param_ctx = context->vari_parameter_decl()) {
            ParameterDecl* vari_parameter_decl = GetFromCtxIfExist<ParameterDecl*>(vari_param_ctx);
            params.emplace_back(vari_parameter_decl);
        }
        return params;
    }

    antlrcpp::Any CST2ASTConvert::visitParameter_decl(rexLangParser::Parameter_declContext *context) {
        ParameterDecl* parameter_decl = CreateNode<ParameterDecl>(context);
        parameter_decl->setName(GetTextIfExist(context->name));
        parameter_decl->setTypeName(GetTextIfExist(context->type));
        parameter_decl->applyAttributes(GetTextVecIfExist(context->attributes));
        parameter_decl->setComment(GetFromCtxIfExist<TString>(context->table_comment()));
        return NodeWarp(parameter_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitVari_parameter_decl(rexLangParser::Vari_parameter_declContext *context) {
        ParameterDecl* parameter_decl = CreateNode<ParameterDecl>(context);
        parameter_decl->setName(GetTextIfExist(context->name));
        parameter_decl->setTypeName( GetTextIfExist(context->type));
        parameter_decl->applyAttributes(GetTextVecIfExist(context->attributes));
        parameter_decl->setComment(GetFromCtxIfExist<TString>(context->table_comment()));
        return NodeWarp(parameter_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitMember_vari_decl(rexLangParser::Member_vari_declContext *context) {
        VariableDecl* variable_decl = GetFromCtxIfExist<VariableDecl*>(context->variable_decl());
        MemberVariableDecl* member_variable_decl = nullptr;
        if (variable_decl) {
            member_variable_decl = CreateNode<MemberVariableDecl>(context);
            member_variable_decl->setDimensionsText(variable_decl->getDimensionsText());
            member_variable_decl->setTypeName      (variable_decl->getTypeName());
            member_variable_decl->setTypeDecl      (variable_decl->takeTypeDecl());
            member_variable_decl->setName          (variable_decl->getName());
            member_variable_decl->setComment       (variable_decl->getComment());
            delete variable_decl;
        }
        return NodeWarp(member_variable_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitFile_vari_decl(rexLangParser::File_vari_declContext *context) {
        VariableDecl* variable_decl = GetFromCtxIfExist<VariableDecl*>(context->variable_decl());
        FileVariableDecl* file_variable_decl = nullptr;
        if (variable_decl) {
            file_variable_decl = CreateNode<FileVariableDecl>(context);
            file_variable_decl->setDimensionsText(variable_decl->getDimensionsText());
            file_variable_decl->setTypeName      (variable_decl->getTypeName());
            file_variable_decl->setTypeDecl      (variable_decl->takeTypeDecl());
            file_variable_decl->setName          (variable_decl->getName());
            file_variable_decl->setComment       (variable_decl->getComment());
            delete variable_decl;
        }
        return NodeWarp(file_variable_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitStatement_list(rexLangParser::Statement_listContext *context) {
        StatementBlock* statement_list = CreateNode<StatementBlock>(context);
        for (auto *stmt_ctx : context->stmts) {
            statement_list->appendStatement(GetFromCtxIfExist<Statement*>(stmt_ctx));
        }
        return NodeWarp(statement_list);
    }

    antlrcpp::Any CST2ASTConvert::visitConditionStatement(rexLangParser::ConditionStatementContext *context) {
        return NodeWarp(GetFromCtxIfExist<Statement*>(context->condition_statement()));
    }

    antlrcpp::Any CST2ASTConvert::visitAssignStatement(rexLangParser::AssignStatementContext *context) {
        AssignStmt* assign_stmt = CreateNode<AssignStmt>(context);
        assign_stmt->setLHS(GetFromCtxIfExist<HierarchyIdentifier*>(context->hierarchy_identifier()));
        assign_stmt->setRHS(GetFromCtxIfExist<Expression*>(context->expression()));
        return NodeWarp(assign_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitExpressionStatement(rexLangParser::ExpressionStatementContext *context) {
        return NodeWarp(GetFromCtxIfExist<Statement*>(context->expression()));
    }

    antlrcpp::Any CST2ASTConvert::visitLoopStatement(rexLangParser::LoopStatementContext *context) {
        return NodeWarp(GetFromCtxIfExist<Statement*>(context->loop_statement()));
    }

    antlrcpp::Any CST2ASTConvert::visitSwitchStatement(rexLangParser::SwitchStatementContext *context) {
        return NodeWarp(GetFromCtxIfExist<Statement*>(context->switch_statement()));
    }

    antlrcpp::Any CST2ASTConvert::visitSwitch_statement(rexLangParser::Switch_statementContext *context) {
        IfStmt* switch_stmt = CreateNode<IfStmt>(context);

        Expression* major_cond_expr = GetFromCtxIfExist<Expression*>(context->major_condition_expr);
        Statement*  major_cond_body = GetFromCtxIfExist<Statement*>(context->major_cond_body);
        switch_stmt->appendBranch(major_cond_expr, major_cond_body);

        assert(context->minor_condition_expr.size() == context->minor_cond_body.size());
        for (size_t idx = 0; idx < context->minor_condition_expr.size(); idx++) {
            Expression* minor_cond_expr = GetFromCtxIfExist<Expression*>(context->minor_condition_expr[idx]);
            Statement*  minor_cond_body = GetFromCtxIfExist<Statement*>(context->minor_cond_body[idx]);
            switch_stmt->appendBranch(minor_cond_expr, minor_cond_body);
        }
        switch_stmt->setDefault(GetFromCtxIfExist<Statement*>(context->default_body));
        return NodeWarp(switch_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitWhile(rexLangParser::WhileContext *context) {
        WhileStmt* while_stmt = CreateNode<WhileStmt>(context);
        while_stmt->setLoopCondition(GetFromCtxIfExist<Expression*>(context->condition_expr));
        while_stmt->setLoopBody(GetFromCtxIfExist<Statement*>(context->loop_body));
        return NodeWarp(while_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitRangeFor(rexLangParser::RangeForContext *context) {
        RangeForStmt* range_for_stmt = CreateNode<RangeForStmt>(context);
        range_for_stmt->setRangeSize(GetFromCtxIfExist<Expression*>(context->times_expr));
        range_for_stmt->setLoopVariable(GetFromCtxIfExist<HierarchyIdentifier*>(context->loop_variable));
        range_for_stmt->setLoopBody(GetFromCtxIfExist<Statement*>(context->loop_body));
        return NodeWarp(range_for_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitFor(rexLangParser::ForContext *context) {
        ForStmt* for_stmt = CreateNode<ForStmt>(context);
        for_stmt->setStartValue(GetFromCtxIfExist<Expression*>(context->loop_start));
        for_stmt->setStopValue (GetFromCtxIfExist<Expression*>(context->loop_end));
        for_stmt->setStepValue (GetFromCtxIfExist<Expression*>(context->loop_step));
        for_stmt->setLoopVari  (GetFromCtxIfExist<HierarchyIdentifier*>(context->loop_variable));
        for_stmt->setLoopBody  (GetFromCtxIfExist<Statement*>(context->loop_body));
        return NodeWarp(for_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitDoWhile(rexLangParser::DoWhileContext *context) {
        DoWhileStmt* do_while_stmt = CreateNode<DoWhileStmt>(context);
        do_while_stmt->setCondition(GetFromCtxIfExist<Expression*>(context->condition_expr));
        do_while_stmt->setLoopBody(GetFromCtxIfExist<Statement*>(context->loop_body));
        return NodeWarp(do_while_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitIfStmt(rexLangParser::IfStmtContext *context) {
        IfStmt* if_stmt = CreateNode<IfStmt>(context);
        Expression* condition = GetFromCtxIfExist<Expression*>(context->condition_expr);
        Statement* true_statement = GetFromCtxIfExist<Statement*>(context->true_stmt_list);
        if_stmt->appendBranch(condition, true_statement);
        if_stmt->setDefault(GetFromCtxIfExist<Statement*>(context->false_stmt_list));
        return NodeWarp(if_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitIfTrueStmt(rexLangParser::IfTrueStmtContext *context) {
        IfStmt* if_stmt = CreateNode<IfStmt>(context);
        Expression* condition = GetFromCtxIfExist<Expression*>(context->condition_expr);
        Statement* true_statement = GetFromCtxIfExist<Statement*>(context->true_stmt_list);
        if_stmt->appendBranch(condition, true_statement);
        return NodeWarp(if_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitControlStatement(rexLangParser::ControlStatementContext *context) {
        return NodeWarp(GetFromCtxIfExist<ControlStmt*>(context->control_statement()));
    }

    antlrcpp::Any CST2ASTConvert::visitContinueStmt(rexLangParser::ContinueStmtContext *context) {
        ContinueStmt* continue_stmt = CreateNode<ContinueStmt>(context);
        return NodeWarp(continue_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitBreakStmt(rexLangParser::BreakStmtContext *context) {
        BreakStmt* break_stmt = CreateNode<BreakStmt>(context);
        return NodeWarp(break_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitReturnStmt(rexLangParser::ReturnStmtContext *context) {
        ReturnStmt* return_stmt = CreateNode<ReturnStmt>(context);
        return_stmt->setReturnValue(GetFromCtxIfExist<Expression*>(context->return_expr));
        return NodeWarp(return_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitExitStmt(rexLangParser::ExitStmtContext *context) {
        ExitStmt* exit_stmt = CreateNode<ExitStmt>(context);
        return NodeWarp(exit_stmt);
    }

    antlrcpp::Any CST2ASTConvert::visitHierarchy_identifier(rexLangParser::Hierarchy_identifierContext *context) {
        HierarchyIdentifier* hierarchy_identifier = CreateNode<HierarchyIdentifier>(context);
        for (auto *name_component_ctx : context->components) {
            NameComponent* name_component = GetFromCtxIfExist<NameComponent*, true>(name_component_ctx);
            hierarchy_identifier->AppendComponent(name_component);
        }
        return NodeWarp(hierarchy_identifier);
    }

    antlrcpp::Any CST2ASTConvert::visitFuncCall(rexLangParser::FuncCallContext *context) {
        FunctionCall* function_call = CreateNode<FunctionCall>(context);
        function_call->setCallName(GetFromCtxIfExist<NameComponent*, true>(context->name_component()));
        for (auto *arg_ctx : context->arguments) {
            Expression* arg_expr = GetFromCtxIfExist<Expression*>(arg_ctx);
            function_call->appendArgument(arg_expr);
        }
        return NodeWarp(function_call);
    }

    antlrcpp::Any CST2ASTConvert::visitIdentifier(rexLangParser::IdentifierContext *context) {
        Identifier* identifier = CreateNode<Identifier>(context, GetTextIfExist(context->IDENTIFIER()->getSymbol()));
        return NodeWarp(identifier);
    }

    antlrcpp::Any CST2ASTConvert::visitArrayIndex(rexLangParser::ArrayIndexContext *context) {
        ArrayIndex* array_index = CreateNode<ArrayIndex>(context);
        array_index->setBaseComponent(GetFromCtxIfExist<NameComponent*, true>(context->name_component()));
        array_index->setIndexExpr(GetFromCtxIfExist<Expression*>(context->expression()));
        return NodeWarp(array_index);
    }

    antlrcpp::Any CST2ASTConvert::visitBracket(rexLangParser::BracketContext *context) {
        return NodeWarp(GetFromCtxIfExist<Expression*>(context->expression()));
    }

    antlrcpp::Any CST2ASTConvert::visitOptElement(rexLangParser::OptElementContext *context) {
        return NodeWarp(GetFromCtxIfExist<Expression*>(context->getRuleContext<antlr4::ParserRuleContext>(0)));
    }

    antlrcpp::Any CST2ASTConvert::visitBinaryExpr(rexLangParser::BinaryExprContext *context) {
        BinaryExpression* binary_expression = CreateNode<BinaryExpression>(context);
        binary_expression->setOperatorText(GetTextIfExist(context->opt));
        switch (context->opt->getType()) {
            if (0) { case rexLangParser::K_ADD_OPT:        binary_expression->setOperator(OperatorType::Opt::kOptAdd);        break; }
            if (0) { case rexLangParser::K_SUB_OPT:        binary_expression->setOperator(OperatorType::Opt::kOptSub);        break; }
            if (0) { case rexLangParser::K_MUL_OPT:        binary_expression->setOperator(OperatorType::Opt::kOptMul);        break; }
            if (0) { case rexLangParser::K_DIV_OPT:        binary_expression->setOperator(OperatorType::Opt::kOptDiv);        break; }
            if (0) { case rexLangParser::K_FULL_DIV_OPT:   binary_expression->setOperator(OperatorType::Opt::kOptFullDiv);    break; }
            if (0) { case rexLangParser::K_MOD_OPT:        binary_expression->setOperator(OperatorType::Opt::kOptMod);        break; }
            if (0) { case rexLangParser::K_AECOM_OPT:      binary_expression->setOperator(OperatorType::Opt::kOptEqual);      break; }
            if (0) { case rexLangParser::K_ASSIGN_OPT:     binary_expression->setOperator(OperatorType::Opt::kOptEqual);      break; }
            if (0) { case rexLangParser::K_EQUAL_OPT:      binary_expression->setOperator(OperatorType::Opt::kOptEqual);      break; }
            if (0) { case rexLangParser::K_NOT_EQUAL_OPT:  binary_expression->setOperator(OperatorType::Opt::kOptNotEqual);   break; }
            if (0) { case rexLangParser::K_GREAT_OPT:      binary_expression->setOperator(OperatorType::Opt::kOptGreatThan);  break; }
            if (0) { case rexLangParser::K_LESS_OPT:       binary_expression->setOperator(OperatorType::Opt::kOptLessThan);   break; }
            if (0) { case rexLangParser::K_GREAT_EQU_OPT:  binary_expression->setOperator(OperatorType::Opt::kOptGreatEqual); break; }
            if (0) { case rexLangParser::K_LESS_EQU_OPT:   binary_expression->setOperator(OperatorType::Opt::kOptLessEqual);  break; }
            if (0) { case rexLangParser::K_LIKE_EQU_OPT:   binary_expression->setOperator(OperatorType::Opt::kOptLikeEqual);  break; }
            if (0) { case rexLangParser::K_AND_OPT:        binary_expression->setOperator(OperatorType::Opt::kOptAnd);        break; }
            if (0) { case rexLangParser::K_OR_OPT:         binary_expression->setOperator(OperatorType::Opt::kOptOr);         break; }
            if (0) { default: assert(false);               binary_expression->setOperator(OperatorType::Opt::kOptNone);       break; }
        }
        binary_expression->setLHS(GetFromCtxIfExist<Expression*>(context->lval));
        binary_expression->setRHS(GetFromCtxIfExist<Expression*>(context->rval));
        return NodeWarp(binary_expression);
    }

    antlrcpp::Any CST2ASTConvert::visitUnaryExpr(rexLangParser::UnaryExprContext *context) {
        UnaryExpression* unary_expression = CreateNode<UnaryExpression>(context);
        unary_expression->setOperatorText(GetTextIfExist(context->opt));
        switch (context->opt->getType()) {
            if (0) { case rexLangParser::K_SUB_OPT:    unary_expression->setOperator(OperatorType::Opt::kOptSub);  break; }
            if (0) { default: assert(false);           unary_expression->setOperator(OperatorType::Opt::kOptNone); break; }
        }
        unary_expression->setOperand(GetFromCtxIfExist<Expression*>(context->expression()));
        return NodeWarp(unary_expression);
    }

    antlrcpp::Any CST2ASTConvert::visitData_set_value(rexLangParser::Data_set_valueContext *context) {
        ValueOfDataSet* value_of_data_set = CreateNode<ValueOfDataSet>(context);
        for (auto *elem_ctx : context->elems) {
            value_of_data_set->appendElement(GetFromCtxIfExist<Expression*>(elem_ctx));
        }
        return NodeWarp(value_of_data_set);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetime_value(rexLangParser::Datetime_valueContext *context) {
        return NodeWarp(GetFromCtxIfExist<ValueOfDatetime*>(context->datetime_value_core()));
    }

    ValueOfDatetime* CST2ASTConvert::TimeNodeBuilder(time_t ntm, antlr4::ParserRuleContext *parserRuleContext) {
        auto start_token = parserRuleContext->getStart();
        auto end_token   = parserRuleContext->getStop();
        ValueOfDatetime* value_of_datetime = CreateNode<ValueOfDatetime>(start_token, end_token);
        value_of_datetime->setTime(ntm);
        return value_of_datetime;
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimePureNumber(rexLangParser::DatetimePureNumberContext *context) {
        TString time_str = GetTextIfExist(context->time);
        return TimeNodeBuilder(strtoul(time_str.string_.c_str(), nullptr, 10), context);
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

    antlrcpp::Any CST2ASTConvert::visitDatetimeSeparateByChinese(rexLangParser::DatetimeSeparateByChineseContext *context) {
        tm time = TimeBuilder(
                GetLongIfExist(context->year),
                GetLongIfExist(context->month),
                GetLongIfExist(context->day),
                GetLongIfExist(context->hour),
                GetLongIfExist(context->minute),
                GetLongIfExist(context->second)
        );
        ValueOfDatetime* new_time = TimeNodeBuilder(mktime(&time), (antlr4::ParserRuleContext *) context);
        return NodeWarp(new_time);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimeSeparateBySlash(rexLangParser::DatetimeSeparateBySlashContext *context) {
        tm time = TimeBuilder(
                GetLongIfExist(context->year),
                GetLongIfExist(context->month),
                GetLongIfExist(context->day),
                GetLongIfExist(context->hour),
                GetLongIfExist(context->minute),
                GetLongIfExist(context->second)
        );
        ValueOfDatetime* new_time = TimeNodeBuilder(mktime(&time), context);
        return NodeWarp(new_time);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimeSeparateBySlashColon(rexLangParser::DatetimeSeparateBySlashColonContext *context) {
        tm time = TimeBuilder(
                GetLongIfExist(context->year),
                GetLongIfExist(context->month),
                GetLongIfExist(context->day),
                GetLongIfExist(context->hour),
                GetLongIfExist(context->minute),
                GetLongIfExist(context->second)
        );
        ValueOfDatetime* new_time = TimeNodeBuilder(mktime(&time), context);
        return NodeWarp(new_time);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimeSeparateByBar(rexLangParser::DatetimeSeparateByBarContext *context) {
        tm time = TimeBuilder(
                GetLongIfExist(context->year),
                GetLongIfExist(context->month),
                GetLongIfExist(context->day),
                GetLongIfExist(context->hour),
                GetLongIfExist(context->minute),
                GetLongIfExist(context->second)
        );
        ValueOfDatetime* new_time = TimeNodeBuilder(mktime(&time), context);
        return NodeWarp(new_time);
    }

    antlrcpp::Any CST2ASTConvert::visitDatetimeSeparateByBarColon(rexLangParser::DatetimeSeparateByBarColonContext *context) {
        tm time = TimeBuilder(
                GetLongIfExist(context->year),
                GetLongIfExist(context->month),
                GetLongIfExist(context->day),
                GetLongIfExist(context->hour),
                GetLongIfExist(context->minute),
                GetLongIfExist(context->second)
        );
        ValueOfDatetime* new_time = TimeNodeBuilder(mktime(&time), context);
        return NodeWarp(new_time);
    }

    antlrcpp::Any CST2ASTConvert::visitMacro_value(rexLangParser::Macro_valueContext *context) {
        ResourceRefExpression* resource_ref_expression = CreateNode<ResourceRefExpression>(context);
        resource_ref_expression->setResourceName(GetTextIfExist(context->IDENTIFIER()->getSymbol()));
        return NodeWarp(resource_ref_expression);
    }

    antlrcpp::Any CST2ASTConvert::visitFunc_ptr(rexLangParser::Func_ptrContext *context) {
        FuncAddrExpression *func_addr_expression = CreateNode<FuncAddrExpression>(context);
        Identifier *reference = CreateNode<Identifier>(context, GetTextIfExist(context->IDENTIFIER()->getSymbol()));
        func_addr_expression->setRefFuncName(reference);
        return NodeWarp(func_addr_expression);
    }

    antlrcpp::Any CST2ASTConvert::visitBoolValueTrue(rexLangParser::BoolValueTrueContext *context) {
        ValueOfBool* value_of_bool = CreateNode<ValueOfBool>(context);
        value_of_bool->setBool(true);
        return NodeWarp(value_of_bool);
    }

    antlrcpp::Any CST2ASTConvert::visitBoolValueFalse(rexLangParser::BoolValueFalseContext *context) {
        ValueOfBool* value_of_bool = CreateNode<ValueOfBool>(context);
        value_of_bool->setBool(false);
        return NodeWarp(value_of_bool);
    }

    antlrcpp::Any CST2ASTConvert::visitInt(rexLangParser::IntContext *context) {
        ValueOfDecimal* value_of_decimal = CreateNode<ValueOfDecimal>(context);
        value_of_decimal->setIntValue(GetLongIfExist(context->INTEGER_LITERAL()->getSymbol()));
        return NodeWarp(value_of_decimal);
    }

    antlrcpp::Any CST2ASTConvert::visitFloat(rexLangParser::FloatContext *context) {
        ValueOfDecimal* value_of_decimal = CreateNode<ValueOfDecimal>(context);
        value_of_decimal->setFloatValue(GetFloatIfExist(context->FLOAT_LITERAL()->getSymbol()));
        return NodeWarp(value_of_decimal);
    }

    antlrcpp::Any CST2ASTConvert::visitString_value(rexLangParser::String_valueContext *context) {
        ValueOfString* value_of_string = CreateNode<ValueOfString>(context);
        value_of_string->setStringLiteral(RemoveRoundQuotes(GetTextIfExist(context->STRING_LITERAL()->getSymbol())));
        return NodeWarp(value_of_string);
    }

    CST2ASTConvert::CST2ASTConvert(ASTContext *ast_context, Diagnostic *diagnostic)
        : ast_context_(ast_context) {
    }

    TranslateUnit * CST2ASTConvert::BuildTranslateUnitFromParseTree(antlr4::tree::ParseTree *tree) {
        antlrcpp::Any build_result = this->visit(tree);
        TranslateUnit * translate_unit = nullptr;
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
