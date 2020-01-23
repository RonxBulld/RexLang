//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_SEMATICANALYSIS_H
#define OPENELANGUAGE_SEMATICANALYSIS_H

namespace opene {

    class SematicAnalysis {
    private:
        bool SATranslateUnit(struct TranslateUnit * node);

        bool SAProgramSetFile(struct ProgramSetFile * node);
        bool SAGlobalVariableFile(struct GlobalVariableFile * node);
        bool SADataStructureFile(struct DataStructureFile * node);
        bool SADllDefineFile(struct DllDefineFile * node);

        int SAStructureDecl(struct StructureDecl * node);
    public:
        bool Run(struct TranslateUnit * translateUnitPtr);
    };

}

#endif //OPENELANGUAGE_SEMATICANALYSIS_H
