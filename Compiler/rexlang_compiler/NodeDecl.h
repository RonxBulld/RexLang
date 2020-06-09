//
// Created by rex on 2020/1/3.
//

#ifndef REXLANG_NODEDECL_H
#define REXLANG_NODEDECL_H

#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <set>

#include "../../lite_util/TString.h"
#include "../../lite_util/ordered_map/ordered_map.h"
#include "ASTContext.h"

namespace rexlang {

    template <typename _Key, typename _Val>
    class ordered_map : public tsl::ordered_map<_Key, _Val> {
    public:
        ordered_map() {}
        ordered_map(const ordered_map<_Key, _Val> &other) {
            *this = other;
        }
        ~ordered_map() {}
        ordered_map<_Key, _Val> &operator=(const ordered_map<_Key, _Val> &other) = default;
    };

    class ASTContext;

    // Base

    typedef struct Node* NodePtr;

    // Project

    typedef struct TranslateUnit* TranslateUnitPtr;

    // File

    typedef struct SourceFile* SourceFilePtr;
    typedef struct ProgramSetFile* ProgramSetFilePtr;
    typedef struct GlobalVariableFile* GlobalVariableFilePtr;
    typedef struct DataStructureFile* DataStructureFilePtr;
    typedef struct DllDefineFile* DllDefineFilePtr;

    // Declare

    // Type declare

    typedef struct Decl* DeclPtr;
    typedef struct TagDecl* TagDeclPtr;
    typedef struct TypeDecl* TypeDeclPtr;
    typedef struct StructureDecl* StructureDeclPtr;
    typedef struct BuiltinTypeDecl* BuiltinTypeDeclPtr;
    typedef struct ArrayDecl* ArrayDeclPtr;

    // Entity declare

    typedef struct BaseVariDecl* BaseVariDeclPtr;
    typedef struct VariableDecl* VariableDeclPtr;
    typedef struct GlobalVariableDecl* GlobalVariableDeclPtr;
    typedef struct LocalVariableDecl* LocalVariableDeclPtr;
    typedef struct ParameterDecl* ParameterDeclPtr;
    typedef struct MemberVariableDecl* MemberVariableDeclPtr;
    typedef struct FileVariableDecl* FileVariableDeclPtr;
    typedef struct FunctorDecl* FunctorDeclPtr;
    typedef struct FunctionDecl* FunctionDeclPtr;
    typedef struct ProgSetDecl* ProgSetDeclPtr;
    typedef struct APICommandDecl* APICommandDeclPtr;

    // Statement

    typedef struct Statement* StatementPtr;
    typedef struct IfStmt* IfStmtPtr;
    typedef struct StatementBlock* StatementBlockPtr;
    typedef struct LoopStatement* LoopStatementPtr;
    typedef struct WhileStmt* WhileStmtPtr;
    typedef struct RangeForStmt* RangeForStmtPtr;
    typedef struct ForStmt* ForStmtPtr;
    typedef struct DoWhileStmt* DoWhileStmtPtr;
    typedef struct AssignStmt* AssignStmtPtr;
    typedef struct ControlStmt *ControlStmtPtr;
    typedef struct LoopControlStmt *LoopControlStmtPtr;
    typedef struct ContinueStmt *ContinueStmtPtr;
    typedef struct BreakStmt *BreakStmtPtr;
    typedef struct ReturnStmt *ReturnStmtPtr;
    typedef struct ExitStmt *ExitStmtPtr;

    // Expression

    typedef struct Expression* ExpressionPtr;
    typedef struct HierarchyIdentifier* HierarchyIdentifierPtr;
    typedef struct NameComponent* NameComponentPtr;
    typedef struct Identifier* IdentifierPtr;
    typedef struct ArrayIndex* ArrayIndexPtr;
    typedef struct FunctionCall* FunctionCallPtr;
    typedef struct UnaryExpression* UnaryExpressionPtr;
    typedef struct BinaryExpression* BinaryExpressionPtr;
    typedef struct _OperatorExpression* _OperatorExpressionPtr;
    typedef struct TypeConvert* TypeConvertPtr;

