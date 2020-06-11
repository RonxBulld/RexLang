//
// Created by Administrator on 2020/6/11.
//

#ifndef REXLANG_DEBUGINFOMGR_H
#define REXLANG_DEBUGINFOMGR_H

#include <string>
#include <vector>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>
#include "../../rexlang_compiler/NodeDecl.h"

namespace rexlang {

    class DebugInfoMgr {
    private:
        llvm::IRBuilder<> &                             TheIRBuilder;
        llvm::DIBuilder &                               TheDIBuilder;
        ordered_map<std::string, llvm::DICompileUnit *> TheDICUMap;
        std::vector<llvm::DIScope *>                    LexicalBlocks;
    public:

        DebugInfoMgr(llvm::IRBuilder<> &IRBuilder, llvm::DIBuilder &DIBuilder);

        /****** 通用功能 *******/

        llvm::DebugLoc EmitLocation(Node *node);

        /******* 编译单元 *******/

        llvm::DICompileUnit *GetOrCreateDICompileUnit(const Node *node);
        llvm::DICompileUnit *GetOrCreateDICompileUnit(const StringRef &FilePath);
        llvm::DICompileUnit *GetOrCreateDICompileUnit(const std::string &FilePath);

        /******* 类型相关 *******/

        /******* 作用域相关 *******/

        void PushLexicalScope(llvm::DIScope *DIScope);
        void PopLexicalScope();

        /******* 函数相关 *******/

        llvm::DISubprogram *CreateFunctionDI(FunctorDecl *functor, llvm::Function *func_ir);
    };

}

#endif //REXLANG_DEBUGINFOMGR_H
