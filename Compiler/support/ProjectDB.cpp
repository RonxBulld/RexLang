//
// Created by rex on 2020/3/21.
//

#include "ProjectDB.h"
#include "../opene_compiler/NodeDecl.h"

namespace opene {
    void ProjectDB::SetProjectName(const std::string &project_name) {
        project_name_ = project_name;
    }

    const std::string &ProjectDB::GetProjectName() {
        return project_name_;
    }

    std::string ProjectDB::GetProjectName() const {
        return project_name_;
    }

    void ProjectDB::SetFileList(const std::vector<std::string> &filelist) {
        file_list_ = filelist;
    }

    const std::vector<std::string> &ProjectDB::GetFileList() {
        return file_list_;
    }

    std::vector<std::string> ProjectDB::GetFileList() const {
        return file_list_;
    }

    void ProjectDB::SetTranslateUnit(TranslateUnit *translateUnit) {
        translate_unit_ = translateUnit;
    }

    TranslateUnit *ProjectDB::GetTranslateUnit() {
        return translate_unit_;
    }

    const TranslateUnit *ProjectDB::GetTranslateUnit() const {
        return translate_unit_;
    }

    ASTContext &ProjectDB::GetASTContext() {
        return *translate_unit_->ast_context_;
    }

    const ASTContext &ProjectDB::GetASTContext() const {
        return *translate_unit_->ast_context_;
    }

    std::string ProjectDB::GetObjectFilename() const {
        return project_name_ + ".bc";
    }

    std::string ProjectDB::GetExecuteFilename() const {
        return project_name_;
    }
}
