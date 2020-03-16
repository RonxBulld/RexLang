//
// Created by rex on 2020/2/4.
//

#ifndef OPENELANGUAGE_EMITLLVMIR_H
#define OPENELANGUAGE_EMITLLVMIR_H

#include "../opene_compiler/NodeDecl.h"

namespace opene {

    class IREmit;

    class EmitLLVMIR {
    public:
        EmitLLVMIR(TranslateUnit *translateUnit);

    public:
        void WriteOutIR();

    private:
        IREmit *emitter = nullptr;
    };

}

#endif //OPENELANGUAGE_EMITLLVMIR_H
