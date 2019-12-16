//
// Created by Administrator on 2019/12/13.
//

#include "oe_driver.h"

namespace opene {
    int tooling::BuildASTFromCode(const std::string &code, const std::string &filename, const std::string &toolname) {
        return tooling::BuildASTFromCodeWithArgs(code, {}, filename, toolname);
    }

    int tooling::BuildASTFromCodeWithArgs(const std::string &code, const std::vector<std::string> &args, const std::string &filename, const std::string &toolname) {
        OECompilerInstance compilerInstance;
        compilerInstance.setInstanceName(toolname);
        compilerInstance.setParseCode(code);
        compilerInstance.Run();
        return 0;
    }
}