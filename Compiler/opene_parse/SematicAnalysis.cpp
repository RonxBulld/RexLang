//
// Created by rex on 2020/1/23.
//

#include "SematicAnalysis.h"

#include "NodeDecl.h"
#include "Str2Attr.h"
#include "TypeAssert.h"

namespace opene {
    template <typename SrcMapContainer, typename TgtMapContainer, typename Pred>
    bool MergeMap(const SrcMapContainer &sourceMap, TgtMapContainer &targetMap, Pred && pred) {
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
    bool MergeMap(const MapContainer &sourceMap, MapContainer &targetMap) {
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
        // 1.1. 创建内置数据类型并写入索引表
        this->CreateBuiltinType();
        // 1.2. 合并全局变量、数据结构、外部库引用、函数定义、DLL声明索引表
        this->MergeGlobal();
        // 2. 针对数据结构定义、类模块定义
        // 2.1. 明确成员的类型指针
        this->SetupAllStructMemberType();
        // 2.2. 明确全局变量、程序集变量类型指针
        this->SetupGlobalAndFileStaticVariableType();
        // 3. 针对每一个程序集中的每一个函数开始遍历
        for (auto & func_item : this->translate_unit_->function_decls_) {
            this->current_function_ = func_item.second;
            this->current_program_file_ = this->current_function_->super_set_;
            // 3.1. 明确每一个参数、返回值和局部变量的类型指针
            if (this->SetupFunctionVariableType(func_item.second) == false) {
                return false;
            }
            // 3.2. 检查每一条语句构造和表达式运算是否合法
            if (this->CheckStatementsAndExpression(func_item.second->statement_list_) == false) {
                return false;
            }
            this->current_function_ = nullptr;
        }
        // 3.3. 明确每一个名称引用的定义
        // 3.4. 展开常量资源引用
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

    TypeDecl *SematicAnalysis::QueryTypeDeclWithName(const StringRef &name) {
        auto found = this->translate_unit_->global_type_.find(name);
        if (found != this->translate_unit_->global_type_.end()) {
            return found->second;
        } else {
            assert(false);
            return nullptr;
        }
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
                bool success = MergeMap(data_structure_file_ptr->structure_decl_map_, translateUnitPtr->global_type_, [](const StructureDeclPtr v) -> TypeDeclPtr {
                    return const_cast<TypeDecl *>(v->as<TypeDecl>());
                });
                if (!success) { return false; }
            } else if (ProgramSetFile *program_set_file = sfptr->as<ProgramSetFile>()) {
                // 外部库引用
                for (const TString &library_name : program_set_file->libraries_) {
                    translateUnitPtr->libraries_list_.insert(library_name.string_);
                }
                // 函数定义
                ProgSetDeclPtr prog_set_decl = program_set_file->program_set_declares_;
                bool success = MergeMap(prog_set_decl->function_decls_, translateUnitPtr->function_decls_, [prog_set_decl](const SubProgDeclPtr func_ptr) -> SubProgDeclPtr {
                    SubProgDeclPtr p = const_cast<SubProgDeclPtr>(func_ptr);
                    p->super_set_ = prog_set_decl;
                    return p;
                });
                if (!success) { return false; }
            } else if (DllDefineFile *dll_define_file = sfptr->as<DllDefineFile>()) {
                // DLL声明
                bool success = MergeMap(dll_define_file->dll_declares_, translateUnitPtr->dll_declares_);
                if (!success) { return success; }
            }
        }
        return true;
    }

