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

/*!
 * 获取数组的维度深度
 * @param arrayPtr 数组对象指针
 * @return 深度
 */
int get_array_dim_depth(RTDynArrayTy arrayPtr);

/*!
 * 获取数组的维度列表
 * @param arrayPtr 数组对象指针
 * @param dims 维度列表起始地址
 * @param n 维度列表长度
 * @return 实际取得的维度列表长度，-1表示失败
 */
int get_array_dims(RTDynArrayTy arrayPtr, int *dims, int n);

/*!
 * 获取数组的大小
 * @param arrayPtr 数组对象指针
 * @return 数组存储元素个数
 */
int get_array_size(RTDynArrayTy arrayPtr);

SimpleRTTI_ArguType get_array_rt_type(RTDynArrayTy arrayPtr);

/*!
 * 获取数组元素值
 * 程序会根据数组中的元素类型获取相应长度的二进制数据，并不会对数据内容进行解释
 * @param arrayPtr 数组对象指针
 * @param dims_n 维度个数
 * @param ... 维度列表
 * @return 取得的数据
 */
unsigned long long get_element_as_bit(RTDynArrayTy arrayPtr, int dims_n, ...);

void init_array_32bit(RTDynArrayTy arrayPtr, int, ...);

int *get_array_ep_32bit(RTDynArrayTy arrayPtr, int, ...);

};

#endif //OPENELANGUAGE_ARRAY_RUNTIME_API_H
