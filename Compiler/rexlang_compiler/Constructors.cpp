//
// Created by rex on 2020/7/28.
//

#include "NodeDecl.h"
#include "rtti.h"

namespace rexlang {

    /******************************************************************
     * Node
     ******************************************************************/

    Node::Node() {}

    /******************************************************************
     * TranslateUnit
     ******************************************************************/

    TranslateUnit::TranslateUnit() {
    }

    /******************************************************************
     * TagDecl
     ******************************************************************/

    TagDecl::TagDecl(IdentDef *name)
        : name_(name) {
        setChild(name_);
        name->setDecl(this);
    }

    /******************************************************************
     * BaseVariDecl
     ******************************************************************/

    BaseVariDecl::BaseVariDecl(VariTypeDecl *type, IdentDef *name)
        : TagDecl(name), type_(type) {
        setChild(type_);
    }

    /******************************************************************
     * ParameterDecl
     ******************************************************************/

    ParameterDecl::ParameterDecl(VariTypeDecl *type, IdentDef *name, bool isVari)
        : BaseVariDecl(type, name) {
        if (isVari)
            markAsVariParam();
    }

    /******************************************************************
     * ReferenceType
     ******************************************************************/

    ReferenceType::ReferenceType(TypeDecl *pointeeType)
            : VariTypeDecl(CreateNode<IdentDef>(pointeeType->getAstContext(), pointeeType->getNameRef().str() + "$ref"))
            , pointee_type_(pointeeType) {
    }

    /******************************************************************
     * IdentDef
     ******************************************************************/

    IdentDef::IdentDef(const char *           id)  : id_(StringPool::Create(id)) {}
    IdentDef::IdentDef(const std::string &    id)  : id_(StringPool::Create(id))  {}
    IdentDef::IdentDef(const StringRef &      id)  : id_(id)  {}
    IdentDef::IdentDef(const TString &        id)  : id_(id.string_)  {}

    IdentDef::IdentDef(const IdentDef &       other) = default ;

    /******************************************************************
     * VariableDecl
     ******************************************************************/

    VariableDecl::VariableDecl(VariTypeDecl *type, IdentDef *name) : BaseVariDecl(type, name) {}

    GlobalVariableDecl::GlobalVariableDecl(VariTypeDecl *type, IdentDef *name) : VariableDecl(type, name) {}
    MemberVariableDecl::MemberVariableDecl(VariTypeDecl *type, IdentDef *name) : VariableDecl(type, name) {}
    FileVariableDecl  ::FileVariableDecl  (VariTypeDecl *type, IdentDef *name) : VariableDecl(type, name) {}
    LocalVariableDecl ::LocalVariableDecl (VariTypeDecl *type, IdentDef *name) : VariableDecl(type, name) {}

    /******************************************************************
     * TypeDecl
     ******************************************************************/

    TypeDecl::TypeDecl(IdentDef *name) : TagDecl(name) {}

    /******************************************************************
     * BuiltinType
     ******************************************************************/

    BuiltinType::BuiltinType(IdentDef *typeName, EnumOfBuiltinType typeEnum)
            : VariTypeDecl(typeName) {
        (void) typeEnum;
    }

    /******************************************************************
     * VariTypeDecl
     ******************************************************************/

    VariTypeDecl::VariTypeDecl(IdentDef *name) : TypeDecl(name) {}

    /******************************************************************
     * StructureDecl
     ******************************************************************/

    StructureDecl::StructureDecl(IdentDef *name) : VariTypeDecl(name) {}

    /******************************************************************
     * ArrayType
     ******************************************************************/

    ArrayType::ArrayType(TypeDecl *baseType, const std::vector<size_t> &dimensions)
            : VariTypeDecl(CreateNode<IdentDef>(baseType->getAstContext(), baseType->getNameRef().str() + "$array")),
              base_type_(baseType), dimensions_(dimensions) {
    }

    /******************************************************************
     * FunctorDecl
     ******************************************************************/

    FunctorDecl::FunctorDecl(VariTypeDecl *retType, IdentDef *name, const std::vector<ParameterDecl *> &parameters)
            : TypeDecl(name), return_type_(retType), parameters_(parameters) {
    }

    /******************************************************************
     * FunctionDecl
     ******************************************************************/

    FunctionDecl::FunctionDecl(VariTypeDecl *retType, IdentDef *name, const std::vector<ParameterDecl *> &parameters)
            : FunctorDecl(retType, name, parameters) {
    }

    /******************************************************************
     * APICommandDecl
     ******************************************************************/

    APICommandDecl::APICommandDecl(
            VariTypeDecl *                          retType,
            IdentDef *                              name,
            const std::vector<ParameterDecl *> &    parameters,
            LibraryType                             libraryType,
            const TString &                         libraryName,
            IdentDef *                              apiName
            )
            : FunctorDecl   (retType, name, parameters)
            , library_file_ (libraryName)
            , library_type_ (libraryType)
            , api_name_     (apiName)
            {
        apiName->setDecl(this);
    }

    /******************************************************************
     * ProgSetDecl
     ******************************************************************/

    ProgSetDecl::ProgSetDecl(IdentDef *name) : TagDecl(name) {}

    /******************************************************************
     * AssignStmt
     ******************************************************************/

