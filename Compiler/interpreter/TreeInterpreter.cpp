//
// Created by rex on 2020/2/7.
//

#include <assert.h>

#include "TreeInterpreter.h"

namespace opene {
    bool RuntimeContext::AddVariable(VariableDecl *variableDecl) {
        return false;
    }

    bool RuntimeContext::PushStack(TranslateUnit *translateUnit) {
        return false;
    }

    bool RuntimeContext::PushStack(FunctionDecl *functionDecl) {
        for (ParameterDecl *parameter_decl : functionDecl->parameters_) {

        }
    }

    bool RuntimeContext::PopStack() {
        if (!this->dyn_symbol_table_.empty()) {
            this->dyn_symbol_table_.pop_back();
            return true;
        } else {
            assert(false);
            return false;
        }
    }

    TIVariable * RuntimeContext::QueryVariableObjectFromDynSymbolTable(VariableDecl *variableDecl) {
        for (auto layer_iter = this->dyn_symbol_table_.rbegin(); layer_iter != this->dyn_symbol_table_.rend(); layer_iter++) {
            for (auto & object_item : *layer_iter) {
                if (object_item.first == variableDecl) {
                    return object_item.second;
                }
            }
        }
        assert(false);
        return nullptr;
    }

    bool TreeInterpreter::LoadAST(TranslateUnit *translateUnit) {
        if (this->translate_unit_) {
            assert(false);
            return false;
        } else {
            this->translate_unit_ = translateUnit;
            this->LoadGlobalVariable();
            this->LoadFileVariable();
            return true;
        }
    }

    bool TreeInterpreter::LoadGlobalVariable() {
        return false;
    }

    bool TreeInterpreter::LoadFileVariable() {
        return false;
    }

    bool TreeInterpreter::LoadLocalVariable() {
        return false;
    }

    bool TreeInterpreter::UnloadAST() {
        this->translate_unit_ = nullptr;
        return true;
    }

    bool TreeInterpreter::Run() {
        if (!this->translate_unit_) {
            assert(false);
            return false;
        }
        StringRef entry_name(u8"_启动子程序");
        auto found = this->translate_unit_->function_decls_.find(entry_name);
        FunctorDecl *entry_function = nullptr;
        if (found != this->translate_unit_->function_decls_.end()) {
            entry_function = *found;
        } else {
            assert(false);
            return false;
        }
        TIValue entry_return_value = this->CallFunction(entry_function, {});
        return true;
    }
}