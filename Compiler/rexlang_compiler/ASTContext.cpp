//
// Created by rex on 2020/1/21.
//

#include <filesystem>

#include "ASTContext.h"
#include "utilities/Diagnostic.h"

namespace rexlang {
    ASTContext::ASTContext() = default;

    ASTContext::~ASTContext() = default;

    StringRef ASTContext::createString(const std::string &str) {
        return StringPool::Create(str);
    }

    StringRef ASTContext::createString(const char *pstr) {
        return StringPool::Create(pstr);
    }

    size_t ASTContext::createLocation(const std::string &filename, size_t line, size_t column) {
        std::filesystem::path file_path = std::filesystem::canonical(filename);
        return this->location_pool_.createLocation(StringPool::Create(file_path.string()), line, column);
    }

    size_t ASTContext::createLocation(const StringRef &filename, size_t line, size_t column) {
        return createLocation(filename.str(), line, column);
    }

    const StringRef &ASTContext::getFileFromLocate(size_t locate) {
        return this->location_pool_.GetFilename(locate);
    }

    size_t ASTContext::getLineFromLocate(size_t locate) {
        return this->location_pool_.GetLineNumber(locate);
    }

    size_t ASTContext::getColumnFromLocate(size_t locate) {
        return this->location_pool_.GetColumnNumber(locate);
    }

    void            ASTContext::setDiagnostic(Diagnostic *diagnostic)   { this->diagnostic_ = diagnostic; }
    Diagnostic *    ASTContext::getDiagnostic()                         { return this->diagnostic_; }

    void            ASTContext::setTranslateUnit(TranslateUnit *translateUnit)  { this->translate_unit_ = translateUnit; }
    TranslateUnit * ASTContext::getTranslateUnit() const                        { return this->translate_unit_; }

    size_t ASTContext::GetNodeIndex() {
        return this->node_index_++;
    }

    void ASTContext::addDependenceLibrary(const StringRef &library_name) {
        this->dependence_libraries_.insert(library_name);
    }

    std::vector<StringRef> ASTContext::getDependenceLibraries() const {
        std::vector<StringRef> libraries;
        for (const StringRef &library : this->dependence_libraries_) {
            libraries.push_back(library);
        }
        return libraries;
    }

    void  ASTContext::cleanScopeStack()            {
        while (currentScope()) {
            popScope(currentScope());
        }
    }
    void  ASTContext::pushScope      (Node *scope) { scope_stack_.push(scope); }
    Node *ASTContext::currentScope   () const      { return scope_stack_.empty() ? nullptr : scope_stack_.top(); }
    void  ASTContext::popScope       (Node *scope) { assert(currentScope() == scope); scope_stack_.pop(); }

}
