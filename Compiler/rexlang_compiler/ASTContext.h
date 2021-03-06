//
// Created by rex on 2020/1/21.
//

#ifndef REXLANG_ASTCONTEXT_H
#define REXLANG_ASTCONTEXT_H

#include <set>
#include <vector>
#include "../../lite_util/StringRef.h"
#include "utilities/Location.h"

namespace rexlang {

    class Diagnostic;

    class ASTContext {
    private:
        StringPool string_pool_;
        LocationPool location_pool_;
        Diagnostic *diagnostic_ = nullptr;
        size_t node_index_ = 0;
        std::set<StringRef> dependence_libraries_;

    public:
        ASTContext();

        ~ASTContext();

        StringRef CreateString(const std::string &str);

        StringRef CreateString(const char *pstr);

        size_t CreateLocation(const std::string &filename, size_t line, size_t column);

        size_t CreateLocation(const StringRef &filename, size_t line, size_t column);

        const StringRef &GetFileFromLocate(size_t locate);

        size_t GetLineFromLocate(size_t locate);

        size_t GetColumnFromLocate(size_t locate);

        void SetDiagnostic(Diagnostic *diagnostic);

        Diagnostic *GetDiagnostic();

        size_t GetNodeIndex();

        size_t GetLineNumber(size_t position_id);

        void AddDependenceLibrary(const StringRef &library_name);

        std::vector<StringRef> GetDependenceLibraries() const;
    };

}

#endif //REXLANG_ASTCONTEXT_H
