//
// Created by rex on 2020/3/20.
//

#ifndef OPENELANGUAGE_LINKER_H
#define OPENELANGUAGE_LINKER_H

#include "../opene_compiler/common_rt/StringRef.h"

namespace opene {

    class ProjectDB;

    class Linker {
    private:
        // 中间文件
        std::string objectFilename;
        // 可执行文件
        std::string executeFilename;
        // 依赖库
        std::vector<opene::StringRef> dependenceLibs;
        // 库搜索路径
        std::vector<std::string> libSearchDirs;
    private:
        std::string BuildLinkCommandLine();
    public:
        Linker();
        int LinkProject(ProjectDB &projectDB);
    };

}

#endif //OPENELANGUAGE_LINKER_H
