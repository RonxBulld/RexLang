//
// Created by rex on 2020/3/20.
//

#ifndef OPENELANGUAGE_LINKER_H
#define OPENELANGUAGE_LINKER_H

#include "../opene_compiler/common_rt/StringRef.h"

namespace opene {

    class ProjectDB;

    class Linker {
    public:
        int LinkProject(ProjectDB &projectDB);
    };

}

#endif //OPENELANGUAGE_LINKER_H
