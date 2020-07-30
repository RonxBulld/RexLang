//
// Created by rexfield on 2020/7/31.
//

#include "NodeDecl.h"

namespace rexlang {

    /*===--------------------------------===*
     * ReferenceType
     *===--------------------------------===*/

    ReferenceType *ReferenceType::get(IdentRefer *typeName) {
        return Node::Create<ReferenceType>(typeName->getAstContext(), typeName);
    }

    ReferenceType *ReferenceType::get(TypeDecl *pointeeType) {
        return Node::Create<ReferenceType>(pointeeType->getAstContext(), pointeeType);
    }

}
