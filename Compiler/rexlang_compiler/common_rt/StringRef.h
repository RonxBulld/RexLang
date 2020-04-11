//
// Created by rex on 2020/1/22.
//

#ifndef REXLANG_STRINGREF_H
#define REXLANG_STRINGREF_H

#include <map>
#include <string>

namespace rexlang {

    class StringRef {
        friend class StringPool;
        friend struct std::hash<rexlang::StringRef>;
    private:
        const std::string *string_ = nullptr;
        class StringPool *pool_ = nullptr;
    public:
        StringRef();

        StringRef(const StringRef &rhs);

        StringRef &operator=(const StringRef &rhs) = default;

        explicit operator std::string() const;

        explicit operator const char *() const;

        const std::string &str() const;

        const char *c_str() const;

        size_t size() const;

        bool empty() const;

        char operator[](size_t index) const;

        StringRef operator+(const StringRef &rhs) const;
        StringRef operator+(const std::string &rhs) const;

        StringRef &operator+=(const StringRef &rhs);
        StringRef &operator+=(const std::string &rhs);

        bool operator==(const StringRef &rhs) const;
        bool operator==(const std::string &rhs) const;
        bool operator==(const unsigned char *rhs) const;
        // bool operator==(const char8_t *rhs) const;

        bool operator!=(const StringRef &rhs) const;
        bool operator!=(const std::string &rhs) const;

        bool operator>(const StringRef &rhs) const;
        bool operator>(const std::string &rhs) const;

        bool operator<(const StringRef &rhs) const;
        bool operator<(const std::string &rhs) const;
    };

    class StringPool {
    private:
        size_t max_string_size_ = 65536;
        std::map<std::string, StringRef> string_pool_;

    public:
        StringRef Create(const std::string &str);

        StringRef Create(const char *pstr);
    };
}

namespace std {
    template<> struct hash<rexlang::StringRef> {
        // Powered by folly at facebook.
        inline uint64_t hash_128_to_64(const uint64_t upper, const uint64_t lower) const noexcept {
            // Murmur-inspired hashing.
            const uint64_t kMul = 0x9ddfea08eb382d69ULL;
            uint64_t a = (lower ^ upper) * kMul;
            a ^= (a >> 47);
            uint64_t b = (upper ^ a) * kMul;
            b ^= (b >> 47);
            b *= kMul;
            return b;
        }

        std::size_t operator()(rexlang::StringRef const& string_ref) const noexcept {
            return hash_128_to_64((uint64_t)string_ref.string_, (uint64_t)string_ref.pool_);
        }
    };
}
#endif //REXLANG_STRINGREF_H
