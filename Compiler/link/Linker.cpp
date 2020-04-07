//
// Created by rex on 2020/3/20.
//

#include <vector>
#include <string>
#include <llvm/Support/Host.h>
#include <cstdlib>
#include <iostream>

#include "Linker.h"
#include "../../lite_util/StringUtil.h"
#include "../../lite_util/ContainerUtil.h"
#include "../support/ProjectDB.h"
#include "../opene_compiler/ASTContext.h"
#include "../support/ProgramDB.h"

namespace opene {
    int Linker::LinkProject(ProjectDB &projectDB) {

        // 中间文件
        std::string objectFilename = projectDB.GetObjectFilename();
        // 可执行文件
        std::string executeFilename = projectDB.GetExecuteFilename();
        // 依赖库
        std::vector<opene::StringRef> dependenceLibs = projectDB.GetASTContext().GetDependenceLibraries();

        std::vector<std::string> libSearchDirs = program_db.GetLibraryPath();
        auto lib_search_dirs_flag = ContainerUtil::Map<std::vector, std::string, std::vector, std::string>(libSearchDirs, [](const std::string &dir){ return "-L" + dir; });
        auto lib_search_dirs_flag_str = StringUtil::Join<std::vector>(lib_search_dirs_flag, " ");
        auto libraries_link_flag = ContainerUtil::Map<std::vector, std::string, std::vector, opene::StringRef>(dependenceLibs, [](const opene::StringRef &elem){ return "-l" + elem.str(); });
        auto libraries_link_flag_str = StringUtil::Join<std::vector>(libraries_link_flag, " ");
        std::string link_exec = LINKER;
        std::string target_triple = llvm::sys::getDefaultTargetTriple();
        std::string link_cmd = StringUtil::Sprintf(
                "%s %s %s %s -o %s -target %s",
                link_exec.c_str(),
                lib_search_dirs_flag_str.c_str(),
                objectFilename.c_str(),
                libraries_link_flag_str.c_str(),
                executeFilename.c_str(),
                target_triple.c_str()
        );
#if defined(NO_MSVCRT_DEFAULT)
        link_cmd += " -z /NODEFAULTLIB:libcmt.lib";
#endif
        int link_ret = system(link_cmd.c_str());
        if (link_ret == 0) {
            remove(objectFilename.c_str());
        } else {
            std::cerr << link_cmd << std::endl;
        }
        return link_ret;
    }
}
