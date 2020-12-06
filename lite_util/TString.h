//
// Created by rex on 2020/1/22.
//

#ifndef REXLANG_TSTRING_H
#define REXLANG_TSTRING_H

#include "StringRef.h"
#include "../Compiler/rexlang_compiler/utilities/Location.h"

namespace rexlang {

    class TString {
    public:
        StringRef string_;
        size_t location_;
    public:
        TString() ;
        TString(StringRef string) ;
        TString(StringRef string, size_t location) ;
    public:
        bool operator<(const TString &rhs) const;
        bool operator<(const StringRef &rhs) const;

    };

}

#endif //REXLANG_TSTRING_H
