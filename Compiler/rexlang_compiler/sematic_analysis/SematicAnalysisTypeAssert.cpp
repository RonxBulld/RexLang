//
// Created by rex on 2020/2/6.
//

#include "SematicAnalysis.h"

namespace rexlang {

    bool SematicAnalysis::IsAssignableBetweenType(TypeDecl *lhs_type, TypeDecl *rhs_type) {
        assert(lhs_type);
        assert(rhs_type);
        // - 可能是数组、内置类型、自定义类型
        {
            ArrayType *lhs_array = lhs_type->as<ArrayType>();
            ArrayType *rhs_array = rhs_type->as<ArrayType>();
            // 1. 至少有一个是数组
            if (lhs_array || rhs_array) {
                if (lhs_array && rhs_array) {
                    // 1.1. 两者都是数组则要求元素类型必须一致
                    TypeDecl *lhs_element_type = this->GetIndexableTypeElement(lhs_array);
                    TypeDecl *rhs_element_type = this->GetIndexableTypeElement(rhs_array);
                    return lhs_element_type == rhs_element_type;
                } else {
                    // 1.2. 其中一个是数组则不可赋值
                    assert(false);
                    return false;
                }
            }
        }
        // - 两者都不是数组
        {
            const BuiltinTypeDecl *lhs_builtin = lhs_type->as<BuiltinTypeDecl>();
            const BuiltinTypeDecl *rhs_builtin = rhs_type->as<BuiltinTypeDecl>();
            // 2. 其中之一是内置类型
            if (lhs_builtin || rhs_builtin) {
                if (lhs_builtin && rhs_builtin) {
                    // 2.1. 两者都是内置类型
                    if (lhs_builtin->GetBuiltinType() == rhs_builtin->GetBuiltinType()) {
                        // 2.1.1. 内置类型一致则可赋值
                        return true;
                    } else {
                        // 2.1.2. 左值类型兼容右值类型则可赋值
                        if (lhs_builtin->isNumerical() && rhs_builtin->isNumerical()) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                } else {
                    // 2.2. 其它情况皆不可赋值
                    return false;
                }
            }
        }
        // - 两者都是自定义类型
        {
            // 3. 两者类型一致则可赋值
            if (lhs_type == rhs_type) {
                return true;
            }
        }
        {
            // 4. 其余情况皆不可赋值
            return false;
        }
    }

}