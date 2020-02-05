//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_STR2ATTR_H
#define OPENELANGUAGE_STR2ATTR_H

#include "common_rt/ErrOr.h"
#include "common_rt/StringRef.h"
#include "NodeDecl.h"

namespace opene {

    class Str2Attr {
    public:
        static ErrOr<BuiltinTypeDecl::EnumOfBuiltinType> Name2BuiltinType(const StringRef &name);

        static ErrOr<std::string> BuiltinType2Name(BuiltinTypeDecl::EnumOfBuiltinType type);

        static ErrOr<AccessLevel> Name2AccessLevel(const StringRef &name);

        static ErrOr<ValueTransferMode> Name2ValueTransferMode(const StringRef &name);

        static ErrOr<std::vector<size_t>> Str2Dimension(const StringRef &str);
    };

}

#endif //OPENELANGUAGE_STR2ATTR_H
