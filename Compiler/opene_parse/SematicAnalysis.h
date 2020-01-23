//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_SEMATICANALYSIS_H
#define OPENELANGUAGE_SEMATICANALYSIS_H

#include "TypeDescription.h"
#include "ErrOr.h"

namespace opene {

    struct TranslateUnit;
    struct ProgramSetFile;
    struct GlobalVariableFile;
    struct DllDefineFile;
    struct StructureDecl;
    struct VariableDecl;
    struct SourceFile;

    class SematicAnalysis {
    private:
        TranslateUnit * translate_unit_;

    private:

    public:
        bool Run(TranslateUnit * translateUnitPtr);
    };

}

#endif //OPENELANGUAGE_SEMATICANALYSIS_H
