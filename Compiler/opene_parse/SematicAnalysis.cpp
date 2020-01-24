//
// Created by rex on 2020/1/23.
//

#include "SematicAnalysis.h"

#include "NodeDecl.h"
#include "Str2Attr.h"

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
                bool success = MergeMap(program_set_file->libraries_, translateUnitPtr->libraries_list_, [](const TString &tString) -> StringRef {
                    return tString.string_;
                });
                if (!success) { return false; }
                // 函数定义
                ProgSetDeclPtr prog_set_decl = program_set_file->program_set_declares_;
                success = MergeMap(prog_set_decl->function_decls_, translateUnitPtr->function_decls_, [prog_set_decl](const SubProgDeclPtr func_ptr) -> SubProgDeclPtr {
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
        // 2. 针对数据结构定义、类模块定义
        // 2.1. 明确成员的类型指针
        this->SetupAllStructMemberType();
        // 2.2. 明确全局变量、程序集变量类型指针
        this->SetupAllVariableType();
        // 3. 针对每一个程序集中的每一个函数开始遍历
        // 3.1. 明确每一个参数、返回值和局部变量的类型指针
        // 3.2. 检查每一条语句构造是否合法
        // 3.3. 检查每一个表达式运算是否合法
        // 3.4. 明确每一个名称引用的定义
        // 3.5. 展开常量资源引用
        return true;
    }

    bool SematicAnalysis::CreateBuiltinType() {
        BuiltinTypeDecl::EnumOfBuiltinType types[] = {
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeChar,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTFloat,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTBool,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTString,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTDataSet,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTShort,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTLong,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTDatatime,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTFuncPtr,
                BuiltinTypeDecl::EnumOfBuiltinType::kBTDouble,
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
                    member_item.second->type_decl_ptr_ = this->QueryTypeDeclWithName(member_item.second->type_.string_);
                    if (member_item.second->type_decl_ptr_ == nullptr) {
                        assert(false);
                        return false;
                    }
                }
            }
        }
        return true;
    }

    TypeDecl *SematicAnalysis::QueryTypeDeclWithName(const StringRef &name) {
        auto found = this->translate_unit_->global_type_.find(name);
        if (found != this->translate_unit_->global_type_.end()) {
            return found->second;
        } else {
            return nullptr;
        }
    }

    bool SematicAnalysis::SetupAllVariableType() {
        // 1. 全局变量
        // 2. 程序集变量
        // 3. 局部变量
    }
}
