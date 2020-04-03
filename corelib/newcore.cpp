//
// Created by rex on 2020/3/20.
//

#include <cstdio>
#include <stdarg.h>
#include <sstream>

#include "newcore.h"

/*!
 * @brief 调试输出整数值
 * @param llval 长整数值
 * @return
 */
void DebugTraceOutInt(long long llval) {
    printf("%lld\n", llval);
    return;
}

void DebugTraceOut(int n, SimpleRTArguInfo *arguments) {
    if (n <= 0) { return; }
    std::stringstream ss;
    ss << arguments[0].argument_value;
    for (int idx = 1; idx < n; ++idx) {
        SimpleRTArguInfo &argu_info = arguments[idx];
        ss << "|" << argu_info.argument_value;
    }
    printf("%s\n", ss.str().c_str());
    return;
}
