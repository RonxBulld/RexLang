//
// Created by rex on 2020/12/13.
//

#ifndef REXLANG_ASTBUILDER_H
#define REXLANG_ASTBUILDER_H

#include "../NodeDecl.h"

namespace rexlang {

    class ASTBuilder {
    private:
        ASTContext *ctx_;
    public:
        ASTBuilder(ASTContext *ctx) : ctx_(ctx) {}

        template <typename Ty, typename ... Args>
        Ty *Create(Args && ... args) const {
            return CreateNode<Ty>(ctx_, std::forward<Args>(args)...);
        }

        FunctionCall *CreateFCall(FunctorDecl *callee, NameComponent *prefix, const std::vector<Expression *> &args = {}) const ;
        StatementBlock *CreateStatementBlock(const std::vector<Statement *> &stmts = {}) const ;
        ValueOfString *CreateStringLiteral(const char *cStr) const ;
        ValueOfDecimal *CreateInt(int d) const ;
        IfStmt *CreateIfStmt(Expression *condition, Statement *trueStmt, Statement *falseStmt = nullptr) const ;
        BinaryExpression *CreateEqual(Expression *lhs, Expression *rhs) const ;
        BinaryExpression *CreateNotEqual(Expression *lhs, Expression *rhs) const ;
    };

}

#endif //REXLANG_ASTBUILDER_H
