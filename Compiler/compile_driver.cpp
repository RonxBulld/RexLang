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
    TranslateUnitPtr tooling::BuildASTFromFiles(ProjectDB &projectDB, const std::string &toolname) {
        std::vector<FileEntry> enties;
        for (const std::string &filename : projectDB.GetFileList()) {
            enties.push_back(FileEntry::MakeFromFile(filename));
        }
        return tooling::BuildASTFromCodeWithArgs(enties, {}, toolname);
    }

    TranslateUnitPtr tooling::BuildASTFromCodes(const std::vector<std::string> &codes, const std::string &filename, const std::string &toolname) {
        std::vector<FileEntry> enties;
        for (const std::string &code : codes) {
            enties.push_back(FileEntry::MakeFromCode(code));
        }
        return tooling::BuildASTFromCodeWithArgs(enties, {}, toolname);
    }

    TranslateUnitPtr tooling::BuildASTFromCodeWithArgs(const std::vector<FileEntry> &entries, const std::vector<std::string> &args, const std::string &toolname) {
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
        rexlang::EmitLLVMIR emitter(projectDB.GetTranslateUnit(), projectDB);
        emitter.WriteOutIR();
        rexlang::LLCodeGen ll_code_gen(emitter);
        return ll_code_gen.WriteOutBC(projectDB.GetObjectFilename());
    }

    int tooling::LinkExecuteFromObjects(ProjectDB &projectDB) {
        Linker linker;
        return linker.LinkProject(projectDB);
    }
}

namespace rexlang {
    int REXCompilerInstance::setInstanceName(const std::string &name) {
        this->instance_name_ = name;
        return 0;
    }

    int REXCompilerInstance::setParseCode(const std::string &code) {
        this->parse_code_ = code;
        return 0;
    }

    int REXCompilerInstance::setParseFilename(const std::string &filename) {
        this->code_filename_ = filename;
        return 0;
    }

    TranslateUnitPtr REXCompilerInstance::runParser() {

        // 分析指定的源代码文件

        TranslateUnitPtr translate_unit = this->ast_generate_.BuildASTFromCode(this->parse_code_, this->code_filename_, this->instance_name_);
        this->translate_units_.push_back(translate_unit);

        // 对于源代码文件中引入的外部库进行分析

        const std::vector<std::string> &include_dirs = program_db.GetIncludePath();

        if (!translate_unit->source_file_.empty()) {
            if (ProgramSetFile *program_set_file = translate_unit->source_file_.front()->as<ProgramSetFile>()) {
                for (const TString &library : program_set_file->libraries_) {

                    StringRef library_name = library.string_;
                    if (this->libraries_name.find(library_name) != this->libraries_name.end()) {
                        continue;
                    }
                    this->libraries_name.insert(library_name);

                    // 尝试探测库的声明文件

                    FileEntry file_entry;

                    for (const std::string &include_dir : include_dirs) {
                        FileEntry test_file_entry = FileEntry::MakeFromFile(include_dir + "/" + library_name.str() + "." + program_db.GetLibraryHeadFileExt());
                        if (test_file_entry.Valid()) {
                            file_entry = test_file_entry;
                            break;
                        }
                    }
                    assert(file_entry.Valid());

                    TranslateUnit *library_tu = this->parseOnFile(file_entry);
                    assert(library_tu);

                }
            }
        }
        return translate_unit;
    }

    TranslateUnitPtr REXCompilerInstance::parseOnFile(const FileEntry &fileEntry) {
        std::cout << "分析文件：" << fileEntry.GetFilename() << std::endl;
        this->setParseFilename(fileEntry.GetFilename());
        this->setParseCode(fileEntry.GetCode());
        return this->runParser();
    }

    bool REXCompilerInstance::assembleTranslate() {

        // 将翻译单元列表中的项目进行依次组装

        if (this->translate_units_.empty()) { return true; }
        this->major_translate_unit_ = this->translate_units_[0];
        for (size_t idx = 1; idx < this->translate_units_.size(); idx++) {
            if (this->major_translate_unit_->edition_ != this->translate_units_[idx]->edition_) {
                assert(false);
                return false;
            }
            this->major_translate_unit_->source_file_.insert(
                    this->major_translate_unit_->source_file_.end(),
                    this->translate_units_[idx]->source_file_.begin(),
                    this->translate_units_[idx]->source_file_.end()
                    );
        }
        return true;
    }

    bool REXCompilerInstance::runSematicAnalysis() {
        if (this->assembleTranslate() == false) {
            assert(false);
            return false;
        }

        SematicAnalysis sematic_analysis;
        bool sematic_success = sematic_analysis.Run(this->major_translate_unit_);

        return sematic_success;
    }

    TranslateUnitPtr REXCompilerInstance::getTranslateUnit() {
        return this->major_translate_unit_;
    }
}