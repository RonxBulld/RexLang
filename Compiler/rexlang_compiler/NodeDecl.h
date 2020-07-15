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

    class Node;

    // Project

    class TranslateUnit;

    // File

    typedef class SourceFile* SourceFilePtr;
    typedef class ProgramSetFile* ProgramSetFilePtr;
    typedef class GlobalVariableFile* GlobalVariableFilePtr;
    typedef class DataStructureFile* DataStructureFilePtr;
    typedef class DllDefineFile* DllDefineFilePtr;

    // Declare

    // Type declare

    typedef class Decl* DeclPtr;
    typedef class TagDecl* TagDeclPtr;
    typedef class TypeDecl* TypeDeclPtr;
    typedef class VariTypeDecl* VariTypeDeclPtr;
    typedef class StructureDecl* StructureDeclPtr;
    typedef class BuiltinTypeDecl* BuiltinTypeDeclPtr;
    typedef class ArrayDecl* ArrayDeclPtr;

    // Entity declare

    typedef class BaseVariDecl* BaseVariDeclPtr;
    typedef class VariableDecl* VariableDeclPtr;
    typedef class GlobalVariableDecl* GlobalVariableDeclPtr;
    typedef class LocalVariableDecl* LocalVariableDeclPtr;
    typedef class ParameterDecl* ParameterDeclPtr;
    typedef class MemberVariableDecl* MemberVariableDeclPtr;
    typedef class FileVariableDecl* FileVariableDeclPtr;
    typedef class FunctorDecl* FunctorDeclPtr;
    typedef class FunctionDecl* FunctionDeclPtr;
    typedef class ProgSetDecl* ProgSetDeclPtr;
    typedef class APICommandDecl* APICommandDeclPtr;

    // Statement

    typedef class Statement* StatementPtr;
    typedef class IfStmt* IfStmtPtr;
    typedef class StatementBlock* StatementBlockPtr;
    typedef class LoopStatement* LoopStatementPtr;
    typedef class WhileStmt* WhileStmtPtr;
    typedef class RangeForStmt* RangeForStmtPtr;
    typedef class ForStmt* ForStmtPtr;
    typedef class DoWhileStmt* DoWhileStmtPtr;
    typedef class AssignStmt* AssignStmtPtr;
    typedef class ControlStmt *ControlStmtPtr;
    typedef class LoopControlStmt *LoopControlStmtPtr;
    typedef class ContinueStmt *ContinueStmtPtr;
    typedef class BreakStmt *BreakStmtPtr;
    typedef class ReturnStmt *ReturnStmtPtr;
    typedef class ExitStmt *ExitStmtPtr;

    // Expression

    typedef class Expression* ExpressionPtr;
    typedef class HierarchyIdentifier* HierarchyIdentifierPtr;
    typedef class NameComponent* NameComponentPtr;
    typedef class Identifier* IdentifierPtr;
    typedef class ArrayIndex* ArrayIndexPtr;
    typedef class FunctionCall* FunctionCallPtr;
    typedef class UnaryExpression* UnaryExpressionPtr;
    typedef class BinaryExpression* BinaryExpressionPtr;
    typedef class _OperatorExpression* _OperatorExpressionPtr;
    typedef class TypeConvert* TypeConvertPtr;

    // Value

    typedef class Value* ValuePtr;
    typedef class ValueOfDataSet* ValueOfDataSetPtr;
    typedef class ValueOfDatetime* ValueOfDatetimePtr;
    typedef class FuncAddrExpression* FuncAddrExpressionPtr;
    typedef class ResourceRefExpression* ResourceRefExpressionPtr;
    typedef class ValueOfBool* ValueOfBoolPtr;
    typedef class ValueOfDecimal* ValueOfDecimalPtr;
    typedef class ValueOfString* ValueOfStringPtr;

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
        kNTyVariTypeDecl,
        kNTyBuiltinTypeDecl,
        kNTyArrayDecl,
        kNTyStructureDecl,
        kNTyFunctorDecl,
        kNTyFunctionDecl,
        kNTyProgSetDecl,
        kNTyAPICommandDecl,
        kNTyStatement,
        kNTyIfStmt,
        kNTyStatementBlock,