    bool SematicAnalysis::SetupFunctionVariableType(SubProgDecl *function) {
        // 3.1.1. 明确返回值类型
        function->return_type_ = this->QueryTypeDeclWithName(function->type_.string_);
        if (function->return_type_ == nullptr) {
            assert(false);
            return false;
        }
        // 3.1.2. 明确参数类型
        for (ParameterDeclPtr parameter_decl : function->parameters_) {
            parameter_decl->type_decl_ptr_ = this->QueryTypeDeclWithName(parameter_decl->type_name_.string_);
            this->SetupParameterType(parameter_decl);
            if (parameter_decl->type_decl_ptr_ == nullptr) {
                assert(false);
                return false;
            }
        }
        // 3.1.3. 明确局部变量类型
        for (auto & item : function->local_vari_) {
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
            return TypeAssert::IsAssignable(lhs_type, rhs_type);
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
        variableDecl->dimensions_ = err_or_dims.Value();
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
        if ((baseVariDecl->type_decl_ptr_ = this->QueryTypeDeclWithName(baseVariDecl->type_name_.string_)) == nullptr) {
            return false;
        }
        return true;
    }

    TypeDecl *SematicAnalysis::CheckExpression(Expression *expression) {
        TranslateUnitPtr translateUnit = this->translate_unit_;
        ASTContext * astContext = translateUnit->ast_context_;
        if (HierarchyIdentifierPtr hierarchy_identifier = expression->as<HierarchyIdentifier>()) {
            // 判断是否有效
            assert(hierarchy_identifier->name_components_.size() > 0);
            BaseVariDecl *vari_decl = nullptr;
            // 找起点
            NameComponentPtr base_component = hierarchy_identifier->name_components_.front();
            ErrOr<StringRef> base_name = this->GetNameComponentQualifiedName(base_component);
            if (base_name.NoError() == false) { return nullptr; }
            BaseVariDecl *base_vari_decl = this->FindVariableWithNameInHierarchy(base_name.Value());
            if (base_vari_decl == nullptr) { return nullptr; }
            // 找递进
            for (size_t idx = 1; idx < hierarchy_identifier->name_components_.size(); idx++) {
                base_name = this->GetNameComponentQualifiedName(hierarchy_identifier->name_components_[idx]);
                if (base_name.NoError() == false) { return nullptr; }
                base_vari_decl = this->FindVariableWithNameInStructureType(base_vari_decl->type_decl_ptr_, base_name.Value());
                assert(base_vari_decl);
            }
            return base_vari_decl->type_decl_ptr_;

        } else if (NameComponentPtr name_component = expression->as<NameComponent>()) {
            // 不应当单独判断NameComponent，因为缺失上下文语境会导致大部分情况无法进行判定
            assert(false);
            return nullptr;

        } else if (FunctionCallPtr function_call = expression->as<FunctionCall>()) {
            // TODO: 检查函数实参是否符合形参定义
            // TODO: 将函数返回值类型作为返回类型
        } else if (UnaryExpressionPtr unary_expression = expression->as<UnaryExpression>()) {
            // TODO: 检查一元表达式是否合法
            // TODO: 根据运算类型返回类型
        } else if (BinaryExpressionPtr binary_expression = expression->as<BinaryExpression>()) {
            // TODO: 检查二元表达式是否可结合
            // TODO: 根据运算类型返回类型
        } else if (ValueOfDataSetPtr value_of_data_set = expression->as<ValueOfDataSet>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet);
            assert(type_decl);
            return type_decl;
        } else if (ValueOfDatetimePtr value_of_datetime = expression->as<ValueOfDatetime>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatetime);
            assert(type_decl);
            return type_decl;
        } else if (FuncAddrExpressionPtr func_addr_expression = expression->as<FuncAddrExpression>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFuncPtr);
            assert(type_decl);
            return type_decl;
        } else if (ResourceRefExpressionPtr resource_ref_expression_ptr = expression->as<ResourceRefExpression>()) {
            // TODO: 需要通过查找常量表来确定类型
        } else if (ValueOfBoolPtr value_of_bool = expression->as<ValueOfBool>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool);
            assert(type_decl);
            return type_decl;
        } else if (ValueOfDecimalPtr value_of_decimal = expression->as<ValueOfDecimal>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger);
            assert(type_decl);
            return type_decl;
        } else if (ValueOfStringPtr value_of_string = expression->as<ValueOfString>()) {
            TypeDecl *type_decl = this->QueryBuiltinTypeWithEnum(BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString);
            assert(type_decl);
            return type_decl;
        } else {
            assert(false);
            return nullptr;
        }
    }

    TypeDecl *SematicAnalysis::QueryBuiltinTypeWithEnum(BuiltinTypeDecl::EnumOfBuiltinType type_enum) {
        TranslateUnitPtr translateUnit = this->translate_unit_;
        ASTContext * astContext = translateUnit->ast_context_;
        StringRef && type_name = astContext->CreateString(Str2Attr::BuiltinType2Name(type_enum).Value());
        TypeDecl * type_decl = this->QueryTypeDeclWithName(type_name);
        assert(type_decl);
        return type_decl;
    }

    BaseVariDecl *SematicAnalysis::FindVariableWithNameInHierarchy(const StringRef &variable_name) {
        // 1. 查找局部变量和参数
        if (SubProgDecl *function = this->current_function_) {
            {
                auto found = function->local_vari_.find(variable_name);
                if (found != function->local_vari_.end()) {
                    return found->second;
                }
            }
            {
                for (ParameterDeclPtr param_item : function->parameters_) {
                    if (param_item->name_.string_ == variable_name) {
                        return param_item;
                    }
                }
            }
        }
        // 2. 查找文件变量
        if (ProgSetDecl *prog_set_file = this->current_program_file_) {
            auto found = prog_set_file->file_static_variables_.find(variable_name);
            if (found != prog_set_file->file_static_variables_.end()) {
                return found->second;
            }
        }
        // 3. 查找全局变量
        {
            auto found = this->translate_unit_->global_variables_.find(variable_name);
            if (found != this->translate_unit_->global_variables_.end()) {
                return found->second;
            }
        }
        assert(false);
        return nullptr;
    }

    NameComponent *SematicAnalysis::GetNameComponentQualifiedBase(NameComponent *nameComponent) {
        if (nameComponent->name_.string_.empty() == false && nameComponent->base_ == nullptr && nameComponent->index_ == nullptr) {
            return nameComponent;
        } else if (nameComponent->name_.string_.empty() == true && nameComponent->base_ != nullptr && nameComponent->index_) {
            return this->GetNameComponentQualifiedBase(nameComponent->base_);
        } else {
            assert(false);
            return nullptr;
        }
    }

    ErrOr<StringRef> SematicAnalysis::GetNameComponentQualifiedName(NameComponent *nameComponent) {
        NameComponent *base_name_component = this->GetNameComponentQualifiedBase(nameComponent);
        if (base_name_component) {
            return MakeNoErrVal<StringRef>(base_name_component->name_.string_);
        } else {
            assert(false);
            return ErrOr<StringRef>::CreateError(1);
        }
    }
}
