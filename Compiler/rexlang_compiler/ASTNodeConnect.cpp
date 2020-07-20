//
// 本文件用于实现：
// 1、将节点加入到另一个节点作为子级节点的例程
// 2、将属性加入到节点并进行解析的例程
// 3、获取属性的例程
// * 注意检查同域冲突
// Created by rex on 2020/7/18.
//

#include "NodeDecl.h"

namespace rexlang {

    /***************************************************
     * ProgramSetFile
     ***************************************************/

    void ProgramSetFile::appendReferenceLibName(const TString &libraryName) {
        libraries_.push_back(libraryName);
        getAstContext()->AddDependenceLibrary(libraryName.string_);
    }

    void ProgramSetFile::appendProgramSetDecl(ProgSetDecl *progSetDecl) {
        program_set_declares_ = progSetDecl;
        setChild(progSetDecl);
    }

    /***************************************************
     * DataStructureFile
     ***************************************************/

    void DataStructureFile::appendStructureDecl(StructureDecl *structureDecl) {
        structure_decl_map_[structureDecl->getNameRef()] = structureDecl;
        setChild(structureDecl);
    }

    /***************************************************
     * GlobalVariableFile
     ***************************************************/

    void GlobalVariableFile::appendGlobalVariableDecl(GlobalVariableDecl *globalVariableDecl) {
        global_variable_map_[globalVariableDecl->getNameRef()] = globalVariableDecl;
        setChild(globalVariableDecl);
    }

    /***************************************************
     * DllDefineFile
     ***************************************************/

    void DllDefineFile::appendDllDefine(APICommandDecl *apiCommandDecl) {
        dll_declares_[apiCommandDecl->getNameRef()] = apiCommandDecl;
        setChild(apiCommandDecl);
    }

    /***************************************************
     * TagDecl
     ***************************************************/

    void                TagDecl::setName         (const TString &name)      { name_ = name; }
    const TString &     TagDecl::getName         () const                   { return name_; }
    const StringRef &   TagDecl::getNameRef      () const                   { return name_.string_; }

    void                TagDecl::setComment      (const TString &comment)   { comment_ = comment; }
    const TString &     TagDecl::getComment      () const                   { return comment_; }
    const StringRef &   TagDecl::getCommentRef   () const                   { return comment_.string_; }

    /***************************************************
     * BaseVariDecl
     ***************************************************/

    void BaseVariDecl::setTypeName(const TString &typeName) { type_name_ = typeName; }

    /***************************************************
     * FunctorDecl
     ***************************************************/

    void FunctorDecl::setReturnTypeName(const TString &typeName) { return_type_name_ = typeName; }

    void FunctorDecl::appendParameter(ParameterDecl *parameterDecl) {
        parameters_.push_back(parameterDecl);
        setChild(parameterDecl);
    }

    /***************************************************
     * APICommandDecl
     ***************************************************/

    APICommandDecl::APICommandDecl(const TString &library, LibraryType libraryType, const TString &name, const TString &apiName) {
        library_file_ = library;
        library_type_ = libraryType;
        setName(name);
    }

    void APICommandDecl::appendParameter(ParameterDecl *parameterDecl) {
        FunctorDecl::appendParameter(parameterDecl);
        mapping_names_.emplace_back(parameterDecl->getNameRef());
        setChild(parameterDecl);
    }

    /***************************************************
     * StructureDecl
     ***************************************************/

    void StructureDecl::appendElement(MemberVariableDecl *element) {
        members_[element->getNameRef()] = element;
        setChild(element);
    }

    /***************************************************
     * ProgSetDecl
     ***************************************************/

    void ProgSetDecl::appendFileStaticVari(FileVariableDecl *variable) {
        file_static_variables_[variable->getNameRef()] = variable;
        setChild(variable);
    }

    void ProgSetDecl::appendFunctionDecl  (FunctionDecl *functionDecl) {
        function_decls_[functionDecl->getNameRef()] = functionDecl;
        setChild(functionDecl);
    }

    /***************************************************
     * FunctionDecl
     ***************************************************/

    void FunctionDecl::appendLocalVariable(LocalVariableDecl *variableDecl) {
        local_vari_[variableDecl->getNameRef()] = variableDecl;
        setChild(variableDecl);
    }

    void FunctionDecl::setStatementBlock(StatementBlock *statementBlock) {
        statement_list_ = statementBlock;
        setChild(statementBlock);
    }

    /***************************************************
     * StatementBlock
     ***************************************************/

    void StatementBlock::appendStatement(Statement *statement) {
        statements_.push_back(statement);
        setChild(statement);
    }

    /***************************************************
     * AssignStmt
     ***************************************************/

    void AssignStmt::setLHS(HierarchyIdentifier *lhs) {
        lhs_ = lhs;
        setChild(lhs);
    }

    void AssignStmt::setRHS(Expression *rhs) {
        rhs_ = rhs;
        setChild(rhs);
    }

    /***************************************************
     * IfStmt
     ***************************************************/

