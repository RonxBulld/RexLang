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
#include "../../rexlang_compiler/ASTUtility.h"

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

        FunctorDecl *create_array_fn_ = nullptr ;
        FunctorDecl *create_string_fn_ = nullptr ;

        FunctorDecl *__rex_acquire_guard_fn_ = nullptr ;
        FunctorDecl *__rex_guard_release_fn_ = nullptr ;

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
            std::vector<VariableDecl *> variables = CollectVariables();
            if ((EC = InitializeGlobalArray(variables))) { return EC; }
            if ((EC = InitializeGlobalString(variables))) { return EC; }
            return 0;
        }

        /*
         * 初始化局部数组对象
         * 例如：
         * arr 整数型 1,1 静态
         * => 如果真 (__static_guard_arr == 0)
         *      如果真 (__rex_guard_acquire(&__static_guard_arr))
         *        arr = create_variable('d', 2, 1, 1)
         *        __rex_guard_release(&__static_guard_arr)
         */
        int InitLocalArrayObject(LocalVariableDecl *staticLocalObj) const {
            assert(staticLocalObj->isStatic());
            ASTContext *ctx = staticLocalObj->getAstContext();
            TranslateUnit *TU = ctx->getTranslateUnit();

            // 生成数组初始化语句

            StatementBlock *init_blk = HandleArrayInit(staticLocalObj);
            Statement *init_stmt = init_blk;

            if (staticLocalObj->isStatic()) {

                // 创建守卫变量并添加到文件变量表

                ProgSetDecl *prog_site = utility::FindSpecifyTypeParent<ProgSetDecl>(staticLocalObj);
                assert(prog_site);
                std::string static_guard_vari_name = "__static_guard_" + std::string(staticLocalObj->getNameStr());
                FileVariableDecl *static_guard_vari = CreateNode<FileVariableDecl>(ctx, TU->getLongTy(), CreateNode<IdentDef>(ctx, static_guard_vari_name));
                prog_site->appendFileStaticVari(static_guard_vari);

                // 在初始化语句块末尾添加__rex_guard_release

                FunctionCall *call_guard_release = CreateNode<FunctionCall>(
                        ctx,
                        CreateNode<IdentRefer>(ctx, __rex_guard_release_fn_->getName()),
                        __rex_guard_release_fn_,
                        std::vector<Expression *>({
                            CreateNode<HierarchyIdentifier>(ctx, std::vector<NameComponent *>({CreateNode<IdentRefer>(ctx, static_guard_vari->getName())}))
                        })
                );
                init_blk->appendStatement(call_guard_release);

                // 双检测条件

                Expression *conditional = CreateNode<BinaryExpression>(
                        ctx,
                        OperatorType(OperatorType::Opt::kOptAnd),
                        CreateNode<BinaryExpression>(
                                ctx,
                                OperatorType(OperatorType::Opt::kOptEqual),
                                CreateNode<HierarchyIdentifier>(ctx, std::vector<NameComponent *>({CreateNode<IdentRefer>(ctx, static_guard_vari->getName())})),
                                CreateNode<ValueOfDecimal>(ctx, 0)
                        ),
                        CreateNode<BinaryExpression>(
                                ctx,
                                OperatorType(OperatorType::Opt::kOptNotEqual),
                                CreateNode<FunctionCall>(
                                        ctx,
                                        CreateNode<IdentRefer>(ctx, __rex_acquire_guard_fn_->getName()),
                                        __rex_acquire_guard_fn_,
                                        std::vector<Expression *>({
                                            CreateNode<HierarchyIdentifier>(ctx, std::vector<NameComponent *>({CreateNode<IdentRefer>(ctx, static_guard_vari->getName())}))
                                        })
                                ),
                                CreateNode<ValueOfDecimal>(ctx, 0)
                        )
                );
                init_stmt = CreateNode<IfStmt>(
                        ctx,
                        std::vector<IfStmt::BranchTy>({
                            std::pair<Expression *, Statement *>(conditional, init_blk)
                        }),
                        nullptr
                );
            }

            // 将初始化代码插入到函数体首部

            FunctionDecl *function_decl = utility::FindSpecifyTypeParent<FunctionDecl>(staticLocalObj);
            assert(function_decl);
            StatementBlock *body = function_decl->getFunctionBody();
            std::vector<Statement *> body_stmts = body->getStatements();
            body_stmts.insert(body_stmts.begin(), init_stmt);
            body->replaceStatements(body_stmts);

            return 0;
        }

        /*
         * 根据输入的数组变量节点生成初始化语句块
         * 初始化局部数组和全局数组的差异是：
         * 全局数组的初始化动作放在Init函数中，局部数组的初始化动作放在变量声明处
         * 局部数组有静态和动态之分，初始化静态局部数组需要用__rex_acquire_guard保证只有第一次到达语句时才执行初始化
         * 例如：
         * arr 整数型 1,1
         * => arr = create_variable('d', 2, 1, 1)
         * 例如：
         * arr 字节型 数组
         * => arr = create_varialbe('c', 1, 0)
         */
        StatementBlock *HandleArrayInit(VariableDecl *arrayObject) const {
            ASTContext *ctx = arrayObject->getAstContext();

            ArrayDecl *vari_arr_ty = rtti::dyn_cast<ArrayDecl>(arrayObject->getType());
            assert(vari_arr_ty);

            // 收集数组信息

            TypeDecl *base_ty = vari_arr_ty->getArrayBase();
            std::vector<size_t> dimensions = vari_arr_ty->getDimensions();
            if (dimensions.empty()) {
                dimensions.push_back(0);
            }

            // 准备数组对象创建参数

            std::vector<Expression *> args_of_create_array;
            args_of_create_array.push_back(CreateNode<ValueOfDecimal>(ctx, (int) mapping_type_to_sp(base_ty)));
            args_of_create_array.push_back(CreateNode<ValueOfDecimal>(ctx, (int) dimensions.size()));
            for (size_t dim : dimensions) {
                args_of_create_array.push_back(CreateNode<ValueOfDecimal>(ctx, (int) dim));
            }

            // 创建数组对象初始化语句

            AssignStmt *assign_stmt = CreateNode<AssignStmt>(
                    ctx,
                    CreateNode<HierarchyIdentifier>(
                            ctx,
                            std::vector<NameComponent *>(
                                    {
                                            CreateNode<IdentRefer>(
                                                    ctx,
                                                    arrayObject->getName()
                                            )
                                    }
                            )
                    ),
                    CreateNode<FunctionCall>(
                            ctx,
                            CreateNode<IdentRefer>(ctx, create_array_fn_->getName()),
                            create_array_fn_,
                            args_of_create_array
                    )
            );

            StatementBlock *init_blk = CreateNode<StatementBlock>(ctx, std::vector<Statement *>({assign_stmt}));
            return init_blk;
        }

        /*
         * 收集所有变量
         * 包括：文件变量、局部变量、全局变量
         */
        std::vector<VariableDecl *> CollectVariables() const {
            TranslateUnit *TU = project_db_.getTranslateUnit();
            ASTContext *ctx = TU->getAstContext();
            std::vector<VariableDecl *> variables;

            for (SourceFile *sf : TU->getSourceFiles()) {
                if (ProgramSetFile *program_set_file = rtti::dyn_cast<ProgramSetFile>(sf)) {
                    if (ProgSetDecl *prog_set_decl = program_set_file->getProgramSetDecl()) {
                        // 文件变量
                        for (FileVariableDecl *file_vari : prog_set_decl->fileVariables()) {
                            variables.push_back(file_vari);
                        }
                        // 局部变量
                        for (FunctionDecl *function : prog_set_decl->functions()) {
                            for (LocalVariableDecl *local_vari : function->getLocalVariables()) {
                                variables.push_back(local_vari);
                            }
                        }
                    }
                } else if (GlobalVariableFile *global_variable_file = rtti::dyn_cast<GlobalVariableFile>(sf)) {
                    // 全局变量
                    for (GlobalVariableDecl *global_vari : global_variable_file->getGlobalVariMap()) {
                        variables.push_back(global_vari);
                    }
                }
            }

            return variables;
        }

        /*
         * 初始化数组对象
         */
        int InitializeGlobalArray(const std::vector<VariableDecl *> &variables) const {
            assert(create_array_fn_);
            for (VariableDecl *vari : variables) {
                if (vari->getType()->isArrayType()) {
                    if (vari->isFileVariable() || vari->isGlobalVariable()) {

                        // 文件变量和全局变量的初始化代码直接放到初始化函数中

                        init_stmtblk_->appendStatement(HandleArrayInit(vari));
                    }
                    else if (LocalVariableDecl *local_vari = rtti::dyn_cast<LocalVariableDecl>(vari)) {
                        int EC = InitLocalArrayObject(local_vari);
                        assert(EC == 0);
                    }
                }
            }

            return 0;
        }

        // 初始化全局字符串/字节集
        int InitializeGlobalString(const std::vector<VariableDecl *> &variables) ;

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

            VariTypeDecl *chrTy = TU->getCharTy(), *intTy = TU->getIntegerTy(), *voidTy = TU->getVoidTy();
            VariTypeDecl *voidPtr = ReferenceType::get(TU->getVoidTy());
            VariTypeDecl *arrTy = voidPtr, *strTy = voidPtr;

            create_array_fn_ = create_corelib_api(
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

            create_string_fn_ = create_corelib_api(
                    strTy,
                    "create_string",
                    std::vector<ParameterDecl *>({
                        CreateNode<ParameterDecl>(ctx, TU->getLongTy(), CreateNode<IdentDef>(ctx, "str"))
                    })
            );

            ReferenceType *refLongTy = ReferenceType::get(TU->getLongTy());

            __rex_acquire_guard_fn_ = create_corelib_api(
                    intTy,
                    "__rex_acquire_guard",
                    std::vector<ParameterDecl *>({
                        CreateNode<ParameterDecl>(ctx, refLongTy, CreateNode<IdentDef>(ctx, "raw_guard_object"))
                    })
            );

            __rex_guard_release_fn_ = create_corelib_api(
                    voidTy,
                    "__rex_guard_release",
                    std::vector<ParameterDecl *>({
                        CreateNode<ParameterDecl>(ctx, refLongTy, CreateNode<IdentDef>(ctx, "raw_guard_object"))
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