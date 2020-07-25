//
// Created by rex on 2020/7/26.
//

#include "SemaCFG.h"
#include "../NodeDecl.h"

namespace rexlang {
    namespace cfg {

        bool CheckFullReturn(Statement *stmt, bool need_return) {
            /*
             * def check_full_ret(stmts,need_return):
             *     for each stmt in stmts:
             *         if stmt is ASSIGN then continue.
             *         if stmt is EXPRESSION then continue.
             *         if stmt is LOOP then continue.
             *         if stmt is RETURN then return true.
             *         if stmt is EXIT then return true.
             *         if stmt is BRANCHES then:
             *             ok = true.
             *             for each branch in BRANCHES:
             *                 ok &= check_full_ret(branch.stmts).
             *             ok &= (BRANCHES has default) && check_full_ret(default).
             *             if ok == true then return true.
             *     return !need_return.
             */
            std::vector<Statement*> stmts;
            if (StatementBlock *statement_block = stmt->as<StatementBlock>()) {
                stmts = statement_block->getStatements();
            } else {
                stmts = { stmt };
            }
            for (Statement *stmt : stmts) {
                if (stmt->is<AssignStmt>())         { continue; }
                else if (stmt->is<Expression>())    { continue; }
                else if (stmt->is<LoopStatement>()) { continue; }
                else if (stmt->is<ReturnStmt>())    { return true; }
                else if (stmt->is<ExitStmt>())      { return true; }
                else if (IfStmt *if_stmt = stmt->as<IfStmt>()) {
                    bool ok = true;
                    for (size_t idx = 0, count = if_stmt->branchesCount(); idx < count; idx++) {
                        Statement *branch_body = if_stmt->branchBodyAt(idx);
                        ok &= CheckFullReturn(branch_body, need_return);
                    }
                    ok &= (if_stmt->defaultBody() != nullptr) && (CheckFullReturn(if_stmt->defaultBody(), need_return));
                    if (ok) { return true; }
                }
                return !need_return;
            }
            return !need_return;
        }

        bool CheckAllBranchesReturnCorrectly(FunctionDecl *functionDecl) {
            StatementBlock *func_body = functionDecl->getFunctionBody();

            TypeDecl *return_type = functionDecl->getReturnType();
            assert(return_type);

            VariTypeDecl *actual_return_ty = return_type->as<VariTypeDecl>();
            assert(actual_return_ty);

            if (!CheckFullReturn(func_body, !actual_return_ty->isVoidType())) {
                assert(false);
                return false;
            } else {
                return true;
            }
        }

    }
}