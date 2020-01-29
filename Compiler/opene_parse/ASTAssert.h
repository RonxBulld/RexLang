//
// Created by rex on 2020/1/29.
//

#ifndef OPENELANGUAGE_ASTASSERT_H
#define OPENELANGUAGE_ASTASSERT_H

#include "NodeDecl.h"

namespace opene {

    class ASTAssert {
    public:
        /*
         * 判定变量是否被定义为数组
         */
        static bool VariableDeclareAsArray(const BaseVariDecl *baseVariDecl);

        /*
         * 判定类型是否可索引
         */
        static bool TypeCanIndexable(const TagDecl *tagDecl);

        /*
         * 判定是否固定维度数组
         */
        static bool IsFixedDimArray(const TagDecl *tagDecl);
    };

}

#endif //OPENELANGUAGE_ASTASSERT_H
