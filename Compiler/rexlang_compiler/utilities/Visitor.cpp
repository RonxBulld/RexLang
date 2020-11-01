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
        if (node) node->Accept(*this);
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

        TraverseNamedMap(node.getGlobalVariMap());

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

    void Visitor::Visit(ArrayDecl &node) {
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

        TraverseNamedMap(node.getLocalVariables());
        TraverseNode(node.getFunctionBody());

        PostAction(node);
    }

    void Visitor::Visit(ProgSetDecl &node) {
        HeadAction(node);
        VISIT_BASE(TagDecl, node);
        PrevAction(node);

        TraverseNamedMap(node.fileVariables());
        TraverseNamedMap(node.functions());

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

}