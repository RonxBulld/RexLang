//
// Created by rex on 2020/1/28.
//

#ifndef OPENELANGUAGE_ASTUTILITY_H
#define OPENELANGUAGE_ASTUTILITY_H

#include "NodeDecl.h"

namespace opene {

    class ASTUtility {
    public:
        static void FixNodeParent(Node *root);
    };

}

#endif //OPENELANGUAGE_ASTUTILITY_H
