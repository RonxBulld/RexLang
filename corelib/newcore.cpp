//
// Created by rex on 2020/3/20.
//

#include <cstdio>
#include <stdarg.h>
#include <sstream>
#include <assert.h>

#include "newcore.h"
#include "array_runtime_api.h"
#include "string_runtime_api.h"

/*!
 * @brief 调试输出整数值
 * @param llval 长整数值
 * @return
 */
void DebugTraceOutInt(long long llval) {
    printf("%lld\n", llval);
    return;
}

static std::string ValueToString(SimpleRTArguInfo *value) {
    switch (value->argu_type) {
        case SimpleRTTI_ArguType::kInt8:
        case SimpleRTTI_ArguType::kInt16:
        case SimpleRTTI_ArguType::kInt32:
        case SimpleRTTI_ArguType::kInt64: {
            return std::to_string(value->argument_value);
        }
        case SimpleRTTI_ArguType::kFloat:
        case SimpleRTTI_ArguType::kDouble: {
            return std::to_string(*(double*)(&value->argument_value));
        }
        case SimpleRTTI_ArguType::kArray: {

            return "[]";
        }
        case SimpleRTTI_ArguType::kString: {
            RTDynStringTy dyn_string = (RTDynStringTy) value->argument_value;
            const char *c_str = string_data_ref(dyn_string);
            return std::string("\"") + c_str + "\"";
        }
        case SimpleRTTI_ArguType::kStruct: {
            return "{}";
        }
        default: {
            assert(false);
        }
    }
}

void DebugTraceOut(int n, SimpleRTArguInfo *arguments) {
    if (n <= 0) { return; }
    std::stringstream ss;
    ss << ValueToString(&arguments[0]);
    for (int idx = 1; idx < n; ++idx) {
        SimpleRTArguInfo &argu_info = arguments[idx];
        ss << "|" << ValueToString(&argu_info);
    }
    printf("%s\n", ss.str().c_str());
    return;
}
