//
// Created by rex on 2020/3/20.
//

#ifndef OPENELANGUAGE_LLCODEGEN_H
#define OPENELANGUAGE_LLCODEGEN_H

#include <string>

namespace opene {

    class EmitLLVMIR;

    class LLCodeGen {
    private:
        EmitLLVMIR &emitter_;

    public:
        LLCodeGen(EmitLLVMIR &llvmIREmitter);

    public:
        int WriteOutBC(const std::string &bc_filename);

        void WriteOutObject(const std::string &bc_filename);

    };

}

#endif //OPENELANGUAGE_LLCODEGEN_H
