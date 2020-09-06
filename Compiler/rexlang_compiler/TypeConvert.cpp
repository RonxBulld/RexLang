//
// Created by rexfield on 2020/7/31.
//

#include "NodeDecl.h"

namespace rexlang {

    /*===--------------------------------===*
     * ReferenceType
     */

    ReferenceType *ReferenceType::get(TypeDecl *pointeeType) {
        return Node::Create<ReferenceType>(pointeeType->getAstContext(), pointeeType);
    }

    /*===--------------------------------===*
     * VariTypeDecl
     */

    ArrayDecl *VariTypeDecl::getArrayToWithDimStr(const std::vector<size_t> &dims) {
        return ArrayDecl::get(this, dims);
    }

    /*===--------------------------------===*
     * ArrayDecl
     */

    ArrayDecl *ArrayDecl::get(TypeDecl *elementType, const std::vector<size_t> &dimensions) {
        return CreateNode<ArrayDecl>(elementType->getAstContext(), elementType, dimensions);
    }

    /*===--------------------------------===*
     * Expression
     */

    Expression *Expression::castTo(TypeDecl *targetType) {
        TypeDecl *this_type = getExpressionType();
        assert(this_type);
        assert(targetType);
        assert(getAstContext() == targetType->getAstContext());
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
