//
// Created by rex on 2020/3/20.
//

#include <stdarg.h>

#include "StringUtil.h"

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