    // Value

    typedef struct Value* ValuePtr;
    typedef struct ValueOfDataSet* ValueOfDataSetPtr;
    typedef struct ValueOfDatetime* ValueOfDatetimePtr;
    typedef struct FuncAddrExpression* FuncAddrExpressionPtr;
    typedef struct ResourceRefExpression* ResourceRefExpressionPtr;
    typedef struct ValueOfBool* ValueOfBoolPtr;
    typedef struct ValueOfDecimal* ValueOfDecimalPtr;
    typedef struct ValueOfString* ValueOfStringPtr;

    /**
     * @brief 节点类型枚举
     */
    typedef enum class NodeType {
        kNTyBadType,
        kNTyTranslateUnit,
        kNTySourceFile,
        kNTyProgramSetFile,
        kNTyGlobalVariableFile,
        kNTyDataStructureFile,
        kNTyDllDefineFile,
        kNTyDecl,
        kNTyTagDecl,
        kNTyVariableDecl,
        kNTyBaseVariDecl,
        kNTyGlobalVariableDecl,
        kNTyParameterDecl,
        kNTyMemberVariableDecl,
        kNTyFileVariableDecl,
        kNTyLocalVariableDecl,
        kNTyTypeDecl,
        kNTyBuiltinTypeDecl,
        kNTyArrayDecl,
        kNTyStructureDecl,
        kNTyFunctorDecl,
        kNTyFunctionDecl,
        kNTyProgSetDecl,
        kNTyDllCommandDecl,
        kNTyStatement,
        kNTyIfStmt,
        kNTyStatementBlock,
        kNTyLoopStatement,
        kNTyWhileStmt,
        kNTyRangeForStmt,
        kNTyForStmt,
        kNTyDoWhileStmt,
        kNTyAssignStmt,
        kNTyControlStmt,
        kNTyLoopControlStmt,
        kNTyContinueStmt,
        kNTyBreakStmt,
        kNTyReturnStmt,
        kNTyExitStmt,
        kNTyExpression,
        kNTyHierarchyIdentifier,
        kNTyNameComponent,
        kNTyIdentifier,
        kNTyArrayIndex,
        kNTyFunctionCall,
        kNTyUnaryExpression,
        kNTyBinaryExpression,
        kNTy_OperatorExpression,
        kNTyTypeConvert,
        kNTyValue,
        kNTyValueOfDataSet,
        kNTyValueOfDatetime,
        kNTyFuncAddrExpression,
        kNTyResourceRefExpression,
        kNTyValueOfBool,
        kNTyValueOfDecimal,
        kNTyValueOfString,
    } NodeType;

    /*
     * 访问级别
     */
    enum class AccessLevel {
        /*
         * 公开
         */
        kALPublic,
        /*
         * 私有
         */
        kALPrivate,
    };

    /*
     * 传值方式
     */
    enum class ValueTransferMode {
        /*
         * 传值
         */
        kVTMValue,
        /*
         * 传址
         */
        kVTMReference,
    };

    /**
     * @brief 节点基类
     */
    struct Node {
        size_t node_id_ = 0;
        ASTContext *ast_context_ = nullptr;
        Node *parent_node_ = nullptr;
        NodeType node_type_ = NodeType::kNTyBadType;
        size_t location_start_ = 0, location_end_ = 0;

        template<typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        const Ty *as() const {
            return dynamic_cast<const Ty *>(this);
        }

        template<typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        Ty *as() {
            return dynamic_cast<Ty *>(this);
        }

        template<typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        bool is() const {
            return dynamic_cast<const Ty *>(this) != nullptr;
        }

        virtual ~Node() {
        }
    };

    /**
     * @brief 资源文件基类
     */
    struct SourceFile : public Node {
        static const NodeType node_type = NodeType::kNTySourceFile;
        enum FileType {kProgramSetFile, kGlobalVariableFile, kDataStructureFile, kDllDefineFile} file_type_;
    };

