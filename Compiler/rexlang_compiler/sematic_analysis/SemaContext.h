//
// Created by rex on 2020/7/25.
//

#ifndef REXLANG_SEMACONTEXT_H
#define REXLANG_SEMACONTEXT_H

#include "../NodeDecl.h"

namespace rexlang {

    class SemaContext {
    private:
        TranslateUnit *present_translate_unit_ = nullptr;
    public:
        TranslateUnit *getTranslateUnit() const ;
        void setTranslateUnit(TranslateUnit *TU) ;
    };

}

#endif //REXLANG_SEMACONTEXT_H
