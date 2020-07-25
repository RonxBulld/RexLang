//
// Created by rex on 2020/7/25.
//

#include "../NodeDecl.h"
#include "SemaContext.h"
#include "APISemaAction.h"
#include "SemaCFG.h"

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
    void ConstDeclareFile::sematicAnalysisInternal(SemaContext &semaCtx) {
        SourceFile::sematicAnalysisInternal(semaCtx);
        SemaNamedMap(consts_declares_, semaCtx);
    }

    void Decl::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void TagDecl::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void TypeDecl::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void VariTypeDecl::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void StructureDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        VariTypeDecl::sematicAnalysisInternal(semaCtx);
        SemaNamedMap(members_, semaCtx);
    }

    void BuiltinTypeDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        VariTypeDecl::sematicAnalysisInternal(semaCtx);
    }

    void ArrayDecl::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void ConstDecl::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void BaseVariDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        // 明确类型指针
        clarifyNamedType(vari_type_decl_, type_name_.string_, this);
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

    void ParameterDecl     ::sematicAnalysisInternal(SemaContext &semaCtx) { BaseVariDecl::sematicAnalysisInternal(semaCtx); }

    void MemberVariableDecl::sematicAnalysisInternal(SemaContext &semaCtx) {}

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

    void ProgSetDecl::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void APICommandDecl::sematicAnalysisInternal(SemaContext &semaCtx) {
        FunctorDecl::sematicAnalysisInternal(semaCtx);

        // 根据外部API的名称处理接口属性
        sa::ExecuteAllAPISemaAction(this, semaCtx);
    }

    void Statement::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void IfStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void StatementBlock::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void LoopStatement::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void WhileStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void RangeForStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void ForStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void DoWhileStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void AssignStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void ControlStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void LoopControlStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void ContinueStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void BreakStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void ReturnStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void ExitStmt::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void Expression::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void HierarchyIdentifier::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void NameComponent::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void Identifier::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void ArrayIndex::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void FunctionCall::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void UnaryExpression::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void BinaryExpression::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void _OperatorExpression::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void TypeConvert::sematicAnalysisInternal(SemaContext &semaCtx) {}

    void Value                ::sematicAnalysisInternal(SemaContext &semaCtx) { Expression::sematicAnalysisInternal(semaCtx); }
    void FuncAddrExpression   ::sematicAnalysisInternal(SemaContext &semaCtx) { Expression::sematicAnalysisInternal(semaCtx); }
    void ResourceRefExpression::sematicAnalysisInternal(SemaContext &semaCtx) { Expression::sematicAnalysisInternal(semaCtx); }

    void ValueOfDataSet ::sematicAnalysisInternal(SemaContext &semaCtx) { Value::sematicAnalysisInternal(semaCtx); }
    void ValueOfDatetime::sematicAnalysisInternal(SemaContext &semaCtx) { Value::sematicAnalysisInternal(semaCtx); }
    void ValueOfBool    ::sematicAnalysisInternal(SemaContext &semaCtx) { Value::sematicAnalysisInternal(semaCtx); }
    void ValueOfDecimal ::sematicAnalysisInternal(SemaContext &semaCtx) { Value::sematicAnalysisInternal(semaCtx); }
    void ValueOfString  ::sematicAnalysisInternal(SemaContext &semaCtx) { Value::sematicAnalysisInternal(semaCtx); }

}
