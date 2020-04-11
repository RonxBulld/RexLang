//
// Created by rexfield on 2020/4/4.
//

#ifndef REXLANG_STRING_RUNTIME_API_H
#define REXLANG_STRING_RUNTIME_API_H


extern "C" {

typedef char *RTDynStringTy;

RTDynStringTy create_string(const char *stringLiteral);
const char *string_data_ref(const RTDynStringTy dynString);
RTDynStringTy clone_string(const RTDynStringTy dynString);

};


#endif //REXLANG_STRING_RUNTIME_API_H
