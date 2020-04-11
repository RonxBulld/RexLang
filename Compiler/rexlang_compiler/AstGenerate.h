//
// Created by Administrator on 2019/12/13.
//

#ifndef REXLANG_ASTGENERATE_H
#define REXLANG_ASTGENERATE_H

#include <string>
#include <vector>

#include "NodeDecl.h"
#include "utilities/Diagnostic.h"
#include "ASTContext.h"

namespace rexlang {

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

#endif //REXLANG_ASTGENERATE_H
