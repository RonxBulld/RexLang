//
// Created by rex on 2020/2/3.
//

#include <cassert>

#include "SematicAnalysisContext.h"

namespace opene {

    bool SematicAnalysisContext::AddNamedSymbol(TagDecl *tagDecl) {
        if (this->dyn_symbol_table_.empty()) {
            assert(false);
            return false;
        }

        for (auto &tag_decl_item : this->dyn_symbol_table_.back()) {
            if (tag_decl_item.first.string_ == tagDecl->name_.string_) {
                assert(false);
                return false;
            }
        }

        this->dyn_symbol_table_.back().insert(std::pair(tagDecl->name_, tagDecl));
        return true;
    }

    void SematicAnalysisContext::PushScope(TranslateUnit *translateUnit) {
        this->dyn_symbol_table_.push_back({});
        // 加载全局变量
        for (auto &global_vari_item : translateUnit->global_variables_) {
            this->AddNamedSymbol(global_vari_item.second);
        }
        // 加载数据结构
        for (auto &structure_item : translateUnit->global_type_) {
            this->AddNamedSymbol(structure_item.second);
        }
        // 加载可调用对象定义
        for (auto &functor_item : translateUnit->functor_declares_) {
            this->AddNamedSymbol(functor_item.second);
        }
    }

    void SematicAnalysisContext::PushScope(ProgSetDecl *progSetDecl) {
        this->dyn_symbol_table_.push_back({});
        // 加载文件变量
        for (auto &file_vari_item : progSetDecl->file_static_variables_) {
            this->AddNamedSymbol(file_vari_item.second);
        }
        // 加载函数定义 这里再次加载函数定义为了提高当前文件作用域符号的优先级
        for (auto &function_item : progSetDecl->function_decls_) {
            this->AddNamedSymbol(function_item.second);
        }

    }

    void SematicAnalysisContext::PushScope(FunctionDecl *functionDecl) {
        this->dyn_symbol_table_.push_back({});
        // 加载参数
        for (auto &parameter_item : functionDecl->parameters_) {
            this->AddNamedSymbol(parameter_item);
        }
        // 加载局部变量
        for (auto &local_vari_item : functionDecl->local_vari_) {
            this->AddNamedSymbol(local_vari_item.second);
        }

    }

    void SematicAnalysisContext::PopScope() {
        if (!this->dyn_symbol_table_.empty()) {
            this->dyn_symbol_table_.pop_back();
        }
    }

    TagDecl *SematicAnalysisContext::QueryTagDeclFromDynSymbolTableWithName(const StringRef &name) {
        for (auto &tag_decl_layer : this->dyn_symbol_table_) {
            for (auto &decl_item : tag_decl_layer) {
                if (decl_item.first.string_ == name) {
                    return decl_item.second;
                }
            }
        }
        assert(false);
        return nullptr;
    }

}
