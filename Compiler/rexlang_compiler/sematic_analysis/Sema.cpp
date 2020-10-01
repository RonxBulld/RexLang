//
// Created by rex on 2020/7/25.
//

#include "../NodeDecl.h"
#include "../rtti.h"
#include "SemaContext.h"
#include "APISemaAction.h"
#include "SemaCFG.h"
#include "../ASTUtility.h"

template <typename MapTy>
void SemaNamedMap(MapTy &namedMap, rexlang::SemaContext &semaCtx) {
    for (auto &item : namedMap) {
        auto *node = item.second;
        assert(node);
        node->sematicAnalysisInternal(semaCtx);
    }
}

template <typename ArrayTy>
void SemaVector(ArrayTy &vect, rexlang::SemaContext &semaCtx) {
    for (auto *node : vect) {
        node->sematicAnalysisInternal(semaCtx);
    }
}

namespace rexlang {

    LocalVariableDecl *createLocalVari(VariTypeDecl *type, StringRef namePrefix, ASTContext *astCtx, FunctionDecl *function) {
        size_t idx = 0;
        StringRef name = namePrefix;
        while (function->findDeclWithNameString(name)) {
            name = StringPool::Create(namePrefix.str() + "_" + std::to_string(idx));
        }
        LocalVariableDecl *implicit_local_vari = CreateNode<LocalVariableDecl>(astCtx);
        implicit_local_vari->setName(TString({name, 0}));
        implicit_local_vari->setValType(type);
        function->appendLocalVariable(implicit_local_vari);
        return implicit_local_vari;
    }

    TypeDecl *semaExprAndRetType(Expression *expr, SemaContext &semaCtx) {
        if (expr) {
            expr->sematicAnalysisInternal(semaCtx);
            return expr->getExpressionType();
        }
        else {
            return nullptr;
        }
    }

    template <bool (TypeDecl::*pmf)() const>
    bool semaExprAndCheckTypeFeature(Expression *expr, SemaContext &semaCtx) {
        if (TypeDecl *ty = semaExprAndRetType(expr, semaCtx)) {
            return (ty->*pmf)();
        }
        else {
            return false;
        }
    }

    bool semaExprAndIsInt   (Expression *expr, SemaContext &semaCtx) { return semaExprAndCheckTypeFeature<&TypeDecl::isIntegerClass>(expr, semaCtx); }
    bool semaExprAndIsBoolEx(Expression *expr, SemaContext &semaCtx) { return semaExprAndCheckTypeFeature<&TypeDecl::isExtendBooleanType>(expr, semaCtx); }

    template <typename Ptr>
    void clarifyNamedType(Ptr & typePtr, const StringRef &typeName, Node *in) {
        if (typePtr) {
            assert(typePtr == in->findDeclWithNameString(typeName)->as<VariTypeDecl>());
        }
        else {
            typePtr = in->findDeclWithNameString(typeName)->as<VariTypeDecl>();
            assert(typePtr);
        }
    }

    void Node::sematicAnalysisInternal(SemaContext &semaCtx) {
        assert(false);
    }

    /********************************************************
     * TranslateUnit
     ********************************************************/

    void TranslateUnit::sematicAnalysisInternal(SemaContext &semaCtx) {
        semaCtx.setTranslateUnit(getTranslateUnit());

        // 检查语言版本
        if (getSourceEdition() != 2) {
            assert(false);
            return;
        }

        SemaVector(source_files_, semaCtx);

        // 指定入口函数

        StringRef start_entry_name = StringPool::Create(u8"_启动子程序");
        FunctorDecl *main_entry = getFunctor(start_entry_name);
        assert(main_entry);
        setMainEnrty(main_entry);

        // TODO: 检查所有父节点指针是否被正确设置
    }

    /********************************************************
     * SourceFile
     ********************************************************/

    void SourceFile::sematicAnalysisInternal(SemaContext &semaCtx) {
        registResourceTo(semaCtx.getTranslateUnit());
    }

    void ProgramSetFile::sematicAnalysisInternal(SemaContext &semaCtx) {
        SourceFile::sematicAnalysisInternal(semaCtx);

        if (program_set_declares_) {
            program_set_declares_->sematicAnalysisInternal(semaCtx);
        }
    }

    void GlobalVariableFile::sematicAnalysisInternal(SemaContext &semaCtx) {
        SourceFile::sematicAnalysisInternal(semaCtx);
        SemaNamedMap(global_variable_map_, semaCtx);
    }

    void DataStructureFile::sematicAnalysisInternal(SemaContext &semaCtx) {
        SourceFile::sematicAnalysisInternal(semaCtx);
        SemaNamedMap(structure_decl_map_, semaCtx);
    }

