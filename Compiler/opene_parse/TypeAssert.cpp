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
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatatime;
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
}