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

    class REXCompilerInstance;

    class AstGenerate {
    private:
        Diagnostic *diagnostic_  = nullptr;
        ASTContext *ast_context_ = nullptr;
        REXCompilerInstance *compiler_instance_ = nullptr;

        std::vector<antlr4::tree::ParseTree *> parse_trees_;

    public:
        explicit AstGenerate(REXCompilerInstance *compiler_instance);
        ~AstGenerate();

    public:
        void setCurrentTranslateUnit(TranslateUnit *translateUnit) ;
        void setDiagnosticRoutine   (Diagnostic *   diagnostic) ;

    public:
        /*===---------------------------------------===*
         * 从代码文本中创建CST
         */
        antlr4::tree::ParseTree *buildCstFromCode        (const std::string &code, const std::string &filename, const std::string &toolname);
        antlr4::tree::ParseTree *buildCstFromCodeWithArgs(const std::string &code, const std::vector<std::string> &args, const std::string &filename, const std::string &toolname);

        /*===---------------------------------------===*
         * 从保存的CST列表中构建AST并清空保存的CST
         */
        TranslateUnit *buildAstFromCsts() ;

        /*===---------------------------------------===*
         * 从代码文本中创建AST
         */
        TranslateUnit *buildAstFromCode        (const std::string &code, const std::string &filename, const std::string &toolname);
        TranslateUnit *buildAstFromCodeWithArgs(const std::string &code, const std::vector<std::string> &args, const std::string &filename, const std::string &toolname);
    };

}

#endif //REXLANG_ASTGENERATE_H