    void APIDeclareFile::sematicAnalysisInternal(SemaContext &semaCtx) {
        SourceFile::sematicAnalysisInternal(semaCtx);
        SemaNamedMap(api_declares_, semaCtx);
    }

    void MacroDeclareFile::sematicAnalysisInternal(SemaContext &semaCtx) {
        SourceFile::sematicAnalysisInternal(semaCtx);
        SemaNamedMap(macros_declares_, semaCtx);
    }

    /*===------------------------------------------------===*
     * Decl
     *===------------------------------------------------===*/

    void Decl::sematicAnalysisInternal(SemaContext &semaCtx) {
    }

    void TagDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        Decl::sematicAnalysisInternal(semaCtx);
    }

    void TypeDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        TagDecl::sematicAnalysisInternal(semaCtx);
    }

    void VariTypeDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        TypeDecl::sematicAnalysisInternal(semaCtx);
    }

    void StructureDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        VariTypeDecl::sematicAnalysisInternal(semaCtx);
        SemaNamedMap(members_, semaCtx);
    }

    void BuiltinTypeDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        VariTypeDecl::sematicAnalysisInternal(semaCtx);
    }

    void ArrayDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        VariTypeDecl::sematicAnalysisInternal(semaCtx);

        assert(base_type_);
    }

    void MacroDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        TagDecl::sematicAnalysisInternal(semaCtx);

        assert(getValue());
    }

    void BaseVariDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        TagDecl::sematicAnalysisInternal(semaCtx);

        // 明确类型指针
        if (type_name_ && !type_) {
            type_ = rtti::dyn_cast<VariTypeDecl>(this->getType());
        }
        assert(type_);
    }

    void VariableDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        BaseVariDecl::sematicAnalysisInternal(semaCtx);

        // 处理数组的情况
        if (is_array_) {
            ArrayDecl *array_decl = ArrayDecl::get(getType(), dimensions_);
            setValType(array_decl);
        }
    }

    void GlobalVariableDecl::sematicAnalysisInternal(SemaContext &semaCtx) { VariableDecl::sematicAnalysisInternal(semaCtx); }
    void LocalVariableDecl ::sematicAnalysisInternal(SemaContext &semaCtx) { VariableDecl::sematicAnalysisInternal(semaCtx); }
    void FileVariableDecl  ::sematicAnalysisInternal(SemaContext &semaCtx) { VariableDecl::sematicAnalysisInternal(semaCtx); }
    void MemberVariableDecl::sematicAnalysisInternal(SemaContext &semaCtx) { VariableDecl::sematicAnalysisInternal(semaCtx); }

    void ParameterDecl     ::sematicAnalysisInternal(SemaContext &semaCtx) { BaseVariDecl::sematicAnalysisInternal(semaCtx); }

    void ProgSetDecl       ::sematicAnalysisInternal(SemaContext &semaCtx) {
        TagDecl::sematicAnalysisInternal(semaCtx);

        SemaNamedMap(file_static_variables_,  semaCtx);
        SemaNamedMap(function_decls_,         semaCtx);
        SemaNamedMap(signature_of_functions_, semaCtx);
    }

    void FunctorDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        TypeDecl::sematicAnalysisInternal(semaCtx);

        // 明确返回类型指针
        clarifyNamedType(return_type_, return_type_name_.string_, this);

        // 明确参数类型
        SemaVector(parameters_, semaCtx);

    }

    void FunctionDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        FunctorDecl::sematicAnalysisInternal(semaCtx);

        // 明确局部变量类型
        SemaNamedMap(local_vari_, semaCtx);

        // 检查每一条语句构造和表达式运算是否合法
        if (statement_list_) {
            statement_list_->sematicAnalysisInternal(semaCtx);

            // 检查所有分支返回
            cfg::CheckAllBranchesReturnCorrectly(this);
        }
    }

    void APICommandDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        FunctorDecl::sematicAnalysisInternal(semaCtx);

        // 根据外部API的名称处理接口属性
        sa::ExecuteAllAPISemaAction(this, semaCtx);
    }

    /********************************************************
     * Statement
     ********************************************************/

    void Statement::sematicAnalysisInternal(SemaContext &semaCtx) {
    }

    void IfStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        Statement::sematicAnalysisInternal(semaCtx);

        // 检查是否有分支
        if (branchesCount() == 0) {
            assert(false);
            return;
        }

        // 检查条件语句的条件表达式是否为扩展布尔类型
        for (size_t idx = 0, count = branchesCount(); idx < count; idx++) {
            Expression *condition = conditionAt(idx);       assert(condition);
            Statement *branch_body = branchBodyAt(idx);     assert(branch_body);

            if (semaExprAndIsBoolEx(condition, semaCtx)) { assert(false); return; }
            branch_body->sematicAnalysisInternal(semaCtx);
        }
        if (defaultBody()) {
            defaultBody()->sematicAnalysisInternal(semaCtx);
        }
    }

    void StatementBlock::sematicAnalysisInternal(SemaContext &semaCtx) {
        Statement::sematicAnalysisInternal(semaCtx);

        // 直接遍历列表进行检查
        for (Statement* stmt : getStatements()) {
            stmt->sematicAnalysisInternal(semaCtx);
        }
    }

    void LoopStatement::sematicAnalysisInternal(SemaContext &semaCtx) {
        Statement::sematicAnalysisInternal(semaCtx);

        if (Statement *loop_body = getLoopBody()) {
            loop_body->sematicAnalysisInternal(semaCtx);
        }
    }

    void WhileStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        LoopStatement::sematicAnalysisInternal(semaCtx);

        // 检查循环条件语句的条件表达式是否为扩展布尔类型
        if (semaExprAndIsBoolEx(getLoopCondition(), semaCtx)) { assert(false); return; }
    }

    void RangeForStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        LoopStatement::sematicAnalysisInternal(semaCtx);

        // 检查次数表达式类型是否为整数族
        Expression *range_expr = getRangeSize();
        if (!semaExprAndIsInt(range_expr, semaCtx)) { assert(false); return; }

        // 如果循环变量存在则检查变量类型是否为整数族
        if (HierarchyIdentifier *loop_vari = getLoopVari()) {
            if (!semaExprAndIsInt(loop_vari, semaCtx)) { assert(false); return; }
        }
    }

    void ForStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        LoopStatement::sematicAnalysisInternal(semaCtx);

        // 检查初值表达式、终值表达式、步长表达式类型是否为整数族
        if (!semaExprAndIsInt(getStartValue(), semaCtx)) { assert(false); return; }
        if (!semaExprAndIsInt(getStopValue(),  semaCtx)) { assert(false); return; }
        if (!semaExprAndIsInt(getStepValue(),  semaCtx)) { assert(false); return; }

        // 检查循环变量
        if (HierarchyIdentifier *loop_vari = getLoopVari()) {
            if (!semaExprAndIsInt(loop_vari, semaCtx)) { assert(false); return; }
        }
    }

    void DoWhileStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        LoopStatement::sematicAnalysisInternal(semaCtx);

        // 检查循环条件语句的条件表达式是否为扩展布尔类型
        if (!semaExprAndIsBoolEx(getCondition(), semaCtx)) { assert(false); return; }
    }

    void AssignStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        Statement::sematicAnalysisInternal(semaCtx);

        // 检查赋值语句左右子式类型是否匹配或兼容

        TypeDecl *lhs_type = semaExprAndRetType(getLHS(), semaCtx);
        if (!lhs_type) { assert(false); return; }

        TypeDecl *rhs_type = semaExprAndRetType(getRHS(), semaCtx);
        if (!rhs_type) { assert(false); return; }

        if (!lhs_type->isAssginValidFrom(rhs_type)) {
            assert(false);
            return;
        }

        if (Expression *casted = getRHS()->castTo(lhs_type)) {
            setRHS(casted);
        }
        else {
            assert(nullptr);
        }
    }

    void ControlStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        Statement::sematicAnalysisInternal(semaCtx);
    }

    void LoopControlStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        ControlStmt::sematicAnalysisInternal(semaCtx);

        // 检查是否在循环内

        setControlledLoop(utility::FindSpecifyTypeParent<LoopStatement>(this));
        assert(getControlledLoop());

    }

    void ContinueStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        LoopControlStmt::sematicAnalysisInternal(semaCtx);
    }

    void BreakStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        LoopControlStmt::sematicAnalysisInternal(semaCtx);
    }

    void ReturnStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        ControlStmt::sematicAnalysisInternal(semaCtx);

        // 检查是否在函数定义内

        FunctionDecl *function_decl = utility::FindSpecifyTypeParent<FunctionDecl>(this);
        if (function_decl == nullptr) {
            assert(false);
            return;
        }

        // 检查返回值表达式类型是否和函数返回值匹配

        // 首先检查是否存在

        Expression *return_value = getReturnValue();

        if ((function_decl->getReturnType() != nullptr) ^ (return_value != nullptr)) {
            assert(false);
            return;
        }

        // 然后检查匹配问题

        if (return_value) {
            TypeDecl *act_ret_type = semaExprAndRetType(return_value, semaCtx);
            if (!act_ret_type) { assert(false); return; }

            VariTypeDecl *decl_ret_type = rtti::dyn_cast<VariTypeDecl>(function_decl->getReturnType());
            if (!decl_ret_type) { assert(false); return; }

            if (decl_ret_type->isAssginValidFrom(act_ret_type)) {
                return_value = return_value->castTo(decl_ret_type);
                if (return_value) {
                    setReturnValue(return_value);
                }
                else {
                    assert(false);
                }
            }
            else {
                assert(false);
            }
        }
    }

    void ExitStmt::sematicAnalysisInternal(SemaContext &semaCtx) {
        ControlStmt::sematicAnalysisInternal(semaCtx);
    }

    /********************************************************
     * Expression
     ********************************************************/

    void Expression::sematicAnalysisInternal(SemaContext &semaCtx) {
        Statement::sematicAnalysisInternal(semaCtx);

        CheckExpression();
    }

    void HierarchyIdentifier::sematicAnalysisInternal(SemaContext &semaCtx) {
        Expression::sematicAnalysisInternal(semaCtx);

        SemaVector(name_components_, semaCtx);
    }

    void NameComponent::sematicAnalysisInternal(SemaContext &semaCtx) {
        Expression::sematicAnalysisInternal(semaCtx);
    }

    void IdentRefer::sematicAnalysisInternal(SemaContext &semaCtx) {
        NameComponent::sematicAnalysisInternal(semaCtx);
    }

    void ArrayIndex::sematicAnalysisInternal(SemaContext &semaCtx) {
        NameComponent::sematicAnalysisInternal(semaCtx);
    }

    void FunctionCall::sematicAnalysisInternal(SemaContext &semaCtx) {
        NameComponent::sematicAnalysisInternal(semaCtx);

        FunctorDecl *functor_decl = getCallee();
        if (functor_decl == nullptr) {
            assert(false);
            return;
        }
        functor_decl->sematicAnalysisInternal(semaCtx);

        // 检查函数实参是否符合形参定义

        for (size_t idx = 0, count = getArgumentsCount(); idx < count; ++idx) {
            Expression *argu = getArgumentAt(idx);
            argu->sematicAnalysisInternal(semaCtx);
        }

        if (!matchFunctor(functor_decl)) {
            assert(false);
            return;
        }

        assert(functor_decl->getReturnType());

    }

    void UnaryExpression::sematicAnalysisInternal(SemaContext &semaCtx) {
        OperatedExpression::sematicAnalysisInternal(semaCtx);
    }

    void BinaryExpression::sematicAnalysisInternal(SemaContext &semaCtx) {
        OperatedExpression::sematicAnalysisInternal(semaCtx);
    }

    void OperatedExpression::sematicAnalysisInternal(SemaContext &semaCtx) {
        Expression::sematicAnalysisInternal(semaCtx);
    }

    void TypeConvert::sematicAnalysisInternal(SemaContext &semaCtx) {
        Expression::sematicAnalysisInternal(semaCtx);

        getSourceExpr()->sematicAnalysisInternal(semaCtx);
        TypeDecl *src_ty = getSourceType();
        TypeDecl *tgt_ty = getTargetType();

        // 检查从源类型到目标类型是否可行

        if (!tgt_ty->isAssginValidFrom(src_ty)) {
            assert(false);
            return;
        }

    }

    void Value                ::sematicAnalysisInternal(SemaContext &semaCtx) { Expression::sematicAnalysisInternal(semaCtx); }
    void FuncAddrExpression   ::sematicAnalysisInternal(SemaContext &semaCtx) { Expression::sematicAnalysisInternal(semaCtx); }

    void ValueOfDataSet ::sematicAnalysisInternal(SemaContext &semaCtx) { Value::sematicAnalysisInternal(semaCtx); }
    void ValueOfDatetime::sematicAnalysisInternal(SemaContext &semaCtx) { Value::sematicAnalysisInternal(semaCtx); }
    void ValueOfBool    ::sematicAnalysisInternal(SemaContext &semaCtx) { Value::sematicAnalysisInternal(semaCtx); }
    void ValueOfDecimal ::sematicAnalysisInternal(SemaContext &semaCtx) { Value::sematicAnalysisInternal(semaCtx); }
    void ValueOfString  ::sematicAnalysisInternal(SemaContext &semaCtx) { Value::sematicAnalysisInternal(semaCtx); }

}
