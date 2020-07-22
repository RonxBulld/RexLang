//
// Created by rex on 2020/1/21.
//

#ifndef REXLANG_ASTCONTEXT_H
#define REXLANG_ASTCONTEXT_H

#include <set>
#include <vector>
#include <stack>
#include "../../lite_util/StringRef.h"
#include "utilities/Location.h"

namespace rexlang {

    class Node;
    class Diagnostic;
    class TranslateUnit;

    class ASTContext {
    private:
        LocationPool        location_pool_;
        Diagnostic *        diagnostic_ = nullptr;
        size_t              node_index_ = 0;
        std::set<StringRef> dependence_libraries_;
        TranslateUnit *     translate_unit_ = nullptr;
        std::stack<Node *>  scope_stack_;

    public:
        ASTContext();
        ~ASTContext();

        StringRef createString(const std::string & str);
        StringRef createString(const char *        pstr);

        size_t createLocation(const std::string & filename, size_t line, size_t column);
        size_t createLocation(const StringRef &   filename, size_t line, size_t column);

        const StringRef &   getFileFromLocate   (size_t locate);
        size_t              getLineFromLocate   (size_t locate);
        size_t              getColumnFromLocate (size_t locate);

        void            setDiagnostic(Diagnostic *diagnostic);
        Diagnostic *    getDiagnostic();

        void            setTranslateUnit(TranslateUnit *translateUnit);
        TranslateUnit * getTranslateUnit() const;

        void                    addDependenceLibrary  (const StringRef &library_name);
        std::vector<StringRef>  getDependenceLibraries() const;

        size_t GetNodeIndex();

        // TranslateUnit、ProgSetDecl和FunctionDecl会被认为带有Scope性质

        void    cleanScopeStack () ;
        void    pushScope       (Node *scope) ;
        Node *  currentScope    () const ;
        void    popScope        (Node *scope) ;

    };

}

#endif //REXLANG_ASTCONTEXT_H
