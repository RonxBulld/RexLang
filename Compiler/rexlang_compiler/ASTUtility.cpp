//
// Created by rex on 2020/1/28.
//

#include <queue>

#include "ASTUtility.h"
#include "ASTContext.h"
#include "utilities/Str2Attr.h"

namespace rexlang {

    /***********************************************************
     * 获取组件的确切名称对象
     ***********************************************************/

    IdentRefer *IdentRefer  ::getBaseId() const { return const_cast<IdentRefer *>(this); }
    IdentRefer *ArrayIndex  ::getBaseId() const { return this->getIndexBase()->getBaseId(); }
    IdentRefer *FunctionCall::getBaseId() const { return this->name_->getBaseId(); }

    Expression * ArrayIndex::getIndex() const { return index_; }

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

    int MemberVariableDecl::indexOfStruct() const {
        if (StructureDecl *structure_decl = rtti::dyn_cast<StructureDecl>(getParent())) {
            const NamedOrderDict<MemberVariableDecl *> &elements = structure_decl->elements();
            int index = 0;
            for (auto &item : elements) {
                if (item.second == this) { return index; }
                index++;
            }
            assert(false);
            return -1;
        } else {
            assert(false);
            return -1;
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