//
// Created by rex on 2020/1/22.
//

#ifndef OPENELANGUAGE_STRINGREF_H
#define OPENELANGUAGE_STRINGREF_H

#include <map>
#include <string>

namespace opene {

    class StringRef {
        friend class StringPool;
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

#endif //OPENELANGUAGE_STRINGREF_H
