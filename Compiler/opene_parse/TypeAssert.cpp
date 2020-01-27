//
// Created by rex on 2020/1/25.
//

#include "TypeAssert.h"

namespace opene {
    bool TypeAssert::IsCharType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeChar;
        }
        return false;
    }

    bool TypeAssert::IsIntegerType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger;
        }
        return false;
    }

    bool TypeAssert::IsFloatType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFloat;
        }
        return false;
    }

    bool TypeAssert::IsBoolType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool;
        }
        return false;
    }

    bool TypeAssert::IsStringType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString;
        }
        return false;
    }

    bool TypeAssert::IsDataSetType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet;
        }
        return false;
    }

    bool TypeAssert::IsShortType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeShort;
        }
        return false;
    }

    bool TypeAssert::IsLongType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeLong;
        }
        return false;
    }

    bool TypeAssert::IsDatatimeType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatetime;
        }
        return false;
    }

    bool TypeAssert::IsFuncPtrType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFuncPtr;
        }
        return false;
    }

    bool TypeAssert::IsDoubleType(const TypeDeclPtr typeDecl) {
        if (const BuiltinTypeDeclPtr builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDouble;
        }
        return false;
    }

    bool TypeAssert::IsExternBooleanType(const TypeDeclPtr typeDecl) {
        if (TypeAssert::IsCharType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsIntegerType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsFloatType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsBoolType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsShortType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsLongType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsFuncPtrType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsDoubleType(typeDecl)) {
            return true;
        } else {
            return false;
        }
    }

    bool TypeAssert::IsAssignable(const TypeDeclPtr lhs_type, const TypeDeclPtr rhs_type) {
        // 1. 至少有一个是数组
        // 1.1. 两者都是数组则递归判定基础类型
        // 1.2. 其中一个是数组则不可赋值
        // 2. 其中之一是内置类型
        // 2.1. 两者都是内置类型
        // 2.1.1. 一致则可赋值
        // 2.1.2. 左值类型兼容右值类型则可赋值
        // 2.2. 其它情况皆不可赋值
        // 3. 两者类型一致则可赋值
        // 4. 其余情况皆不可赋值
    }
}