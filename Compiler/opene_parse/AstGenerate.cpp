//
// Created by Administrator on 2019/12/13.
//

#include <ANTLRFileStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>

#include "gen/openeLangLexer.h"
#include "gen/openeLangParser.h"
#include "AstGenerate.h"
#include "SematicAnalysis.h"
#include "Diagnostic.h"

#include "ASTBuilder.h"

namespace opene {
    int AstGenerate::BuildASTFromCode(const std::string &code,
                                      const std::string &filename,
                                      const std::string &toolname) {
        // 配置解析源。
        antlr4::ANTLRInputStream __input_stream(code);
        __input_stream.name = filename;
        openeLangLexer __lexer(&__input_stream);
        antlr4::CommonTokenStream __token_stream(&__lexer);
        openeLangParser __parser(&__token_stream);
        // 设置自定义诊断监听器。
        __parser.removeErrorListeners();
        Diagnostic *diagnostic = new Diagnostic();
        __parser.addErrorListener(diagnostic);
        // 执行语法分析。
        antlr4::tree::ParseTree* __tree = __parser.opene_src();
        if (__tree == nullptr) {
            assert(false);
            return 1;
        }
        // 遍历树以生成抽象语法树。
        ASTBuilder ast_builder(diagnostic);
        antlrcpp::Any build_result = ast_builder.visit(__tree);
        TranslateUnitPtr translate_unit = nullptr;
        if (build_result.is<NodeWarp>()) {
            if ((translate_unit = build_result.as<NodeWarp>())) {
            } else {
                assert(false);
                return 1;
            }
        } else {
            assert(false);
            return 1;
        }
        // 执行语义分析，构建符号表，绑定定义引用。
        SematicAnalysis sematic_analysis;
        sematic_analysis.Run(translate_unit);

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