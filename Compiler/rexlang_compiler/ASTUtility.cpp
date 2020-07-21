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

    ErrOr<std::vector<Expression *>> ArrayIndex::getIndexesList() const {
        std::vector<Expression *> indexes;
        const ArrayIndex *ptr = this;
        while (ptr) {
            indexes.push_back(ptr->index_);
            ptr = ptr->base_->as<ArrayIndex>();
        }
        return MakeNoErrVal(indexes);
    }

}