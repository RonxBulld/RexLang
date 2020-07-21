//
// Created by rex on 2020/1/28.
//

#ifndef REXLANG_ASTUTILITY_H
#define REXLANG_ASTUTILITY_H

#include "NodeDecl.h"
#include "../../lite_util/ErrOr.h"
#include "sematic_analysis/SematicAnalysisContext.h"

namespace rexlang {

    class ASTUtility {
    public:
        static void FixNodeParent(Node *root);

        template <typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        static Ty *FindSpecifyTypeParent(Node *base) {
            while (base && !base->is<Ty>()) {
                base = base->getParent();
            }
            return base->as<Ty>();
        }

    };

}

#endif //REXLANG_ASTUTILITY_H
