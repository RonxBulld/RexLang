//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_STR2ATTR_H
#define OPENELANGUAGE_STR2ATTR_H

#include "ErrOr.h"
#include "StringRef.h"
#include "TypeDescription.h"
#include "NodeDecl.h"

namespace opene {

    class Str2Attr {
    public:
        static ErrOr<BuiltInTypeDecl::EnumOfBuiltInType> Name2BuiltInType(const StringRef &name);

        static ErrOr<type::AccessLevel> Name2AccessLevel(const StringRef &name);

        static ErrOr<type::ValueTransferMode> Name2ValueTransferMode(const StringRef &name);

        static ErrOr<std::vector<size_t>> Str2Dimension(const StringRef &str);
    };

}

#endif //OPENELANGUAGE_STR2ATTR_H
