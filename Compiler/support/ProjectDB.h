//
// Created by rex on 2020/3/20.
//

#ifndef REXLANG_PROJECTDB_H
#define REXLANG_PROJECTDB_H

#include <string>
#include <vector>

namespace rexlang {

    struct TranslateUnit;
    struct FunctorDecl;
    class ASTContext;
    class ArgumentParser;

    /*!
     * 项目数据库
     * 包含众多与项目相关的信息
     */
    class ProjectDB {
    private:
        /*!
         * 随机字符串
         * 在初始化对象时被创建
         * 当项目名称和生成目标名称未指定时使用此字符串替代
         */
        std::string random_string_;
        /*!
         * 项目名称
         * 如果未指定则使用随机字符串替代
         */
        std::string project_name_;
        /*!
         * 项目中的文件列表
         */
        std::vector<std::string> file_list_;
        /*!
         * 生成目标二进制文件名
         */
        std::string target_bin_name_;
        /*!
         * 输入的翻译单元
         */
        TranslateUnit *translate_unit_;
        /*!
         * 主入口函数名称
         */
        std::string main_entry_name_;
        /*!
         * 主入口函数定义
         */
        FunctorDecl *main_entry_;

    public:
        ProjectDB();
        bool                                ApplyArgument       (const ArgumentParser &argumentParser);

        void                                SetProjectName      (const std::string &project_name);
        const std::string &                 GetProjectName      () const;
        std::string                         GetProjectName      ();

        void                                SetFileList         (const std::vector<std::string> &filelist);
        const std::vector<std::string> &    GetFileList         () const;
        std::vector<std::string>            GetFileList         ();

        void                                SetTargetBinName    (const std::string &targetBinName);
        const std::string &                 GetTargetBinName    () const;
        std::string                         GetTargetBinName    ();

        void                                SetTranslateUnit    (TranslateUnit *translateUnit);
        TranslateUnit *                     GetTranslateUnit    ();
        const TranslateUnit *               GetTranslateUnit    () const;
        ASTContext &                        GetASTContext       ();
        const ASTContext &                  GetASTContext       () const;

        std::string                         GetBitCodeFilename  () const;
        std::string                         GetObjectFilename   () const;
        std::string                         GetExecuteFilename  () const;

        void                                SetMainEntryName    (const std::string &main_entry_name);
        std::string &                       GetMainEntryName    ();
        const std::string &                 GetMainEntryName    () const;

        void                                SetMainEntry        (FunctorDecl *main_entry);
        FunctorDecl *                       GetMainEntry        ();
        const FunctorDecl *                 GetMainEntry        () const;
    };

}
#endif //REXLANG_PROJECTDB_H
