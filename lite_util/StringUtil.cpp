//
// Created by rex on 2020/3/20.
//

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "StringUtil.h"

/*
 * vscprintf:
 * MSVC implements this as _vscprintf, thus we just 'symlink' it here
 * GNU-C-compatible compilers do not implement this, thus we implement it here
 */
#ifdef _MSC_VER
#define vscprintf _vscprintf
#endif

#ifdef __GNUC__

int vscprintf(const char *format, va_list ap) {
    va_list ap_copy;
    va_copy(ap_copy, ap);
    int retval = vsnprintf(NULL, 0, format, ap_copy);
    va_end(ap_copy);
    return retval;
}

#endif

/*
 * asprintf, vasprintf:
 * MSVC does not implement these, thus we implement them here
 * GNU-C-compatible compilers implement these with the same names, thus we
 * don't have to do anything
 */
#ifdef _MSC_VER
int vasprintf(char **strp, const char *format, va_list ap)
{
    int len = vscprintf(format, ap);
    if (len == -1)
        return -1;
    char *str = (char*)malloc((size_t) len + 1);
    if (!str)
        return -1;
    int retval = vsnprintf(str, len + 1, format, ap);
    if (retval == -1) {
        free(str);
        return -1;
    }
    *strp = str;
    return retval;
}

int asprintf(char **strp, const char *format, ...)
{
    va_list ap;
            va_start(ap, format);
    int retval = vasprintf(strp, format, ap);
            va_end(ap);
    return retval;
}
#endif

std::string StringUtil::Sprintf(const char *fmt, ...) {
    char *astrp = nullptr;
    va_list ap;
    va_start(ap, fmt);
    vasprintf(&astrp, fmt, ap);
    va_end(ap);
    std::string astr = astrp;
    free(astrp);
    return astr;
}

std::string StringUtil::TrimLeft(const std::string &str) {
    size_t len = str.length();
    const char *pstr = str.c_str();
    size_t cut_pos = 0;
    for (cut_pos = 0; cut_pos < len; ++cut_pos) {
        if (isblank(pstr[cut_pos]) == 0) {
            break;
        }
    }
    return std::string(pstr + cut_pos);
}

std::string StringUtil::TrimRight(const std::string &str) {
    std::string __str = str;
    while (!__str.empty() && isblank(__str.back())) {
        __str.pop_back();
    }
    return __str;
}

std::string StringUtil::Trim(const std::string &str) {
    return StringUtil::TrimRight(StringUtil::TrimLeft(str));
}
