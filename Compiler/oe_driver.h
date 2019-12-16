//
// Created by Administrator on 2019/12/13.
//

#ifndef OPENELANGUAGE_OE_DRIVER_H
#define OPENELANGUAGE_OE_DRIVER_H

#include <string>
#include <vector>

namespace opene {

    class SourceManager {};

    class OECompilerInstance {
    public:
        int setInstanceName(const std::string &name);

        int setParseCode(const std::string &code);

        SourceManager &getSourceManager();

        int Run();
    };

    namespace tooling {
        int BuildASTFromCode(const std::string &code, const std::string &filename, const std::string &toolname);

        int BuildASTFromCodeWithArgs(const std::string &code, const std::vector<std::string> &args, const std::string &filename, const std::string &toolname);
    }

}

#endif //OPENELANGUAGE_OE_DRIVER_H
