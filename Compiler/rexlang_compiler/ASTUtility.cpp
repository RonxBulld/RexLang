//
// Created by rex on 2020/1/28.
//

#include <queue>

#include "ASTUtility.h"
#include "utilities/ASTFetchSubnode.h"
#include "ASTAssert.h"
#include "ASTContext.h"
#include "utilities/Str2Attr.h"
#include "TypeAssert.h"

namespace rexlang {

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

    /*TagDecl * ASTUtility::GetQualifiedTypeWithHierarchyName(HierarchyIdentifier *hierarchyIdentifier) {
        // 首先查找引用目标变量定义
        const BaseVariDecl *vari_decl = ASTUtility::FindDeclareInASTWithHierarchyName(hierarchyIdentifier);
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
    }*/

    ErrOr<StringRef> ASTUtility::GetNameComponentQualifiedName(NameComponent *nameComponent) {
        Identifier *base_name_component = ASTUtility::GetNameComponentQualifiedBase(nameComponent);
        if (base_name_component) {
            return MakeNoErrVal<StringRef>(base_name_component->name_.string_);
        } else {
            assert(false);
            return ErrOr<StringRef>::CreateError(1);
        }
    }

    Identifier *ASTUtility::GetNameComponentQualifiedBase(NameComponent *nameComponent) {
        if (Identifier *identifier = nameComponent->as<Identifier>()) {
            return identifier;
        } else if (ArrayIndex *array_index = nameComponent->as<ArrayIndex>()) {
            return ASTUtility::GetNameComponentQualifiedBase(array_index->base_);
        } else if (FunctionCall *function_call = nameComponent->as<FunctionCall>()) {
            return ASTUtility::GetNameComponentQualifiedBase(function_call->function_name_);
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

    NameComponent *ArrayIndex::GetIndexBase() const {
        NameComponent *base = nullptr;
        const ArrayIndex *arrayIndex = this;
        do{
            base = arrayIndex->base_;
        } while ((arrayIndex = base->as<ArrayIndex>()));
        return base;
    }

    ErrOr<std::vector<Expression *>> ASTUtility::GetArrayIndexIndexList(ArrayIndex *arrayIndex) {
        std::vector<Expression *> indexes;
        while (arrayIndex) {
            indexes.push_back(arrayIndex->index_);
            arrayIndex = arrayIndex->base_->as<ArrayIndex>();
        }
        return MakeNoErrVal(indexes);
    }

    FunctorDecl * ASTUtility::GetFunctionDeclare(FunctionCall *functionCall) {
        TranslateUnit *translate_unit = ASTUtility::FindSpecifyTypeParent<TranslateUnit>(functionCall);
        NameComponent *func_name = functionCall->function_name_;
        if (Identifier *identifier = func_name->as<Identifier>()) {
            // 直接函数调用
            auto found = translate_unit->functor_declares_.find(identifier->name_.string_);
            if (found == translate_unit->functor_declares_.end()) {
                assert(false);
                return nullptr;
            }
            functionCall->functor_declare_ = found->second;
            return functionCall->functor_declare_;
        } else {
            // 间接函数调用
            assert(false);
            return nullptr;
        }
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