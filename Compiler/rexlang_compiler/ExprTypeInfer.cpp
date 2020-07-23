//
// Created by Administrator on 2020/7/23.
//

#include "NodeDecl.h"

namespace rexlang {

    TypeDecl *Expression::getExpressionTy() const {
        if (expression_type_) {
            assert(expression_type_ == getExpressionTypeInternal());
            return expression_type_;
        } else {
            return getExpressionTypeInternal();
        }
    }

    TypeDecl *Expression::getExpressionTy() {
        expression_type_ = const_cast<const Expression *>(this)->getExpressionTy();
        return expression_type_;
    }

    /**************************************************************
     * 实现各表达式叶子节点的 getExpressionTypeInternal
     **************************************************************/

    TypeDecl *HierarchyIdentifier::getExpressionTypeInternal() const {
        assert(name_components_.empty() == false);

        // HierarchyIdentifier 会试图获取所有组件的类型，但是只以最后一个组件类型作为返回类型

        TypeDecl *type = nullptr;
        for (NameComponent *name_component : name_components_) {
            type = name_component->getExpressionTy();
        }
        return type;
    }

    TypeDecl *Identifier::getExpressionTypeInternal() const {
        TagDecl *tag_decl = this->getDecl();
        return tag_decl->getType();
    }

    TypeDecl *ArrayIndex::getExpressionTypeInternal() const {
        return getElementTy();
    }

    TypeDecl *FunctionCall::getExpressionTypeInternal() const {
        FunctorDecl *functor_decl = getFunctionDeclare();
        assert(functor_decl);
        return functor_decl->getReturnType();
    }

    TypeDecl *TypeConvert::getExpressionTypeInternal ()  const {
        return getTargetType();
    }

    TypeDecl *UnaryExpression::getExpressionTypeInternal ()  const {
        return operand_value_->getExpressionTy();
    }

    TypeDecl *BinaryExpression::getExpressionTypeInternal ()  const {
        const OperatorType &opt = getOperator();
        if (opt.isExtraRelOpt() || opt.isBooleanOpt()) {
            return getTranslateUnit()->getBoolTy();
        }
        else if (opt.isNumericalOpt()) {
            return getBinaryOperateUpgradeType();
        }
        else {
            assert(false);
            return nullptr;
        }
    }

}
