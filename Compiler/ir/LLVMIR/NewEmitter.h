//
// Created by Rexfield on 2021/2/12.
//

#ifndef REXLANG_NEWEMITTER_H
#define REXLANG_NEWEMITTER_H

#include "DebugInfoMgr.h"

namespace rexlang {

#define DEF_EMIT(RET_TY,NODE_TY,NAME) RET_TY *impl_Emit##NODE_TY(NODE_TY *NAME) ; \
                                      RET_TY *Emit(NODE_TY *NAME) { \
                                          OnEmitBegin(NAME); \
                                          RET_TY *r = impl_Emit##NODE_TY(NAME); \
                                          OnEmitEnd(NAME); \
                                          return r; \
                                      }
    class NewEmitter {
    private:
        llvm::LLVMContext   TheContext      ;               /* 当前上下文(LLVM) */
        llvm::Module *      TheModule       = nullptr ;     /* 当前模块(LLVM) */
        llvm::IRBuilder<>   Builder         ;               /* IR构造器 */
        llvm::DIBuilder     DebInfoBuilder  ;               /* 调试信息构造器 */
        DebugInfoMgr        RexDbgMgr       ;

    private:
        ordered_map<FunctorDecl *, llvm::Function *> functor_map_ ;

    private:
        llvm::Function *    SysEntryFunc    = nullptr ;

    private:
        int OnEmitBegin (Node *astNode) ;
        int OnEmitEnd   (Node *astNode) ;

        bool DefineMainEntryAndInitFunc() ;

        DEF_EMIT(llvm::Module, TranslateUnit, TU)
        DEF_EMIT(llvm::GlobalVariable, GlobalVariableDecl, globalVariDecl)

    public:
        NewEmitter() ;
        ~NewEmitter() ;

        llvm::Module *GetModule() const ;
    };

#undef DEF_EMIT

}

#endif //REXLANG_NEWEMITTER_H
