//
// Created by rex on 2020/1/29.
//

#include "ASTAssert.h"

namespace opene {

    bool ASTAssert::VariableDeclareAsArray(const BaseVariDecl *baseVariDecl) {
        if (const VariableDecl *variable_decl = baseVariDecl->as<VariableDecl>()) {
            return !variable_decl->dimensions_.empty();
        } else {
            return false;
        }
    }

    bool ASTAssert::TypeCanIndexable(const TagDecl *tagDecl) {
        if (const VariableDecl *variable_decl = tagDecl->as<VariableDecl>()) {
            // 是变量定义并且定义为多维
            return ASTAssert::VariableDeclareAsArray(variable_decl);
        } else if (const BuiltinTypeDecl *builtin_type_decl = tagDecl->as<BuiltinTypeDecl>()) {
            // 内置类型只有字节集能够被索引
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet;
        } else {
            return false;
        }
    }

    bool ASTAssert::IsFixedDimArray(const TagDecl *tagDecl) {
        if (ASTAssert::TypeCanIndexable(tagDecl) == false) { return false; }
        if (const VariableDecl *variable_decl = tagDecl->as<VariableDecl>()) {
            // 数组变量总是可变的
            return false;
        } else if (const BuiltinTypeDecl *builtin_type_decl = tagDecl->as<BuiltinTypeDecl>()) {
            // 字节集维度总是固定为1
            return true;
        } else {
            return false;
        }
    }

}