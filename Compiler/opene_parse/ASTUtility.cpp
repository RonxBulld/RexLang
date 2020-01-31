//
// Created by rex on 2020/1/28.
//

#include <queue>

#include "ASTUtility.h"
#include "ASTFetchSubnode.h"
#include "ASTAssert.h"
#include "ASTContext.h"
#include "Str2Attr.h"

namespace opene {

    void ASTUtility::FixNodeParent(Node *root) {
        std::queue<std::pair<const Node*, ASTFetchSubnode::ASTFetchResult>> workqueue;
        workqueue.push(std::pair(root, ASTFetchSubnode::ASTFetchResult()));
        while (workqueue.empty() == false) {
            std::pair<const Node*, ASTFetchSubnode::ASTFetchResult> work = workqueue.front();
            workqueue.pop();
            if (ASTFetchSubnode::FetchSubNode(work.first, work.second) == false) {
                continue;
            }
            for (const Node * node : work.second) {
                const_cast<Node *>(node)->parent_node_ = const_cast<Node *>(work.first);
                workqueue.push(std::pair(node, ASTFetchSubnode::ASTFetchResult()));
            }
        }
    }

    BaseVariDecl * ASTUtility::FindVariableDeclareInASTWithHierarchyName(HierarchyIdentifier *hierarchyIdentifier) {
        // 判断是否有效
        assert(hierarchyIdentifier->name_components_.size() > 0);
        BaseVariDecl *vari_decl = nullptr;
        // 找起点
        NameComponentPtr base_component = hierarchyIdentifier->name_components_.front();
        ErrOr<StringRef> base_name = ASTUtility::GetNameComponentQualifiedName(base_component);
        if (base_name.NoError() == false) { return nullptr; }

        const Node *nearstScope = hierarchyIdentifier;
        const BaseVariDecl *base_vari_decl = nullptr;
        while (base_vari_decl == nullptr) {
            nearstScope = ASTUtility::FindNearstScope(nearstScope->parent_node_);
            if (nearstScope == nullptr) {
                return nullptr;
            }
            base_vari_decl = ASTUtility::FindVariableDeclInScopeWithName(nearstScope, base_name.Value());
        }

        // 找递进
        for (size_t idx = 1; idx < hierarchyIdentifier->name_components_.size(); idx++) {
            base_name = ASTUtility::GetNameComponentQualifiedName(hierarchyIdentifier->name_components_[idx]);
            if (base_name.NoError() == false) { return nullptr; }
            base_vari_decl = ASTUtility::FindVariableWithNameInStructureType(base_vari_decl->type_decl_ptr_, base_name.Value());
            assert(base_vari_decl);
        }
        return base_vari_decl;
    }

    TypeDecl *ASTUtility::GetVariableQualifiedTypeWithHierarchyName(HierarchyIdentifier *hierarchyIdentifier) {
        // 首先查找引用目标变量定义
        const BaseVariDecl *vari_decl = ASTUtility::FindVariableDeclareInASTWithHierarchyName(hierarchyIdentifier);
        if (vari_decl == nullptr) { return nullptr; }
        // 判断数组定义和引用情况
        ErrOr<std::vector<size_t>> type_indexes = ASTUtility::GetTypeIndexList(vari_decl->type_decl_ptr_);
        if (type_indexes.NoError() == false) { return nullptr; }
        ErrOr<std::vector<Expression *>> ref_indexes = ASTUtility::GetNameComponentIndexList(hierarchyIdentifier->name_components_.back());
        if (ref_indexes.NoError() == false) { return nullptr; }
        if (ref_indexes.Value().empty()) {      // 实际未索引，定义即引用
            return vari_decl->type_decl_ptr_;
        } else {    // 索引引用
            if (type_indexes.Value().empty()) {    // 类型不可索引
                assert(false);
                return nullptr;
            } else { // 类型可索引
                if (ASTAssert::IsFixedDimArray(vari_decl->type_decl_ptr_)) {    // 判断维度约束
                    if (type_indexes.Value().size() < ref_indexes.Value().size()) {
                        assert(false);
                        return nullptr;
                    }
                }
                // 有索引则认为是元素索引而非片选
                return ASTUtility::GetIndexableTypeElement(vari_decl->type_decl_ptr_);
            }
        }
    }

