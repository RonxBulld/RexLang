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

    class SourceFile;           class ProgramSetFile;           class GlobalVariableFile;
    class DataStructureFile;    class DllDefineFile;

    // Declare

    // Type declare

    class Decl;                 class TagDecl;                  class TypeDecl;
    class VariTypeDecl;         class StructureDecl;            class BuiltinTypeDecl;
    class ArrayDecl;

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
        kNTyFuncAddrExpression,
        kNTyResourceRefExpression,

        kNTyValue,
        kNTyValueOfDataSet,
        kNTyValueOfDatetime,
        kNTyValueOfBool,
        kNTyValueOfDecimal,
        kNTyValueOfString,
    } NodeType;

    /*
     * 访问级别
     */
    enum class AccessLevel {
        // 公开
        kALPublic,
        // 私有
        kALPrivate,
    };

    /*
     * 传值方式
     */
    enum class ValueTransferMode {
        // 传值
        kVTMValue,
        // 传址
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

    protected:
        void setParent(Node *parent) { parent_node_ = parent; }
        void setChild (Node *child)  { child->parent_node_ = this; }

    public:
        virtual ~Node() = default;

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
        const Ty *as() const { return dynamic_cast<const Ty *>(this); }

        template<typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        Ty *as() { return dynamic_cast<Ty *>(this); }

        template<typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        bool is() const { return dynamic_cast<const Ty *>(this) != nullptr; }

    public:
        TranslateUnit * getTranslateUnit    () const { return ast_context_->GetTranslateUnit(); }
        ASTContext *    getAstContext       () const { return ast_context_; }

    public:
        void setLocation(const char *filename, size_t leftLine, size_t leftColumn, size_t rightLine, size_t rightColumn) {
            location_start_ = this->ast_context_->CreateLocation(filename, leftLine,  leftColumn );
            location_end_   = this->ast_context_->CreateLocation(filename, rightLine, rightColumn);
        }

        const char *    getFileName   () const { return ast_context_->GetFileFromLocate  (location_start_).c_str(); }
        size_t          getLeftLine   () const { return ast_context_->GetLineFromLocate  (location_start_); }
        size_t          getLeftColumn () const { return ast_context_->GetColumnFromLocate(location_start_); }
        size_t          getRightLine  () const { return ast_context_->GetLineFromLocate  (location_end_); }
        size_t          getRightColumn() const { return ast_context_->GetColumnFromLocate(location_end_); }
    };

    /**
     * @brief 资源文件基类
     */
    class SourceFile : public Node {
//        enum FileType {kProgramSetFile, kGlobalVariableFile, kDataStructureFile, kDllDefineFile} file_type_;

    public:
        static const NodeType GetClassId () ;

        virtual bool IsProgramSetFile       () const ;
        virtual bool IsGlobalVariableFile   () const ;
        virtual bool IsDataStructureFile    () const ;
        virtual bool IsDllDefineFile        () const ;
    };

    /**
     * @brief 函数声明文件
     */
    class ProgramSetFile : public SourceFile {
    private:
        std::vector<TString> libraries_;
        ProgSetDecl* program_set_declares_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    public:
        bool IsProgramSetFile       () const override ;

    public:
        void appendReferenceLibName (const TString &libraryName) ;
        void appendProgramSetDecl   (ProgSetDecl *progSetDecl) ;
    };

    /**
     * @brief 全局变量声明文件
     */
    class GlobalVariableFile : public SourceFile {
    public:
        typedef ordered_map<StringRef, GlobalVariableDecl*> GlobalVariMapTy;

    private:
        GlobalVariMapTy global_variable_map_;

    public:
        void appendGlobalVariableDecl(GlobalVariableDecl *globalVariableDecl) ;

    public:
        bool IsGlobalVariableFile   () const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief 数据结构定义文件
     */
    class DataStructureFile : public SourceFile {
    public:
        typedef ordered_map<StringRef, StructureDecl*> StructDeclMapTy;

    private:
        StructDeclMapTy structure_decl_map_;

    public:
        void appendStructureDecl(StructureDecl *structureDecl) ;

    public:
        bool IsDataStructureFile    () const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * @brief DLL函数接口声明文件
     */
    class DllDefineFile : public SourceFile {
    public:
        typedef ordered_map<StringRef, APICommandDecl*> DllDefMayTy;
    private:
        DllDefMayTy dll_declares_;

    public:
        void appendDllDefine(APICommandDecl *apiCommandDecl) ;

    public:
        bool IsDllDefineFile        () const override ;

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
        virtual void applyAttribute(const TString &attribute) ;
        virtual void applyAttributes(const std::vector<TString> &attributes) ;

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

    public:
        void                setName         (const TString &name)    ;
        const TString &     getName         () const                 ;
        const StringRef &   getNameRef      () const                 ;
        void                setComment      (const TString &comment) ;
        const TString &     getComment      () const                 ;
        const StringRef &   getCommentRef   () const                 ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述成员变量、全局变量、局部变量、参数等带有类型的基本结构
     */
    class BaseVariDecl : public TagDecl {
    private:
        // 类型名称
        TString type_name_;
        // 类型指针
        VariTypeDecl *vari_type_decl_ = nullptr;

    public:
        void setTypeName(const TString &typeName) ;
        const TString &getTypeName() const ;

        void setTypeDecl(VariTypeDecl *variType) ;
        virtual VariTypeDecl *getTypeDecl() const ;
        virtual VariTypeDecl *takeTypeDecl() const ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述参数
     */
    class ParameterDecl : public BaseVariDecl {
        // 可选参数为：参考、可空、数组
        std::vector<TString> attributes_;
        // 形参位置索引
        unsigned index_        = -1;
        // 是否引用类型
        bool     is_reference_ = false;
        // 是否可空
        bool     is_nullable_  = false;
        // 是否数组
        bool     is_array_     = false;

    public:
        unsigned getParamIndex      () const ;
        bool     isNullable         () const ;
        bool     isArray            () const ;

        // 判断该参数是否应该以引用的方式传递，如果是数组、字符串、字节集、自定义类型或 is_reference 为真时则为真
        bool     shouldBeReference  () const ;

    public:
        static const NodeType GetClassId () ;

    };

    /*
     * 描述成员变量、全局变量、局部变量、文件变量
     */
    class VariableDecl : public BaseVariDecl {
    private:
        // 维度声明
        TString dimensions_decl_;

    public:
        void setDimensionsText(const TString &dimStr) ;
        const TString &getDimensionsText() const ;

    public:
        static const NodeType GetClassId () ;
    };

    /*
     * 描述全局变量
     */
    class GlobalVariableDecl : public VariableDecl {
    public:
        void applyAttribute(const TString &attribute) override ;

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
        ArrayDecl *getArrayToWithDimStr(const TString &dimensions) ;

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
        [[nodiscard]] virtual bool    isExternBooleanType () const ;   // 类型是否具有扩展布尔性
        [[nodiscard]] virtual bool    isNumerical         () const ;   // 类型是否具有数值性
        [[nodiscard]] virtual bool    isIntegerClass      () const ;   // 类型是否整数族
        [[nodiscard]] virtual bool    isArray             () const ;   // 类型是否数组

        /********************************************************
         * 高级类型工具
         ********************************************************/

        [[nodiscard]] virtual bool       isIndexable         () const ;   // 类型是否可索引
        [[nodiscard]] virtual bool       isFixedDimensions   () const ;   // 维度数量是否可变
        [[nodiscard]] virtual TypeDecl * getIndexedElementTy () const ;   // 获取索引的类型

        [[nodiscard]] virtual std::vector<size_t> getDimensions () const ;  // 获取定义的索引维度

        [[nodiscard]] virtual bool       isUnyOptValid       (OperatorType opt) const ;                      // 判断一元计算有效性
        [[nodiscard]] virtual bool       isBinOptValid       (OperatorType opt, VariTypeDecl *otherType) const ; // 判断二元计算有效性
        [[nodiscard]] virtual bool       isAssginFromValid   (TypeDecl *fromType) const ;                    // 判断赋值有效性

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
        bool    isExternBooleanType () const override;
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

        TypeDecl *          getIndexedElementTy     () const override ;

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

        TypeDecl *          getIndexedElementTy     () const override ;

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
    public:
        ordered_map<StringRef, MemberVariableDecl*> members_;

    public:
        static const NodeType GetClassId () ;

    public:
        bool            isBinOptValid       (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool            isStructType        () const override ;
        void            appendElement       (MemberVariableDecl *element) ;
        BaseVariDecl *  getElementWithIndex () ;
        BaseVariDecl *  getElementWithName  (const StringRef &variable_name) const ;
    };

    /*
     * 数组类型
     */
    class ArrayDecl : public VariTypeDecl {
        TString base_type_str;

        // === 下面是经过语义分析后的数据 ===

        TypeDecl* base_type_ = nullptr;
        // 数组维度定义，如果不是数组，则为空
        std::vector<size_t> dimensions_;

    public:
        bool                isIndexable             () const override ;
        bool                isFixedDimensions       () const override ;
        bool                isArray                 () const override ;
        TypeDecl *          getIndexedElementTy     () const override ;
        std::vector<size_t> getDimensions           () const override ;
        bool                isBinOptValid           (OperatorType opt, VariTypeDecl *otherType) const override ;

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
        // 参数列表
        std::vector<ParameterDecl *> parameters_;
        // 返回值类型
        TypeDecl* return_type_ = nullptr;

    public:
                void setReturnTypeName  (const TString &typeName) ;
        virtual void appendParameter    (ParameterDecl *parameterDecl) ;

    public:
        ParameterDecl * GetParameterAt(unsigned idx) const ;

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
        StatementBlock* statement_list_ = nullptr;
        // 所属程序集
        ProgSetDecl* super_set_ = nullptr;

    public:
        void appendLocalVariable(LocalVariableDecl *variableDecl) ;
        void setStatementBlock(StatementBlock *statementBlock) ;

    public:
        bool    isStaticLibraryAPI  () const override ;
        bool    isDynamicLibraryAPI () const override ;

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
        // 原生函数名称
        TString api_name_;
        // 参数传递方式
        ArgumentPassModel argument_pass_model_ = ArgumentPassModel::kDirect;
        // 原生参数名称
        std::vector<StringRef> mapping_names_;

    public:
        APICommandDecl(const TString &library, LibraryType libraryType, const TString &name, const TString &apiName);

    public:
        void appendParameter    (ParameterDecl *parameterDecl) override ;

    public:
        bool    isStaticLibraryAPI  () const override ;
        bool    isDynamicLibraryAPI () const override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 程序集定义
     */
    class ProgSetDecl : public TagDecl {
    private:
        ordered_map<StringRef, FileVariableDecl*>   file_static_variables_;
        ordered_map<StringRef, FunctionDecl*>       function_decls_;

    public:
        void appendFileStaticVari(FileVariableDecl *variable) ;
        void appendFunctionDecl  (FunctionDecl *functionDecl) ;

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
        HierarchyIdentifier* lhs_ = nullptr;
        Expression* rhs_ = nullptr;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;

    public:
        void setLHS(HierarchyIdentifier *lhs) ;
        void setRHS(Expression *rhs) ;

    public:
        static const NodeType GetClassId () ;

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
        LoopStatement* loop_statement_ = nullptr;

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
    private:
        Expression* return_value_ = nullptr;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;

    public:
        void setReturnValue(Expression *returnValue) ;

    public:
        static const NodeType GetClassId () ;

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
    private:
        // 选择分支，每个pair第一个元素为测试表达式，第二个元素为相应的语句块
        std::vector<std::pair<Expression*, Statement*>> switches_;
        // 默认分支
        Statement* default_statement_ = nullptr;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;

    public:
        void appendBranch(Expression *condition, Statement *statement) ;
        void setDefault  (Statement *statement) ;

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
        void setLoopBody(Statement *loopBody) ;

    };

    /**
     * @brief 描述先判断后执行的While-Loop结构
     */
    class WhileStmt : public LoopStatement {
    private:
        Expression* condition_ = nullptr;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;

    public:
        void setLoopCondition(Expression *condition) ;

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
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;

    public:
        void setRangeSize    (Expression *rangeSize) ;
        void setLoopVariable (HierarchyIdentifier *loopVari) ;

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
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;

    public:
        void setStartValue(Expression *startValue) ;
        void setStopValue (Expression *stopValue)  ;
        void setStepValue (Expression *stepValue)  ;
        void setLoopVari  (HierarchyIdentifier *loopVari) ;

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
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;

    public:
        void setCondition(Expression *condition) ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 语句块
     */
    class StatementBlock : public Statement {
    private:
        std::vector<Statement*> statements_;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;

    public:
        void appendStatement(Statement *statement) ;

    public:
        static const NodeType GetClassId () ;

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
        TypeDecl* expression_type_ = nullptr;

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
        std::vector<NameComponent*> name_components_;

        // === 下面是经过语义分析后的数据 ===
    public:
        // 该层次名称所指向的类型
        TypeDecl* qualified_type_ = nullptr;

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
        NameComponent* forward_name_component_ = nullptr;
        NameComponent* backward_name_component_ = nullptr;

    public:
        void            SetForward  (NameComponent *component) ;
        void            SetBackward (NameComponent *component) ;
        NameComponent * Forward     () const ;
        NameComponent * Backward    () const ;

        virtual TypeDecl *      EvalBaseNameComponentType   () = 0;

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
        BaseVariDecl * reference_    = nullptr;
        FunctorDecl *  function_ref_ = nullptr;

    private:
        TypeDecl *CheckExpressionInternal() override;

    protected:
        ExprUsage GetSubExprLRType(const Expression *expr) const override;

    public:
        void            setName                     (const TString &name) ;
        TypeDecl *      EvalBaseNameComponentType   ()       override ;
        Identifier *    getBaseId                   () const override ;

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
        ExprUsage GetSubExprLRType(const Expression *expr) const override;

    private:
        TypeDecl *CheckExpressionInternal() override;

    public:
        void setBaseComponent(NameComponent *baseComponent) ;
        void setIndexExpr    (Expression *indexExpr) ;

        TypeDecl *      EvalBaseNameComponentType   () override;

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
        ExprUsage GetSubExprLRType          (const Expression *expr) const override ;

    public:
        TypeDecl *      CheckExpressionInternal     ()       override ;
        TypeDecl *      EvalBaseNameComponentType   ()       override ;
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

        /*
         * 被转换表达式
         */
        Expression* from_expression_ = nullptr;
        /*
         * 源类型
         */
        TypeDecl* source_type_ = nullptr;
        /*
         * 目标类型
         */
        TypeDecl* target_type_ = nullptr;

    public:
        static const NodeType GetClassId () ;

    public:
        TypeDecl *CheckExpressionInternal() override ;
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
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
        void setOperatorText            (const TString &operatorText) ;
        void setOperator                (const OperatorType &opt) ;
        const OperatorType &getOperator () const ;

    public:
        static const NodeType GetClassId () ;

    };

    class UnaryExpression : public _OperatorExpression {
    private:
        Expression* operand_value_ = nullptr;

    protected:
        ExprUsage GetSubExprLRType          (const Expression *expr) const override ;

    public:
        void setOperand(Expression *operand) ;
        VariTypeDecl *CheckExpressionInternal   () override ;

    public:
        static const NodeType GetClassId () ;

    };

    class BinaryExpression : public _OperatorExpression {
    private:
        Expression* lhs_ = nullptr;
        Expression* rhs_ = nullptr;

    protected:
        ExprUsage   GetSubExprLRType                (const Expression *expr) const override ;

    public:
        void    setLHS(Expression *lhsExpr) ;
        void    setRHS(Expression *rhsExpr) ;

        bool            IsBinaryOperateValid         () const;   // 检查二元运算是否合法，该断言主要判断二元表达式中左右子式是否可以通过运算符计算
        VariTypeDecl *  GetBinaryOperateUpgradeType  () const;   // 获取二元表达式提升后的类型

    public:
        VariTypeDecl *CheckExpressionInternal() override ;

    public:
        static const NodeType GetClassId () ;

    };

    class ResourceRefExpression : public Expression {
    private:
        TString resource_name_;

    public:
        void setResourceName(const TString &resourceName) ;
        TypeDecl *CheckExpressionInternal() override ;
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;

    public:
        static const NodeType GetClassId () ;

    };

    class FuncAddrExpression : public Expression {
    private:
        TString function_name_;
        FunctorDecl* functor_declare_ = nullptr;

    public:
        void setRefFuncName(const TString &functionName) ;
        TypeDecl *CheckExpressionInternal() override ;
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;

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
        ExprUsage GetSubExprLRType(const Expression *expr) const override ;
    };

    class ValueOfDataSet : public Value {
    private:
        std::vector<Expression*> elements_;

    public:
        void appendElement(Expression *element) ;

        TypeDecl *CheckExpressionInternal() override ;

    public:
        static const NodeType GetClassId () ;

    };

    class ValueOfDatetime : public Value {
    private:
        time_t time_ = 0;

    public:
        void setTime(time_t time) ;

        TypeDecl *CheckExpressionInternal() override ;

    public:
        static const NodeType GetClassId () ;

    };

    class ValueOfBool : public Value {
    private:
        bool value_ = false;

    public:
        void setBool(bool boolValue) ;
        TypeDecl *CheckExpressionInternal() override ;

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

    public:
        void setIntValue  (int   value) ;
        void setFloatValue(float value) ;

        TypeDecl *CheckExpressionInternal() override ;

    public:
        static const NodeType GetClassId () ;

    };

    class ValueOfString : public Value {
    private:
        TString string_literal_;

    public:
        void setStringLiteral(const TString &literal) ;

        TypeDecl *CheckExpressionInternal() override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * @brief 翻译单元
     * 翻译单元结构将所有可编译数据打包，提供一致的索引方式，同时应对可能的名称冲突。
     */
    class TranslateUnit : public Node {
    private:
        // 语法版本号
        unsigned int edition_ = 0;
        // 资源文件列表（包括全局变量定义、数据结构定义、类模块定义、DLL接口定义、子程序集合）
        std::vector<SourceFile*> source_file_;

        // === 下面是经过语义分析后的数据 ===

        // 全局类型索引表
        ordered_map<StringRef, TypeDecl*> global_type_;
        // 全局变量索引表
        ordered_map<StringRef, GlobalVariableDecl*> global_variables_;
        // 支持库引用列表
        std::set<StringRef> libraries_list_;
        // 程序集索引表
        ordered_map<StringRef, ProgSetDecl*> program_sets_;
        // 函数定义表
        ordered_map<StringRef, FunctionDecl*> function_decls_;
        // DLL函数声明表
        ordered_map<StringRef, APICommandDecl*> dll_declares_;
        // 函数定义表和DLL声明表的合并
        // TODO: 是否要将上面两个逗逼玩意干掉
        ordered_map<StringRef, FunctorDecl*> functor_declares_;
        // 程序入口
        FunctorDecl* main_entry_ = nullptr;
        // 内建类型索引
        ordered_map<EnumOfBuiltinType, BuiltinTypeDecl *> builtin_type_map_;

    public:
        static const NodeType GetClassId () ;

        /******************************************************
         * 资源文件操作接口
         ******************************************************/

    public:
        void    appendSourceFile(SourceFile* sourceFile) { assert(false); source_file_.push_back(sourceFile); }

        /******************************************************
         * 版本号操作接口
         ******************************************************/

    public:
        void     setSourceEdition(unsigned edition) { edition_ = edition; }
        unsigned getSourceEdition() const           { return edition_; }

        /******************************************************
         * 内建类型操作接口
         ******************************************************/

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
