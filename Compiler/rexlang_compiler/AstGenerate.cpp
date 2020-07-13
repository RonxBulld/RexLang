//
// Created by Administrator on 2019/12/13.
//

#include <ANTLRFileStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>

#include "gen/rexLangLexer.h"
#include "gen/rexLangParser.h"
#include "AstGenerate.h"
#include "sematic_analysis/SematicAnalysis.h"
#include "utilities/Diagnostic.h"

#include "CST2ASTConvert.h"

namespace rexlang {
    TranslateUnit * AstGenerate::BuildASTFromCode(const std::string &code,
                                      const std::string &filename,
                                      const std::string &toolname) {
        return this->BuildASTFromCodeWithArgs(code, {}, filename, toolname);
    }

    TranslateUnit * AstGenerate::BuildASTFromCodeWithArgs(const std::string &code,
                                              const std::vector<std::string> &args,
                                              const std::string &filename,
                                              const std::string &toolname) {

        // 配置解析源。

        antlr4::ANTLRInputStream __input_stream(code);
        __input_stream.name = filename;
        rexLangLexer __lexer(&__input_stream);
        antlr4::CommonTokenStream __token_stream(&__lexer);
        rexLangParser __parser(&__token_stream);

        // 设置自定义诊断监听器。

        __parser.removeErrorListeners();
        __parser.addErrorListener(diagnostic_);

        // 执行语法分析。

        antlr4::tree::ParseTree* __tree = __parser.rexlang_src();
        if (__tree == nullptr) {
            assert(false);
            return nullptr;
        }

        // 遍历树以生成抽象语法树。

        CST2ASTConvert ast_builder(ast_context_, diagnostic_);
        return ast_builder.BuildTranslateUnitFromParseTree(__tree);
    }

    AstGenerate::AstGenerate() {
        diagnostic_ = new Diagnostic();
        ast_context_ = new ASTContext();
    }
}