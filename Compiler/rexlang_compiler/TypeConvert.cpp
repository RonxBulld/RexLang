/*
 * 通过包装的方式将一个类型的节点转换为另一种类型
 * Rex
 * 2020/7/31
 */

#include "NodeDecl.h"
#include "rtti.h"

namespace rexlang {

    /*===--------------------------------===*
     * ReferenceType
     */

    VariTypeDecl *ReferenceType::get(TypeDecl *pointeeType) {
        if (!pointeeType->isReferenceType()) {
            return Node::Create<ReferenceType>(pointeeType->getAstContext(), pointeeType);
        } else {
            return rtti::dyn_cast<ReferenceType>(pointeeType);
        }
    }

    TypeDecl * ReferenceType::peek(TypeDecl *type) {
        if (type->isReferenceType()) {
            ReferenceType *reference_type = rtti::dyn_cast<ReferenceType>(type);
            assert(reference_type);
            return ReferenceType::peek(reference_type->getPointee());
        } else {
            return type;
        }
    }

    /*===--------------------------------===*
     * VariTypeDecl
     */

    ArrayType *VariTypeDecl::getArrayToWithDimStr(const std::vector<size_t> &dims) {
        return ArrayType::get(this, dims);
    }

    /*===--------------------------------===*
     * ArrayType
     */

    ArrayType *ArrayType::get(TypeDecl *elementType, const std::vector<size_t> &dimensions) {
        return CreateNode<ArrayType>(elementType->getAstContext(), elementType, dimensions);
    }

    /*===--------------------------------===*
     * Expression
     */

    Expression *Expression::castTo(TypeDecl *targetType) {
        TypeDecl *this_type = getExpressionType();
        assert(this_type);
        assert(targetType);
        assert(getAstContext() == targetType->getAstContext());
        this_type = ReferenceType::peek(this_type);
        targetType = ReferenceType::peek(targetType);
        if (this_type == targetType) {
            return this;
        } else {
            if (targetType->isAssginValidFrom(this_type)) {
                TypeConvert *conv_expr = CreateNode<TypeConvert>(getAstContext(), targetType, this);
                return conv_expr;
            } else {
                assert(false);
                return nullptr;
            }
        }
    }

}
