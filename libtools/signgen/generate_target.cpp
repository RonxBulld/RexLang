//
// Created by rex on 2020/4/18.
//

#include <assert.h>

#include "generate_target.h"
#include "../CDecl/cdecl.h"
#include "../../lite_util/StringUtil.h"

std::string GenerateReturnType(const struct TypeDesc &type);
std::string GenerateParameterType(const struct TypeDesc &type);
std::string GenerateParameterTypeAttributes(const struct TypeDesc &type);

const char *targetLanguageName =    "Rex语言";
const char *int8Typename =          "字节型";
const char *int16Typename =         "短整型";
const char *int32Typename =         "整数型";
const char *int64Typename =         "长整数型";
const char *float32Typename =       "小数型";
const char *float64Typename =       "双精度小数型";
const char *pointerTypename =       int32Typename;

const char *GetTargetLanguageName() {
    return targetLanguageName;
}

std::string GenerateReturnType(const struct TypeDesc &type) {
    if (type.is_array) {
        std::cerr << "返回值类型不允许为数组。" << std::endl;
        return "";
    }
    if (type.is_nullable) {
        std::cerr << "返回值类型不允许为可空。" << std::endl;
        return "";
    }
    if (type.is_reference) {
        return pointerTypename;
    }
    switch (type.base_typename[0]) {
        case 'v': return "";
        case 'i': {
            size_t bits = strtol(type.base_typename.c_str() + 1, nullptr, 10);
            switch (bits) {
                case 8: return int8Typename;
                case 16: return int16Typename;
                case 32: return int32Typename;
                case 64: return int64Typename;
                default:
                    std::cerr << "位宽为 " << bits << " 的整数型无法映射到目标类型。" << std::endl;
                    assert(false);
                    return "";
            }
        }
        case 'f': {
            size_t bits = strtol(type.base_typename.c_str() + 1, nullptr, 10);
            switch (bits) {
                case 32: return float32Typename;
                case 64: return float64Typename;
                default:
                    std::cerr << "位宽为 " << bits << " 的小数型无法映射到目标类型。" << std::endl;
                    assert(false);
                    return "";
            }
        }
        default:
            std::cerr << "未知的基础类型 " << type.base_typename << std::endl;
            assert(false);
            return "";
    }
}

std::string GenerateParameterType(const struct TypeDesc &type) {
    switch (type.base_typename[0]) {
        case 'v': return "";
        case 'i': {
            size_t bits = strtol(type.base_typename.c_str() + 1, nullptr, 10);
            switch (bits) {
                case 8: return int8Typename;
                case 16: return int16Typename;
                case 32: return int32Typename;
                case 64: return int64Typename;
                default:
                    std::cerr << "位宽为 " << bits << " 的整数型无法映射到目标类型。" << std::endl;
                    assert(false);
                    return "";
            }
        }
        case 'f': {
            size_t bits = strtol(type.base_typename.c_str() + 1, nullptr, 10);
            switch (bits) {
                case 32: return float32Typename;
                case 64: return float64Typename;
                default:
                    std::cerr << "位宽为 " << bits << " 的小数型无法映射到目标类型。" << std::endl;
                    assert(false);
                    return "";
            }
        }
        case '*': {
            return "通用型";
        }
        default:
            return type.base_typename;
    }
}

std::string GenerateParameterTypeAttributes(const struct TypeDesc &type) {
    std::vector<std::string> type_attribute_list;
    if (type.is_reference) {
        type_attribute_list.emplace_back("传址");
    }
    if (type.is_array) {
        type_attribute_list.emplace_back("数组");
    }
    if (type.is_nullable) {
        type_attribute_list.emplace_back("可空");
    }
    return StringUtil::Join<std::vector, std::string>(type_attribute_list, " ");
}

int GenerateInterface(std::ostream &outs, const struct InterfaceDeclare &interfaceDeclare) {
    outs
            << ".LIB命令 " << interfaceDeclare.interface_reference_name << ","
            << " " << GenerateReturnType(interfaceDeclare.return_type) << ","
            << " \"" << interfaceDeclare.library_name << "\","
            << " \"" << interfaceDeclare.interface_api_name << "\","
            << " " /* 此处应填写属性列表 */ ","
            << " " << StringUtil::Join<std::vector, std::string>(interfaceDeclare.interface_breif.comments, " ")
            << std::endl;

    for (const struct ParameterDesc &__parameter_desc : interfaceDeclare.parameters) {
        outs
                << "    " << ".参数"
                << " " << __parameter_desc.parameter_name << ","
                << " " << GenerateParameterType(__parameter_desc.type_desc) << ","
                << " " << GenerateParameterTypeAttributes(__parameter_desc.type_desc) << ","
                << " " << StringUtil::Join<std::vector, std::string>(__parameter_desc.parameter_comments.comments, " ")
                << std::endl;
    }

    outs << std::endl;
    return 0;
}
