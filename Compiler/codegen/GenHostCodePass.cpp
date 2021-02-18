/*
 * 生成宿主机代码
 * 由于从IR生成宿主代码是与IR强相关的，所以 HOST CODE 生成器由IR生成PASS指定，本PASS仅调用。
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
    } gen_host_code_pass ;
}
