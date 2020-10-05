//
// 本文件用于实现：
// 1、将节点加入到另一个节点作为子级节点的例程
// 2、将属性加入到节点并进行解析的例程
// 3、获取属性的例程
// * 注意检查同域冲突
// Created by rex on 2020/7/18.
//

#include <cstring>
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

    void TranslateUnit::appendSourceFile(rexlang::SourceFile *sourceFile) {
        sourceFile->registResourceTo(this);
        source_files_.emplace_back(sourceFile);
        setChild(sourceFile);
    }

    void     TranslateUnit::setSourceEdition(unsigned edition) { edition_ = edition; }
    unsigned TranslateUnit::getSourceEdition() const           { return edition_; }

    void         TranslateUnit::setMainEnrty(FunctorDecl *functorDecl) { main_entry_ = functorDecl; }
    FunctorDecl *TranslateUnit::getMainEntry() const                   { return main_entry_; }

    template <typename Ty>
    Ty *getAnyInSources(const StringRef &name, const std::vector<SourceFile *> &sourceFiles, Ty *(SourceFile::*fn)(const StringRef &) const) {
        for (SourceFile *source_file : sourceFiles) {
            if (source_file) {
                if (Ty *entity = (source_file->*fn)(name)) {
                    return entity;
                }
            }
        }
        return nullptr;
    }

    FunctorDecl *TranslateUnit::getFunctor(const StringRef &name) const {
        return getAnyInSources(name, source_files_, &SourceFile::getFunctor);
    }

    ProgSetDecl *TranslateUnit::getProgSet(const StringRef &name) const {
        return getAnyInSources(name, source_files_, &SourceFile::getProgSet);
    }

    TypeDecl *TranslateUnit::getType(const StringRef &name) const {
        TypeDecl *type_decl = getAnyInSources(name, source_files_, &SourceFile::getType);
        if (type_decl) { return type_decl; }
        auto found_builtin = named_builtin_type_map_.find(name);
        if (found_builtin != named_builtin_type_map_.end()) { return found_builtin->second; }
        return nullptr;
    }

    GlobalVariableDecl *TranslateUnit::getGlobalVari(const StringRef &name) const {
        return getAnyInSources(name, source_files_, &SourceFile::getGlobalVari);
    }

    MacroDecl *TranslateUnit::getMacro(const StringRef &name) const {
        return getAnyInSources(name, source_files_, &SourceFile::getMacro);
    }

    /***************************************************
     * SourceFile
     ***************************************************/

    void SourceFile::registResourceTo(TranslateUnit *translateUnit) {
        translateUnit->appendSourceFile(this);
    }

    FunctorDecl *        SourceFile::getFunctor   (const StringRef &name) const { return nullptr; }
    ProgSetDecl *        SourceFile::getProgSet   (const StringRef &name) const { return nullptr; }
    TypeDecl *           SourceFile::getType      (const StringRef &name) const { return nullptr; }
    GlobalVariableDecl * SourceFile::getGlobalVari(const StringRef &name) const { return nullptr; }
    MacroDecl *          SourceFile::getMacro     (const StringRef &name) const { return nullptr; }

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

    FunctorDecl *ProgramSetFile::getFunctor(const StringRef &name) const {
        if (program_set_declares_) {
            return program_set_declares_->getFunctionDecl(name);
        } else {
            return nullptr;
        }
    }
    ProgSetDecl *ProgramSetFile::getProgSet(const StringRef &name) const {
        if (program_set_declares_) {
            if (strcmp(program_set_declares_->getNameStr(), name.c_str()) == 0) {
                return program_set_declares_;
            }
        }
        return nullptr;
    }

    /***************************************************
     * DataStructureFile
     ***************************************************/

    void DataStructureFile::appendStructureDecl(StructureDecl *structureDecl) {
        structure_decl_map_[structureDecl->getNameRef()] = structureDecl;
        setChild(structureDecl);
    }

    const DataStructureFile::StructDeclMapTy & DataStructureFile::getTypes() const { return structure_decl_map_; }

    TypeDecl *DataStructureFile::getType(const StringRef &name) const {
        auto found = structure_decl_map_.find(name);
        if (found != structure_decl_map_.end()) {
            return found->second;
        } else {
            return nullptr;
        }
    }

    /***************************************************
     * GlobalVariableFile
     ***************************************************/

    void GlobalVariableFile::appendGlobalVariableDecl(GlobalVariableDecl *globalVariableDecl) {
        global_variable_map_[globalVariableDecl->getNameRef()] = globalVariableDecl;
        setChild(globalVariableDecl);
    }

    const GlobalVariableFile::GlobalVariMapTy &GlobalVariableFile::getGlobalVariMap() const { return global_variable_map_; }

    GlobalVariableDecl *GlobalVariableFile::getGlobalVari(const StringRef &name) const {
        auto found = global_variable_map_.find(name);
        if (found != global_variable_map_.end()) {
            return found->second;
        } else {
            return nullptr;
        }
    }

    /***************************************************
     * APIDeclareFile
     ***************************************************/

    void APIDeclareFile::appendAPIDeclare(APICommandDecl *apiCommandDecl) {
        api_declares_[apiCommandDecl->getNameRef()] = apiCommandDecl;
        setChild(apiCommandDecl);
    }

    const APIDeclareFile::DllDefMapTy & APIDeclareFile::getAPIDefMap () const { return api_declares_; }

    FunctorDecl *APIDeclareFile::getFunctor(const StringRef &name) const {
        auto found = api_declares_.find(name);
        if (found != api_declares_.end()) {
            return found->second;
        } else {
            return nullptr;
        }
    }

    /***************************************************
     * MacroDeclareFile
     ***************************************************/

    void MacroDeclareFile::appendMacroDeclare(MacroDecl *macroDecl) {
        macros_declares_[macroDecl->getNameRef()] = macroDecl;
        setChild(macroDecl);
    }

    const MacroDeclareFile::MacroDeclMapTy & MacroDeclareFile::getMacroDeclMap () const { return macros_declares_; }

    MacroDecl *MacroDeclareFile::getMacro(const StringRef &name) const {
        auto found = macros_declares_.find(name);
        if (found != macros_declares_.end()) {
            return found->second;
        } else {
            return nullptr;
        }
    }

    /***************************************************
     * IdentDef
     ***************************************************/

    const char *        IdentDef::name    () const { return id_.c_str(); }
    const StringRef &   IdentDef::id      () const { return id_; }

    void                IdentDef::setDecl (TagDecl *tagDecl) { tag_decl_ = tagDecl; }
    TagDecl *           IdentDef::decl    () const           { return tag_decl_; }

    /***************************************************
     * MacroDecl
     ***************************************************/

    MacroDecl::MacroDecl(IdentDef *name, Value *value) : TagDecl(name), macro_value_(value) {}

    Value *MacroDecl::getValue() { return macro_value_; }

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

    IdentDef *          TagDecl::getName    () const    { return name_; }
    const StringRef &   TagDecl::getNameRef () const    { return name_->id(); }
    const char *        TagDecl::getNameStr () const    { return name_->name(); }

    void                TagDecl::setComment     (const TString &comment)   { comment_ = comment; }
    const TString &     TagDecl::getComment     () const                   { return comment_; }
    const char *        TagDecl::getCommentStr  () const                   { return comment_.string_.c_str(); }

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
            wrapTypeUse<ReferenceType>();
        }
        else if (Str2Attr::isNameOfNullable(attribute.string_)) {
            is_nullable_  = true;
        }
        else if (Str2Attr::isNameOfArray(attribute.string_)) {
            wrapTypeUse<ArrayDecl>(std::vector<size_t>());
        }
        else {
            Decl::applyAttribute(attribute);
        }
    }

    void ParameterDecl::markAsVariParam ()          { is_variable_param_ = true; }
    bool ParameterDecl::isVariParam     () const    { return is_variable_param_; }

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
        if (Str2Attr::isNameOfReference(attribute.string_)) {
            wrapTypeUse<ReferenceType>();
        }
        else {
            VariableDecl::applyAttribute(attribute);
        }
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

    void FunctorDecl::appendParameter(ParameterDecl *parameterDecl) {
        parameters_.push_back(parameterDecl);
        setChild(parameterDecl);
    }

    const std::vector<ParameterDecl *> &FunctorDecl::getParameters() const { return parameters_; }
          std::vector<ParameterDecl *> &FunctorDecl::getParameters()       { return parameters_; }

    ParameterDecl *FunctorDecl::getParameterAt(unsigned idx) const {
        if (idx < parameters_.size()) {
            return parameters_.at(idx);
        } else {
            assert(false);
            return nullptr;
        }
    }

    ParameterDecl *FunctorDecl::getParamByName(const StringRef &name) const {
        for (ParameterDecl *parameter_decl : parameters_) {
            if (parameter_decl->getNameRef() == name) {
                return parameter_decl;
            }
        }
        assert(false);
        return nullptr;
    }

    int FunctorDecl::getIndexOf(const ParameterDecl *parameterDecl) const {
        for (int idx = 0, count = parameters_.size(); idx < count; ++idx) {
            if (parameters_[idx] == parameterDecl) { return idx; }
        }
        assert(false);
        return -1;
    }

    TypeDecl *FunctorDecl::getReturnType() const { return return_type_; }

    bool FunctorDecl::hasVarArgs() const {
        for (ParameterDecl *parameter_decl : parameters_) {
            if (parameter_decl->isVariParam()) { return true; }
        }
        return false;
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

    BaseVariDecl *StructureDecl::getElementWithIndex(size_t idx) {
        if (idx < members_.size()) {
            return (members_.begin() + idx)->second;
        } else {
            assert(false);
            return nullptr;
        }
    }
    BaseVariDecl *StructureDecl::getElementWithName(const StringRef &variable_name) const {
        auto found = members_.find(variable_name);
        if (found != members_.end()) {
            return found->second;
        } else {
            assert(false);
            return nullptr;
        }
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

    FileVariableDecl *ProgSetDecl::getFileVariableDecl(const StringRef &name) const {
        auto found = file_static_variables_.find(name);
        if (found != file_static_variables_.end()) {
            return found->second;
        } else {
            return nullptr;
        }
    }

    FunctionDecl *ProgSetDecl::getFunctionDecl(const StringRef &name) const {
        auto found = function_decls_.find(name);
        if (found != function_decls_.end()) {
            return found->second;
        } else {
            return nullptr;
        }
    }

    std::vector<FunctorDecl *> ProgSetDecl::getFuncSignatures() {
        std::vector<FunctorDecl *> signatures;
        for (auto &item : function_decls_) {
            signatures.push_back(item.second);
        }
        return signatures;
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

    LocalVariableDecl *FunctionDecl::getLocalVari(const StringRef &name) const {
        auto found = local_vari_.find(name);
        if (found != local_vari_.end()) {
            return found->second;
        } else {
            return nullptr;
        }
    }

    StatementBlock *FunctionDecl::getFunctionBody() const { return statement_list_; }

    /***************************************************
     * APICommandDecl
     ***************************************************/

    const TString &     APICommandDecl::getLibraryName   () const { return library_file_; }
    LibraryType         APICommandDecl::getLibraryType   () const { return library_type_; }
    IdentDef *          APICommandDecl::getApiName       () const { return api_name_;     }

    ArgumentPassModel   APICommandDecl::getArguPassModel () const { return argument_pass_model_; }
    void                APICommandDecl::setArguPassModel (ArgumentPassModel model) { argument_pass_model_ = model; }

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

    void AssignStmt::setLHS(HierarchyIdentifier *lhs) { lhs_ = lhs; setChild(lhs); }
    void AssignStmt::setRHS(Expression *rhs)          { rhs_ = rhs; setChild(rhs); }

    HierarchyIdentifier *   AssignStmt::getLHS() const { return lhs_; }
    Expression *            AssignStmt::getRHS() const { return rhs_; }

    /***************************************************
     * LoopControlStmt
     ***************************************************/

    LoopStatement *LoopControlStmt::getControlledLoop() {
        for (Node *cur = this; cur; cur = cur->getParent()) {
            if (LoopStatement *loop_statement = cur->as<LoopStatement>()) {
                return loop_statement;
            }
        }
        assert(false);
        return nullptr;
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

    size_t          IfStmt::branchesCount() const           { return switches_.size() + (default_statement_ ? 1 : 0); }
    Expression *    IfStmt::conditionAt (size_t idx) const  { return switches_.at(idx).first;  }
    Statement *     IfStmt::branchBodyAt(size_t idx) const  { return switches_.at(idx).second; }
    Statement *     IfStmt::defaultBody () const            { return default_statement_; }

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

    Expression *         RangeForStmt::getRangeSize () const { return range_size_; }
    HierarchyIdentifier *RangeForStmt::getLoopVari  () const { return loop_vari_;  }

    /***************************************************
     * ForStmt
     ***************************************************/

    void ForStmt::setStartValue(Expression *startValue)        { start_value_ = startValue; setChild(startValue); }
    void ForStmt::setStopValue (Expression *stopValue)         { stop_value_  = stopValue;  setChild(stopValue); }
    void ForStmt::setStepValue (Expression *stepValue)         { step_value_  = stepValue;  setChild(stepValue); }
    void ForStmt::setLoopVari  (HierarchyIdentifier *loopVari) { loop_vari_   = loopVari;   setChild(loopVari); }

    Expression *            ForStmt::getStartValue () const { return start_value_; }
    Expression *            ForStmt::getStopValue  () const { return stop_value_ ; }
    Expression *            ForStmt::getStepValue  () const { return step_value_ ; }
    HierarchyIdentifier *   ForStmt::getLoopVari   () const { return loop_vari_  ; }

    /***************************************************
     * DoWhileStmt
     ***************************************************/

    void DoWhileStmt::setCondition(Expression *condition) { condition_ = condition; setChild(condition); }

    Expression *DoWhileStmt::getCondition() const { return condition_; }

    /***************************************************
     * ReturnStmt
     ***************************************************/

    void ReturnStmt::setReturnValue(Expression *returnValue) { return_value_ = returnValue; setChild(returnValue); }

    Expression * ReturnStmt::getReturnValue() const { return return_value_; }

    /***************************************************
     * FunctionCall
     ***************************************************/

    void FunctionCall::setName(IdentRefer *funcName) { name_ = funcName; setChild(funcName); }

    void FunctionCall::appendArgument (Expression *argument) {
        arguments_.emplace_back(argument);
        setChild(argument);
    }

    void FunctionCall::setArguments(const std::vector<Expression *> &arguments) {
        arguments_.clear();
        for (Expression *argument : arguments) {
            appendArgument(argument);
        }
    }

    void FunctionCall::bindPrototype(FunctorDecl *functorDecl) {
        callee_ = functorDecl;
    }

    FunctorDecl *FunctionCall::getCallee() const {
        return callee_;
    }

    size_t FunctionCall::getArgumentsCount() const {
        return arguments_.size();
    }

    Expression * FunctionCall::getArgumentAt(size_t idx) const {
        return arguments_.at(idx);
    }

    std::vector<Expression *> &FunctionCall::getArguments() {
        return arguments_;
    }

    const std::vector<Expression *> &FunctionCall::getArguments() const {
        return arguments_;
    }

    bool FunctionCall::isArgument(Expression *expr) const {
        return isArgument(const_cast<const Expression *>(expr));
    }
    bool FunctionCall::isArgument(const Expression *expr) const {
        return indexOfArgument(expr) >= 0;
    }

    int FunctionCall::indexOfArgument(const Expression *expr) const {
        for (unsigned idx = 0, count = arguments_.size(); idx < count; ++idx) {
            if (expr == arguments_[idx]) {
                return idx;
            }
        }
        return -1;
    }

    int FunctionCall::indexOfArgument(Expression *expr) const {
        return indexOfArgument(const_cast<const Expression *>(expr));
    }

    /***************************************************
     * IdentRefer
     ***************************************************/

    IdentDef * IdentRefer::def() const { return reference_; }

    /***************************************************
     * ArrayIndex
     ***************************************************/

    void ArrayIndex::setBaseComponent(NameComponent *baseComponent) { base_  = baseComponent; setChild(baseComponent); }
    void ArrayIndex::setIndexExpr    (Expression *indexExpr)        { index_ = indexExpr;     setChild(indexExpr); }

    /***************************************************
     * _OperatorExpression
     ***************************************************/

    void                 OperatedExpression::setOperator    (const OperatorType &     opt) { operator_type_ = opt; }
    void                 OperatedExpression::setOperator    (const OperatorType::Opt &opt) { setOperator(OperatorType(opt)); }
    const OperatorType & OperatedExpression::getOperator    () const                       { return operator_type_; }
    void                 OperatedExpression::setOperatorText(const TString & operatorText) { operator_ = operatorText; }

    /***************************************************
     * UnaryExpression
     ***************************************************/

    void        UnaryExpression::setOperand(Expression *operand) { operand_value_ = operand; setChild(operand); }
    Expression *UnaryExpression::getOperand()                    { return operand_value_; }

    /***************************************************
     * BinaryExpression
     ***************************************************/

    void BinaryExpression::setLHS(Expression *lhsExpr) { lhs_ = lhsExpr; setChild(lhsExpr); }
    void BinaryExpression::setRHS(Expression *rhsExpr) { rhs_ = rhsExpr; setChild(rhsExpr); }

    Expression *BinaryExpression::getLHS() { return lhs_; }
    Expression *BinaryExpression::getRHS() { return rhs_; }

    /***************************************************
     * ValueOfDataSet
     ***************************************************/

    void ValueOfDataSet::appendElement(Expression *element) { elements_.push_back(element); setChild(element); }

    /***************************************************
     * ValueOfDatetime
     ***************************************************/

    void ValueOfDatetime::setTime(time_t time) { time_ = time; }

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

    /******************************************************************
     * TypeConvert
     ******************************************************************/

    void TypeConvert::setFromExpression(Expression *expression) { from_expression_ = expression; setChild(expression); }
    void TypeConvert::setTargetType    (TypeDecl *  targetType) { target_type_ = targetType;     setChild(targetType); }

}
