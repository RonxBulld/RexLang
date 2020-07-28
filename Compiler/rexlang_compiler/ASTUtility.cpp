//
// Created by rex on 2020/1/28.
//

#include <queue>

#include "ASTUtility.h"
#include "ASTContext.h"
#include "utilities/Str2Attr.h"
#include "TypeAssert.h"

namespace rexlang {

    /***********************************************************
     * 获取组件的确切名称对象
     ***********************************************************/

    IdentRefer *IdentRefer  ::getBaseId() const { return const_cast<IdentRefer *>(this); }
    IdentRefer *ArrayIndex  ::getBaseId() const { return this->base_->getBaseId(); }
    IdentRefer *FunctionCall::getBaseId() const { return this->function_name_->getBaseId(); }

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

    int MemberVariableDecl::indexOfStruct() {
        if (index_of_struct_ >= 0) {
            int tmp = index_of_struct_;
            assert((index_of_struct_ = -1, tmp == indexOfStruct()));
            return index_of_struct_;
        }
        else {
            StructureDecl *structure_decl = getParent()->as<StructureDecl>();
            int index = structure_decl->indexMemberOfThis(this);
            assert(index >= 0);
            index_of_struct_ = index;
            return index;
        }
    }

    bool StructureDecl::isMemberOfThis(MemberVariableDecl *memberVariDecl) const {
        return indexMemberOfThis(memberVariDecl) >= 0;
    }

    int StructureDecl::indexMemberOfThis(MemberVariableDecl *memberVariDecl) const {
        int idx = 0;
        for (auto & member_item : members_) {
            if (member_item.second == memberVariDecl) {
                return idx;
            }
            idx++;
        }
        return -1;
    }
}