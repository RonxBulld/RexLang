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
#include "link/Linker.h"
#include "support/ProjectDB.h"

namespace opene {

    struct TranslateUnit;

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
        TranslateUnitPtr BuildASTFromFiles(ProjectDB &projectDB, const std::string &toolname);

        TranslateUnitPtr BuildASTFromCodes(const std::vector<std::string> &codes, const std::string &filename, const std::string &toolname);

        TranslateUnitPtr BuildASTFromCodeWithArgs(const std::vector<FileEntry> &entries, const std::vector<std::string> &args, const std::string &toolname);

        int GenerateCodeFromTranslateUnit(ProjectDB &projectDB);

        int LinkExecuteFromObjects(ProjectDB &projectDB);
    }

}

#endif //OPENELANGUAGE_OE_DRIVER_H
