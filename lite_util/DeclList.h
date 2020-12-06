//
// Created by rex on 2020/12/6.
//

#ifndef REXLANG_DECLLIST_H
#define REXLANG_DECLLIST_H

#include <vector>
#include <string>
#include <cassert>
#include "StringRef.h"

namespace rexlang {

    template <typename DeclTy>
    class DeclList {
    private:
        std::vector<DeclTy *> list_;

    public:
        typedef typename std::vector<DeclTy *>::iterator DeclListIter;
        typedef typename std::vector<DeclTy *>::const_iterator ConstDeclListIter;

        DeclTy *operator[](const char *       name)  const ;
        DeclTy *operator[](const std::string &name)  const ;
        DeclTy *operator[](const StringRef &  name)  const ;
        DeclTy *operator[](size_t             index) const ;

        template <typename IdxTy>
        bool has(IdxTy && key) const {
            return (bool) operator[](std::forward<IdxTy>(key));
        }

        bool add(DeclTy *declare) ;

        DeclListIter begin() ;
        DeclListIter end() ;
        ConstDeclListIter begin() const ;
        ConstDeclListIter end() const ;

    };

    template <typename DeclTy>
    DeclTy *DeclList<DeclTy>::operator[](const char *name) const {
        return operator[](StringPool::Create(name));
    }

    template <typename DeclTy>
    DeclTy *DeclList<DeclTy>::operator[](const std::string &name) const {
        return operator[](StringPool::Create(name));
    }

    template <typename DeclTy>
    DeclTy *DeclList<DeclTy>::operator[](const StringRef &name) const {
        for (DeclTy *decl : list_) {
            if (decl->getNameRef() == name) {
                return decl;
            }
        }
        return nullptr;
    }

    template <typename DeclTy>
    DeclTy *DeclList<DeclTy>::operator[](size_t index) const {
        if (index >= list_.size()) {
            assert(false);
            return nullptr;
        }
        return list_[index];
    }

    template <typename DeclTy>
    bool DeclList<DeclTy>::add(DeclTy *declare) {
        if (has(declare->getNameRef())) {
            assert(false);
            return false;
        }
        list_.push_back(declare);
        return true;
    }

    template <typename DeclTy>
    typename DeclList<DeclTy>::DeclListIter DeclList<DeclTy>::begin() { return list_.begin(); }

    template <typename DeclTy>
    typename DeclList<DeclTy>::DeclListIter DeclList<DeclTy>::end() { return list_.end(); }

    template <typename DeclTy>
    typename DeclList<DeclTy>::ConstDeclListIter DeclList<DeclTy>::begin() const { return list_.begin(); }

    template <typename DeclTy>
    typename DeclList<DeclTy>::ConstDeclListIter DeclList<DeclTy>::end() const { return list_.end(); }

}

#endif //REXLANG_DECLLIST_H
