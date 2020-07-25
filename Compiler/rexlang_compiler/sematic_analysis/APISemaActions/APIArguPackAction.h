//
// Created by rex on 2020/4/2.
//

#ifndef REXLANG_APIARGUPACKACTION_H
#define REXLANG_APIARGUPACKACTION_H

#include "../APISemaAction.h"

namespace rexlang {

    struct APICommandDecl;

    namespace sa {

        class APIArguPackAction : public APISemaAction {
        public:
            bool need(const APICommandDecl *apiCommandDecl, SemaContext &semaCtx) const override ;
            bool doAction(APICommandDecl *apiCommandDecl, SemaContext &semaCtx) override ;
        };

    }

}

#endif //REXLANG_APIARGUPACKACTION_H
