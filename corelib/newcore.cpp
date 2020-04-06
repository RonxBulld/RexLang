//
// Created by rex on 2020/3/20.
//

#include <cstdio>
#include <stdarg.h>
#include <sstream>
#include <assert.h>
#include <vector>
#include <queue>

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

static std::string ValueToString(SimpleRTTI_ArguType ty, long long val) {
    switch (ty) {
        case SimpleRTTI_ArguType::kInt8:
        case SimpleRTTI_ArguType::kInt16:
        case SimpleRTTI_ArguType::kInt32:
        case SimpleRTTI_ArguType::kInt64: {
            return std::to_string(val);
        }
        case SimpleRTTI_ArguType::kFloat:
        case SimpleRTTI_ArguType::kDouble: {
            return std::to_string(*(double*)(&val));
        }
        case SimpleRTTI_ArguType::kArray: {
            RTDynArrayTy array = (RTDynArrayTy)val;

            // 获取维度信息

            int dim_depth = get_array_dim_depth(array);
            int *array_dims = (int*)alloca(dim_depth * sizeof(int));
            (void) get_array_dims(array, array_dims, dim_depth);

            // 将元素转换为字符串列表

            SimpleRTTI_ArguType arr_elem_ty = get_array_rt_type(array);
            int count = get_array_size(array);
            std::vector<std::string> elem_str_list;
            elem_str_list.reserve(count);
            for (int idx = 0; idx < count; ++idx) {
                unsigned long long d = get_element_as_bit(array, 1, idx + 1);
                elem_str_list.push_back(ValueToString(arr_elem_ty, d));
            }

            // 将字符串列表根据维度信息进行规约打包

            for (int idx = dim_depth - 1; idx >= 0; --idx) {
                int dim = array_dims[idx];
                assert(dim > 0);
                assert(elem_str_list.size() % dim == 0);

                int read_idx = 0, write_idx = 0;
                while (read_idx < elem_str_list.size()) {

                    // 打包 [read_idx : read_idx+dim-1] 范围的数据

                    std::stringstream s0;
                    s0 << dim << "[" << elem_str_list[read_idx];
                    for (int i = read_idx + 1; i <= read_idx+dim-1; ++i) { s0 << "," << elem_str_list[i]; }
                    s0 << "]";

                    // 写入到 write_idx 位置

                    elem_str_list[write_idx] = s0.str();

                    read_idx += dim;
                    write_idx +=1;
                }

                // 移除多余的元素

                elem_str_list.resize(write_idx);
            }

            assert(elem_str_list.size() <= 1);

            return "数组:" + (elem_str_list.empty() ? "" : elem_str_list.front());
        }
        case SimpleRTTI_ArguType::kString: {
            RTDynStringTy dyn_string = (RTDynStringTy) val;
            const char *c_str = string_data_ref(dyn_string);
            return std::string("\"") + c_str + "\"";
        }
        case SimpleRTTI_ArguType::kStruct: {
            return "{}";
        }
        default: {
            assert(false);
            return "";
        }
    }
}

static std::string ValueToString(SimpleRTArguInfo *value) {
    return ValueToString(value->argu_type, value->argument_value);
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
