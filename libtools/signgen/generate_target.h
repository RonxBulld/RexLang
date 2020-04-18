//
// Created by rex on 2020/4/18.
//

#ifndef REXLANG_GENERATE_TARGET_H
#define REXLANG_GENERATE_TARGET_H

#include <string>
#include <iostream>

const char *GetTargetLanguageName();
int GenerateInterface(std::ostream &outs, const struct InterfaceDeclare &interfaceDeclare);

#endif //REXLANG_GENERATE_TARGET_H
