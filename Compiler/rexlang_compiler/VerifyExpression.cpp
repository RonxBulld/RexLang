//
// Created by rex on 2020/11/21.
//

#include "NodeDecl.h"
#include "rtti.h"

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
        if (!def()) {
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

    bool FunctionCall::matchFunctor(FunctorDecl *functorDecl) const {
        std::vector<Expression*> arguments = getArguments();
        const std::vector<ParameterDecl*> &parameters = functorDecl->getParameters();

        // 检查所有实参表达式

        // 1. 获取形参有效个数

        // 1.1. 获取个数

        size_t argu_count = arguments.size();
        size_t param_count = parameters.size();

        // 1.2. 检查是否有不定参数

        bool dynamic_params = functorDecl->hasVarArgs();
        if (param_count > 0 && parameters.back()->isVariParam()) {
            param_count -= 1;
            dynamic_params = true;
        }

        // 2. 根据形参有效个数用空指针扩展实参

        while (argu_count < param_count) {
            arguments.push_back(nullptr);
            argu_count++;
        }

        // 3. 如果形参长度不定则截取实参前N个进行计算

        if (dynamic_params) {
            argu_count = param_count;
        }

        // 4. 检查形参和实参个数是否匹配

        if (argu_count != param_count) {
            assert(false);
            return false;
        }

        // 5. 针对每个实参/形参对

        for (size_t idx = 0; idx < argu_count; idx++) {

            Expression *          & argument  = arguments [idx];
            ParameterDecl * const & parameter = parameters[idx];

            TypeDecl *argu_ty  = argument->getExpressionType();
            TypeDecl *param_ty = parameter->type();

            if (argument == nullptr) {

                // 5.1. 如果实参为空指针

                // 5.1.1. 检查形参可空属性

                if (!parameter->isNullable()) {
                    assert(false);
                    return false;
                } else {
                    continue;
                }

            }
            /*else*/
            if (param_ty->isArrayType() && argument != nullptr) {

                // 5.2. 如果形参类型为数组，则实参必须为左值或左值引用（参考形参）数组变量，且元素类型严格一致
                // 数组参数只能以引用方式传递

                // 检查数组的元素类型是否匹配

                if (!param_ty->compareTo(argu_ty)) {
                    assert(false);
                    return false;
                }

            }
            /*else*/
            if (parameter->shouldBeReference() && argument != nullptr) {

                // 5.3. 如果形参参考属性为真，则实参必须为左值或左值引用（参考形参），并且变量类型严格一致

                if (HierarchyIdentifier *hierarchy_identifier = argument->as<HierarchyIdentifier>()) {
                    (void) hierarchy_identifier;
                    if (!ReferenceType::peek(param_ty)->compareTo(ReferenceType::peek(argu_ty))) {
                        assert(false);
                        return false;
                    }
                } else {
                    assert(false);
                    return false;
                }

            }
            /*else*/
            if (argument != nullptr) {

                // 5.4. 如果形参不具备上述属性
                // 以传值的方式检查，允许隐式类型提升

                if (Expression * implicit_convert = argument->castTo(param_ty)) {
                    argument = implicit_convert;

                } else {
                    assert(false);
                    return false;
                }
            }
        }
        return true;
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