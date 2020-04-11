//
// Created by rex on 2020/2/7.
//

#include <assert.h>

#include "TreeInterpreter.h"

namespace rexlang {
    bool RuntimeContext::AddVariable(BaseVariDecl *variableDecl) {
        // TODO:
        return false;
    }

    bool RuntimeContext::PushStack(TranslateUnit *translateUnit) {
        // TODO:
        return false;
    }

    bool RuntimeContext::PushStack(FunctionDecl *functionDecl) {
        for (ParameterDecl *parameter_decl : functionDecl->parameters_) {
            // TODO:
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

    TIVariable * RuntimeContext::QueryVariableObjectFromDynSymbolTable(BaseVariDecl *variableDecl) {
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
            this->runtime_context_.PushStack(translateUnit);
            return true;
        }
    }

    bool TreeInterpreter::LoadFunctionFragment(FunctionDecl *functionDecl) {
        this->runtime_context_.PushStack(functionDecl);
        this->runtime_context_.SetExecutePtr(functionDecl->statement_list_);
        return true;
    }

    TIValue TreeInterpreter::CallFunction(FunctorDecl *functorDecl, std::vector<TIValue*> arguments) {
        if (FunctionDecl *function_decl = functorDecl->as<FunctionDecl>()) {
            this->LoadFunctionFragment(function_decl);
            // 设置参数值
            for (size_t idx = 0; idx < function_decl->parameters_.size(); idx++) {
                ParameterDecl *parameter_decl = function_decl->parameters_[idx];
                StringRef param_name = parameter_decl->name_.string_;
                if (param_name == u8"...") {
                    assert(false);
                } else {
                    this->runtime_context_.SetValue(parameter_decl, *arguments[idx]);
                }
            }
            // 执行语句
            this->ExecuteCore();
            // 返回值
            return this->runtime_context_.GetLatestReturnValue();

        } else if (DllCommandDecl *dll_command_decl = functorDecl->as<DllCommandDecl>()) {
            // TODO:
            assert(false);
            return TIValue();
        } else {
            assert(false);
            return TIValue();
        }
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

    bool TreeInterpreter::ExecStatement(Statement *statement) {
        if (AssignStmt *assign_stmt = statement->as<AssignStmt>()) {
            return this->ExecAssign(assign_stmt);
        } else if (ControlStmt *control_stmt = statement->as<ControlStmt>()) {
            return this->ExecControl(control_stmt);
        } else if (IfStmt *if_stmt = statement->as<IfStmt>()) {
            return this->ExecIf(if_stmt);
        } else if (LoopStatement *loop_statement = statement->as<LoopStatement>()) {
            return this->ExecLoop(loop_statement);
        } else if (StatementBlock *statement_block = statement->as<StatementBlock>()) {
            return this->ExecStmtBlock(statement_block);
        } else {
            assert(false);
            return false;
        }
    }

    bool TreeInterpreter::ExecuteCore() {
        while (Statement *current_statement = this->runtime_context_.GetExecutePtr()) {
            this->runtime_context_.SetExecutePtr(nullptr);
            this->ExecStatement(current_statement);
        }
        return true;
    }

}