//
// Created by rex on 2020/3/20.
//

#ifndef REXLANG_LINKER_H
#define REXLANG_LINKER_H

#include "../rexlang_compiler/common_rt/StringRef.h"

namespace rexlang {

    class ProjectDB;

    class Linker {
    private:
        // 中间文件
        std::string objectFilename;
        // 可执行文件
        std::string executeFilename;
        // 依赖库
        std::vector<rexlang::StringRef> dependenceLibs;
        // 库搜索路径
        std::vector<std::string> libSearchDirs;
    private:
        std::string BuildLinkCommandLine();
    public:
        Linker();
        int LinkProject(ProjectDB &projectDB);
    };

}

#endif //REXLANG_LINKER_H
