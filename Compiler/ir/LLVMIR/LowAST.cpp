/*
 * 抽象语法树下降器
 * Rexfield
 * 2020/11/29
 */

#include "LowAST.h"
#include "../../rexlang_compiler/NodeDecl.h"
#include "../../support/ProjectDB.h"
#include "../../rexlang_compiler/rtti.h"
#include "../SimpleRTTI_ArguType.h"

namespace rexlang {

    SimpleRTTI_ArguType mapping_type_to_sp(TypeDecl *type) {
        if (type->isCharType    ()) { return SimpleRTTI_ArguType::kInt8;   }
        if (type->isShortType   ()) { return SimpleRTTI_ArguType::kInt16;  }
        if (type->isIntegerType ()) { return SimpleRTTI_ArguType::kInt32;  }
        if (type->isLongType    ()) { return SimpleRTTI_ArguType::kInt64;  }
        if (type->isFloatType   ()) { return SimpleRTTI_ArguType::kFloat;  }
        if (type->isDoubleType  ()) { return SimpleRTTI_ArguType::kDouble; }
        if (type->isArrayType   ()) { return SimpleRTTI_ArguType::kArray;  }
        if (type->isStringType  ()) { return SimpleRTTI_ArguType::kString; }
        if (type->isStructType  ()) { return SimpleRTTI_ArguType::kStruct; }
        assert(false);
        return SimpleRTTI_ArguType::kUnknow;
    }

    class Lower {
    private:
        ProjectDB &project_db_ ;
        StatementBlock *startup_stmtblk_ = nullptr ;    // 启动函数语句块
        StatementBlock *init_stmtblk_    = nullptr ;    // 初始化函数语句块

        FunctorDecl *create_array_fn = nullptr ;

    private:    // 启动
        // 创建启动和初始化函数
        int CreateStartup() {
            ASTContext &ast_context = project_db_.GetASTContext();
            TranslateUnit *TU = ast_context.getTranslateUnit();
            assert(TU);

            // 创建虚拟的代码文件

            ProgramSetFile *sys_fw_sf = CreateNode<ProgramSetFile>(&ast_context);
            ProgSetDecl *sys_fw_ps = CreateNode<ProgSetDecl>(&ast_context, CreateNode<IdentDef>(&ast_context, "@system_fw"));
            sys_fw_sf->appendProgramSetDecl(sys_fw_ps);
            TU->appendSourceFile(sys_fw_sf);

            // 创建启动函数

            IdentDef *rex_startup_fn_name = CreateNode<IdentDef>(&ast_context, "RexStartup");
            assert(rex_startup_fn_name);
            FunctionDecl *startup_fn = CreateNode<FunctionDecl>(&ast_context, TU->getIntegerTy(), rex_startup_fn_name, std::vector<ParameterDecl *>());
            sys_fw_ps->appendFunctionDecl(startup_fn);
            startup_stmtblk_ = CreateNode<StatementBlock>(&ast_context, std::vector<Statement *>());

            // 创建初始化函数

            IdentDef *init_fn_name = CreateNode<IdentDef>(&ast_context, "RexInit");
            assert(init_fn_name);
            FunctionDecl *init_fn = CreateNode<FunctionDecl>(&ast_context, TU->getVoidTy(), init_fn_name, std::vector<ParameterDecl *>());
            sys_fw_ps->appendFunctionDecl(init_fn);
            init_stmtblk_ = CreateNode<StatementBlock>(&ast_context, std::vector<Statement *>());

            // 在启动函数中调用初始化函数

            FunctionCall *call_init_fn = CreateNode<FunctionCall>(
                    &ast_context,
                    CreateNode<IdentRefer>(&ast_context, init_fn->getName()),
                    init_fn,
                    std::vector<Expression *>()
            );
            startup_stmtblk_->appendStatement(call_init_fn);

            // 在启动函数中调用用户的入口函数，并将其返回值作为启动函数的返回值

            FunctorDecl *entry_fn = project_db_.GetMainEntry();
            FunctionCall *call_entry_fn = CreateNode<FunctionCall>(
                    &ast_context,
                    CreateNode<IdentRefer>(&ast_context, entry_fn->getName()),
                    entry_fn,
                    std::vector<Expression *>()
            );
            ReturnStmt *return_stmt = CreateNode<ReturnStmt>(&ast_context, call_entry_fn);
            startup_stmtblk_->appendStatement(return_stmt);

            return 0;
        }

