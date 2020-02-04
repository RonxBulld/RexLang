//
// Created by rex on 2020/2/4.
//

#include "SematicAnalysis.h"
#include "TypeAssert.h"
#include "ASTAssert.h"
#include "ASTUtility.h"
#include "ASTContext.h"
#include "Str2Attr.h"

namespace opene {

    /*
     * 递归推断名称组件类型
     */
    TypeDecl * SematicAnalysis::EvalBaseNameComponentType(NameComponent *nameComponent, TypeDecl *frontType) {
        assert(nameComponent);
        if (ArrayIndex *array_index = nameComponent->as<ArrayIndex>()) {
            TypeDecl *index_target = EvalBaseNameComponentType(ASTUtility::GetArrayIndexBase(array_index), frontType);
            if (!index_target) { return nullptr; }
            // 检查类型是否可索引
            if (ASTAssert::TypeCanIndexable(index_target) == false) {
                assert(false);
                return nullptr;
            }
            return this->GetIndexableTypeElement(index_target);

        } else if (FunctionCall *function_call = nameComponent->as<FunctionCall>()) {
            TypeDecl *call_target = EvalBaseNameComponentType(function_call->function_name_, frontType);
            // 检查类型是否可调用
            if (ASTAssert::TypeCanCallable(call_target) == false) {
                assert(false);
                return nullptr;
            }
            return ASTUtility::GetCallableReturnType(call_target);

        } else if (Identifier *identifier = nameComponent->as<Identifier>()) {
            // 必须是实体定义
            TagDecl *id_type = nullptr;
            if (frontType) {
                // 如果frontType非空表明有父级类型，将从父级类型中查找子类型
                if (StructureDecl *structure_decl = frontType->as<StructureDecl>()) {
                    auto found = structure_decl->members_.find(identifier->name_.string_);
                    if (found != structure_decl->members_.end()) {
                        id_type = found->second;
                    } else {
                        assert(false);
                        return nullptr;
                    }
                }
            } else {
                // 如果frontType为空则表明无父级类型，将从动态符号表中查询
                id_type = this->analysis_context_.QueryTagDeclFromDynSymbolTableWithName(identifier->name_.string_);
            }
            if (TypeDecl *type_decl = id_type->as<TypeDecl>()) {
                return type_decl;
            } else if (BaseVariDecl *base_vari_decl = id_type->as<BaseVariDecl>()) {
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

    TypeDecl * SematicAnalysis::QueryTypeDeclWithName(TranslateUnit *translateUnit, const StringRef &name, SematicAnalysisContext *context) {
        if (name.empty()) {
            // 类型默认为整数型
            return this->QueryBuiltinTypeWithEnum(translateUnit, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger);
        }
        if (TagDecl *tag_decl = context->QueryTagDeclFromDynSymbolTableWithName(name)) {
            if (TypeDecl *type_decl = tag_decl->as<TypeDecl>()) {
                return type_decl;
            }
        }
        assert(false);
        return nullptr;
    }

}