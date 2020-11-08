//
// Created by rex on 2020/11/8.
//

#include "../support/Pass.h"
#include "../support/ProjectDB.h"
#include "LLVMIR/EmitLLVMIR.h"

namespace rexlang {
    class GenIRPass : public Pass {
    public:
        GenIRPass() : Pass("GenIR") {}

        int Call(ProjectDB &projectDB) override {
            rexlang::EmitLLVMIR emitter(projectDB.getTranslateUnit(), projectDB);
//        emitter.WriteOutIR();
            rexlang::LLCodeGen ll_code_gen(emitter);
//        if (int EC = ll_code_gen.WriteOutBitCode(projectDB.GetBitCodeFilename())) { return EC; }
            if (int EC = ll_code_gen.WriteOutObject (projectDB.GetObjectFilename()))  { return EC; }
            return 0;
        }
    };
}
