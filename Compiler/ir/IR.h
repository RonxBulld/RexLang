//
// Created by rex on 2020/2/5.
//

#ifndef OPENELANGUAGE_IR_H
#define OPENELANGUAGE_IR_H

namespace opene {

    struct IR {
    };

    struct BaseBlock : public IR {
    };

    struct Module : public BaseBlock {
    };

    struct Function : public IR {
    };

}

#endif //OPENELANGUAGE_IR_H
