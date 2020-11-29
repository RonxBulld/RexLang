//
// Created by rex on 2020/11/29.
//

#include <memory>
#include "../../support/Pass.h"
#include "../../support/ProjectDB.h"
#include "EmitLLVMIR.h"
#include "LLCodeGen.h"

namespace rexlang {

    class GenCodeWithLLIR : public ProjectDB::CodeGeneratorInterface {
    private:
        std::shared_ptr<EmitLLVMIR> emitter_;
    public:
        int GenerateCode(const std::string &host, ProjectDB &projectDB) override {
            LLCodeGen ll_code_gen(*emitter_);
//            if (int EC = ll_code_gen.WriteOutBitCode(projectDB.GetBitCodeFilename())) { return EC; }
            if (int EC = ll_code_gen.WriteOutObject (projectDB.GetObjectFilename()))  { return EC; }
            return 0;
        }

        void UpdateEmitter(std::shared_ptr<EmitLLVMIR> emitter) {
            emitter_ = emitter;
        }

        ~GenCodeWithLLIR() override = default;

    } gen_code_with_llir;

    class GenLLIRPass : public Pass {
    public:
        GenLLIRPass() : Pass("EmitLLIR") {}

        int Call(ProjectDB &projectDB) override {

            // 生成LLVMIR
            std::shared_ptr<EmitLLVMIR> emitter(new EmitLLVMIR(projectDB.getTranslateUnit(), projectDB));
//            emitter.WriteOutIR();

            // 指定代码生成方式
            gen_code_with_llir.UpdateEmitter(emitter);
            projectDB.SetCodeGenerator(&gen_code_with_llir);

            return 0;
        }
    };
}
