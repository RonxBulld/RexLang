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
//        class StringPool *pool_ = nullptr;
    public:
        StringRef();
        StringRef(const StringRef &rhs);

        StringRef &operator=(const StringRef &rhs) = default;
        explicit operator std::string() const;
        explicit operator const char *() const;

        const std::string & str     () const;
        const char *        c_str   () const;
        size_t              size    () const;
        bool                empty   () const;

        char operator[](size_t index) const;

        StringRef operator+(const StringRef &other) const;
        StringRef operator+(const std::string &other) const;

        StringRef &operator+=(const StringRef &other);
        StringRef &operator+=(const std::string &other);

        bool operator==(const StringRef &other) const;
        bool operator==(const std::string &other) const;
        bool operator==(const unsigned char *rhs) const;
        // bool operator==(const char8_t *rhs) const;

        bool operator!=(const StringRef &other) const;
        bool operator!=(const std::string &other) const;

        bool operator>(const StringRef &other) const;
        bool operator>(const std::string &other) const;

        bool operator<(const StringRef &other) const;
        bool operator<(const std::string &other) const;
    };

    class StringPool {
    private:
        StringPool() = default;
        static size_t max_string_size_;
        static std::map<std::string, StringRef> string_pool_;
    public:
        static StringRef Create(const std::string &str);
        static StringRef Create(const char *pstr);
    };
}

namespace std {

    template<> struct hash<rexlang::StringRef> {
        std::size_t operator()(rexlang::StringRef const& string_ref) const noexcept {
            return (std::size_t) (intptr_t) string_ref.string_;
        }
    };
}
#endif //REXLANG_STRINGREF_H
