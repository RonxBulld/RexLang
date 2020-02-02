//
// Created by Administrator on 2019/12/13.
//

#ifndef OPENELANGUAGE_OE_DRIVER_H
#define OPENELANGUAGE_OE_DRIVER_H

#include <string>
#include <vector>
#include "opene_parse/AstGenerate.h"

namespace opene {

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
    };

    class OECompilerInstance {
    private:
        AstGenerate ast_generate_;
        std::string instance_name_;
        std::string parse_code_;
        std::vector<TranslateUnitPtr> translate_units_;
        TranslateUnitPtr major_translate_unit_ = nullptr;

    private:
        bool assembleTranslate();

    public:
        int setInstanceName(const std::string &name);

        int setParseCode(const std::string &code);

        SourceManager &getSourceManager();

        TranslateUnitPtr runParser();

        bool runSematicAnalysis();

        TranslateUnitPtr getTranslateUnit();
    };

    namespace tooling {
        TranslateUnitPtr BuildASTFromFiles(const std::vector<std::string> &filenames, const std::string &toolname);

        TranslateUnitPtr BuildASTFromCodes(const std::vector<std::string> &codes, const std::string &filename, const std::string &toolname);

        TranslateUnitPtr BuildASTFromCodeWithArgs(const std::vector<FileEntry> &entries, const std::vector<std::string> &args, const std::string &toolname);
    }

}

#endif //OPENELANGUAGE_OE_DRIVER_H
