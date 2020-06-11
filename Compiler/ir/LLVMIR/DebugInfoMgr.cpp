//
// Created by Administrator on 2020/6/11.
//

#include <filesystem>

#include "DebugInfoMgr.h"

namespace rexlang {

    DebugInfoMgr::DebugInfoMgr(llvm::IRBuilder<> &IRBuilder, llvm::DIBuilder &DIBuilder)
            : TheIRBuilder(IRBuilder), TheDIBuilder(DIBuilder) {
    }

    llvm::DebugLoc DebugInfoMgr::EmitLocation(Node *node) {
        llvm::DIScope *scope;
        if (LexicalBlocks.empty()) {
            scope = GetOrCreateDICompileUnit(node);
        } else {
            scope = LexicalBlocks.back();
        }
        size_t line = node->ast_context_->GetLineFromLocate(node->location_start_);
        size_t column = node->ast_context_->GetColumnFromLocate(node->location_start_);
        llvm::DebugLoc debug_loc = llvm::DebugLoc::get(line, column, scope);
//        TheIRBuilder.SetCurrentDebugLocation(debug_loc);
        return debug_loc;
    }

    llvm::DICompileUnit *DebugInfoMgr::GetOrCreateDICompileUnit(const Node *node) {
        if (node) {
            const StringRef &file_path = node->ast_context_->GetFileFromLocate(node->location_start_);
            return GetOrCreateDICompileUnit(file_path);
        } else {
            return nullptr;
        }
    }

    llvm::DICompileUnit *DebugInfoMgr::GetOrCreateDICompileUnit(const StringRef &FilePath) {
        return GetOrCreateDICompileUnit(FilePath.str());
    }

    llvm::DICompileUnit *DebugInfoMgr::GetOrCreateDICompileUnit(const std::string &FilePath) {
        std::filesystem::path dir(FilePath);
        if (!dir.has_filename()) {
            // TODO:
            assert(false);
            return nullptr;
        }
        std::string filename = dir.filename();
        std::string directory = dir.has_parent_path() ? dir.parent_path() : ".";

        std::filesystem::path abs_dir = std::filesystem::absolute(dir);
        llvm::DICompileUnit *cu = TheDICUMap[abs_dir.string()];
        if (cu) { return cu; }

        cu = TheDIBuilder.createCompileUnit(
                llvm::dwarf::DW_LANG_C,
                TheDIBuilder.createFile(filename, directory),
                "RexLang Compiler",
                0,
                "",
                0
        );
        TheDICUMap[abs_dir.string()] = cu;
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
        std::filesystem::path file_name(functor->ast_context_->GetFileFromLocate(func_loc).str());
        unsigned file_line = functor->ast_context_->GetLineNumber(file_line);
        // TODO:有必要的话需要执行 Name Mangle
        StringRef mangled_name = functor->name_.string_;

        llvm::DIFile *Unit = TheDIBuilder.createFile(
                file_name.filename().c_str(),
                file_name.parent_path().c_str()
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
