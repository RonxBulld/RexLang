//
// Created by rex on 2020/11/3.
//

#include "DumpAST.h"

namespace rexlang {

    /*===-------------------------------------===*
     * 实现Node::Dump
     */

    void Node::Dump(std::ostream &OS) {
        DumpASTWritter writter(OS);
        DumpAST dump_ast(writter);
        Visit(dump_ast);
    }

    /*===-------------------------------------===*
     * 实现DumpASTWritter
     */

    DumpASTWritter::DumpASTWritter(std::ostream &OS) : OS_(OS) {
    }

    /*===-------------------------------------===*
     * 实现DumpAST构造
     */

    DumpAST::DumpAST(DumpASTWritter &writter) : writter_(writter) {
    }

    /*===-------------------------------------===*
     * 实现DumpAST各节点内容输出
     */

    void DumpAST::Visit(Node &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(TranslateUnit &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(SourceFile &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ProgramSetFile &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(GlobalVariableFile &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(DataStructureFile &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(APIDeclareFile &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(MacroDeclareFile &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(IdentDef &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(Decl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(TagDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(TypeDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(VariTypeDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(StructureDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(BuiltinTypeDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ArrayDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ReferenceType &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(MacroDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(BaseVariDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(VariableDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(GlobalVariableDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(LocalVariableDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ParameterDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(MemberVariableDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(FileVariableDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(FunctorDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(FunctionDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ProgSetDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(APICommandDecl &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(Statement &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(IfStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(StatementBlock &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(LoopStatement &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(WhileStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(RangeForStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ForStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(DoWhileStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(AssignStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ControlStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(LoopControlStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ContinueStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(BreakStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ReturnStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ExitStmt &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(Expression &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(HierarchyIdentifier &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(NameComponent &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(IdentRefer &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ArrayIndex &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(FunctionCall &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(UnaryExpression &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(BinaryExpression &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(OperatedExpression &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(TypeConvert &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(Value &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ValueOfDataSet &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ValueOfDatetime &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(FuncAddrExpression &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ValueOfBool &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ValueOfDecimal &node) {
        Visitor::Visit(node);
    }

    void DumpAST::Visit(ValueOfString &node) {
        Visitor::Visit(node);
    }

}
