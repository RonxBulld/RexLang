//
// Created by rex on 2020/1/2.
//

#ifndef REXLANG_DIAGNOSTIC_H
#define REXLANG_DIAGNOSTIC_H

#include "BaseErrorListener.h"

namespace rexlang {
    class Diagnostic : public antlr4::BaseErrorListener {
    private:
        void ReportToStdError(const std::vector<std::string> &stack, size_t line, size_t charPositionInLine, const std::string &msg);

    public:
        Diagnostic();

    public:
        void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override;

        // 内部错误
        bool InternalError(size_t error_id = 0);

        // 版本号错误
        bool EditionWrong(size_t current_edition);
    };
}

#endif //REXLANG_DIAGNOSTIC_H
