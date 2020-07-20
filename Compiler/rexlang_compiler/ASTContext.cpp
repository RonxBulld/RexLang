//
// Created by rex on 2020/1/21.
//

#include <filesystem>

#include "ASTContext.h"
#include "utilities/Diagnostic.h"

namespace rexlang {
    ASTContext::ASTContext() = default;

    ASTContext::~ASTContext() = default;

    StringRef ASTContext::CreateString(const std::string &str) {
        return StringPool::Create(str);
    }

    StringRef ASTContext::CreateString(const char *pstr) {
        return StringPool::Create(pstr);
    }

    size_t ASTContext::CreateLocation(const std::string &filename, size_t line, size_t column) {
        std::filesystem::path file_path = std::filesystem::canonical(filename);
        return this->location_pool_.CreateLocation(StringPool::Create(file_path.string()), line, column);
    }

    size_t ASTContext::CreateLocation(const StringRef &filename, size_t line, size_t column) {
        return CreateLocation(filename.str(), line, column);
    }

    const StringRef &ASTContext::GetFileFromLocate(size_t locate) {
        return this->location_pool_.GetFilename(locate);
    }

    size_t ASTContext::GetLineFromLocate(size_t locate) {
        return this->location_pool_.GetLineNumber(locate);
    }

    size_t ASTContext::GetColumnFromLocate(size_t locate) {
        return this->location_pool_.GetColumnNumber(locate);
    }

    void            ASTContext::SetDiagnostic(Diagnostic *diagnostic)   { this->diagnostic_ = diagnostic; }
    Diagnostic *    ASTContext::GetDiagnostic()                         { return this->diagnostic_; }

    void            ASTContext::SetTranslateUnit(TranslateUnit *translateUnit)  { this->translate_unit_ = translateUnit; }
    TranslateUnit * ASTContext::GetTranslateUnit() const                        { return this->translate_unit_; }

    size_t ASTContext::GetNodeIndex() {
        return this->node_index_++;
    }

    void ASTContext::AddDependenceLibrary(const StringRef &library_name) {
        this->dependence_libraries_.insert(library_name);
    }

    std::vector<StringRef> ASTContext::GetDependenceLibraries() const {
        std::vector<StringRef> libraries;
        for (const StringRef &library : this->dependence_libraries_) {
            libraries.push_back(library);
        }
        return libraries;
    }

    void  ASTContext::pushScope   (Node *scope) { scope_stack_.push(scope); }
    Node *ASTContext::currentScope() const      { return scope_stack_.empty() ? nullptr : scope_stack_.top(); }
    void  ASTContext::popScope    (Node *scope) { assert(currentScope() == scope); scope_stack_.pop(); }

}
