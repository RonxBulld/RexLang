//
// Created by rex on 2020/1/23.
//

#include <cassert>
#include <regex>
#include <string>
#include "Str2Attr.h"

namespace rexlang {
    ErrOr<AccessLevel> Str2Attr::name2AccessLevel(const StringRef &name) {
        if (name == u8"公开") {
            return ErrOr<AccessLevel>(AccessLevel::kALPublic);
        } else if (name == u8"") {
            return ErrOr<AccessLevel>(AccessLevel::kALPrivate);
        } else {
            assert(false);
            return ErrOr<AccessLevel>::CreateError(1);
        }
    }

    ErrOr<ValueTransferMode> Str2Attr::name2ValueTransferMode(const StringRef &name) {
        if (name == u8"传址") {
            return ErrOr<ValueTransferMode>(ValueTransferMode::kVTMReference);
        } else if (name == u8"") {
            return ErrOr<ValueTransferMode>(ValueTransferMode::kVTMValue);
        } else {
            assert(false);
            return ErrOr<ValueTransferMode>::CreateError(1);
        }
    }

    ErrOr<std::vector<size_t>> Str2Attr::str2Dimension(const StringRef &str) {
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

    bool Str2Attr::isNameOfReference(const StringRef &str) { return str == u8"参考"; }
    bool Str2Attr::isNameOfNullable (const StringRef &str) { return str == u8"可空"; }
    bool Str2Attr::isNameOfArray    (const StringRef &str) { return str == u8"数组"; }
    bool Str2Attr::isNameOfStatic   (const StringRef &str) { return str == u8"静态"; }

}
