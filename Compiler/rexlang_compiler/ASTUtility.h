//
// Created by rex on 2020/1/28.
//

#ifndef REXLANG_ASTUTILITY_H
#define REXLANG_ASTUTILITY_H

#include "NodeDecl.h"
#include "rtti.h"

namespace rexlang {

    namespace utility {

        void FixNodeParent(Node *root);

        template <typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        static Ty *FindSpecifyTypeParent(Node *base) {
            while (base && !rtti::dyn_cast<Ty>(base)) {
                base = base->getParent();
            }
            return rtti::dyn_cast<Ty>(base);
        }

    };

}

#endif //REXLANG_ASTUTILITY_H
