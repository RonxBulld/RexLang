//
// Created by rex on 2020/3/22.
//

#ifndef OPENELANGUAGE_NEWCORE_H
#define OPENELANGUAGE_NEWCORE_H

extern "C" {

#include "../Compiler/ir/SimpleRTTI_ArguType.h"

struct SimpleRTArguInfo {
    SimpleRTTI_ArguType argu_type;
    long long argument_value;
};

void DebugTraceOutInt(long long llval);

void DebugTraceOut(int n, SimpleRTArguInfo *arguments);

};

#endif //OPENELANGUAGE_NEWCORE_H
