/*
 * 抽象语法树下降器
 * Rexfield
 * 2020/11/29
 */

#include "LowAST.h"
#include "../../rexlang_compiler/NodeDecl.h"

namespace rexlang {

    class Lower {
    private:
        ProjectDB &project_db_ ;

    private:
        // 创建启动函数
        int CreateStartup() ;

    private:
        // 创建全局对象初始化函数
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