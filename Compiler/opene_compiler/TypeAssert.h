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
         * @brief 是否为空类型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为空类型
         */
        static bool IsVoidType(const TypeDecl *typeDecl);

        /**
         * @brief 是否为字节型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为字节型
         */
        static bool IsCharType(const TypeDecl * typeDecl);

        /**
         * @brief 是否为整数型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为整数型
         */
        static bool IsIntegerType(const TypeDecl * typeDecl);

        /**
         * @brief 是否为小数型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为小数型
         */
        static bool IsFloatType(const TypeDecl * typeDecl);

        /**
         * @brief 是否为逻辑型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为逻辑型
         */
        static bool IsBoolType(const TypeDecl * typeDecl);

        /**
         * @brief 是否为文本型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为文本型
         */
        static bool IsStringType(const TypeDecl * typeDecl);

        /**
         * @brief 是否为字节集
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为字节集
         */
        static bool IsDataSetType(const TypeDecl * typeDecl);

        /**
         * @brief 是否为短整型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为短整型
         */
        static bool IsShortType(const TypeDecl * typeDecl);

        /**
         * @brief 是否为长整型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为长整型
         */
        static bool IsLongType(const TypeDecl * typeDecl);

        /**
         * @brief 是否为日期时间型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为日期时间型
         */
        static bool IsDatatimeType(const TypeDecl * typeDecl);

        /**
         * @brief 是否为子程序指针
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为子程序指针
         */
        static bool IsFuncPtrType(const TypeDecl * typeDecl);

        /**
         * @brief 是否为双精度小数型
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为双精度小数型
         */
        static bool IsDoubleType(const TypeDecl * typeDecl);

        // === 扩展类型断言 ===

        /**
         * @brief 类型是否具有扩展布尔性
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为字节、整数、小数、双精度、逻辑、短整、长整类型
         */
        static bool IsExternBooleanType(const TypeDecl * typeDecl);

        /**
         * @brief 类型是否具有数值性
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为字节、整数、小数、双精度、短整、长整、浮点、双精度类型
         */
        static bool IsNumerical(const TypeDecl *typeDecl);

        /**
         * @brief 类型是否整数族
         * @param typeDecl 需要检查的类型
         * @return 检查指定类型是否为字节、整数、小数、双精度、短整、长整类型
         */
        static bool IsIntegerClass(const TypeDecl *typeDecl);

        // === 高阶类型断言 ===

        /*
         * 检查二元运算是否合法
         * 该断言主要判断二元表达式中左右子式是否可以通过运算符计算
         */
        static bool IsBinaryOperationValid(TypeDecl *lhsType, TypeDecl *rhsType, _OperatorExpression::OperatorType operatorType);

        /*
         * 获取类型提升结果
         */
        static BuiltinTypeDecl::EnumOfBuiltinType ResultOfTypeUpgrade(BuiltinTypeDecl::EnumOfBuiltinType ltype, BuiltinTypeDecl::EnumOfBuiltinType rtype);

        /*
         * 判断表达式是否为左值
         */
        static bool ExpressionIsLValue(Expression *expression);
    };

}

#endif //OPENELANGUAGE_TYPEASSERT_H
