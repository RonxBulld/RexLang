//
// Created by Administrator on 2019/12/13.
//

#include <fstream>
#include "oe_driver.h"

namespace opene {
    int tooling::BuildASTFromFile(const std::string &filename, const std::string &toolname){
        std::ifstream ifs;
        ifs.open(filename);
        if (ifs.is_open() == false) {
            return 1;
        }
        std::string codes((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        return tooling::BuildASTFromCode(codes, filename, toolname);
    }

    int tooling::BuildASTFromCode(const std::string &code, const std::string &filename, const std::string &toolname) {
        return tooling::BuildASTFromCodeWithArgs(code, {}, filename, toolname);
    }

    int tooling::BuildASTFromCodeWithArgs(const std::string &code, const std::vector<std::string> &args, const std::string &filename, const std::string &toolname) {
        OECompilerInstance compilerInstance;
        compilerInstance.setInstanceName(toolname);
        compilerInstance.setParseCode(code);
        compilerInstance.run();
        return 0;
    }

    int OECompilerInstance::setInstanceName(const std::string &name) {
        this->instance_name_ = name;
        return 0;
    }

    int OECompilerInstance::setParseCode(const std::string &code) {
        this->parse_code_ = code;
        return 0;
    }

    int OECompilerInstance::run() {
        this->ast_generate_.BuildASTFromCode(this->parse_code_, "", this->instance_name_);
        return 0;
    }
}