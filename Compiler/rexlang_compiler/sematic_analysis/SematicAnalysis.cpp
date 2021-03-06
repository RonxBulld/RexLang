//
// Created by rex on 2020/1/23.
//

#include "SematicAnalysis.h"

#include "../NodeDecl.h"
#include "../utilities/Str2Attr.h"
#include "../TypeAssert.h"
#include "../ASTUtility.h"
#include "../ASTContext.h"
#include "../ASTAssert.h"
#include "../utilities/Diagnostic.h"
#include "../../../lite_util/Defer.h"
#include "SematicAnalysisNameMangle.h"

namespace rexlang {
    template <typename SrcMapContainer, typename TgtMapContainer, typename Pred>
    bool MergeMap(SrcMapContainer &sourceMap, TgtMapContainer &targetMap, Pred && pred) {
        for (auto & item : sourceMap) {

            // 检查冲突

            auto found = targetMap.find(item.first);
            if (found != targetMap.end()) {
                assert(false);
                return false;
            }

            targetMap[item.first] = pred(item.second);
        }
        return true;
    }

    template<
            typename MapContainer,
            typename ReturnType = std::remove_const_t<typename MapContainer::mapped_type>,
            typename ElementType = typename MapContainer::mapped_type
    >
    bool MergeMap(MapContainer &sourceMap, MapContainer &targetMap) {
        return MergeMap(sourceMap, targetMap, [](const ElementType &value) -> ReturnType {
            return const_cast<ReturnType>(value);
        });
    }

    void SetupHierarchyReferenceType(HierarchyIdentifier *hierarchyIdentifier, IdentifierUsage referenceType) {
        hierarchyIdentifier->identifier_usage_ = referenceType;
        for (NameComponent *name_component : hierarchyIdentifier->name_components_) {

            name_component->identifier_usage_ = IdentifierUsage::kAsRightValue;

            if (ArrayIndex *array_index = name_component->as<ArrayIndex>()) {
                array_index->base_->identifier_usage_ = IdentifierUsage::kAsRightValue;
            }
            else if (FunctionCall *function_call = name_component->as<FunctionCall>()) {
                function_call->function_name_->identifier_usage_ = IdentifierUsage::kAsRightValue;
            }
            else if (Identifier *identifier = name_component->as<Identifier>()) {
                identifier->identifier_usage_ = IdentifierUsage::kAsRightValue;
            }
            else {
                assert(false);
            }
        }
        hierarchyIdentifier->name_components_.back()->identifier_usage_ = referenceType;
    }

    bool SematicAnalysis::Run(TranslateUnit * translateUnitPtr) {

        // this->ast_builder_ = new ASTBuilder(*translateUnitPtr->ast_context_);
        // defer free_ast_builer([&](){ delete this->ast_builder_; this->ast_builder_ = nullptr; });

        if (translateUnitPtr->edition_ != 2) {
            translateUnitPtr->ast_context_->GetDiagnostic()->EditionWrong(translateUnitPtr->edition_);
            return false;
        }
        this->translate_unit_ = translateUnitPtr;

        // 1. 初始化动作

        ASTUtility::FixNodeParent(translateUnitPtr);

        // 1.1. 创建内置数据类型并写入索引表

        this->CreateBuiltinType();

        // 1.2. 合并全局变量、数据结构、外部库引用、函数定义、DLL声明索引表

        this->MergeGlobal();

        // 1.3. 解释外部API的引用名称

        this->ExplainExternAPINameMangle();

        // 1.4. 用翻译单元初始化分析上下文

        this->analysis_context_.PushScope(translateUnitPtr);

        // 2. 针对数据结构定义、类模块定义

        // 2.1. 明确成员的类型指针

        this->SetupAllStructMemberType();

        // 2.2. 明确全局变量、程序集变量类型指针

        this->SetupGlobalAndFileStaticVariableType();

        // 3. 针对可调用声明

        for (auto & func_item : this->translate_unit_->functor_declares_) {

            // 3.1. 明确每一个可调用对象的参数和返回值的类型指针

            if (this->SetupFunctorVariableType(func_item.second) == false) {
                return false;
            }
        }

        // 4. 针对每一个程序集

        for (auto & prog_file_item : this->translate_unit_->program_sets_) {
            this->analysis_context_.PushScope(prog_file_item.second);

            // 4.1 针对每一个函数定义

            for (auto &func_item : prog_file_item.second->function_decls_) {
                this->analysis_context_.PushScope(func_item.second);

                // 4.1.1. 明确函数定义局部变量的类型指针

                if (this->SetupFunctionLocalVariableType(func_item.second) == false) {
                    return false;
                }

                // 4.1.2. 检查每一条语句构造和表达式运算是否合法

                if (this->CheckStatementsAndExpression(func_item.second->statement_list_) == false) {
                    return false;
                }

                // 4.1.3. 检查所有分支返回

                if (this->CheckAllBranchesReturnCorrectly(func_item.second) == false) {
                    return false;
                }
            }
        }

        // 5. 后续处理

        // 5.1. 指定入口函数

        StringRef start_entry = translateUnitPtr->ast_context_->CreateString(u8"_启动子程序");
        translateUnitPtr->main_entry_ = this->analysis_context_.QueryTagDeclFromDynSymbolTableWithName(start_entry)->as<FunctorDecl>();
        assert(translateUnitPtr->main_entry_);
        return true;
    }

