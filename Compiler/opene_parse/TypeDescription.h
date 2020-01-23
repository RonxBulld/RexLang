//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_TYPEDESCRIPTION_H
#define OPENELANGUAGE_TYPEDESCRIPTION_H

namespace opene {

    namespace type {

        // 访问级别
        enum class AccessLevel {
            kALPublic,      // 公开
            kALPrivate,     // 私有
        };

        // 传值方式
        enum class ValueTransferMode {
            kVTMValue,      // 传值
            kVTMReference,  // 传址
        };

    }

}

#endif //OPENELANGUAGE_TYPEDESCRIPTION_H
