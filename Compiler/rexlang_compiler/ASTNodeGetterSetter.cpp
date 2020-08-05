//
// 本文件用于实现：
// 1、将节点加入到另一个节点作为子级节点的例程
// 2、将属性加入到节点并进行解析的例程
// 3、获取属性的例程
// * 注意检查同域冲突
// Created by rex on 2020/7/18.
//

#include "NodeDecl.h"
#include "utilities/Str2Attr.h"

namespace rexlang {

    /***************************************************
     * Node
     ***************************************************/

    void Node::setParent(Node *parent) { parent_node_ = parent; }
    void Node::setChild (Node *child)  { child->parent_node_ = this; }

    TranslateUnit * Node::getTranslateUnit() const { return ast_context_->getTranslateUnit(); }
    ASTContext *    Node::getAstContext   () const { return ast_context_;  }
    Node *          Node::getNearstScope  () const { return parent_scope_; }
    Node *          Node::getParent       () const { assert(parent_node_); return parent_node_;  }

    void Node::setLocation(const char *filename, size_t leftLine, size_t leftColumn, size_t rightLine, size_t rightColumn) {
        location_start_ = this->ast_context_->createLocation(filename, leftLine,  leftColumn );
        location_end_   = this->ast_context_->createLocation(filename, rightLine, rightColumn);
    }

    const char * Node::getFileName   () const { return ast_context_->getFileFromLocate  (location_start_).c_str(); }
    size_t       Node::getLeftLine   () const { return ast_context_->getLineFromLocate  (location_start_); }
    size_t       Node::getLeftColumn () const { return ast_context_->getColumnFromLocate(location_start_); }
    size_t       Node::getRightLine  () const { return ast_context_->getLineFromLocate  (location_end_); }
    size_t       Node::getRightColumn() const { return ast_context_->getColumnFromLocate(location_end_); }

    /***************************************************
     * TranslateUnit
     ***************************************************/

    const std::set<TString> &TranslateUnit::getReferenceLibraries() const {
        return libraries_list_;
    }

    void TranslateUnit::appendSourceFile(rexlang::SourceFile *sourceFile) {
        sourceFile->registResourceTo(this);
        source_files_.emplace_back(sourceFile);
        setChild(sourceFile);
    }

    /***************************************************
     * ProgramSetFile
     ***************************************************/

    void ProgramSetFile::appendReferenceLibName(const TString &libraryName) {
        libraries_.push_back(libraryName);
        getAstContext()->addDependenceLibrary(libraryName.string_);
    }

    void ProgramSetFile::appendProgramSetDecl(ProgSetDecl *progSetDecl) {
        program_set_declares_ = progSetDecl;
        setChild(progSetDecl);
    }

    ProgSetDecl *                ProgramSetFile::getProgramSetDecl() const { return program_set_declares_; }
    const std::vector<TString> & ProgramSetFile::getRefLibs       () const { return libraries_; }

    /***************************************************
     * DataStructureFile
     ***************************************************/

    void DataStructureFile::appendStructureDecl(StructureDecl *structureDecl) {
        structure_decl_map_[structureDecl->getNameRef()] = structureDecl;
        setChild(structureDecl);
    }

    const DataStructureFile::StructDeclMapTy & DataStructureFile::getTypes() const { return structure_decl_map_; }

    /***************************************************
     * GlobalVariableFile
     ***************************************************/

    void GlobalVariableFile::appendGlobalVariableDecl(GlobalVariableDecl *globalVariableDecl) {
        global_variable_map_[globalVariableDecl->getNameRef()] = globalVariableDecl;
        setChild(globalVariableDecl);
    }

    const GlobalVariableFile::GlobalVariMapTy &GlobalVariableFile::getGlobalVariMap() const { return global_variable_map_; }

    /***************************************************
     * APIDeclareFile
     ***************************************************/

    void APIDeclareFile::appendAPIDeclare(APICommandDecl *apiCommandDecl) {
        api_declares_[apiCommandDecl->getNameRef()] = apiCommandDecl;
        setChild(apiCommandDecl);
    }

    const APIDeclareFile::DllDefMapTy & APIDeclareFile::getAPIDefMap () const { return api_declares_; }

    /***************************************************
     * ConstDeclareFile
     ***************************************************/

    void ConstDeclareFile::appendConstDeclare(ConstDecl *constDecl) {
        consts_declares_[constDecl->getNameRef()] = constDecl;
        setChild(constDecl);
    }

    const ConstDeclareFile::ConstDeclMapTy & ConstDeclareFile::getConstDeclMap () const { return consts_declares_; }

    /***************************************************
     * ConstDecl
     ***************************************************/

    ConstDecl::ConstDecl(IdentDef *name, Value *value) : TagDecl(name), const_value_(value) {}

    /***************************************************
     * Decl
     ***************************************************/

    void Decl::applyAttribute(const TString &attribute) {
        auto err_or_al = Str2Attr::name2AccessLevel(attribute.string_);
        if (err_or_al.NoError()) {
            setAccessLevel(err_or_al.Value());
        }
        else {
            assert(false);
        }
    }
    void Decl::applyAttributes(const std::vector<TString> &attributes) {
        for (const TString &attr : attributes) {
            applyAttribute(attr);
        }
    }

    void        Decl::setAccessLevel(AccessLevel accessLevel) { access_level_ = accessLevel; }
    AccessLevel Decl::getAccessLevel() const                  { return access_level_; }

    /***************************************************
     * TagDecl
     ***************************************************/

    IdentDef *      TagDecl::getName    () const    { return name_; }
    const char *    TagDecl::getNameStr () const    { return name_->name(); }

