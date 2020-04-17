//
// Created by Administrator on 2020/4/14.
//

#include <iostream>
#include <fstream>

#include "../CDecl/cdecl.h"
#include "../../lite_util/StringUtil.h"

const char *targetLanguageName = "Rex语言";

std::string generateReturnType(const struct TypeDesc &type) {
    if (type.is_array) {
        std::cerr << "返回值类型不允许为数组。" << std::endl;
        return "";
    }
    if (type.is_nullable) {
        std::cerr << "返回值类型不允许为可空。" << std::endl;
        return "";
    }
    bool __is_reference = type.is_reference;

    return "";
}

int generateInterface(std::ostream &outs, const struct InterfaceDeclare &interfaceDeclare) {
    std::cout << "开始为 " << interfaceDeclare.interface_api_name << " 生成" << targetLanguageName << "接口。" << std::endl;

    outs
        << ".LIB命令 " << interfaceDeclare.interface_api_name << ","
        << " " << generateReturnType(interfaceDeclare.return_type) << ","
        << " \"" /* 此处应填写所属库名 */ "\","
        << " \"" << interfaceDeclare.interface_api_name << "\","
        << " " << ","
        << " " << StringUtil::Join<std::vector, std::string>(interfaceDeclare.interface_breif.comments, " ") << std::endl;
    return 0;
}

int main(int argc, char **argv) {
    struct InterfaceDeclareList __interface_declare_list;
    ReadDeclFiles("newcore.h", {}, __interface_declare_list);
    std::cout << "找到 " << __interface_declare_list.interface_declare_list.size() << " 个接口。" << std::endl;

    std::ofstream __interface_out;
    __interface_out.open("interface_output.txt");
    if (!__interface_out.is_open()) {
        return __LINE__;
    }

    __interface_out << ".版本 2" << std::endl;
    __interface_out << std::endl;
    for (const struct InterfaceDeclare &__interface_declare : __interface_declare_list.interface_declare_list) {
        generateInterface(std::cout, __interface_declare);
    }
    return 0;
}

