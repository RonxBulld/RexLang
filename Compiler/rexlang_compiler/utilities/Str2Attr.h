//
// Created by rex on 2020/1/23.
//

#ifndef REXLANG_STR2ATTR_H
#define REXLANG_STR2ATTR_H

#include "../../../lite_util/ErrOr.h"
#include "../../../lite_util/StringRef.h"
#include "../NodeDecl.h"

namespace rexlang {

//    extern const std::map<std::string, EnumOfBuiltinType> builtin_type_map;

    class Str2Attr {
    public:

        static ErrOr<AccessLevel>         name2AccessLevel      (const StringRef &name);
        static ErrOr<ValueTransferMode>   name2ValueTransferMode(const StringRef &name);
        static ErrOr<std::vector<size_t>> str2Dimension         (const StringRef &str);

        static bool isNameOfReference(const StringRef &str) ;
        static bool isNameOfNullable (const StringRef &str) ;
        static bool isNameOfArray    (const StringRef &str) ;

    };

}

#endif //REXLANG_STR2ATTR_H
