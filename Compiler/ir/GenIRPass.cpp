//
// Created by rex on 2020/11/8.
//

#include "../support/Pass.h"
#include "../support/ProjectDB.h"

namespace rexlang {
    class GenIRPass : public Pass {
    public:
        GenIRPass() : Pass("EmitIR") {}

        int Call(ProjectDB &projectDB) override {
            Pass::Call("EmitLLIR", projectDB);
            return 0;
        }
    };
}
