//
// Created by rex on 2020/3/20.
//

#ifndef REXLANG_LINKER_H
#define REXLANG_LINKER_H

#include "../../lite_util/StringRef.h"

namespace rexlang {

    class ProjectDB;

    class Linker {
    private:
        // 中间文件
        std::string objectFilename;
        // 目标文件
        std::string targetFilename;
        // 依赖库
        std::vector<rexlang::StringRef> dependenceLibs;
        // 库搜索路径
        std::vector<std::string> libSearchDirs;
    private:
        std::vector<std::string> BuildUserLevelLinkCommandArgs();
    public:
        Linker();
        int LinkProject(ProjectDB &projectDB);
    };

}

#endif //REXLANG_LINKER_H
