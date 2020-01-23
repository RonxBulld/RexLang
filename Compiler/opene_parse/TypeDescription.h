//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_TYPEDESCRIPTION_H
#define OPENELANGUAGE_TYPEDESCRIPTION_H

#include "TString.h"

namespace opene {

    namespace type {

        enum class EnumOfBuiltInType {
            kBTypeChar,     // 字节型
            kBTypeInteger,  // 整数型
            kBTFloat,       // 小数型
            kBTBool,        // 逻辑型
            kBTString,      // 文本型
            kBTDataSet,     // 字节集
            kBTShort,       // 短整型
            kBTLong,        // 长整型
            kBTDatatime,    // 日期时间型
            kBTFuncPtr,     // 子程序指针
            kBTDouble,      // 双精度小数型
        };

        enum class AccessLevel {
            kALPublic,      // 公开
            kALPrivate,     // 私有
        };

        class TypeDescription {
        public:
            TString name_;
        };

        class BuiltInTypeDescription {
        public:
            EnumOfBuiltInType built_in_type_ = EnumOfBuiltInType::kBTypeInteger;
        };

        class DataStructDescription : public TypeDescription {
        public:
            AccessLevel access_level_ = AccessLevel::kALPublic;
            TString comment_;
            std::map<TString, TypeDescription *> members_;
        };

        class FunctionDescription : public TypeDescription {
        public:
            TypeDescription *return_type_ = nullptr;
        };

    }

}

#endif //OPENELANGUAGE_TYPEDESCRIPTION_H
