//
// Created by rex on 2020/1/28.
//

#include <queue>

#include "ASTUtility.h"
#include "ASTFetchSubnode.h"
#include "ASTAssert.h"

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

    const BaseVariDecl *ASTUtility::FindVariableDeclareInASTWithHierarchyName(const HierarchyIdentifier *hierarchyIdentifier) {
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

    TypeDecl *ASTUtility::GetVariableQualifiedTypeWithHierarchyName(const HierarchyIdentifier *hierarchyIdentifier) {
        const BaseVariDecl *vari_decl = ASTUtility::FindVariableDeclareInASTWithHierarchyName(hierarchyIdentifier);
        if (vari_decl == nullptr) { return nullptr; }
        // 判断数组定义和引用情况
        ErrOr<std::vector<size_t>> type_indexes = ASTUtility::GetTypeIndexList(vari_decl);
        if (type_indexes.NoError() == false) { return nullptr; }
        ErrOr<std::vector<Expression *>> ref_indexes = ASTUtility::GetNameComponentIndexList(hierarchyIdentifier->name_components_.back());
        if (ref_indexes.NoError() == false) { return nullptr; }
        if (type_indexes.Value().empty()) {   // 类型不可索引
            if (ref_indexes.Value().empty()) {  // 实际未索引
                return vari_decl->type_decl_ptr_;
            } else {    // 实际索引
                assert(false);
                return nullptr;
            }
        }
        // 判断维度约束
        if (ASTAssert::IsFixedDimArray(vari_decl)) {
            if (type_indexes.Value().size() != ref_indexes.Value().size()) {
                assert(false);
                return nullptr;
            }
        }
        // 对于数组，利用ArrayDecl构建新的类型描述符号
        // TODO: 是的，这里会发生内存泄露，但是我不在乎！
        ArrayDecl *array_decl = CreateNode<ArrayDecl>(vari_decl->ast_context_);
        
        return array_decl;
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

    const Node *ASTUtility::FindNearstScope(const Node *base) {
        while (base) {
            if (base->node_type_ == NodeType::kNTySubProgDecl) {
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

    const BaseVariDecl *ASTUtility::FindVariableDeclInScopeWithName(const Node *scope, const StringRef &name) {
        if (const SubProgDecl *sub_prog_decl = scope->as<SubProgDecl>()) {
            // 1. 查找局部变量
            for (auto & item : sub_prog_decl->local_vari_) {
                if (item.first == name) {
                    return item.second;
                }
            }
            // 2. 查找全局变量
            for (const ParameterDecl *parameter_decl : sub_prog_decl->parameters_) {
                if (parameter_decl->name_.string_ == name) {
                    return parameter_decl;
                }
            }
        } else if (const ProgSetDecl *prog_set_decl = scope->as<ProgSetDecl>()) {
            // 1. 查找文件变量
            for (auto & item : prog_set_decl->file_static_variables_) {
                if (item.first == name) {
                    return item.second;
                }
            }
        } else if (const SourceFile *source_file = scope->as<SourceFile>()) {
        } else if (const TranslateUnit *translate_unit = scope->as<TranslateUnit>()) {
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

    const BaseVariDecl *ASTUtility::FindVariableWithNameInStructureType(const TypeDecl *typeDecl, const StringRef &variable_name) {
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

    ErrOr<std::vector<Expression *>> ASTUtility::GetNameComponentIndexList(const NameComponent *nameComponent) {
        std::vector<Expression *> indexes;
        while (nameComponent && nameComponent->index_ != nullptr) {
            indexes.push_back(nameComponent->index_);
            nameComponent = nameComponent->base_;
        }
        return MakeNoErrVal(indexes);
    }

    ErrOr<std::vector<size_t>> ASTUtility::GetTypeIndexList(const TagDecl *tagDecl) {
        if (ASTAssert::TypeCanIndexable(tagDecl) == false) {
            return MakeNoErrVal(std::vector<size_t>{});
        }
        if (const VariableDecl *variable_decl = tagDecl->as<VariableDecl>()) {
            // 是变量定义并且定义为多维
            return MakeNoErrVal(variable_decl->dimensions_);
        } else if (const BuiltinTypeDecl *builtin_type_decl = tagDecl->as<BuiltinTypeDecl>()) {
            // 内置类型只有字节集能够被索引
            return MakeNoErrVal(std::vector<size_t>{0});
        } else {
            assert(false);
            return ErrOr<std::vector<size_t>>::CreateError(1);
        }
    }

}