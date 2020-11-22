//
// Created by rex on 2020/11/21.
//

#include "NodeDecl.h"

#define VERIFY_SUB_EXPR(expr) if (!(expr)->VerifyExpression())

namespace rexlang {

    bool Expression::VerifyExpression() {
        return VerifyExpressionInternal();
    }

    bool HierarchyIdentifier::VerifyExpressionInternal() {

        // 验证所有子式

        for (NameComponent *component : getNameComponents()) {
            VERIFY_SUB_EXPR(component) { assert(false); return false; }
        }

        return true;
    }

    bool NameComponent::VerifyExpressionInternal() {

        // 如果前面有名称组件那么只能是结构体

        if (NameComponent *forward = Forward()) {
            StructureDecl *structure = forward->getExpressionType()->as<StructureDecl>();
            if (!structure) {
                assert(false);
                return false;
            }
            if (structure->getElementWithName(getBaseId()->def()->id()) == nullptr) {
                assert(false);
                return false;
            }
        }

        return true;
    }

    bool IdentRefer::VerifyExpressionInternal() {
        if (!reference_) {
            assert(false);
            return false;
        }

        return this->NameComponent::VerifyExpressionInternal();
    }

    bool ArrayIndex::VerifyExpressionInternal() {
        VERIFY_SUB_EXPR(base_)  { assert(false); return false; }
        VERIFY_SUB_EXPR(index_) { assert(false); return false; }

        if (!getBaseId()->getExpressionType()->isIndexable()) {
            assert(false);
            return false;
        }

        return this->NameComponent::VerifyExpressionInternal();
    }

    bool FunctionCall::VerifyExpressionInternal() {
        VERIFY_SUB_EXPR(name_) { assert(false); return false; }
        for (Expression *argu : arguments_) {
            VERIFY_SUB_EXPR(argu) { assert(false); return false; }
        }

        if (!matchFunctor(callee_)) {
            assert(false);
            return false;
        }

        return this->NameComponent::VerifyExpressionInternal();
    }

    bool TypeConvert::VerifyExpressionInternal() {
        return isTypeConvertValid();
    }

    bool UnaryExpression::VerifyExpressionInternal() {

        // 检查一元表达式是否合法

        VERIFY_SUB_EXPR(operand_value_) { assert(false); return false; }
        TypeDecl *operand_type = operand_value_->getExpressionType();
        if (operand_type == nullptr) { return false; }

        // 由于一元运算只支持符号求反，故只检查其数值性

        bool is_numerical = operand_type->isNumerical();
        if (is_numerical == false) {
            assert(false);
            return false;
        }

        return true;

    }

    bool BinaryExpression::VerifyExpressionInternal() {

        // 检查二元表达式是否可结合

        VERIFY_SUB_EXPR(lhs_) { assert(false); return false; }
        VERIFY_SUB_EXPR(rhs_) { assert(false); return false; }
        bool operand_valid = isBinaryOperateValid();
        if (operand_valid == false) {
            assert(false);
            return false;
        }

        return true;
    }

    bool FuncAddrExpression::VerifyExpressionInternal() {

        // 检查只要是函数就行

        return (bool) callee_;
    }

    bool ValueOfDataSet::VerifyExpressionInternal() {

        // 当前版本只允许字节集中的元素全为整数常量

        for (Expression *element : this->elements_) {
            if (ValueOfDecimal *value_of_decimal = element->as<ValueOfDecimal>()) {
                VERIFY_SUB_EXPR(value_of_decimal) { assert(false); return false; }
                if (!value_of_decimal->isIntValue()) {
                    assert(false);
                    return false;
                }
            } else {
                assert(false);
                return false;
            }
        }
        return true;
    }

    bool ValueOfDatetime::VerifyExpressionInternal() { return true; }
    bool ValueOfBool    ::VerifyExpressionInternal() { return true; }
    bool ValueOfDecimal ::VerifyExpressionInternal() { return true; }
    bool ValueOfString  ::VerifyExpressionInternal() { return true; }

}