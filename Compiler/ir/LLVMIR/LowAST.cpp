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
#include "../../rexlang_compiler/utilities/ASTBuilder.h"

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
        ASTBuilder B;
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

            ProgramSetFile *sys_fw_sf = B.Create<ProgramSetFile>();
            ProgSetDecl *sys_fw_ps = B.Create<ProgSetDecl>(B.Create<IdentDef>("@system_fw"));
            sys_fw_sf->appendProgramSetDecl(sys_fw_ps);
            TU->appendSourceFile(sys_fw_sf);

            // 创建启动函数

            IdentDef *rex_startup_fn_name = B.Create<IdentDef>("RexStartup");
            assert(rex_startup_fn_name);
            FunctionDecl *startup_fn = B.Create<FunctionDecl>(TU->getIntegerTy(), rex_startup_fn_name, std::vector<ParameterDecl *>());
            sys_fw_ps->appendFunctionDecl(startup_fn);
            startup_stmtblk_ = B.Create<StatementBlock>(std::vector<Statement *>());

            // 创建初始化函数

            IdentDef *init_fn_name = B.Create<IdentDef>("RexInit");
            assert(init_fn_name);
            FunctionDecl *init_fn = B.Create<FunctionDecl>(TU->getVoidTy(), init_fn_name, std::vector<ParameterDecl *>());
            sys_fw_ps->appendFunctionDecl(init_fn);
            init_stmtblk_ = B.Create<StatementBlock>(std::vector<Statement *>());

            // 在启动函数中调用初始化函数

            FunctionCall *call_init_fn = B.CreateFCall(init_fn);
            startup_stmtblk_->appendStatement(call_init_fn);

            // 在启动函数中调用用户的入口函数，并将其返回值作为启动函数的返回值

            FunctorDecl *entry_fn = project_db_.GetMainEntry();
            FunctionCall *call_entry_fn = B.CreateFCall(entry_fn);
            ReturnStmt *return_stmt = B.Create<ReturnStmt>(call_entry_fn);
            startup_stmtblk_->appendStatement(return_stmt);

            return 0;
        }

    private:    // 全局字符串、字节集和数组
        // TODO: 还有结构体
        // 处理所有对象的初始化
        int HandleAllObjectsInit() {
            int EC = 0;
            std::vector<VariableDecl *> variables = CollectVariables();
            if ((EC = InitializeObject(variables))) { return EC; }
            return 0;
        }

        /*
         * 初始化局部对象
         * 静态局部对象需要做特别初始化
         * 例如：
         * arr 整数型 1,1 静态
         * => 如果真 (__static_guard_arr == 0)
         *      如果真 (__rex_guard_acquire(&__static_guard_arr))
         *        arr = create_variable('d', 2, 1, 1)
         *        __rex_guard_release(&__static_guard_arr)
         */
        int InitLocalObject(LocalVariableDecl *localObj) const {
            TranslateUnit *TU = localObj->getTranslateUnit();

            // 生成初始化语句

            Statement *init_stmt = HandleObjectInit(localObj);
            if (!init_stmt) { return 0; }

            if (localObj->isStatic()) {
                StatementBlock *init_blk = rtti::dyn_cast<StatementBlock>(init_stmt);
                assert(init_blk);

                // 创建守卫变量并添加到文件变量表

                ProgSetDecl *prog_site = utility::FindSpecifyTypeParent<ProgSetDecl>(localObj);
                assert(prog_site);
                std::string static_guard_vari_name = "$__static_guard_" + std::string(localObj->getNameStr());
                FileVariableDecl *static_guard_vari = B.Create<FileVariableDecl>(TU->getLongTy(), B.Create<IdentDef>(static_guard_vari_name));
                prog_site->appendFileStaticVari(static_guard_vari);

                // 在初始化语句块末尾添加__rex_guard_release

                FunctionCall *call_guard_release = B.CreateFCall(
                        __rex_guard_release_fn_,
                        {
                            B.Create<HierarchyIdentifier>(std::vector<NameComponent *>({B.Create<IdentRefer>(static_guard_vari->getName())}))
                        }
                );
                init_blk->appendStatement(call_guard_release);

                // 双检测条件

                Expression *conditional = B.Create<BinaryExpression>(
                        OperatorType(OperatorType::Opt::kOptAnd),
                        B.Create<BinaryExpression>(
                                OperatorType(OperatorType::Opt::kOptEqual),
                                B.Create<HierarchyIdentifier>(std::vector<NameComponent *>({B.Create<IdentRefer>(static_guard_vari->getName())})),
                                B.Create<ValueOfDecimal>(0)
                        ),
                        B.Create<BinaryExpression>(
                                OperatorType(OperatorType::Opt::kOptNotEqual),
                                B.CreateFCall(
                                        __rex_acquire_guard_fn_,
                                        {
                                            B.Create<HierarchyIdentifier>(std::vector<NameComponent *>({B.Create<IdentRefer>(static_guard_vari->getName())}))
                                        }
                                ),
                                B.Create<ValueOfDecimal>(0)
                        )
                );
                init_stmt = B.Create<IfStmt>(
                        std::vector<IfStmt::BranchTy>({
                            std::pair<Expression *, Statement *>(conditional, init_blk)
                        }),
                        nullptr
                );
            }

            // 将初始化代码插入到函数体首部

            FunctionDecl *function_decl = utility::FindSpecifyTypeParent<FunctionDecl>(localObj);
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
            ArrayType *vari_arr_ty = rtti::dyn_cast<ArrayType>(arrayObject->getType());
            assert(vari_arr_ty);

            // 收集数组信息

            TypeDecl *base_ty = vari_arr_ty->getArrayBase();
            std::vector<size_t> dimensions = vari_arr_ty->getDimensions();
            if (dimensions.empty()) {
                dimensions.push_back(0);
            }

            // 准备数组对象创建参数

            std::vector<Expression *> args_of_create_array;
            args_of_create_array.push_back(B.Create<ValueOfDecimal>((int) mapping_type_to_sp(base_ty)));
            args_of_create_array.push_back(B.Create<ValueOfDecimal>((int) dimensions.size()));
            for (size_t dim : dimensions) {
                args_of_create_array.push_back(B.Create<ValueOfDecimal>((int) dim));
            }

            // 创建数组对象初始化语句

            AssignStmt *assign_stmt = B.Create<AssignStmt>(
                    B.Create<HierarchyIdentifier>(
                            std::vector<NameComponent *>({
                                B.Create<IdentRefer>(
                                        arrayObject->getName()
                                        )
                            })
                    ),
                    B.CreateFCall(create_array_fn_, args_of_create_array)
            );

            StatementBlock *init_blk = B.Create<StatementBlock>(std::vector<Statement *>({assign_stmt}));
            return init_blk;
        }

        /*
         * 初始化字符串对象
         * 目前语言设计不支持自定义初始化值，所有的字符串初始化都是空字符串
         * 例如：
         * str 文本型
         * => str = create_string("")
         */
        StatementBlock *HandleStringInit(VariableDecl *stringObject) const {
            assert(stringObject->getType()->isStringType());

            // 准备字符串对象创建参数

            std::vector<Expression *> args_of_create_string;
            args_of_create_string.push_back(B.Create<ValueOfString>(TString(StringPool::Create(""))));

            // 创建字符串对象初始化语句

            AssignStmt *assign_stmt = B.Create<AssignStmt>(
                    B.Create<HierarchyIdentifier>(
                            std::vector<NameComponent *>({
                                B.Create<IdentRefer>(
                                        stringObject->getName()
                                )
                            })
                    ),
                    B.CreateFCall(create_string_fn_, args_of_create_string)
            );

            StatementBlock *init_blk = B.Create<StatementBlock>(std::vector<Statement *>({assign_stmt}));
            return init_blk;
        }

        /*
         * 初始化字节集对象
         * 目前语言设计不支持自定义初始化值，所有的字节集初始化都是空字节集
         * 字节集的操作复用字符串接口
         * 例如：
         * ds 字节集型
         * => ds = create_string(0)
         */
        StatementBlock *HandleDatasetInit(VariableDecl *datasetObject) const {
            assert(datasetObject->getType()->isDataSetType());

            // 准备字节集对象创建参数

            std::vector<Expression *> args_of_create_dataset;
            args_of_create_dataset.push_back(B.Create<ValueOfDecimal>((int) 0));

            // 创建字节集对象初始化语句

            AssignStmt *assign_stmt = B.Create<AssignStmt>(
                    B.Create<HierarchyIdentifier>(
                            std::vector<NameComponent *>({
                                B.Create<IdentRefer>(
                                        datasetObject->getName()
                                )
                            })
                    ),
                    B.CreateFCall(create_string_fn_, args_of_create_dataset)
            );

            StatementBlock *init_blk = B.Create<StatementBlock>(std::vector<Statement *>({assign_stmt}));
            return init_blk;
        }

        /*
         * 收集所有变量
         * 包括：文件变量、局部变量、全局变量
         */
        std::vector<VariableDecl *> CollectVariables() const {
            TranslateUnit *TU = project_db_.getTranslateUnit();
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
         * 根据不同的类型调用不同的对象初始化函数
         */
        StatementBlock *HandleObjectInit(VariableDecl *object) const {
            if (object->getType()->isArrayType  ()) { return HandleArrayInit  (object); }
            if (object->getType()->isStringType ()) { return HandleStringInit (object); }
            if (object->getType()->isDataSetType()) { return HandleDatasetInit(object); }
            // TODO: 支持生成平凡类型的初始化语句
            return nullptr;
        }

        /*
         * 初始化对象
         */
        int InitializeObject(const std::vector<VariableDecl *> &variables) const {
            assert(create_array_fn_);
            for (VariableDecl *vari : variables) {
                if (vari->isFileVariable() || vari->isGlobalVariable()) {

                    // 文件变量和全局变量的初始化代码直接放到初始化函数中

                    if (StatementBlock *init_blk = HandleObjectInit(vari)) {
                        init_stmtblk_->appendStatement(init_blk);
                    }
                }
                else if (LocalVariableDecl *local_vari = rtti::dyn_cast<LocalVariableDecl>(vari)) {

                    // 局部对象由独立函数处理

                    int EC = InitLocalObject(local_vari);
                    assert(EC == 0);
                }
            }

            return 0;
        }

    private:
        // 重写字符串/字节集操作符
        int OverrideStringOperator() {
            // 1. 重写赋值操作符
            // 2. 重写加法操作符
            // 3. 重写索引操作符
        }

    private:    // 杂项辅助
        /*
         * 获取运行时API定义
         * corelib/array_runtime_api.h
         * corelib/string_runtime_api.h
         * corelib/struct_runtime_api.h
         */
        void CreateImplicitSysApiDecl() {
            TranslateUnit *TU = project_db_.getTranslateUnit();
            assert(TU);

            auto fetch_api = [TU](const std::string &apiName) -> FunctorDecl* {
                FunctorDecl *api = TU->getFunctor(StringPool::Create(apiName));
                assert(api);
                return api;
            };

            create_array_fn_        = fetch_api("create_array");
            create_string_fn_       = fetch_api("create_string");
            __rex_acquire_guard_fn_ = fetch_api("__rex_acquire_guard");
            __rex_guard_release_fn_ = fetch_api("__rex_guard_release");

        }

    public:
        explicit Lower(ProjectDB &projectDB)
            : project_db_(projectDB), B(projectDB.getTranslateUnit()->getAstContext()) {
        }

        int Run() {
            CreateImplicitSysApiDecl();

            int EC = 0;
            if ((EC = CreateStartup         ())) { return EC; }
            if ((EC = HandleAllObjectsInit  ())) { return EC; }
            if ((EC = OverrideStringOperator())) { return EC; }
            return 0;
        }

    };

    int AstLowing(ProjectDB &projectDB) {
        Lower lower(projectDB);
        return lower.Run();
    }

}