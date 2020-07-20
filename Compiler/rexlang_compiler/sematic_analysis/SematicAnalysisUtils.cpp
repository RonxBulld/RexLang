//
// Created by rex on 2020/2/4.
//

#include "SematicAnalysis.h"
#include "../TypeAssert.h"
#include "../ASTAssert.h"
#include "../ASTUtility.h"
#include "../ASTContext.h"
#include "../utilities/Str2Attr.h"
#include "../NodeDecl.h"


namespace rexlang {

    TypeDecl * ArrayIndex::getElementTy() const {

        if (!this->getIndexBase()->GetExpressionTy()->IsIndexable()) {
            return nullptr;
        }

        if (const BuiltinTypeDecl *builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            if (builtin_type_decl->isDataSetType()) {
                TranslateUnit *translate_unit = ASTUtility::FindSpecifyTypeParent<TranslateUnit>(typeDecl);
                return translate_unit->getCharTy();
            } else {
                return nullptr;
            }

        } else if (const ArrayDecl *array_decl = typeDecl->as<ArrayDecl>()) {
            do {
                typeDecl = array_decl->base_type_;
            } while ((array_decl = typeDecl->as<ArrayDecl>()));
            return typeDecl;

        } else {
            assert(false);
            return nullptr;
        }
    }

    TagDecl *ArrayIndex::EvalBaseNameComponentType() {
        NameComponent *array_base = this->getIndexBase();
        TagDecl *index_target = array_base->EvalBaseNameComponentType();
        if (!index_target) {
            assert(false);
            return nullptr;
        }

        // 检查类型是否可索引

        if (!ASTAssert::TypeCanIndexable(index_target)) {
            assert(false);
            return nullptr;
        }

        this->index_->CheckExpression();

        return this->getElementTy(index_target);
    }

    TagDecl *FunctionCall::EvalBaseNameComponentType() {
        TagDecl *call_target = EvalBaseNameComponentType(function_call->function_name_, frontType);

        // 检查类型是否可调用

        if (!ASTAssert::TypeCanCallable(call_target)) {
            assert(false);
            return nullptr;
        }

        // 添加依赖库

        FunctorDecl *call_functor = call_target->as<FunctorDecl>();
        if (ASTAssert::IsStaticLibraryAPI(call_functor)) {
            APICommandDecl *api_command_decl = call_functor->as<APICommandDecl>();
            function_call->ast_context_->AddDependenceLibrary(api_command_decl->library_file_.string_);
        }

        this->CheckExpression(function_call);

        return ASTUtility::GetCallableReturnType(call_target);
    }

    TagDecl *Identifier::EvalBaseNameComponentType() {
        TagDecl *id_type = nullptr;

        // 如果frontType非空表明有父级类型，将从父级类型中查找子类型

        if (frontType) {
            if (StructureDecl *structure_decl = frontType->as<StructureDecl>()) {
                auto found = structure_decl->members_.find(identifier->name_.string_);
                if (found != structure_decl->members_.end()) {
                    id_type = found->second;
                } else {
                    assert(false);
                    return nullptr;
                }
            }

        }

            // 如果frontType为空则表明无父级类型，将从动态符号表中查询

        else {
            id_type = this->analysis_context_.QueryTagDeclFromDynSymbolTableWithName(identifier->name_.string_);

        }

        // 必须是实体定义

        if (TypeDecl *type_decl = id_type->as<TypeDecl>()) {
            if (FunctorDecl *functor_decl = type_decl->as<FunctorDecl>()) {
                identifier->function_ref_ = functor_decl;
                return functor_decl;
            } else {
                assert(false);
                return nullptr;
            }

        } else if (BaseVariDecl *base_vari_decl = id_type->as<BaseVariDecl>()) {
            identifier->reference_ = base_vari_decl;
            return base_vari_decl->vari_type_decl_;

        } else {
            assert(false);
            return nullptr;
        }
    }

    TypeDecl * HierarchyIdentifier::GetQualifiedType() {
        if (this->qualified_type_ == nullptr) {
            if (this->name_components_.empty()) {
                assert(false);
                return nullptr;
            }
            this->qualified_type_ = this->EvalComponentsType();
        }
        return this->qualified_type_;
    }

    TypeDecl * SematicAnalysis::QueryTypeDeclWithName(TranslateUnit *translateUnit, const StringRef &name, SematicAnalysisContext *context, BuiltinTypeDecl *hint) {
        if (name.empty()) {
            return hint ? hint : TU->getIntegerTy();
        }
        if (TagDecl *tag_decl = context->QueryTagDeclFromDynSymbolTableWithName(name)) {
            if (TypeDecl *type_decl = tag_decl->as<TypeDecl>()) {
                return type_decl;
            }
        }
        assert(false);
        return nullptr;
    }

    enum class MarkType { kChecking = 1, kChecked = 2 };

    bool SematicAnalysis::CheckRecursiveDefinition(TypeDecl * typeDecl, std::map<TypeDecl *, MarkType> &marks) {
        if (marks[typeDecl] == MarkType::kChecking) {
            assert(false);
            return false;
        } else if (marks[typeDecl] == MarkType::kChecked) {
            return true;
        } else {
            marks[typeDecl] = MarkType::kChecking;
            if (BuiltinTypeDecl *builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
                (void) builtin_type_decl;
            } else if (StructureDecl *structure_decl = typeDecl->as<StructureDecl>()) {
                for (auto &member_item : structure_decl->members_) {
                    CheckRecursiveDefinition(member_item.second->type_decl_ptr_, marks);
                }
            } else if (ArrayDecl *array_decl = typeDecl->as<ArrayDecl>()) {
                CheckRecursiveDefinition(array_decl->base_type_, marks);
            } else if (FunctorDecl *functor_decl = typeDecl->as<FunctorDecl>()) {
                CheckRecursiveDefinition(functor_decl->return_type_, marks);
                for (ParameterDecl *parameter_decl : functor_decl->parameters_) {
                    CheckRecursiveDefinition(parameter_decl->vari_type_decl_, marks);
                }
            }
            marks[typeDecl] = MarkType::kChecked;
            return true;
        }
    }

    bool SematicAnalysis::CheckRecursiveDefinition(TypeDecl * typeDecl) {
        std::map<TypeDecl *, MarkType> marks;
        return CheckRecursiveDefinition(typeDecl, marks);
    }

    bool SematicAnalysis::CheckIfStructureRecursiveReference() {
        bool all_check_success = true;
        for (auto & type_decl_item : TU->global_type_) {
            all_check_success &= this->CheckRecursiveDefinition(type_decl_item.second);
        }
        return all_check_success;
    }

}