    ErrOr<StringRef> ASTUtility::GetNameComponentQualifiedName(NameComponent *nameComponent) {
        NameComponent *base_name_component = ASTUtility::GetNameComponentQualifiedBase(nameComponent);
        if (base_name_component) {
            return MakeNoErrVal<StringRef>(base_name_component->name_.string_);
        } else {
            assert(false);
            return ErrOr<StringRef>::CreateError(1);
        }
    }

    NameComponent *ASTUtility::GetNameComponentQualifiedBase(NameComponent *nameComponent) {
        if (nameComponent->name_.string_.empty() == false && nameComponent->base_ == nullptr && nameComponent->index_ == nullptr) {
            return nameComponent;
        } else if (nameComponent->name_.string_.empty() == true && nameComponent->base_ != nullptr && nameComponent->index_) {
            return ASTUtility::GetNameComponentQualifiedBase(nameComponent->base_);
        } else {
            assert(false);
            return nullptr;
        }
    }

    Node * ASTUtility::FindNearstScope(Node *base) {
        while (base) {
            if (base->node_type_ == NodeType::kNTyFunctionDecl) {
                return base;
            } else if (base->node_type_ == NodeType::kNTyProgSetDecl) {
                return base;
            } else if (base->is<SourceFile>()) {
                return base;
            } else if (base->node_type_ == NodeType::kNTyTranslateUnit) {
                return base;
            } else {
                base = base->parent_node_;
            }
        }
        return nullptr;
    }

    BaseVariDecl * ASTUtility::FindVariableDeclInScopeWithName(Node *scope, const StringRef &name) {
        if (const FunctionDecl *sub_prog_decl = scope->as<FunctionDecl>()) {
            // 1. 查找局部变量
            for (auto & item : sub_prog_decl->local_vari_) {
                if (item.first == name) {
                    return item.second;
                }
            }
            // 2. 查找全局变量
            for (ParameterDecl *parameter_decl : sub_prog_decl->parameters_) {
                if (parameter_decl->name_.string_ == name) {
                    return parameter_decl;
                }
            }
        } else if (ProgSetDecl *prog_set_decl = scope->as<ProgSetDecl>()) {
            // 1. 查找文件变量
            for (auto & item : prog_set_decl->file_static_variables_) {
                if (item.first == name) {
                    return item.second;
                }
            }
        } else if (SourceFile *source_file = scope->as<SourceFile>()) {
        } else if (TranslateUnit *translate_unit = scope->as<TranslateUnit>()) {
            // 1. 全局变量索引表
            for (auto & item : translate_unit->global_variables_) {
                if (item.first == name) {
                    return item.second;
                }
            }
        } else {
            assert(false);
        }
        return nullptr;
    }

    BaseVariDecl *ASTUtility::FindVariableWithNameInStructureType(TypeDecl *typeDecl, const StringRef &variable_name) {
        if (const StructureDecl *structure_decl = typeDecl->as<StructureDecl>()) {
            for (auto & item : structure_decl->members_) {
                if (item.first == variable_name) {
                    return item.second;
                }
            }
            return nullptr;
        } else {
            return nullptr;
        }
    }

    ErrOr<std::vector<Expression *>> ASTUtility::GetNameComponentIndexList(NameComponent *nameComponent) {
        std::vector<Expression *> indexes;
        while (nameComponent && nameComponent->index_ != nullptr) {
            indexes.push_back(nameComponent->index_);
            nameComponent = nameComponent->base_;
        }
        return MakeNoErrVal(indexes);
    }