    private:    // 全局字符串、字节集和数组
        // 创建全局对象初始化
        int CreateGlobalObjectInitFunction() {
            int EC = 0;
            if ((EC = InitializeGlobalArray())) { return EC; }
            if ((EC = InitializeGlobalString())) { return EC; }
            return 0;
        }

        // 初始化全局数组
        int InitializeGlobalArray() {
            TranslateUnit *TU = project_db_.getTranslateUnit();
            ASTContext *ctx = TU->getAstContext();
            std::vector<VariableDecl *> variables_of_array;
            for (SourceFile *sf : TU->getSourceFiles()) {
                if (ProgramSetFile *program_set_file = rtti::dyn_cast<ProgramSetFile>(sf)) {
                    if (ProgSetDecl *prog_set_decl = program_set_file->getProgramSetDecl()) {
                        for (auto &item : prog_set_decl->fileVariables()) {
                            if (item.second->getType()->isArrayType()) {
                                FileVariableDecl *file_vari_decl = item.second;
                                assert(file_vari_decl);
                                variables_of_array.push_back(file_vari_decl);
                            }
                        }
                    }
                } else if (GlobalVariableFile *global_variable_file = rtti::dyn_cast<GlobalVariableFile>(sf)) {
                    for (auto &item : global_variable_file->getGlobalVariMap()) {
                        if (item.second->getType()->isArrayType()) {
                            GlobalVariableDecl *global_vari_decl = item.second;
                            assert(global_vari_decl);
                            variables_of_array.push_back(global_vari_decl);
                        }
                    }
                }
            }
            // 创建数组对象
            /*
             * 例如：
             * arr 整数型 1,1
             * => arr = create_variable('d', 2, 1, 1)
             * 例如：
             * arr 字节型 数组
             * => arr = create_varialbe('c', 1, 0)
             *
             * 后续的所有数组类型被当做句柄处理
             */
            assert(create_array_fn);
            for (VariableDecl *variable_decl : variables_of_array) {
                ArrayDecl *vari_arr_ty = rtti::dyn_cast<ArrayDecl>(variable_decl->getType());
                assert(vari_arr_ty);

                // 收集数组信息

                TypeDecl *base_ty = vari_arr_ty->getArrayBase();
                std::vector<size_t> dimensions = vari_arr_ty->getDimensions();
                if (dimensions.empty()) {
                    dimensions.push_back(0);
                }

                // 准备数组对象创建参数

                std::vector<Expression *> args_of_create_array;
                args_of_create_array.push_back(CreateNode<ValueOfDecimal>(ctx, (int)mapping_type_to_sp(base_ty)));
                args_of_create_array.push_back(CreateNode<ValueOfDecimal>(ctx, (int)dimensions.size()));
                for (size_t dim : dimensions) {
                    args_of_create_array.push_back(CreateNode<ValueOfDecimal>(ctx, (int) dim));
                }

                // 创建数组对象初始化语句

                AssignStmt *assign_stmt = CreateNode<AssignStmt>(
                        ctx,
                        CreateNode<HierarchyIdentifier>(
                                ctx,
                                std::vector<NameComponent *>({
                                    CreateNode<IdentRefer>(
                                            ctx,
                                            variable_decl->getName()
                                    )
                                })
                        ),
                        CreateNode<FunctionCall>(
                                ctx,
                                CreateNode<IdentRefer>(ctx, create_array_fn->getName()),
                                create_array_fn,
                                args_of_create_array
                        )
                );
                init_stmtblk_->appendStatement(assign_stmt);
            }

            return 0;
        }

        // 初始化局部数组
        int InitializeLocalArray() {
            /*
             * 初始化局部数组和全局数组的差异是：
             * 局部数组有静态和动态之分，初始化静态局部数组需要用acquire guard保证只有第一次到达语句时才执行初始化
             */
        }

        // 初始化全局字符串/字节集
        int InitializeGlobalString() ;

        // 初始化局部字符串/字节集
        int InitializeLocalString() ;

