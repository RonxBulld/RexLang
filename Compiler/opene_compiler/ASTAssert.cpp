//
// Created by rex on 2020/1/29.
//

#include "ASTAssert.h"

namespace opene {

    bool ASTAssert::VariableDeclareAsArray(const BaseVariDecl *baseVariDecl) {
        if (const VariableDecl *variable_decl = baseVariDecl->as<VariableDecl>()) {
            return !variable_decl->type_decl_ptr_->is<ArrayDecl>();
        } else {
            return false;
        }
    }

    bool ASTAssert::TypeCanIndexable(const TypeDecl *typeDecl) {
        if (const ArrayDecl *array_decl = typeDecl->as<ArrayDecl>()) {
            (void) array_decl;
            return true;
        } else if (const BuiltinTypeDecl *builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            // 内置类型只有字节集能够被索引
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet;
        } else {
            return false;
        }
    }

    bool ASTAssert::TypeCanCallable(const TypeDecl *typeDecl) {
        if (const FunctorDecl *functor_decl = typeDecl->as<FunctorDecl>()) {
            (void) functor_decl;
            return true;
        } else {
            return false;
        }
    }

    bool ASTAssert::IsFixedDimArray(const TypeDecl *typeDecl) {
        if (ASTAssert::TypeCanIndexable(typeDecl) == false) { return false; }
        if (const ArrayDecl *array_decl = typeDecl->as<ArrayDecl>()) {
            // 数组变量总是可变的
            return false;
        } else if (const BuiltinTypeDecl *builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            // 字节集维度总是固定为1
            return true;
        } else {
            return false;
        }
    }

    bool ASTAssert::IsStaticLibraryAPI(const FunctorDecl *functorDecl) {
        if (const APICommandDecl *api_command_decl = functorDecl->as<APICommandDecl>()) {
            return api_command_decl->library_type_ == LibraryType::kLTStatic;
        } else {
            return false;
        }
    }

    bool ASTAssert::IsDynamicLibraryAPI(const FunctorDecl *functorDecl) {
        if (const APICommandDecl *api_command_decl = functorDecl->as<APICommandDecl>()) {
            return api_command_decl->library_type_ == LibraryType::kLTDynamic;
        } else {
            return false;
        }
    }
}