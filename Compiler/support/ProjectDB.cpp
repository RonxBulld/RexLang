//
// Created by rex on 2020/3/21.
//

#include <filesystem>
#include "ProjectDB.h"
#include "ProgramDB.h"
#include "../rexlang_compiler/NodeDecl.h"
#include "../../lite_util/Command.h"

namespace rexlang {

    const std::string ProjectDBModuleName;

    class ProjectDBParamDef {
    public:
        ProjectDBParamDef() {
            ArgumentParser::AddGlobalParam(CmdParameter("o", "", "生成的目标文件路径", false, ProjectDBModuleName).CfgAsValue());
            ArgumentParser::AddGlobalParam(CmdParameter("", "project", "工程名称", false, ProjectDBModuleName).CfgAsValue());
        }
    } projectdb_param_def;

    void gen_random(char *s, const int len) {
        static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < len; ++i) {
            s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
        }
        s[len] = 0;
    }

    ProjectDB::ProjectDB() : translate_unit_(nullptr), main_entry_(nullptr) {
        char rnd_str[8+1];
        gen_random(rnd_str, sizeof(rnd_str) - 1);
        random_string_ = rnd_str;
        std::error_code EC;
        temp_directory_path_ = (std::filesystem::temp_directory_path(EC) / "rex" / random_string_).string();
        if (!EC) {
            temp_directory_path_ = (std::filesystem::current_path() / "rex_temp" / random_string_).string();
        }
        std::filesystem::remove(temp_directory_path_);
        std::filesystem::create_directories(temp_directory_path_);
    }

    bool ProjectDB::ApplyArgument(const ArgumentParser &argumentParser) {

        if (argumentParser.HadSwitch(ProjectDBModuleName, "project")) {
            auto args = argumentParser.GetSwitchArguments(ProjectDBModuleName, "project");
            SetProjectName(args.back());
        }

        if (argumentParser.HadSwitch(ProjectDBModuleName, "o")) {
            auto args = argumentParser.GetSwitchArguments(ProjectDBModuleName, "o");
            SetTargetBinName(args.back());
        }

        std::vector<std::string> parsing_files;
        for (const std::string &file : argumentParser.GetFreeArguments(ProjectDBModuleName)) {
            parsing_files.emplace_back(file);
        }
        SetFileList(parsing_files);

        return true;
    }

    void               ProjectDB::SetProjectName(const std::string &project_name) { project_name_ = project_name; }
    const std::string &ProjectDB::GetProjectName() const { return project_name_.empty() ? random_string_ : project_name_; }
          std::string  ProjectDB::GetProjectName()       { return project_name_.empty() ? random_string_ : project_name_; }

    void                            ProjectDB::SetFileList(const std::vector<std::string> &filelist) { file_list_ = filelist; }
    const std::vector<std::string> &ProjectDB::GetFileList() const { return file_list_; }
          std::vector<std::string>  ProjectDB::GetFileList()       { return file_list_; }

    void               ProjectDB::SetTargetBinName(const std::string &targetBinName) { target_bin_name_ = targetBinName; }
    const std::string &ProjectDB::GetTargetBinName() const { return target_bin_name_.empty() ? random_string_ : target_bin_name_; }
          std::string  ProjectDB::GetTargetBinName()       { return target_bin_name_.empty() ? random_string_ : target_bin_name_; }

    void                 ProjectDB::setTranslateUnit(TranslateUnit *translateUnit) { translate_unit_ = translateUnit; }
    const TranslateUnit *ProjectDB::getTranslateUnit() const { return translate_unit_; }
          TranslateUnit *ProjectDB::getTranslateUnit()       { return translate_unit_; }

    const ASTContext &ProjectDB::GetASTContext() const { return *translate_unit_->getAstContext(); }
          ASTContext &ProjectDB::GetASTContext()       { return *translate_unit_->getAstContext(); }

    std::string ProjectDB::GetByteCodeFilename() const { return GetProjectName() + "." + program_db.GetByteCodeFileExt(); }
    std::string ProjectDB::GetObjectFilename  () const { return GetProjectName() + "." + program_db.GetObjectFileExt(); }
    std::string ProjectDB::GetExecuteFilename () const { return GetTargetBinName(); }

    void               ProjectDB::SetMainEntryName(const std::string &main_entry_name) { main_entry_name_ = main_entry_name; }
    const std::string &ProjectDB::GetMainEntryName() const { return main_entry_name_; }
          std::string &ProjectDB::GetMainEntryName()       { return main_entry_name_; }

    void               ProjectDB::SetMainEntry(FunctorDecl *main_entry) { main_entry_ = main_entry; }
    const FunctorDecl *ProjectDB::GetMainEntry() const { return main_entry_; }
          FunctorDecl *ProjectDB::GetMainEntry()       { return main_entry_; }

}
