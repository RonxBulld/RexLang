//
// Created by rex on 2020/7/12.
//

#include "NodeDecl.h"

namespace rexlang {

    /****************************************************************
     * 对于表达式节点求其左右值特性
     * - 语句参数、函数调用的参数、索引的下标、层次名称的非尾名称是可以自决的
     * - 一元、二元表达式的运算值恒为右值
     * - 资源引用、函数求址恒为右值
     * - 常量值恒为右值
     * - 其它类型需要向上传递
     ****************************************************************/

#define L ExprUsage::kAsLeftValue
#define R ExprUsage::kAsRightValue
#define U ExprUsage::kUnknown

    ExprUsage Expression::GetLRType() const {
        Node *P = this->parent_node_;
        if (Statement *STMT = P->as<Statement>()) {
            return STMT->GetSubExprLRType(this);
        } else {
            assert(false);
            return U;
        }
    }

    /********************************************************
     * 语句参数
     ********************************************************/

    ExprUsage AssignStmt    ::GetSubExprLRType(const Expression *expr) const {
             if (expr == lhs_) { return L; }
        else if (expr == rhs_) { return R; }
        else { assert(false);    return U; }
    }
    ExprUsage ContinueStmt  ::GetSubExprLRType(const Expression *expr) const {
        assert(false);
        return U;
    }
    ExprUsage BreakStmt     ::GetSubExprLRType(const Expression *expr) const {
        assert(false);
        return U;
    }
    ExprUsage ReturnStmt    ::GetSubExprLRType(const Expression *expr) const {
        // 由于目前语言不支持返回引用固返回值一定是右值
        return R;
    }
    ExprUsage ExitStmt      ::GetSubExprLRType(const Expression *expr) const {
        assert(false);
        return U;
    }
    ExprUsage IfStmt        ::GetSubExprLRType(const Expression *expr) const {
        return R;
    }
    ExprUsage WhileStmt     ::GetSubExprLRType(const Expression *expr) const {
        return R;
    }
    ExprUsage RangeForStmt  ::GetSubExprLRType(const Expression *expr) const {
             if (expr == this->range_size_) { return R; }
        else if (expr == this->loop_vari_)  { return L; }
        else { assert(false);                 return U; }
    }
    ExprUsage ForStmt       ::GetSubExprLRType(const Expression *expr) const {
             if (expr == start_value_) { return R; }
        else if (expr == stop_value_)  { return R; }
        else if (expr == step_value_)  { return R; }
        else if (expr == loop_vari_)   { return L; }
        else { assert(false);            return U; }
    }
    ExprUsage DoWhileStmt   ::GetSubExprLRType(const Expression *expr) const {
             if (expr == conditon_)   { return R; }
        else { assert(false);           return U; }
    }
    ExprUsage StatementBlock::GetSubExprLRType(const Expression *expr) const {
        assert(false);
        return U;
    }

    /********************************************************
     * 函数调用
     ********************************************************/

    ExprUsage FunctionCall::GetSubExprLRType(const Expression *expr) const {
        // 函数名本身是右值的
        if (expr == function_name_) { return R; }
        // 如果参数是传值则为右值，如果传址则为左值
        else if (this->IsArgument(expr)) {
            int idx = this->IndexOfArgument(expr);
            FunctorDecl *functor_decl = this->GetFunctionDeclare();
            ParameterDecl *parameter = functor_decl->GetParameterAt(idx);
            return parameter->ShouldBeReference() ? L : R ;
        }
        else {
            assert(false);
            return U;
        }
    }

    /********************************************************
     * 索引
     ********************************************************/

    ExprUsage ArrayIndex::GetSubExprLRType(const Expression *expr) const {
             if (expr == base_)  { return this->GetLRType(); }
        else if (expr == index_) { return R; }
        else { assert(false);      return U;}
    }

    /********************************************************
     * 层次名称
     ********************************************************/

    ExprUsage HierarchyIdentifier::GetSubExprLRType(const Expression *expr) const {
        auto &NCS = this->name_components_;
        assert(!NCS.empty());
             if (expr == NCS.back())                                   { return this->GetLRType(); }
        else if (std::find(NCS.begin(), NCS.end(), expr) != NCS.end()) { return R; }
        else { assert(false);                                            return U; }
    }

    /********************************************************
     * 一元、二元表达式
     ********************************************************/

    ExprUsage UnaryExpression::GetSubExprLRType(const Expression *expr) const {
        if (expr == operand_value_) { return R; }
        else { assert(false);              return U; }
    }

    ExprUsage BinaryExpression::GetSubExprLRType(const Expression *expr) const {
             if (expr == lhs_) { return R; }
        else if (expr == rhs_) { return R; }
        else { assert(false);    return U; }
    }

    ExprUsage Value::GetSubExprLRType(const Expression *expr) const {
        assert(false);
        return U;
    }

#undef L
#undef R
#undef U

}
