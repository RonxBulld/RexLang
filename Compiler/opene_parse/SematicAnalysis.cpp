//
// Created by rex on 2020/1/23.
//

#include "SematicAnalysis.h"

#include "NodeDecl.h"
#include "Str2Attr.h"
#include "TypeAssert.h"
#include "ASTUtility.h"
#include "ASTContext.h"

namespace opene {
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

    template <typename MapContainer, typename ReturnType = std::remove_const_t<typename MapContainer::mapped_type>>
    bool MergeMap(MapContainer &sourceMap, MapContainer &targetMap) {
        return MergeMap(sourceMap, targetMap, [](const typename MapContainer::mapped_type &value) -> ReturnType {
            return const_cast<ReturnType>(value);
        });
    }

    bool SematicAnalysis::Run(TranslateUnit * translateUnitPtr) {

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
        // 4. 针对函数定义
        for (auto & func_item : this->translate_unit_->function_decls_) {
            // 4.1. 明确函数定义局部变量的类型指针
            if (this->SetupFunctionLocalVariableType(func_item.second) == false) {
                return false;
            }
            // 4.2. 检查每一条语句构造和表达式运算是否合法
            if (this->CheckStatementsAndExpression(func_item.second->statement_list_) == false) {
                return false;
            }
        }
        // 4.3. 明确每一个名称引用的定义
        // 4.4. 展开常量资源引用
        return true;
    }

