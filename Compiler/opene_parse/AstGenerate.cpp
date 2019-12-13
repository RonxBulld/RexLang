//
// Created by Administrator on 2019/12/13.
//

#include <ANTLRFileStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>

#include "AstGenerate.h"
#include "openeLexer.h"
#include "openeParser.h"

namespace opene {
    int AstGenerate::BuildASTFromCode(const std::string &code,
                                      const std::string &filename,
                                      const std::string &toolname) {
        antlr4::ANTLRInputStream __input_stream(code);
        __input_stream.name = filename;
        openeLexer __lexer(&__input_stream);
        antlr4::CommonTokenStream __token_stream(&__lexer);
        openeParser __parser(&__token_stream);
        antlr4::tree::ParseTree* __tree = __parser.opene_src();

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