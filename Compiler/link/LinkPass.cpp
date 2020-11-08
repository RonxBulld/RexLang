//
// Created by rex on 2020/11/8.
//


#include "../support/Pass.h"
#include "../support/ProjectDB.h"
#include "Linker.h"

namespace rexlang {
    class GenIRPass : public Pass {
    public:
        GenIRPass() : Pass("Link") {}

        int Call(ProjectDB &projectDB) override {
            Linker linker;
            return linker.LinkProject(projectDB);
        }
    };
}
