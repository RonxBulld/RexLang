//
// 本文件用于实现节点的子节点替换功能
// 1. 支持表达式节点
// 2. 支持语句节点
// Created by rex on 2021/1/26.
//

#include <type_traits>
#include "NodeDecl.h"
#include "rtti.h"

namespace rexlang {
    template <typename ObjectNodeTy, typename SetterTy, typename PlaceNodeTy>
    void doReplace(ObjectNodeTy *object, SetterTy && setter, PlaceNodeTy *goal) {
        std::invoke(setter, *object, goal);
    }

    template <typename ObjectNodeTy, typename PlaceNodeTy, typename SetterTy>
    bool tryReplace(Node *origin, Node *goal, PlaceNodeTy *place, ObjectNodeTy *object, SetterTy && setter) {
        if (origin == place) {
            if (PlaceNodeTy *_goal = rtti::dyn_cast<PlaceNodeTy>(goal)) {
                doReplace(object, setter, _goal);
                return true;
            } else {
                assert(false);
                return false;
            }
        } else {
            return false;
        }
    }


#define TRY_REPLACE(PLACE,SETTER) do { if (tryReplace(origin, goal, PLACE, this, SETTER)) { return true; } } while(0)

    bool Statement::replaceChild(Node *origin, Node *goal) {
        return false;
    }
    bool AssignStmt::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getLHS(), &AssignStmt::setLHS);
        TRY_REPLACE(getRHS(), &AssignStmt::setRHS);
        return Statement::replaceChild(origin, goal);
    }
    bool ControlStmt::replaceChild(Node *origin, Node *goal) {
        return Statement::replaceChild(origin, goal);
    }
    bool LoopControlStmt::replaceChild(Node *origin, Node *goal) {
        return ControlStmt::replaceChild(origin, goal);
    }
    bool ContinueStmt::replaceChild(Node *origin, Node *goal) {
        return LoopControlStmt::replaceChild(origin, goal);
    }
    bool BreakStmt::replaceChild(Node *origin, Node *goal) {
        return LoopControlStmt::replaceChild(origin, goal);
    }
    bool ReturnStmt::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getReturnValue(), &ReturnStmt::setReturnValue);
        return ControlStmt::replaceChild(origin, goal);
    }
    bool ExitStmt::replaceChild(Node *origin, Node *goal) {
        return ControlStmt::replaceChild(origin, goal);
    }
    void IfStmt::replaceConditionAt(size_t idx, Expression *condition) {
        if (idx < switches_.size()) {
            switches_[idx].first = condition;
            setChild(condition);
        } else {
            assert(false);
        }
    }
    void IfStmt::replaceBranchBodyAt(size_t idx, Statement *statement) {
        if (idx < switches_.size()) {
            switches_[idx].second = statement;
            setChild(statement);
        } else {
            assert(false);
        }
    }
    bool IfStmt::replaceChild(Node *origin, Node *goal) {
        size_t idx = 0, count = switches_.size();
        auto CondReplPred = [this, &idx](IfStmt &, Expression *goal) { this->replaceConditionAt(idx, goal); };
        auto BodyReplPred = [this, &idx](IfStmt &, Statement *goal) { this->replaceBranchBodyAt(idx, goal); };
        for (; idx < count; ++idx) {
            TRY_REPLACE(conditionAt(idx), CondReplPred);
            TRY_REPLACE(branchBodyAt(idx), BodyReplPred);
        }
        TRY_REPLACE(defaultBody(), &IfStmt::setDefault);
        return Statement::replaceChild(origin, goal);
    }
    bool LoopStatement::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getLoopBody(), &LoopStatement::setLoopBody);
        return Statement::replaceChild(origin, goal);
    }
    bool WhileStmt::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getLoopCondition(), &WhileStmt::setLoopCondition);
        return LoopStatement::replaceChild(origin, goal);
    }
    bool RangeForStmt::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getRangeSize(), &RangeForStmt::setRangeSize);
        TRY_REPLACE(getLoopVari(), &RangeForStmt::setLoopVariable);
        return LoopStatement::replaceChild(origin, goal);
    }
    bool ForStmt::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getStartValue(), &ForStmt::setStartValue);
        TRY_REPLACE(getStopValue(),  &ForStmt::setStopValue);
        TRY_REPLACE(getStepValue(),  &ForStmt::setStepValue);
        TRY_REPLACE(getLoopVari(),   &ForStmt::setLoopVari);
        return LoopStatement::replaceChild(origin, goal);
    }
    bool DoWhileStmt::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getCondition(), &DoWhileStmt::setCondition);
        return LoopStatement::replaceChild(origin, goal);
    }
    bool StatementBlock::replaceChild(Node *origin, Node *goal) {
        if (replaceStatement(rtti::dyn_cast<Statement>(origin), rtti::dyn_cast<Statement>(goal))) { return true; }
        return Statement::replaceChild(origin, goal);
    }
    bool Expression::replaceChild(Node *origin, Node *goal) {
        return Statement::replaceChild(origin, goal);
    }
    bool HierarchyIdentifier::replaceChild(Node *origin, Node *goal) {
        size_t idx = 0, count = name_components_.size();
        auto CompReplPred = [this, &idx](HierarchyIdentifier &, NameComponent *goal) { this->setNameComponentAt(idx, rtti::dyn_cast<NameComponent>(goal)); };
        for (; idx < count; ++idx) {
            TRY_REPLACE(getNameComponentAt(idx), CompReplPred);
        }
        return Expression::replaceChild(origin, goal);
    }
    bool NameComponent::replaceChild(Node *origin, Node *goal) {
        return Expression::replaceChild(origin, goal);
    }
    bool IdentRefer::replaceChild(Node *origin, Node *goal) {
        return NameComponent::replaceChild(origin, goal);
    }
    bool ArrayIndex::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getBaseComponent(), &ArrayIndex::setBaseComponent);
        TRY_REPLACE(getIndex(), &ArrayIndex::setIndexExpr);
        return NameComponent::replaceChild(origin, goal);
    }
    bool FunctionCall::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getName(), &FunctionCall::setName);
        size_t idx = 0, count = arguments_.size();
        auto ArguReplPred = [this, &idx](FunctionCall &, Expression *goal) { this->setArgumentAt(idx, goal); };
        for (; idx < count; ++idx) {
            TRY_REPLACE(getArgumentAt(idx), ArguReplPred);
        }
        return NameComponent::replaceChild(origin, goal);
    }
    bool TypeConvert::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getSourceExpr(), &TypeConvert::setFromExpression);
        TRY_REPLACE(getTargetType(), &TypeConvert::setTargetType);
        return Expression::replaceChild(origin, goal);
    }
    bool OperatedExpression::replaceChild(Node *origin, Node *goal) {
        return Expression::replaceChild(origin, goal);
    }
    bool UnaryExpression::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getOperand(), &UnaryExpression::setOperand);
        return OperatedExpression::replaceChild(origin, goal);
    }
    bool BinaryExpression::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getLHS(), &BinaryExpression::setLHS);
        TRY_REPLACE(getRHS(), &BinaryExpression::setRHS);
        return OperatedExpression::replaceChild(origin, goal);
    }
    bool FuncAddrExpression::replaceChild(Node *origin, Node *goal) {
        TRY_REPLACE(getCallee(), &FuncAddrExpression::setCallee);
        return Expression::replaceChild(origin, goal);
    }
    bool Value::replaceChild(Node *origin, Node *goal) {
        return Expression::replaceChild(origin, goal);
    }
    bool ValueOfDataSet::replaceChild(Node *origin, Node *goal) {
        size_t idx = 0, count = elements_.size();
        auto ElemReplPred = [this, &idx](ValueOfDataSet &, Expression *goal) { elements_[idx] = goal; this->setChild(goal); };
        for (; idx < count; ++idx) {
            TRY_REPLACE(elements_[idx], ElemReplPred);
        }
        return Value::replaceChild(origin, goal);
    }
    bool ValueOfDatetime::replaceChild(Node *origin, Node *goal) {
        return Value::replaceChild(origin, goal);
    }
    bool ValueOfBool::replaceChild(Node *origin, Node *goal) {
        return Value::replaceChild(origin, goal);
    }
    bool ValueOfDecimal::replaceChild(Node *origin, Node *goal) {
        return Value::replaceChild(origin, goal);
    }
    bool ValueOfString::replaceChild(Node *origin, Node *goal) {
        return Value::replaceChild(origin, goal);
    }
}
