/*
 * 抽象语法树下降器
 * Rexfield
 * 2020/11/29
 */

#include "LowAST.h"
#include "../../rexlang_compiler/NodeDecl.h"
#include "../../support/ProjectDB.h"

namespace rexlang {

    class Lower {
    private:
        ProjectDB &project_db_ ;
        StatementBlock *startup_stmtblk_ = nullptr ;    // 启动函数语句块
        StatementBlock *init_stmtblk_    = nullptr ;    // 初始化函数语句块

    private:
        // 创建启动和初始化函数
        int CreateStartup() {
            ASTContext &ast_context = project_db_.GetASTContext();
            TranslateUnit *TU = ast_context.getTranslateUnit();

            // 创建启动函数
            IdentDef *rex_startup_fn_name = CreateNode<IdentDef>(&ast_context, "RexStartup");
            assert(rex_startup_fn_name);
            std::vector<ParameterDecl *> args;
            FunctionDecl *startup_fn = CreateNode<FunctionDecl>(&ast_context, TU->getIntegerTy(), rex_startup_fn_name, args);
            startup_stmtblk_ = CreateNode<StatementBlock>(&ast_context, std::vector<Statement *>());

            // 创建初始化函数
            IdentDef *init_fn_name = CreateNode<IdentDef>(&ast_context, "RexInit");
            assert(init_fn_name);
            FunctionDecl *init_fn = CreateNode<FunctionDecl>(&ast_context, TU->getVoidTy(), init_fn_name, args);
            init_stmtblk_ = CreateNode<StatementBlock>(&ast_context, std::vector<Statement *>());

            // 在启动函数中调用初始化函数
            FunctionCall *call_init_fn = CreateNode<FunctionCall>(
                    &ast_context,
                    CreateNode<IdentRefer>(&ast_context, init_fn_name),
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

    private:
        // 创建全局对象初始化
        int CreateGlobalObjectInitFunction() ;

        // 初始化全局数组
        int InitializeGlobalArray() ;

        // 初始化局部数组
        int InitializeLocalArray() ;

        // 初始化全局字符串/字节集
        int InitializeGlobalString() ;

        // 初始化局部字符串/字节集
        int InitializeLocalString() ;

    private:
        // 重命名函数名
        int MangleFunctionName() ;

        // 重写字符串/字节集操作符
        int OverrideStringOperator() ;

    public:
        explicit Lower(ProjectDB &projectDB) : project_db_(projectDB) {
        }

        int Run() {
            int EC = 0;
            if ((EC = CreateStartup())) { return EC; }
            if ((EC = CreateGlobalObjectInitFunction())) { return EC; }
            if ((EC = MangleFunctionName())) { return EC; }
            if ((EC = OverrideStringOperator())) { return EC; }
            return 0;
        }

    };

    int AstLowing(ProjectDB &projectDB) {
        Lower lower(projectDB);
        return lower.Run();
    }

}