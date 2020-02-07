//
// Created by rex on 2020/2/5.
//

#ifndef OPENELANGUAGE_EMITOEIR_H
#define OPENELANGUAGE_EMITOEIR_H

namespace opene {

    struct OEIR {
    };

    struct BaseBlock : public OEIR {
    };

    struct Module : public BaseBlock {
    };

    struct Function : public OEIR {
    };

}

#endif //OPENELANGUAGE_EMITOEIR_H
