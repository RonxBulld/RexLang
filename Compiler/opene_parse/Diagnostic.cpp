//
// Created by rex on 2020/1/2.
//

#include <algorithm>

#include "Diagnostic.h"
#include "gen/openeLangParser.h"

namespace opene {

    using antlr4::Recognizer;
    using antlr4::Token;

    Diagnostic::Diagnostic() : antlr4::BaseErrorListener() {
    }

    void Diagnostic::syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) {
//        std::vector<std::string> stack = dynamic_cast<openeLangParser*>(recognizer)->getRuleInvocationStack();
//        std::reverse(stack.begin(), stack.end());
        std::cerr << "[" << line << ":" << charPositionInLine << "]:" << msg << std::endl;
        antlr4::CommonTokenStream *tokens = dynamic_cast<antlr4::CommonTokenStream*>(recognizer->getInputStream());
        std::string input = tokens->getTokenSource()->getInputStream()->toString();
        size_t beg_pos = 0;
        while(line > 1) {
            beg_pos = input.find('\n', beg_pos);
            line--;
        }
        size_t end_pos = beg_pos;
        for (; end_pos < input.length(); end_pos++) {
            if (input[end_pos] == '\n') {
                break;
            }
        }
        end_pos--;
        std::string code_line = input.substr(beg_pos, end_pos - beg_pos);
        std::cerr << code_line << std::endl;
        for (int i = 0; i < charPositionInLine; i++) {
            std::cerr << " ";
        }
        int mark_start = offendingSymbol->getStartIndex();
        int mark_end = offendingSymbol->getStopIndex();
        if (mark_start >= 0 && mark_end >= 0) {
            for (int i = mark_start; i <= mark_end; i++) {
                std::cerr << "^";
            }
        }
        std::cerr << std::endl;
    }

}
