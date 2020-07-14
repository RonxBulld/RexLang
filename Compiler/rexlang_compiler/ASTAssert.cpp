//
// Created by rex on 2020/1/29.
//

#include "ASTAssert.h"

namespace rexlang {

    bool ASTAssert::VariableDeclareAsArray(const BaseVariDecl *baseVariDecl) {
        if (const VariableDecl *variable_decl = baseVariDecl->as<VariableDecl>()) {
            return !variable_decl->vari_type_decl_->is<ArrayDecl>();
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