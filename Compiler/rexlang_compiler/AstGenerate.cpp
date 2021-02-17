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

    class ParseContext {
    private:
        antlr4::ANTLRInputStream    *IS     = nullptr ;
        antlr4::CommonTokenStream   *CTS    = nullptr ;
        rexLangLexer                *Lexer  = nullptr ;
        rexLangParser               *Parser = nullptr ;
        antlr4::tree::ParseTree     *Tree   = nullptr ;
    public:
        ParseContext(const std::string &code, const std::string &filename, Diagnostic *diagnostic) {
            // 配置解析源

            this->IS       = new antlr4::ANTLRInputStream(code);
            this->IS->name = filename;
            this->Lexer    = new rexLangLexer(IS);
            this->CTS      = new antlr4::CommonTokenStream(Lexer);
            this->Parser   = new rexLangParser(this->CTS);

            // 设置自定义诊断监听器

            this->Parser->removeErrorListeners();
            this->Parser->addErrorListener(diagnostic);

        }

        ~ParseContext() {
            delete IS;     IS     = nullptr;
            delete CTS;    CTS    = nullptr;
            delete Lexer;  Lexer  = nullptr;
            delete Parser; Parser = nullptr;
        }

        antlr4::tree::ParseTree *run() {
            return Tree = this->Parser->rexlang_src();
        }

        antlr4::tree::ParseTree *get() const {
            return Tree;
        }
    };

    antlr4::tree::ParseTree *AstGenerate::buildCstFromCode(const std::string &code,
                                       const std::string &filename,
                                       const std::string &toolname) {
        return this->buildCstFromCodeWithArgs(code, {}, filename, toolname);
    }

    antlr4::tree::ParseTree *AstGenerate::buildCstFromCodeWithArgs(const std::string &code,
                                               const std::vector<std::string> &args,
                                               const std::string &filename,
                                               const std::string &toolname) {

        ParseContext *parse_context = new ParseContext(code, filename, diagnostic_);

        // 执行语法分析，生成语法分析树

        if (antlr4::tree::ParseTree *__tree = parse_context->run()) {
            this->parse_contexts_.push_back(parse_context);
            return __tree;
        } else {
            assert(false);
            return nullptr;
        }

    }

    TranslateUnit * AstGenerate::buildAstFromCsts() {

        // 遍历树以生成抽象语法树

        CST2ASTConvert ast_builder(ast_context_, diagnostic_, compiler_instance_);
        std::vector<antlr4::tree::ParseTree *> parse_trees;
        for (ParseContext *parse_context : parse_contexts_) {
            parse_trees.push_back(parse_context->get());
        }

        return ast_builder.buildTUFromParseTrees(parse_trees);
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
        /*delete ast_context_;*/

        diagnostic_  = nullptr;
        ast_context_ = nullptr;

        for (ParseContext *parse_context : parse_contexts_) {
            delete parse_context;
        }
        parse_contexts_.clear();
    }
}