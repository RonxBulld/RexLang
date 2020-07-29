//
// Created by rex on 2020/7/26.
//

#ifndef REXLANG_RTTI_H
#define REXLANG_RTTI_H

#include "NodeDecl.h"

namespace rexlang {
    namespace rtti {

        template <typename T>
        T *dyn_cast(Node *n) {
            return dynamic_cast<T *>(n);
        }

    }
}

#endif //REXLANG_RTTI_H