    void                TagDecl::setComment      (const TString &comment)   { comment_ = comment; }
    const TString &     TagDecl::getComment      () const                   { return comment_; }
    const char *        TagDecl::getCommentStr   () const                   { return comment_.string_.c_str(); }

    std::set<IdentRefer *> &TagDecl::getReferenceTable()    { return name_->getReferenceTable(); }

    int TagDecl::addReference     (IdentRefer *reference) { name_->addReference(reference);    return 0; }
    int TagDecl::removeReference  (IdentRefer *reference) { name_->removeReference(reference); return 0; }

    /***************************************************
     * BaseVariDecl
     ***************************************************/

    void BaseVariDecl::updateType(VariTypeDecl *type) {
        type_      = type;

        delete type_name_;
        type_name_ = nullptr;
    }

    IdentRefer *   BaseVariDecl::id  () const { return type_name_; }
    VariTypeDecl * BaseVariDecl::type() const { return type_; }

    /***************************************************
     * ParameterDecl
     ***************************************************/

    int ParameterDecl::getParamIndex() const {
        FunctorDecl *parent_func = getParent()->as<FunctorDecl>();
        if (parent_func) {
            int idx = parent_func->getIndexOf(this);
            if (idx >= 0) return idx;
            assert(false);
        } else {
            assert(parent_func);
        }
        return -1;
    }

    void ParameterDecl::applyAttribute(const TString &attribute) {
        if (Str2Attr::isNameOfReference(attribute.string_)) {
            updateType(ReferenceType::get(getType()));
        }
        else if (Str2Attr::isNameOfNullable(attribute.string_)) {
            is_nullable_  = true;
        }
        else if (Str2Attr::isNameOfArray(attribute.string_)) {
            if (IdentRefer *__id = id()) {
                updateType(ArrayDecl::get(__id, {}));
            }
            else if (VariTypeDecl *__type = type()) {
                updateType(ArrayDecl::get(__type, {}));
            }
        }
        else {
            Decl::applyAttribute(attribute);
        }
    }

    /***************************************************
     * VariableDecl
     ***************************************************/

    void VariableDecl::setDimensionsText(const TString &dimStr) {
        dimensions_decl_ = dimStr;
        if (!dimensions_decl_.string_.empty()) {
            auto err_or_dims = Str2Attr::str2Dimension(dimensions_decl_.string_);
            if (err_or_dims.HadError()) {
                assert(false);
                return;
            }
            is_array_ = true;
            dimensions_ = err_or_dims.Value();
        }
        else {
            is_array_ = false;
            dimensions_ = {};
        }
    }

    /***************************************************
     * GlobalVariableDecl
     ***************************************************/

    /***************************************************
     * MemberVariableDecl
     ***************************************************/

    void MemberVariableDecl::applyAttribute(const TString &attribute) {
        if (Str2Attr::isNameOfReference(attribute.string_)) { is_reference_ = true; }
        else { VariableDecl::applyAttribute(attribute); }
    }

    /***************************************************
     * LocalVariableDecl
     ***************************************************/

    void LocalVariableDecl::applyAttribute (const TString &attribute) {
        if (Str2Attr::isNameOfStatic(attribute.string_)) { is_static_ = true; }
        else { VariableDecl::applyAttribute(attribute); }
    }

    bool LocalVariableDecl::isStatic() const { return is_static_; }

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

    const std::vector<Statement *> &StatementBlock::getStatements() const {
        return statements_;
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
     * LoopControlStmt
     ***************************************************/

    void           LoopControlStmt::setControlledLoop(LoopStatement *loopStatement) { controlled_loop_ = loopStatement; }
    LoopStatement *LoopControlStmt::getControlledLoop() const                       { return controlled_loop_; }

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
        setChild(loop_body_);
    }

    Statement * LoopStatement::getLoopBody() const {
        return loop_body_;
    }

    /***************************************************
     * WhileStmt
     ***************************************************/

    void WhileStmt::setLoopCondition(Expression *condition) {
        condition_ = condition;
        setChild(condition);
    }

    Expression * WhileStmt::getLoopCondition() const {
        return condition_;
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

    Expression * ReturnStmt::getReturnValue() const { return return_value_; }

    /***************************************************
     * FunctionCall
     ***************************************************/

    void FunctionCall::setCallName    (NameComponent *funcName) { function_name_ = funcName; setChild(funcName); }

    void FunctionCall::appendArgument (Expression *argument) {
        arguments_.emplace_back(argument);
        setChild(argument);
    }

    /***************************************************
     * IdentRefer
     ***************************************************/

         IdentRefer::IdentRefer () = default;
         IdentRefer::IdentRefer (const TString &name)   { setName(name); }
    void IdentRefer::setName    (const TString &name)   { name_ = name; }

    /***************************************************
     * ArrayIndex
     ***************************************************/

    void ArrayIndex::setBaseComponent(NameComponent *baseComponent) { base_  = baseComponent; setChild(baseComponent); }
    void ArrayIndex::setIndexExpr    (Expression *indexExpr)        { index_ = indexExpr;     setChild(indexExpr); }

    /***************************************************
     * _OperatorExpression
     ***************************************************/

    void                 _OperatorExpression::setOperatorText(const TString & operatorText) { operator_      = operatorText; }
    void                 _OperatorExpression::setOperator    (const OperatorType &     opt) { operator_type_ = opt; }
    void                 _OperatorExpression::setOperator    (const OperatorType::Opt &opt) { operator_type_ = OperatorType(opt); }
    const OperatorType & _OperatorExpression::getOperator    () const                       { return operator_type_; }

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

    void FuncAddrExpression::setRefFuncName(IdentRefer *functionName) { function_name_ = functionName; }

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