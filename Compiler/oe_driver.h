//
// Created by Administrator on 2019/12/13.
//

#ifndef OPENELANGUAGE_OE_DRIVER_H
#define OPENELANGUAGE_OE_DRIVER_H

#include <string>
#include <vector>
#include "opene_compiler/AstGenerate.h"
#include "ir/EmitLLVMIR.h"
#include "codegen/LLCodeGen.h"

namespace opene {

    class TranslateUnit;

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

    class SourceManager {};

    class FileEntry {
    private:
        std::string filename_;
        std::string code_;
        bool valid_ = false;
    public:
        static FileEntry MakeFromFile(const std::string &filename);
        static FileEntry MakeFromCode(const std::string &code, std::string filename = "");

    public:
        const std::string &GetFilename() const;
        const std::string &GetCode() const;
        bool Valid() const;
    };

    class OECompilerInstance {
    private:
        AstGenerate ast_generate_;
        std::string instance_name_;
        std::string parse_code_;
        std::vector<TranslateUnitPtr> translate_units_;
        TranslateUnitPtr major_translate_unit_ = nullptr;
        std::set<StringRef> libraries_name;

    private:
        bool assembleTranslate();

    public:
        int setInstanceName(const std::string &name);

        int setParseCode(const std::string &code);

        SourceManager &getSourceManager();

        TranslateUnitPtr runParser();

        TranslateUnitPtr parseOnFile(const FileEntry &fileEntry);

        bool runSematicAnalysis();

        TranslateUnitPtr getTranslateUnit();
    };

    namespace tooling {
        TranslateUnitPtr BuildASTFromFiles(const std::vector<std::string> &filenames, const std::string &toolname);

        TranslateUnitPtr BuildASTFromCodes(const std::vector<std::string> &codes, const std::string &filename, const std::string &toolname);

        TranslateUnitPtr BuildASTFromCodeWithArgs(const std::vector<FileEntry> &entries, const std::vector<std::string> &args, const std::string &toolname);

        int GenerateCodeFromTranslateUnit(TranslateUnitPtr translateUnit, const std::string &gen_file);

        int LinkExecuteFromObjects(ProjectDB &projectDB);
    }

}

#endif //OPENELANGUAGE_OE_DRIVER_H
