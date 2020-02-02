//
// Created by Administrator on 2019/12/13.
//

#include "oe_driver.h"

int main(int argc, char *argv[]) {
    opene::tooling::BuildASTFromFiles({
        "oe_test/struct_declare.txt",
        "oe_test/dll_define.txt",
        "oe_test/global_variable.txt",
        "oe_test/gcd_algorithm.txt",
        }, "demo");
    return 0;
}
