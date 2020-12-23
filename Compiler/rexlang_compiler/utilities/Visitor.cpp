//
// Created by rex on 2020/10/31.
//

#include "Visitor.h"

namespace rexlang {

    /*===---------------------------------------===*
     * 基础例程
     */

    void Visitor::HeadAction(Node &node) {}

    void Visitor::PrevAction(Node &node) {}

    void Visitor::PostAction(Node &node) {}

    void Visitor::TraverseNode(Node *node) {
        if (node) node->Visit(*this);       // 调用节点重写的特定Visit函数实现从叶子类到根基类的访问
    }

    template <typename ArrayLikeTy>
    void Visitor::TraverseArray(const ArrayLikeTy &arrayLike) {
        for (auto *element : arrayLike) {
            TraverseNode(element);
        }
    }
    template <typename NamedMapLikeTy>
    void Visitor::TraverseNamedMap(const NamedMapLikeTy &namedMapLikeTy) {
        for (auto &item : namedMapLikeTy) {
            TraverseNode(item.second);
        }
    }

    /*===---------------------------------------===*
     * 节点类型特定例程
     */

#define VISIT_BASE(BASE_TYPE, VARI) Visit((BASE_TYPE &) VARI)

    void Visitor::Visit(Node &node) {
        HeadAction(node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(TranslateUnit &node) {
        HeadAction(node);
        VISIT_BASE(Node, node);
        PrevAction(node);

        TraverseArray(node.getSourceFiles());

        PostAction(node);
    }

    void Visitor::Visit(SourceFile &node) {
        HeadAction(node);
        VISIT_BASE(Node, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(ProgramSetFile &node) {
        HeadAction(node);
        VISIT_BASE(SourceFile, node);
        PrevAction(node);

        TraverseNode(node.getProgSet());

        PostAction(node);
    }

    void Visitor::Visit(GlobalVariableFile &node) {
        HeadAction(node);
        VISIT_BASE(SourceFile, node);
        PrevAction(node);

        TraverseArray(node.getGlobalVariMap());

        PostAction(node);
    }

    void Visitor::Visit(DataStructureFile &node) {
        HeadAction(node);
        VISIT_BASE(SourceFile, node);
        PrevAction(node);

        TraverseNamedMap(node.getTypes());

        PostAction(node);
    }

    void Visitor::Visit(APIDeclareFile &node) {
        HeadAction(node);
        VISIT_BASE(SourceFile, node);
        PrevAction(node);

        TraverseNamedMap(node.getAPIDefMap());

        PostAction(node);
    }

    void Visitor::Visit(MacroDeclareFile &node) {
        HeadAction(node);
        VISIT_BASE(SourceFile, node);
        PrevAction(node);

        TraverseNamedMap(node.getMacroDeclMap());

        PostAction(node);
    }

    void Visitor::Visit(IdentDef &node) {
        HeadAction(node);
        VISIT_BASE(Node, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(Decl &node) {
        HeadAction(node);
        VISIT_BASE(Node, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(TagDecl &node) {
        HeadAction(node);
        VISIT_BASE(Decl, node);
        PrevAction(node);

        TraverseNode(node.getName());

        PostAction(node);
    }

    void Visitor::Visit(TypeDecl &node) {
        HeadAction(node);
        VISIT_BASE(TagDecl, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(VariTypeDecl &node) {
        HeadAction(node);
        VISIT_BASE(TypeDecl, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(StructureDecl &node) {
        HeadAction(node);
        VISIT_BASE(VariTypeDecl, node);
        PrevAction(node);

        TraverseNamedMap(node.elements());

        PostAction(node);
    }

    void Visitor::Visit(BuiltinTypeDecl &node) {
        HeadAction(node);
        VISIT_BASE(VariTypeDecl, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(ArrayType &node) {
        HeadAction(node);
        VISIT_BASE(VariTypeDecl, node);
        PrevAction(node);

        TraverseNode(node.getArrayBase());

        PostAction(node);
    }

    void Visitor::Visit(ReferenceType &node) {
        HeadAction(node);
        VISIT_BASE(VariTypeDecl, node);
        PrevAction(node);

        TraverseNode(node.getPointee());

        PostAction(node);
    }

    void Visitor::Visit(MacroDecl &node) {
        HeadAction(node);
        VISIT_BASE(TagDecl, node);
        PrevAction(node);

        TraverseNode(node.getValue());

        PostAction(node);
    }

    void Visitor::Visit(BaseVariDecl &node) {
        HeadAction(node);
        VISIT_BASE(TagDecl, node);
        PrevAction(node);

        TraverseNode(node.type());

        PostAction(node);
    }

    void Visitor::Visit(VariableDecl &node) {
        HeadAction(node);
        VISIT_BASE(BaseVariDecl, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(GlobalVariableDecl &node) {
        HeadAction(node);
        VISIT_BASE(VariableDecl, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(LocalVariableDecl &node) {
        HeadAction(node);
        VISIT_BASE(VariableDecl, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(ParameterDecl &node) {
        HeadAction(node);
        VISIT_BASE(BaseVariDecl, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(MemberVariableDecl &node) {
        HeadAction(node);
        VISIT_BASE(VariableDecl, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(FileVariableDecl &node) {
        HeadAction(node);
        VISIT_BASE(VariableDecl, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(FunctorDecl &node) {
        HeadAction(node);
        VISIT_BASE(TypeDecl, node);
        PrevAction(node);

        TraverseArray(node.getParameters());

        PostAction(node);
    }

    void Visitor::Visit(FunctionDecl &node) {
        HeadAction(node);
        VISIT_BASE(FunctorDecl, node);
        PrevAction(node);

        TraverseArray(node.getLocalVariables());
        TraverseNode(node.getFunctionBody());

        PostAction(node);
    }

    void Visitor::Visit(ProgSetDecl &node) {
        HeadAction(node);
        VISIT_BASE(TagDecl, node);
        PrevAction(node);

        TraverseArray(node.fileVariables());
        TraverseArray(node.functions());

        PostAction(node);
    }

    void Visitor::Visit(APICommandDecl &node) {
        HeadAction(node);
        VISIT_BASE(FunctorDecl, node);
        PrevAction(node);

        TraverseNode(node.getApiName());

        PostAction(node);
    }

    void Visitor::Visit(Statement &node) {
        HeadAction(node);
        VISIT_BASE(Node, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(IfStmt &node) {
        HeadAction(node);
        VISIT_BASE(Statement, node);
        PrevAction(node);

        for (auto &branch : node.expressionSwitches()) {
            TraverseNode(branch.first);
            TraverseNode(branch.second);
        }
        TraverseNode(node.defaultBody());

        PostAction(node);
    }

    void Visitor::Visit(StatementBlock &node) {
        HeadAction(node);
        VISIT_BASE(Statement, node);
        PrevAction(node);

        TraverseArray(node.getStatements());

        PostAction(node);
    }

    void Visitor::Visit(LoopStatement &node) {
        HeadAction(node);
        VISIT_BASE(Statement, node);
        PrevAction(node);

        TraverseNode(node.getLoopBody());

        PostAction(node);
    }

    void Visitor::Visit(WhileStmt &node) {
        HeadAction(node);
        VISIT_BASE(LoopStatement, node);
        PrevAction(node);

        TraverseNode(node.getLoopCondition());

        PostAction(node);
    }

    void Visitor::Visit(RangeForStmt &node) {
        HeadAction(node);
        VISIT_BASE(LoopStatement, node);
        PrevAction(node);

        TraverseNode(node.getRangeSize());
        TraverseNode(node.getLoopVari());

        PostAction(node);
    }

    void Visitor::Visit(ForStmt &node) {
        HeadAction(node);
        VISIT_BASE(LoopStatement, node);
        PrevAction(node);

        TraverseNode(node.getStartValue());
        TraverseNode(node.getStopValue());
        TraverseNode(node.getStepValue());
        TraverseNode(node.getLoopVari());

        PostAction(node);
    }

    void Visitor::Visit(DoWhileStmt &node) {
        HeadAction(node);
        VISIT_BASE(LoopStatement, node);
        PrevAction(node);

        TraverseNode(node.getCondition());

        PostAction(node);
    }

    void Visitor::Visit(AssignStmt &node) {
        HeadAction(node);
        VISIT_BASE(Statement, node);
        PrevAction(node);

        TraverseNode(node.getLHS());
        TraverseNode(node.getRHS());

        PostAction(node);
    }

    void Visitor::Visit(ControlStmt &node) {
        HeadAction(node);
        VISIT_BASE(Statement, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(LoopControlStmt &node) {
        HeadAction(node);
        VISIT_BASE(ControlStmt, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(ContinueStmt &node) {
        HeadAction(node);
        VISIT_BASE(LoopControlStmt, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(BreakStmt &node) {
        HeadAction(node);
        VISIT_BASE(LoopControlStmt, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(ReturnStmt &node) {
        HeadAction(node);
        VISIT_BASE(ControlStmt, node);
        PrevAction(node);

        TraverseNode(node.getReturnValue());

        PostAction(node);
    }

    void Visitor::Visit(ExitStmt &node) {
        HeadAction(node);
        VISIT_BASE(ControlStmt, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(Expression &node) {
        HeadAction(node);
        VISIT_BASE(Statement, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(HierarchyIdentifier &node) {
        HeadAction(node);
        VISIT_BASE(Expression, node);
        PrevAction(node);

        TraverseArray(node.getNameComponents());

        PostAction(node);
    }

    void Visitor::Visit(NameComponent &node) {
        HeadAction(node);
        VISIT_BASE(Expression, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(IdentRefer &node) {
        HeadAction(node);
        VISIT_BASE(NameComponent, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(ArrayIndex &node) {
        HeadAction(node);
        VISIT_BASE(NameComponent, node);
        PrevAction(node);

        TraverseNode(node.getIndexBase());
        TraverseNode(node.getIndex());

        PostAction(node);
    }

    void Visitor::Visit(FunctionCall &node) {
        HeadAction(node);
        VISIT_BASE(NameComponent, node);
        PrevAction(node);

        TraverseNode(node.getBaseId());
        TraverseArray(node.getArguments());

        PostAction(node);
    }

    void Visitor::Visit(UnaryExpression &node) {
        HeadAction(node);
        VISIT_BASE(OperatedExpression, node);
        PrevAction(node);

        TraverseNode(node.getOperand());

        PostAction(node);
    }

    void Visitor::Visit(BinaryExpression &node) {
        HeadAction(node);
        VISIT_BASE(OperatedExpression, node);
        PrevAction(node);

        TraverseNode(node.getLHS());
        TraverseNode(node.getRHS());

        PostAction(node);
    }

    void Visitor::Visit(OperatedExpression &node) {
        HeadAction(node);
        VISIT_BASE(Expression, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(TypeConvert &node) {
        HeadAction(node);
        VISIT_BASE(Expression, node);
        PrevAction(node);

        TraverseNode(node.getSourceExpr());

        PostAction(node);
    }

    void Visitor::Visit(Value &node) {
        HeadAction(node);
        VISIT_BASE(Expression, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(ValueOfDataSet &node) {
        HeadAction(node);
        VISIT_BASE(Value, node);
        PrevAction(node);

        TraverseArray(node.elements());

        PostAction(node);
    }

    void Visitor::Visit(ValueOfDatetime &node) {
        HeadAction(node);
        VISIT_BASE(Value, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(FuncAddrExpression &node) {
        HeadAction(node);
        VISIT_BASE(Expression, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(ValueOfBool &node) {
        HeadAction(node);
        VISIT_BASE(Value, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(ValueOfDecimal &node) {
        HeadAction(node);
        VISIT_BASE(Value, node);
        PrevAction(node);

        PostAction(node);
    }

    void Visitor::Visit(ValueOfString &node) {
        HeadAction(node);
        VISIT_BASE(Value, node);
        PrevAction(node);

        PostAction(node);
    }

    /*===---------------------------------------===*
     * 利用节点上的Visit多态性进行转发
     */

    int Node               ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int TranslateUnit      ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int SourceFile         ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ProgramSetFile     ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int GlobalVariableFile ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int DataStructureFile  ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int APIDeclareFile     ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int MacroDeclareFile   ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int IdentDef           ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int Decl               ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int TagDecl            ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int TypeDecl           ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int VariTypeDecl       ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int StructureDecl      ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int BuiltinTypeDecl    ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ArrayType          ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ReferenceType      ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int MacroDecl          ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int BaseVariDecl       ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int VariableDecl       ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int GlobalVariableDecl ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int LocalVariableDecl  ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ParameterDecl      ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int MemberVariableDecl ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int FileVariableDecl   ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int FunctorDecl        ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int FunctionDecl       ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ProgSetDecl        ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int APICommandDecl     ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int Statement          ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int IfStmt             ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int StatementBlock     ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int LoopStatement      ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int WhileStmt          ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int RangeForStmt       ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ForStmt            ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int DoWhileStmt        ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int AssignStmt         ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ControlStmt        ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int LoopControlStmt    ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ContinueStmt       ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int BreakStmt          ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ReturnStmt         ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ExitStmt           ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int Expression         ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int HierarchyIdentifier::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int NameComponent      ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int IdentRefer         ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ArrayIndex         ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int FunctionCall       ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int UnaryExpression    ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int BinaryExpression   ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int OperatedExpression ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int TypeConvert        ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int Value              ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ValueOfDataSet     ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ValueOfDatetime    ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int FuncAddrExpression ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ValueOfBool        ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ValueOfDecimal     ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }
    int ValueOfString      ::Visit(Visitor &visitor) { visitor.Visit(*this); return 0; }

}