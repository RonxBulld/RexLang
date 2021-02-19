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
#include <clang/Basic/DiagnosticFrontend.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/VirtualFileSystem.h>

#include "Linker.h"
#include "../../lite_util/StringUtil.h"
#include "../../lite_util/ContainerUtil.h"
#include "../support/ProjectDB.h"
#include "../rexlang_compiler/ASTContext.h"
#include "../support/ProgramDB.h"
#include "lld-driver.h"

#define TSTR(t) #t

namespace rexlang {
    Linker::Linker() : libSearchDirs(program_db.GetLibraryPath()) {
    }

    std::vector<std::string> Linker::BuildUserLevelLinkCommandArgs() {
        std::string target_triple = llvm::sys::getDefaultTargetTriple();
        std::vector<std::string> user_level_args;

#if defined(MSVC_LINKER_STYLE)

        auto lib_search_dirs_flag = ContainerUtil::Map<std::vector<std::string>, std::vector<std::string>>(libSearchDirs, [](const std::string &dir){ return "-L" + dir + ""; });
        auto libraries_link_flag = ContainerUtil::Map<std::vector<std::string>, std::vector<rexlang::StringRef>>(dependenceLibs, [](const rexlang::StringRef &elem){ return "-l" + elem.str(); });
        user_level_args.insert(user_level_args.end(), lib_search_dirs_flag.begin(), lib_search_dirs_flag.end());
        user_level_args.insert(user_level_args.end(), objectFilename);
        user_level_args.insert(user_level_args.end(), libraries_link_flag.begin(), libraries_link_flag.end());
        user_level_args.insert(user_level_args.end(), { "-o",       targetFilename });
        user_level_args.insert(user_level_args.end(), { "-target",  target_triple });
        user_level_args.insert(user_level_args.end(), { "-lmsvcrtd" });

#elif defined(GNU_LINKER_STYLE)

        auto lib_search_dirs_flag = ContainerUtil::Map<std::vector<std::string>, std::vector<std::string>>(libSearchDirs, [](const std::string &dir){ return "-L" + dir + ""; });
        auto libraries_link_flag = ContainerUtil::Map<std::vector<std::string>, std::vector<rexlang::StringRef>>(dependenceLibs, [](const rexlang::StringRef &elem){ return "-l" + elem.str(); });
        user_level_args.insert(user_level_args.end(), lib_search_dirs_flag.begin(), lib_search_dirs_flag.end());
        user_level_args.insert(user_level_args.end(), objectFilename);
        user_level_args.insert(user_level_args.end(), libraries_link_flag.begin(), libraries_link_flag.end());
        user_level_args.insert(user_level_args.end(), { "-o",       targetFilename });
        user_level_args.insert(user_level_args.end(), { "-target",  target_triple });
        user_level_args.insert(user_level_args.end(), { "-lstdc++" });
        user_level_args.insert(user_level_args.end(), { "-lrex_startup_kit" });

#else

#   error "Unknow what the linker switch style."

#endif
        return user_level_args;
    }

    static void FixupDiagPrefixExeName(clang::TextDiagnosticPrinter *DiagClient, const std::string &Path) {
        // If the clang binary happens to be named cl.exe for compatibility reasons,
        // use clang-cl.exe as the prefix to avoid confusion between clang and MSVC.
        llvm::StringRef ExeBasename(llvm::sys::path::stem(Path));
//        if (ExeBasename.equals_lower("cl"))
//            ExeBasename = "clang-cl";
        DiagClient->setPrefix(ExeBasename);
    }

    int Linker::LinkProject(ProjectDB &projectDB) {

        objectFilename = projectDB.GetObjectFilename();
        targetFilename = projectDB.GetTargetBinName();
        dependenceLibs = projectDB.GetASTContext().getDependenceLibraries();

        // 移除目标文件

        std::filesystem::remove(targetFilename);

        // 构建用户级参数列表

        std::filesystem::path link_exec = program_db.GetProgramPath();
        link_exec = link_exec.parent_path() / LINKER;
        std::vector<std::string> user_level_args = BuildUserLevelLinkCommandArgs();

        // 执行连接

        // 构建工具级参数列表

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

        const clang::driver::JobList &Jobs = Link->getJobs();
        if (Jobs.size() != 1 || !llvm::isa<clang::driver::Command>(*Jobs.begin())) {
            llvm::SmallString<256> Msg;
            llvm::raw_svector_ostream OS(Msg);
            Jobs.Print(OS, "; ", true);
            Diags.Report(clang::diag::err_fe_expected_compiler_job) << OS.str();
            return 1;
        }

        std::vector<std::string> ld_program_args;
        for (const auto &Job : Jobs) {
            const llvm::opt::ArgStringList &arg_string_list = Job.getArguments();
            for (const char *arg : arg_string_list) {
                ld_program_args.push_back(arg);
            }
        }

#   if defined(MSVC_LINKER_STYLE)
        ld_program_args.insert(ld_program_args.begin(), {"-flavor", "link"});
#   elif defined(GNU_LINKER_STYLE)
        ld_program_args.insert(ld_program_args.begin(), {"-flavor", "ld"});
#   else
#       error "Unknow what the linker switch style."
#   endif
        std::string link_args_str = StringUtil::Join<std::vector<std::string>, std::string>(ld_program_args, " ");
        std::string link_cmdline = link_exec.string() + " " + link_args_str;
        int link_ret = system(link_cmdline.c_str());

        if (link_ret == 0) {
//            std::cout << link_cmdline << std::endl;
            remove(objectFilename.c_str());
            std::cout << "连接成功" << std::endl;
        } else {
            std::cerr << link_cmdline << std::endl;
            llvm::SmallString<256> Msg;
            llvm::raw_svector_ostream OS(Msg);
            std::cerr << "连接失败" << std::endl;
            Diags.dump();
            Jobs.Print(OS, "; ", true);
            llvm::errs() << OS.str() << "\n";
        }
        return link_ret;
    }
}
