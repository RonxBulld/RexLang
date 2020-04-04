//
// Created by rexfield on 2020/4/4.
//

#include <stdlib.h>
#include <string.h>

#include "string_runtime_api.h"

/*************************************
 * 动态字符串的内存模型：
 * 字符串长度
 * 数据空间
 *************************************/

static const char *empty_string_literal = "";

RTDynStringTy create_string(const char *stringLiteral) {
    if (!stringLiteral) {
        stringLiteral = empty_string_literal;
    }

    size_t nlen = strlen(stringLiteral);
    char *memp = (char*)malloc(sizeof(size_t) + nlen + 1);
    memcpy(memp, &nlen, sizeof(size_t));
    (void) strcpy(memp + sizeof(size_t), stringLiteral);
    return memp;
}

const char *string_data_ref(const RTDynStringTy dynString) {
    return dynString + sizeof(size_t);
}

RTDynStringTy clone_string(const RTDynStringTy dynString) {
    return create_string(string_data_ref(dynString));
}
