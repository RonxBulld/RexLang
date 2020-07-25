//
// Created by rex on 2020/7/26.
//

#ifndef REXLANG_SEMACFG_H
#define REXLANG_SEMACFG_H

namespace rexlang {

    class Statement;
    class FunctionDecl;

    namespace cfg {

        bool CheckFullReturn(Statement *stmt, bool need_return);
        bool CheckAllBranchesReturnCorrectly(FunctionDecl *functionDecl);

    }
}

#endif //REXLANG_SEMACFG_H
