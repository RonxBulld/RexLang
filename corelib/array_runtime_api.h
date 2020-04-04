//
// Created by rex on 2020/3/22.
//

#ifndef OPENELANGUAGE_ARRAY_RUNTIME_API_H
#define OPENELANGUAGE_ARRAY_RUNTIME_API_H

extern "C" {

#include "../Compiler/ir/SimpleRTTI_ArguType.h"

typedef char *RTDynArrayTy;

/*!
 * 创建数组
 * @param ety 数组元素类型
 * @param dims_n 维度深度
 * @param ... 维度列表
 * @return 数组对象
 */
RTDynArrayTy create_array(SimpleRTTI_ArguType ety, int dims_n, ...);

void init_array_32bit(RTDynArrayTy, int, ...);

int *get_array_ep_32bit(RTDynArrayTy, int, ...);

};

#endif //OPENELANGUAGE_ARRAY_RUNTIME_API_H
