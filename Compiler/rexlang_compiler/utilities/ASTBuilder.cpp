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

    StatementBlock *ASTBuilder::CreateStatementBlock(const std::vector<Statement *> &stmts) const {
        return Create<StatementBlock>(stmts);
    }

    ValueOfString *ASTBuilder::CreateStringLiteral(const char *cStr) const {
        return Create<ValueOfString>(TString(StringPool::Create(cStr)));
    }

    ValueOfDecimal *ASTBuilder::CreateInt(int d) const {
        return Create<ValueOfDecimal>(d);
    }

    IfStmt *ASTBuilder::CreateIfStmt(Expression *condition, Statement *trueStmt, Statement *falseStmt) const {
        return Create<IfStmt>(
                std::vector<IfStmt::BranchTy>(
                        {std::pair<Expression *, Statement *>(condition, trueStmt)}
                        ),
                falseStmt
        );
    }

    BinaryExpression *ASTBuilder::CreateEqual(Expression *lhs, Expression *rhs) const {
        return Create<BinaryExpression>(
                OperatorType(OperatorType::Opt::kOptEqual),
                lhs,
                rhs
        );
    }

    BinaryExpression *ASTBuilder::CreateNotEqual(Expression *lhs, Expression *rhs) const {
        return Create<BinaryExpression>(
                OperatorType(OperatorType::Opt::kOptNotEqual),
                lhs,
                rhs
        );
    }
}