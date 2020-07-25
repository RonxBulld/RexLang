//
// Created by rex on 2020/7/25.
//

#include "../NodeDecl.h"

namespace rexlang {
    void ProgramSetFile::registResourceTo(TranslateUnit *translateUnit) const {
        if (ProgSetDecl *prog_set_decl = getProgramSetDecl()) {
            translateUnit->addProgSet(prog_set_decl);
            for (FunctorDecl *signature : prog_set_decl->getFuncSignatures()) {
                translateUnit->addFunctor(signature);
            }
            translateUnit->addProgSet(getProgramSetDecl());
        }
        for (const TString &lib : getRefLibs()) {
            translateUnit->addRefLib(lib);
        }
    }

    void DataStructureFile::registResourceTo(TranslateUnit *translateUnit) const {
        for (auto &item : getTypes()) {
            translateUnit->addType(item.second);
        }
    }

    void GlobalVariableFile::registResourceTo(TranslateUnit *translateUnit) const {
        for (auto &item : getGlobalVariMap()) {
            translateUnit->addGlobalVari(item.second);
        }
    }

    void APIDeclareFile::registResourceTo(TranslateUnit *translateUnit) const {
        for (auto &item : getAPIDefMap()) {
            translateUnit->addFunctor(item.second);
        }
    }

}
