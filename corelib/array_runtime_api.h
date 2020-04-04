//
// Created by rex on 2020/3/22.
//

#ifndef OPENELANGUAGE_ARRAY_RUNTIME_API_H
#define OPENELANGUAGE_ARRAY_RUNTIME_API_H

extern "C" {

typedef char *RTDynArrayTy;

RTDynArrayTy create_array(int, ...);
void init_array_32bit(RTDynArrayTy, int, ...);
int *get_array_ep_32bit(RTDynArrayTy, int, ...);

};

#endif //OPENELANGUAGE_ARRAY_RUNTIME_API_H
