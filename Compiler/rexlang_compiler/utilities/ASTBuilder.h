//
// Created by rex on 2020/12/13.
//

#ifndef REXLANG_ASTBUILDER_H
#define REXLANG_ASTBUILDER_H

#include "../NodeDecl.h"

namespace rexlang {
    class ASTBuilder {
    private:
        ASTContext *ctx_;
    public:
        ASTBuilder(ASTContext *ctx) : ctx_(ctx) {}

        template <typename Ty, typename ... Args>
        Ty *Create(Args && ... args) const {
            return CreateNode<Ty>(ctx_, std::forward<Args>(args)...);
        }
    };
}

#endif //REXLANG_ASTBUILDER_H
