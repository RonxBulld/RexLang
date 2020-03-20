//
// Created by rex on 2020/3/20.
//

#include <cstdio>

extern "C" {
int DebugTraceOutInt(long long llval);
}

int DebugTraceOutInt(long long llval) {
    printf("%lld\n", llval);
    return 1;
}