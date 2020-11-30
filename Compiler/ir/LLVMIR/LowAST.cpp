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
        int CreateGlobalObjectInitFunction() ;  // 创建全局对象初始化函数

    public:
        explicit Lower(ProjectDB &projectDB) : project_db_(projectDB) {
        }

    };

    int AstLowing(ProjectDB &projectDB) {
        Lower lower(projectDB);

        return 0;
    }

}