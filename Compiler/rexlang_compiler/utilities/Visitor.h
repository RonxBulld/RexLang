//
// Created by rex on 2020/10/31.
//

#ifndef REXLANG_VISITOR_H
#define REXLANG_VISITOR_H

#include "../NodeDecl.h"

namespace rexlang {

    class Visitor {
    public:
        virtual ~Visitor() = default ;

    public:     // 基础例程

        virtual void HeadAction(Node &node) ;   // 访问基类之前调用
        virtual void PrevAction(Node &node) ;   // 访问子节点之前调用
        virtual void PostAction(Node &node) ;   // 访问子节点之后调用

        virtual void TraverseNode(Node *node) ; // 访问节点

        template <typename ArrayLikeTy>
        void TraverseArray(const ArrayLikeTy &arrayLike) ;   // 访问数组

        template <typename NamedMapLikeTy>
        void TraverseNamedMap(const NamedMapLikeTy &namedMapLikeTy) ;   // 访问命名字典

    public:     // 节点类型特定例程

        virtual void Visit(Node                &node) ;

        virtual void Visit(TranslateUnit       &node) ;

        virtual void Visit(SourceFile          &node) ;
        virtual void Visit(ProgramSetFile      &node) ;
        virtual void Visit(GlobalVariableFile  &node) ;
        virtual void Visit(DataStructureFile   &node) ;
        virtual void Visit(APIDeclareFile      &node) ;
        virtual void Visit(MacroDeclareFile    &node) ;

        virtual void Visit(IdentDef            &node) ;

        virtual void Visit(Decl                &node) ;
        virtual void Visit(TagDecl             &node) ;
        virtual void Visit(TypeDecl            &node) ;
        virtual void Visit(VariTypeDecl        &node) ;
        virtual void Visit(StructureDecl       &node) ;
        virtual void Visit(BuiltinType         &node) ;
        virtual void Visit(ArrayType           &node) ;
        virtual void Visit(ReferenceType       &node) ;
        virtual void Visit(MacroDecl           &node) ;

        virtual void Visit(BaseVariDecl        &node) ;
        virtual void Visit(VariableDecl        &node) ;
        virtual void Visit(GlobalVariableDecl  &node) ;
        virtual void Visit(LocalVariableDecl   &node) ;
        virtual void Visit(ParameterDecl       &node) ;
        virtual void Visit(MemberVariableDecl  &node) ;
        virtual void Visit(FileVariableDecl    &node) ;
        virtual void Visit(FunctorDecl         &node) ;
        virtual void Visit(FunctionDecl        &node) ;
        virtual void Visit(ProgSetDecl         &node) ;
        virtual void Visit(APICommandDecl      &node) ;

        virtual void Visit(Statement           &node) ;
        virtual void Visit(IfStmt              &node) ;
        virtual void Visit(StatementBlock      &node) ;
        virtual void Visit(LoopStatement       &node) ;
        virtual void Visit(WhileStmt           &node) ;
        virtual void Visit(RangeForStmt        &node) ;
        virtual void Visit(ForStmt             &node) ;
        virtual void Visit(DoWhileStmt         &node) ;
        virtual void Visit(AssignStmt          &node) ;
        virtual void Visit(ControlStmt         &node) ;
        virtual void Visit(LoopControlStmt     &node) ;
        virtual void Visit(ContinueStmt        &node) ;
        virtual void Visit(BreakStmt           &node) ;
        virtual void Visit(ReturnStmt          &node) ;

        virtual void Visit(Expression          &node) ;
        virtual void Visit(NameComponent       &node) ;
        virtual void Visit(IdentRefer          &node) ;
        virtual void Visit(ArrayIndex          &node) ;
        virtual void Visit(FunctionCall        &node) ;
        virtual void Visit(UnaryExpression     &node) ;
        virtual void Visit(BinaryExpression    &node) ;
        virtual void Visit(OperatedExpression  &node) ;
        virtual void Visit(TypeConvert         &node) ;

        virtual void Visit(Value               &node) ;
        virtual void Visit(ValueOfDataSet      &node) ;
        virtual void Visit(ValueOfDatetime     &node) ;
        virtual void Visit(FuncAddrExpression  &node) ;
        virtual void Visit(ValueOfBool         &node) ;
        virtual void Visit(ValueOfDecimal      &node) ;
        virtual void Visit(ValueOfString       &node) ;

    };

}

#endif //REXLANG_VISITOR_H
