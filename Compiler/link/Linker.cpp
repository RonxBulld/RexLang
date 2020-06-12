//
// Created by rex on 2020/3/20.
//

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <llvm/Support/Host.h>
#include <clang/Driver/Driver.h>
#include <clang/Driver/Compilation.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Frontend/SerializedDiagnosticPrinter.h>
#include <clang/Frontend/ChainedDiagnosticConsumer.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/VirtualFileSystem.h>

#include "Linker.h"
#include "../../lite_util/StringUtil.h"
#include "../../lite_util/ContainerUtil.h"
#include "../support/ProjectDB.h"
#include "../rexlang_compiler/ASTContext.h"
#include "../support/ProgramDB.h"

namespace rexlang {
    Linker::Linker() : libSearchDirs(program_db.GetLibraryPath()) {
    }

    std::vector<std::string> Linker::BuildUserLevelLinkCommandArgs() {
        std::string target_triple = llvm::sys::getDefaultTargetTriple();

#if defined(MSVC_LINKER_STYLE)

        auto lib_search_dirs_flag = ContainerUtil::Map<std::vector, std::string, std::vector, std::string>(libSearchDirs, [](const std::string &dir){ return "/LIBPATH:\"" + dir + "\""; });
        auto lib_search_dirs_flag_str = StringUtil::Join<std::vector>(lib_search_dirs_flag, " ");
        auto libraries_link_flag = ContainerUtil::Map<std::vector, std::string, std::vector, rexlang::StringRef>(dependenceLibs, [](const rexlang::StringRef &elem){ return "\"" + elem.str() + ".lib\""; });
        auto libraries_link_flag_str = StringUtil::Join<std::vector>(libraries_link_flag, " ");
        link_cmd = StringUtil::Sprintf(
                "%s /link %s %s /OUT:%s",
                objectFilename.c_str(),
                lib_search_dirs_flag_str.c_str(),
                libraries_link_flag_str.c_str(),
                executeFilename.c_str()
        );
#   if defined(NO_MSVCRT_DEFAULT)
//        link_cmd += " /NODEFAULTLIB:MSVCRT";
#   endif

#elif defined(GNU_LINKER_STYLE)

        auto lib_search_dirs_flag = ContainerUtil::Map<std::vector, std::string, std::vector, std::string>(libSearchDirs, [](const std::string &dir){ return "-L" + dir; });
        auto lib_search_dirs_flag_str = StringUtil::Join<std::vector>(lib_search_dirs_flag, " ");
        auto libraries_link_flag = ContainerUtil::Map<std::vector, std::string, std::vector, rexlang::StringRef>(dependenceLibs, [](const rexlang::StringRef &elem){ return "-l" + elem.str(); });
        auto libraries_link_flag_str = StringUtil::Join<std::vector>(libraries_link_flag, " ");
        std::vector<std::string> user_level_args = {
                lib_search_dirs_flag_str,
                objectFilename,
                libraries_link_flag_str,
                "-o",       executeFilename,
                "-target",  target_triple,
        };

#else

#   error "Unknow what the linker switch style."

#endif
        return user_level_args;
    }

    static void FixupDiagPrefixExeName(clang::TextDiagnosticPrinter *DiagClient,
                                       const std::string &Path) {
        // If the clang binary happens to be named cl.exe for compatibility reasons,
        // use clang-cl.exe as the prefix to avoid confusion between clang and MSVC.
        llvm::StringRef ExeBasename(llvm::sys::path::stem(Path));
//        if (ExeBasename.equals_lower("cl"))
//            ExeBasename = "clang-cl";
        DiagClient->setPrefix(ExeBasename);
    }

    int Linker::LinkProject(ProjectDB &projectDB) {

        objectFilename = projectDB.GetObjectFilename();
        executeFilename = projectDB.GetExecuteFilename();
        dependenceLibs = projectDB.GetASTContext().GetDependenceLibraries();

        // 构建用户级参数列表

        std::string link_exec = LINKER;
        std::vector<std::string> user_level_args = BuildUserLevelLinkCommandArgs();
        std::string link_args_str = StringUtil::Join<std::vector, std::string>(user_level_args, " ");

        // 执行连接

#if defined(REX_USE_EMBED_LINKER)

        // 构建系统级参数列表

        clang::SmallVector<const char *, 256> TheClangStyleArgs;
        for (const std::string &argu : user_level_args) {
            TheClangStyleArgs.push_back(argu.c_str());
        }

        clang::IntrusiveRefCntPtr<clang::DiagnosticIDs> DiagID(new clang::DiagnosticIDs());
        clang::DiagnosticOptions *DiagOpts = new clang::DiagnosticOptions;
        clang::TextDiagnosticPrinter *DiagClient  = new clang::TextDiagnosticPrinter(llvm::errs(), &*DiagOpts);
        FixupDiagPrefixExeName(DiagClient, program_db.GetProgramPath());

        clang::DiagnosticsEngine Diags(DiagID, &*DiagOpts, DiagClient);

        if (!DiagOpts->DiagnosticSerializationFile.empty()) {
            auto SerializedConsumer = clang::serialized_diags::create(DiagOpts->DiagnosticSerializationFile, &*DiagOpts, /*MergeChildRecords=*/true);
            Diags.setClient(new clang::ChainedDiagnosticConsumer(Diags.takeClient(), std::move(SerializedConsumer)));
        }

        ProcessWarningOptions(Diags, *DiagOpts, /*ReportDiags=*/false);

        clang::driver::Driver TheDriver(program_db.GetProgramPath(), llvm::sys::getDefaultTargetTriple(), Diags);
        std::unique_ptr<clang::driver::Compilation> Link(TheDriver.BuildCompilation(TheClangStyleArgs));

        std::string link_cmdline = link_exec + " " + link_args_str;
        int link_ret = 0;
#else
        std::string link_cmdline = link_exec + " " + link_args_str;
        int link_ret = system(link_cmdline.c_str());
#endif

        if (link_ret == 0) {
            std::cout << link_cmdline << std::endl;
            remove(objectFilename.c_str());
            std::cout << "连接成功" << std::endl;
        } else {
            std::cerr << link_cmdline << std::endl;
            std::cerr << "连接失败" << std::endl;
        }
        return link_ret;
    }
}
