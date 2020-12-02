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

    private:
        // 创建启动和初始化函数
        int CreateStartup() {
            ASTContext &ast_context = project_db_.GetASTContext();
            TranslateUnit *TU = ast_context.getTranslateUnit();

            // 创建启动函数
            IdentDef *RexStartupFnName = CreateNode<IdentDef>(&ast_context, "RexStartup");
            assert(RexStartupFnName);
            std::vector<ParameterDecl *> args;
            FunctionDecl *startup_fn = CreateNode<FunctionDecl>(&ast_context, TU->getIntegerTy(), RexStartupFnName, args);
            StatementBlock *startup_sb = CreateNode<StatementBlock>(&ast_context, std::vector<Statement *>());

            // 创建初始化函数
            IdentDef *InitFnName = CreateNode<IdentDef>(&ast_context, "RexInit");
            assert(InitFnName);
            FunctionDecl *init_fn = CreateNode<FunctionDecl>(&ast_context, TU->getVoidTy(), InitFnName, args);
            StatementBlock *init_sb = CreateNode<StatementBlock>(&ast_context, std::vector<Statement *>());

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