    bool SematicAnalysis::CreateBuiltinType() {
        for (auto & name_type_pair : builtin_type_map) {
            ErrOr<std::string> type_name = Str2Attr::BuiltinType2Name(name_type_pair.second);
            if (type_name.NoError()) {
                TString ts_tname;
                ts_tname.string_ = this->translate_unit_->ast_context_->CreateString(type_name.Value());
                ts_tname.location_ = 0;
                BuiltinTypeDeclPtr builtin_type = CreateNode<BuiltinTypeDecl>(this->translate_unit_->ast_context_);
                builtin_type->name_ = ts_tname;
                builtin_type->built_in_type_ = name_type_pair.second;
                this->translate_unit_->global_type_[ts_tname.string_] = builtin_type;
            } else {
                assert(false);
                return false;
            }
        }
        return true;
    }

    bool SematicAnalysis::SetupAllStructMemberType() {
        for (auto & item: this->translate_unit_->global_type_) {
            if (StructureDeclPtr structure_decl = item.second->as<StructureDecl>()) {
                size_t idx = 0;
                for (auto & member_item : structure_decl->members_) {
                    this->SetupMemberVariableType(member_item.second);
                    member_item.second->index_of_struct_ = idx++;
                    if (member_item.second->type_decl_ptr_ == nullptr) {
                        assert(false);
                        return false;
                    }
                }
            }
        }
        return this->CheckIfStructureRecursiveReference();
    }

    bool SematicAnalysis::SetupGlobalAndFileStaticVariableType() {
        // 1. 全局变量
        for (auto & item : this->translate_unit_->global_variables_) {
            this->SetupGlobalVariableType(item.second);
            if (item.second->type_decl_ptr_ == nullptr) {
                return false;
            }
        }
        // 2. 程序集变量
        for (auto & prog_set_item : this->translate_unit_->program_sets_) {
            for (auto & prog_set_vari_item : prog_set_item.second->file_static_variables_) {
                this->SetupFileVariableType(prog_set_vari_item.second);
                if (prog_set_vari_item.second->type_decl_ptr_ == nullptr) {
                    return false;
                }
            }
        }
        return true;
    }

    bool SematicAnalysis::MergeGlobal() {
        TranslateUnitPtr translateUnitPtr = this->translate_unit_;
        for (SourceFilePtr sfptr : translateUnitPtr->source_file_) {
            if (GlobalVariableFile *global_variable_file = sfptr->as<GlobalVariableFile>()) {

                // 全局变量

                bool success = MergeMap(global_variable_file->global_variable_map_, translateUnitPtr->global_variables_);
                if (!success) { return false; }

            } else if (DataStructureFile *data_structure_file_ptr = sfptr->as<DataStructureFile>()) {

                // 数据结构

                bool success = MergeMap(data_structure_file_ptr->structure_decl_map_, translateUnitPtr->global_type_, [](StructureDeclPtr v) -> TypeDeclPtr {
                    return v->as<TypeDecl>();
                });
                if (!success) { return false; }

            } else if (ProgramSetFile *program_set_file = sfptr->as<ProgramSetFile>()) {

                // 外部库引用

                for (const TString &library_name : program_set_file->libraries_) {
                    translateUnitPtr->libraries_list_.insert(library_name.string_);
                }

                // 程序集

                ProgSetDeclPtr prog_set_decl = program_set_file->program_set_declares_;
                translateUnitPtr->program_sets_[prog_set_decl->name_.string_] = prog_set_decl;

                // 函数定义

                bool success = MergeMap(prog_set_decl->function_decls_, translateUnitPtr->function_decls_);
                if (!success) { return false; }

                success = MergeMap(prog_set_decl->function_decls_, translateUnitPtr->functor_declares_, [](FunctionDeclPtr v) -> FunctorDeclPtr {
                    return v->as<FunctorDecl>();
                });
                if (!success) { return false; }

            } else if (DllDefineFile *dll_define_file = sfptr->as<DllDefineFile>()) {

                // DLL声明

                bool success = MergeMap(dll_define_file->dll_declares_, translateUnitPtr->dll_declares_);
                if (!success) { return success; }
                success = MergeMap(dll_define_file->dll_declares_, translateUnitPtr->functor_declares_, [](APICommandDeclPtr v) -> FunctorDeclPtr {
                    return v->as<FunctorDecl>();
                });
                if (!success) { return false; }
            }
        }
        return true;
    }

    bool SematicAnalysis::ExplainExternAPINameMangle() {
        assert(translate_unit_);
        for (auto &functor_decl_item : translate_unit_->functor_declares_) {

            FunctorDecl *functor_decl = functor_decl_item.second;

            if (APICommandDecl *api_command_decl = functor_decl->as<APICommandDecl>()) {

                // 检查参数传递方面的修饰

                if (SematicAnalysisNameMangle::IsRequireArgumentPack(api_command_decl)) {
                    api_command_decl->argument_pass_model_ = ArgumentPassModel::kSimpleRTTIPack;
                    SematicAnalysisNameMangle::RemoveArgumentPackRequire(api_command_decl);
                }

                // 检查调用方式方面的修饰

            }
        }
        return true;
    }

