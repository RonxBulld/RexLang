//
// Created by Administrator on 2019/12/13.
//

#include "oe_driver.h"

int main(int argc, char *argv[]) {
    std::cout << u8"开始编译..." << std::endl;
    opene::TranslateUnit *translate_unit_ptr = opene::tooling::BuildASTFromFiles({
//        "oe_test/struct_declare.txt",
//        "oe_test/dll_define.txt",
//        "oe_test/global_variable.txt",
        "oe_test/corelib.txt",
        "oe_test/gcd_algorithm.txt",
        }, "demo");
    if (!translate_unit_ptr) {
        std::cout << u8"编译失败..." << std::endl;
        assert(false);
        return 1;
    }
    std::cout << u8"生成代码..." << std::endl;
    opene::EmitLLVMIR emitter(translate_unit_ptr);

    emitter.WriteOutIR();

    opene::LLCodeGen ll_code_gen(emitter);
    ll_code_gen.WriteOutBC("gcd_algorithm.bc");

    std::cout << u8"连接程序..." << std::endl;
    std::vector<opene::StringRef> dependence_libs = translate_unit_ptr->ast_context_->GetDependenceLibraries();

    std::cout << u8"执行程序..." << std::endl;
    return 0;
}
