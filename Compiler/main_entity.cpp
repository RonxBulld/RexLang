//
// Created by Administrator on 2019/12/13.
//

#include "oe_driver.h"

int main(int argc, char *argv[]) {
    opene::tooling::BuildASTFromFile("oe_test/struct_declare.txt", "demo");
    return 0;
}
