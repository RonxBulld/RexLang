//
// Created by rex on 2020/4/2.
//

#ifndef OPENELANGUAGE_SEMATICANALYSISNAMEMANGLE_H
#define OPENELANGUAGE_SEMATICANALYSISNAMEMANGLE_H

namespace opene {

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

#endif //OPENELANGUAGE_SEMATICANALYSISNAMEMANGLE_H