    void IfStmt::appendBranch(Expression *condition, Statement *statement) {
        switches_.push_back(std::pair(condition, statement));
        setChild(condition);
        setChild(statement);
    }

    void IfStmt::setDefault(Statement *statement) {
        default_statement_ = statement;
        setChild(statement);
    }

    /***************************************************
     * LoopStatement
     ***************************************************/

    void LoopStatement::setLoopBody(Statement *loopBody) {
        loop_body_ = loopBody;
        setChild(loopBody);
    }

    /***************************************************
     * WhileStmt
     ***************************************************/

    void WhileStmt::setLoopCondition(Expression *condition) {
        condition_ = condition;
        setChild(condition);
    }

    /***************************************************
     * RangeForStmt
     ***************************************************/

    void RangeForStmt::setRangeSize   (Expression *rangeSize)         { range_size_ = rangeSize; setChild(rangeSize); }
    void RangeForStmt::setLoopVariable(HierarchyIdentifier *loopVari) { loop_vari_ = loopVari; setChild(loopVari); }

    /***************************************************
     * ForStmt
     ***************************************************/

    void ForStmt::setStartValue(Expression *startValue)        { start_value_ = startValue; setChild(startValue); }
    void ForStmt::setStopValue (Expression *stopValue)         { stop_value_  = stopValue;  setChild(stopValue); }
    void ForStmt::setStepValue (Expression *stepValue)         { step_value_  = stepValue;  setChild(stepValue); }
    void ForStmt::setLoopVari  (HierarchyIdentifier *loopVari) { loop_vari_   = loopVari;   setChild(loopVari); }

    /***************************************************
     * DoWhileStmt
     ***************************************************/

    void DoWhileStmt::setCondition(Expression *condition) { condition_ = condition; setChild(condition); }

    /***************************************************
     * ReturnStmt
     ***************************************************/

    void ReturnStmt::setReturnValue(Expression *returnValue) { return_value_ = returnValue; setChild(returnValue); }

    /***************************************************
     * FunctionCall
     ***************************************************/

    void FunctionCall::setCallName    (NameComponent *funcName) { function_name_ = funcName; setChild(funcName); }

    void FunctionCall::appendArgument (Expression *argument) {
        arguments_.emplace_back(argument);
        setChild(argument);
    }

    /***************************************************
     * Identifier
     ***************************************************/

         Identifier::Identifier () = default;
         Identifier::Identifier (const TString &name)   { setName(name); }
    void Identifier::setName    (const TString &name)   { name_ = name; }

    /***************************************************
     * ArrayIndex
     ***************************************************/

    void ArrayIndex::setBaseComponent(NameComponent *baseComponent) { base_  = baseComponent; setChild(baseComponent); }
    void ArrayIndex::setIndexExpr    (Expression *indexExpr)        { index_ = indexExpr;     setChild(indexExpr); }

    /***************************************************
     * _OperatorExpression
     ***************************************************/

    void                 _OperatorExpression::setOperatorText(const TString &operatorText) { operator_      = operatorText; }
    void                 _OperatorExpression::setOperator    (const OperatorType &opt)     { operator_type_ = opt; }
    const OperatorType & _OperatorExpression::getOperator    () const                      { return operator_type_; }

    /***************************************************
     * BinaryExpression
     ***************************************************/

    void BinaryExpression::setLHS(Expression *lhsExpr) { lhs_ = lhsExpr; setChild(lhsExpr); }
    void BinaryExpression::setRHS(Expression *rhsExpr) { rhs_ = rhsExpr; setChild(rhsExpr); }

    /***************************************************
     * UnaryExpression
     ***************************************************/

    void UnaryExpression::setOperand(Expression *operand) { operand_value_ = operand; setChild(operand); }

    /***************************************************
     * ValueOfDataSet
     ***************************************************/

    void ValueOfDataSet::appendElement(Expression *element) { elements_.push_back(element); setChild(element); }

    /***************************************************
     * ValueOfDatetime
     ***************************************************/

    void ValueOfDatetime::setTime(time_t time) { time_ = time; }

    /***************************************************
     * ResourceRefExpression
     ***************************************************/

    void ResourceRefExpression::setResourceName(const TString &resourceName) { resource_name_ = resourceName; }

    /***************************************************
     * FuncAddrExpression
     ***************************************************/

    void FuncAddrExpression::setRefFuncName(Identifier *functionName) { function_name_ = functionName; }

    /***************************************************
     * ValueOfBool
     ***************************************************/

    void ValueOfBool::setBool(bool boolValue) { value_ = boolValue; }

    /***************************************************
     * ValueOfDecimal
     ***************************************************/

    void ValueOfDecimal::setIntValue  (int value)   { type_ = type::kInt;   int_val_   = value; }
    void ValueOfDecimal::setFloatValue(float value) { type_ = type::kFloat; float_val_ = value; }

    /***************************************************
     * ValueOfString
     ***************************************************/

    void ValueOfString::setStringLiteral(const TString &literal) { string_literal_ = literal; }

}