//
// Created by rex on 2020/3/22.
//

#ifndef REXLANG_NEWCORE_H
#define REXLANG_NEWCORE_H

extern "C" {

#include "../Compiler/ir/SimpleRTTI_ArguType.h"

struct SimpleRTArguInfo {
    SimpleRTTI_ArguType argu_type;
    long long argument_value;
};

/*!
 * @brief 调试输出整数值
 * @param llval 长整数值
 */
void DebugTraceOutInt(long long llval);

/*!
 * @brief 调试输出
 * @param n 不定参数个数
 * @param arguments 不定参数序列
 */
void DebugTraceOut(int n, SimpleRTArguInfo *arguments);

};

#endif //REXLANG_NEWCORE_H
