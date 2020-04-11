//
// Created by rex on 2020/1/22.
//

#include <cassert>
#include <cstring>
#include "StringRef.h"

namespace rexlang {
    static std::string _kEmptyStr = "";

    StringRef::StringRef() : pool_(nullptr), string_(&_kEmptyStr) {
    }

    StringRef::StringRef(const StringRef &rhs) {
        this->pool_ = rhs.pool_;
        this->string_ = rhs.string_;
    }

    StringRef::operator std::string() const {
        return *this->string_;
    }

    StringRef::operator const char *() const {
        return this->string_->c_str();
    }

    char StringRef::operator[](size_t index) const {
        if (this->size() > index) {
            return this->string_->operator[](index);
        } else {
            assert(false);
            return '\0';
        }
    }

    size_t StringRef::size() const {
        return this->string_->size();
    }

    StringRef StringRef::operator+(const StringRef &rhs) const {
        const std::string &lhs_v = *this->string_;
        const std::string &rhs_v = *rhs.string_;
        std::string comp = lhs_v + rhs_v;
        if (this->pool_ == rhs.pool_) {
            assert(false);
            rhs.pool_->Create(comp);
        }
        return this->pool_->Create(comp);
    }

    StringRef &StringRef::operator+=(const StringRef &rhs) {
        return this->operator+=(*rhs.string_);
    }

    bool StringRef::operator==(const StringRef &rhs) const {
        if (rhs.string_ == this->string_) { return true; }
        return *this->string_ == *rhs.string_;
    }

    bool StringRef::operator!=(const StringRef &rhs) const {
        return !this->operator==(rhs);
    }

    bool StringRef::operator>(const StringRef &rhs) const {
        return *this->string_ > *rhs.string_;
    }

    bool StringRef::operator<(const StringRef &rhs) const {
        return *this->string_ < *rhs.string_;
    }

    const std::string &StringRef::str() const {
        return *this->string_;
    }

    const char *StringRef::c_str() const {
        return this->string_->c_str();
    }

    StringRef StringRef::operator+(const std::string &rhs) const {
        return this->operator+(this->pool_->Create(rhs));
    }

    StringRef &StringRef::operator+=(const std::string &rhs) {
        *this = this->pool_->Create(*this->string_ + rhs);
        return *this;
    }

    bool StringRef::operator==(const std::string &rhs) const {
        return *this->string_ == rhs;
    }

    bool StringRef::operator!=(const std::string &rhs) const {
        return *this->string_ != rhs;
    }

    bool StringRef::operator>(const std::string &rhs) const {
        return *this->string_ > rhs;
    }

    bool StringRef::operator<(const std::string &rhs) const {
        return *this->string_ < rhs;
    }

    bool StringRef::operator==(const unsigned char *rhs) const {
        if (rhs == nullptr) { return false; }
        return strncmp(this->string_->c_str(), (const char *)rhs, this->string_->length()) == 0;
    }

    bool StringRef::empty() const {
        return (this->string_ == nullptr || this->string_->empty());
    }

    StringRef StringPool::Create(const std::string &str) {
        auto found = this->string_pool_.find(str);
        if (found == this->string_pool_.end()) {
            auto insres = this->string_pool_.insert({str, StringRef()});
            assert(insres.second == true);
            insres.first->second.string_ = &insres.first->first;
            insres.first->second.pool_ = this;
            found = insres.first;
        }
        return found->second;
    }

    StringRef StringPool::Create(const char *pstr) {
        size_t slen = 0;
        while (slen < this->max_string_size_) {
            if (pstr[slen] == '\0') {
                break;
            }
            slen++;
        }
        if (slen >= this->max_string_size_) {
            assert(false);
            slen = this->max_string_size_ - 1;
        }
        return this->Create(std::string(pstr, slen));
    }
}