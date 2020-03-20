//
// Created by rex on 2020/3/20.
//

#ifndef OPENELANGUAGE_PROJECT_DB_H
#define OPENELANGUAGE_PROJECT_DB_H

#include <string>
#include <vector>

namespace opene {

    class TranslateUnit;
    class ASTContext;

    class ProjectDB {
    private:
        std::string project_name_;
        std::vector<std::string> file_list_;
        TranslateUnit *translate_unit_ = nullptr;

    public:
        void SetProjectName(const std::string &project_name);
        const std::string & GetProjectName();
        std::string GetProjectName() const;

        void SetFileList(const std::vector<std::string> &filelist);
        const std::vector<std::string> &GetFileList();
        std::vector<std::string> GetFileList() const;

        void SetTranslateUnit(TranslateUnit *translateUnit);
        TranslateUnit * GetTranslateUnit();
        const TranslateUnit * GetTranslateUnit() const;
        ASTContext &GetASTContext();
        const ASTContext &GetASTContext() const;

        std::string GetObjectFilename() const;
        std::string GetExecuteFilename() const;
    };

}
#endif //OPENELANGUAGE_PROJECT_DB_H
