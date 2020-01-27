//
// Created by rex on 2020/1/21.
//

#ifndef OPENELANGUAGE_ASTCONTEXT_H
#define OPENELANGUAGE_ASTCONTEXT_H

#include "StringRef.h"
#include "Location.h"
#include "Diagnostic.h"

namespace opene {

    class ASTContext {
    private:
        StringPool string_pool_;
        LocationPool location_pool_;
        Diagnostic *diagnostic_ = nullptr;
    public:
        StringRef CreateString(const std::string &str);

        StringRef CreateString(const char *pstr);

        size_t CreateLocation(const std::string &filename, size_t line, size_t column);

        size_t CreateLocation(const StringRef &filename, size_t line, size_t column);

        void SetDiagnostic(Diagnostic *diagnostic);

        Diagnostic *GetDiagnostic();
    };

}

#endif //OPENELANGUAGE_ASTCONTEXT_H
