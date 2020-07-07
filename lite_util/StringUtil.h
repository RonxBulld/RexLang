//
// Created by rex on 2020/3/20.
//

#ifndef REXLANG_STRINGUTIL_H
#define REXLANG_STRINGUTIL_H

#include <string>
#include <sstream>

class StringUtil {
public:
    template<typename IterTy>
    static std::string Join(IterTy begin, IterTy end, const std::string &separator) {
        std::stringstream ss;
        if (begin != end) {
            ss << *begin++;
            while (begin != end) {
                ss << separator;
                ss << *begin++;
            }
        }
        return ss.str();
    }

    template<typename ContainerTy, typename Elem>
    static std::string Join(const ContainerTy &string_list, const std::string &separator) {
        return Join(string_list.begin(), string_list.end(), separator);
    }

    template<typename IterTy, typename ConvertPred>
    static std::string Join(IterTy begin, IterTy end, const std::string &separator, ConvertPred && convert_pred) {
        std::stringstream ss;
        if (begin != end) {
            ss << convert_pred(*begin++);
            while (begin != end) {
                ss << separator;
                ss << convert_pred(*begin++);
            }
        }
        return ss.str();
    }

    template<typename ContainerTy, typename ConvertPred>
    static std::string Join(const ContainerTy &string_list, const std::string &separator, ConvertPred && convert_pred) {
        return Join(string_list.begin(), string_list.end(), separator, convert_pred);
    }

    static std::string Sprintf(const char *fmt, ...);

    static std::string TrimLeft(const std::string &str);

    static std::string TrimRight(const std::string &str);

    static std::string Trim(const std::string &str);
};


#endif //REXLANG_STRINGUTIL_H