//        kNTyLoopStatement,
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

    /*
     * 运算符类型
     */
    class OperatorType {
    public:
        enum class Opt {
            kOptNone,
            kOptAdd, kOptSub, kOptMul, kOptDiv, kOptFullDiv, kOptMod,
            kOptEqual, kOptNotEqual, kOptGreatThan, kOptLessThan, kOptGreatEqual, kOptLessEqual, kOptLikeEqual,
            kOptAnd, kOptOr,
            kOptEND,
        };

        OperatorType(Opt opt) ;

    public:

        /***********************************************
         * 基本符号特性判定
         ***********************************************/

        bool IsUnaryOpt      () const ;
        bool IsBinaryOpt     () const ;
        bool IsNumericalOpt  () const ;
        bool IsEqualOrNotOpt () const ;
        bool IsRelationalOpt () const ;
        bool IsExtraRelOpt   () const ;
        bool IsBooleanOpt    () const ;

    public:

    public:
        Opt GetOperate() const;

    private:
        Opt opt_;
    };

    /**
     * @brief 节点基类
     */
    class Node {
    private:
        size_t node_id_          = 0;
        ASTContext *ast_context_ = nullptr;
        Node *parent_node_       = nullptr;
        NodeType node_type_      = NodeType::kNTyBadType;
        size_t location_start_   = 0;
        size_t location_end_     = 0;

    public:
        template<typename NodeTy, typename ... Args, typename = typename std::enable_if<std::is_base_of<Node, NodeTy>::value>::type>
        static NodeTy *Create(ASTContext *ast_context, Args && ... args) {
            NodeTy *node = new NodeTy(args...);
            node->node_id_     = ast_context->GetNodeIndex();
            node->node_type_   = NodeTy::GetClassId();
            node->ast_context_ = ast_context;
            return node;
        }

    public:
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

        virtual ~Node() = default;

        TranslateUnit * getTranslateUnit    () const { return this->ast_context_->GetTranslateUnit(); }
        ASTContext *    getAstContext       () const { return this->ast_context_; }
    };

    /**
     * @brief 资源文件基类
     */
    class SourceFile : public Node {
        enum FileType {kProgramSetFile, kGlobalVariableFile, kDataStructureFile, kDllDefineFile} file_type_;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 函数声明文件
     */
    class ProgramSetFile : public SourceFile {
        std::vector<TString> libraries_;
        ProgSetDeclPtr program_set_declares_ = nullptr;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 全局变量声明文件
     */
    class GlobalVariableFile : public SourceFile {
        ordered_map<StringRef, GlobalVariableDeclPtr> global_variable_map_;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 数据结构定义文件
     */
    class DataStructureFile : public SourceFile {
        ordered_map<StringRef, StructureDeclPtr> structure_decl_map_;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief DLL函数接口声明文件
     */
    class DllDefineFile : public SourceFile {
        ordered_map<StringRef, APICommandDeclPtr> dll_declares_;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 定义基类
     */
    class Decl : public Node {

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 带有名称和注释的命名定义基本结构
     */
    class TagDecl : public Decl {
        // 定义名称
        TString name_;
        // 注释
        TString comment_;

    public:
        void                SetName     (const TString &name)   { name_ = name; }
        const TString &     GetName     () const                { return name_; }
        const StringRef &   GetNameRef  () const                { return name_.string_; }

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述成员变量、全局变量、局部变量、参数等带有类型的基本结构
     */
    class BaseVariDecl : public TagDecl {
        // 类型名称
        TString type_name_;
        // === 下面是经过语义分析后的数据 ===

        // 类型指针
        VariTypeDecl *vari_type_decl_ = nullptr;

    public:
        virtual VariTypeDecl *GetTypeDecl() const ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述参数
     */
    class ParameterDecl : public BaseVariDecl {
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
        bool is_reference_ = false;

        /*
         * 是否可空
         */
        bool is_nullable = false;

        /*
         * 是否数组
         */
        bool is_array = false;

    public:
        static const NodeType GetClassId () ;

    public:
        bool ShouldBeReference() const ;    // 判断该参数是否应该以引用的方式传递，如果是数组、字符串、字节集、自定义类型或 is_reference 为真时则为真
    };

    /*
     * 描述成员变量、全局变量、局部变量、文件变量
     */
    class VariableDecl : public BaseVariDecl {
        // 变量属性
        std::vector<TString> attributes_;

        // 维度的文本描述
        TString dimension_;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述全局变量
     */
    class GlobalVariableDecl : public VariableDecl {
        // 访问级别的文本描述
        TString access_;

        // === 下面是经过语义分析后的数据 ===

        /*
         * 访问级别
         */
        AccessLevel access_level_ = AccessLevel::kALPublic;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述成员变量
     */
    class MemberVariableDecl : public VariableDecl {

        // === 下面是经过语义分析后的数据 ===

        size_t index_of_struct_ = 0;

        bool is_reference_ = false;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述文件变量
     */
    class FileVariableDecl : public VariableDecl {
    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述局部变量
     */
    class LocalVariableDecl : public VariableDecl {
        // === 下面是经过语义分析后的数据 ===

        /*
         * 是否为静态
         */
        bool is_static_ = false;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 类型定义分支
     */
    class TypeDecl : public TagDecl {
    public:
        static const NodeType GetClassId () ;

    public:

    };

    class VariTypeDecl : public TypeDecl {
    public:
        static const NodeType GetClassId () ;

    public:

        /********************************************************
         * 基本类型工具
         ********************************************************/

        [[nodiscard]] virtual bool    IsVoidType          () const ;   // 是否为空类型
        [[nodiscard]] virtual bool    IsCommonType        () const ;   // 是否为通用型
        [[nodiscard]] virtual bool    IsCharType          () const ;   // 是否为字节型
        [[nodiscard]] virtual bool    IsIntegerType       () const ;   // 是否为整数型
        [[nodiscard]] virtual bool    IsFloatType         () const ;   // 是否为小数型
        [[nodiscard]] virtual bool    IsBoolType          () const ;   // 是否为逻辑型
        [[nodiscard]] virtual bool    IsStringType        () const ;   // 是否为文本型
        [[nodiscard]] virtual bool    IsDataSetType       () const ;   // 是否为字节集
        [[nodiscard]] virtual bool    IsShortType         () const ;   // 是否为短整型
        [[nodiscard]] virtual bool    IsLongType          () const ;   // 是否为长整型
        [[nodiscard]] virtual bool    IsDatetimeType      () const ;   // 是否为日期时间型
        [[nodiscard]] virtual bool    IsFuncPtrType       () const ;   // 是否为子程序指针
        [[nodiscard]] virtual bool    IsDoubleType        () const ;   // 是否为双精度小数型
        [[nodiscard]] virtual bool    IsStructType        () const ;   // 是否为自定义结构体类型
        [[nodiscard]] virtual bool    IsExternBooleanType () const ;   // 类型是否具有扩展布尔性
        [[nodiscard]] virtual bool    IsNumerical         () const ;   // 类型是否具有数值性
        [[nodiscard]] virtual bool    IsIntegerClass      () const ;   // 类型是否整数族
        [[nodiscard]] virtual bool    IsArray             () const ;   // 类型是否数组

        /********************************************************
         * 高级类型工具
         ********************************************************/

        [[nodiscard]] virtual bool       IsIndexable         () const ;   // 类型是否可索引
        [[nodiscard]] virtual bool       IsFixedDimensions   () const ;   // 维度数量是否可变
        [[nodiscard]] virtual TypeDecl * GetIndexedElementTy () const ;   // 获取索引的类型

        [[nodiscard]] virtual std::vector<size_t> GetDimensions () const ;  // 获取定义的索引维度

        [[nodiscard]] virtual bool       IsUnyOptValid       (OperatorType opt) const ;                      // 判断一元计算有效性
        [[nodiscard]] virtual bool       IsBinOptValid       (OperatorType opt, VariTypeDecl *otherType) const ; // 判断二元计算有效性
        [[nodiscard]] virtual bool       IsAssginFromValid   (TypeDecl *fromType) const ;                    // 判断赋值有效性

    };

    // 内置类型枚举
    enum class EnumOfBuiltinType {
        kBTypeVoid,        // 空
        kBTypeCommon,      // 通用型
        kBTypeChar,        // 字节型
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
        kBTypeEND,
    };

    /*
     * 内置类型定义
     */
    class BuiltinTypeDecl : public VariTypeDecl {
    protected:
        BuiltinTypeDecl(const char *typeName, EnumOfBuiltinType typeEnum) ;

    public:
        virtual EnumOfBuiltinType GetBuiltinType() const = 0;

    public:
        bool    IsExternBooleanType () const override;
        bool    IsNumerical         () const override;
        bool    IsIntegerClass      () const override;

        virtual const char *GetTypeText () const = 0;

    public:
        static const NodeType GetClassId () ;
    };

    class BuiltinVoidType : public BuiltinTypeDecl {
    public:
        BuiltinVoidType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsVoidType      () const override ;
        const char *        GetTypeText     () const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinCommonType : public BuiltinTypeDecl {
    public:
        BuiltinCommonType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsCommonType    () const override ;
        const char *        GetTypeText     () const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinCharType : public BuiltinTypeDecl {
    public:
        BuiltinCharType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsCharType      () const override ;
        const char *        GetTypeText     () const override ;
        bool                IsBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinIntegerType : public BuiltinTypeDecl {
    public:
        BuiltinIntegerType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsIntegerType   () const override ;
        const char *        GetTypeText     () const override ;
        bool                IsBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinFloatType : public BuiltinTypeDecl {
    public:
        BuiltinFloatType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsFloatType     () const override ;
        const char *        GetTypeText     () const override ;
        bool                IsBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinBoolType : public BuiltinTypeDecl {
    public:
        BuiltinBoolType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsBoolType      () const override ;
        const char *        GetTypeText     () const override ;
        bool                IsBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinStringType : public BuiltinTypeDecl {
    public:
        BuiltinStringType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType          () const override ;
        bool                IsStringType            () const override ;
        const char *        GetTypeText             () const override ;
        bool                IsIndexable             () const override ;
        bool                IsFixedDimensions       () const override ;
        std::vector<size_t> GetDimensions           () const override ;
        bool                IsBinOptValid           (OperatorType opt, VariTypeDecl *otherType) const override ;

        TypeDecl *          GetIndexedElementTy     () const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinDataSetType : public BuiltinTypeDecl {
    public:
        BuiltinDataSetType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType          () const override ;
        bool                IsDataSetType           () const override ;
        const char *        GetTypeText             () const override ;
        bool                IsIndexable             () const override ;
        bool                IsFixedDimensions       () const override ;
        std::vector<size_t> GetDimensions           () const override ;
        bool                IsBinOptValid           (OperatorType opt, VariTypeDecl *otherType) const override ;

        TypeDecl *          GetIndexedElementTy     () const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinShortType : public BuiltinTypeDecl {
    public:
        BuiltinShortType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsShortType     () const override ;
        const char *        GetTypeText     () const override ;
        bool                IsBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinLongType : public BuiltinTypeDecl {
    public:
        BuiltinLongType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsLongType      () const override ;
        const char *        GetTypeText     () const override ;
        bool                IsBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinDatetimeType : public BuiltinTypeDecl {
    public:
        BuiltinDatetimeType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsDatetimeType  () const override ;
        const char *        GetTypeText     () const override ;
        bool                IsBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinFuncPtrType : public BuiltinTypeDecl {
    public:
        BuiltinFuncPtrType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsFuncPtrType   () const override ;
        const char *        GetTypeText     () const override ;
        bool                IsBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinDoubleType : public BuiltinTypeDecl {
    public:
        BuiltinDoubleType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                IsDoubleType    () const override ;
        const char *        GetTypeText     () const override ;
        bool                IsBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    /*
     * 数据结构定义
     */
    class StructureDecl : public VariTypeDecl {
        TString access_;
        ordered_map<StringRef, MemberVariableDeclPtr> members_;
    public:
        static const NodeType GetClassId () ;

    public:
        bool            IsBinOptValid       (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool            IsStructType        () const override ;
        BaseVariDecl *  GetElementWithName  (const StringRef &variable_name);
    };

    /*
     * 数组类型
     */
    class ArrayDecl : public VariTypeDecl {
        TString base_type_str;

        // === 下面是经过语义分析后的数据 ===

        TypeDeclPtr base_type_ = nullptr;
        // 数组维度定义，如果不是数组，则为空
        std::vector<size_t> dimensions_;

    public:
        bool                IsIndexable             () const override ;
        bool                IsFixedDimensions       () const override ;
        bool                IsArray                 () const override ;
        TypeDecl *          GetIndexedElementTy     () const override ;
        std::vector<size_t> GetDimensions           () const override ;
        bool                IsBinOptValid           (OperatorType opt, VariTypeDecl *otherType) const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 具有函数性的定义
     * 包含子函数定义和DLL函数定义
     */
    class FunctorDecl : public TypeDecl {
        // 返回值类型名
        TString return_type_name_;
        // 参数列表
        std::vector<ParameterDecl *> parameters_;

        // === 下面是经过语义分析后的数据 ===

        // 返回值类型
        TypeDeclPtr return_type_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    public:
        ParameterDecl * GetParameterAt(unsigned idx) const ;

        virtual bool    IsStaticLibraryAPI  () const = 0;
        virtual bool    IsDynamicLibraryAPI () const = 0;
    };

    /**
     * @brief 子程序/函数定义
     */
    class FunctionDecl : public FunctorDecl {
        // 访问级别
        TString access_;
        // 局部变量列表
        ordered_map<StringRef, LocalVariableDeclPtr> local_vari_;
        // 语句列表
        StatementBlockPtr statement_list_ = nullptr;

        // === 下面是经过语义分析后的数据 ===

        // 所属程序集
        ProgSetDeclPtr super_set_ = nullptr;

    public:
        static const NodeType GetClassId () ;

        bool    IsStaticLibraryAPI  () const override ;
        bool    IsDynamicLibraryAPI () const override ;
    };

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
    class APICommandDecl : public FunctorDecl {
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

    public:
        static const NodeType GetClassId () ;

        bool    IsStaticLibraryAPI  () const override ;
        bool    IsDynamicLibraryAPI () const override ;
    };

    /**
     * @brief 程序集定义
     */
    class ProgSetDecl : public TagDecl {
        TString base_;
        TString access_;
        ordered_map<StringRef, FileVariableDeclPtr> file_static_variables_;
        ordered_map<StringRef, FunctionDeclPtr> function_decls_;

    public:
        static const NodeType GetClassId () ;
    };

    enum class ExprUsage {
        kUnknown,
        kAsLeftValue,
        kAsRightValue,
    };

    /**
     * @brief 语句基类
     */
    class Statement : public Node {
    protected:
        virtual ExprUsage GetSubExprLRType(const Expression *expr) const = 0;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 赋值语句
     */
    class AssignStmt : public Statement {
        HierarchyIdentifierPtr lhs_ = nullptr;
        ExpressionPtr rhs_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 控制语句
     */
    class ControlStmt : public Statement {
    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 循环控制语句
     */
    class LoopControlStmt : public ControlStmt {
        // === 下面是经过语义分析后的数据 ===

        // 所控制的循环语句
        LoopStatementPtr loop_statement_ = nullptr;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 到循环尾
     */
    class ContinueStmt : public LoopControlStmt {
    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 跳出循环
     */
    class BreakStmt : public LoopControlStmt {
    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 返回
     */
    class ReturnStmt : public ControlStmt {
        ExpressionPtr return_value_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 结束
     */
    class ExitStmt : public ControlStmt {
    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 包含多种条件分支表达式
     * 如果、如果真、判断
     */
    class IfStmt : public Statement {
        // 选择分支，每个pair第一个元素为测试表达式，第二个元素为相应的语句块
        std::vector<std::pair<ExpressionPtr, StatementPtr>> switches_;
        // 默认分支
        StatementPtr default_statement_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 循环语句基本结构
     */
    class LoopStatement : public Statement {
        StatementPtr loop_body_ = nullptr;
    };

    /**
     * @brief 描述先判断后执行的While-Loop结构
     */
    class WhileStmt : public LoopStatement {
        ExpressionPtr condition_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 描述计次循环的范围迭代循环结构
     */
    class RangeForStmt : public LoopStatement {
        ExpressionPtr range_size_ = nullptr;
        HierarchyIdentifierPtr loop_vari_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 描述计步循环的范围迭代循环结构
     */
    class ForStmt : public LoopStatement {
        ExpressionPtr start_value_ = nullptr;
        ExpressionPtr stop_value_ = nullptr;
        ExpressionPtr step_value_ = nullptr;
        HierarchyIdentifierPtr loop_vari_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 描述先执行后判断的Do-While循环结构
     */
    class DoWhileStmt : public LoopStatement {
        ExpressionPtr conditon_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 语句块
     */
    class StatementBlock : public Statement {
        std::vector<StatementPtr> statements_;

    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 表达式基类
     * 在这里，表达式被视作一种特殊的语句。
     */
    class Expression : public Statement {
    public:
        static const NodeType GetClassId () ;

        // === 下面是经过语义分析后的数据 ===

    private:
        // 该表达式的类型
        TypeDeclPtr expression_type_ = nullptr;

        virtual TypeDecl *CheckExpressionInternal() = 0;

    public:
        TypeDecl *CheckExpression();    // 检查表达式并推算类型
        TypeDecl *GetExpressionTy() const;
        ExprUsage GetLRType() const;    // 获取表达式自身的引用类型，依赖父节点的 GetSubExprLRType 实现
    };

    /**
     * @brief 多层名称序列
     * 该节点用于表示通过英文句点`.'连接的多层引用结构
     */
    class HierarchyIdentifier : public Expression {
    public:
        static const NodeType GetClassId () ;

    private:
        std::vector<NameComponentPtr> name_components_;

        // === 下面是经过语义分析后的数据 ===
    public:
        // 该层次名称所指向的类型
        TypeDeclPtr qualified_type_ = nullptr;

    public:
        void AppendComponent(NameComponent *component);
        TypeDecl *CheckExpressionInternal() override ;
        TypeDecl *GetQualifiedType() ;  // 获取层次名称描述的准确类型
        TypeDecl *EvalComponentsType();

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    /**
     * @brief 单个命名组件
     */
    class NameComponent : public Expression {
    public:
        static const NodeType GetClassId () ;

    private:
        NameComponentPtr forward_name_component_ = nullptr;
        NameComponentPtr backward_name_component_ = nullptr;

    public:
        void            SetForward  (NameComponent *component) ;
        void            SetBackward (NameComponent *component) ;
        NameComponent * Forward     () const ;
        NameComponent * Backward    () const ;

        virtual TypeDecl *      EvalBaseNameComponentType   () = 0;
    };

    /**
     * @brief 普通名称组件
     */
    class Identifier : public NameComponent {
        // 引用名
        TString name_;

        // === 下面是经过语义分析后的数据 ===

        BaseVariDeclPtr reference_ = nullptr;
        FunctorDeclPtr function_ref_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *      EvalBaseNameComponentType   () override;
    };

    /**
     * @brief 数组引用组件
     */
    class ArrayIndex : public NameComponent {
        // 索引对象
        NameComponentPtr base_ = nullptr;
        // 索引表达式
        ExpressionPtr index_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *      EvalBaseNameComponentType   () override;

        /*
         * 获取数组索引组件的真实基对象
         * 例如：
         * arrayIndex[1][2][3][1]->arrayIndex
         * func()[1][3]->func()
         */
        NameComponent *GetIndexBase() const;

        /*
         * 获取可索引类型的元素类型
         * 例如：
         * 整数型数组返回整数型
         * 字节集返回字节型
         */
        TypeDecl * GetElementTy() const ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override;
    };

    /**
     * @brief 函数调用组件
     */
    class FunctionCall : public NameComponent {
        NameComponentPtr function_name_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    private:
        std::vector<ExpressionPtr> arguments_;

    public:
        // === 下面是经过语义分析后的数据 ===

        FunctorDecl * functor_declare_ = nullptr;

    public:
        TypeDecl *CheckExpressionInternal   () override ;
        TypeDecl *EvalBaseNameComponentType () override ;

        FunctorDecl *   GetFunctionDeclare  () const ;

        bool    IsArgument      (Expression *expr) const ;          // 判定表达式是否为实参，依赖 IndexOfArgument 实现
        bool    IsArgument      (const Expression *expr) const ;    // 判定表达式是否为实参，依赖 IndexOfArgument 实现
        int     IndexOfArgument (Expression *expr) const ;          // 若表达式是实参则返回是第几个参数，否则返回-1
        int     IndexOfArgument (const Expression *expr) const ;    // 若表达式是实参则返回是第几个参数，否则返回-1

    protected:
        ExprUsage GetSubExprLRType          (const Expression *expr) const override ;
    };

    /*
     * 类型转换
     */
    class TypeConvert : public Expression {
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

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *CheckExpressionInternal() override ;
    };

    /*
     * 有运算符的表达式
     */
    class _OperatorExpression : public Expression {
        OperatorType operator_type_ = OperatorType::Opt::kOptNone;
        /*
         * 可选运算符：
         * 一元：-
         * 二元：* / \ % + - != == < > <= >= ?= && ||
         */
        TString operator_;

    public:
        static const NodeType GetClassId () ;

    public:
        const OperatorType &GetOpt() const ;
    };

    class UnaryExpression : public _OperatorExpression {
        ExpressionPtr operand_value_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    public:
        VariTypeDecl *CheckExpressionInternal   () override ;

    protected:
        ExprUsage GetSubExprLRType          (const Expression *expr) const override ;
    };

    class BinaryExpression : public _OperatorExpression {
        ExpressionPtr lhs_ = nullptr;
        ExpressionPtr rhs_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    public:
        bool            IsBinaryOperateValid         () const;   // 检查二元运算是否合法，该断言主要判断二元表达式中左右子式是否可以通过运算符计算
        VariTypeDecl *  GetBinaryOperateUpgradeType  () const;   // 获取二元表达式提升后的类型

    protected:
        ExprUsage   GetSubExprLRType                (const Expression *expr) const override ;

    public:
        VariTypeDecl *CheckExpressionInternal() override ;
    };

    class ResourceRefExpression : public Expression {
        TString resource_name_;

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *CheckExpressionInternal() override ;
    };

    class FuncAddrExpression : public Expression {
        TString function_name_;

        // === 下面是经过语义分析后的数据 ===

        FunctorDeclPtr functor_declare_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *CheckExpressionInternal() override ;
    };

    /**
     * @brief 值基类
     * 值基类可以表示所有的常量
     */
    class Value : public Expression {
    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    class ValueOfDataSet : public Value {
        std::vector<ExpressionPtr> elements_;

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *CheckExpressionInternal() override ;
    };

    class ValueOfDatetime : public Value {
        time_t time_ = 0;

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *CheckExpressionInternal() override ;
    };

    class ValueOfBool : public Value {
        bool value_ = false;

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *CheckExpressionInternal() override ;
    };

    class ValueOfDecimal : public Value {
        union {
            int int_val_ = 0;
            float float_val_;
        };
        enum type { kInt, kFloat } type_ = type::kInt;

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *CheckExpressionInternal() override ;
    };

    class ValueOfString : public Value {
        TString string_literal_;

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *CheckExpressionInternal() override ;
    };

    /**
     * @brief 翻译单元
     * 翻译单元结构将所有可编译数据打包，提供一致的索引方式，同时应对可能的名称冲突。
     */
    class TranslateUnit : public Node {
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

    public:
        static const NodeType GetClassId () ;

    private:
        ordered_map<EnumOfBuiltinType, BuiltinTypeDecl *> builtin_type_map_;

    public:
        bool RegistBuiltinType(BuiltinTypeDecl *builtinTypeDecl);
        bool InitBuiltinTypes();

    public:
        BuiltinTypeDecl *       getBuiltinTy    (EnumOfBuiltinType enumOfBuiltinType) const ;
        BuiltinVoidType *       getVoidTy       () const ;
        BuiltinCommonType *     getCommonTy     () const ;
        BuiltinCharType *       getCharTy       () const ;
        BuiltinIntegerType *    getIntegerTy    () const ;
        BuiltinFloatType *      getFloatTy      () const ;
        BuiltinBoolType *       getBoolTy       () const ;
        BuiltinStringType *     getStringTy     () const ;
        BuiltinDataSetType *    getDataSetTy    () const ;
        BuiltinShortType *      getShortTy      () const ;
        BuiltinLongType *       getLongTy       () const ;
        BuiltinDatetimeType *   getDatetimeTy   () const ;
        BuiltinFuncPtrType *    getFuncPtrTy    () const ;
        BuiltinDoubleType *     getDoubleTy     () const ;

    };

    class NodeWarp {
        Node * node_;
        explicit NodeWarp(Node * node) {
            node_ = node;
        }

        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Node, T>>>
        operator T *() {
            return dynamic_cast<T *>(this->node_);
        }
    };

    template<typename NodeTy, typename ... Args, typename = typename std::enable_if<std::is_base_of<Node, NodeTy>::value>::type>
    NodeTy *CreateNode(ASTContext *ast_context, Args && ... args) {
        return Node::Create<NodeTy, Args...>(ast_context, args...);
    }
}

#endif //REXLANG_NODEDECL_H