    /**
     * @brief 函数声明文件
     */
    struct ProgramSetFile : public SourceFile {
        static const NodeType node_type = NodeType::kNTyProgramSetFile;
        std::vector<TString> libraries_;
        ProgSetDeclPtr program_set_declares_ = nullptr;
    };

    /**
     * @brief 全局变量声明文件
     */
    struct GlobalVariableFile : public SourceFile {
        static const NodeType node_type = NodeType::kNTyGlobalVariableFile;
        ordered_map<StringRef, GlobalVariableDeclPtr> global_variable_map_;
    };

    /**
     * @brief 数据结构定义文件
     */
    struct DataStructureFile : public SourceFile {
        static const NodeType node_type = NodeType::kNTyDataStructureFile;
        ordered_map<StringRef, StructureDeclPtr> structure_decl_map_;
    };

    /**
     * @brief DLL函数接口声明文件
     */
    struct DllDefineFile : public SourceFile {
        static const NodeType node_type = NodeType::kNTyDllDefineFile;
        ordered_map<StringRef, APICommandDeclPtr> dll_declares_;
    };

    /**
     * @brief 定义基类
     */
    struct Decl : public Node {
        static const NodeType node_type = NodeType::kNTyDecl;
    };

    /*
     * 带有名称和注释的命名定义基本结构
     */
    struct TagDecl : public Decl {
        static const NodeType node_type = NodeType::kNTyTagDecl;
        // 定义名称
        TString name_;
        // 注释
        TString comment_;
    };

    /*
     * 描述成员变量、全局变量、局部变量、参数等带有类型的基本结构
     */
    struct BaseVariDecl : public TagDecl {
        static const NodeType node_type = NodeType::kNTyBaseVariDecl;
        // 类型名称
        TString type_name_;

        // === 下面是经过语义分析后的数据 ===

        // 类型指针
        TypeDeclPtr type_decl_ptr_ = nullptr;
    };

    /*
     * 描述参数
     */
    struct ParameterDecl : public BaseVariDecl {
        static const NodeType node_type = NodeType::kNTyParameterDecl;
        // 可选参数为：参考、可空、数组
        std::vector<TString> attributes_;

        // === 下面是经过语义分析后的数据 ===

        /*
         * 形参位置索引
         */
        size_t index_ = 0;

        /*
         * 是否引用类型
         */
        bool is_reference = false;

        /*
         * 是否可空
         */
        bool is_nullable = false;

        /*
         * 是否数组
         */
        bool is_array = false;

    };

    /*
     * 描述成员变量、全局变量、局部变量、文件变量
     */
    struct VariableDecl : public BaseVariDecl {
        static const NodeType node_type = NodeType::kNTyVariableDecl;

        // 变量属性
        std::vector<TString> attributes_;

        // 维度的文本描述
        TString dimension_;
    };

    /*
     * 描述全局变量
     */
    struct GlobalVariableDecl : public VariableDecl {
        static const NodeType node_type = NodeType::kNTyGlobalVariableDecl;

        // 访问级别的文本描述
        TString access_;

        // === 下面是经过语义分析后的数据 ===

        /*
         * 访问级别
         */
        AccessLevel access_level_ = AccessLevel::kALPublic;
    };

    /*
     * 描述成员变量
     */
    struct MemberVariableDecl : public VariableDecl {
        static const NodeType node_type = NodeType::kNTyMemberVariableDecl;

        // === 下面是经过语义分析后的数据 ===

        size_t index_of_struct_ = 0;

        bool is_reference_ = false;

    };

    /*
     * 描述文件变量
     */
    struct FileVariableDecl : public VariableDecl {
        static const NodeType node_type = NodeType::kNTyFileVariableDecl;
    };

    /*
     * 描述局部变量
     */
    struct LocalVariableDecl : public VariableDecl {
        static const NodeType node_type = NodeType::kNTyLocalVariableDecl;

        // === 下面是经过语义分析后的数据 ===

        /*
         * 是否为静态
         */
        bool is_static_ = false;
    };

    /*
     * 类型定义分支
     */
    struct TypeDecl : public TagDecl {
        static const NodeType node_type = NodeType::kNTyTypeDecl;
    };

