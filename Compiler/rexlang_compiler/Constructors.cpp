//
// Created by rex on 2020/7/28.
//

#include "NodeDecl.h"
#include "rtti.h"

namespace rexlang {

    /******************************************************************
     * TagDecl
     ******************************************************************/

    TagDecl::TagDecl(IdentDef *name)
        : name_(name) {
        setChild(name_);
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

    ParameterDecl::ParameterDecl(VariTypeDecl *type, IdentDef *name)
        : BaseVariDecl(type, name) {
    }

    /******************************************************************
     * ReferenceType
     ******************************************************************/

    ReferenceType::ReferenceType(TypeDecl *pointeeType) : VariTypeDecl(nullptr), pointee_type_(pointeeType) {}

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
     * VariTypeDecl
     ******************************************************************/

    VariTypeDecl::VariTypeDecl(IdentDef *name) : TypeDecl(name) {}

    /******************************************************************
     * StructureDecl
     ******************************************************************/

    StructureDecl::StructureDecl(IdentDef *name) : VariTypeDecl(name) {}

    /******************************************************************
     * ArrayDecl
     ******************************************************************/

    ArrayDecl::ArrayDecl(TypeDecl *baseType, const std::vector<size_t> &dimensions)
            : VariTypeDecl(CreateNode<IdentDef>(baseType->getAstContext(), "")),
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
    }

    /******************************************************************
     * ProgSetDecl
     ******************************************************************/

    ProgSetDecl::ProgSetDecl(IdentDef *name) : TagDecl(name) {}

    /******************************************************************
     * AssignStmt
     ******************************************************************/

    AssignStmt::AssignStmt(HierarchyIdentifier *lhs, Expression *rhs) {
        setLHS(lhs);
        setRHS(rhs);
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

    RangeForStmt::RangeForStmt(Expression *rangeSize, HierarchyIdentifier *loopVari, Statement *loopBody)
        : LoopStatement(loopBody) {
        setRangeSize(rangeSize);
        setLoopVariable(loopVari);
    }

    ForStmt::ForStmt(Expression *startValue, Expression *stopValue, Expression *stepValue, HierarchyIdentifier *loopVari, Statement *loopBody)
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
     * HierarchyIdentifier
     ******************************************************************/

    HierarchyIdentifier::HierarchyIdentifier(const std::vector<NameComponent *> &nameComponents) {
        for (NameComponent *name_component : nameComponents) {
            AppendComponent(name_component);
        }
    }

    /******************************************************************
     * IdentRefer
     ******************************************************************/

    IdentRefer::IdentRefer(const StringRef &name, NameComponent *prefix) {
        // 查找定义
        if (!prefix) {
            // 没有前缀则直接在符号域中开始检索
            if (TagDecl *decl = Node::findDeclWithNameString(name)) {
                reference_ = decl->getName();
            } else {
                assert(false);
            }
        } else {
            TypeDecl *prefix_type = prefix->getExpressionType();
            // prefix_type 应该是一个结构体
            if (StructureDecl *structure_decl = rtti::dyn_cast<StructureDecl>(prefix_type)) {
                if (BaseVariDecl *member = structure_decl->getElementWithName(name)) {
                    reference_ = member->getName();
                } else {
                    assert(false);
                }
            } else {
                assert(false);
            }
        }
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

    FunctionCall::FunctionCall(IdentRefer *name, FunctorDecl *functorDecl, const std::vector<Expression *> &arguments) {
        setName(name);
        setArguments(arguments);
        if (matchFunctor(functorDecl)) {
            bindPrototype(functorDecl);
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
    }

}