    LocalVariableDecl *SematicAnalysis::InsertLocalVariable(StringRef referenceName, ASTContext *astContext, FunctionDecl *parentFunction) {
        size_t idx = 0;
        while (this->analysis_context_.CheckIfNameExist(referenceName)) {
            std::string name = referenceName.str();
            referenceName = astContext->CreateString(name + "_" + std::to_string(idx));
        }
        LocalVariableDecl *implicit_local_vari = CreateNode<LocalVariableDecl>(astContext);
        implicit_local_vari->parent_node_ = parentFunction;
        implicit_local_vari->name_.string_ = referenceName;
        implicit_local_vari->type_decl_ptr_ = this->QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger);
        parentFunction->local_vari_[referenceName] = implicit_local_vari;
        this->analysis_context_.AddNamedSymbol(implicit_local_vari);
        return implicit_local_vari;
    }

    bool SematicAnalysis::SetupFunctorVariableType(FunctorDecl *functorDecl) {

        // 3.1.1. 明确返回值类型

        functorDecl->return_type_ = this->QueryTypeDeclWithName(this->translate_unit_, functorDecl->return_type_name_.string_, &this->analysis_context_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeVoid);
        if (functorDecl->return_type_ == nullptr) {
            assert(false);
            return false;
        }

        // 3.1.2. 明确参数类型

        size_t param_idx = 0;
        for (ParameterDeclPtr parameter_decl : functorDecl->parameters_) {
            parameter_decl->type_decl_ptr_ = this->QueryTypeDeclWithName(this->translate_unit_, parameter_decl->type_name_.string_, &this->analysis_context_);
            this->SetupParameterType(parameter_decl);
            parameter_decl->index_ = param_idx++;
            if (parameter_decl->type_decl_ptr_ == nullptr) {
                assert(false);
                return false;
            }
        }
        return true;
    }

    bool SematicAnalysis::SetupFunctionLocalVariableType(FunctionDecl *functionDecl) {

        // 3.1.3. 明确局部变量类型

        for (auto & item : functionDecl->local_vari_) {
            LocalVariableDeclPtr local_vari = item.second;
            this->SetupLocalVariableType(local_vari);
            if (local_vari->type_decl_ptr_ == nullptr) {
                assert(false);
                return false;
            }
        }
        return true;
    }

    bool SematicAnalysis::CheckStatementsAndExpression(Statement *statement) {
        if (statement == nullptr) {
            return true;
        }
        if (IfStmtPtr if_stmt = statement->as<IfStmt>()) {

            // 检查是否有分支

            if (if_stmt->switches_.empty()) {
                assert(false);
                return false;
            }

            // 检查条件语句的条件表达式是否为扩展布尔类型

            for (auto & branch : if_stmt->switches_) {
                TypeDeclPtr switch_expr_type = this->CheckExpression(branch.first);
                if (TypeAssert::IsExternBooleanType(switch_expr_type) == false) {
                    assert(false);
                    return false;
                }

                if (this->CheckStatementsAndExpression(branch.second) ==  false) {
                    return false;
                }
            }
            if (if_stmt->default_statement_) {
                if (this->CheckStatementsAndExpression(if_stmt->default_statement_) ==  false) {
                    return false;
                }
            }
            return true;

        } else if (StatementBlockPtr statement_list = statement->as<StatementBlock>()) {

            // 直接遍历列表进行检查

            for (StatementPtr stmt : statement_list->statements_) {
                if (this->CheckStatementsAndExpression(stmt) == false) {
                    return false;
                }
            }
            return true;

        } else if (WhileStmtPtr while_stmt = statement->as<WhileStmt>()) {

            // 检查循环条件语句的条件表达式是否为扩展布尔类型

            TypeDeclPtr while_expr_type = this->CheckExpression(while_stmt->condition_);
            if (TypeAssert::IsExternBooleanType(while_expr_type) == false) {
                assert(false);
                return false;
            }

            if (this->CheckStatementsAndExpression(while_stmt->loop_body_) == false) {
                assert(false);
                return false;
            }
            return true;

        } else if (LoopStatementPtr loop_statement = statement->as<LoopStatement>()) {
            return this->CheckLoopStatement(loop_statement);

        } else if (AssignStmtPtr assign_stmt = statement->as<AssignStmt>()) {

            // 检查赋值语句左右子式类型是否匹配或兼容

            TypeDeclPtr lhs_type = this->CheckExpression(assign_stmt->lhs_);
            TypeDeclPtr rhs_type = this->CheckExpression(assign_stmt->rhs_);
            SetupHierarchyReferenceType(assign_stmt->lhs_, IdentifierUsage::kAsLeftValue);
            ErrOr<Expression*> implicit_convert = this->MakeImplicitConvertIfNeccessary(lhs_type, assign_stmt->rhs_);
            if (implicit_convert.HadError()) { return false; }
            assign_stmt->rhs_ = implicit_convert.Value();
            assign_stmt->rhs_->parent_node_ = assign_stmt;
            return true;

        } else if (Expression *expression = statement->as<Expression>()) {
            return this->CheckExpression(expression) != nullptr;

        } else if (LoopControlStmt *loop_control_stmt = statement->as<LoopControlStmt>()) {

            // 检查是否在循环内

            loop_control_stmt->loop_statement_ = ASTUtility::FindSpecifyTypeParent<LoopStatement>(loop_control_stmt);
            return loop_control_stmt->loop_statement_ != nullptr;

        } else if (ReturnStmt *return_stmt = statement->as<ReturnStmt>()) {

            // 检查是否在函数定义内

            FunctionDecl *function_decl = ASTUtility::FindSpecifyTypeParent<FunctionDecl>(return_stmt);
            if (function_decl == nullptr) {
                assert(false);
                return false;
            }

            // 检查返回值表达式类型是否和函数返回值匹配

            // 首先检查是否存在

            if ((function_decl->return_type_ != nullptr) ^ (return_stmt->return_value_ != nullptr)) {
                assert(false);
                return false;
            }

            // 然后检查匹配问题

            if (return_stmt->return_value_) {
                TypeDecl *act_ret_type = this->CheckExpression(return_stmt->return_value_);
                TypeDecl *decl_ret_type = function_decl->return_type_;
                ErrOr<Expression*> implicit_convert = this->MakeImplicitConvertIfNeccessary(decl_ret_type, return_stmt->return_value_);
                if (implicit_convert.NoError()) {
                    return_stmt->return_value_ = implicit_convert.Value();
                    return true;
                } else {
                    assert(false);
                    return false;
                }
            }
            return true;

        } else if (ExitStmt *exit_stmt = statement->as<ExitStmt>()) {
            (void) exit_stmt;

        } else {
            assert(false);
            return false;
        }

        return true;
    }

    bool SematicAnalysis::CheckIfExprTypeIsIntegerClass(Expression *expression) {
        if (expression == nullptr) {
            assert(false);
            return false;
        }
        TypeDecl *expr_type = this->CheckExpression(expression);
        if (expr_type == nullptr) {
            assert(false);
            return false;
        }
        bool is_integer_class = TypeAssert::IsIntegerClass(expr_type);
        if (is_integer_class == false) {
            assert(false);
            return false;
        }
        return true;
    }

    bool SematicAnalysis::CheckLoopStatement(LoopStatement *loopStatement) {
        if (RangeForStmtPtr range_for_stmt = loopStatement->as<RangeForStmt>()) {
            // 检查次数表达式类型是否为整数族
            if (this->CheckIfExprTypeIsIntegerClass(range_for_stmt->range_size_) == false) { assert(false); return false; }
            // 如果循环变量存在则检查变量类型是否为整数族
            if (range_for_stmt->loop_vari_) {
                TypeDecl *loop_vari_type = this->GetHierarchyIdentifierQualifiedType(range_for_stmt->loop_vari_);
                if (TypeAssert::IsIntegerClass(loop_vari_type) == false) {
                    assert(false);
                    return false;
                }
            }
        } else if (ForStmtPtr for_stmt = loopStatement->as<ForStmt>()) {
            // 检查初值表达式、终值表达式、步长表达式类型是否为整数族
            if (this->CheckIfExprTypeIsIntegerClass(for_stmt->start_value_) == false) { assert(false); return false; }
            if (this->CheckIfExprTypeIsIntegerClass(for_stmt->stop_value_) == false) { assert(false); return false; }
            if (this->CheckIfExprTypeIsIntegerClass(for_stmt->step_value_) == false) { assert(false); return false; }
            if (for_stmt->loop_vari_) {
                // 如果循环变量存在则检查变量类型是否为整数族
                TypeDecl *loop_vari_type = this->GetHierarchyIdentifierQualifiedType(for_stmt->loop_vari_);
                if (TypeAssert::IsIntegerClass(loop_vari_type) == false) {
                    assert(false);
                    return false;
                }
            } else {
                // 如果循环变量不存在则隐式创建循环变量
//                FunctionDecl *function_decl = ASTUtility::FindSpecifyTypeParent<FunctionDecl>(loopStatement);
//                assert(function_decl);
//                StringRef reference_name = loopStatement->ast_context_->CreateString("implicit_loop_vari");
//                ASTContext *ast_context = loopStatement->ast_context_;
//                LocalVariableDecl *implicit_lv_decl = this->InsertLocalVariable(reference_name, ast_context, function_decl);
//                for_stmt->loop_vari_ = CreateNode<HierarchyIdentifier>(ast_context);
//                Identifier *implicit_lv = CreateNode<Identifier>(ast_context);
//                implicit_lv->name_.string_ = implicit_lv_decl->name_.string_;
//                for_stmt->loop_vari_->name_components_.push_back(implicit_lv);
//                for_stmt->loop_vari_->qualified_type_ = implicit_lv_decl->type_decl_ptr_;
            }
        } else if (DoWhileStmtPtr do_while_stmt = loopStatement->as<DoWhileStmt>()) {
            // 检查条件表达式类型是否为布尔类型
            TypeDecl *condition_expr_type = this->CheckExpression(do_while_stmt->conditon_);
            bool is_boolean = TypeAssert::IsBoolType(condition_expr_type);
            if (is_boolean == false) {
                assert(false);
                return false;
            }
        } else {
            assert(false);
            return false;
        }
        this->CheckStatementsAndExpression(loopStatement->loop_body_);
        return true;
    }

    bool SematicAnalysis::SetupParameterType(ParameterDecl *parameter) {
        if (this->SetupBaseVariableType(parameter) == false) {
            return false;
        }
        for (const TString &attr : parameter->attributes_) {
            if (attr.string_ == u8"参考" || attr.string_ == u8"传址") {
                parameter->is_reference_ = true;
            } else if (attr.string_ == u8"可空") {
                parameter->is_nullable = true;
            } else if (attr.string_ == u8"数组") {
                parameter->is_array = true;
                assert(parameter->type_decl_ptr_->is<ArrayDecl>() == false);
                ArrayDecl *array_decl = CreateNode<ArrayDecl>(parameter->ast_context_);
                array_decl->dimensions_ = {0};
                array_decl->base_type_ = parameter->type_decl_ptr_;
                parameter->type_decl_ptr_ = array_decl;
            } else {
                assert(false);
                return false;
            }
        }
        return true;
    }

    bool SematicAnalysis::SetupVariableType(VariableDecl *variableDecl) {
        if (this->SetupBaseVariableType(variableDecl) == false) {
            return false;
        }
        auto err_or_dims = Str2Attr::Str2Dimension(variableDecl->dimension_.string_);
        if (err_or_dims.NoError() == false) {
            return false;
        }
        // 如果是数组则还需要使用ArrayDecl再封装一次
        if (!err_or_dims.Value().empty()) {
            ArrayDecl *array_decl = CreateNode<ArrayDecl>(variableDecl->ast_context_);
            array_decl->dimensions_ = err_or_dims.Value();
            array_decl->base_type_ = variableDecl->type_decl_ptr_;
            variableDecl->type_decl_ptr_ = array_decl;
        }
        return true;
    }

    bool SematicAnalysis::SetupGlobalVariableType(GlobalVariableDecl *globalVariableDecl) {
        if (this->SetupVariableType(globalVariableDecl) == false) {
            return false;
        }
        auto err_or_access = Str2Attr::Name2AccessLevel(globalVariableDecl->access_.string_);
        if (err_or_access.NoError() == false) {
            return false;
        }
        globalVariableDecl->access_level_ = err_or_access.Value();
        return true;
    }

    bool SematicAnalysis::SetupMemberVariableType(MemberVariableDecl *memberVariableDecl) {
        if (!this->SetupVariableType(memberVariableDecl)) {
            return false;
        }
        for (const TString &attr : memberVariableDecl->attributes_) {
            if (attr.string_ == u8"引用") {
                memberVariableDecl->is_reference_ = true;
            } else {
                assert(false);
                return false;
            }
        }
        return true;
    }

    bool SematicAnalysis::SetupFileVariableType(FileVariableDecl *fileVariableDecl) {
        return this->SetupVariableType(fileVariableDecl);
    }

    bool SematicAnalysis::SetupLocalVariableType(LocalVariableDecl *localVariableDecl) {
        if (!this->SetupVariableType(localVariableDecl)) {
            return false;
        }
        for (const TString &attr : localVariableDecl->attributes_) {
            if (attr.string_ == u8"静态") {
                localVariableDecl->is_static_ = true;
            } else {
                assert(false);
                return false;
            }
        }
        return true;
    }

    bool SematicAnalysis::SetupBaseVariableType(BaseVariDecl *baseVariDecl) {
        StringRef name = baseVariDecl->type_name_.string_;
        baseVariDecl->type_decl_ptr_ = this->QueryTypeDeclWithName(this->translate_unit_, name, &this->analysis_context_)->as<TypeDecl>();
        if (baseVariDecl->type_decl_ptr_ == nullptr) {
            assert(false);
            return false;
        }
        return true;
    }

    TypeDecl *SematicAnalysis::CheckExpression(Expression *expression) {
        expression->expression_type_ = this->__CheckExpressionImpl__(expression);
        return expression->expression_type_;
    }

    TypeDecl *SematicAnalysis::__CheckExpressionImpl__(Expression *expression) {
        TranslateUnitPtr translateUnit = this->translate_unit_;
        if (HierarchyIdentifier * hierarchy_identifier = expression->as<HierarchyIdentifier>()) {
            SetupHierarchyReferenceType(hierarchy_identifier, IdentifierUsage::kAsRightValue);

            // 可能是直接名称、函数引用、数组组合的序列

            TypeDecl *qualified_type = this->GetHierarchyIdentifierQualifiedType(hierarchy_identifier);
            if (qualified_type == nullptr) {
                assert(false);
                return nullptr;
            }
            return qualified_type;

        } else if (TypeConvert * type_convert = expression->as<TypeConvert>()) {
            TypeDecl *expr_type = this->CheckExpression(type_convert->from_expression_);
            type_convert->source_type_ = expr_type;

            // 检查从源类型到目标类型是否可行

            if (!this->IsAssignableBetweenType(type_convert->target_type_, type_convert->source_type_)) {
                assert(false);
                return nullptr;
            }
            return type_convert->target_type_;

        } else if (FunctionCall * function_call = expression->as<FunctionCall>()) {

            // 检查函数实参是否符合形参定义

            std::vector<ExpressionPtr> &arguments = function_call->arguments_;
            FunctorDecl *functor_decl = ASTUtility::GetFunctionDeclare(function_call);
            if (functor_decl == nullptr) {
                assert(false);
                return nullptr;
            }
            std::vector<ParameterDeclPtr> &parameters = functor_decl->parameters_;
            if (this->CheckIfArgumentMatch(arguments, parameters) == false) {
                assert(false);
                return nullptr;
            }

            // 将函数返回值类型作为返回类型

            assert(functor_decl->return_type_);
            return functor_decl->return_type_;

        } else if (UnaryExpression * unary_expression = expression->as<UnaryExpression>()) {

            // 检查一元表达式是否合法

            if (unary_expression->operator_type_ == UnaryExpression::OperatorType::kOptNone) { return nullptr; }
            TypeDecl *operand_type = this->CheckExpression(unary_expression->operand_value_);
            if (operand_type == nullptr) { return nullptr; }

            // 由于一元运算只支持符号求反，故只检查其数值性

            bool is_numerical = TypeAssert::IsNumerical(operand_type);
            if (is_numerical == false) {
                assert(false);
                return nullptr;
            }

            // 根据运算类型返回类型

            return operand_type;

        } else if (BinaryExpression * binary_expression = expression->as<BinaryExpression>()) {

            // 检查二元表达式是否可结合

            if (binary_expression->operator_type_ == UnaryExpression::OperatorType::kOptNone) { return nullptr; }
            TypeDecl *lhs_operand_type = this->CheckExpression(binary_expression->lhs_);
            TypeDecl *rhs_operand_type = this->CheckExpression(binary_expression->rhs_);
            bool operand_valid = TypeAssert::IsBinaryOperationValid(lhs_operand_type, rhs_operand_type, binary_expression->operator_type_);
            if (operand_valid == false) {
                assert(false);
                return nullptr;
            }

            // 根据运算类型返回类型

            TypeDecl *upgraded_type = this->GetBinaryOperationUpgradedType(lhs_operand_type, rhs_operand_type, binary_expression->operator_type_);
            assert(upgraded_type);

            ErrOr<Expression*> implicit_conv_lhs = this->MakeImplicitConvertIfNeccessary(upgraded_type, binary_expression->lhs_);
            ErrOr<Expression*> implicit_conv_rhs = this->MakeImplicitConvertIfNeccessary(upgraded_type, binary_expression->rhs_);
            if (implicit_conv_lhs.NoError()) { binary_expression->lhs_ = implicit_conv_lhs.Value(); }
            if (implicit_conv_rhs.NoError()) { binary_expression->rhs_ = implicit_conv_rhs.Value(); }

            if (binary_expression->operator_type_ == _OperatorExpression::OperatorType::kOptDiv) {
                return this->QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFloat);
            } else if (binary_expression->operator_type_ == _OperatorExpression::OperatorType::kOptFullDiv) {
                return this->QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger);
            } else if (TypeAssert::IsCompareOperator(binary_expression->operator_type_)) {
                return this->QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool);
            } else {
                return upgraded_type;
            }

        } else if (FuncAddrExpression * func_addr_expression = expression->as<FuncAddrExpression>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFuncPtr);
            assert(type_decl);
            FunctorDecl * functor_decl = ASTUtility::GetFunctionDeclare(func_addr_expression);
            if (functor_decl == nullptr) {
                assert(false);
                return nullptr;
            }
            return type_decl;

        } else if (ResourceRefExpression * resource_ref_expression_ptr = expression->as<ResourceRefExpression>()) {

            // TODO: 需要通过查找常量表来确定类型

            assert(false);
            return nullptr;

        } else if (Value *value = expression->as<Value>()) {
            return this->CheckValue(value);

        } else {
            assert(false);
            return nullptr;
        }
    }

    TypeDecl *SematicAnalysis::CheckValue(Value *value) {
        if (ValueOfDataSet * value_of_data_set = value->as<ValueOfDataSet>()) {

            // 当前版本只允许字节集中的元素全为整数常量

            for (Expression *element : value_of_data_set->elements_) {
                if (ValueOfDecimal *value_of_decimal = element->as<ValueOfDecimal>()) {
                    if (value_of_decimal->type_ != ValueOfDecimal::type::kInt) {
                        assert(false);
                        return nullptr;
                    }
                } else if (ResourceRefExpression *resource_ref_expr = element->as<ResourceRefExpression>()) {

                    // TODO: 检查值

                } else {
                    assert(false);
                    return nullptr;
                }
            }
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet);
            assert(type_decl);
            return type_decl;

        } else if (ValueOfDatetime * value_of_datetime = value->as<ValueOfDatetime>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatetime);
            assert(type_decl);
            return type_decl;

        } else if (ValueOfBool * value_of_bool = value->as<ValueOfBool>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool);
            assert(type_decl);
            return type_decl;

        } else if (ValueOfDecimal * value_of_decimal = value->as<ValueOfDecimal>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger);
            assert(type_decl);
            return type_decl;

        } else if (ValueOfString * value_of_string = value->as<ValueOfString>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString);
            assert(type_decl);
            return type_decl;

        } else {
            assert(false);
            return nullptr;
        }
    }

    ErrOr<Expression *> SematicAnalysis::MakeImplicitConvertIfNeccessary(TypeDecl *targetType, Expression *convertExpression) {
        // 先判断赋值性
        if (!this->IsAssignableBetweenType(targetType, convertExpression->expression_type_)) {
            // 两边类型不可赋值
            return ErrOr<Expression*>::CreateError(1);
        }
        // 再判断是否转换
        if (convertExpression->expression_type_ == targetType) {
            // 类型一致，无需转换
            return MakeNoErrVal(convertExpression);
        } else if (!targetType->is<BuiltinTypeDecl>() || !convertExpression->expression_type_->is<BuiltinTypeDecl>()) {
            // 其中有非内置类型，无法转换
            return MakeNoErrVal(convertExpression);
        } else {
            TypeConvert *type_convert = CreateNode<TypeConvert>(convertExpression->ast_context_);
            type_convert->from_expression_ = convertExpression;
            type_convert->expression_type_ = targetType;
            type_convert->source_type_ = convertExpression->expression_type_;
            type_convert->target_type_ = targetType;
            type_convert->parent_node_ = convertExpression;
            convertExpression->parent_node_ = type_convert;
            return MakeNoErrVal<Expression*>(type_convert);
        }
    }

    TypeDecl *SematicAnalysis::GetBinaryOperationUpgradedType(TypeDecl *lhsType, TypeDecl *rhsType, _OperatorExpression::OperatorType operatorType) {
        // 首先保证可进行二元计算
        bool binary_opt_valid = TypeAssert::IsBinaryOperationValid(lhsType, rhsType, operatorType);
        if (binary_opt_valid == false) {
            assert(false);
            return nullptr;
        }
        // 再计算结果类型
        {
            // 1. 如果是内置类型

            BuiltinTypeDecl *lhs_builtin = lhsType->as<BuiltinTypeDecl>();
            BuiltinTypeDecl *rhs_builtin = rhsType->as<BuiltinTypeDecl>();
            if (lhs_builtin || rhs_builtin) {
                if (lhs_builtin && rhs_builtin) {
                    bool lhs_numerical = TypeAssert::IsNumerical(lhs_builtin);
                    bool rhs_numerical = TypeAssert::IsNumerical(rhs_builtin);
                    if (lhs_numerical && rhs_numerical) {

                        // 1.1. 都有数值性

                        BuiltinTypeDecl::EnumOfBuiltinType upgrade_type = TypeAssert::ResultOfTypeUpgrade(lhs_builtin->built_in_type_, rhs_builtin->built_in_type_);
                        return this->QueryBuiltinTypeWithEnum(this->translate_unit_, upgrade_type);

                    } else if (!lhs_numerical && !rhs_numerical) {

                        // 1.2. 都无数值性

                        if (lhs_builtin == rhs_builtin) {
                            if (lhs_builtin->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool) {
                                return lhs_builtin;

                            } else if (lhs_builtin->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString) {

                                return lhs_builtin;

                            } else if (lhs_builtin->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet) {

                                return lhs_builtin;

                            } else if (lhs_builtin->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatetime) {

                                assert(false);
                                return nullptr;

                            } else if (lhs_builtin->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFuncPtr) {

                                assert(false);
                                return nullptr;

                            } else {
                                assert(false);
                                return nullptr;

                            }
                        } else {
                            assert(false);
                            return nullptr;

                        }
                    } else {

                        // 其中一个有数值性

                        assert(false);
                        return nullptr;
                    }
                } else {

                    // 只有一个是内置类型是无法计算的

                    assert(false);
                    return nullptr;
                }
            }
        }
        {
            // 2. 非内置类型
            assert(false);
            return nullptr;
        }
    }

    bool SematicAnalysis::CheckIfArgumentMatch(std::vector<ExpressionPtr> &arguments, const std::vector<ParameterDeclPtr> &parameters) {

        // 检查所有实参表达式

        for (Expression *argument : arguments) {
            this->CheckExpression(argument);
        }

        // 1. 获取形参有效个数

        // 1.1. 获取个数

        size_t argu_count = arguments.size();
        size_t param_count = parameters.size();

        // 1.2. 检查是否有不定参数

        bool dynamic_params = false;
        if (param_count > 0 && parameters.back()->name_.string_ == u8"...") {
            param_count -= 1;
            dynamic_params = true;
        }

        // 2. 根据形参有效个数用空指针扩展实参

        while (argu_count < param_count) {
            arguments.push_back(nullptr);
            argu_count++;
        }

        // 3. 如果形参长度不定则截取实参前N个进行计算

        if (dynamic_params) {
            argu_count = param_count;
        }

        // 4. 检查形参和实参个数是否匹配

        if (argu_count != param_count) {
            assert(false);
            return false;
        }

        // 5. 针对每个实参/形参对

        for (size_t idx = 0; idx < argu_count; idx++) {

            if (arguments[idx] == nullptr) {

                // 5.1. 如果实参为空指针

                // 5.1.1. 检查形参可空属性

                if (parameters[idx]->is_nullable == false) {
                    assert(false);
                    return false;
                } else {
                    continue;
                }

            }
            /*else*/ if (parameters[idx]->is_array && arguments[idx] != nullptr) {

                // 5.2. 如果形参数组属性为真，则实参必须为左值或左值引用（参考形参）数组变量，且元素类型严格一致
                // 数组参数只能以引用方式传递

                parameters[idx]->is_reference_ = true;
                if (TypeAssert::ExpressionIsLValue(arguments[idx]) == false) {
                    assert(false);
                    return false;
                }

                // 检查数组的元素类型是否匹配

                if (HierarchyIdentifier *hierarchy_identifier = arguments[idx]->as<HierarchyIdentifier>()) {
                    TypeDecl *argu_type = this->GetHierarchyIdentifierQualifiedType(hierarchy_identifier);
                    if (argu_type->is<ArrayDecl>()) {
                        TypeDecl *param_arr_element_type = this->GetIndexableTypeElement(parameters[idx]->type_decl_ptr_);
                        TypeDecl *argu_arr_element_type = this->GetIndexableTypeElement(argu_type);
                        if (param_arr_element_type != argu_arr_element_type) {
                            assert(false);
                            return false;
                        }
                    } else {
                        assert(false);
                        return false;
                    }
                } else {
                    assert(false);
                    return false;
                }

            }
            /*else*/ if (parameters[idx]->is_reference_ && arguments[idx] != nullptr) {

                // 5.3. 如果形参参考属性为真，则实参必须为左值或左值引用（参考形参），并且变量类型严格一致

                if (TypeAssert::ExpressionIsLValue(arguments[idx]) == false) {
                    assert(false);
                    return false;
                }
                if (HierarchyIdentifier *hierarchy_identifier = arguments[idx]->as<HierarchyIdentifier>()) {
                    TypeDecl *argu_type = this->GetHierarchyIdentifierQualifiedType(hierarchy_identifier);
                    SetupHierarchyReferenceType(hierarchy_identifier, IdentifierUsage::kAsLeftValue);
                    if (argu_type != parameters[idx]->type_decl_ptr_) {
                        assert(false);
                        return false;
                    }
                } else {
                    assert(false);
                    return false;
                }

            }
            /*else*/ if (arguments[idx] != nullptr) {

                // 5.4. 如果形参不具备上述属性
                TypeDecl *argu_type = arguments[idx]->expression_type_;
                assert(argu_type);
                TypeDecl *param_type = parameters[idx]->type_decl_ptr_;
                ErrOr<Expression*> implicit_convert = this->MakeImplicitConvertIfNeccessary(param_type, arguments[idx]);
                if (implicit_convert.NoError()) {
                    arguments[idx] = implicit_convert.Value();

                } else {
                    assert(false);
                    return false;
                }
            }
        }
        return true;
    }

    bool CheckFullReturn(Statement *stmt, bool need_return) {
        /*
         * def check_full_ret(stmts,need_return):
         *     for each stmt in stmts:
         *         if stmt is ASSIGN then continue.
         *         if stmt is EXPRESSION then continue.
         *         if stmt is LOOP then continue.
         *         if stmt is RETURN then return true.
         *         if stmt is EXIT then return true.
         *         if stmt is BRANCHES then:
         *             ok = true.
         *             for each branch in BRANCHES:
         *                 ok &= check_full_ret(branch.stmts).
         *             ok &= (BRANCHES has default) && check_full_ret(default).
         *             if ok == true then return true.
         *     return !need_return.
         */
        std::vector<Statement*> stmts;
        if (StatementBlock *statement_block = stmt->as<StatementBlock>()) {
            stmts = statement_block->statements_;
        } else {
            stmts = { stmt };
        }
        for (Statement *stmt : stmts) {
            if (stmt->is<AssignStmt>())         { continue; }
            else if (stmt->is<Expression>())    { continue; }
            else if (stmt->is<LoopStatement>()) { continue; }
            else if (stmt->is<ReturnStmt>())    { return true; }
            else if (stmt->is<ExitStmt>())      { return true; }
            else if (IfStmt *if_stmt = stmt->as<IfStmt>()) {
                bool ok = true;
                for (auto & branch : if_stmt->switches_) {
                    ok &= CheckFullReturn(branch.second, need_return);
                }
                ok &= (if_stmt->default_statement_ != nullptr) && (CheckFullReturn(if_stmt->default_statement_, need_return));
                if (ok) { return true; }
            }
            return !need_return;
        }
        return !need_return;
    }

    bool SematicAnalysis::CheckAllBranchesReturnCorrectly(FunctionDecl *functionDecl) {
        if (!CheckFullReturn(functionDecl->statement_list_, !TypeAssert::IsVoidType(functionDecl->return_type_))) {
            assert(false);
            return false;
        } else {
            return true;
        }
    }

}
