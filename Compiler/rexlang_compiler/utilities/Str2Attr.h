//
// Created by rex on 2020/1/23.
//

#ifndef REXLANG_STR2ATTR_H
#define REXLANG_STR2ATTR_H

#include "../common_rt/ErrOr.h"
#include "../common_rt/StringRef.h"
#include "../NodeDecl.h"

namespace rexlang {

    extern const std::map<std::string, BuiltinTypeDecl::EnumOfBuiltinType> builtin_type_map;

    class Str2Attr {
    public:

        static ErrOr<BuiltinTypeDecl::EnumOfBuiltinType> Name2BuiltinType(const StringRef &name);

        static ErrOr<std::string> BuiltinType2Name(BuiltinTypeDecl::EnumOfBuiltinType type);

        static ErrOr<AccessLevel> Name2AccessLevel(const StringRef &name);

        static ErrOr<ValueTransferMode> Name2ValueTransferMode(const StringRef &name);

        static ErrOr<std::vector<size_t>> Str2Dimension(const StringRef &str);
    };

}

#endif //REXLANG_STR2ATTR_H
