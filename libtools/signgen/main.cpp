//
// Created by Administrator on 2020/4/14.
//

#include <iostream>
#include <fstream>
#include <assert.h>

#include "../CDecl/cdecl.h"
#include "../../lite_util/StringUtil.h"
#include "elaborate.h"

const char *targetLanguageName = "Rex语言";
const char *int8Typename = "字节型";
const char *int16Typename = "短整型";
const char *int32Typename = "整数型";
const char *int64Typename = "长整数型";
const char *float32Typename = "小数型";
const char *float64Typename = "双精度小数型";
const char *pointerTypename = int32Typename;

std::string generateReturnType(const struct TypeDesc &type) {
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

std::string generateParameterType(const struct TypeDesc &type) {
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

std::string generateParameterTypeAttributes(const struct TypeDesc &type) {
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

int generateInterface(std::ostream &outs, const struct InterfaceDeclare &interfaceDeclare) {
    std::cout << "开始为 " << interfaceDeclare.interface_api_name << " 生成" << targetLanguageName << "接口。" << std::endl;

    outs
        << ".LIB命令 " << interfaceDeclare.interface_reference_name << ","
        << " " << generateReturnType(interfaceDeclare.return_type) << ","
        << " \"" /* 此处应填写所属库名 */ "\","
        << " \"" << interfaceDeclare.interface_api_name << "\","
        << " " /* 此处应填写属性列表 */ ","
        << " " << StringUtil::Join<std::vector, std::string>(interfaceDeclare.interface_breif.comments, " ")
        << std::endl;

    for (const struct ParameterDesc &__parameter_desc : interfaceDeclare.parameters) {
        outs
            << "    " << ".参数"
            << " " << __parameter_desc.parameter_name << ","
            << " " << generateParameterType(__parameter_desc.type_desc) << ","
            << " " << generateParameterTypeAttributes(__parameter_desc.type_desc) << ","
            << " " << StringUtil::Join<std::vector, std::string>(__parameter_desc.parameter_comments.comments, " ")
            << std::endl;
    }
    return 0;
}

int main(int argc, char **argv) {
    struct InterfaceDeclareList __interface_declare_list;
    ReadDeclFiles("newcore.h", {}, __interface_declare_list);
    std::cout << "找到 " << __interface_declare_list.interface_declare_list.size() << " 个接口。" << std::endl;
    __interface_declare_list.printToString(std::cout, "");

    std::ofstream __interface_out;
    __interface_out.open("interface_output.txt");
    if (!__interface_out.is_open()) {
        return __LINE__;
    }

    __interface_out << ".版本 2" << std::endl;
    __interface_out << std::endl;
    for (struct InterfaceDeclare &__interface_declare : __interface_declare_list.interface_declare_list) {
        Elaborate::ElaborateInterface(__interface_declare);
        generateInterface(std::cout, __interface_declare);
    }
    return 0;
}

