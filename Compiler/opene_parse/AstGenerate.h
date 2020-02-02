//
// Created by Administrator on 2019/12/13.
//

#ifndef OPENELANGUAGE_ASTGENERATE_H
#define OPENELANGUAGE_ASTGENERATE_H

#include <string>
#include <vector>

#include "NodeDecl.h"
#include "Diagnostic.h"
#include "ASTContext.h"

namespace opene {

    class AstGenerate {
    public:
        Diagnostic *diagnostic_ = nullptr;
        ASTContext *ast_context_ = nullptr;

    public:
        AstGenerate();

    public:
        TranslateUnitPtr BuildASTFromCode(const std::string &code, const std::string &filename, const std::string &toolname);

        TranslateUnitPtr BuildASTFromCodeWithArgs(const std::string &code, const std::vector<std::string> &args, const std::string &filename, const std::string &toolname);
    };

}

#endif //OPENELANGUAGE_ASTGENERATE_H
