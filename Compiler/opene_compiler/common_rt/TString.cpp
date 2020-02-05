//
// Created by rex on 2020/1/22.
//

#include "TString.h"

namespace opene {
    bool TString::operator<(const TString &rhs) const {
        return this->string_.operator<(rhs.string_);
    }

    bool TString::operator<(const StringRef &rhs) const {
        return this->string_.operator<(rhs);
    }
}