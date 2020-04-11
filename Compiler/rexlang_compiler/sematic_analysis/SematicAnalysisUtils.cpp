//
// Created by rex on 2020/2/4.
//

#include "SematicAnalysis.h"
#include "../TypeAssert.h"
#include "../ASTAssert.h"
#include "../ASTUtility.h"
#include "../ASTContext.h"
#include "../utilities/Str2Attr.h"

namespace rexlang {

    /*
     * 递归推断名称组件类型
     */
    TypeDecl * SematicAnalysis::EvalBaseNameComponentType(NameComponent *nameComponent, TypeDecl *frontType) {
        assert(nameComponent);

        if (ArrayIndex *array_index = nameComponent->as<ArrayIndex>()) {
            NameComponent *array_base = ASTUtility::GetArrayIndexBase(array_index);
            TypeDecl *index_target = EvalBaseNameComponentType(array_base, frontType);
            if (!index_target) {
                assert(false);
                return nullptr;
            }

            // 检查类型是否可索引

            if (!ASTAssert::TypeCanIndexable(index_target)) {
                assert(false);
                return nullptr;
            }

            this->CheckExpression(array_index->index_);

            return this->GetIndexableTypeElement(index_target);

        } else if (FunctionCall *function_call = nameComponent->as<FunctionCall>()) {
            TypeDecl *call_target = EvalBaseNameComponentType(function_call->function_name_, frontType);

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

        } else if (Identifier *identifier = nameComponent->as<Identifier>()) {
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
                return base_vari_decl->type_decl_ptr_;

            } else {
                assert(false);
                return nullptr;
            }

        } else {
            assert(false);
            return nullptr;
        }
    }

    TypeDecl * SematicAnalysis::GetHierarchyIdentifierQualifiedType(HierarchyIdentifier *hierarchyIdentifier) {
        if (hierarchyIdentifier->qualified_type_ == nullptr) {
            if (hierarchyIdentifier->name_components_.empty()) {
                assert(false);
                return nullptr;
            }
            TypeDecl *type = nullptr;
            for (NameComponent *name_component : hierarchyIdentifier->name_components_) {
                type = EvalBaseNameComponentType(name_component, type);
                if (!type) {
                    assert(false);
                    return nullptr;
                }
            }
            hierarchyIdentifier->qualified_type_ = type;
        }
        return hierarchyIdentifier->qualified_type_;
    }

    BuiltinTypeDecl *SematicAnalysis::QueryBuiltinTypeWithEnum(TranslateUnit *translateUnit, BuiltinTypeDecl::EnumOfBuiltinType type_enum) {
        StringRef &&type_name = translateUnit->ast_context_->CreateString(Str2Attr::BuiltinType2Name(type_enum).Value());
        BuiltinTypeDecl *builtin_type_decl = this->QueryTypeDeclWithName(translateUnit, type_name, &this->analysis_context_)->as<BuiltinTypeDecl>();
        assert(builtin_type_decl);
        return builtin_type_decl;
    }

    TypeDecl * SematicAnalysis::GetIndexableTypeElement(TypeDecl *typeDecl) {
        if (ASTAssert::TypeCanIndexable(typeDecl) == false) {
            return nullptr;
        }
        if (const BuiltinTypeDecl *builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            if (builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet) {
                TranslateUnit *translate_unit = ASTUtility::FindSpecifyTypeParent<TranslateUnit>(typeDecl);
                return this->QueryBuiltinTypeWithEnum(translate_unit, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeChar);
            } else {
                return nullptr;
            }

        } else if (const ArrayDecl *array_decl = typeDecl->as<ArrayDecl>()) {
            do {
                typeDecl = array_decl->base_type_;
            } while (array_decl = typeDecl->as<ArrayDecl>());
            return typeDecl;

        } else {
            assert(false);
            return nullptr;
        }
    }

    TypeDecl * SematicAnalysis::QueryTypeDeclWithName(TranslateUnit *translateUnit, const StringRef &name, SematicAnalysisContext *context, BuiltinTypeDecl::EnumOfBuiltinType hint) {
        if (name.empty()) {
            // 类型默认为整数型
            return this->QueryBuiltinTypeWithEnum(translateUnit, hint);
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
                    CheckRecursiveDefinition(parameter_decl->type_decl_ptr_, marks);
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
        for (auto & type_decl_item : this->translate_unit_->global_type_) {
            all_check_success &= this->CheckRecursiveDefinition(type_decl_item.second);
        }
        return all_check_success;
    }

}