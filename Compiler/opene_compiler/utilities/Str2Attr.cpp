//
// Created by rex on 2020/1/23.
//

#include <cassert>
#include <regex>
#include <string>
#include "Str2Attr.h"

namespace opene {
    const std::map<std::string, BuiltinTypeDecl::EnumOfBuiltinType> builtin_type_map {
            {std::string(u8"<空类型>"),    BuiltinTypeDecl::EnumOfBuiltinType::kBTypeVoid},
            {std::string(u8"通用型"),    BuiltinTypeDecl::EnumOfBuiltinType::kBTTypeCommon},
            {std::string(u8"字节型"),    BuiltinTypeDecl::EnumOfBuiltinType::kBTypeChar},
            {std::string(u8"整数型"),    BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger},
            {std::string(u8"小数型"),    BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFloat},
            {std::string(u8"逻辑型"),    BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool},
            {std::string(u8"文本型"),    BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString},
            {std::string(u8"字节集"),    BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet},
            {std::string(u8"短整型"),    BuiltinTypeDecl::EnumOfBuiltinType::kBTypeShort},
            {std::string(u8"长整数型"),  BuiltinTypeDecl::EnumOfBuiltinType::kBTypeLong},
            {std::string(u8"日期时间型"),  BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatetime},
            {std::string(u8"子程序指针"),  BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFuncPtr},
            {std::string(u8"双精度小数型"), BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDouble},
    };

    ErrOr<BuiltinTypeDecl::EnumOfBuiltinType> Str2Attr::Name2BuiltinType(const StringRef &name) {
        auto found = builtin_type_map.find(name.str());
        if (found != builtin_type_map.end()) {
            return MakeNoErrVal(found->second);
        } else {
            return CreateError<BuiltinTypeDecl::EnumOfBuiltinType>(1);
        }
    }

    ErrOr<std::string> Str2Attr::BuiltinType2Name(BuiltinTypeDecl::EnumOfBuiltinType type) {
        for (const auto & item : builtin_type_map) {
            if (item.second == type) {
                return MakeNoErrVal(item.first);
            }
        }
        return CreateError<std::string>(1);
    }

    ErrOr<AccessLevel> Str2Attr::Name2AccessLevel(const StringRef &name) {
        if (name == u8"公开") {
            return ErrOr<AccessLevel>(AccessLevel::kALPublic);
        } else if (name == u8"") {
            return ErrOr<AccessLevel>(AccessLevel::kALPrivate);
        } else {
            assert(false);
            return ErrOr<AccessLevel>::CreateError(1);
        }
    }

    ErrOr<ValueTransferMode> Str2Attr::Name2ValueTransferMode(const StringRef &name) {
        if (name == u8"传址") {
            return ErrOr<ValueTransferMode>(ValueTransferMode::kVTMReference);
        } else if (name == u8"") {
            return ErrOr<ValueTransferMode>(ValueTransferMode::kVTMValue);
        } else {
            assert(false);
            return ErrOr<ValueTransferMode>::CreateError(1);
        }
    }

    ErrOr<std::vector<size_t>> Str2Attr::Str2Dimension(const StringRef &str) {
        std::string s = str.str();
        std::vector<size_t> dims;
        size_t n = 0;
        int status = 0;
        for (char c : s) {
            if (status == 0) {
                if (c == '"') {
                    status = 1;
                } else {
                    break;
                }
            } else if (status == 1) {
                if (isdigit(c)) {
                    n = c - '0';    // 设置首位值
                    status = 2;
                } else if (c == '\"') {
                    status = 4;     // 终止
                } else {
                    break;
                }
            } else if (status == 2) {
                if (isdigit(c)) {
                    n = n * 10 + (c - '0'); // 移入
                    status = 2;
                } else if (c == ',') {
                    dims.push_back(n);      // 规约
                    n = 0;
                    status = 3;
                } else if (c == '"') {
                    dims.push_back(n);  // 规约
                    n = 0;
                    status = 4;         // 终结
                } else {
                    break;
                }
            } else if (status == 3) {
                if (isdigit(c)) {
                    n = c - '0';    // 设置首位值
                    status = 2;
                } else if (c == '"') {
                    status = 4;     // 终结
                } else {
                    break;
                }
            } else if (status == 4) {
                return ErrOr<decltype(dims)>(dims);
            } else {
                assert(false);
                break;
            }
        }
        if (status == 0 || status == 4) {
            return MakeNoErrVal(dims);
        } else {
            return ErrOr<decltype(dims)>::CreateError(1);
        }
    }

}
