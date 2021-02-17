/************************************************************
 * getExpressionTypeInternal会假定表达式经过了验证，
 * 即VerifyExpression返回值为true。
 * RonxBulld 2020/7/23.
 ************************************************************/

#include "NodeDecl.h"

namespace rexlang {

    TypeDecl *Expression::getExpressionType() const {
        return getExpressionTypeInternal();
    }

    /**************************************************************
     * 实现各表达式叶子节点的 getExpressionTypeInternal
     **************************************************************/

    TypeDecl *IdentRefer::getExpressionTypeInternal() const {
        TagDecl *tag_decl = this->getDecl();
        return tag_decl->getType();
    }

    TypeDecl *ArrayIndex::getExpressionTypeInternal() const {
        return getElementTy();
    }

    TypeDecl *FunctionCall::getExpressionTypeInternal() const {
        FunctorDecl *functor_decl = getCallee();
        assert(functor_decl);
        return functor_decl->getReturnType();
    }

    TypeDecl *TypeConvert::getExpressionTypeInternal()  const {
        return getTargetType();
    }

    TypeDecl *UnaryExpression::getExpressionTypeInternal()  const {
        return operand_value_->getExpressionType();
    }

    TypeDecl *BinaryExpression::getExpressionTypeInternal()  const {
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

    TypeDecl *FuncAddrExpression::getExpressionTypeInternal() const { return getTranslateUnit()->getFuncPtrTy(); }
    TypeDecl *ValueOfDataSet    ::getExpressionTypeInternal() const { return getTranslateUnit()->getDataSetTy(); }
    TypeDecl *ValueOfDatetime   ::getExpressionTypeInternal() const { return getTranslateUnit()->getDatetimeTy(); }
    TypeDecl *ValueOfBool       ::getExpressionTypeInternal() const { return getTranslateUnit()->getBoolTy(); }
    TypeDecl *ValueOfDecimal    ::getExpressionTypeInternal() const { if (type_ == type::kInt) return getTranslateUnit()->getIntegerTy(); else return getTranslateUnit()->getFloatTy() ; }
    TypeDecl *ValueOfString     ::getExpressionTypeInternal() const { return getTranslateUnit()->getStringTy(); }

}