    private:
        // 重命名函数名
        int MangleFunctionName() {
            // 1. 用户自定义函数名添加_前缀和#后缀
            TranslateUnit *TU = project_db_.GetASTContext().getTranslateUnit();
            for (SourceFile *source_file : TU->getSourceFiles()) {
                if (ProgramSetFile *program_set_file = rtti::dyn_cast<ProgramSetFile>(source_file)) {
                    if (ProgSetDecl *prog_set_decl = program_set_file->getProgramSetDecl()) {
                        for (FunctionDecl *function_decl : prog_set_decl->functions()) {
                            assert(function_decl);
                            IdentDef *fn_name = function_decl->getName();
                            std::string mangled_name = "_" + fn_name->id().str() + "#";
                            fn_name->update(mangled_name);
                        }
                    }
                }
            }
            // 2. 根据变量的存储类型不同修改变量名
            /*
             * 全局变量
             * 文件变量
             * 局部变量
             * 静态变量
             */
            return 0;
        }

        // 重写字符串/字节集操作符
        int OverrideStringOperator() {
            // 1. 重写赋值操作符
            // 2. 重写加法操作符
            // 3. 重写索引操作符
        }

    private:    // 杂项辅助
        /*
         * 创建隐式系统API定义
         * corelib/array_runtime_api.h
         * corelib/string_runtime_api.h
         * corelib/struct_runtime_api.h
         */
        void CreateImplicitSysApiDecl() {
            ASTContext *ctx = &project_db_.GetASTContext();
            TranslateUnit *TU = ctx->getTranslateUnit();
            assert(TU);

            // 创建虚拟接口文件

            APIDeclareFile *impl_api_df = CreateNode<APIDeclareFile>(ctx);
            TU->appendSourceFile(impl_api_df);

            auto create_corelib_api = [ctx, impl_api_df] (
                    VariTypeDecl *retType,
                    const std::string &apiName,
                    const std::vector<ParameterDecl *> &parameters
            ) -> FunctorDecl * {
                APICommandDecl *created_api = CreateNode<APICommandDecl>(
                        ctx,
                        retType,
                        CreateNode<IdentDef>(ctx, apiName),
                        parameters,
                        LibraryType::kLTStatic,
                        TString(StringPool::Create("corelib"), 0),
                        CreateNode<IdentDef>(ctx, apiName)
                );
                impl_api_df->appendAPIDeclare(created_api);
                return created_api;
            };

            VariTypeDecl *chrTy = TU->getCharTy(), *intTy = TU->getIntegerTy();
            VariTypeDecl *arrTy = ReferenceType::get(TU->getVoidTy());

            create_array_fn = create_corelib_api(
                    arrTy,
                    "create_array",
                    std::vector<ParameterDecl *>({
                        CreateNode<ParameterDecl>(ctx, chrTy, CreateNode<IdentDef>(ctx, "ty")),
                        CreateNode<ParameterDecl>(ctx, intTy, CreateNode<IdentDef>(ctx, "dimn")),
                        CreateNode<ParameterDecl>(ctx, intTy, CreateNode<IdentDef>(ctx, "..."), true)
                    })
            );

            create_corelib_api(
                    intTy,
                    "get_array_dim_depth",
                    std::vector<ParameterDecl *>({
                        CreateNode<ParameterDecl>(ctx, arrTy, CreateNode<IdentDef>(ctx, "arr"))
                    })
            );

            create_corelib_api(
                    intTy,
                    "get_array_size",
                    std::vector<ParameterDecl *>({
                        CreateNode<ParameterDecl>(ctx, arrTy, CreateNode<IdentDef>(ctx, "arr"))
                    })
            );

        }

    public:
        explicit Lower(ProjectDB &projectDB) : project_db_(projectDB) {
        }

        int Run() {
            int EC = 0;
            if ((EC = MangleFunctionName            ())) { return EC; }
            if ((EC = CreateStartup                 ())) { return EC; }
            if ((EC = CreateGlobalObjectInitFunction())) { return EC; }
            if ((EC = OverrideStringOperator        ())) { return EC; }
            return 0;
        }

    };

    int AstLowing(ProjectDB &projectDB) {
        Lower lower(projectDB);
        return lower.Run();
    }

}