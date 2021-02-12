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
#include "../../rexlang_compiler/utilities/Visitor.h"

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

    bool isAggregateType(TypeDecl *type) {
        if (type->isStringType()) { return true; }
        else if (type->isDataSetType()) { return true; }
        else if (type->isArrayType()) { return true; }
        else if (type->isStructType()) { return true; }
        else if (ReferenceType *ref_ty = rtti::dyn_cast<ReferenceType>(type)) {
            return isAggregateType(ref_ty->getPointee());
        }
        else { return false; }
    }

    class LowingContext {
    private:
        ASTBuilder &    ast_builder_;
        StatementBlock *init_stmtblk_ = nullptr ;

        FunctorDecl *   create_array_fn_    = nullptr ;
        FunctorDecl *   copy_array_fn_      = nullptr ;
        FunctorDecl *   index_array_fn_     = nullptr ;

        FunctorDecl *   create_string_fn_   = nullptr ;
        FunctorDecl *   copy_string_fn_     = nullptr ;
        FunctorDecl *   concat_string_fn_   = nullptr ;
        FunctorDecl *   string_index_fn_    = nullptr ;

        FunctorDecl *   __rex_acquire_guard_fn_     = nullptr ;
        FunctorDecl *   __rex_guard_release_fn_     = nullptr ;

    public:
        LowingContext(ASTBuilder &astBuilder) : ast_builder_(astBuilder) {}

        ASTBuilder &    getASTBuilder   () const { return ast_builder_; }
        StatementBlock *getInitStmtBlk  () const { return init_stmtblk_; }

        void setInitStmtBlk(StatementBlock *blk) { init_stmtblk_ = blk; }

        FunctorDecl *getCreateArrayFn       () const { return create_array_fn_; }
        FunctorDecl *getCopyArrayFn         () const { return copy_array_fn_; }
        FunctorDecl *getIndexArrayFn        () const { return index_array_fn_; }
        FunctorDecl *getCreateStringFn      () const { return create_string_fn_; }
        FunctorDecl *getCopyStringFn        () const { return copy_string_fn_; }
        FunctorDecl *getConcatStringFn      () const { return concat_string_fn_; }
        FunctorDecl *getStringIndexFn       () const { return string_index_fn_; }
        FunctorDecl *getRexAcquireGuardFn   () const { return __rex_acquire_guard_fn_; }
        FunctorDecl *getRexGuardReleaseFn   () const { return __rex_guard_release_fn_; }

        /*
         * 获取运行时API定义
         */
        void CreateImplicitSysApiDeclFrom(TranslateUnit *TU) {
            assert(TU);

            auto fetch_api = [TU](const std::string &apiName) -> FunctorDecl* {
                FunctorDecl *api = TU->getFunctor(StringPool::Create(apiName));
                assert(api);
                return api;
            };

            create_array_fn_        = fetch_api("create_array");
            copy_array_fn_          = fetch_api("copy_array");
            index_array_fn_         = fetch_api("index_array");
            create_string_fn_       = fetch_api("create_string");
            copy_string_fn_         = fetch_api("copy_string");
            concat_string_fn_       = fetch_api("concat_string");
            string_index_fn_        = fetch_api("string_index");
            __rex_acquire_guard_fn_ = fetch_api("__rex_acquire_guard");
            __rex_guard_release_fn_ = fetch_api("__rex_guard_release");

        }

    };

    /*
     * Lowing 动作的基类
     */
    class LowingAction {
    protected:
        LowingContext &Ctx ;
        ASTBuilder &B ;
    public:
        LowingAction(LowingContext &ctx) : Ctx(ctx), B(ctx.getASTBuilder()) {}
        virtual int Do() = 0 ;
    public:
        virtual ~LowingAction() = default ;
    };

    class LowingActionCreator {
    public:
        virtual LowingAction *Create(Node *node, LowingContext &ctx) = 0 ;
        virtual ~LowingActionCreator() = default ;
    };

    /*
     * 处理所有变量的初始化
     * 包括文件变量、全局变量、局部变量、参数变量的初始化
     * TODO: 成员变量
     * 包括平凡类型和非凡类型的初始化
     */
    class VariInitLower : public LowingAction {
    private:
        BaseVariDecl *base_vari_ = nullptr;
        TypeDecl *vari_origin_ty_ = nullptr ;
    public:
        VariInitLower(BaseVariDecl *vari, TypeDecl *variOriginType, LowingContext &ctx)
        : base_vari_(vari)
        , vari_origin_ty_(variOriginType)
        , LowingAction(ctx)
        {}

        class Creator : public LowingActionCreator {
        public:
            LowingAction *Create(Node *node, LowingContext &ctx) override {
                // 文件变量、局部变量、全局变量、成员变量
                if (BaseVariDecl *base_vari_decl = rtti::dyn_cast<BaseVariDecl>(node)) {
                    return new VariInitLower(base_vari_decl, base_vari_decl->getType(), ctx);
                } else {
                    return nullptr;
                }
            }

            ~Creator() override = default;
        };

        /*
         * 路由函数
         * 根据不同的类型调用不同的对象初始化函数
         */
        StatementBlock *HandleObjectInit() const {
            if (vari_origin_ty_->isArrayType  ()) { return HandleArrayInit  (); }
            if (vari_origin_ty_->isStringType ()) { return HandleStringInit (); }
            if (vari_origin_ty_->isDataSetType()) { return HandleDatasetInit(); }

            // 平凡类型的初始化语句

            StatementBlock *init_normal = B.CreateStatementBlock({
                B.Create<AssignStmt>(B.CreateHierName(base_vari_->getName()), B.CreateInt(0))
            });
            return init_normal;
        }

        /*
         * 初始化局部对象
         * 静态局部对象需要做特别初始化
         * 全局对象的初始化动作放在Init函数中，局部对象的初始化动作放在变量声明处
         * 局部对象有静态和动态之分，初始化静态局部对象需要用__rex_acquire_guard保证只有第一次到达语句时才执行初始化
         * 例1：
         * arr 整数型 1,1 静态
         * => arr 长整数型
         * => 如果真 (__static_guard_arr == 0)
         *      如果真 (__rex_guard_acquire(&__static_guard_arr))
         *        arr = create_array('d', 2, 1, 1)
         *        __rex_guard_release(&__static_guard_arr)
         * 例2：
         * arr 整数型 1,1
         * => arr 长整数型
         * => arr = create_array('d', 2, 1, 1)
         */
        int InitLocalObject(LocalVariableDecl *localObj) const {
            TranslateUnit *TU = localObj->getTranslateUnit();

            // 生成初始化语句

            Statement *init_stmt = HandleObjectInit();
            if (!init_stmt) { return 0; }

            if (localObj->isStatic()) {
                StatementBlock *init_blk = rtti::dyn_cast<StatementBlock>(init_stmt);
                assert(init_blk);

                // 创建守卫变量并添加到文件变量表

                ProgSetDecl *prog_site = utility::FindSpecifyTypeParent<ProgSetDecl>(localObj);
                assert(prog_site);
                std::string static_guard_vari_name = "__static_guard_" + std::string(localObj->getNameStr());
                FileVariableDecl *static_guard_vari = B.Create<FileVariableDecl>(TU->getLongTy(), B.Create<IdentDef>(static_guard_vari_name));
                prog_site->appendFileStaticVari(static_guard_vari);

                // 在初始化语句块末尾添加__rex_guard_release

                FunctionCall *call_guard_release = B.CreateFCall(
                        Ctx.getRexGuardReleaseFn(),
                        {
                                B.CreateHierName(static_guard_vari->getName())
                        }
                );
                init_blk->appendStatement(call_guard_release);

                // 双检测条件

                Expression *conditional = B.Create<BinaryExpression>(
                        OperatorType(OperatorType::Opt::kOptAnd),
                        B.CreateEqual(
                                B.CreateHierName(static_guard_vari->getName()),
                                B.CreateInt(0)
                        ),
                        B.CreateNotEqual(
                                B.CreateFCall(
                                        Ctx.getRexAcquireGuardFn(),
                                        {
                                                B.CreateHierName(static_guard_vari->getName())
                                        }
                                ),
                                B.CreateInt(0)
                        )
                );
                init_stmt = B.CreateIfStmt(conditional, init_blk, nullptr);
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
         * 例1：
         * arr 整数型 1,1
         * => arr 长整数型
         * => arr = create_array('d', 2, 1, 1)
         * 例2：
         * arr 字节型 数组
         * => arr 长整数型
         * => arr = create_array('c', 1, 0)
         */
        StatementBlock *HandleArrayInit() const {
            ArrayType *vari_arr_ty = rtti::dyn_cast<ArrayType>(vari_origin_ty_);
            assert(vari_arr_ty);

            // 收集数组信息

            TypeDecl *base_ty = vari_arr_ty->getArrayBase();
            std::vector<size_t> dimensions = vari_arr_ty->getDimensions();
            if (dimensions.empty()) {
                dimensions.push_back(0);
            }

            // 更新变量类型

            base_vari_->updateType(base_vari_->getTranslateUnit()->getLongTy());

            // 准备数组对象创建参数

            std::vector<Expression *> args_of_create_array;
            args_of_create_array.push_back(B.CreateInt(mapping_type_to_sp(base_ty)));
            args_of_create_array.push_back(B.CreateInt(dimensions.size()));
            for (size_t dim : dimensions) {
                args_of_create_array.push_back(B.CreateInt(dim));
            }

            // 创建数组对象初始化语句

            AssignStmt *assign_stmt = B.Create<AssignStmt>(
                    B.CreateHierName(base_vari_->getName()),
                    B.CreateFCall(Ctx.getCreateArrayFn(), args_of_create_array)
            );

            StatementBlock *init_blk = B.CreateStatementBlock({assign_stmt});
            return init_blk;
        }

        /*
         * 初始化字符串对象
         * 目前语言设计不支持自定义初始化值，所有的字符串初始化都是空字符串
         * 例如：
         * str 文本型
         * => str 长整数型
         * => str = create_string("")
         */
        StatementBlock *HandleStringInit() const {
            assert(vari_origin_ty_->isStringType());

            // 准备字符串对象创建参数

            std::vector<Expression *> args_of_create_string;
            args_of_create_string.push_back(B.CreateStringLiteral(""));

            // 更新变量类型

            base_vari_->updateType(base_vari_->getTranslateUnit()->getLongTy());

            // 创建字符串对象初始化语句

            AssignStmt *assign_stmt = B.Create<AssignStmt>(
                    B.CreateHierName(base_vari_->getName()),
                    B.CreateFCall(Ctx.getCreateStringFn(), args_of_create_string)
            );
            StatementBlock *init_blk = B.CreateStatementBlock({assign_stmt});
            return init_blk;
        }

        /*
         * 初始化字节集对象
         * 目前语言设计不支持自定义初始化值，所有的字节集初始化都是空字节集
         * 字节集的操作复用字符串接口
         * 例如：
         * ds 字节集型
         * => ds 长整数型
         * => ds = create_string(0)
         */
        StatementBlock *HandleDatasetInit() const {
            assert(vari_origin_ty_->isDataSetType());

            // 准备字节集对象创建参数

            std::vector<Expression *> args_of_create_dataset;
            args_of_create_dataset.push_back(B.CreateInt(0));

            // 更新变量类型

            base_vari_->updateType(base_vari_->getTranslateUnit()->getLongTy());

            // 创建字节集对象初始化语句

            AssignStmt *assign_stmt = B.Create<AssignStmt>(
                    B.CreateHierName(base_vari_->getName()),
                    B.CreateFCall(Ctx.getCreateStringFn(), args_of_create_dataset)
            );
            StatementBlock *init_blk = B.CreateStatementBlock({assign_stmt});
            return init_blk;
        }

        int Do() override {
            if (base_vari_->is<FileVariableDecl>() || base_vari_->is<GlobalVariableDecl>()) {

                // 文件变量和全局变量的初始化代码直接放到初始化函数中

                if (StatementBlock *init_blk = HandleObjectInit()) {
                    Ctx.getInitStmtBlk()->appendStatement(init_blk);
                }
            } else if (LocalVariableDecl *local_vari = rtti::dyn_cast<LocalVariableDecl>(base_vari_)) {

                // 局部对象由独立函数处理

                int EC = InitLocalObject(local_vari);
                assert(EC == 0);
            } else if (ParameterDecl *parameter_decl = rtti::dyn_cast<ParameterDecl>(base_vari_)) {

                // 参数变量仅修改类型即可

                parameter_decl->updateType(parameter_decl->getTranslateUnit()->getLongTy());
            }
            return 0;
        }

        ~VariInitLower() override = default ;
    };

    /*
     * 处理复合类型的赋值
     */
    class AggregateAssignLower : public LowingAction {
    private:
        AssignStmt *assign_stmt_ = nullptr ;
        FunctorDecl *copy_fn_ = nullptr ;
    public:
        AggregateAssignLower(AssignStmt *assignStmt, LowingContext &ctx, FunctorDecl *copyFn)
        : assign_stmt_(assignStmt)
        , LowingAction(ctx)
        , copy_fn_(copyFn)
        {}

        class Creator : public LowingActionCreator {
        public:
            LowingAction *Create(Node *node, LowingContext &ctx) override {

                // 文件变量、局部变量、全局变量

                if (AssignStmt *assign_stmt = rtti::dyn_cast<AssignStmt>(node)) {

                    // 获取左右表达式及类型

                    Expression *lhs = assign_stmt->getLHS();
                    Expression *rhs = assign_stmt->getRHS();
                    TypeDecl *lhs_type = lhs->getExpressionType();
                    TypeDecl *rhs_type = rhs->getExpressionType();

                    // 选择与类型相应的复制方法

                    FunctorDecl *copy_fn = nullptr;
                    if (lhs_type->isArrayType() && rhs_type->isArrayType()) {
                        copy_fn = ctx.getCopyArrayFn();
                    }
                    else if (lhs_type->isStringType() && rhs_type->isStringType()) {
                        copy_fn = ctx.getCopyStringFn();
                    }
                    else if (lhs_type->isDataSetType() && rhs_type->isDataSetType()) {
                        copy_fn = ctx.getCopyStringFn();
                    }

                    if (copy_fn) {
                        return new AggregateAssignLower(assign_stmt, ctx, copy_fn);
                    }
                }
                return nullptr;
            }

            ~Creator() override = default ;
        };
        int Do() override {
            Expression *lhs = assign_stmt_->getLHS();
            Expression *rhs = assign_stmt_->getRHS();
            if (copy_fn_) {
                Statement *lowed_stmt = B.CreateFCall(copy_fn_, {lhs, rhs});

                // 替换原赋值语句

                StatementBlock *parent_blk = rtti::dyn_cast<StatementBlock>(assign_stmt_->getParent());
                assert(parent_blk);
                parent_blk->replaceStatement(assign_stmt_, lowed_stmt);
                return 0;
            } else {
                assert(false);
                return 1;
            }
        }

        ~AggregateAssignLower() override = default ;
    };

    /*
     * 处理复合类型的二元操作
     */
    class AggregateBinaryExprLower : public LowingAction {
    private:
        BinaryExpression *binary_expression_ = nullptr ;
        FunctorDecl *concat_fn_ = nullptr ;
    public:
        AggregateBinaryExprLower(BinaryExpression *binaryExpression, LowingContext &ctx, FunctorDecl *concatFn)
        : binary_expression_(binaryExpression)
        , LowingAction(ctx)
        , concat_fn_(concatFn)
        {}

        class Creator : public LowingActionCreator {
        public:
            LowingAction *Create(Node *node, LowingContext &ctx) override {
                if (BinaryExpression *bin_expr = rtti::dyn_cast<BinaryExpression>(node)) {

                    if (bin_expr->getOperator().getOperate() == OperatorType::Opt::kOptAdd) {

                        // 获取左右表达式及类型

                        Expression *lopt = bin_expr->getLHS();
                        Expression *ropt = bin_expr->getRHS();
                        TypeDecl *lopt_type = lopt->getExpressionType();
                        TypeDecl *ropt_type = ropt->getExpressionType();

                        // 选择与类型相应的拼接方法并调用

                        FunctorDecl *concat_fn = nullptr;
                        if (lopt_type->isStringType() && ropt_type->isStringType()) {
                            concat_fn = ctx.getConcatStringFn();
                        }
                        else if (lopt_type->isDataSetType() && ropt_type->isDataSetType()) {
                            concat_fn = ctx.getConcatStringFn();
                        }

                        if (concat_fn) {
                            return new AggregateBinaryExprLower(bin_expr, ctx, concat_fn);
                        }
                    }
                }
                return nullptr;
            }

            ~Creator() override = default;
        };

        int Do() override {
            Expression *lopt = binary_expression_->getLHS();
            Expression *ropt = binary_expression_->getRHS();
            if (concat_fn_) {
                Expression *lowed_expression = B.CreateFCall(concat_fn_, {lopt, ropt});

                // 替换原拼接表达式

                Node *parent_node = binary_expression_->getParent();
                assert(parent_node);
                Statement *parent_stmt = rtti::dyn_cast<Statement>(parent_node);
                assert(parent_stmt);
                parent_stmt->replaceChild(binary_expression_, lowed_expression);
                return 0;
            }
            return 1;
        }

        ~AggregateBinaryExprLower() override = default ;
    };

    /*
     * 处理数组索引
     */
    class ArrayIndexLower : public LowingAction {
    private:
        ArrayIndex *array_index_ = nullptr;
        FunctorDecl *index_fn_ = nullptr;
    public:
        ArrayIndexLower(ArrayIndex *arrayIndex, LowingContext &ctx, FunctorDecl *indexFn)
        : array_index_(arrayIndex)
        , LowingAction(ctx)
        , index_fn_(indexFn)
        {}

        class Creator : public LowingActionCreator {
        public:
            LowingAction *Create(Node *node, LowingContext &ctx) override {
                if (ArrayIndex *array_index = rtti::dyn_cast<ArrayIndex>(node)) {
                    IdentRefer *base = array_index->getBaseId();
                    assert(base);
                    TagDecl *vari = base->def()->decl();
                    assert(vari);
                    TypeDecl *vari_ty = vari->getType();
                    FunctorDecl *index_fn = nullptr;
                    if (vari_ty->isStringType() || vari_ty->isDataSetType()) {
                        index_fn = ctx.getStringIndexFn();
                    }
                    else if (vari_ty->isArrayType()) {
                        index_fn = ctx.getIndexArrayFn();
                    }
                    else {
                        assert(false);
                    }
                    return new ArrayIndexLower(array_index, ctx, index_fn);
                }
                return nullptr;
            }

            ~Creator() override = default;
        };

        int Do() override {
            ErrOr<std::vector<Expression *>> err_or_dims = array_index_->getIndexesList();
            assert(err_or_dims.NoError());

            std::vector<Expression *> args = err_or_dims.Value();
            ValueOfDecimal *n = B.CreateInt(args.size());
            args.insert(args.begin(), n);
            IdentRefer *vari = array_index_->getBaseId();
            assert(vari);
            args.insert(args.begin(), vari);

            FunctionCall *lowed_index = B.CreateFCall(Ctx.getIndexArrayFn(), args);
            assert(lowed_index);

            Statement *parent_stmt = rtti::dyn_cast<Statement>(array_index_->getParent());
            assert(parent_stmt);
            parent_stmt->replaceChild(array_index_, lowed_index);

            return 0;
        }

        ~ArrayIndexLower() override = default ;
    };

    class Lower {
    private:
        LowingContext lowing_context_ ;
        ProjectDB &project_db_ ;
        ASTBuilder B;

    private:    // 启动
        // 创建启动和初始化函数
        int CreateStartup() {
            ASTContext &ast_context = project_db_.GetASTContext();
            TranslateUnit *TU = ast_context.getTranslateUnit();
            assert(TU);

            // 创建虚拟的代码文件

            ProgramSetFile *sys_fw_sf = B.Create<ProgramSetFile>();
            ProgSetDecl *sys_fw_ps = B.Create<ProgSetDecl>(B.Create<IdentDef>("@system_fw"));
            sys_fw_sf->appendProgramSetDecl(sys_fw_ps); // 添加到虚拟代码文件
            TU->appendSourceFile(sys_fw_sf);    // 添加到翻译单元

            // 创建启动函数

            IdentDef *rex_startup_fn_name = B.Create<IdentDef>("RexStartup");
            assert(rex_startup_fn_name);
            FunctionDecl *startup_fn = B.Create<FunctionDecl>(TU->getIntegerTy(), rex_startup_fn_name, std::vector<ParameterDecl *>());
            sys_fw_ps->appendFunctionDecl(startup_fn);  // 添加到代码集
            StatementBlock *startup_stmtblk_ = B.Create<StatementBlock>(std::vector<Statement *>());

            // 创建初始化函数

            IdentDef *init_fn_name = B.Create<IdentDef>("RexInit");
            assert(init_fn_name);
            FunctionDecl *init_fn = B.Create<FunctionDecl>(TU->getVoidTy(), init_fn_name, std::vector<ParameterDecl *>());
            sys_fw_ps->appendFunctionDecl(init_fn);     // 添加到代码集
            StatementBlock *init_stmtblk_ = B.Create<StatementBlock>(std::vector<Statement *>());
            lowing_context_.setInitStmtBlk(init_stmtblk_);

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

        class LowerVisitor : public Visitor {
        private:
            std::vector<LowingActionCreator *> lower_creators_ ;
            LowingContext &lowing_context_;
        public:
            std::vector<LowingAction *> lowing_actions_ ;

            LowerVisitor(const std::vector<LowingActionCreator *> &lowerCreators, LowingContext &lowingContext)
            : lower_creators_(lowerCreators)
            , lowing_context_(lowingContext)
            {}
            ~LowerVisitor() override = default;
        public:
            void Visit(Node &node) override {
                for (LowingActionCreator *creator : lower_creators_) {
                    LowingAction *lowing_action = creator->Create(&node, lowing_context_);
                    if (lowing_action) {
                        lowing_actions_.push_back(lowing_action);
                    }
                }
            }
        };

    public:
        explicit Lower(ProjectDB &projectDB)
            : project_db_(projectDB)
            , B(projectDB.getTranslateUnit()->getAstContext())
            , lowing_context_(LowingContext{B}) {
        }

        int Run() {
            lowing_context_.CreateImplicitSysApiDeclFrom(project_db_.getTranslateUnit());

            int EC = 0;
            if ((EC = CreateStartup         ())) { return EC; }

            std::vector<LowingActionCreator *> creators;

            creators.push_back(new VariInitLower           ::Creator());
            creators.push_back(new AggregateAssignLower    ::Creator());
            creators.push_back(new AggregateBinaryExprLower::Creator());
            creators.push_back(new ArrayIndexLower         ::Creator());

            LowerVisitor lower_visitor(creators, lowing_context_);
            project_db_.getTranslateUnit()->Visit(lower_visitor);

            for (LowingAction *action : lower_visitor.lowing_actions_) {
                action->Do();
                delete action;
            }

            for (LowingActionCreator *creator : creators) {
                delete creator;
            }

            return 0;
        }

    };

    int AstLowing(ProjectDB &projectDB) {
        Lower lower(projectDB);
        return lower.Run();
    }

}