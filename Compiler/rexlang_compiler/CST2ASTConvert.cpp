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
#include "../compile_driver.h"
#include "rtti.h"
#include "utilities/Str2Attr.h"

/*===---------------------------------------------------------===*
 * 辅助函数
 *===---------------------------------------------------------===*/

namespace rexlang {

    static void RemoveRoundQuotes(TString &tString) {
        if (!tString.string_.empty() && tString.string_.str().front() == '"' && tString.string_.str().back() == '"') {
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

    std::vector<TString> CST2ASTConvert::GetTextVecIfExist(const std::vector<antlr4::Token *> &tokens, const std::string &hint) const {
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
    NodeTy *CST2ASTConvert::CreateNode(antlr4::Token *start_token, antlr4::Token *end_token, Args &&... args) {
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
    NodeTy *CreateNode(antlr4::ParserRuleContext *parserRuleContext, Args &&... args) {
        return CreateNode<NodeTy, Args...>(parserRuleContext->getStart(), parserRuleContext->getStop(), args...);
    }

    template <typename T, typename>
    std::vector<T *> CST2ASTConvert::filterSources() {
        std::vector<T *> source_list;
        for (rexLangParser::Src_contentContext * ctx : source_cache_) {
            if (T *tgt_ctx = ctx->getRuleContext<T>(0)) {
                source_list.push_back(tgt_ctx);
            }
        }
        return source_list;
    }

    template <typename T, typename>
    TString CST2ASTConvert::getTableComment(T *ctx) {
        return GetFromCtxIfExist<TString>(ctx->table_comment());
    }

    TString CST2ASTConvert::getTableComment(rexLangParser::Table_commentContext *commentCtx) {
        return GetFromCtxIfExist<TString>(commentCtx);
    }

    /*===----------------------------------------------------===*
     * 从分析树上下文对象中构建变量定义
     * 内部自动处理：变量名称、变量类型、数组声明、注释信息
     * 需要外部处理：属性列表
     */
    template <typename N, typename T, typename>
    N *CST2ASTConvert::buildVariableDecl(T *ctx) {

        // 取得名称

        IdentDef *name = CreateNode<IdentDef>(ctx, GetTextIfExist(ctx->name));

        // 取得类型

        TString type_name = GetTextIfExist(ctx->type);
        VariTypeDecl *type = rtti::dyn_cast<VariTypeDecl>(ast_context_->getTranslateUnit()->getType(type_name.string_));
        TString dimension_str = GetTextIfExist(ctx->dimension);
        if (!dimension_str.string_.empty()) {
            auto err_or_dims = Str2Attr::str2Dimension(dimension_str.string_);
            assert(err_or_dims.NoError());
            type = ArrayDecl::get(type, err_or_dims.Value());
        }

        // 构造变量定义

        N *variable_decl = CreateNode<N>(ctx, type, name);
        variable_decl->setComment(getTableComment(ctx));

        return variable_decl;
    }

    /*===----------------------------------------------------===*
     * 从分析树上下文对象中构建参数定义
     */
    template <typename T, typename>
    ParameterDecl *CST2ASTConvert::buildParameterDecl(T *ctx) {
        IdentDef *name = CreateNode<IdentDef>(ctx, GetTextIfExist(ctx->name));

        TString type_name = GetTextIfExist(ctx->type);
        VariTypeDecl *type = rtti::dyn_cast<VariTypeDecl>(ast_context_->getTranslateUnit()->getType(type_name.string_));

        ParameterDecl *parameter_decl = CreateNode<ParameterDecl>(ctx, type, name);
        parameter_decl->applyAttributes(GetTextVecIfExist(ctx->attributes));
        parameter_decl->setComment(getTableComment(ctx));

        return parameter_decl;
    }

    /*===----------------------------------------------------===*
     * 从分析树上下文获取形式参数列表
     */
    std::vector<ParameterDecl *> CST2ASTConvert::getParameterDecl(rexLangParser::Parameter_decl_listContext *paramsCtx) {
        std::vector<ParameterDecl *> parameters = GetFromCtxIfExist<std::vector<ParameterDecl*>>(paramsCtx);
        return parameters;
    }

}

/*===---------------------------------------------------------===*
 * 转换
 *===---------------------------------------------------------===*/

namespace rexlang {

    antlrcpp::Any CST2ASTConvert::visitTable_comment(rexLangParser::Table_commentContext *context) {
        return GetTextIfExist(context->comment);
    }

    // --- 加载待解析资源 ---------------------------------------------------------------------------------

    antlrcpp::Any CST2ASTConvert::visitRexlang_src(rexLangParser::Rexlang_srcContext *context) {
        TranslateUnit * translate_unit = ast_context_->getTranslateUnit();
        if(!translate_unit) {
            translate_unit = CreateNode<TranslateUnit>(context);
            ast_context_->setTranslateUnit(translate_unit);
        }

        ast_context_->cleanScopeStack();
        ast_context_->pushScope(translate_unit);

        // 分析版本号并检查兼容性
        unsigned int edition = GetFromCtxIfExist<unsigned int, true>(context->edition_spec(), 2);
        assert(edition == 2);
        translate_unit->setSourceEdition(edition);

        // 将源文件上下文添加到待处理池中，以便于后续分类处理
        rexLangParser::Src_contentContext *src_ctx = context->src_content();
        this->source_cache_.insert(src_ctx);

        ast_context_->popScope(translate_unit);
        return NodeWarp(translate_unit);
    }

    bool CST2ASTConvert::buildTranslateUnitAndFetchSrc(const std::vector<antlr4::tree::ParseTree *> &trees) {

        for (antlr4::tree::ParseTree *tree : trees) {
            this->visit(tree);
        }

        return true;
    }

    // --- 外部库引入 ---------------------------------------------------------------------------------

    bool CST2ASTConvert::importLibraries() {
        std::vector<rexLangParser::Program_set_fileContext *> ctx_list = this->filterSources<rexLangParser::Program_set_fileContext>();
        for (rexLangParser::Program_set_fileContext * ctx : ctx_list) {
            for (antlr4::Token *token : ctx->libraries) {
                TString library_name = GetTextIfExist(token);
                /// 此处调用 CompilerInstance 分析引用的库
                antlr4::tree::ParseTree *parse_tree = compiler_instance_->processExternLibrary(library_name.string_);
                assert(parse_tree);
                /// 就地对引用库进行进一步分析（一般情况下引用库接口文件是一组定义文件）
                this->buildTUFromParseTrees({parse_tree});
            }
        }
        return true;
    }

    // --- 自定义数据结构 ---------------------------------------------------------------------------------

    bool CST2ASTConvert::parseDataStructFiles() {
        TranslateUnit *TU = ast_context_->getTranslateUnit();
        std::map<StructureDecl *, rexLangParser::Struct_declareContext *> structures;
        std::vector<rexLangParser::Data_structure_fileContext *> ctx_list = this->filterSources<rexLangParser::Data_structure_fileContext>();
        for (rexLangParser::Data_structure_fileContext *ctx : ctx_list) {
            DataStructureFile *ds_file = CreateNode<DataStructureFile>(ctx);
            // 扫描数据结构列表并创建空声明
            for (rexLangParser::Struct_declareContext *struct_decl_ctx : ctx->struct_declare()) {

                // 获取名称
                antlr4::Token *name_tk = struct_decl_ctx->name;
                assert(name_tk);
                TString name = GetTextIfExist(name_tk, "");
                assert(name.string_ != "");
                IdentDef *struct_name = CreateNode<IdentDef>(name_tk, name_tk, name.string_);

                // 创建节点
                StructureDecl *structure_decl = CreateNode<StructureDecl>(struct_decl_ctx, struct_name);

                // 设置公有属性
                structure_decl->applyAttribute(GetTextIfExist(struct_decl_ctx->access));
                structure_decl->setComment(getTableComment(struct_decl_ctx));

                // 注册到类型池中
                ds_file->appendStructureDecl(structure_decl);
                structures.insert(std::make_pair(structure_decl, struct_decl_ctx));
            }
            ds_file->registResourceTo(TU);
        }

        // 对每个空声明创建定义实体并检查循环引用问题
        for (auto &item : structures) {
            StructureDecl *struct_decl = item.first;
            rexLangParser::Struct_declareContext *struct_decl_ctx = item.second;
            for (rexLangParser::Member_vari_declContext *mem_ctx : struct_decl_ctx->struct_mems) {
                MemberVariableDecl *member = GetFromCtxIfExist<MemberVariableDecl *>(mem_ctx);
                assert(member);
                // TODO: 检查循环引用
                struct_decl->appendElement(member);
            }
        }

        return true;
    }

    antlrcpp::Any CST2ASTConvert::visitMember_vari_decl(rexLangParser::Member_vari_declContext *context) {
        MemberVariableDecl* member_variable_decl = buildVariableDecl<MemberVariableDecl>(context->variable_decl());
        member_variable_decl->applyAttributes(GetTextVecIfExist(context->variable_decl()->attributes));
        return NodeWarp(member_variable_decl);
    }

    // --- 全局变量 ---------------------------------------------------------------------------------
    // GlobalVariableFiles
    //      `---global_variable_file
    //              `---global_variable_list
    //                      `---global_variable_item

    bool CST2ASTConvert::parseGlobalVariableFiles() {
        TranslateUnit *TU = ast_context_->getTranslateUnit();
        std::vector<rexLangParser::Global_variable_fileContext *> ctx_list = this->filterSources<rexLangParser::Global_variable_fileContext>();
        for (rexLangParser::Global_variable_fileContext *ctx : ctx_list) {
            GlobalVariableFile * gvari_file = this->GetFromCtxIfExist<GlobalVariableFile *>(ctx);
            gvari_file->registResourceTo(TU);
        }
    }

    antlrcpp::Any CST2ASTConvert::visitGlobal_variable_file(rexLangParser::Global_variable_fileContext *context) {
        GlobalVariableFile* global_variable_file = CreateNode<GlobalVariableFile>(context);
        rexLangParser::Global_variable_listContext *gvari_list_ctx = context->global_variable_list();
        GlobalVariableFile::GlobalVariMapTy gvari_map = GetFromCtxIfExist<GlobalVariableFile::GlobalVariMapTy>(gvari_list_ctx);
        for (auto &gvari_item : gvari_map) {
            global_variable_file->appendGlobalVariableDecl(gvari_item.second);
        }
        return NodeWarp(global_variable_file);
    }

    antlrcpp::Any CST2ASTConvert::visitGlobal_variable_list(rexLangParser::Global_variable_listContext *context) {
        GlobalVariableFile::GlobalVariMapTy gvari_map;
        for (rexLangParser::Global_variable_itemContext *global_vari_decl_ctx : context->global_variable_item()) {
            GlobalVariableDecl *global_variable_decl = GetFromCtxIfExist<GlobalVariableDecl *>(global_vari_decl_ctx);
            gvari_map[StringPool::Create(global_variable_decl->getNameStr())] = global_variable_decl;
        }
        return gvari_map;
    }

    antlrcpp::Any CST2ASTConvert::visitGlobal_variable_item(rexLangParser::Global_variable_itemContext *context) {
        GlobalVariableDecl* global_variable_decl = buildVariableDecl<GlobalVariableDecl>(context);
        global_variable_decl->applyAttribute(GetTextIfExist(context->access));
        return NodeWarp(global_variable_decl);
    }

    // --- 文件静态变量 ---------------------------------------------------------------------------------

    antlrcpp::Any CST2ASTConvert::visitFile_vari_decl(rexLangParser::File_vari_declContext *context) {
        FileVariableDecl* file_variable_decl = buildVariableDecl<FileVariableDecl>(context->variable_decl());
        file_variable_decl->applyAttributes(GetTextVecIfExist(context->variable_decl()->attributes));
        return NodeWarp(file_variable_decl);
    }

    // --- 局部变量 ---------------------------------------------------------------------------------

    antlrcpp::Any CST2ASTConvert::visitLocal_variable_decl(rexLangParser::Local_variable_declContext *context) {
        LocalVariableDecl* local_variable_decl = buildVariableDecl<LocalVariableDecl>(context);
        local_variable_decl->applyAttribute(GetTextIfExist(context->attribute));
        return NodeWarp(local_variable_decl);
    }

    // --- 函数声明及参数定义 ---------------------------------------------------------------------------------

    bool CST2ASTConvert::parseGlobalFuntors() {
        // 先处理DLL定义文件中DLL与LIB声明
        TranslateUnit *TU = ast_context_->getTranslateUnit();
        std::vector<rexLangParser::Api_define_fileContext *> dll_ctx_list = this->filterSources<rexLangParser::Api_define_fileContext>();
        for (rexLangParser::Api_define_fileContext *ctx : dll_ctx_list) {
            APIDeclareFile *api_declare_file = GetFromCtxIfExist<APIDeclareFile *>(ctx);
            api_declare_file->registResourceTo(TU);
        }
        // 然后处理各个程序集中的函数声明
        std::vector<rexLangParser::Program_set_fileContext *> prg_ctx_list = this->filterSources<rexLangParser::Program_set_fileContext>();
        for (rexLangParser::Program_set_fileContext *ctx : prg_ctx_list) {
            ProgramSetFile *program_set_file = CreateNode<ProgramSetFile>(ctx);
            if (rexLangParser::Prog_setContext *prog_set_ctx = ctx->prog_set()) {
                ProgSetDecl *prog_set_decl = CreateNode<ProgSetDecl>(prog_set_ctx);
                for (rexLangParser::Sub_programContext *prog_ctx : prog_set_ctx->functions) {
                    // TODO:创建声明
                }
                program_set_file->appendProgramSetDecl(prog_set_decl);
            }
            program_set_file->registResourceTo(TU);
        }
        return true;
    }

    antlrcpp::Any CST2ASTConvert::visitApi_define_file(rexLangParser::Api_define_fileContext *context) {
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
        TranslateUnit *TU            = ast_context_->getTranslateUnit();
        TString        library_file  = RemoveRoundQuotes(GetTextIfExist(context->file));
        TString        name          = RemoveRoundQuotes(GetTextIfExist(context->name));
        TString        api_name      = RemoveRoundQuotes(GetTextIfExist(context->cmd));
        TString        ret_type_name = GetTextIfExist(context->type);
        VariTypeDecl * ret_type      = rtti::dyn_cast<VariTypeDecl>(TU->getType(ret_type_name.string_));

        APICommandDecl *dll_api_decl = CreateNode<APICommandDecl>(context,
                /*retType*/     ret_type,
                /*name*/        CreateNode<IdentDef>(context, name),
                /*parameters*/  getParameterDecl(context->params),
                /*libraryType*/ LibraryType::kLTDynamic,
                /*libraryName*/ library_file,
                /*apiName*/     api_name
        );
        dll_api_decl->setComment(getTableComment(context));
        return NodeWarp(dll_api_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitLib_command(rexLangParser::Lib_commandContext *context) {
        TranslateUnit *TU            = ast_context_->getTranslateUnit();
        TString        library_file  = RemoveRoundQuotes(GetTextIfExist(context->file));
        TString        name          = RemoveRoundQuotes(GetTextIfExist(context->name));
        TString        api_name      = RemoveRoundQuotes(GetTextIfExist(context->cmd));
        TString        ret_type_name = GetTextIfExist(context->type);
        VariTypeDecl * ret_type      = rtti::dyn_cast<VariTypeDecl>(TU->getType(ret_type_name.string_));

        APICommandDecl* lib_api_decl = CreateNode<APICommandDecl>(context,
                /*retType*/     ret_type,
                /*name*/        CreateNode<IdentDef>(context, name),
                /*parameters*/  getParameterDecl(context->params),
                /*libraryType*/ LibraryType::kLTStatic,
                /*libraryName*/ library_file,
                /*apiName*/     api_name
        );
        lib_api_decl->setComment(getTableComment(context));
        return NodeWarp(lib_api_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitParameter_decl_list(rexLangParser::Parameter_decl_listContext *context) {
        std::vector<ParameterDecl*> params;

        // 常规参数表
        for (rexLangParser::Parameter_declContext *param_vari_ctx : context->parameter_decl()) {
            ParameterDecl *parameter_decl = GetFromCtxIfExist<ParameterDecl *>(param_vari_ctx);
            params.emplace_back(parameter_decl);
        }

        // 可变参数项
        if (rexLangParser::Vari_parameter_declContext *vari_param_ctx = context->vari_parameter_decl()) {
            ParameterDecl *vari_parameter_decl = GetFromCtxIfExist<ParameterDecl *>(vari_param_ctx);
            params.emplace_back(vari_parameter_decl);
        }

        return params;
    }

    antlrcpp::Any CST2ASTConvert::visitParameter_decl(rexLangParser::Parameter_declContext *context) {
        ParameterDecl* parameter_decl = buildParameterDecl(context);
        return NodeWarp(parameter_decl);
    }

    antlrcpp::Any CST2ASTConvert::visitVari_parameter_decl(rexLangParser::Vari_parameter_declContext *context) {
        ParameterDecl* parameter_decl = buildParameterDecl(context);
        return NodeWarp(parameter_decl);
    }

    /******************************************************************************************************************/

    antlrcpp::Any CST2ASTConvert::visitSrc_content(rexLangParser::Src_contentContext *context) {
               if (auto *program_set_file_ctx     = context->program_set_file())     { return NodeWarp(GetFromCtxIfExist<ProgramSetFile*,     true>(program_set_file_ctx));
        } else if (auto *global_variable_file_ctx = context->global_variable_file()) { return NodeWarp(GetFromCtxIfExist<GlobalVariableFile*, true>(global_variable_file_ctx));
        } else if (auto *dll_define_file_ctx      = context->dll_define_file())      { return NodeWarp(GetFromCtxIfExist<APIDeclareFile*,     true>(dll_define_file_ctx));
        } else { return NodeWarp(nullptr); }
    }

    antlrcpp::Any CST2ASTConvert::visitProgram_set_file(rexLangParser::Program_set_fileContext *context) {
        auto program_set_file = CreateNode<ProgramSetFile>(context);
        // 依赖库已经在 importLibraries 被提取，此处不再处理
        program_set_file->appendProgramSetDecl(GetFromCtxIfExist<ProgSetDecl*>(context->prog_set()));
        return NodeWarp(program_set_file);
    }

    antlrcpp::Any CST2ASTConvert::visitEdition_spec(rexLangParser::Edition_specContext *context) {
        return (unsigned int) strtoul(context->INTEGER_LITERAL()->getText().c_str(), nullptr, 10);
    }

    antlrcpp::Any CST2ASTConvert::visitProg_set(rexLangParser::Prog_setContext *context) {
        ProgSetDecl* prog_set_decl = CreateNode<ProgSetDecl>(context);
        ast_context_->pushScope(prog_set_decl);

        prog_set_decl->setName(GetTextIfExist(context->name));
        prog_set_decl->applyAttribute(GetTextIfExist(context->access));
        prog_set_decl->setComment(getTableComment(context));
        for (rexLangParser::File_vari_declContext *vari_ctx : context->prog_set_varis) {
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

    antlrcpp::Any CST2ASTConvert::visitSub_program(rexLangParser::Sub_programContext *context) {
        FunctionDecl* sub_prog_decl = CreateNode<FunctionDecl>(context);
        ast_context_->pushScope(sub_prog_decl);

        sub_prog_decl->setName(GetTextIfExist(context->name));
        sub_prog_decl->setReturnTypeName(GetTextIfExist(context->type));
        sub_prog_decl->applyAttribute(GetTextIfExist(context->access));
        sub_prog_decl->setComment(getTableComment(context));
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
        IdentRefer* identifier = CreateNode<IdentRefer>(context, GetTextIfExist(context->IDENTIFIER()->getSymbol()));
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
        IdentRefer *reference = CreateNode<IdentRefer>(context, GetTextIfExist(context->IDENTIFIER()->getSymbol()));
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

    CST2ASTConvert::CST2ASTConvert(ASTContext *ast_context, Diagnostic *diagnostic, REXCompilerInstance *compiler_instance)
        : ast_context_(ast_context), compiler_instance_(compiler_instance) {
    }

    TranslateUnit * CST2ASTConvert::buildTUFromParseTrees(const std::vector<antlr4::tree::ParseTree *> &trees) {

        // TODO: 这里可以尝试合并一下树，或者给树排序
        // TODO: 在编译过程中遇到外部文件引用会重入这个函数
        // TODO: 分层的遍历CST，而不是一次性遍历整个树

        this->buildTranslateUnitAndFetchSrc(trees);
        this->importLibraries();

        this->parseDataStructFiles();
        this->parseGlobalVariableFiles();
        this->parseGlobalFuntors();

        return ast_context_->getTranslateUnit();
    }

}