    ErrOr<std::vector<size_t>> ASTUtility::GetTypeIndexList(TypeDecl *typeDecl) {
        if (ASTAssert::TypeCanIndexable(typeDecl) == false) {
            return MakeNoErrVal(std::vector<size_t>{});
        }
        if (const ArrayDecl *array_decl = typeDecl->as<ArrayDecl>()) {
            // 变量定义为数组
            return MakeNoErrVal(array_decl->dimensions_);
        } else if (const BuiltinTypeDecl *builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            if (builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet) {
                // 内置类型只有字节集能够被索引
                return MakeNoErrVal(std::vector<size_t>{0});
            } else {
                assert(false);
                return ErrOr<std::vector<size_t>>::CreateError(1);
            }
        } else {
            assert(false);
            return ErrOr<std::vector<size_t>>::CreateError(1);
        }
    }

    TypeDecl * ASTUtility::GetIndexableTypeElement(TypeDecl *typeDecl) {
        if (ASTAssert::TypeCanIndexable(typeDecl) == false) {
            return nullptr;
        }
        if (const BuiltinTypeDecl *builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            if (builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet) {
                TranslateUnit *translate_unit = ASTUtility::FindSpecifyTypeParent<TranslateUnit>(typeDecl);
                return ASTUtility::QueryBuiltinTypeWithEnum(translate_unit, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeChar);
            } else {
                return nullptr;
            }
        } else if (const ArrayDecl *array_decl = typeDecl->as<ArrayDecl>()) {
            do {
                typeDecl = array_decl->base_type_;
            } while (array_decl = typeDecl->as<ArrayDecl>());
            return typeDecl;
        }
    }

    TypeDecl * ASTUtility::QueryBuiltinTypeWithEnum(TranslateUnit *translateUnit, BuiltinTypeDecl::EnumOfBuiltinType type_enum) {
            StringRef && type_name = translateUnit->ast_context_->CreateString(Str2Attr::BuiltinType2Name(type_enum).Value());
            TypeDecl * type_decl = ASTUtility::QueryTypeDeclWithName(translateUnit, type_name);
            assert(type_decl);
            return type_decl;
    }

    TypeDecl * ASTUtility::QueryTypeDeclWithName(TranslateUnit *translateUnit, const StringRef &name) {
        auto found = translateUnit->global_type_.find(name);
        if (found != translateUnit->global_type_.end()) {
            return found->second;
        } else {
            assert(false);
            return nullptr;
        }
    }

    FunctorDecl * ASTUtility::GetFunctionDeclare(FunctionCall *functionCall) {
        TranslateUnit *translate_unit = ASTUtility::FindSpecifyTypeParent<TranslateUnit>(functionCall);
        if (functionCall->function_name_->name_.string_.empty() || (functionCall->function_name_->base_ != nullptr || functionCall->function_name_->index_ != nullptr)) {
            assert(false);
            return nullptr;
        }
        auto found = translate_unit->functor_declares_.find(functionCall->function_name_->name_.string_);
        if (found == translate_unit->functor_declares_.end()) {
            assert(false);
            return nullptr;
        }
        functionCall->functor_declare_ = found->second;
        return functionCall->functor_declare_;
    }

    FunctorDecl *ASTUtility::GetFunctionDeclare(FuncAddrExpression *funcAddrExpression) {
        TranslateUnit *translate_unit = ASTUtility::FindSpecifyTypeParent<TranslateUnit>(funcAddrExpression);
        if (funcAddrExpression->function_name_.string_.empty()) {
            assert(false);
            return nullptr;
        }
        auto found = translate_unit->functor_declares_.find(funcAddrExpression->function_name_.string_);
        if (found == translate_unit->functor_declares_.end()) {
            assert(false);
            return nullptr;
        }
        funcAddrExpression->functor_declare_ = found->second;
        return funcAddrExpression->functor_declare_;
    }
}