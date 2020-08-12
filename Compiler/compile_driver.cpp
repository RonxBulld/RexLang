//
// Created by Administrator on 2019/12/13.
//

#include <fstream>
#include <utility>
#include "compile_driver.h"
#include "rexlang_compiler/sematic_analysis/SematicAnalysis.h"
#include "../lite_util/StringUtil.h"
#include "../lite_util/ContainerUtil.h"
#include "support/ProgramDB.h"

namespace rexlang {
    FileEntry FileEntry::MakeFromFile(const std::string &filename) {
        FileEntry file_entry;
        file_entry.filename_ = filename;
        std::ifstream ifs;
        ifs.open(filename);
        if (ifs.is_open()) {
            std::string codes((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            file_entry.code_ = codes;
            file_entry.valid_ = true;
        }
        return file_entry;
    }

    FileEntry FileEntry::MakeFromCode(const std::string &code, std::string filename) {
        FileEntry file_entry;
        file_entry.filename_ = std::move(filename);
        file_entry.code_ = code;
        file_entry.valid_ = true;
        return file_entry;
    }

    const std::string &FileEntry::GetFilename() const {
        return this->filename_;
    }

    const std::string &FileEntry::GetCode() const {
        return this->code_;
    }

    bool FileEntry::Valid() const {
        return this->valid_;
    }
}

namespace rexlang {
    TranslateUnit * tooling::BuildASTFromFiles(ProjectDB &projectDB, const std::string &toolname) {
        std::vector<FileEntry> enties;
        for (const std::string &filename : projectDB.GetFileList()) {
            enties.push_back(FileEntry::MakeFromFile(filename));
        }
        return tooling::BuildASTFromCodeWithArgs(enties, {}, toolname);
    }

    TranslateUnit * tooling::BuildASTFromCodes(const std::vector<std::string> &codes, const std::string &filename, const std::string &toolname) {
        std::vector<FileEntry> enties;
        for (const std::string &code : codes) {
            enties.push_back(FileEntry::MakeFromCode(code));
        }
        return tooling::BuildASTFromCodeWithArgs(enties, {}, toolname);
    }

    TranslateUnit * tooling::BuildASTFromCodeWithArgs(const std::vector<FileEntry> &entries, const std::vector<std::string> &args, const std::string &toolname) {
        REXCompilerInstance compilerInstance;
        compilerInstance.setInstanceName(toolname);
        bool all_parse_success = true;
        for (const FileEntry &entry : entries) {
            assert(entry.Valid());
            all_parse_success &= (compilerInstance.parseOnFile(entry) != nullptr);
        }
        if (all_parse_success) {
            if (compilerInstance.runSematicAnalysis() == false) {
                return nullptr;
            }
        }
        return compilerInstance.getTranslateUnit();
    }

    int tooling::GenerateCodeFromTranslateUnit(ProjectDB &projectDB) {
        rexlang::EmitLLVMIR emitter(projectDB.getTranslateUnit(), projectDB);
//        emitter.WriteOutIR();
        rexlang::LLCodeGen ll_code_gen(emitter);
//        if (int EC = ll_code_gen.WriteOutBitCode(projectDB.GetBitCodeFilename())) { return EC; }
        if (int EC = ll_code_gen.WriteOutObject (projectDB.GetObjectFilename()))  { return EC; }
        return 0;
    }

    int tooling::LinkExecuteFromObjects(ProjectDB &projectDB) {
        Linker linker;
        return linker.LinkProject(projectDB);
    }
}

namespace rexlang {

    int REXCompilerInstance::setInstanceName    (const std::string &name)       { this->instance_name_ = name;     return 0; }
    int REXCompilerInstance::setParseCode       (const std::string &code)       { this->parse_code_    = code;     return 0; }
    int REXCompilerInstance::setParseFilename   (const std::string &filename)   { this->code_filename_ = filename; return 0; }

    bool REXCompilerInstance::runParser() {
        return this->runParser(this->parse_code_, this->code_filename_);
    }

    bool REXCompilerInstance::runParser(const std::string &code, const std::string &file) {

        // 分析指定的源代码

        return this->ast_generate_.buildCstFromCode(code, file, this->instance_name_);
    }

    bool REXCompilerInstance::parseOnFile(const FileEntry &fileEntry) {
        std::cout << "分析文件：" << fileEntry.GetFilename() << std::endl;
        return this->runParser(fileEntry.GetCode(), fileEntry.GetFilename());
    }

    FileEntry REXCompilerInstance::detectLibraryFile(const rexlang::StringRef &filePath) {

        FileEntry file_entry;

        for (const std::string &include_dir : program_db.GetIncludePath()) {
            FileEntry test_file_entry = FileEntry::MakeFromFile(include_dir + "/" + filePath.str() + "." + program_db.GetDefaultLibraryHeadFileExt());
            if (test_file_entry.Valid()) {
                file_entry = test_file_entry;
                break;
            }
        }
        return file_entry;
    }

    int REXCompilerInstance::processExternLibrary(const rexlang::StringRef &filePath) {
        FileEntry file_entry = detectLibraryFile(filePath);
        assert(file_entry.Valid());
        bool suc = this->parseOnFile(file_entry);
        assert(suc);
        return 0;
    }

    bool REXCompilerInstance::assembleTranslates() {
        this->major_translate_unit_ = this->ast_generate_.buildAstFromCsts();
        return true;
    }

    bool REXCompilerInstance::runSematicAnalysis() {
        if (this->assembleTranslates() == false) {
            assert(false);
            return false;
        }

        SematicAnalysis sematic_analysis;
        bool sematic_success = sematic_analysis.Run(this->major_translate_unit_);

        return sematic_success;
    }

    TranslateUnit * REXCompilerInstance::getTranslateUnit() {
        return this->major_translate_unit_;
    }
}