    /*
     * 内置类型定义
     */
    struct BuiltinTypeDecl : public TypeDecl {
        static const NodeType node_type = NodeType::kNTyBuiltinTypeDecl;
        // 内置类型枚举
		enum class EnumOfBuiltinType {
			kBTypeVoid,         // 空
			kBTTypeCommon,      // 通用型
			kBTypeChar,         // 字节型
			kBTypeInteger,     // 整数型
			kBTypeFloat,       // 小数型
			kBTypeBool,        // 逻辑型
			kBTypeString,      // 文本型
			kBTypeDataSet,     // 字节集
			kBTypeShort,       // 短整型
			kBTypeLong,        // 长整型
			kBTypeDatetime,    // 日期时间型
			kBTypeFuncPtr,     // 子程序指针
			kBTypeDouble,      // 双精度小数型
			kBTtypeEND,
		};
		EnumOfBuiltinType built_in_type_ = EnumOfBuiltinType::kBTypeInteger;
    };

    /*
     * 数据结构定义
     */
    struct StructureDecl : public TypeDecl {
        static const NodeType node_type = NodeType::kNTyStructureDecl;
        TString access_;
        ordered_map<StringRef, MemberVariableDeclPtr> members_;
    };

    /*
     * 数组类型
     */
    struct ArrayDecl : public TypeDecl {
        static const NodeType node_type = NodeType::kNTyArrayDecl;
        TString base_type_str;

        // === 下面是经过语义分析后的数据 ===

        TypeDeclPtr base_type_ = nullptr;
        // 数组维度定义，如果不是数组，则为空
        std::vector<size_t> dimensions_;
    };

    /**
     * @brief 具有函数性的定义
     * 包含子函数定义和DLL函数定义
     */
    struct FunctorDecl : public TypeDecl {
        static const NodeType node_type = NodeType::kNTyFunctorDecl;
        // 返回值类型名
        TString return_type_name_;
        // 参数列表
        std::vector<ParameterDeclPtr> parameters_;

        // === 下面是经过语义分析后的数据 ===

        // 返回值类型
        TypeDeclPtr return_type_ = nullptr;
    };

    /**
     * @brief 子程序/函数定义
     */
    struct FunctionDecl : public FunctorDecl {
        static const NodeType node_type = NodeType::kNTyFunctionDecl;
        // 访问级别
        TString access_;
        // 局部变量列表
        ordered_map<StringRef, LocalVariableDeclPtr> local_vari_;
        // 语句列表
        StatementBlockPtr statement_list_ = nullptr;

        // === 下面是经过语义分析后的数据 ===

        // 所属程序集
        ProgSetDeclPtr super_set_ = nullptr;
    };

//    /**
//     * @brief 内建函数声明
//     */
//    struct BuiltinFunctionDecl : public FunctorDecl {
//        static const NodeType node_type = NodeType::kNTyBuiltinFunctionDecl;
//    };

    /*!
     * @brief 程序库类型
     */
    enum LibraryType {
        /*!
         * @brief 动态链接库函数
         */
        kLTDynamic,
        /*!
         * @brief 静态链接库函数
         */
        kLTStatic,
    };

    /*
     * 参数传递模型
     */
    enum ArgumentPassModel {
        /*!
         * @brief 直接传递
         */
        kDirect,
        /*!
         * @brief 简单RTTI参数包
         */
        kSimpleRTTIPack,
    };

    /**
     * @brief DLL函数声明
     */
    struct APICommandDecl : public FunctorDecl {
        static const NodeType node_type = NodeType::kNTyDllCommandDecl;
        // API库文件名
        TString library_file_;
        // API库类型
        LibraryType library_type_ = LibraryType::kLTDynamic;
        // 原生函数名称
        TString api_name_;
        // 参数传递方式
        ArgumentPassModel argument_pass_model_ = ArgumentPassModel::kDirect;
        // 原生参数名称
        std::vector<StringRef> mapping_names_;
    };

