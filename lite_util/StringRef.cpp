//
// Created by rex on 2020/1/22.
//

#include <cassert>
#include <cstring>
#include "StringRef.h"

namespace rexlang {

    static std::string _kEmptyStr = "";

    /********************************************
     * StringRef
     ********************************************/

    StringRef::StringRef()                     : /*pool_(nullptr),*/   string_(&_kEmptyStr) { }
    StringRef::StringRef(const StringRef &rhs) : /*pool_(rhs.pool_),*/ string_(rhs.string_) { }

    StringRef::operator std::string () const { return *this->string_; }
    StringRef::operator const char *() const { return this->string_->c_str(); }

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

    StringRef StringRef::operator+(const StringRef &other) const {
        const std::string &lhs_v = *this->string_;
        const std::string &rhs_v = *other.string_;
        std::string comp = lhs_v + rhs_v;
        return StringPool::Create(comp);
    }

    StringRef &StringRef::operator+=(const StringRef &other) {
        return this->operator+=(*other.string_);
    }

    bool StringRef::operator==(const StringRef &other) const {
        if (other.string_ == this->string_) { return true; }
        return *this->string_ == *other.string_;
    }

    bool StringRef::operator!=(const StringRef &other) const { return !this->operator==(other); }
    bool StringRef::operator> (const StringRef &other) const { return *this->string_ > *other.string_; }
    bool StringRef::operator< (const StringRef &other) const { return *this->string_ < *other.string_; }

    const std::string & StringRef::str  () const { return *this->string_; }
    const char *        StringRef::c_str() const { return this->string_->c_str(); }

    StringRef StringRef::operator+(const std::string &other) const {
        return this->operator+(StringPool::Create(other));
    }

    StringRef &StringRef::operator+=(const std::string &other) {
        *this = StringPool::Create(*this->string_ + other);
        return *this;
    }

    bool StringRef::operator==(const std::string &other) const { return *this->string_ == other; }
    bool StringRef::operator!=(const std::string &other) const { return *this->string_ != other; }
    bool StringRef::operator> (const std::string &other) const { return *this->string_ > other; }
    bool StringRef::operator< (const std::string &other) const { return *this->string_ < other; }

    bool StringRef::operator==(const unsigned char *rhs) const {
        if (rhs == nullptr) { return false; }
        return strncmp(this->string_->c_str(), (const char *)rhs, this->string_->length()) == 0;
    }

    bool StringRef::empty() const {
        return (this->string_ == nullptr || this->string_->empty());
    }

    /********************************************
     * StringPool
     ********************************************/

    size_t                           StringPool::max_string_size_ = 65536;
    std::map<std::string, StringRef> StringPool::string_pool_;

    StringRef StringPool::Create(const std::string &str) {
        auto found = string_pool_.find(str);
        if (found == string_pool_.end()) {
            auto insres = string_pool_.insert({str, StringRef()});
            assert(insres.second == true);
            insres.first->second.string_ = &insres.first->first;
//            insres.first->second.pool_ = this;
            found = insres.first;
        }
        return found->second;
    }

    StringRef StringPool::Create(const char *pstr) {
        size_t slen = 0;
        while (slen < max_string_size_) {
            if (pstr[slen] == '\0') {
                break;
            }
            slen++;
        }
        if (slen >= max_string_size_) {
            assert(false);
            slen = max_string_size_ - 1;
        }
        return Create(std::string(pstr, slen));
    }
}