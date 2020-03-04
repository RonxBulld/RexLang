//
// Created by rex on 2020/3/1.
//

#include "ASTBuilder.h"

#include <utility>

namespace opene {
    ASTBuilder::ASTBuilder(ASTContext &context) : context_(context) {
    }

    ParameterDecl *ASTBuilder::CreateParameter(const std::string &name, TypeDecl *paramType, bool isReference, bool isNullable, bool isArray) {
        ParameterDecl *parameter_decl = CreateNode<ParameterDecl>(&context_);
        parameter_decl->name_.string_ = context_.CreateString(name);
        parameter_decl->type_decl_ptr_ = paramType;
        parameter_decl->type_name_ = paramType->name_;
        parameter_decl->is_reference = isReference;
        parameter_decl->is_nullable = isNullable;
        parameter_decl->is_array = isArray;
    }

    FunctorDecl * ASTBuilder::CreateFunctorDecl(const std::string &name, TypeDecl *returnType, const std::vector<ParameterDecl *> &params, TranslateUnit *translateUnit) {
        FunctorDecl *functor_decl = CreateNode<FunctorDecl>(&context_);
        functor_decl->name_.string_ = context_.CreateString(name);
        functor_decl->return_type_ = returnType;
        functor_decl->return_type_name_ = returnType->name_;
        functor_decl->parameters_ = params;
        for (size_t idx = 0; idx < params.size(); idx++) {
            params[idx]->index_ = idx;
        }

        translateUnit->functor_declares_[functor_decl->name_.string_] = functor_decl;
        return functor_decl;
    }

    FunctorDecl * ASTBuilder::GetFunctor(const std::string &name, TranslateUnit *translateUnit) {
        for (auto &functor_item : translateUnit->functor_declares_) {
            if (functor_item.first == name) {
                return functor_item.second;
            }
        }
        if (name[0] != '$') { return nullptr; }
        StringRef name_sr = context_.CreateString(name);
        auto functor_iter = translateUnit->functor_declares_.find(name_sr);
        if (functor_iter != translateUnit->functor_declares_.end()) {
            return functor_iter->second;
        }

        return CreateSysRTFunctor(name_sr, translateUnit);
    }

    Expression *ASTBuilder::CreateCall(FunctorDecl *callee, std::vector<Expression *> args) {
        return nullptr;
    }

    FunctorDecl *ASTBuilder::CreateSysRTFunctor(const StringRef &name, TranslateUnit *translateUnit) {
        if (name == "$array_copy") {
            ArrayDecl *array_type = CreateNode<ArrayDecl>(&context_);
            ParameterDecl *array_copy_param = CreateParameter("arrPtr", array_type, true, false, true);
            CreateFunctorDecl(name.str(), array_type, {array_copy_param}, translateUnit);
        } else if (name == "$struct_copy") {
        } else if (name == "$dataset_copy") {
        } else if (name == "$string_copy") {
        } else {
            assert(false);
            return nullptr;
        }
    }
}