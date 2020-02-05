//
// Created by rex on 2020/1/21.
//

#include "ASTContext.h"
#include "Diagnostic.h"

namespace opene {
    ASTContext::ASTContext() = default;

    ASTContext::~ASTContext() = default;

    StringRef ASTContext::CreateString(const std::string &str) {
        return this->string_pool_.Create(str);
    }

    StringRef ASTContext::CreateString(const char *pstr) {
        return this->string_pool_.Create(pstr);
    }

    size_t ASTContext::CreateLocation(const std::string &filename, size_t line, size_t column) {
        return this->location_pool_.CreateLocation(this->string_pool_.Create(filename), line, column);
    }

    size_t ASTContext::CreateLocation(const StringRef &filename, size_t line, size_t column) {
        return this->location_pool_.CreateLocation(filename, line, column);
    }

    void ASTContext::SetDiagnostic(Diagnostic *diagnostic) {
        this->diagnostic_ = diagnostic;
    }

    Diagnostic *ASTContext::GetDiagnostic() {
        return this->diagnostic_;
    }

    size_t ASTContext::GetNodeIndex() {
        return this->node_index_++;
    }
}