    /**
     * @brief 程序集定义
     */
    struct ProgSetDecl : public TagDecl {
        static const NodeType node_type = NodeType::kNTyProgSetDecl;
        TString base_;
        TString access_;
        ordered_map<StringRef, FileVariableDeclPtr> file_static_variables_;
        ordered_map<StringRef, FunctionDeclPtr> function_decls_;
    };

    /**
     * @brief 语句基类
     */
    struct Statement : public Node {
        static const NodeType node_type = NodeType::kNTyStatement;
    };

    /**
     * @brief 赋值语句
     */
    struct AssignStmt : public Statement {
        static const NodeType node_type = NodeType::kNTyAssignStmt;
        HierarchyIdentifierPtr lhs_ = nullptr;
        ExpressionPtr rhs_ = nullptr;
    };

    /**
     * @brief 控制语句
     */
    struct ControlStmt : public Statement {
        static const NodeType node_type = NodeType::kNTyControlStmt;
    };

    /**
     * @brief 循环控制语句
     */
    struct LoopControlStmt : public ControlStmt {
        static const NodeType node_type = NodeType::kNTyLoopControlStmt;

        // === 下面是经过语义分析后的数据 ===

        // 所控制的循环语句
        LoopStatementPtr loop_statement_ = nullptr;
    };

    /**
     * @brief 到循环尾
     */
    struct ContinueStmt : public LoopControlStmt {
        static const NodeType node_type = NodeType::kNTyContinueStmt;
    };

    /**
     * @brief 跳出循环
     */
    struct BreakStmt : public LoopControlStmt {
        static const NodeType node_type = NodeType::kNTyBreakStmt;
    };

    /**
     * @brief 返回
     */
    struct ReturnStmt : public ControlStmt {
        static const NodeType node_type = NodeType::kNTyReturnStmt;
        ExpressionPtr return_value_ = nullptr;

        // === 下面是经过语义分析后的数据 ===

    };

    /**
     * @brief 结束
     */
    struct ExitStmt : public ControlStmt {
        static const NodeType node_type = NodeType::kNTyExitStmt;
    };

    /**
     * @brief 包含多种条件分支表达式
     * 如果、如果真、判断
     */
    struct IfStmt : public Statement {
        static const NodeType node_type = NodeType::kNTyIfStmt;
        // 选择分支，每个pair第一个元素为测试表达式，第二个元素为相应的语句块
        std::vector<std::pair<ExpressionPtr, StatementPtr>> switches_;
        // 默认分支
        StatementPtr default_statement_ = nullptr;
    };

    /**
     * @brief 循环语句基本结构
     */
    struct LoopStatement : public Statement {
        StatementPtr loop_body_ = nullptr;
    };

    /**
     * @brief 描述先判断后执行的While-Loop结构
     */
    struct WhileStmt : public LoopStatement {
        static const NodeType node_type = NodeType::kNTyWhileStmt;
        ExpressionPtr condition_ = nullptr;
    };

    /**
     * @brief 描述计次循环的范围迭代循环结构
     */
    struct RangeForStmt : public LoopStatement {
        static const NodeType node_type = NodeType::kNTyRangeForStmt;
        ExpressionPtr range_size_ = nullptr;
        HierarchyIdentifierPtr loop_vari_ = nullptr;

        // === 下面是经过语义分析后的数据 ===

    };

    /**
     * @brief 描述计步循环的范围迭代循环结构
     */
    struct ForStmt : public LoopStatement {
        static const NodeType node_type = NodeType::kNTyForStmt;
        ExpressionPtr start_value_ = nullptr;
        ExpressionPtr stop_value_ = nullptr;
        ExpressionPtr step_value_ = nullptr;
        HierarchyIdentifierPtr loop_vari_ = nullptr;

        // === 下面是经过语义分析后的数据 ===

    };

    /**
     * @brief 描述先执行后判断的Do-While循环结构
     */
    struct DoWhileStmt : public LoopStatement {
        static const NodeType node_type = NodeType::kNTyDoWhileStmt;
        ExpressionPtr conditon_ = nullptr;
    };

