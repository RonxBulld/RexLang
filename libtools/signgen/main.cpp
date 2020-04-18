//
// Created by Administrator on 2020/4/14.
//

#include <iostream>
#include <fstream>
#include <assert.h>

#include "../CDecl/cdecl.h"
#include "elaborate.h"
#include "generate_target.h"

int SetLibrary(struct InterfaceDeclareList &interfaceDeclareList, const std::string &libraryName) {
    for (struct InterfaceDeclare &__interface_declare : interfaceDeclareList.interface_declare_list) {
        __interface_declare.library_name = libraryName;
    }
    return 0;
}

int main(int argc, char **argv) {
    struct InterfaceDeclareList __interface_declare_list;
    ReadDeclFiles("newcore.h", {}, __interface_declare_list);
    SetLibrary(__interface_declare_list, "corelib");
    std::cout << "找到 " << __interface_declare_list.interface_declare_list.size() << " 个接口。" << std::endl;
//    __interface_declare_list.printToString(std::cout, "");

    std::ofstream __interface_out;
    __interface_out.open("interface_output.txt");
    if (!__interface_out.is_open()) {
        return __LINE__;
    }

    __interface_out << ".版本 2" << std::endl;
    __interface_out << std::endl;
    for (struct InterfaceDeclare &__interface_declare : __interface_declare_list.interface_declare_list) {
        std::cout << "开始为 " << __interface_declare.interface_api_name << " 生成" << GetTargetLanguageName() << "接口。" << std::endl;
        Elaborate::ElaborateInterface(__interface_declare);
        GenerateInterface(__interface_out, __interface_declare);
    }
    __interface_out.close();
    return 0;
}

