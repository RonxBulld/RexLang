//
// Created by rex on 2020/3/20.
//

#ifndef OPENELANGUAGE_PROJECTDB_H
#define OPENELANGUAGE_PROJECTDB_H

#include <string>
#include <vector>

namespace opene {

    class TranslateUnit;
    class ASTContext;
    class ArgumentParser;

    class ProjectDB {
    private:
        std::string random_string_;
        std::string project_name_;
        std::vector<std::string> file_list_;
        std::string target_bin_name_;
        TranslateUnit *translate_unit_;

    public:
        ProjectDB();
        bool ApplyArgument(const ArgumentParser &argumentParser);

        void SetProjectName(const std::string &project_name);
        const std::string & GetProjectName() const;
        std::string GetProjectName();

        void SetFileList(const std::vector<std::string> &filelist);
        const std::vector<std::string> &GetFileList() const;
        std::vector<std::string> GetFileList();

        void SetTargetBinName(const std::string &targetBinName);
        const std::string & GetTargetBinName() const;
        std::string GetTargetBinName();

        void SetTranslateUnit(TranslateUnit *translateUnit);
        TranslateUnit * GetTranslateUnit();
        const TranslateUnit * GetTranslateUnit() const;
        ASTContext &GetASTContext();
        const ASTContext &GetASTContext() const;

        std::string GetObjectFilename() const;
        std::string GetExecuteFilename() const;
    };

}
#endif //OPENELANGUAGE_PROJECTDB_H
