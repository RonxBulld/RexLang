//
// Created by rex on 2020/1/2.
//

#ifndef OPENELANGUAGE_DIAGNOSTIC_H
#define OPENELANGUAGE_DIAGNOSTIC_H

#include "BaseErrorListener.h"

namespace opene {
    class Diagnostic : antlr4::BaseErrorListener {
    private:
        void ReportToStdError(const std::vector<std::string> &stack, size_t line, size_t charPositionInLine, const std::string &msg);

    public:
        void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override;
    };
}

#endif //OPENELANGUAGE_DIAGNOSTIC_H