    AssignStmt::AssignStmt(NameComponent *lhs, Expression *rhs) {
        setLHS(lhs);
        setRHS(rhs);
        // TODO: Must add assignable check.
    }

    /******************************************************************
     * AssignStmt
     ******************************************************************/

    ReturnStmt::ReturnStmt(Expression *returnValue) {
        setReturnValue(returnValue);
    }

    /******************************************************************
     * IfStmt
     ******************************************************************/

    IfStmt::IfStmt(const std::vector<BranchTy> &branches, Statement *defaultBranchBody) {
        for (const BranchTy &branch : branches) {
            appendBranch(branch.first, branch.second);
        }
        setDefault(defaultBranchBody);
    }

    /******************************************************************
     * LoopStatement
     ******************************************************************/

    LoopStatement::LoopStatement(Statement *loopBody) {
        setLoopBody(loopBody);
    }

    WhileStmt::WhileStmt(Expression *condition, Statement *loopBody) : LoopStatement(loopBody) {
        setLoopCondition(condition);
    }

    RangeForStmt::RangeForStmt(Expression *rangeSize, NameComponent *loopVari, Statement *loopBody)
        : LoopStatement(loopBody) {
        setRangeSize(rangeSize);
        setLoopVariable(loopVari);
    }

    ForStmt::ForStmt(Expression *startValue, Expression *stopValue, Expression *stepValue, NameComponent *loopVari, Statement *loopBody)
        : LoopStatement(loopBody) {
        setStartValue(startValue);
        setStopValue (stopValue) ;
        setStepValue (stepValue) ;
        setLoopVari  (loopVari)  ;
    }

    DoWhileStmt::DoWhileStmt(Expression *condition, Statement *loopBody)
        : LoopStatement(loopBody) {
        setCondition(condition);
    }

    /******************************************************************
     * StatementBlock
     ******************************************************************/

    StatementBlock::StatementBlock(const std::vector<Statement *> &statement_list) {
        for (Statement *statement : statement_list) {
            appendStatement(statement);
        }
    }

    /******************************************************************
     * IdentRefer
     ******************************************************************/

    IdentRefer::IdentRefer(IdentDef *referenceTo, NameComponent * prefix) {
        reference_ = referenceTo;
        if ((prefix_ = prefix))
            setChild(prefix_);
    }

    /******************************************************************
     * ArrayIndex
     ******************************************************************/

    ArrayIndex::ArrayIndex(NameComponent *baseComponent, Expression *indexExpression) {
        setBaseComponent(baseComponent);
        setIndexExpr(indexExpression);
    }

    /******************************************************************
     * FunctionCall
     ******************************************************************/

    FunctionCall::FunctionCall(IdentRefer *name, FunctorDecl *callee, const std::vector<Expression *> &arguments) {
        setName(name);
        setArguments(arguments);
        if (matchFunctor(callee)) {
            assert(callee == name->def()->getParent());
        } else {
            assert(false);
        }
    }

    /******************************************************************
     * TypeConvert
     ******************************************************************/

    TypeConvert::TypeConvert(TypeDecl *targetType, Expression *fromExpression) {
        setTargetType(targetType);
        setFromExpression(fromExpression);
        isTypeConvertValid();
    }

    /******************************************************************
     * OperatedExpression
     ******************************************************************/

    OperatedExpression::OperatedExpression(const OperatorType &opt) {
        setOperator(opt);
    }

    /******************************************************************
     * UnaryExpression
     ******************************************************************/

    UnaryExpression::UnaryExpression(const OperatorType &opt, Expression *operand) : OperatedExpression(opt) {
        setOperand(operand);
        assert(isUnaryOperateValid());
    }

    /******************************************************************
     * BinaryExpression
     ******************************************************************/

    BinaryExpression::BinaryExpression(const OperatorType &opt, Expression *lhs, Expression *rhs)
        : OperatedExpression(opt) {
        setLHS(lhs);
        setRHS(rhs);
        assert(isBinaryOperateValid());
    }

    /******************************************************************
     * FuncAddrExpression
     ******************************************************************/

    FuncAddrExpression::FuncAddrExpression(FunctorDecl *callee) {
        callee_ = callee;
    }

    /******************************************************************
     * ValueOfDataSet
     ******************************************************************/

    ValueOfDataSet::ValueOfDataSet(const std::vector<Expression *> &dataSet) {
        for (Expression *data : dataSet) {
            appendElement(data);
        }
    }

    /******************************************************************
     * ValueOfDatetime
     ******************************************************************/

    ValueOfDatetime::ValueOfDatetime(time_t time) {
        setTime(time);
    }

    /******************************************************************
     * ValueOfBool
     ******************************************************************/

    ValueOfBool::ValueOfBool(bool boolValue) {
        setBool(boolValue);
    }

    /******************************************************************
     * ValueOfDecimal
     ******************************************************************/

    ValueOfDecimal::ValueOfDecimal(int   value) {
        setIntValue(value);
    }

    ValueOfDecimal::ValueOfDecimal(float value) {
        setFloatValue(value);
    }

    /******************************************************************
     * ValueOfString
     ******************************************************************/

    ValueOfString::ValueOfString(const TString &literal) {
        setStringLiteral(literal);
    }

}
