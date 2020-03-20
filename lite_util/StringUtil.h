//
// Created by rex on 2020/3/20.
//

#ifndef OPENELANGUAGE_STRINGUTIL_H
#define OPENELANGUAGE_STRINGUTIL_H

#include <string>
#include <sstream>

class StringUtil {
public:
    template <typename IterTy>
    static std::string Join(IterTy begin, IterTy end, const std::string &separator) {
        std::stringstream ss;
        ss << *begin++;
        while (begin != end) {
            ss << separator;
            ss << *begin++;
        }
        return ss.str();
    }

    template <template <typename Key> typename Container, typename Elem>
    static std::string Join(Container<Elem> &string_list, const std::string &separator) {
        return Join(string_list.begin(), string_list.end(), separator);
    }

    static std::string Sprintf(const char *fmt, ...);
};


#endif //OPENELANGUAGE_STRINGUTIL_H
