//
// Created by Administrator on 2019/12/13.
//

#ifndef REXLANG_OE_DRIVER_H
#define REXLANG_OE_DRIVER_H

#include <string>
#include <vector>
#include "rexlang_compiler/AstGenerate.h"
#include "ir/EmitLLVMIR.h"
#include "codegen/LLCodeGen.h"
#include "link/Linker.h"
#include "support/ProjectDB.h"

namespace rexlang {

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

    class REXCompilerInstance {
    private:
        AstGenerate ast_generate_;
        std::string instance_name_;
        std::string code_filename_;
        std::string parse_code_;
        std::vector<TranslateUnitPtr> translate_units_;
        TranslateUnitPtr major_translate_unit_ = nullptr;
        std::set<StringRef> libraries_name;

    private:
        bool assembleTranslate();

    public:
        int setInstanceName(const std::string &name);

        int setParseCode(const std::string &code);

        int setParseFilename(const std::string &filename);

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

#endif //REXLANG_OE_DRIVER_H
