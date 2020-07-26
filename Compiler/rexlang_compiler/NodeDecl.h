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
#include "../../lite_util/ErrOr.h"
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
    class SemaContext;

    // Base

    class Node;

    // Project

    class TranslateUnit;

    // File

    class SourceFile;           class ProgramSetFile;           class GlobalVariableFile;
    class DataStructureFile;    class APIDeclareFile;           class ConstDeclareFile;

    // Declare

    // Type declare

    class Decl;                 class TagDecl;                  class TypeDecl;
    class VariTypeDecl;         class StructureDecl;            class BuiltinTypeDecl;
    class ArrayDecl;            class ConstDecl;

    // Entity declare

    class BaseVariDecl;         class VariableDecl;             class GlobalVariableDecl;
    class LocalVariableDecl;    class ParameterDecl;            class MemberVariableDecl;
    class FileVariableDecl;     class FunctorDecl;              class FunctionDecl;
    class ProgSetDecl;          class APICommandDecl;

    // Statement

    class Statement;            class IfStmt;                   class StatementBlock;
    class LoopStatement;        class WhileStmt;                class RangeForStmt;
    class ForStmt;              class DoWhileStmt;              class AssignStmt;
    class ControlStmt;          class LoopControlStmt;          class ContinueStmt;
    class BreakStmt;            class ReturnStmt;               class ExitStmt;

    // Expression

    class Expression;           class HierarchyIdentifier;      class NameComponent;
    class Identifier;           class ArrayIndex;               class FunctionCall;
    class UnaryExpression;      class BinaryExpression;         class _OperatorExpression;
    class TypeConvert;

    // Value

    class Value;                class ValueOfDataSet;           class ValueOfDatetime;
    class FuncAddrExpression;   class ResourceRefExpression;    class ValueOfBool;
    class ValueOfDecimal;       class ValueOfString;

    /**
     * @brief 节点类型枚举
     */
    typedef enum class NodeType {
        kNTyBadType,

        kNTyTranslateUnit,

        kNTySourceFile,
        kNTyProgramSetFile, kNTyGlobalVariableFile, kNTyDataStructureFile,
        kNTyAPIDeclareFile, kNTyConstDeclareFile,

        kNTyDecl,
        kNTyTagDecl, kNTyVariableDecl, kNTyBaseVariDecl, kNTyGlobalVariableDecl,
        kNTyParameterDecl, kNTyMemberVariableDecl, kNTyFileVariableDecl, kNTyLocalVariableDecl,
        kNTyTypeDecl, kNTyVariTypeDecl, kNTyBuiltinTypeDecl, kNTyArrayDecl,
        kNTyConstDecl, kNTyStructureDecl, kNTyFunctorDecl, kNTyFunctionDecl,
        kNTyProgSetDecl, kNTyAPICommandDecl,

        kNTyStatement,
        kNTyIfStmt, kNTyStatementBlock, kNTyWhileStmt, kNTyRangeForStmt,
        kNTyForStmt, kNTyDoWhileStmt, kNTyAssignStmt, kNTyControlStmt,
        kNTyLoopControlStmt, kNTyContinueStmt, kNTyBreakStmt, kNTyReturnStmt,
        kNTyExitStmt,

        kNTyExpression,
        kNTyHierarchyIdentifier, kNTyNameComponent, kNTyIdentifier, kNTyArrayIndex,
        kNTyFunctionCall, kNTyUnaryExpression, kNTyBinaryExpression, kNTy_OperatorExpression,

        kNTyTypeConvert, kNTyFuncAddrExpression, kNTyResourceRefExpression,

        kNTyValue,
        kNTyValueOfDataSet, kNTyValueOfDatetime, kNTyValueOfBool, kNTyValueOfDecimal,
        kNTyValueOfString,
    } NodeType;

    // 访问级别
    enum class AccessLevel {
        // 公开
        kALPublic,
        // 私有
        kALPrivate,
    };

    // 传值方式
    enum class ValueTransferMode {
        kVTMValue,      // 传值
        kVTMReference,  // 传址
    };

    // 运算符类型
    class OperatorType {
    public:
        enum class Opt {
            kOptNone,
            kOptAdd, kOptSub, kOptMul, kOptDiv, kOptFullDiv, kOptMod,
            kOptEqual, kOptNotEqual, kOptGreatThan, kOptLessThan, kOptGreatEqual, kOptLessEqual, kOptLikeEqual,
            kOptAnd, kOptOr,
            kOptEND,
        };

        explicit OperatorType(const Opt &opt) : opt_(opt) { }

    public:

        /***********************************************
         * 基本符号特性判定
         ***********************************************/

        [[nodiscard]] bool isUnaryOpt      () const ;   // -
        [[nodiscard]] bool isBinaryOpt     () const ;   // + - * / \ % == != > < >= <= ?= && ||
        [[nodiscard]] bool isNumericalOpt  () const ;   // + - * / \ %
        [[nodiscard]] bool isEqualOrNotOpt () const ;   // == !=
        [[nodiscard]] bool isRelationalOpt () const ;   // == != > < >= <=
        [[nodiscard]] bool isExtraRelOpt   () const ;   // == != > < >= <= ?=
        [[nodiscard]] bool isBooleanOpt    () const ;   // && ||

    public:
        const Opt &getOperate() const { return opt_; }

    private:
        Opt opt_;
    };

    /**
     * @brief 节点基类
     */
    class Node {
    private:
        size_t          node_id_            = 0;
        ASTContext *    ast_context_        = nullptr;
        Node *          parent_scope_       = nullptr;
        Node *          parent_node_        = nullptr;
        NodeType        node_type_          = NodeType::kNTyBadType;
        size_t          location_start_     = 0;
        size_t          location_end_       = 0;

    protected:
        void setParent(Node *parent) ;
        void setChild (Node *child)  ;

    public:
        virtual ~Node() = default;

    public:
        template<typename NodeTy, typename ... Args, typename = typename std::enable_if<std::is_base_of<Node, NodeTy>::value>::type>
        static NodeTy *Create(ASTContext *ast_context, Args && ... args) {
            NodeTy *node = new NodeTy(args...);

            node->node_id_      = ast_context->GetNodeIndex();
            node->node_type_    = NodeTy::GetClassId();
            node->ast_context_  = ast_context;
            node->parent_scope_ = ast_context->currentScope();

            return node;
        }

    public:
        template<typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        const Ty *as() const { return dynamic_cast<const Ty *>(this); }

        template<typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        Ty *as() { return dynamic_cast<Ty *>(this); }

        template<typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        bool is() const { return dynamic_cast<const Ty *>(this) != nullptr; }

    public:
        TranslateUnit * getTranslateUnit    () const ;
        ASTContext *    getAstContext       () const ;
        Node *          getNearstScope      () const ;
        Node *          getParent           () const ;

    public:
        void setLocation(const char *filename, size_t leftLine, size_t leftColumn, size_t rightLine, size_t rightColumn) ;

        const char *    getFileName   () const ;
        size_t          getLeftLine   () const ;
        size_t          getLeftColumn () const ;
        size_t          getRightLine  () const ;
        size_t          getRightColumn() const ;

    public:
        virtual TagDecl * findDeclWithNameString(const StringRef &name) const ;
        virtual void sematicAnalysisInternal(SemaContext &semaCtx) = 0;

    };

    /**
     * @brief 资源文件基类
     */
    class SourceFile : public Node {
    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

        virtual bool isProgramSetFile    () const ;
        virtual bool isGlobalVariableFile() const ;
        virtual bool isDataStructureFile () const ;
        virtual bool isAPIDeclareFile    () const ;
        virtual bool isConstDeclareFile  () const ;

        virtual void registResourceTo   (TranslateUnit *translateUnit) const = 0;
    };

    /**
     * @brief 函数声明文件
     */
    class ProgramSetFile : public SourceFile {
    private:
        std::vector<TString> libraries_;
        ProgSetDecl *        program_set_declares_ = nullptr;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        bool isProgramSetFile() const override ;
        void registResourceTo(TranslateUnit *translateUnit) const override ;

    public:
        void appendReferenceLibName (const TString &libraryName) ;
        void appendProgramSetDecl   (ProgSetDecl *progSetDecl) ;

        ProgSetDecl *                getProgramSetDecl() const ;
        const std::vector<TString> & getRefLibs       () const ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 全局变量声明文件
     */
    class GlobalVariableFile : public SourceFile {
    public:
        typedef ordered_map<StringRef, GlobalVariableDecl *> GlobalVariMapTy;

    private:
        GlobalVariMapTy global_variable_map_;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void                    appendGlobalVariableDecl(GlobalVariableDecl *globalVariableDecl) ;
        const GlobalVariMapTy & getGlobalVariMap        () const ;

    public:
        bool isGlobalVariableFile() const override ;
        void registResourceTo(TranslateUnit *translateUnit) const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 数据结构定义文件
     */
    class DataStructureFile : public SourceFile {
    public:
        typedef ordered_map<StringRef, StructureDecl *> StructDeclMapTy;

    private:
        StructDeclMapTy structure_decl_map_;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void                    appendStructureDecl(StructureDecl *structureDecl) ;
        const StructDeclMapTy & getTypes() const ;

    public:
        bool isDataStructureFile() const override ;
        void registResourceTo(TranslateUnit *translateUnit) const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief DLL函数接口声明文件
     */
    class APIDeclareFile : public SourceFile {
    public:
        typedef ordered_map<StringRef, APICommandDecl *> DllDefMapTy;

    private:
        DllDefMapTy api_declares_;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void                appendAPIDeclare(APICommandDecl *apiCommandDecl) ;
        const DllDefMapTy & getAPIDefMap () const ;

    public:
        bool isAPIDeclareFile() const override ;
        void registResourceTo(TranslateUnit *translateUnit) const override ;

    public:
        static const NodeType GetClassId () ;
    };

    class ConstDeclareFile : public SourceFile {
    public:
        typedef ordered_map<StringRef, ConstDecl *> ConstDeclMapTy;

    private:
        ConstDeclMapTy consts_declares_;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void                    appendConstDeclare(ConstDecl *constDecl) ;
        const ConstDeclMapTy &  getConstDeclMap   () const ;

    public:
        bool isConstDeclareFile() const override ;
        void registResourceTo(TranslateUnit *translateUnit) const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 定义基类
     */
    class Decl : public Node {
    private:
        // 访问级别
        AccessLevel access_level_ = AccessLevel::kALPublic;

    public:
        virtual void applyAttribute (const TString &attribute) ;
        virtual void applyAttributes(const std::vector<TString> &attributes) ;

        void        setAccessLevel(AccessLevel accessLevel) ;
        AccessLevel getAccessLevel() const ;

        virtual TypeDecl* getType () const = 0;    // 获取定义的类型，若为实例则获取实例类型，若为类型则返回自身

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 带有名称和注释的命名定义基本结构
     */
    class TagDecl : public Decl {
    private:
        // 定义名称
        TString name_;
        // 注释
        TString comment_;
        // 引用表
        std::set<Identifier *> reference_table_;

    public:

        void                setName         (const TString &name)   ;
        const TString &     getName         () const                ;
        const StringRef &   getNameRef      () const                ;

        void                setComment      (const TString &comment) ;
        const TString &     getComment      () const                 ;
        const StringRef &   getCommentRef   () const                 ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        const std::set<Identifier *> &  getReferenceTable   () const ;
        int                             addReference        (Identifier *reference) ;
        int                             removeReference     (Identifier *reference) ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述成员变量、全局变量、局部变量、参数、常量等带有类型的基本结构
     */
    class BaseVariDecl : public TagDecl {
    private:
        // 类型名称
        TString type_name_;
        // 类型指针
        VariTypeDecl *vari_type_decl_ = nullptr;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void            setTypeName(const TString &typeName) ;
        const TString & getTypeName() const ;

                void          setValType  (VariTypeDecl *variType) ;
        virtual VariTypeDecl *getValType  () ;
        virtual VariTypeDecl *evalValType () const ;
        virtual VariTypeDecl *takeValType () ;

        TypeDecl* getType () const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述参数
     */
    class ParameterDecl : public BaseVariDecl {
    private:
        bool is_reference_ = false; // 是否引用类型
        bool is_nullable_  = false; // 是否可空
        bool is_array_     = false; // 是否数组

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void applyAttribute (const TString &attribute)  override ;

    public:
        unsigned getParamIndex  () const ;
        bool     isNullable     () const ;
        bool     isArray        () const ;

        // 判断该参数是否应该以引用的方式传递，如果是数组、字符串、字节集、自定义类型或 is_reference 为真时则为真
        bool     shouldBeReference  () const ;

    public:
        static const NodeType GetClassId () ;

    };

    // 描述常量值定义
    class ConstDecl : public TagDecl {
    private:
        TString const_name_;
        Value * const_value_ = nullptr;

    public:
        ConstDecl(const TString &name, Value *value) ;

    public:
        Value *getValue() ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /*
     * 描述成员变量、全局变量、局部变量、文件变量
     */
    class VariableDecl : public BaseVariDecl {
    private:
        bool                is_array_ = false;
        TString             dimensions_decl_;   // 维度声明
        std::vector<size_t> dimensions_;        // 解析后的维度定义

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void    setDimensionsText(const TString &dimStr) ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述全局变量
     */
    class GlobalVariableDecl : public VariableDecl {
    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述成员变量
     */
    class MemberVariableDecl : public VariableDecl {
    private:
        int    index_of_struct_ = -1;
        bool   is_reference_    = false;

    public:
        void applyAttribute (const TString &attribute) override ;

        // 判断该参数是否应该以引用的方式传递，如果是数组、字符串、字节集、自定义类型或 is_reference 为真时则为真
        bool    shouldBeReference   () const ;
        int     indexOfStruct       () ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述文件变量
     */
    class FileVariableDecl : public VariableDecl {
    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述局部变量
     */
    class LocalVariableDecl : public VariableDecl {
    private:
        bool is_static_ = false;    // 是否为静态

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void applyAttribute (const TString &attribute) override ;
        bool isStatic() const ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 类型定义分支
     */

    class TypeDecl : public TagDecl {
    public:
        TypeDecl* getType () const override ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:

        /********************************************************
         * 基本类型工具
         ********************************************************/

        [[nodiscard]] virtual bool    isVoidType          () const ;   // 是否为空类型
        [[nodiscard]] virtual bool    isCommonType        () const ;   // 是否为通用型
        [[nodiscard]] virtual bool    isCharType          () const ;   // 是否为字节型
        [[nodiscard]] virtual bool    isIntegerType       () const ;   // 是否为整数型
        [[nodiscard]] virtual bool    isFloatType         () const ;   // 是否为小数型
        [[nodiscard]] virtual bool    isBoolType          () const ;   // 是否为逻辑型
        [[nodiscard]] virtual bool    isStringType        () const ;   // 是否为文本型
        [[nodiscard]] virtual bool    isDataSetType       () const ;   // 是否为字节集
        [[nodiscard]] virtual bool    isShortType         () const ;   // 是否为短整型
        [[nodiscard]] virtual bool    isLongType          () const ;   // 是否为长整型
        [[nodiscard]] virtual bool    isDatetimeType      () const ;   // 是否为日期时间型
        [[nodiscard]] virtual bool    isFuncPtrType       () const ;   // 是否为子程序指针
        [[nodiscard]] virtual bool    isDoubleType        () const ;   // 是否为双精度小数型
        [[nodiscard]] virtual bool    isStructType        () const ;   // 是否为自定义结构体类型
        [[nodiscard]] virtual bool    isExtendBooleanType () const ;   // 类型是否具有扩展布尔性
        [[nodiscard]] virtual bool    isNumerical         () const ;   // 类型是否具有数值性
        [[nodiscard]] virtual bool    isIntegerClass      () const ;   // 类型是否整数族
        [[nodiscard]] virtual bool    isArrayType         () const ;   // 是否为数组
        [[nodiscard]] virtual bool    isFunctionType      () const ;   // 是否为函数
        [[nodiscard]] virtual bool    isAPICommandType    () const ;   // 是否为外部API

        /********************************************************
         * 高级类型工具
         ********************************************************/

        [[nodiscard]] virtual bool       isCallable           () const ;   // 类型是否可调用对象
        [[nodiscard]] virtual bool       isIndexable          () const ;   // 类型是否可索引
        [[nodiscard]] virtual bool       isFixedDimensions    () const ;   // 维度数量是否不可变
        [[nodiscard]] virtual TypeDecl * evalIndexedElementTy () const ;   // 获取索引的类型

        [[nodiscard]] virtual std::vector<size_t> getDimensions () const ;  // 获取定义的索引维度

        [[nodiscard]] virtual bool       isUnyOptValid       (OperatorType opt) const ;                      // 判断一元计算有效性
        [[nodiscard]] virtual bool       isBinOptValid       (OperatorType opt, VariTypeDecl *otherType) const ; // 判断二元计算有效性
        [[nodiscard]] virtual bool       isAssginValidFrom   (TypeDecl *fromType) const ;                    // 判断赋值有效性

    public:
        static const NodeType GetClassId () ;

    };

    class VariTypeDecl : public TypeDecl {
    public:
        ArrayDecl *getArrayToWithDimStr(const std::vector<size_t> dims) ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

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
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        virtual EnumOfBuiltinType GetBuiltinType() const = 0;

    public:
        bool    isExtendBooleanType () const override;
        bool    isNumerical         () const override;
        bool    isIntegerClass      () const override;

        virtual const char *GetTypeText () const = 0;

    public:
        static const NodeType GetClassId () ;
    };

    class BuiltinVoidType : public BuiltinTypeDecl {
    public:
        BuiltinVoidType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isVoidType      () const override ;
        const char *        GetTypeText     () const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinCommonType : public BuiltinTypeDecl {
    public:
        BuiltinCommonType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isCommonType    () const override ;
        const char *        GetTypeText     () const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinCharType : public BuiltinTypeDecl {
    public:
        BuiltinCharType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isCharType      () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinIntegerType : public BuiltinTypeDecl {
    public:
        BuiltinIntegerType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isIntegerType   () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinFloatType : public BuiltinTypeDecl {
    public:
        BuiltinFloatType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isFloatType     () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinBoolType : public BuiltinTypeDecl {
    public:
        BuiltinBoolType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isBoolType      () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinStringType : public BuiltinTypeDecl {
    public:
        BuiltinStringType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType          () const override ;
        bool                isStringType            () const override ;
        const char *        GetTypeText             () const override ;
        bool                isIndexable             () const override ;
        bool                isFixedDimensions       () const override ;
        std::vector<size_t> getDimensions           () const override ;
        bool                isBinOptValid           (OperatorType opt, VariTypeDecl *otherType) const override ;

        TypeDecl *          evalIndexedElementTy     () const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinDataSetType : public BuiltinTypeDecl {
    public:
        BuiltinDataSetType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType          () const override ;
        bool                isDataSetType           () const override ;
        const char *        GetTypeText             () const override ;
        bool                isIndexable             () const override ;
        bool                isFixedDimensions       () const override ;
        std::vector<size_t> getDimensions           () const override ;
        bool                isBinOptValid           (OperatorType opt, VariTypeDecl *otherType) const override ;

        TypeDecl *          evalIndexedElementTy     () const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinShortType : public BuiltinTypeDecl {
    public:
        BuiltinShortType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isShortType     () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinLongType : public BuiltinTypeDecl {
    public:
        BuiltinLongType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isLongType      () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinDatetimeType : public BuiltinTypeDecl {
    public:
        BuiltinDatetimeType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isDatetimeType  () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinFuncPtrType : public BuiltinTypeDecl {
    public:
        BuiltinFuncPtrType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isFuncPtrType   () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    class BuiltinDoubleType : public BuiltinTypeDecl {
    public:
        BuiltinDoubleType() ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isDoubleType    () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        static EnumOfBuiltinType    BuiltinType     () ;
        static const char *         TypeText        () ;
    };

    /*
     * 数据结构定义
     */
    class StructureDecl : public VariTypeDecl {
    private:
        ordered_map<StringRef, MemberVariableDecl *> members_;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    public:
        bool            isBinOptValid       (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool            isStructType        () const override ;
        void            appendElement       (MemberVariableDecl *element) ;
        BaseVariDecl *  getElementWithIndex () ;
        BaseVariDecl *  getElementWithName  (const StringRef &variable_name) const ;

        bool            isMemberOfThis      (MemberVariableDecl *memberVariDecl) const ;
        int             indexMemberOfThis   (MemberVariableDecl *memberVariDecl) const ;

    };

    /*
     * 数组类型
     * 该节点不会在语法分析阶段产生，在语义分析阶段根据 VariableDecl 生成
     */
    class ArrayDecl : public VariTypeDecl {
    private:
        // 元素类型定义
        TypeDecl * base_type_ = nullptr;
        // 数组维度定义
        std::vector<size_t> dimensions_;

    public:
        bool                isIndexable             () const override ;
        bool                isFixedDimensions       () const override ;
        bool                isArrayType             () const override ;
        TypeDecl *          evalIndexedElementTy    () const override ;
        std::vector<size_t> getDimensions           () const override ;
        bool                isBinOptValid           (OperatorType opt, VariTypeDecl *otherType) const override ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static ArrayDecl *  get (TypeDecl *elementType, const std::vector<size_t> dimensions) ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 具有函数性的定义
     * 包含子函数定义和DLL函数定义
     */
    class FunctorDecl : public TypeDecl {
    private:
        // 返回值类型名
        TString return_type_name_;
        // 返回值类型
        TypeDecl* return_type_ = nullptr;
        // 参数列表
        std::vector<ParameterDecl *> parameters_;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
                void setReturnTypeName  (const TString &typeName) ;
        virtual void appendParameter    (ParameterDecl *parameterDecl) ;

    public:
        ParameterDecl * getParameterAt  (unsigned idx)                       const ;
        ParameterDecl * getParameter    (const StringRef &name)              const ;
        int             getIndexOf      (const ParameterDecl *parameterDecl) const ;
        TypeDecl *      getReturnType   ()                                   const ;

        virtual bool    isStaticLibraryAPI  () const = 0;
        virtual bool    isDynamicLibraryAPI () const = 0;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 子程序/函数定义
     */
    class FunctionDecl : public FunctorDecl {
    private:
        // 局部变量列表
        ordered_map<StringRef, LocalVariableDecl*> local_vari_;
        // 语句列表
        StatementBlock *statement_list_ = nullptr;
        // 所属程序集
        ProgSetDecl *super_set_ = nullptr;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void     appendLocalVariable(LocalVariableDecl * variableDecl) ;
        void     setStatementBlock  (StatementBlock *    statementBlock) ;

        LocalVariableDecl * getLocalVari    (const StringRef &name) const ;
        StatementBlock *    getFunctionBody () const ;

    public:
        bool    isStaticLibraryAPI  () const override ;
        bool    isDynamicLibraryAPI () const override ;
        bool    isFunctionType      () const override ;

    public:
        TagDecl *findDeclWithNameString(const StringRef &name) const override ;

    public:
        static const NodeType GetClassId () ;

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
    private:
        // API库文件名
        TString library_file_;
        // API库类型
        LibraryType library_type_ = LibraryType::kLTDynamic;
        // API函数名称
        TString api_name_;
        // 参数传递方式
        ArgumentPassModel argument_pass_model_ = ArgumentPassModel::kDirect;
        // API参数名称
        std::vector<StringRef> mapping_names_;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        APICommandDecl(const TString &library, LibraryType libraryType, const TString &name, const TString &apiName);

    public:
        const StringRef &   getApiNameRef() const ;
        void                setApiNameRef(const StringRef &apiName) ;

        ArgumentPassModel   getArguPassModel() const ;
        void                setArguPassModel(ArgumentPassModel model) ;

        void appendParameter    (ParameterDecl *parameterDecl) override ;

    public:
        bool    isStaticLibraryAPI  () const override ;
        bool    isDynamicLibraryAPI () const override ;
        bool    isAPICommandType    () const override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 程序集定义
     */
    class ProgSetDecl : public TagDecl {
    private:
        ordered_map<StringRef, FileVariableDecl *>  file_static_variables_;
        ordered_map<StringRef, FunctionDecl *>      function_decls_;
        ordered_map<StringRef, FunctorDecl *>       signature_of_functions_;

    public:
        void appendFileStaticVari(FileVariableDecl *variable) ;
        void appendFunctionDecl  (FunctionDecl *functionDecl) ;

        FileVariableDecl *  getFileVariableDecl (const StringRef &name) const ;
        FunctionDecl *      getFunctionDecl     (const StringRef &name) const ;

        std::vector<FunctorDecl *>  getFuncSignatures() const ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

        TagDecl * findDeclWithNameString(const StringRef &name) const override ;
        TypeDecl* getType () const override ;

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
        virtual ExprUsage getSubExprAccessType(const Expression *expr) const = 0;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 赋值语句
     */
    class AssignStmt : public Statement {
    private:
        HierarchyIdentifier* lhs_ = nullptr;
        Expression* rhs_ = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void setLHS(HierarchyIdentifier *lhs) ;
        void setRHS(Expression *rhs) ;

        HierarchyIdentifier *   getLHS() const ;
        Expression *            getRHS() const ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 控制语句
     */
    class ControlStmt : public Statement {
    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 循环控制语句
     */
    class LoopControlStmt : public ControlStmt {
    private:
        // 所控制的循环语句
        LoopStatement *controlled_loop_ = nullptr;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

        void setControlledLoop(LoopStatement *loopStatement) ;
        LoopStatement *getControlledLoop() const ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 到循环尾
     */
    class ContinueStmt : public LoopControlStmt {
    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 跳出循环
     */
    class BreakStmt : public LoopControlStmt {
    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 返回
     */
    class ReturnStmt : public ControlStmt {
    private:
        Expression* return_value_ = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

        void setReturnValue(Expression *returnValue) ;
        Expression *getReturnValue() const ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 结束
     */
    class ExitStmt : public ControlStmt {
    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 包含多种条件分支表达式
     * 如果、如果真、判断
     */
    class IfStmt : public Statement {
    private:
        // 选择分支，每个pair第一个元素为测试表达式，第二个元素为相应的语句块
        std::vector<std::pair<Expression *, Statement *>> switches_;
        // 默认分支
        Statement* default_statement_ = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void        appendBranch    (Expression *condition, Statement *statement) ;
        void        setDefault      (Statement *statement) ;
        size_t      branchesCount   () const ;
        Expression *conditionAt     (size_t idx) const ;
        Statement * branchBodyAt    (size_t idx) const ;
        Statement * defaultBody     () const ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 循环语句基本结构
     */
    class LoopStatement : public Statement {
    private:
        Statement* loop_body_ = nullptr;

    public:
        void        setLoopBody(Statement *loopBody) ;
        Statement * getLoopBody() const ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;
    };

    /**
     * @brief 描述先判断后执行的While-Loop结构
     */
    class WhileStmt : public LoopStatement {
    private:
        Expression* condition_ = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void            setLoopCondition(Expression *condition) ;
        Expression *    getLoopCondition() const ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 描述计次循环的范围迭代循环结构
     */
    class RangeForStmt : public LoopStatement {
    private:
        Expression *            range_size_ = nullptr;
        HierarchyIdentifier *   loop_vari_  = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void setRangeSize    (Expression *rangeSize) ;
        void setLoopVariable (HierarchyIdentifier *loopVari) ;

        Expression *            getRangeSize () const ;
        HierarchyIdentifier *   getLoopVari  () const ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 描述计步循环的范围迭代循环结构
     */
    class ForStmt : public LoopStatement {
        Expression *          start_value_ = nullptr;
        Expression *          stop_value_  = nullptr;
        Expression *          step_value_  = nullptr;
        HierarchyIdentifier * loop_vari_   = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void setStartValue(Expression *startValue) ;
        void setStopValue (Expression *stopValue)  ;
        void setStepValue (Expression *stepValue)  ;
        void setLoopVari  (HierarchyIdentifier *loopVari) ;

        Expression *            getStartValue () const ;
        Expression *            getStopValue  () const ;
        Expression *            getStepValue  () const ;
        HierarchyIdentifier *   getLoopVari   () const ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 描述先执行后判断的Do-While循环结构
     */
    class DoWhileStmt : public LoopStatement {
    private:
        Expression* condition_ = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void setCondition(Expression *condition) ;
        Expression *getCondition() const ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 语句块
     */
    class StatementBlock : public Statement {
    private:
        std::vector<Statement *> statements_;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        void appendStatement(Statement *statement) ;
        const std::vector<Statement *> &getStatements() const ;
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 表达式基类
     * 在这里，表达式被视作一种特殊的语句。
     */
    class Expression : public Statement {
    private:
        // 该表达式的类型
        TypeDecl* expression_type_ = nullptr;

    protected:
        virtual TypeDecl *CheckExpressionInternal() = 0 ;
        virtual TypeDecl *getExpressionTypeInternal() const = 0 ;

    public:
        virtual TypeDecl *CheckExpression() { return expression_type_ = CheckExpressionInternal(); }

        TypeDecl *getExpressionType() const ;
        TypeDecl *getExpressionType() ;
        ExprUsage getLRType      () const;    // 获取表达式自身的引用类型，依赖父节点的 getSubExprAccessType 实现

        // 创建类型转换将表达式转换为目标类型
        // 如果无需转换则返回原表达式
        // 如果无法转换则返回空指针
        virtual Expression *castTo(TypeDecl *targetType) ;

        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 多层名称序列
     * 该节点用于表示通过英文句点`.'连接的多层引用结构
     */
    class HierarchyIdentifier : public Expression {
    private:
        std::vector<NameComponent*> name_components_;

    protected:
        TypeDecl *CheckExpressionInternal   ()                             override ;
        ExprUsage getSubExprAccessType      (const Expression *expr) const override ;
        TypeDecl *getExpressionTypeInternal ()                       const override ;

    public:
        void AppendComponent(NameComponent *component);
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 单个命名组件
     */
    class NameComponent : public Expression {
    public:
        static const NodeType GetClassId () ;

    private:
        NameComponent* forward_name_component_ = nullptr;
        NameComponent* backward_name_component_ = nullptr;

    public:
        void            SetForward  (NameComponent *component) ;
        void            SetBackward (NameComponent *component) ;
        NameComponent * Forward     () const ;
        NameComponent * Backward    () const ;

        virtual TagDecl *      EvalBaseNameComponentType   () = 0;

    public:
        virtual Identifier *getBaseId() const = 0;    // 获取组件的确切名称对象
    };

    /**
     * @brief 普通名称组件
     */
    class Identifier : public NameComponent {
    private:
        // 引用名
        TString name_;
        // 引用目标
        TagDecl * reference_    = nullptr;

    protected:
        TypeDecl *CheckExpressionInternal   () override;
        ExprUsage getSubExprAccessType      (const Expression *expr) const override ;
        TypeDecl *getExpressionTypeInternal ()                       const override ;

    public:
        Identifier() ;
        Identifier(const TString &name) ;

    public:
        void                setName         (const TString &name) ;
        const TString &     getName         () const ;
        const StringRef &   getNameRef      () const ;

        TagDecl *       EvalBaseNameComponentType   ()       override ;
        Identifier *    getBaseId                   () const override ;
        TagDecl *       getDecl                     () ;
        TagDecl *       getDecl                     () const ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 数组引用组件
     */
    class ArrayIndex : public NameComponent {
    private:
        // 索引对象
        NameComponent* base_ = nullptr;
        // 索引表达式
        Expression* index_ = nullptr;

    protected:
        TypeDecl *CheckExpressionInternal() override;
        ExprUsage getSubExprAccessType      (const Expression *expr) const override ;
        TypeDecl *getExpressionTypeInternal ()                       const override ;

    public:
        void setBaseComponent(NameComponent *baseComponent) ;
        void setIndexExpr    (Expression *indexExpr) ;

        TagDecl *EvalBaseNameComponentType() override ;

        /*
         * 获取数组索引组件的真实基对象
         * 例如：
         * arrayIndex[1][2][3][1]->arrayIndex
         * func()[1][3]->func()
         */
        NameComponent *getIndexBase() const;

        /*
         * 获取可索引类型的元素类型
         * 例如：
         * 整数型数组返回整数型
         * 字节集返回字节型
         */
        TypeDecl * getElementTy() const ;

        Identifier *getBaseId() const override ;

        ErrOr<std::vector<Expression *>> getIndexesList() const ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 函数调用组件
     */
    class FunctionCall : public NameComponent {
    private:
        NameComponent *           function_name_ = nullptr;
        std::vector<Expression *> arguments_;
        FunctorDecl *             functor_declare_ = nullptr;

    protected:
        TypeDecl *CheckExpressionInternal   () override ;
        ExprUsage getSubExprAccessType      (const Expression *expr) const override ;
        TypeDecl *getExpressionTypeInternal ()                       const override ;

    public:
        TagDecl *       EvalBaseNameComponentType   ()       override ;
        Identifier *    getBaseId                   () const override ;

        void setCallName(NameComponent *funcName) ;
        void appendArgument(Expression *argument) ;
        FunctorDecl *   getFunctionDeclare  () const ;

        bool    IsArgument      (      Expression *expr) const ;    // 判定表达式是否为实参，依赖 IndexOfArgument 实现
        bool    IsArgument      (const Expression *expr) const ;    // 判定表达式是否为实参，依赖 IndexOfArgument 实现
        int     IndexOfArgument (      Expression *expr) const ;    // 若表达式是实参则返回是第几个参数，否则返回-1
        int     IndexOfArgument (const Expression *expr) const ;    // 若表达式是实参则返回是第几个参数，否则返回-1

    public:
        static const NodeType GetClassId () ;

    };

    /*
     * 类型转换
     */
    class TypeConvert : public Expression {
        enum ConvertType { kCTImplicit, kCTExplicit };
        ConvertType convert_type_ = ConvertType::kCTImplicit;

        Expression * from_expression_ = nullptr;     // 被转换表达式
        TypeDecl *   target_type_     = nullptr;     // 目标类型

    protected:
        TypeDecl *CheckExpressionInternal   ()        override ;
        TypeDecl *getExpressionTypeInternal ()  const override ;

    public:
        ExprUsage   getSubExprAccessType    (const Expression *expr) const override ;
        void        sematicAnalysisInternal (SemaContext &semaCtx) override ;

        TypeDecl * getSourceType () const ;
        TypeDecl * getTargetType () const ;

    public:
        static const NodeType GetClassId () ;

    };

    /*
     * 有运算符的表达式
     */
    class _OperatorExpression : public Expression {
        OperatorType operator_type_ = OperatorType(OperatorType::Opt::kOptNone);
        /*
         * 可选运算符：
         * 一元：-
         * 二元：* / \ % + - != == < > <= >= ?= && ||
         */
        TString operator_;

    public:
        void setOperatorText            (const TString &            operatorText) ;
        void setOperator                (const OperatorType &       opt) ;
        void setOperator                (const OperatorType::Opt &  opt) ;
        const OperatorType &getOperator () const ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        static const NodeType GetClassId () ;

    };

    class UnaryExpression : public _OperatorExpression {
    private:
        Expression* operand_value_ = nullptr;

    protected:
        VariTypeDecl *CheckExpressionInternal   () override ;
        ExprUsage getSubExprAccessType          (const Expression *expr) const override ;
        TypeDecl *getExpressionTypeInternal ()  const override ;

    public:
        void setOperand(Expression *operand) ;

    public:
        static const NodeType GetClassId () ;

    };

    class BinaryExpression : public _OperatorExpression {
    private:
        Expression* lhs_ = nullptr;
        Expression* rhs_ = nullptr;

    protected:
        VariTypeDecl *  CheckExpressionInternal     () override ;
        ExprUsage       getSubExprAccessType        (const Expression *expr) const override ;
        TypeDecl *      getExpressionTypeInternal   ()  const override ;

    public:
        void    setLHS(Expression *lhsExpr) ;
        void    setRHS(Expression *rhsExpr) ;

        bool            IsBinaryOperateValid         () const;   // 检查二元运算是否合法，该断言主要判断二元表达式中左右子式是否可以通过运算符计算
        VariTypeDecl *  getBinaryOperateUpgradeType  () const;   // 获取二元表达式提升后的类型

    public:
        static const NodeType GetClassId () ;

    };

    class ResourceRefExpression : public Expression {
    private:
        TString resource_name_;

    protected:
        TypeDecl *  CheckExpressionInternal     () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void setResourceName(const TString &resourceName) ;
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        static const NodeType GetClassId () ;

    };

    class FuncAddrExpression : public Expression {
    private:
        Identifier *  function_name_;
        FunctorDecl * functor_declare_ = nullptr;

    protected:
        TypeDecl *  CheckExpressionInternal     () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void setRefFuncName(Identifier *functionName) ;
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 值基类
     * 值基类可以表示所有的常量
     */
    class Value : public Expression {
    public:
        static const NodeType GetClassId () ;

    protected:
        ExprUsage   getSubExprAccessType    (const Expression *expr) const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;
    };

    class ValueOfDataSet : public Value {
    private:
        std::vector<Expression*> elements_;

    protected:
        TypeDecl *  CheckExpressionInternal     () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void appendElement(Expression *element) ;

    public:
        static const NodeType GetClassId () ;

    };

    class ValueOfDatetime : public Value {
    private:
        time_t time_ = 0;

    protected:
        TypeDecl *  CheckExpressionInternal     () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void setTime(time_t time) ;

    public:
        static const NodeType GetClassId () ;

    };

    class ValueOfBool : public Value {
    private:
        bool value_ = false;

    protected:
        TypeDecl *  CheckExpressionInternal     () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void setBool(bool boolValue) ;

    public:
        static const NodeType GetClassId () ;

    };

    class ValueOfDecimal : public Value {
    private:
        union {
            int   int_val_ = 0;
            float float_val_;
        };
        enum type { kInt, kFloat } type_ = type::kInt;

    protected:
        TypeDecl *  CheckExpressionInternal     () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void setIntValue  (int   value) ;
        void setFloatValue(float value) ;

    public:
        static const NodeType GetClassId () ;

    };

    class ValueOfString : public Value {
    private:
        TString string_literal_;

    protected:
        TypeDecl *  CheckExpressionInternal     () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void setStringLiteral(const TString &literal) ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 翻译单元
     * 翻译单元结构将所有可编译数据打包，提供一致的索引方式，同时应对可能的名称冲突。
     */
    class TranslateUnit : public Node {
    private:
        unsigned int                edition_ = 0;   // 语法版本号
        std::vector<SourceFile *>   source_files_;  // 资源文件列表（包括全局变量定义、数据结构定义、类模块定义、DLL接口定义、子程序集合、常量资源）

        /********************** 符号表需要用到的公共信息 **********************/

        ordered_map<StringRef, TypeDecl *>              global_type_;       // 全局类型索引表
        ordered_map<StringRef, GlobalVariableDecl *>    global_variables_;  // 全局变量索引表
        std::set<TString>                               libraries_list_;    // 支持库引用列表
        ordered_map<StringRef, FunctorDecl*>            functor_declares_;  // 函数定义表和DLL声明表的合并
        ordered_map<StringRef, ConstDecl *>             consts_declares_;   // 常量定义索引表
        ordered_map<StringRef, ProgSetDecl *>           program_sets_;      // 程序集索引表

        /****************************************************************/

        FunctorDecl *                                       main_entry_ = nullptr;  // 程序入口
        ordered_map<EnumOfBuiltinType, BuiltinTypeDecl *>   builtin_type_map_;      // 内建类型索引

    private:
        void setMainEnrty(FunctorDecl *functorDecl) ;

    public:
        void sematicAnalysisInternal(SemaContext &semaCtx) override ;

    public:
        void    appendSourceFile(SourceFile* sourceFile) ;
        bool    merge(TranslateUnit *other) ;   // 兼容性检查、冲突检查，并合并其它翻译单元

    public:
        bool    addFunctor      (FunctorDecl *  functorDecl) const ;    // 添加函数原型声明
        bool    addProgSet      (ProgSetDecl *  progSetDecl) const ;    // 添加程序集和程序集中的公开函数声明
        bool    addType         (TypeDecl *     typeDecl)    const ;    // 添加类型
        bool    addGlobalVari   (BaseVariDecl * variDecl)    const ;    // 添加全局变量
        bool    addConstVal     (ConstDecl *    constDecl)   const ;    // 添加常量定义
        bool    addRefLib       (const TString &libName)     const ;    // 添加引用库

        TypeDecl *              getType         (const StringRef &name) const ;
        GlobalVariableDecl *    getGlobalVari   (const StringRef &name) const ;
        FunctorDecl *           getFunctor      (const StringRef &name) const ;
        ConstDecl *             getConst        (const StringRef &name) const ;

    public:
        void     setSourceEdition(unsigned edition) { edition_ = edition; }
        unsigned getSourceEdition() const           { return edition_; }

        const std::set<TString> &getReferenceLibraries () const ;
        FunctorDecl *getMainEntry() const ;

    private:
        bool RegistBuiltinType(BuiltinTypeDecl *builtinTypeDecl);

    public:
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

        TagDecl *findDeclWithNameString(const StringRef &name) const override ;

    public:
        static const NodeType GetClassId () ;

    };

    class NodeWarp {
        Node * node_;

    public:
        explicit NodeWarp(Node * node) {
            node_ = node;
        }

        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Node, T>>>
        operator T *() {
            return dynamic_cast<T *>(this->node_);
        }

        template <typename T>
        T *get() { return node_->as<T>(); }
    };

    template<typename NodeTy, typename ... Args, typename = typename std::enable_if<std::is_base_of<Node, NodeTy>::value>::type>
    NodeTy *CreateNode(ASTContext *ast_context, Args && ... args) {
        return Node::Create<NodeTy, Args...>(ast_context, args...);
    }
}

#endif //REXLANG_NODEDECL_H
