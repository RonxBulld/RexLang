//
// Created by rex on 2020/3/22.
//

#include "runtime_api.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>

/*
 * 动态数组的内存模型：
 * 维度个数
 * 维度列表
 * 数据空间
 */

static int *ArrayDimNum_Ref(RTDynArrayTy arrayPtr) {
    return &reinterpret_cast<int*>(arrayPtr)[0];
}

static int *ArrayDims_Ref(RTDynArrayTy arrayPtr) {
    return &reinterpret_cast<int*>(arrayPtr)[1];
}

template <typename ElemTy>
static ElemTy *ArrayDatas_Ref(RTDynArrayTy arrayPtr) {
    return reinterpret_cast<ElemTy *>(ArrayDims_Ref(arrayPtr) + *ArrayDimNum_Ref(arrayPtr));
}

static int ArrayCapacity(RTDynArrayTy arrayPtr) {
    int dims_n = *ArrayDimNum_Ref(arrayPtr);
    int *dim_ptr = ArrayDims_Ref(arrayPtr);
    int size = 1;
    for (int i = 0; i < dims_n; ++i) { size *= dim_ptr[i]; }
    return size;
}

RTDynArrayTy create_array(int dims_n, ...) {
    int mem_size = sizeof(int) + dims_n * sizeof(int);
    int *dims = (int*)alloca(dims_n * sizeof(int));
    int element_count = 1;

    va_list ap;
    va_start(ap, dims_n);
    for (int i = 0; i < dims_n; ++i) {
        int dim = va_arg(ap, int);
        dims[i] = dim;
        element_count *= dim;
    }
    va_end(ap);

    mem_size += element_count * sizeof(uint64_t);
    int *p = (int*)malloc(mem_size);

    p[0] = dims_n;
    for (int i = 0; i < dims_n; ++i) { p[i + 1] = dims[0]; }

    return reinterpret_cast<RTDynArrayTy>(p);
}

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
    printf("idx: %d\n", index);
    return index;
}

void init_array_32bit(RTDynArrayTy arrayPtr, int n, ...) {
    va_list ap;
    va_start(ap, n);
    int32_t *data_ptr = ArrayDatas_Ref<int32_t>(arrayPtr);
    int capacity = ArrayCapacity(arrayPtr);
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
