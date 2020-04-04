//
// Created by rexfield on 2020/4/4.
//

#ifndef OPENELANGUAGE_SIMPLERTTI_ARGUTYPE_H
#define OPENELANGUAGE_SIMPLERTTI_ARGUTYPE_H

enum SimpleRTTI_ArguType : char {
    /* Integer */
    kInt8 = 'c', kInt16 = 'w', kInt32 = 'd', kInt64 = 'q',
    /* Float */
    kFloat = 'f', kDouble = 'e',
    /* Aggregates */
    kArray = 'a', kString = 's', kStruct = 't',
};

unsigned GetTypeStorageSize(SimpleRTTI_ArguType ty) {
    switch (ty) {
        case SimpleRTTI_ArguType::kInt8:    return 1;
        case SimpleRTTI_ArguType::kInt16:   return 2;
        case SimpleRTTI_ArguType::kInt32:   return 4;
        case SimpleRTTI_ArguType::kInt64:   return 8;
        case SimpleRTTI_ArguType::kFloat:   return 4;
        case SimpleRTTI_ArguType::kDouble:  return 8;
        case SimpleRTTI_ArguType::kArray:   return 8;
        case SimpleRTTI_ArguType::kString:  return 8;
        case SimpleRTTI_ArguType::kStruct:  return 8;
        default:                            return 0;
    }
}

#endif //OPENELANGUAGE_SIMPLERTTI_ARGUTYPE_H