    /**
     * @brief 语句块
     */
    struct StatementBlock : public Statement {
        static const NodeType node_type = NodeType::kNTyStatementBlock;
        std::vector<StatementPtr> statements_;
    };

    /**
     * @brief 表达式基类
     * 在这里，表达式被视作一种特殊的语句。
     */
    struct Expression : public Statement {
        static const NodeType node_type = NodeType::kNTyExpression;

        // === 下面是经过语义分析后的数据 ===

        // 该表达式的类型
        TypeDeclPtr expression_type_ = nullptr;
    };

    enum class IdentifierUsage {
        kUnknown,
        kAsLeftValue,
        kAsRightValue,
    };

    /**
     * @brief 多层名称序列
     * 该节点用于表示通过英文句点`.'连接的多层引用语法结构
     */
    struct HierarchyIdentifier : public Expression {
        static const NodeType node_type = NodeType::kNTyHierarchyIdentifier;
        std::vector<NameComponentPtr> name_components_;

        // === 下面是经过语义分析后的数据 ===

        // 该层次名称所指向的类型
        TypeDeclPtr qualified_type_ = nullptr;

        IdentifierUsage identifier_usage_ = IdentifierUsage::kUnknown;
    };

    /**
     * @brief 单个命名组件
     */
    struct NameComponent : public Expression {
        static const NodeType node_type = NodeType::kNTyNameComponent;

        IdentifierUsage identifier_usage_ = IdentifierUsage::kUnknown;

        NameComponentPtr forward_name_component_ = nullptr;

        NameComponentPtr backward_name_component_ = nullptr;
    };

    /**
     * @brief 普通名称组件
     */
    struct Identifier : public NameComponent {
        static const NodeType node_type = NodeType::kNTyIdentifier;
        // 引用名
        TString name_;

        // === 下面是经过语义分析后的数据 ===

        BaseVariDeclPtr reference_ = nullptr;
        FunctorDeclPtr function_ref_ = nullptr;
    };

    /**
     * @brief 数组引用组件
     */
    struct ArrayIndex : public NameComponent {
        static const NodeType node_type = NodeType::kNTyArrayIndex;
        // 索引对象
        NameComponentPtr base_ = nullptr;
        // 索引表达式
        ExpressionPtr index_ = nullptr;
    };

    /**
     * @brief 函数调用组件
     */
    struct FunctionCall : public NameComponent {
        static const NodeType node_type = NodeType::kNTyFunctionCall;
        NameComponentPtr function_name_ = nullptr;
        std::vector<ExpressionPtr> arguments_;

        // === 下面是经过语义分析后的数据 ===

        FunctorDecl * functor_declare_ = nullptr;
    };

    /*
     * 类型转换
     */
    struct TypeConvert : public Expression {
        static const NodeType node_type = NodeType::kNTyTypeConvert;

        enum ConvertType { kCTImplicit, kCTExplicit };
        ConvertType convert_type_ = ConvertType::kCTImplicit;

        /*
         * 被转换表达式
         */
        ExpressionPtr from_expression_ = nullptr;
        /*
         * 源类型
         */
        TypeDeclPtr source_type_ = nullptr;
        /*
         * 目标类型
         */
        TypeDeclPtr target_type_ = nullptr;
    };

    /*
     * 有运算符的表达式
     */
    struct _OperatorExpression : public Expression {
        static const NodeType node_type = NodeType::kNTy_OperatorExpression;
        enum class OperatorType {
            kOptNone,
            kOptAdd, kOptSub, kOptMul, kOptDiv, kOptFullDiv, kOptMod,
            kOptEqual, kOptNotEqual, kOptGreatThan, kOptLessThan, kOptGreatEqual, kOptLessEqual, kOptLikeEqual,
            kOptAnd, kOptOr,
            kOptEND,
        };
        OperatorType operator_type_ = OperatorType::kOptNone;
        /*
         * 可选运算符：
         * 一元：-
         * 二元：* / \ % + - != == < > <= >= ?= && ||
         */
        TString operator_;
    };

