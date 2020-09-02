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

}
