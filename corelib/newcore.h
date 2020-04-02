//
// Created by rex on 2020/3/22.
//

#ifndef OPENELANGUAGE_NEWCORE_H
#define OPENELANGUAGE_NEWCORE_H

extern "C" {

enum ArguType : char {
    /* Integer */
    kInt8='c', kInt16='w', kInt32='d', kInt64='q',
    /* Float */
    kFloat='f', kDouble='e',
    /* Aggregates */
    kArray='a', kString='s', kStruct='t',
};

struct SimpleRTArguInfo {
    ArguType argu_type;
    long long argument_value;
};

void DebugTraceOutInt(long long llval);

void DebugTraceOut(int n, SimpleRTArguInfo *arguInfoList);

};

#endif //OPENELANGUAGE_NEWCORE_H
