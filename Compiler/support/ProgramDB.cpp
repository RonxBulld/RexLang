//
// Created by rex on 2020/3/22.
//

#include <iostream>
#include <filesystem>
#include "ProgramDB.h"
#include "../../lite_util/Command.h"

namespace rexlang {

    ProgramDB program_db;

    std::string ProgramDBModuleName = "";

    class ProgramDBParamDef {
    public:
        ProgramDBParamDef() {
            ArgumentParser::AddGlobalParam(
                    CmdParameter("", "print-libdirs", "打印库搜索路径", true, ProgramDBModuleName).CfgAsSwitch()
            );
        }
    } programdb_param_def;

    bool ProgramDB::ApplyArgument(const ArgumentParser &argumentParser) {
        if (argumentParser.HadSwitch(ProgramDBModuleName, "print-libdirs")) {
            for (const std::string &libdir : GetLibraryPath()) {
                std::cout << libdir << std::endl;
            }
        }
        return true;
    }

    void ProgramDB::SetProgramPath(const char *programPath) {
        execute_path_.clear();
        include_path_.clear();
        library_path_.clear();
        program_path_ = programPath;

        std::filesystem::path root_path(programPath);
        root_path = std::filesystem::canonical(root_path);
        root_path = root_path.remove_filename();
        root_path /= "..";
        root_path = std::filesystem::canonical(root_path);

        execute_path_.push_back((root_path / "bin").string());
        execute_path_.push_back((root_path / "bin" / "rex").string());
        include_path_.push_back((root_path / "include").string());
        include_path_.push_back((root_path / "include" / "rex").string());
        library_path_.push_back((root_path / "lib").string());
        library_path_.push_back((root_path / "lib" / "rex").string());
    }

    const std::string &ProgramDB::GetProgramPath() const {
        return program_path_;
    }

    const std::vector<std::string> &ProgramDB::GetExecutePath() const {
        return execute_path_;
    }

    const std::vector<std::string> &ProgramDB::GetIncludePath() const {
        return include_path_;
    }

    const std::vector<std::string> &ProgramDB::GetLibraryPath() const {
        return library_path_;
    }

    const char *ProgramDB::GetLibraryHeadFileExt() const {
        return "txt";
    }
}