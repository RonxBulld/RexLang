//
// Created by rex on 2020/1/22.
//

#ifndef OPENELANGUAGE_TSTRING_H
#define OPENELANGUAGE_TSTRING_H

#include "StringRef.h"
#include "Location.h"

namespace opene {

    class TString {
    public:
        StringRef string_;
        size_t location_;
    public:
        bool operator<(const TString &rhs) const;
    };

}

#endif //OPENELANGUAGE_TSTRING_H
