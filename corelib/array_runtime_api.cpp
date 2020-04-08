//
// Created by rex on 2020/3/22.
//

#include "array_runtime_api.h"

#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*************************************
 * 动态数组的内存模型：
 * 元素类型
 * 维度个数
 * 维度列表
 * 数据空间
 *************************************/

static SimpleRTTI_ArguType *ArrayElementTy_Ref(RTDynArrayTy arrayPtr) {
    return (SimpleRTTI_ArguType *)  ((char*)arrayPtr + 0);
}

static int *ArrayDimNum_Ref(RTDynArrayTy arrayPtr) {
    return (int *)                  ((char*)arrayPtr + sizeof(SimpleRTTI_ArguType));
}

static int *ArrayDims_Ref(RTDynArrayTy arrayPtr) {
    return (int *)                  ((char*)arrayPtr + sizeof(SimpleRTTI_ArguType) + sizeof(int));
}

template <typename ElemTy>
static ElemTy *ArrayDatas_Ref(RTDynArrayTy arrayPtr) {
    return reinterpret_cast<ElemTy *>(ArrayDims_Ref(arrayPtr) + *ArrayDimNum_Ref(arrayPtr));
}

/*
 * 获取数组大小
 */
static int ArraySize(RTDynArrayTy arrayPtr) {
    int dims_n = *ArrayDimNum_Ref(arrayPtr);
    int *dim_ptr = ArrayDims_Ref(arrayPtr);
    int size = 1;
    for (int i = 0; i < dims_n; ++i) { size *= dim_ptr[i]; }
    return size;
}

int get_array_size(RTDynArrayTy arrayPtr) {
    return ArraySize(arrayPtr);
}

RTDynArrayTy create_array(SimpleRTTI_ArguType ety, int dims_n, ...) {
    int mem_size = sizeof(SimpleRTTI_ArguType) + sizeof(int) + dims_n * sizeof(int);

    int *dims = (int*)alloca(dims_n * sizeof(int));
    int element_count = 1;

    // 获取维度列表并计算元素总数

    va_list ap;
    va_start(ap, dims_n);
    for (int i = 0; i < dims_n; ++i) {
        int dim = va_arg(ap, int);
        dims[i] = dim;
        element_count *= dim;
    }
    va_end(ap);
    mem_size += element_count * GetTypeStorageSize(ety);

    RTDynArrayTy new_array = (RTDynArrayTy)malloc(mem_size);

    // 将元素类型、维度深度、维度列表写入对象

    *ArrayElementTy_Ref(new_array) = ety;
    *ArrayDimNum_Ref(new_array) = dims_n;
    int *array_dims_ref = ArrayDims_Ref(new_array);
    for (int i = 0; i < dims_n; ++i) { array_dims_ref[i] = dims[i]; }

    return new_array;
}

int get_array_dim_depth(RTDynArrayTy arrayPtr) {
    return *ArrayDimNum_Ref(arrayPtr);
}

int get_array_dims(RTDynArrayTy arrayPtr, int *dims, int n) {
    assert(dims);
    int actual_n = *ArrayDimNum_Ref(arrayPtr);
    n = n > actual_n ? actual_n : n;
    int *dims_ref = ArrayDims_Ref(arrayPtr);
    for (int i = 0; i < n; ++i) {
        dims[i] = dims_ref[i];
    }
    return n;
}

/*
 * 将多维索引转换为一维
 */
static int GetLinearIndex(RTDynArrayTy arrayPtr, int dims_n, va_list ap) {
    int index = 0;
    if (dims_n == 1) {
        index = va_arg(ap, int) - 1;
    } else {
        if (dims_n != *ArrayDimNum_Ref(arrayPtr)) {
            assert(false);
            index = 0;
        } else {
            int *dim_ptr = ArrayDims_Ref(arrayPtr);
            index = va_arg(ap, int) - 1;
            for (int i = 1; i < dims_n; ++i) {
                int _cidx = va_arg(ap, int) - 1;
                index = (index * dim_ptr[i - 1]) + _cidx;
            }
        }
    }
    return index;
}

SimpleRTTI_ArguType get_array_rt_type(RTDynArrayTy arrayPtr) {
    return *ArrayElementTy_Ref(arrayPtr);
}

unsigned long long get_element_as_bit(RTDynArrayTy arrayPtr, int dims_n, ...) {
    va_list ap;
    va_start(ap, dims_n);
    int index = GetLinearIndex(arrayPtr, dims_n, ap);
    assert(index >= 0);
    va_end(ap);
    unsigned element_size = GetTypeStorageSize(*ArrayElementTy_Ref(arrayPtr));
    unsigned long long addr = (unsigned long long)ArrayDatas_Ref<void>(arrayPtr) + element_size * index;
    unsigned long long data = 0;
    memcpy(&data, (void*)addr, element_size);
    return data;
}

void init_array_32bit(RTDynArrayTy arrayPtr, int n, ...) {
    va_list ap;
    va_start(ap, n);
    int32_t *data_ptr = ArrayDatas_Ref<int32_t>(arrayPtr);
    int capacity = ArraySize(arrayPtr);
    n = n > capacity ? capacity : n;
    for (int i = 0; i < n; ++i) {
        data_ptr[i] = va_arg(ap, int32_t);
    }
    va_end(ap);
}

int *get_array_ep_32bit(RTDynArrayTy arrayPtr, int dims_n, ...) {
    va_list ap;
    va_start(ap, dims_n);
    int index = GetLinearIndex(arrayPtr, dims_n, ap);
    va_end(ap);
    int32_t * elem_ptr = ArrayDatas_Ref<int32_t>(arrayPtr) + index;
    return elem_ptr;
}

void init_array_64bit(RTDynArrayTy arrayPtr, int n, ...) {
    va_list ap;
    va_start(ap, n);
    int64_t *data_ptr = ArrayDatas_Ref<int64_t>(arrayPtr);
    int capacity = ArraySize(arrayPtr);
    n = n > capacity ? capacity : n;
    for (int i = 0; i < n; ++i) {
        data_ptr[i] = va_arg(ap, int64_t);
    }
    va_end(ap);
}

int64_t *get_array_ep_64bit(RTDynArrayTy arrayPtr, int dims_n, ...) {
    va_list ap;
    va_start(ap, dims_n);
    int index = GetLinearIndex(arrayPtr, dims_n, ap);
    va_end(ap);
    int64_t * elem_ptr = ArrayDatas_Ref<int64_t>(arrayPtr) + index;
    return elem_ptr;
}
