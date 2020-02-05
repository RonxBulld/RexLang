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
    TranslateUnitPtr AstGenerate::BuildASTFromCode(const std::string &code,
                                      const std::string &filename,
                                      const std::string &toolname) {
        return this->BuildASTFromCodeWithArgs(code, {}, filename, toolname);
    }

    TranslateUnitPtr AstGenerate::BuildASTFromCodeWithArgs(const std::string &code,
                                              const std::vector<std::string> &args,
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
        __parser.addErrorListener(diagnostic_);

        // 执行语法分析。

        antlr4::tree::ParseTree* __tree = __parser.opene_src();
        if (__tree == nullptr) {
            assert(false);
            return nullptr;
        }

        // 遍历树以生成抽象语法树。

        ASTBuilder ast_builder(ast_context_, diagnostic_);
        antlrcpp::Any build_result = ast_builder.visit(__tree);
        TranslateUnitPtr translate_unit = nullptr;
        if (build_result.is<NodeWarp>()) {
            if ((translate_unit = build_result.as<NodeWarp>())) {
            } else {
                assert(false);
                return nullptr;
            }
        } else {
            assert(false);
            return nullptr;
        }

        // 执行语义分析，构建符号表，绑定定义引用。

//        SematicAnalysis sematic_analysis;
//        bool sematic_success = sematic_analysis.Run(translate_unit);

        return translate_unit;
    }

    AstGenerate::AstGenerate() {
        diagnostic_ = new Diagnostic();
        ast_context_ = new ASTContext();
    }
}