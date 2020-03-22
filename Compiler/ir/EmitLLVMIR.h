//
// Created by rex on 2020/2/4.
//

#ifndef OPENELANGUAGE_EMITLLVMIR_H
#define OPENELANGUAGE_EMITLLVMIR_H

#include "../opene_compiler/NodeDecl.h"

namespace llvm {
    class Module;
}

namespace opene {

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

#endif //OPENELANGUAGE_EMITLLVMIR_H
