//
// Created by rex on 2020/3/20.
//

#ifndef REXLANG_LLCODEGEN_H
#define REXLANG_LLCODEGEN_H

#include <string>

namespace rexlang {

    class EmitLLVMIR;

    class LLCodeGen {
    private:
        EmitLLVMIR &emitter_;

    public:
        LLCodeGen(EmitLLVMIR &llvmIREmitter);

    public:
        int WriteOutBitCode(const std::string &bc_filename);

        int WriteOutObject(const std::string &obj_filename);

    };

}

#endif //REXLANG_LLCODEGEN_H
