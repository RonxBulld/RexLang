//
// Created by Rexfield on 2021/2/12.
//

#ifndef REXLANG_NEWEMITTER_H
#define REXLANG_NEWEMITTER_H

#include "DebugInfoMgr.h"

namespace rexlang {

    class ProjectDB;

#define DEF_EMIT(RET_TY,NODE_TY,NAME) RET_TY *impl_Emit##NODE_TY(NODE_TY *NAME) ; \
                                      RET_TY *Emit(NODE_TY *NAME) { \
                                          OnEmitBegin(NAME); \
                                          RET_TY *r = impl_Emit##NODE_TY(NAME); \
                                          OnEmitEnd(NAME); \
                                          return r; \
                                      }
    class NewEmitter {
    private:
        struct BasicBlockRange {
            llvm::BasicBlock *head = nullptr ;
            llvm::BasicBlock *tail = nullptr ;
        };

    private:
        llvm::LLVMContext   TheContext      ;               /* 当前上下文(LLVM) */
        llvm::Module *      TheModule       = nullptr ;     /* 当前模块(LLVM) */
        llvm::IRBuilder<>   Builder         ;               /* IR构造器 */
        llvm::DIBuilder     DebInfoBuilder  ;               /* 调试信息构造器 */
        DebugInfoMgr        RexDbgMgr       ;

    private:
        /*********************************************************************************************
         * 定义和声明的缓存
         */
        ordered_map<FunctorDecl  *, llvm::FunctionType *> functor_map_  ;
        ordered_map<FunctionDecl *, llvm::Function     *> function_map_ ;
        ordered_map<BaseVariDecl *, llvm::Value        *> variable_map_ ;
        ordered_map<VariTypeDecl *, llvm::Type         *> varitype_map_ ;
        /*********************************************************************************************/

    private:
        /*********************************************************************************************
         * 生成时上下文
         */
        FunctionDecl      * TheASTFunction  = nullptr ;
        llvm::Function    * SysEntryFunc    = nullptr ;
        llvm::Function    * TheFunction     = nullptr ;
        llvm::BasicBlock  * TheReturnBB     = nullptr ;
        llvm::Value       * TheReturnValue  = nullptr ;
        /*********************************************************************************************/

    private:
        int OnEmitBegin (Node *astNode) ;
        int OnEmitEnd   (Node *astNode) ;

        bool DefineMainEntry() ;
        llvm::GlobalVariable *CreateGlobalVariable(VariTypeDecl *type, const std::string &name) ;

        /**********************************************************************************************
         * 这是一组路由函数，用于在对基类 Emit 时便捷的转发到子类的 Emit 处理中
         */
        template<typename RetTy, typename BaseTy>
        RetTy EmitNavigate(BaseTy *node) ;
        template <typename RetTy, typename BaseTy, typename AlternativeTy, typename ... AlternativesTy>
        RetTy EmitNavigate(BaseTy *node) ;
        /*********************************************************************************************/

        DEF_EMIT(llvm::Module, TranslateUnit, TU)

        /**********************************************************************************************
         * 全局变量相关
         */
        DEF_EMIT(llvm::GlobalVariable, GlobalVariableDecl, globalVariDecl  )
        DEF_EMIT(llvm::GlobalVariable, FileVariableDecl  , fileVariableDecl)
        /**********************************************************************************************/

        /**********************************************************************************************
         * 函数相关
         */
        DEF_EMIT(llvm::FunctionType, FunctorDecl      , functorDecl      )
        DEF_EMIT(llvm::Function    , FunctionDecl     , functionDecl     )
        DEF_EMIT(llvm::Value       , ParameterDecl    , parameterDecl    )
        DEF_EMIT(llvm::Value       , LocalVariableDecl, localVariableDecl)
        /**********************************************************************************************/

        /**********************************************************************************************
         * 语句相关
         */
        DEF_EMIT(BasicBlockRange, StatementBlock, statementBlock)
        /**********************************************************************************************/

        /**********************************************************************************************
         * 类型相关
         */
        DEF_EMIT(llvm::Type, VariTypeDecl       , type               )
        DEF_EMIT(llvm::Type, BuiltinVoidType    , builtinVoidType    )
        DEF_EMIT(llvm::Type, BuiltinCommonType  , builtinCommonType  )
        DEF_EMIT(llvm::Type, BuiltinCharType    , builtinCharType    )
        DEF_EMIT(llvm::Type, BuiltinIntegerType , builtinIntegerType )
        DEF_EMIT(llvm::Type, BuiltinFloatType   , builtinFloatType   )
        DEF_EMIT(llvm::Type, BuiltinBoolType    , builtinBoolType    )
        DEF_EMIT(llvm::Type, BuiltinStringType  , builtinStringType  )
        DEF_EMIT(llvm::Type, BuiltinDataSetType , builtinDataSetType )
        DEF_EMIT(llvm::Type, BuiltinShortType   , builtinShortType   )
        DEF_EMIT(llvm::Type, BuiltinLongType    , builtinLongType    )
        DEF_EMIT(llvm::Type, BuiltinDatetimeType, builtinDatetimeType)
        DEF_EMIT(llvm::Type, BuiltinFuncPtrType , builtinFuncPtrType )
        DEF_EMIT(llvm::Type, BuiltinDoubleType  , builtinDoubleType  )
        DEF_EMIT(llvm::Type, ReferenceType      , referenceType      )
        DEF_EMIT(llvm::Type, StructureDecl      , structureDecl      )
        DEF_EMIT(llvm::Type, ArrayType          , arrayType          )
        /**********************************************************************************************/

    public:
        NewEmitter() ;
        ~NewEmitter() ;

        llvm::Module *Gen(ProjectDB &projectDB) ;

        llvm::Module *GetModule() const ;
        llvm::Module *TakeModule() ;
    };

#undef DEF_EMIT

}

#endif //REXLANG_NEWEMITTER_H