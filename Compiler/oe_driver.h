//
// Created by Administrator on 2019/12/13.
//

#ifndef OPENELANGUAGE_OE_DRIVER_H
#define OPENELANGUAGE_OE_DRIVER_H

#include <string>
#include <vector>
#include "opene_parse/AstGenerate.h"

namespace opene {

    class SourceManager {};

    class OECompilerInstance {
    private:
        AstGenerate ast_generate_;
        std::string instance_name_;
        std::string parse_code_;

    public:
        int setInstanceName(const std::string &name);

        int setParseCode(const std::string &code);

        SourceManager &getSourceManager();

        int run();
    };

    namespace tooling {
        int BuildASTFromFile(const std::string &filename, const std::string &toolname);

        int BuildASTFromCode(const std::string &code, const std::string &filename, const std::string &toolname);

        int BuildASTFromCodeWithArgs(const std::string &code, const std::vector<std::string> &args, const std::string &filename, const std::string &toolname);
    }

}

#endif //OPENELANGUAGE_OE_DRIVER_H
