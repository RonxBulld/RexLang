//
// Created by rex on 2020/11/3.
//

#include <cstring>
#include "DumpAST.h"
#include "../rtti.h"

namespace rexlang {

    /*===-------------------------------------===*
     * 实现Node::Dump
     */

    void Node::Dump(std::ostream &OS) {
        DumpAST dump_ast(OS);
        Visit(dump_ast);
    }

    /*===-------------------------------------===*
     * DumpASTWritter的事件方法
     */

    DumpASTWritter::DumpASTWritter(std::ostream &OS) : OS_(OS) {
    }

    void DumpASTWritter::NodeEnter(Node &node) {
        if (latest_node_ != &node) {
            // 进入了一个新节点，一般情况下是子节点

            WriteNodeType(node.getNodeType());
            WriteNodeAddr(&node);
            WriteLocation(node.getFileName(), node.getLeftLine(), node.getLeftColumn(), node.getRightLine(), node.getRightColumn());

            latest_node_ = &node;
        }
    }

    void DumpASTWritter::NodeExit(Node &node) {
    }

    void DumpASTWritter::PrevAttribute(Node &node) {
    }

    void DumpASTWritter::PostAttribute(Node &node) {
    }

    /*===-------------------------------------===*
     * DumpASTWritter的输出方法
     */

    void DumpASTWritter::WriteNodeType(NodeType nodeType) {
        OS_ << rtti::name(nodeType) << " ";
    }

    void DumpASTWritter::WriteNodeAddr(Node *nodePoint) {
        OS_ << (void*) nodePoint << " ";
    }

    void DumpASTWritter::WriteLocation(const char *filename, size_t leftLine, size_t leftCol, size_t rightLine, size_t rightCol) {
        OS_ << "<";
        if (filename && std::strncmp(filename, latest_filename_.c_str(), latest_filename_.size()) != 0) {
            latest_filename_ = std::string(filename);
            OS_ << filename << ":";
        }
        OS_ << leftLine << ":" << leftCol;
        OS_ << "-";
        OS_ << rightLine << ":" << rightCol;
        OS_ << ">";
        OS_ << " ";
    }

    void DumpASTWritter::WriteMajorName(const char *major_name) {
        OS_ << major_name << " ";
    }

    void DumpASTWritter::WriteString(const char *str) {
        if (str) {
            OS_ << "\"" << str << "\"";
        } else {
            OS_ << "<NULL-STR>";
        }
        OS_ << " ";
    }

    /*===-------------------------------------===*
     * 实现DumpAST构造
     */

    DumpAST::DumpAST(std::ostream &OS) : DumpASTWritter(OS) {
    }

    DumpAST::~DumpAST() = default ;

    /*===-------------------------------------===*
     * 实现DumpAST各节点内容输出
     */

#define PREV_ACTION()   do { \
                            NodeEnter(node); \
                            PrevAttribute(node); \
                        } while(0)
#define POST_ACTION()   do { \
                            PostAttribute(node); \
                            Visitor::Visit(node); /* 访问子节点 */ \
                            NodeExit(node); \
                        } while(0)

    void DumpAST::Visit(Node &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(TranslateUnit &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(SourceFile &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ProgramSetFile &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(GlobalVariableFile &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(DataStructureFile &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(APIDeclareFile &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(MacroDeclareFile &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(IdentDef &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(Decl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(TagDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(TypeDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(VariTypeDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(StructureDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(BuiltinType &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ArrayType &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ReferenceType &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(MacroDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(BaseVariDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(VariableDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(GlobalVariableDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(LocalVariableDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ParameterDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(MemberVariableDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(FileVariableDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(FunctorDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(FunctionDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ProgSetDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(APICommandDecl &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(Statement &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(IfStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(StatementBlock &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(LoopStatement &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(WhileStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(RangeForStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ForStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(DoWhileStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(AssignStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ControlStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(LoopControlStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ContinueStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(BreakStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ReturnStmt &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(Expression &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(NameComponent &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(IdentRefer &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ArrayIndex &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(FunctionCall &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(UnaryExpression &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(BinaryExpression &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(OperatedExpression &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(TypeConvert &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(Value &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ValueOfDataSet &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ValueOfDatetime &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(FuncAddrExpression &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ValueOfBool &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ValueOfDecimal &node) {
        PREV_ACTION();

        POST_ACTION();
    }

    void DumpAST::Visit(ValueOfString &node) {
        PREV_ACTION();

        POST_ACTION();
    }

}
