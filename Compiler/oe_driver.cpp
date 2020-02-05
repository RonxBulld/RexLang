//
// Created by Administrator on 2019/12/13.
//

#include <fstream>
#include <utility>
#include "oe_driver.h"
#include "opene_compiler/SematicAnalysis.h"

namespace opene {
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

namespace opene {
    TranslateUnitPtr tooling::BuildASTFromFiles(const std::vector<std::string> &filenames, const std::string &toolname) {
        std::vector<FileEntry> enties;
        for (const std::string &filename : filenames) {
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
        OECompilerInstance compilerInstance;
        compilerInstance.setInstanceName(toolname);
        bool all_parse_success = true;
        for (const FileEntry &entry : entries) {
            assert(entry.Valid());
            compilerInstance.setParseCode(entry.GetCode());
            if (compilerInstance.runParser() == nullptr) {
                all_parse_success = false;
            }
        }
        if (all_parse_success) {
            if (compilerInstance.runSematicAnalysis() == false) {
                return nullptr;
            }
        }
        return compilerInstance.getTranslateUnit();
    }
}

namespace opene {
    int OECompilerInstance::setInstanceName(const std::string &name) {
        this->instance_name_ = name;
        return 0;
    }

    int OECompilerInstance::setParseCode(const std::string &code) {
        this->parse_code_ = code;
        return 0;
    }

    TranslateUnitPtr OECompilerInstance::runParser() {
        TranslateUnitPtr translate_unit = this->ast_generate_.BuildASTFromCode(this->parse_code_, "", this->instance_name_);
        this->translate_units_.push_back(translate_unit);
        return translate_unit;
    }

    bool OECompilerInstance::assembleTranslate() {
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

    bool OECompilerInstance::runSematicAnalysis() {
        if (this->assembleTranslate() == false) {
            assert(false);
            return false;
        }

        SematicAnalysis sematic_analysis;
        bool sematic_success = sematic_analysis.Run(this->major_translate_unit_);

        return sematic_success;
    }

    TranslateUnitPtr OECompilerInstance::getTranslateUnit() {
        return this->major_translate_unit_;
    }
}