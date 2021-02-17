//
// Created by rex on 2020/11/3.
//

#ifndef REXLANG_DUMPAST_H
#define REXLANG_DUMPAST_H

#include <sstream>
#include "Visitor.h"

namespace rexlang {

    class DumpASTWritter {
    private:
        std::ostream &OS_;
        Node *latest_node_ = nullptr;
        std::string latest_filename_;

    public:
        explicit DumpASTWritter(std::ostream &OS) ;

    public:
        void NodeEnter(Node &node) ;
        void NodeExit(Node &node) ;

        void PrevAttribute(Node &node) ;
        void PostAttribute(Node &node) ;

        void WriteNodeType(NodeType nodeType) ;
        void WriteNodeAddr(Node *nodePoint) ;
        void WriteLocation(const char *filename, size_t leftLine, size_t leftCol, size_t rightLine, size_t rightCol) ;

        void WriteMajorName(const char *major_name) ;
        void WriteString(const char *str) ;
    };

    class DumpAST : public Visitor, private DumpASTWritter {
    public:
        explicit DumpAST(std::ostream &OS) ;

    public:
        void Visit(Node &                node) override;
        void Visit(TranslateUnit &       node) override;
        void Visit(SourceFile &          node) override;
        void Visit(ProgramSetFile &      node) override;
        void Visit(GlobalVariableFile &  node) override;
        void Visit(DataStructureFile &   node) override;
        void Visit(APIDeclareFile &      node) override;
        void Visit(MacroDeclareFile &    node) override;
        void Visit(IdentDef &            node) override;
        void Visit(Decl &                node) override;
        void Visit(TagDecl &             node) override;
        void Visit(TypeDecl &            node) override;
        void Visit(VariTypeDecl &        node) override;
        void Visit(StructureDecl &       node) override;
        void Visit(BuiltinType &         node) override;
        void Visit(ArrayType &           node) override;
        void Visit(ReferenceType &       node) override;
        void Visit(MacroDecl &           node) override;
        void Visit(BaseVariDecl &        node) override;
        void Visit(VariableDecl &        node) override;
        void Visit(GlobalVariableDecl &  node) override;
        void Visit(LocalVariableDecl &   node) override;
        void Visit(ParameterDecl &       node) override;
        void Visit(MemberVariableDecl &  node) override;
        void Visit(FileVariableDecl &    node) override;
        void Visit(FunctorDecl &         node) override;
        void Visit(FunctionDecl &        node) override;
        void Visit(ProgSetDecl &         node) override;
        void Visit(APICommandDecl &      node) override;
        void Visit(Statement &           node) override;
        void Visit(IfStmt &              node) override;
        void Visit(StatementBlock &      node) override;
        void Visit(LoopStatement &       node) override;
        void Visit(WhileStmt &           node) override;
        void Visit(RangeForStmt &        node) override;
        void Visit(ForStmt &             node) override;
        void Visit(DoWhileStmt &         node) override;
        void Visit(AssignStmt &          node) override;
        void Visit(ControlStmt &         node) override;
        void Visit(LoopControlStmt &     node) override;
        void Visit(ContinueStmt &        node) override;
        void Visit(BreakStmt &           node) override;
        void Visit(ReturnStmt &          node) override;
        void Visit(ExitStmt &            node) override;
        void Visit(Expression &          node) override;
        void Visit(NameComponent &       node) override;
        void Visit(IdentRefer &          node) override;
        void Visit(ArrayIndex &          node) override;
        void Visit(FunctionCall &        node) override;
        void Visit(UnaryExpression &     node) override;
        void Visit(BinaryExpression &    node) override;
        void Visit(OperatedExpression &  node) override;
        void Visit(TypeConvert &         node) override;
        void Visit(Value &               node) override;
        void Visit(ValueOfDataSet &      node) override;
        void Visit(ValueOfDatetime &     node) override;
        void Visit(FuncAddrExpression &  node) override;
        void Visit(ValueOfBool &         node) override;
        void Visit(ValueOfDecimal &      node) override;
        void Visit(ValueOfString &       node) override;
    };
}

#endif //REXLANG_DUMPAST_H