    struct UnaryExpression : public _OperatorExpression {
        static const NodeType node_type = NodeType::kNTyUnaryExpression;
        ExpressionPtr operand_value_ = nullptr;
    };

    struct BinaryExpression : public _OperatorExpression {
        static const NodeType node_type = NodeType::kNTyBinaryExpression;
        ExpressionPtr lhs_ = nullptr;
        ExpressionPtr rhs_ = nullptr;
    };

    /**
     * @brief 值基类
     * 值基类可以表示所有的常量
     */
    struct Value : public Expression {
        static const NodeType node_type = NodeType::kNTyValue;
    };

    struct ValueOfDataSet : public Value {
        static const NodeType node_type = NodeType::kNTyValueOfDataSet;
        std::vector<ExpressionPtr> elements_;
    };

    struct ValueOfDatetime : public Value {
        static const NodeType node_type = NodeType::kNTyValueOfDatetime;
        time_t time_ = 0;
    };

    struct ResourceRefExpression : public Expression {
        static const NodeType node_type = NodeType::kNTyResourceRefExpression;
        TString resource_name_;
    };

    struct FuncAddrExpression : public Expression {
        static const NodeType node_type = NodeType::kNTyFuncAddrExpression;
        TString function_name_;

        // === 下面是经过语义分析后的数据 ===

        FunctorDeclPtr functor_declare_ = nullptr;
    };

    struct ValueOfBool : public Value {
        static const NodeType node_type = NodeType::kNTyValueOfBool;
        bool value_ = false;
    };

    struct ValueOfDecimal : public Value {
        static const NodeType node_type = NodeType::kNTyValueOfDecimal;
        union {
            int int_val_ = 0;
            float float_val_;
        };
        enum type { kInt, kFloat } type_ = type::kInt;
    };

    struct ValueOfString : public Value {
        static const NodeType node_type = NodeType::kNTyValueOfString;
        TString string_literal_;
    };

    /**
     * @brief 翻译单元
     * 翻译单元结构将所有可编译数据打包，提供一致的索引方式，同时应对可能的名称冲突。
     */
    struct TranslateUnit : public Node {
        static const NodeType node_type = NodeType::kNTyTranslateUnit;
        // 语法版本号
        unsigned int edition_ = 0;
        // 资源文件列表（包括全局变量定义、数据结构定义、类模块定义、DLL接口定义、子程序集合）
        std::vector<SourceFilePtr> source_file_;

        // === 下面是经过语义分析后的数据 ===

        // 全局类型索引表
        ordered_map<StringRef, TypeDeclPtr> global_type_;
        // 全局变量索引表
        ordered_map<StringRef, GlobalVariableDeclPtr> global_variables_;
        // 支持库引用列表
        std::set<StringRef> libraries_list_;
        // 程序集索引表
        ordered_map<StringRef, ProgSetDeclPtr> program_sets_;
        // 函数定义表
        ordered_map<StringRef, FunctionDeclPtr> function_decls_;
        // DLL函数声明表
        ordered_map<StringRef, APICommandDeclPtr> dll_declares_;
        // 函数定义表和DLL声明表的合并
        // TODO: 是否要将上面两个逗逼玩意干掉
        ordered_map<StringRef, FunctorDeclPtr> functor_declares_;
        // 程序入口
        FunctorDeclPtr main_entry_ = nullptr;
    };

    struct NodeWarp {
        NodePtr node_;
        explicit NodeWarp(NodePtr node) {
            node_ = node;
        }

        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Node, T>>>
        operator T *() {
            return dynamic_cast<T *>(this->node_);
        }
    };

    template<typename NodeTy, typename ... Args, typename = typename std::enable_if<std::is_base_of<Node, NodeTy>::value>::type>
    NodeTy *CreateNode(ASTContext *ast_context, Args ... args) {
        NodeTy *node = new NodeTy(args...);
        Node *base_node = node;
        base_node->node_id_ = ast_context->GetNodeIndex();
        base_node->node_type_ = NodeTy::node_type;
        base_node->ast_context_ = ast_context;
        return node;
    }
}

#endif //REXLANG_NODEDECL_H
