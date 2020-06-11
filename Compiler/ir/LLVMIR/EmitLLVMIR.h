//
// Created by rex on 2020/2/4.
//

#ifndef REXLANG_EMITLLVMIR_H
#define REXLANG_EMITLLVMIR_H

#include "../../rexlang_compiler/NodeDecl.h"

namespace llvm {
    class Module;
}

namespace rexlang {

    class IREmit;
    class LLCodeGen;
    class ProjectDB;

    class EmitLLVMIR {
        friend LLCodeGen;
    public:
        EmitLLVMIR(TranslateUnit *translateUnit, ProjectDB &projectDB);

    public:
        void WriteOutIR();

        llvm::Module *GetModule() const;

    private:
        IREmit *emitter = nullptr;
    };

}

#endif //REXLANG_EMITLLVMIR_H
