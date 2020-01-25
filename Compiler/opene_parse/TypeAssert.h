//
// Created by rex on 2020/1/25.
//

#ifndef OPENELANGUAGE_TYPEASSERT_H
#define OPENELANGUAGE_TYPEASSERT_H

#include "NodeDecl.h"

namespace opene {

    /**
     * @brief 类型断言静态类
     */
    class TypeAssert {
    public:
        // === 基本类型断言 ===

        /**
         * @brief 是否为字节型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为字节型
         */
        static bool IsCharType(const TypeDeclPtr typeDecl);

        /**
         * @brief 是否为整数型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为整数型
         */
        static bool IsIntegerType(const TypeDeclPtr typeDecl);

        /**
         * @brief 是否为小数型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为小数型
         */
        static bool IsFloatType(const TypeDeclPtr typeDecl);

        /**
         * @brief 是否为逻辑型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为逻辑型
         */
        static bool IsBoolType(const TypeDeclPtr typeDecl);

        /**
         * @brief 是否为文本型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为文本型
         */
        static bool IsStringType(const TypeDeclPtr typeDecl);

        /**
         * @brief 是否为字节集
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为字节集
         */
        static bool IsDataSetType(const TypeDeclPtr typeDecl);

        /**
         * @brief 是否为短整型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为短整型
         */
        static bool IsShortType(const TypeDeclPtr typeDecl);

        /**
         * @brief 是否为长整型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为长整型
         */
        static bool IsLongType(const TypeDeclPtr typeDecl);

        /**
         * @brief 是否为日期时间型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为日期时间型
         */
        static bool IsDatatimeType(const TypeDeclPtr typeDecl);

        /**
         * @brief 是否为子程序指针
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为子程序指针
         */
        static bool IsFuncPtrType(const TypeDeclPtr typeDecl);

        /**
         * @brief 是否为双精度小数型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为双精度小数型
         */
        static bool IsDoubleType(const TypeDeclPtr typeDecl);

        // === 扩展类型断言 ===

        /**
         * @brief 类型是否具有扩展布尔性
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为字节、整数、小数、双精度、逻辑、短整、长整类型
         */
        static bool IsExternBooleanType(const TypeDeclPtr typeDecl);
    };

}

#endif //OPENELANGUAGE_TYPEASSERT_H
