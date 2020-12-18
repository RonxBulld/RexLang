//
// Created by rex on 2020/12/13.
//

#include "ASTBuilder.h"

namespace rexlang {

    FunctionCall *ASTBuilder::CreateFCall(FunctorDecl *callee, const std::vector<Expression *> &args) const {
        return Create<FunctionCall>(
                Create<IdentRefer>(callee->getName()),
                callee,
                args
        );
    }

}