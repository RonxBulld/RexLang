//
// Created by rex on 2020/1/29.
//

#ifndef REXLANG_ASTASSERT_H
#define REXLANG_ASTASSERT_H

#include "NodeDecl.h"

namespace rexlang {

    class ASTAssert {
    public:
        /*
         * 判定变量是否被定义为数组
         */
        static bool VariableDeclareAsArray(const BaseVariDecl *baseVariDecl);

        /*
         * 判定类型是否可调用
         * 只有函数定义是可调用类型
         */
        static bool TypeCanCallable(const TypeDecl *typeDecl);

        /*
         * 判定是否固定维度数组
         */
        static bool IsFixedDimArray(const TypeDecl *typeDecl);

        static bool IsStaticLibraryAPI(const FunctorDecl *functorDecl);

        static bool IsDynamicLibraryAPI(const FunctorDecl *functorDecl);
    };

}

#endif //REXLANG_ASTASSERT_H
