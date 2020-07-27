//
// Created by rex on 2020/1/23.
//

#include "SematicAnalysis.h"

#include "../NodeDecl.h"
#include "../utilities/Str2Attr.h"
#include "../TypeAssert.h"
#include "../ASTUtility.h"
#include "../ASTContext.h"
#include "../utilities/Diagnostic.h"
#include "../../../lite_util/Defer.h"
#include "APISemaActions/APIArguPackAction.h"

namespace rexlang {
    TypeDecl *FunctionCall::CheckExpressionInternal() {

    }

    VariTypeDecl *UnaryExpression::CheckExpressionInternal() {

        // 检查一元表达式是否合法

        if (unary_expression->operator_type_ == UnaryExpression::OperatorType::kOptNone) { return nullptr; }
        TypeDecl *operand_type = this->CheckExpression(unary_expression->operand_value_);
        if (operand_type == nullptr) { return nullptr; }

        // 由于一元运算只支持符号求反，故只检查其数值性

        bool is_numerical = operand_type->IsNumerical();
        if (is_numerical == false) {
            assert(false);
            return nullptr;
        }

        // 根据运算类型返回类型

        return operand_type;

    }

    VariTypeDecl *BinaryExpression::CheckExpressionInternal() {

        // 检查二元表达式是否可结合

        if (binary_expression->operator_type_ == UnaryExpression::OperatorType::kOptNone) { return nullptr; }
        TypeDecl *lhs_operand_type = this->CheckExpression(binary_expression->lhs_);
        TypeDecl *rhs_operand_type = this->CheckExpression(binary_expression->rhs_);
        bool operand_valid = binary_expression->IsBinaryOperateValid();
        if (operand_valid == false) {
            assert(false);
            return nullptr;
        }

        // 根据运算类型返回类型

        TypeDecl *upgraded_type = binary_expression->getBinaryOperateUpgradeType();
        assert(upgraded_type);

        ErrOr<Expression*> implicit_conv_lhs = this->MakeImplicitConvertIfNeccessary(upgraded_type, binary_expression->lhs_);
        ErrOr<Expression*> implicit_conv_rhs = this->MakeImplicitConvertIfNeccessary(upgraded_type, binary_expression->rhs_);
        if (implicit_conv_lhs.NoError()) { binary_expression->lhs_ = implicit_conv_lhs.Value(); }
        if (implicit_conv_rhs.NoError()) { binary_expression->rhs_ = implicit_conv_rhs.Value(); }

        if (binary_expression->operator_type_ == OperatorType::kOptDiv) {
            return TU->getFloatTy();
        } else if (binary_expression->operator_type_ == OperatorType::kOptFullDiv) {
            return TU->getIntegerTy();
        } else if (TypeAssert::IsCompareOperator(binary_expression->operator_type_)) {
            return TU->getBoolTy();
        } else {
            return upgraded_type;
        }

    }

    TypeDecl *FuncAddrExpression::CheckExpressionInternal() {
        TypeDecl *type_decl = TU->getFuncPtrTy();
        assert(type_decl);
        FunctorDecl * functor_decl = ASTUtility::GetFunctionDeclare(func_addr_expression);
        if (functor_decl == nullptr) {
            assert(false);
            return nullptr;
        }
        return type_decl;

    }

    TypeDecl *ResourceRefExpression::CheckExpressionInternal() {

        // TODO: 需要通过查找常量表来确定类型

        assert(false);
        return nullptr;

    }

    TypeDecl *ValueOfDataSet::CheckExpressionInternal() {

        // 当前版本只允许字节集中的元素全为整数常量

        for (Expression *element : this->elements_) {
            if (ValueOfDecimal *value_of_decimal = element->as<ValueOfDecimal>()) {
                if (value_of_decimal->type_ != ValueOfDecimal::type::kInt) {
                    assert(false);
                    return nullptr;
                }
            } else if (ResourceRefExpression *resource_ref_expr = element->as<ResourceRefExpression>()) {

                // TODO: 检查值

            } else {
                assert(false);
                return nullptr;
            }
        }
        return this->getTranslateUnit()->getDataSetTy();
    }

    TypeDecl *ValueOfDatetime::CheckExpressionInternal() {
        return this->getTranslateUnit()->getDatetimeTy();
    }

    TypeDecl *ValueOfBool::CheckExpressionInternal() {
        return this->getTranslateUnit()->getBoolTy();
    }

    TypeDecl *ValueOfDecimal::CheckExpressionInternal() {
        return this->getTranslateUnit()->getIntegerTy();
    }

    TypeDecl *ValueOfString::CheckExpressionInternal() {
        return this->getTranslateUnit()->getStringTy();
    }

