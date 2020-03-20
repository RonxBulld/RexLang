//
// Created by rex on 2020/3/20.
//

#include <vector>
#include <string>
#include <llvm/Support/Host.h>

#include "Linker.h"
#include "../../lite_util/StringUtil.h"
#include "../../lite_util/ContainerUtil.h"

namespace opene {
    int Linker::LinkProject(const std::string &objectFilename, const std::string &executeFilename, std::vector<opene::StringRef> dependenceLibs) {
        auto libraries_link_flag = ContainerUtil::Map<std::vector, std::string>(dependenceLibs, [](opene::StringRef &elem){ return "-l" + elem.str(); });
        auto libraries_link_flag_str = StringUtil::Join(libraries_link_flag, " ");
        std::string link_exec = "clang";
        std::string target_triple = llvm::sys::getDefaultTargetTriple();
        std::string link_cmd = StringUtil::Sprintf(
                "%s -Lcorelib %s %s -o %s -target %s",
                link_exec.c_str(),
                objectFilename.c_str(),
                libraries_link_flag_str.c_str(),
                executeFilename.c_str(),
                target_triple.c_str()
        );
        int link_ret = system(link_cmd.c_str());
        remove(objectFilename.c_str());
        return link_ret;
    }
}