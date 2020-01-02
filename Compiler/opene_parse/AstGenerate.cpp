//
// Created by Administrator on 2019/12/13.
//

#include <ANTLRFileStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>

#include "AstGenerate.h"
#include "gen/openeLangLexer.h"
#include "gen/openeLangParser.h"

#include "gen/openeLangVisitor.h"

namespace opene {
    struct TranslateUnit {
        unsigned int edition_;
    };
}

namespace opene {
    class ASTBuilder : public openeLangVisitor {
    public:
        antlrcpp::Any visitOpene_src(openeLangParser::Opene_srcContext *context) override {
            TranslateUnit translate_unit{0};
            auto edition_spec_ret = visit(context->edition_spec());
            if (edition_spec_ret.is<unsigned int>()) {
                unsigned int edition_number = edition_spec_ret.as<unsigned int>();
                translate_unit.edition_ = edition_number;
            }
            return translate_unit;
        }
    };
}

namespace opene {
    int AstGenerate::BuildASTFromCode(const std::string &code,
                                      const std::string &filename,
                                      const std::string &toolname) {
        antlr4::ANTLRInputStream __input_stream(code);
        __input_stream.name = filename;
        openeLangLexer __lexer(&__input_stream);
        antlr4::CommonTokenStream __token_stream(&__lexer);
        openeLangParser __parser(&__token_stream);
        antlr4::tree::ParseTree* __tree = __parser.opene_src();

        antlr4::tree::ParseTreeWalker parse_tree_walker;
        ASTBuilder ast_builder;
        parse_tree_walker.walk(&ast_builder, __tree);

        std::cout << __tree->toStringTree(&__parser) << std::endl;

        return 0;
    }

    int AstGenerate::BuildASTFromCodeWithArgs(const std::string &code,
                                              const std::vector<std::string> &args,
                                              const std::string &filename,
                                              const std::string &toolname) {
        return this->BuildASTFromCodeWithArgs(code, {}, filename, toolname);
    }
}