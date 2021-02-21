/****************************************************************
 * 对于表达式节点求其左右值特性
 * - 语句参数、函数调用的参数、索引的下标、层次名称的非尾名称是可以自决的
 * - 一元、二元表达式的运算值恒为右值
 * - 资源引用、函数求址恒为右值
 * - 常量值恒为右值
 * - 其它类型需要向上传递
 *
 * Rex
 * 2020/7/12
 ****************************************************************/

#include "NodeDecl.h"

namespace rexlang {

#define L ExprUsage::kAsLeftValue
#define R ExprUsage::kAsRightValue
#define U ExprUsage::kUnknown

    class StmtProtectedInvoker : public Statement {
    public:
        ExprUsage InvokeGetSubExprLRType(const Expression *expr) const {
            return getSubExprAccessType(expr);
        }

    };

    ExprUsage Expression::getLRType() const {
        Node *P = this->getParent();
        if (Statement *STMT = P->as<Statement>()) {
            return ((StmtProtectedInvoker *)STMT)->InvokeGetSubExprLRType(this);
        } else {
            assert(false);
            return U;
        }
    }

    bool    Expression::isLeftUsage   () const { return getLRType() == L; }
    bool    Expression::isRightUsage  () const { return getLRType() == R; }

    /********************************************************
     * 语句参数
     ********************************************************/

    ExprUsage AssignStmt    ::getSubExprAccessType(const Expression *expr) const {
             if (expr == lhs_) { return L; }
        else if (expr == rhs_) { return R; }
        else { assert(false);    return U; }
    }
    ExprUsage ContinueStmt  ::getSubExprAccessType(const Expression *expr) const { assert(false); return U; }
    ExprUsage BreakStmt     ::getSubExprAccessType(const Expression *expr) const { assert(false); return U; }
    ExprUsage ReturnStmt    ::getSubExprAccessType(const Expression *expr) const { return R; } // 由于目前语言不支持返回引用固返回值一定是右值
    ExprUsage IfStmt        ::getSubExprAccessType(const Expression *expr) const { return R; }
    ExprUsage WhileStmt     ::getSubExprAccessType(const Expression *expr) const { return R; }
    ExprUsage RangeForStmt  ::getSubExprAccessType(const Expression *expr) const {
             if (expr == this->range_size_) { return R; }
        else if (expr == this->loop_vari_)  { return L; }
        else { assert(false);                 return U; }
    }
    ExprUsage ForStmt       ::getSubExprAccessType(const Expression *expr) const {
             if (expr == start_value_) { return R; }
        else if (expr == stop_value_)  { return R; }
        else if (expr == step_value_)  { return R; }
        else if (expr == loop_vari_)   { return L; }
        else { assert(false);            return U; }
    }
    ExprUsage DoWhileStmt   ::getSubExprAccessType(const Expression *expr) const {
             if (expr == condition_)  { return R; }
        else { assert(false);           return U; }
    }
    ExprUsage StatementBlock::getSubExprAccessType(const Expression *expr) const {
        assert(false);
        return U;
    }

    /********************************************************
     * 函数调用
     ********************************************************/

    ExprUsage FunctionCall::getSubExprAccessType(const Expression *expr) const {
        // 函数名本身是右值的
        if (expr == name_) { return R; }
        // 如果参数是传值则为右值，如果传址则为左值
        else if (this->isPartOfArgument(expr)) {
            int idx = this->indexOfArgument(expr);
            FunctorDecl *functor_decl = this->getCallee();
            ParameterDecl *parameter = functor_decl->getParameterAt(idx);
            return parameter->shouldBeReference() ? L : R ;
        }
        else {
            assert(false);
            return U;
        }
    }

    /********************************************************
     * 索引
     ********************************************************/

    ExprUsage ArrayIndex::getSubExprAccessType(const Expression *expr) const {
             if (expr == base_)  { return this->getLRType(); }
        else if (expr == index_) { return R; }
        else { assert(false);      return U;}
    }

    /********************************************************
     * 一元、二元表达式
     ********************************************************/

    ExprUsage UnaryExpression::getSubExprAccessType(const Expression *expr) const {
        if (expr == operand_value_) { return R; }
        else { assert(false);         return U; }
    }

    ExprUsage BinaryExpression::getSubExprAccessType(const Expression *expr) const {
             if (expr == lhs_) { return R; }
        else if (expr == rhs_) { return R; }
        else { assert(false);    return U; }
    }

    /********************************************************
     * 常量值
     ********************************************************/

    ExprUsage Value::getSubExprAccessType(const Expression *expr) const {
        return R;
    }

    ExprUsage FuncAddrExpression::getSubExprAccessType(const Expression *expr) const {
        return R;
    }

    /********************************************************
     * 其它类型
     ********************************************************/

    ExprUsage TypeConvert::getSubExprAccessType(const Expression *expr) const {
        return this->getLRType();
    }

    ExprUsage IdentRefer::getSubExprAccessType(const Expression *expr) const {
        return this->getLRType();
    }

#undef L
#undef R
#undef U

}
