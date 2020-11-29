/*
 * 生成宿主机代码
 * Rexfield
 * 2020/11/29
 */

#include <assert.h>
#include <iostream>
#include "../support/Pass.h"
#include "../support/ProjectDB.h"

namespace rexlang {
    class GenHostCodePass : public Pass {
    public:
        GenHostCodePass() : Pass("GenHostCode") {}

        int Call(ProjectDB &projectDB) override {
            ProjectDB::CodeGeneratorInterface *code_generator = projectDB.GetCodeGenerator();
            if (code_generator) {
                return code_generator->GenerateCode("host", projectDB);
            } else {
                std::cerr << u8"不知道如何生成Host代码。" << std::endl;
                assert(false);
                return 3;
            }
        }
    };
}
