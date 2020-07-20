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

    /***********************************************************
     * 获取组件的确切名称对象
     ***********************************************************/

    Identifier *Identifier  ::getBaseId() const { return const_cast<Identifier *>(this); }
    Identifier *ArrayIndex  ::getBaseId() const { return this->base_->getBaseId(); }
    Identifier *FunctionCall::getBaseId() const { return this->function_name_->getBaseId(); }

    NameComponent *ArrayIndex::getIndexBase() const {
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