    bool SematicAnalysis::CreateBuiltinType() {
        BuiltinTypeDecl::EnumOfBuiltinType types[] = {
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeChar,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFloat,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeShort,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeLong,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatetime,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFuncPtr,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDouble,
        };
        for (auto & type : types) {
            ErrOr<std::string> type_name = Str2Attr::BuiltinType2Name(type);
            if (type_name.NoError()) {
                TString ts_tname;
                ts_tname.string_ = this->translate_unit_->ast_context_->CreateString(type_name.Value());
                ts_tname.location_ = 0;
                BuiltinTypeDeclPtr builtin_type = CreateNode<BuiltinTypeDecl>(this->translate_unit_->ast_context_);
                builtin_type->name_ = ts_tname;
                builtin_type->built_in_type_ = type;
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
                for (auto & member_item : structure_decl->members_) {
                    this->SetupMemberVariableType(member_item.second);
                    if (member_item.second->type_decl_ptr_ == nullptr) {
                        assert(false);
                        return false;
                    }
                }
            }
        }
        return true;
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
                // 函数定义
                ProgSetDeclPtr prog_set_decl = program_set_file->program_set_declares_;
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
                success = MergeMap(dll_define_file->dll_declares_, translateUnitPtr->functor_declares_, [](DllCommandDeclPtr v) -> FunctorDeclPtr {
                    return v->as<FunctorDecl>();
                });
                if (!success) { return false; }
            }
        }
        return true;
    }

    bool SematicAnalysis::SetupFunctorVariableType(FunctorDecl *functorDecl) {
        // 3.1.1. 明确返回值类型
        functorDecl->return_type_ = ASTUtility::QueryTypeDeclWithName(this->translate_unit_, functorDecl->return_type_name_.string_);
        if (functorDecl->return_type_ == nullptr) {
            assert(false);
            return false;
        }
        // 3.1.2. 明确参数类型
        for (ParameterDeclPtr parameter_decl : functorDecl->parameters_) {
            parameter_decl->type_decl_ptr_ = ASTUtility::QueryTypeDeclWithName(this->translate_unit_, parameter_decl->type_name_.string_);
            this->SetupParameterType(parameter_decl);
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

            return true;
        } else if (StatementListPtr statement_list = statement->as<StatementBlock>()) {
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
        } else if (RangeForStmtPtr range_for_stmt = statement->as<RangeForStmt>()) {
        } else if (ForStmtPtr for_stmt = statement->as<ForStmt>()) {
        } else if (DoWhileStmtPtr do_while_stmt = statement->as<DoWhileStmt>()) {
        } else if (AssignStmtPtr assign_stmt = statement->as<AssignStmt>()) {
            // 检查赋值语句左右子式类型是否匹配或兼容
            TypeDeclPtr lhs_type = this->CheckExpression(assign_stmt->lhs_);
            TypeDeclPtr rhs_type = this->CheckExpression(assign_stmt->rhs_);
            return TypeAssert::IsAssignableBetweenType(lhs_type, rhs_type);
        } else {
            assert(false);
            return false;
        }
        return true;
    }

    bool SematicAnalysis::SetupParameterType(ParameterDecl *parameter) {
        if (this->SetupBaseVariableType(parameter) == false) {
            return false;
        }
        for (const TString &attr : parameter->attributes_) {
            if (attr.string_ == u8"参考") {
                parameter->is_reference = true;
            } else if (attr.string_ == u8"可空") {
                parameter->is_nullable = true;
            } else if (attr.string_ == u8"数组") {
                parameter->is_array = true;
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
        return this->SetupVariableType(memberVariableDecl);
    }

    bool SematicAnalysis::SetupFileVariableType(FileVariableDecl *fileVariableDecl) {
        return this->SetupVariableType(fileVariableDecl);
    }

    bool SematicAnalysis::SetupLocalVariableType(LocalVariableDecl *localVariableDecl) {
        if (this->SetupVariableType(localVariableDecl) == false) {
            return false;
        }
        if (localVariableDecl->attributes_.string_ == u8"静态") {
            localVariableDecl->is_static_ = true;
        } else if (localVariableDecl->attributes_.string_ == u8"") {
            localVariableDecl->is_static_ = false;
        } else {
            assert(false);
            return false;
        }
        return true;
    }

    bool SematicAnalysis::SetupBaseVariableType(BaseVariDecl *baseVariDecl) {
        if ((baseVariDecl->type_decl_ptr_ = ASTUtility::QueryTypeDeclWithName(this->translate_unit_, baseVariDecl->type_name_.string_)) == nullptr) {
            return false;
        }
        return true;
    }

    TypeDecl *SematicAnalysis::CheckExpression(Expression *expression) {
        TranslateUnitPtr translateUnit = this->translate_unit_;
        ASTContext * astContext = translateUnit->ast_context_;
        if (HierarchyIdentifier * hierarchy_identifier = expression->as<HierarchyIdentifier>()) {
            const BaseVariDecl *vari_decl = ASTUtility::FindVariableDeclareInASTWithHierarchyName(hierarchy_identifier);
            assert(vari_decl);
            return vari_decl->type_decl_ptr_;

        } else if (NameComponent * name_component = expression->as<NameComponent>()) {
            // 不应当单独判断NameComponent，因为缺失上下文语境会导致大部分情况无法进行判定
            assert(false);
            return nullptr;

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
            if (unary_expression->operator_type_ == UnaryExpression::OperatorType::kOptNone) { return nullptr; }
            TypeDecl *lhs_operand_type = this->CheckExpression(binary_expression->lhs_);
            TypeDecl *rhs_operand_type = this->CheckExpression(binary_expression->rhs_);
            bool operand_valid = TypeAssert::IsBinaryOperationValid(lhs_operand_type, rhs_operand_type, unary_expression->operator_type_);
            if (operand_valid == false) {
                assert(false);
                return nullptr;
            }
            // 根据运算类型返回类型
            return this->GetBinaryOperationType(lhs_operand_type, rhs_operand_type, unary_expression->operator_type_);

        } else if (ValueOfDataSet * value_of_data_set = expression->as<ValueOfDataSet>()) {
            TypeDecl *type_decl = ASTUtility::QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet);
            assert(type_decl);
            return type_decl;

        } else if (ValueOfDatetime * value_of_datetime = expression->as<ValueOfDatetime>()) {
            TypeDecl *type_decl = ASTUtility::QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatetime);
            assert(type_decl);
            return type_decl;

        } else if (FuncAddrExpression * func_addr_expression = expression->as<FuncAddrExpression>()) {
            TypeDecl *type_decl = ASTUtility::QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFuncPtr);
            assert(type_decl);
            return type_decl;

        } else if (ResourceRefExpression * resource_ref_expression_ptr = expression->as<ResourceRefExpression>()) {
            // TODO: 需要通过查找常量表来确定类型
            assert(false);
            return nullptr;

        } else if (ValueOfBool * value_of_bool = expression->as<ValueOfBool>()) {
            TypeDecl *type_decl = ASTUtility::QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool);
            assert(type_decl);
            return type_decl;

        } else if (ValueOfDecimal * value_of_decimal = expression->as<ValueOfDecimal>()) {
            TypeDecl *type_decl = ASTUtility::QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger);
            assert(type_decl);
            return type_decl;

        } else if (ValueOfString * value_of_string = expression->as<ValueOfString>()) {
            TypeDecl *type_decl = ASTUtility::QueryBuiltinTypeWithEnum(this->translate_unit_, BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString);
            assert(type_decl);
            return type_decl;

        } else {
            assert(false);
            return nullptr;
        }
    }

    TypeDecl *SematicAnalysis::GetBinaryOperationType(TypeDecl *lhsType, TypeDecl *rhsType, _OperatorExpression::OperatorType operatorType) {
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
                        return ASTUtility::QueryBuiltinTypeWithEnum(this->translate_unit_, upgrade_type);
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
}
