//
// Created by Administrator on 2020/6/11.
//

#include <filesystem>

#include "DebugInfoMgr.h"

namespace rexlang {

    DebugInfoMgr::DebugInfoMgr(llvm::IRBuilder<> &IRBuilder, llvm::DIBuilder &DIBuilder)
            : TheIRBuilder(IRBuilder), TheDIBuilder(DIBuilder) {
    }

    int DebugInfoMgr::OnEmitBegin(Node *astNode) {
        if (ShouldBeGenerateDI(astNode)) {
            llvm::DebugLoc debug_loc = GetDebugLocation(astNode);
            TheIRBuilder.SetCurrentDebugLocation(debug_loc);
            DebugLocateStack.push(debug_loc);
        }
        return 0;
    }

    int DebugInfoMgr::OnEmitEnd(Node *astNode) {
        if (ShouldBeGenerateDI(astNode)) {
            DebugLocateStack.pop();
            if (!DebugLocateStack.empty()) {
                llvm::DebugLoc debug_loc = DebugLocateStack.top();
                TheIRBuilder.SetCurrentDebugLocation(debug_loc);
            }
        }
        return 0;
    }

    llvm::DebugLoc DebugInfoMgr::GetDebugLocation(Node *astNode) {
        llvm::DIScope *scope;
        if (LexicalBlocks.empty()) {
//            scope = GetOrCreateDICompileUnit(astNode);
            return llvm::DebugLoc();
        } else {
            scope = LexicalBlocks.back();
        }
        size_t line = astNode->ast_context_->getLineFromLocate(astNode->location_start_);
        size_t column = astNode->ast_context_->getColumnFromLocate(astNode->location_start_);
        llvm::DebugLoc debug_loc = llvm::DebugLoc::get(line, column, scope);
        return debug_loc;
    }

    bool DebugInfoMgr::ShouldBeGenerateDI(Node *astNode) {
        // 判定是否生成调试信息的标准就是看这个节点是否在Subprogram或者Function中
        if (dynamic_cast<Statement*>(astNode)) {
            return true;
        } else if (dynamic_cast<FunctionDecl*>(astNode)) {
            return true;
        } else if (dynamic_cast<FunctorDecl*>(astNode)) {
            return true;
        } else {
            return false;
        }
    }

    llvm::DICompileUnit *DebugInfoMgr::GetOrCreateDICompileUnit(const Node *node) {
        if (node) {
            const StringRef &file_path = node->ast_context_->getFileFromLocate(node->location_start_);
            return GetOrCreateDICompileUnit(file_path.str());
        } else {
            return nullptr;
        }
    }

    llvm::DICompileUnit *DebugInfoMgr::GetOrCreateDICompileUnit(const std::string &FilePath) {
        std::filesystem::path dir(FilePath);
        std::string filename;
        std::string directory;
        if (!dir.has_filename()) {
            assert(false);
            return nullptr;
        }
        filename = dir.filename().string();
        directory = dir.has_parent_path() ? dir.parent_path().string() : ".";

        std::filesystem::path abs_dir = std::filesystem::absolute(dir);

        llvm::DICompileUnit *cu = nullptr;
        auto found_di_cu = TheDICUMap.find(abs_dir.string());
        if (found_di_cu != TheDICUMap.end()) {
            return found_di_cu->second;
        }

        // 一个DIBuilder实例只能创建一个编译单元
        if (TheDICUMap.empty()) {
            cu = TheDIBuilder.createCompileUnit(
                    llvm::dwarf::DW_LANG_C,
                    TheDIBuilder.createFile(filename, directory),
                    "RexLang Compiler",
                    0,
                    "",
                    0
            );
            TheDICUMap[abs_dir.string()] = cu;
        } else {
            cu = TheDICUMap.begin()->second;
        }

        return cu;
    }


    void DebugInfoMgr::PushLexicalScope(llvm::DIScope *DIScope) {
        LexicalBlocks.push_back(DIScope);
    }

    void DebugInfoMgr::PopLexicalScope() {
        if (!LexicalBlocks.empty()) {
            LexicalBlocks.pop_back();
        }
    }

    llvm::DISubprogram *DebugInfoMgr::CreateFunctionDI(FunctorDecl *functor, llvm::Function *func_ir) {
        size_t func_loc = functor->location_start_;
        std::filesystem::path file_name(functor->ast_context_->getFileFromLocate(func_loc).str());
        unsigned file_line = functor->ast_context_->GetLineNumber(functor->location_start_);
        // TODO:有必要的话需要执行 Name Mangle
        StringRef mangled_name = functor->name_.string_;

        llvm::DIFile *Unit = TheDIBuilder.createFile(
                file_name.filename().string(),
                file_name.parent_path().string()
        );
        llvm::DISubprogram *FuncDI = TheDIBuilder.createFunction(
                GetOrCreateDICompileUnit(file_name.string().c_str()),
                functor->name_.string_.str(),
                mangled_name.str(),
                Unit,
                file_line,
                TheDIBuilder.createSubroutineType(llvm::DITypeRefArray()),
                file_line,
                llvm::DINode::FlagPrototyped,
                llvm::DISubprogram::DISPFlags::SPFlagDefinition
        );
        return FuncDI;
    }

}
