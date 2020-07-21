//
// Created by rex on 2020/1/25.
//

#ifndef REXLANG_TYPEASSERT_H
#define REXLANG_TYPEASSERT_H

#include "NodeDecl.h"

namespace rexlang {

    /**
     * @brief 类型断言静态类
     */
    class TypeAssert {
    public:
        // === 基本类型断言 ===

        // === 高阶类型断言 ===

        /*
         * 获取类型提升结果
         */
        static EnumOfBuiltinType ResultOfTypeUpgrade(EnumOfBuiltinType ltype, EnumOfBuiltinType rtype);

    };

}

#endif //REXLANG_TYPEASSERT_H
