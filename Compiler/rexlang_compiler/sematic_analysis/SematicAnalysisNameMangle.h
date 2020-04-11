//
// Created by rex on 2020/4/2.
//

#ifndef REXLANG_SEMATICANALYSISNAMEMANGLE_H
#define REXLANG_SEMATICANALYSISNAMEMANGLE_H

namespace rexlang {

    struct APICommandDecl;

    class SematicAnalysisNameMangle {
    private:
        SematicAnalysisNameMangle() = delete;
        ~SematicAnalysisNameMangle() = delete;
    public:
        static bool IsRequireArgumentPack(const APICommandDecl *apiCommandDecl);
        static bool RemoveArgumentPackRequire(APICommandDecl *apiCommandDecl);
    };

}

#endif //REXLANG_SEMATICANALYSISNAMEMANGLE_H
