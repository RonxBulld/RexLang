//
// Created by Administrator on 2020/4/14.
//

#include "../CDecl/cdecl.h"

int main(int argc, char **argv) {
    struct InterfaceDeclare __interface_declare;
    ReadDeclFiles("newcore.h", {}, __interface_declare);
    return 0;
}

