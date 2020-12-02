/*
 * 抽象语法树下降器
 * Rexfield
 * 2020/11/29
 */

#include "LowAST.h"
#include "../../rexlang_compiler/NodeDecl.h"
#include "../../support/ProjectDB.h"
#include "../../rexlang_compiler/rtti.h"

namespace rexlang {

    class Lower {
    private:
        ProjectDB &project_db_ ;
        StatementBlock *startup_stmtblk_ = nullptr ;    // 启动函数语句块
        StatementBlock *init_stmtblk_    = nullptr ;    // 初始化函数语句块

    private:    // 启动
        // 创建启动和初始化函数
        int CreateStartup() {
            ASTContext &ast_context = project_db_.GetASTContext();
            TranslateUnit *TU = ast_context.getTranslateUnit();
            assert(TU);

            // 创建虚拟的代码文件

            ProgramSetFile *sys_fw_sf = CreateNode<ProgramSetFile>(&ast_context);
            ProgSetDecl *sys_fw_ps = CreateNode<ProgSetDecl>(&ast_context, CreateNode<IdentDef>(&ast_context, "@system_fw"));
            sys_fw_sf->appendProgramSetDecl(sys_fw_ps);
            TU->appendSourceFile(sys_fw_sf);

            // 创建启动函数

            IdentDef *rex_startup_fn_name = CreateNode<IdentDef>(&ast_context, "RexStartup");
            assert(rex_startup_fn_name);
            FunctionDecl *startup_fn = CreateNode<FunctionDecl>(&ast_context, TU->getIntegerTy(), rex_startup_fn_name, std::vector<ParameterDecl *>());
            sys_fw_ps->appendFunctionDecl(startup_fn);
            startup_stmtblk_ = CreateNode<StatementBlock>(&ast_context, std::vector<Statement *>());

            // 创建初始化函数

            IdentDef *init_fn_name = CreateNode<IdentDef>(&ast_context, "RexInit");
            assert(init_fn_name);
            FunctionDecl *init_fn = CreateNode<FunctionDecl>(&ast_context, TU->getVoidTy(), init_fn_name, std::vector<ParameterDecl *>());
            sys_fw_ps->appendFunctionDecl(init_fn);
            init_stmtblk_ = CreateNode<StatementBlock>(&ast_context, std::vector<Statement *>());

            // 在启动函数中调用初始化函数

            FunctionCall *call_init_fn = CreateNode<FunctionCall>(
                    &ast_context,
                    CreateNode<IdentRefer>(&ast_context, init_fn->getName()),
                    init_fn,
                    std::vector<Expression *>()
            );
            startup_stmtblk_->appendStatement(call_init_fn);

            // 在启动函数中调用用户的入口函数，并将其返回值作为启动函数的返回值

            FunctorDecl *entry_fn = project_db_.GetMainEntry();
            FunctionCall *call_entry_fn = CreateNode<FunctionCall>(
                    &ast_context,
                    CreateNode<IdentRefer>(&ast_context, entry_fn->getName()),
                    entry_fn,
                    std::vector<Expression *>()
            );
            ReturnStmt *return_stmt = CreateNode<ReturnStmt>(&ast_context, call_entry_fn);
            startup_stmtblk_->appendStatement(return_stmt);

            return 0;
        }

    private:    // 全局字符串、字节集和数组
        // 创建全局对象初始化
        int CreateGlobalObjectInitFunction() {
            int EC = 0;
            if ((EC = InitializeGlobalArray())) { return EC; }
            if ((EC = InitializeGlobalString())) { return EC; }
            return 0;
        }

        // 初始化全局数组
        int InitializeGlobalArray() {
            // 1. 创建数组对象
            // 2. 设置数组维度
        }

        // 初始化局部数组
        int InitializeLocalArray() ;

        // 初始化全局字符串/字节集
        int InitializeGlobalString() ;

        // 初始化局部字符串/字节集
        int InitializeLocalString() ;

    private:
        // 重命名函数名
        int MangleFunctionName() {
            // 1. 用户自定义函数名添加_前缀和#后缀
            TranslateUnit *TU = project_db_.GetASTContext().getTranslateUnit();
            for (SourceFile *source_file : TU->getSourceFiles()) {
                if (ProgramSetFile *program_set_file = rtti::dyn_cast<ProgramSetFile>(source_file)) {
                    if (ProgSetDecl *prog_set_decl = program_set_file->getProgramSetDecl()) {
                        for (FunctionDecl *function_decl : prog_set_decl->functions()) {
                            assert(function_decl);
                            IdentDef *fn_name = function_decl->getName();
                            std::string mangled_name = "_" + fn_name->id().str() + "#";
                            fn_name->update(mangled_name);
                        }
                    }
                }
            }
            return 0;
        }

        // 重写字符串/字节集操作符
        int OverrideStringOperator() {
            // 1. 重写赋值操作符
            // 2. 重写加法操作符
            // 3. 重写索引操作符
        }

    private:    // 杂项辅助
        /*
         * 创建隐式系统API定义
         * corelib/array_runtime_api.h
         * corelib/string_runtime_api.h
         * corelib/struct_runtime_api.h
         */
        void CreateImplicitSysApiDecl() {
            ASTContext &ast_context = project_db_.GetASTContext();
            TranslateUnit *TU = ast_context.getTranslateUnit();
            assert(TU);

            // 创建虚拟接口文件

            APIDeclareFile *impl_api_df = CreateNode<APIDeclareFile>(&ast_context);
            TU->appendSourceFile(impl_api_df);

            auto create_corelib_api = [&ast_context, impl_api_df](
                    VariTypeDecl *retType,
                    const std::string &apiName,
                    const std::vector<ParameterDecl *> &parameters
            ) {
                APICommandDecl *created_api = CreateNode<APICommandDecl>(
                        &ast_context,
                        retType,
                        CreateNode<IdentDef>(&ast_context, apiName),
                        parameters,
                        LibraryType::kLTStatic,
                        TString(StringPool::Create("corelib"), 0),
                        CreateNode<IdentDef>(&ast_context, apiName)
                );
                impl_api_df->appendAPIDeclare(created_api);
            };

            create_corelib_api(
                    ReferenceType::get(TU->getVoidTy()),
                    "create_array",
                    std::vector<ParameterDecl *>({
                        CreateNode<ParameterDecl>(&ast_context, TU->getCharTy(), CreateNode<IdentDef>(&ast_context, "ty")),
                        CreateNode<ParameterDecl>(&ast_context, TU->getIntegerTy(), CreateNode<IdentDef>(&ast_context, "dimn")),
                        CreateNode<ParameterDecl>(&ast_context, TU->getIntegerTy(), CreateNode<IdentDef>(&ast_context, "..."), true)
                    })
            );

        }

    public:
        explicit Lower(ProjectDB &projectDB) : project_db_(projectDB) {
        }

        int Run() {
            int EC = 0;
            if ((EC = MangleFunctionName            ())) { return EC; }
            if ((EC = CreateStartup                 ())) { return EC; }
            if ((EC = CreateGlobalObjectInitFunction())) { return EC; }
            if ((EC = OverrideStringOperator        ())) { return EC; }
            return 0;
        }

    };

    int AstLowing(ProjectDB &projectDB) {
        Lower lower(projectDB);
        return lower.Run();
    }

}