    ErrOr<Expression *> SematicAnalysis::MakeImplicitConvertIfNeccessary(TypeDecl *targetType, Expression *convertExpression) {
        // 先判断赋值性
        if (!this->IsAssignableBetweenType(targetType, convertExpression->getExpressionType())) {
            // 两边类型不可赋值
            return ErrOr<Expression*>::CreateError(1);
        }
        // 再判断是否转换
        if (convertExpression->getExpressionType() == targetType) {
            // 类型一致，无需转换
            return MakeNoErrVal(convertExpression);
        } else if (!targetType->is<BuiltinTypeDecl>() || !convertExpression->getExpressionType()->is<BuiltinTypeDecl>()) {
            // 其中有非内置类型，无法转换
            return MakeNoErrVal(convertExpression);
        } else {
            TypeConvert *type_convert = CreateNode<TypeConvert>(convertExpression->ast_context_);
            type_convert->from_expression_ = convertExpression;
            type_convert->getExpressionType() = targetType;
            type_convert->source_type_ = convertExpression->getExpressionType();
            type_convert->target_type_ = targetType;
            type_convert->parent_node_ = convertExpression;
            convertExpression->parent_node_ = type_convert;
            return MakeNoErrVal<Expression*>(type_convert);
        }
    }

    bool SematicAnalysis::CheckIfArgumentMatch(std::vector<Expression*> &arguments, const std::vector<ParameterDecl*> &parameters) {

        // 检查所有实参表达式

        for (Expression *argument : arguments) {
            this->CheckExpression(argument);
        }

        // 1. 获取形参有效个数

        // 1.1. 获取个数

        size_t argu_count = arguments.size();
        size_t param_count = parameters.size();

        // 1.2. 检查是否有不定参数

        bool dynamic_params = false;
        if (param_count > 0 && parameters.back()->name_.string_ == u8"...") {
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

            if (arguments[idx] == nullptr) {

                // 5.1. 如果实参为空指针

                // 5.1.1. 检查形参可空属性

                if (parameters[idx]->is_nullable_ == false) {
                    assert(false);
                    return false;
                } else {
                    continue;
                }

            }
            /*else*/ if (parameters[idx]->is_array_ && arguments[idx] != nullptr) {

                // 5.2. 如果形参数组属性为真，则实参必须为左值或左值引用（参考形参）数组变量，且元素类型严格一致
                // 数组参数只能以引用方式传递

                parameters[idx]->is_reference_ = true;
                if (TypeAssert::ExpressionIsLValue(arguments[idx]) == false) {
                    assert(false);
                    return false;
                }

                // 检查数组的元素类型是否匹配

                if (HierarchyIdentifier *hierarchy_identifier = arguments[idx]->as<HierarchyIdentifier>()) {
                    TypeDecl *argu_type = this->GetHierarchyIdentifierQualifiedType(hierarchy_identifier);
                    if (argu_type->is<ArrayDecl>()) {
                        TypeDecl *param_arr_element_type = this->GetIndexableTypeElement(parameters[idx]->vari_type_decl_);
                        TypeDecl *argu_arr_element_type = this->GetIndexableTypeElement(argu_type);
                        if (param_arr_element_type != argu_arr_element_type) {
                            assert(false);
                            return false;
                        }
                    } else {
                        assert(false);
                        return false;
                    }
                } else {
                    assert(false);
                    return false;
                }

            }
            /*else*/ if (parameters[idx]->is_reference_ && arguments[idx] != nullptr) {

                // 5.3. 如果形参参考属性为真，则实参必须为左值或左值引用（参考形参），并且变量类型严格一致

                if (TypeAssert::ExpressionIsLValue(arguments[idx]) == false) {
                    assert(false);
                    return false;
                }
                if (HierarchyIdentifier *hierarchy_identifier = arguments[idx]->as<HierarchyIdentifier>()) {
                    TypeDecl *argu_type = this->GetHierarchyIdentifierQualifiedType(hierarchy_identifier);
                    SetupHierarchyReferenceType(hierarchy_identifier, ExprUsage::kAsLeftValue);
                    if (argu_type != parameters[idx]->vari_type_decl_) {
                        assert(false);
                        return false;
                    }
                } else {
                    assert(false);
                    return false;
                }

            }
            /*else*/ if (arguments[idx] != nullptr) {

                // 5.4. 如果形参不具备上述属性
                TypeDecl *argu_type = arguments[idx]->getExpressionType();
                assert(argu_type);
                TypeDecl *param_type = parameters[idx]->vari_type_decl_;
                ErrOr<Expression*> implicit_convert = this->MakeImplicitConvertIfNeccessary(param_type, arguments[idx]);
                if (implicit_convert.NoError()) {
                    arguments[idx] = implicit_convert.Value();

                } else {
                    assert(false);
                    return false;
                }
            }
        }
        return true;
    }

    bool FunctionCall::isArgument(Expression *expr)       const { return isArgument(const_cast<const Expression *>(expr)); }
    bool FunctionCall::isArgument(const Expression *expr) const { return indexOfArgument(expr) >= 0; }

    int FunctionCall::indexOfArgument(const Expression *expr) const {
        for (unsigned idx = 0, count = arguments_.size(); idx < count; ++idx) {
            if (expr == arguments_[idx]) {
                return idx;
            }
        }
        return -1;
    }

    int FunctionCall::indexOfArgument(Expression *expr) const { return indexOfArgument(const_cast<const Expression *>(expr)); }

}
