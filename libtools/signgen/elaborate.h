//
// Created by Administrator on 2020/4/18.
//

#ifndef __REXLANG_ELABORATE_H__
#define __REXLANG_ELABORATE_H__

#include "../CDecl/cdecl.h"

class Elaborate {
public:
    static int ElaborateVariArgs(struct InterfaceDeclare &interfaceDeclare);
    static int ElaborateInterfaceNameReplace(InterfaceDeclare &interfaceDeclare);
    static int ElaborateInterface(struct InterfaceDeclare &interfaceDeclare);
};


#endif //__REXLANG_ELABORATE_H__
