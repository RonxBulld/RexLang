//
// Created by rex on 2020/1/28.
//

#ifndef REXLANG_ASTFETCHSUBNODE_H
#define REXLANG_ASTFETCHSUBNODE_H

#include <set>

#include "../NodeDecl.h"
#include "../../../lite_util/ErrOr.h"

namespace rexlang {

    class ASTFetchSubnode {
    public:
        class ASTFetchResult {
        public:
            class Iterator {
            private:
                std::set<const Node *>::const_iterator iterator_;
            public:
                Iterator(std::set<const Node *>::const_iterator iterator) : iterator_(iterator) {}
                bool operator != (const Iterator &other) { return this->iterator_ != other.iterator_; }
                Iterator &operator ++ () { this->iterator_.operator++(); return *this; }
                const Node *operator * () { return *this->iterator_; }
            };
        private:
            std::set<const Node *> nodes;
        public:
            void AddNode(const Node *node);

            Iterator begin() const { return Iterator(this->nodes.begin()); }

            Iterator end() const { return Iterator(this->nodes.end()); }
        };

    public:
        static bool FetchSubNode                (const Node *node, ASTFetchResult &result);
        static ErrOr<ASTFetchResult> FetchSubNode(const Node *node);

    public:
        static bool FetchTranslateUnit          (const TranslateUnit *translateUnit             , ASTFetchResult &result);
        static bool FetchSourceFile             (const SourceFile *sourceFile                   , ASTFetchResult &result);
        static bool FetchProgramSetFile         (const ProgramSetFile *programSetFile           , ASTFetchResult &result);
        static bool FetchGlobalVariableFile     (const GlobalVariableFile *globalVariableFile   , ASTFetchResult &result);
        static bool FetchDataStructureFile      (const DataStructureFile *dataStructureFile     , ASTFetchResult &result);
        static bool FetchAPIDeclareFile         (const APIDeclareFile *apiDeclareFile           , ASTFetchResult &result);
        static bool FetchDecl                   (const Decl *decl                               , ASTFetchResult &result);
        static bool FetchTagDecl                (const TagDecl *tagDecl                         , ASTFetchResult &result);
        static bool FetchVariableDecl           (const VariableDecl *variableDecl               , ASTFetchResult &result);
        static bool FetchBaseVariDecl           (const BaseVariDecl *baseVariDecl               , ASTFetchResult &result);
        static bool FetchGlobalVariableDecl     (const GlobalVariableDecl *globalVariableDecl   , ASTFetchResult &result);
        static bool FetchParameterDecl          (const ParameterDecl *parameterDecl             , ASTFetchResult &result);
        static bool FetchMemberVariableDecl     (const MemberVariableDecl *memberVariableDecl   , ASTFetchResult &result);
        static bool FetchFileVariableDecl       (const FileVariableDecl *fileVariableDecl       , ASTFetchResult &result);
        static bool FetchLocalVariableDecl      (const LocalVariableDecl *localVariableDecl     , ASTFetchResult &result);
        static bool FetchTypeDecl               (const TypeDecl *typeDecl                       , ASTFetchResult &result);
        static bool FetchBuiltinTypeDecl        (const BuiltinTypeDecl *builtinTypeDecl         , ASTFetchResult &result);
        static bool FetchArrayDecl              (const ArrayDecl *arrayDecl                     , ASTFetchResult &result);
        static bool FetchStructureDecl          (const StructureDecl *structureDecl             , ASTFetchResult &result);
        static bool FetchSubProgDecl            (const FunctionDecl *subProgDecl                 , ASTFetchResult &result);
        static bool FetchProgSetDecl            (const ProgSetDecl *progSetDecl                 , ASTFetchResult &result);
        static bool FetchDllCommandDecl         (const APICommandDecl *dllCommandDecl           , ASTFetchResult &result);
        static bool FetchStatement              (const Statement *statement                     , ASTFetchResult &result);
        static bool FetchIfStmt                 (const IfStmt *ifStmt                           , ASTFetchResult &result);
        static bool FetchStatementBlock         (const StatementBlock *statementBlock           , ASTFetchResult &result);
        static bool FetchLoopStatement          (const LoopStatement *loopStatement             , ASTFetchResult &result);
        static bool FetchWhileStmt              (const WhileStmt *whileStmt                     , ASTFetchResult &result);
        static bool FetchRangeForStmt           (const RangeForStmt *rangeForStmt               , ASTFetchResult &result);
        static bool FetchForStmt                (const ForStmt *forStmt                         , ASTFetchResult &result);
        static bool FetchDoWhileStmt            (const DoWhileStmt *doWhileStmt                 , ASTFetchResult &result);
        static bool FetchAssignStmt             (const AssignStmt *assignStmt                   , ASTFetchResult &result);
        static bool FetchControlStmt            (const ControlStmt *controlStmt                 , ASTFetchResult &result);
        static bool FetchLoopControlStmt        (const LoopControlStmt *loopControlStmt         , ASTFetchResult &result);
        static bool FetchContinueStmt           (const ContinueStmt *continueStmt               , ASTFetchResult &result);
        static bool FetchBreakStmt              (const BreakStmt *breakStmt                     , ASTFetchResult &result);
        static bool FetchReturnStmt             (const ReturnStmt *returnStmt                   , ASTFetchResult &result);
        static bool FetchExitStmt               (const ExitStmt *exitStmt                       , ASTFetchResult &result);
        static bool FetchExpression             (const Expression *expression                   , ASTFetchResult &result);
        static bool FetchTypeConvert            (const TypeConvert *expression                  , ASTFetchResult &result);
        static bool FetchHierarchyIdentifier    (const HierarchyIdentifier *hierarchyIdentifier , ASTFetchResult &result);
        static bool FetchNameComponent          (const NameComponent *nameComponent             , ASTFetchResult &result);
        static bool FetchIdentifier             (const Identifier *identifier                   , ASTFetchResult &result);
        static bool FetchArrayIndex             (const ArrayIndex *arrayIndex                   , ASTFetchResult &result);
        static bool FetchFunctionCall           (const FunctionCall *functionCall               , ASTFetchResult &result);
        static bool FetchUnaryExpression        (const UnaryExpression *unaryExpression         , ASTFetchResult &result);
        static bool FetchBinaryExpression       (const BinaryExpression *binaryExpression       , ASTFetchResult &result);
        static bool Fetch_OperatorExpression    (const _OperatorExpression *operatorExpression  , ASTFetchResult &result);
    };

}

#endif //REXLANG_ASTFETCHSUBNODE_H
