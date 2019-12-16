//
// Created by Administrator on 2019/12/13.
//

#ifndef OPENELANGUAGE_ASTGENERATE_H
#define OPENELANGUAGE_ASTGENERATE_H

#include <string>
#include <vector>

namespace opene {

    class AstGenerate {
    public:
        int BuildASTFromCode(const std::string &code, const std::string &filename, const std::string &toolname);

        int BuildASTFromCodeWithArgs(const std::string &code, const std::vector<std::string> &args, const std::string &filename, const std::string &toolname);
    };

}

#endif //OPENELANGUAGE_ASTGENERATE_H
