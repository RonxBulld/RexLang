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
    bool AstGenerate::buildCstFromCode(const std::string &code,
                                       const std::string &filename,
                                       const std::string &toolname) {
        return this->buildCstFromCodeWithArgs(code, {}, filename, toolname);
    }

    bool AstGenerate::buildCstFromCodeWithArgs(const std::string &code,
                                               const std::vector<std::string> &args,
                                               const std::string &filename,
                                               const std::string &toolname) {

        // 配置解析源

        antlr4::ANTLRInputStream __input_stream(code);
        __input_stream.name = filename;

        rexLangLexer __lexer(&__input_stream);
        antlr4::CommonTokenStream __token_stream(&__lexer);

        rexLangParser __parser(&__token_stream);

        // 设置自定义诊断监听器

        __parser.removeErrorListeners();
        __parser.addErrorListener(diagnostic_);

        // 执行语法分析，生成语法分析树

        if (antlr4::tree::ParseTree* __tree = __parser.rexlang_src()) {
            this->parse_trees_.push_back(__tree);
            return true;
        } else {
            assert(false);
            return false;
        }

    }

    TranslateUnit * AstGenerate::buildAstFromCsts() {

        // 遍历树以生成抽象语法树

        CST2ASTConvert ast_builder(ast_context_, diagnostic_);
        return ast_builder.buildTUFromParseTrees(this->parse_trees_);
    }

    TranslateUnit *AstGenerate::buildAstFromCode(const std::string &code, const std::string &filename, const std::string &toolname) {
        buildCstFromCode(code, filename, toolname);
        return buildAstFromCsts();
    }

    TranslateUnit *AstGenerate::buildAstFromCodeWithArgs(const std::string &code, const std::vector<std::string> &args, const std::string &filename, const std::string &toolname) {
        buildCstFromCodeWithArgs(code, args, filename, toolname);
        return buildAstFromCsts();
    }

    AstGenerate::AstGenerate(REXCompilerInstance *compiler_instance)
        : compiler_instance_(compiler_instance) {
        diagnostic_  = new Diagnostic();
        ast_context_ = new ASTContext();
    }

    AstGenerate::~AstGenerate() {

        delete diagnostic_;
        delete ast_context_;

        diagnostic_  = nullptr;
        ast_context_ = nullptr;

    }
}