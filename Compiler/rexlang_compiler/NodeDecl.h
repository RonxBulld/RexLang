/***********************************************************************
 * 节点类型定义文件
 * 当新增或删除节点类型时，需要注意同步处理以下部分：
 * 1、类型的前置声明；
 * 2、节点类型枚举；
 * 3、节点中的GetClassId静态方法；
 * 4、节点中的sematicAnalysisInternal静态方法；
 * 5、Visit类中的接口；
 * 6、DumpAST类中的接口。
 * 7、rtti中的name方法。
 * Created by rex on 2020/1/3.
 ***********************************************************************/

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
#include "../../lite_util/DeclList.h"
#include "ASTContext.h"

namespace rexlang {

    // 有序字典
    template <typename Key, typename Val>
    class ordered_map : public tsl::ordered_map<Key, Val> {
    public:
        ordered_map() = default;
        ordered_map(const ordered_map<Key, Val> &other) {
            *this = other;
        }
        ~ordered_map() = default;

        ordered_map<Key, Val> &operator=(const ordered_map<Key, Val> &other) = default;
    };

    // 命名有序字典
    template <typename Val>
    using NamedOrderDict = ordered_map<StringRef, Val>;

    class ASTContext;
    class SemaContext;

    // Base

    class Node;

    // Project

    class TranslateUnit;

    // File

    class SourceFile;           class ProgramSetFile;           class GlobalVariableFile;
    class DataStructureFile;    class APIDeclareFile;           class MacroDeclareFile;

    // Declare

    class IdentDef;

    // Type declare

    class Decl;                 class TagDecl;                  class TypeDecl;
    class VariTypeDecl;         class StructureDecl;            class BuiltinType;
    class ArrayType;            class ReferenceType;            class MacroDecl;

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
    class BreakStmt;            class ReturnStmt;

    // Expression

    class Expression;           class NameComponent;
    class IdentRefer;           class ArrayIndex;               class FunctionCall;
    class UnaryExpression;      class BinaryExpression;         class OperatedExpression;
    class TypeConvert;

    // Value

    class Value;                class ValueOfDataSet;           class ValueOfDatetime;
    class FuncAddrExpression;   class ValueOfBool;
    class ValueOfDecimal;       class ValueOfString;

    /**
     * 节点类型枚举
     */
    typedef enum class NodeType {
        kNTyBadType,

        kNTyTranslateUnit,

        kNTySourceFile,
        kNTyProgramSetFile, kNTyGlobalVariableFile, kNTyDataStructureFile,
        kNTyAPIDeclareFile, kNTyMacroDeclareFile,

        kNTyDecl,
        kNTyIdentDef, kNTyTagDecl, kNTyVariableDecl, kNTyBaseVariDecl,
        kNTyGlobalVariableDecl, kNTyParameterDecl, kNTyMemberVariableDecl, kNTyFileVariableDecl,
        kNTyLocalVariableDecl, kNTyTypeDecl, kNTyVariTypeDecl, kNTyBuiltinType,
        kNTyArrayType, kNTyMacroDecl, kNTyStructureDecl, kNTyReferenceType,
        kNTyFunctorDecl, kNTyFunctionDecl, kNTyProgSetDecl, kNTyAPICommandDecl,

        kNTyStatement,
        kNTyIfStmt, kNTyStatementBlock, kNTyWhileStmt, kNTyRangeForStmt,
        kNTyForStmt, kNTyDoWhileStmt, kNTyAssignStmt, kNTyControlStmt,
        kNTyLoopControlStmt, kNTyContinueStmt, kNTyBreakStmt, kNTyReturnStmt,
        kNTyExitStmt,

        kNTyExpression,
        kNTyNameComponent, kNTyIdentRefer, kNTyArrayIndex, kNTyFunctionCall,
        kNTyUnaryExpression, kNTyBinaryExpression, kNTyOperatorExpression,

        kNTyTypeConvert, kNTyFuncAddrExpression,

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
        // 传值
        kVTMValue,
        // 传址
        kVTMReference,
    };

    // 程序库类型
    enum LibraryType {
        // 动态链接库函数
        kLTDynamic,
        // 静态链接库函数
        kLTStatic,
    };

    // 参数传递模型
    enum ArgumentPassModel {
        // 直接传递
        kDirect,
        // 简单RTTI参数包
        kSimpleRTTIPack,
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

    // 运算符类型
    class OperatorType final {
    public:
        enum class Opt {
            kOptNone,
            kOptAdd, kOptSub, kOptMul, kOptDiv, kOptFullDiv, kOptMod,
            kOptEqual, kOptNotEqual, kOptGreatThan, kOptLessThan, kOptGreatEqual, kOptLessEqual, kOptLikeEqual,
            kOptAnd, kOptOr,
            kOptEND,
        };

        explicit OperatorType(const Opt &opt) : opt_(opt) { }

        ~OperatorType() = default ;

    public:

        /*===---------------------------------------===*
         * 基本符号特性判定
         *===---------------------------------------===*/

        [[nodiscard]] bool isUnaryOpt      () const ;   // -
        [[nodiscard]] bool isBinaryOpt     () const ;   // + - * / \ % == != > < >= <= ?= && ||
        [[nodiscard]] bool isNumericalOpt  () const ;   // + - * / \ %
        [[nodiscard]] bool isEqualOrNotOpt () const ;   // == !=
        [[nodiscard]] bool isRelationalOpt () const ;   // == != > < >= <=
        [[nodiscard]] bool isExtraRelOpt   () const ;   // == != > < >= <= ?=
        [[nodiscard]] bool isBooleanOpt    () const ;   // && ||
        [[nodiscard]] bool isIllegal       () const ;

    public:
        const Opt &getOperate() const { return opt_; }  // 获取运算符枚举值

    private:
        Opt opt_;
    };

    /*===---------------------------------------===*
     * 节点基类
     *===---------------------------------------===*/
    class Node {
    private:
        size_t          node_id_            = 0;        // 节点ID
        ASTContext *    ast_context_        = nullptr;  // 语法树编译上下文
        Node *          parent_node_        = nullptr;  // 父节点
        NodeType        node_type_          = NodeType::kNTyBadType;    // 节点类型
        size_t          location_start_     = 0;        // 起始位置
        size_t          location_end_       = 0;        // 终止位置

    protected:
        void setParent(Node *parent) ;
        void setChild (Node *child)  ;

    public:
        Node() ;
        virtual ~Node() { }

    public:
        template<typename NodeTy, typename ... Args, typename = typename std::enable_if<std::is_base_of<Node, NodeTy>::value>::type>
        static NodeTy *Create(ASTContext *ast_context, Args && ... args) {
            NodeTy *node = new NodeTy(std::forward<Args>(args)...);

            node->node_id_      = ast_context->GetNodeIndex();
            node->node_type_    = NodeTy::GetClassId();
            node->ast_context_  = ast_context;

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
        Node *          getParent           () const ;
        NodeType        getNodeType         () const ;

    public:
        void setLocation(const char *filename, size_t leftLine, size_t leftColumn, size_t rightLine, size_t rightColumn) ;

        const char *    getFileName   () const ;
        size_t          getLeftLine   () const ;
        size_t          getLeftColumn () const ;
        size_t          getRightLine  () const ;
        size_t          getRightColumn() const ;

    public:
        virtual int Visit(class Visitor &visitor) ;
        void Dump(std::ostream &OS) ;

    public:
        virtual TagDecl * findDeclWithNameString(const StringRef &name) const ; // 沿着语法树搜索指定名称的定义

    public:
#define REX_NO_SEMA_ANALY
#ifndef REX_NO_SEMA_ANALY
        virtual void sematicAnalysisInternal(SemaContext &semaCtx) = 0;     // 在节点上执行语义分析
#   define SEMATIC_ANALYSIS_INTERNAL void sematicAnalysisInternal(SemaContext &semaCtx) override ;
#else
#   define SEMATIC_ANALYSIS_INTERNAL
#endif

    };

    /*===---------------------------------------===*
     * 文件
     *===---------------------------------------===*/

    /**
     * 资源文件基类
     */
    class SourceFile : public Node {
    public:
        virtual FunctorDecl *        getFunctor   (const StringRef &name) const ; // 在文件中查找函数原型声明
        virtual ProgSetDecl *        getProgSet   (const StringRef &name) const ; // 在文件中查找程序集和程序集中的公开函数声明
        virtual TypeDecl *           getType      (const StringRef &name) const ; // 在文件中查找类型
        virtual GlobalVariableDecl * getGlobalVari(const StringRef &name) const ; // 在文件中查找全局变量
        virtual MacroDecl *          getMacro     (const StringRef &name) const ; // 在文件中查找宏定义

        virtual std::vector<FunctorDecl *>          getFunctorList          () const ;
        virtual std::vector<FunctionDecl *>         getFunctionList         () const ;
        virtual std::vector<VariTypeDecl *>         getVariTypeList         () const ;
        virtual std::vector<GlobalVariableDecl *>   getGlobalVariableList   () const ;
        virtual std::vector<FileVariableDecl *>     getFileVariableList     () const ;
        virtual std::vector<MacroDecl *>            getMacroList            () const ;

        virtual void registResourceTo   (TranslateUnit *translateUnit) ;   // 将资源注册到翻译单元

    public:
        SEMATIC_ANALYSIS_INTERNAL

        virtual bool isProgramSetFile    () const ;
        virtual bool isGlobalVariableFile() const ;
        virtual bool isDataStructureFile () const ;
        virtual bool isAPIDeclareFile    () const ;
        virtual bool isMacroDeclareFile  () const ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 函数声明文件
     */
    class ProgramSetFile : public SourceFile {
    private:
        std::vector<TString> libraries_;
        ProgSetDecl *        program_set_declares_ = nullptr;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        bool isProgramSetFile() const override ;

        FunctorDecl *                   getFunctor          (const StringRef &name) const override ;
        std::vector<FunctorDecl *>      getFunctorList      () const override ;
        std::vector<FunctionDecl *>     getFunctionList     () const override ;
        ProgSetDecl *                   getProgSet          (const StringRef &name) const override ;
        ProgSetDecl *                   getProgSet          ()                      const ;
        std::vector<FileVariableDecl *> getFileVariableList () const override ;


    public:
        void appendReferenceLibName (const TString &libraryName) ;
        void appendProgramSetDecl   (ProgSetDecl *progSetDecl) ;

        ProgSetDecl *                getProgramSetDecl() const ;
        const std::vector<TString> & getRefLibs       () const ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 全局变量声明文件
     */
    class GlobalVariableFile : public SourceFile {
    public:
        typedef DeclList<GlobalVariableDecl> GlobalVariMapTy;

    private:
        GlobalVariMapTy global_variable_map_;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        void                                appendGlobalVariableDecl(GlobalVariableDecl *globalVariableDecl) ;
        const GlobalVariMapTy &             getGlobalVariMap        () const ;
        GlobalVariableDecl *                getGlobalVari           (const StringRef &name) const override ;
        std::vector<GlobalVariableDecl *>   getGlobalVariableList   () const override ;

    public:
        bool isGlobalVariableFile() const override ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 数据结构定义文件
     */
    class DataStructureFile : public SourceFile {
    public:
        typedef NamedOrderDict<StructureDecl *> StructDeclMapTy;

    private:
        StructDeclMapTy structure_decl_map_;

    public:
        DataStructureFile() = default ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        void                        appendStructureDecl (StructureDecl *structureDecl) ;
        const StructDeclMapTy &     getTypes            () const ;
        TypeDecl *                  getType             (const StringRef &name) const override ;
        std::vector<VariTypeDecl *> getVariTypeList     () const override ;

    public:
        bool isDataStructureFile() const override ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * DLL函数接口声明文件
     */
    class APIDeclareFile : public SourceFile {
    public:
        typedef NamedOrderDict<APICommandDecl *> DllDefMapTy;

    private:
        DllDefMapTy api_declares_;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        void                        appendAPIDeclare(APICommandDecl *apiCommandDecl) ;
        const DllDefMapTy &         getAPIDefMap    () const ;
        FunctorDecl *               getFunctor      (const StringRef &name) const override ;
        std::vector<FunctorDecl *>  getFunctorList  () const override ;

    public:
        bool isAPIDeclareFile() const override ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 宏资源定义文件
     */
    class MacroDeclareFile : public SourceFile {
    public:
        typedef NamedOrderDict<MacroDecl *> MacroDeclMapTy;

    private:
        MacroDeclMapTy macros_declares_;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        void                        appendMacroDeclare(MacroDecl *macroDecl) ;
        const MacroDeclMapTy &      getMacroDeclMap   () const ;
        MacroDecl *                 getMacro          (const StringRef &name) const override ;
        std::vector<MacroDecl *>    getMacroList      () const override ;

    public:
        bool isMacroDeclareFile() const override ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /*===---------------------------------------===*
     *
     *===---------------------------------------===*/

    /**
     * Id的定义节点
     * 一般用于各种具名定义的名称字段
     */
    class IdentDef final : public Node {
    private:
        StringRef id_;                  // 名称
        TagDecl * tag_decl_ = nullptr;  // 反指定义指针

    public:
        explicit IdentDef(const char *           id) ;
        explicit IdentDef(const std::string &    id) ;
        explicit IdentDef(const StringRef &      id) ;
        explicit IdentDef(const TString &        id) ;

        IdentDef(const IdentDef &       other) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        const char *        name    () const ;
        const StringRef &   id      () const ;

        void                setDecl (TagDecl *tagDecl) ;
        TagDecl *           decl    () const ;

        void                update  (const char *           id) ;
        void                update  (const std::string &    id) ;
        void                update  (const StringRef &      id) ;
        void                update  (const TString &        id) ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /*===---------------------------------------===*
     * 声明
     *===---------------------------------------===*/

    /**
     * 声明节点族基类
     */
    class Decl : public Node {
    private:
        // 访问级别
        AccessLevel access_level_ = AccessLevel::kALPublic;

    public:
        virtual void applyAttribute (const TString &attribute) ;
        virtual void applyAttributes(const std::vector<TString> &attributes) ;

    public:
        void        setAccessLevel(AccessLevel accessLevel) ;   // 设置访问级别
        AccessLevel getAccessLevel() const ;        // 获取访问级别

    public:
        // 获取定义的类型，若为实例则获取实例类型，若为类型则返回自身
        virtual TypeDecl* getType () const = 0;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 带有名称和注释的命名声明基本结构
     */
    class TagDecl : public Decl {
    public:    // 属性列表
        enum class LinkageManglingStyle { MS_C, MS_CXX };
    private:
        // 链接时签名方式
        LinkageManglingStyle linkage_mangling_style_ = LinkageManglingStyle::MS_CXX;
        // 声明名称
        IdentDef *name_ = nullptr;
        // 注释
        TString comment_;

    public:
        explicit TagDecl(IdentDef *name) ;

    public:
        IdentDef *          getName    () const ;
        const StringRef &   getNameRef () const ;
        const char *        getNameStr () const ;

        void            setComment      (const TString &comment) ;
        const TString & getComment      () const                 ;
        const char *    getCommentStr   () const                 ;

        virtual StringRef getSelfMangling() const ;
        virtual StringRef getMangling    () const ;

        void                    setLinkageManglingStyle(LinkageManglingStyle manglingStyle) ;
        LinkageManglingStyle    getLinkageManglingStyle() const ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /***===------------------------------------------------===***
     * 变量声明
     ***===------------------------------------------------===***/

    /**
     * 描述带有明确类型的具名实例的基本结构
     * 例如：成员变量、全局变量、局部变量、参数等
     */
    class BaseVariDecl : public TagDecl {
    private:
        VariTypeDecl *type_      = nullptr; // 类型

    public:
        BaseVariDecl(VariTypeDecl *type, IdentDef *name) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        void        updateType (VariTypeDecl *type) ;
        TypeDecl *  getType () const override ;     // 获取变量实例的类型

        VariTypeDecl *  type() const ;

    public:
        /*===-----------------------------------------------------------===*
         * 使用其他类型来包装原有类型
         * 其他类型节点必须有签名如下的静态成员方法：
         * static VariTypeDecl *get(TypeDecl *  elementType, ...);
         *===-----------------------------------------------------------===*/
        template <typename NewTy, typename ... Args>
        void wrapTypeUse(Args && ... args) {
            if (VariTypeDecl *__type = type()) {
                VariTypeDecl *__warped = NewTy::get(__type, args...);
                assert(__warped);
                updateType(__warped);
            }
            else {
                assert(false);
            }
        }

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 描述参数结构
     */
    class ParameterDecl : public BaseVariDecl {
    private:
        bool is_variable_param_ = false; // 是否可变
        bool is_nullable_       = false; // 是否可空

    public:
        ParameterDecl(VariTypeDecl *type, IdentDef *name, bool isVari = false) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        void applyAttribute (const TString &attribute) override ;

        void markAsVariParam () ;
        bool isVariParam     () const ;

        StringRef getSelfMangling() const override ;

    public:
        int      getParamIndex  () const ;
        bool     isNullable     () const ;

        // 判断该参数是否应该以引用的方式传递
        // 如果是数组、字符串、字节集、自定义类型或引用类型时则为真
        bool     shouldBeReference  () const ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 描述宏值定义
     */
    class MacroDecl : public TagDecl {
    private:
        Value * macro_value_ = nullptr;

    public:
        MacroDecl(IdentDef *name, Value *value) ;

    public:
        Value *getValue() ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 描述成员变量、全局变量、局部变量、文件变量
     */
    class VariableDecl : public BaseVariDecl {
    public:
        VariableDecl(VariTypeDecl *type, IdentDef *name) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;

        virtual bool isMemberVariable () const ;
        virtual bool isGlobalVariable () const ;
        virtual bool isLocalVariable  () const ;
        virtual bool isFileVariable   () const ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 描述全局变量
     */
    class GlobalVariableDecl : public VariableDecl {
    public:
        GlobalVariableDecl(VariTypeDecl *type, IdentDef *name) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;

        bool isGlobalVariable() const override ;

        StringRef getSelfMangling() const override ;
        StringRef getMangling    () const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 描述成员变量
     */
    class MemberVariableDecl : public VariableDecl {
    public:
        MemberVariableDecl(VariTypeDecl *type, IdentDef *name) ;

    public:
        void applyAttribute (const TString &attribute) override ;

        // 判断该参数是否应该以引用的方式传递
        // 如果是数组、字符串、字节集、自定义类型或引用类型时则为真
        bool    shouldBeReference   () const ;

        // 获取成员变量在结构体中的索引顺序
        // 返回值应当为非负数，如果返回负数则表示发生错误
        int     indexOfStruct       () const ;

        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;

        bool isMemberVariable() const override ;

        StringRef getSelfMangling() const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 描述文件变量
     */
    class FileVariableDecl : public VariableDecl {
    public:
        FileVariableDecl(VariTypeDecl *type, IdentDef *name) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;

        bool isFileVariable() const override ;

        StringRef getSelfMangling() const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 描述局部变量
     */
    class LocalVariableDecl : public VariableDecl {
    private:
        bool is_static_ = false;    // 是否为静态

    public:
        LocalVariableDecl(VariTypeDecl *type, IdentDef *name) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        void applyAttribute (const TString &attribute) override ;
        bool isStatic() const ;

        StringRef getSelfMangling() const override ;

    public:
        int Visit(class Visitor &visitor) override ;

        bool isLocalVariable() const override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 类型定义分支
     */
    class TypeDecl : public TagDecl {
    public:
        explicit TypeDecl(IdentDef *name) ;

    public:
        TypeDecl *getType () const override ;

        SEMATIC_ANALYSIS_INTERNAL

    public:

        /********************************************************
         * 基本类型工具
         ********************************************************/

        virtual bool    isBuiltinType       () const ;   // 是否为内置类型
        virtual bool    isVoidType          () const ;   // 是否为空类型
        virtual bool    isCommonType        () const ;   // 是否为通用型
        virtual bool    isCharType          () const ;   // 是否为字节型
        virtual bool    isIntegerType       () const ;   // 是否为整数型
        virtual bool    isFloatType         () const ;   // 是否为小数型
        virtual bool    isBoolType          () const ;   // 是否为逻辑型
        virtual bool    isStringType        () const ;   // 是否为文本型
        virtual bool    isDataSetType       () const ;   // 是否为字节集
        virtual bool    isShortType         () const ;   // 是否为短整型
        virtual bool    isLongType          () const ;   // 是否为长整型
        virtual bool    isDatetimeType      () const ;   // 是否为日期时间型
        virtual bool    isFuncPtrType       () const ;   // 是否为子程序指针
        virtual bool    isDoubleType        () const ;   // 是否为双精度小数型
        virtual bool    isStructType        () const ;   // 是否为自定义结构体类型
        virtual bool    isExtendBooleanType () const ;   // 类型是否具有扩展布尔性
        virtual bool    isNumerical         () const ;   // 类型是否具有数值性
        virtual bool    isIntegerCategory   () const ;   // 类型是否整数族
        virtual bool    isFloatCategory     () const ;   // 类型是否浮点族
        virtual bool    isArrayType         () const ;   // 是否为数组
        virtual bool    isFunctionType      () const ;   // 是否为函数
        virtual bool    isAPICommandType    () const ;   // 是否为外部API
        virtual bool    isReferenceType     () const ;   // 是否为应用类型

        /********************************************************
         * 高级类型工具
         ********************************************************/

        virtual bool       isCallable           () const ;   // 类型是否可调用对象
        virtual bool       isIndexable          () const ;   // 类型是否可索引
        virtual bool       isFixedDimensions    () const ;   // 维度数量是否不可变
        virtual TypeDecl * evalIndexedElementTy () const ;   // 获取索引的类型

        virtual std::vector<size_t> getDimensions () const ;  // 获取定义的索引维度

        virtual bool  compareTo        (TypeDecl *otherType) const ;                       // 比较类型
        virtual bool  isUnyOptValid    (OperatorType opt) const ;                          // 判断一元计算有效性
        virtual bool  isBinOptValid    (OperatorType opt, VariTypeDecl *otherType) const ; // 判断二元计算有效性
        virtual bool  isAssginValidFrom(TypeDecl *fromType) const ;                        // 判断赋值有效性

        /********************************************************
         * 类型转换助手
         * NOTE: 在构造类型转换系统的时候考虑使用DAG？
         ********************************************************/

        virtual TypeDecl *promoteType(TypeDecl *otherType) const ;      // 获取当前类型与指定类型的共同兼容类型

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 变量类型定义
     */
    class VariTypeDecl : public TypeDecl {
    public:
        explicit VariTypeDecl(IdentDef *name);

    public:
        ArrayType *getArrayToWithDimStr(const std::vector<size_t> &dims) ;

        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(rexlang::Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 引用类型包装
     */
    class ReferenceType final : public VariTypeDecl {
        friend class Node;
    private:
        TypeDecl *   pointee_type_ = nullptr;

    private:
        explicit ReferenceType(TypeDecl *   pointeeType) ;

    public:
        static VariTypeDecl *   get (TypeDecl *pointeeType) ;   // 获取指定类型的引用类型，如果已经是引用类型则返回其自身
        static TypeDecl *       peek(TypeDecl *type) ;          // 获取引用的目标类型

    public:
        TypeDecl *getPointee() const ;
        bool isReferenceType() const override ;

        StringRef getSelfMangling() const override ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 内置类型定义
     */
    class BuiltinType : public VariTypeDecl {
    protected:
        BuiltinType(IdentDef *typeName, EnumOfBuiltinType typeEnum) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        virtual EnumOfBuiltinType GetBuiltinType() const = 0;

    public:
        bool    isBuiltinType       () const override ;
        bool    isExtendBooleanType () const override ;
        bool    isNumerical         () const override ;
        bool    isIntegerCategory   () const override ;
        bool    isFloatCategory     () const override ;

        virtual const char *GetTypeText () const = 0;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 内置类型-空类型
     */
    class BuiltinVoidType : public BuiltinType {
    public:
        explicit BuiltinVoidType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isVoidType      () const override ;
        const char *        GetTypeText     () const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-通用型
     */
    class BuiltinCommonType : public BuiltinType {
    public:
        explicit BuiltinCommonType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isCommonType    () const override ;
        const char *        GetTypeText     () const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-字符型
     */
    class BuiltinCharType : public BuiltinType {
    public:
        explicit BuiltinCharType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isCharType      () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool                isUnyOptValid   (OperatorType opt) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-整数型
     */
    class BuiltinIntegerType : public BuiltinType {
    public:
        explicit BuiltinIntegerType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isIntegerType   () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool                isUnyOptValid   (OperatorType opt) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-浮点型
     */
    class BuiltinFloatType : public BuiltinType {
    public:
        explicit BuiltinFloatType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isFloatType     () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool                isUnyOptValid   (OperatorType opt) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-逻辑型
     */
    class BuiltinBoolType : public BuiltinType {
    public:
        explicit BuiltinBoolType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isBoolType      () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-文本型
     */
    class BuiltinStringType : public BuiltinType {
    public:
        explicit BuiltinStringType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType          () const override ;
        bool                isStringType            () const override ;
        const char *        GetTypeText             () const override ;
        bool                isIndexable             () const override ;
        bool                isFixedDimensions       () const override ;
        std::vector<size_t> getDimensions           () const override ;
        bool                isBinOptValid           (OperatorType opt, VariTypeDecl *otherType) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        TypeDecl *          evalIndexedElementTy     () const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-字节集型
     */
    class BuiltinDataSetType : public BuiltinType {
    public:
        explicit BuiltinDataSetType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType          () const override ;
        bool                isDataSetType           () const override ;
        const char *        GetTypeText             () const override ;
        bool                isIndexable             () const override ;
        bool                isFixedDimensions       () const override ;
        std::vector<size_t> getDimensions           () const override ;
        bool                isBinOptValid           (OperatorType opt, VariTypeDecl *otherType) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        TypeDecl *          evalIndexedElementTy     () const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-短整型
     */
    class BuiltinShortType : public BuiltinType {
    public:
        explicit BuiltinShortType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isShortType     () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool                isUnyOptValid   (OperatorType opt) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-长整型
     */
    class BuiltinLongType : public BuiltinType {
    public:
        explicit BuiltinLongType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isLongType      () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool                isUnyOptValid   (OperatorType opt) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-日期时间型
     */
    class BuiltinDatetimeType : public BuiltinType {
    public:
        explicit BuiltinDatetimeType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isDatetimeType  () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-函数指针型
     */
    class BuiltinFuncPtrType : public BuiltinType {
    public:
        explicit BuiltinFuncPtrType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isFuncPtrType   () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 内置类型-双精度浮点型
     */
    class BuiltinDoubleType : public BuiltinType {
    public:
        explicit BuiltinDoubleType(IdentDef *typeName) ;

    public:
        EnumOfBuiltinType   GetBuiltinType  () const override ;
        bool                isDoubleType    () const override ;
        const char *        GetTypeText     () const override ;
        bool                isBinOptValid   (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool                isUnyOptValid   (OperatorType opt) const override ;

        TypeDecl *          promoteType(TypeDecl *otherType) const override ;

        StringRef           getSelfMangling() const override ;

        static EnumOfBuiltinType    builtinType     () ;
        static const char *         typeText        () ;
    };

    /**
     * 数据结构定义
     */
    class StructureDecl : public VariTypeDecl {
    private:
        NamedOrderDict<MemberVariableDecl *> members_;

    public:
        explicit StructureDecl(IdentDef *name) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        bool            isBinOptValid       (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool            isStructType        () const override ;
        void            appendElement       (MemberVariableDecl *element) ;
        BaseVariDecl *  getElementWithIndex (size_t idx) ;
        BaseVariDecl *  getElementWithName  (const StringRef &variable_name) const ;

        const NamedOrderDict<MemberVariableDecl *> &elements() const ;

        bool            isMemberOfThis      (MemberVariableDecl *memberVariDecl) const ;
        int             indexMemberOfThis   (MemberVariableDecl *memberVariDecl) const ;

        TypeDecl *      promoteType         (TypeDecl *otherType) const override ;

        StringRef       getSelfMangling     () const override ;
        StringRef       getMangling         () const override ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 数组类型
     * 该节点不会在语法分析阶段产生，在语义分析阶段根据 VariableDecl 生成
     */
    class ArrayType : public VariTypeDecl {
    private:
        // 元素类型
        TypeDecl *base_type_ = nullptr;
        // 数组维度定义
        std::vector<size_t> dimensions_;

    public:
        ArrayType(TypeDecl *baseType, const std::vector<size_t> &dimensions) ;

    public:
        bool                isIndexable             () const override ;
        bool                isFixedDimensions       () const override ;
        bool                isArrayType             () const override ;
        TypeDecl *          evalIndexedElementTy    () const override ;
        std::vector<size_t> getDimensions           () const override ;
        bool                isBinOptValid           (OperatorType opt, VariTypeDecl *otherType) const override ;
        bool                compareTo               (TypeDecl *otherType) const override ;
        bool                isAssginValidFrom       (TypeDecl *fromType) const override ;

        TypeDecl *          getArrayBase            () const ;

        StringRef           getSelfMangling         () const override ;
        StringRef           getMangling             () const override ;

        SEMATIC_ANALYSIS_INTERNAL

    public:
        static ArrayType *get(TypeDecl *elementType, const std::vector<size_t> &dimensions) ;   // 获取指定类型为元素的数组类型，如果已经是数组类型则返回由其元素类型创建的新数组类型

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 具有函数性的定义
     * 包含子函数定义和DLL函数定义
     */
    class FunctorDecl : public TypeDecl {
    private:
        // 返回值类型
        VariTypeDecl *return_type_ = nullptr;
        // 参数列表
        std::vector<ParameterDecl *> parameters_;

    protected:
        FunctorDecl(VariTypeDecl *retType, IdentDef *name, const std::vector<ParameterDecl *> &parameters) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

        bool isCallable             ()                      const override ;
        bool isAssginValidFrom      (TypeDecl *fromType)    const override ;

    public:
        void appendParameter(ParameterDecl *parameterDecl) ;

    public:
        const std::vector<ParameterDecl *> &getParameters() const ;
              std::vector<ParameterDecl *> &getParameters() ;

        ParameterDecl * getParameterAt  (unsigned idx)                       const ;
        ParameterDecl * getParamByName  (const StringRef &name)              const ;
        int             getIndexOf      (const ParameterDecl *parameterDecl) const ;    // 不存在返回-1

        void            updateReturnType    (VariTypeDecl *returnType) ;
        VariTypeDecl *  getReturnType       () const ;
        bool            hasVarArgs          () const ;

        virtual bool    isStaticLibraryAPI  () const = 0;
        virtual bool    isDynamicLibraryAPI () const = 0;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 子程序/函数定义
     */
    class FunctionDecl : public FunctorDecl {
    private:
        // 局部变量列表
        DeclList<LocalVariableDecl> local_vari_;
        // 语句列表
        StatementBlock *statement_list_ = nullptr;

    public:
        FunctionDecl(VariTypeDecl *retType, IdentDef *name, const std::vector<ParameterDecl *> &parameters) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        void     appendLocalVariable(LocalVariableDecl * variableDecl) ;
        void     setStatementBlock  (StatementBlock *    statementBlock) ;

        LocalVariableDecl *                 getLocalVari     (const StringRef &name) const ;
        const DeclList<LocalVariableDecl> & getLocalVariables() const ;
        StatementBlock *                    getFunctionBody  () const ;

    public:
        bool    isStaticLibraryAPI  () const override ;
        bool    isDynamicLibraryAPI () const override ;
        bool    isFunctionType      () const override ;

        StringRef getSelfMangling() const override ;

    public:
        TagDecl *findDeclWithNameString(const StringRef &name) const override ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * DLL函数声明
     */
    class APICommandDecl : public FunctorDecl {
    private:
        // API库文件名
        TString library_file_;
        // API库类型
        LibraryType library_type_ = LibraryType::kLTDynamic;
        // API函数名称
        IdentDef *api_name_ = nullptr;
        // 参数传递方式
        ArgumentPassModel argument_pass_model_ = ArgumentPassModel::kDirect;
        // API参数名称
//        std::vector<StringRef> mapping_names_;

    public:
        APICommandDecl(
                VariTypeDecl *                          retType,
                IdentDef *                              name,
                const std::vector<ParameterDecl *> &    parameters,
                LibraryType                             libraryType,
                const TString &                         libraryName,
                IdentDef *                              apiName
                ) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        const TString & getLibraryName  () const ;
        LibraryType     getLibraryType  () const ;
        IdentDef *      getApiName      () const ;

        ArgumentPassModel   getArguPassModel() const ;
        void                setArguPassModel(ArgumentPassModel model) ;

    public:
        bool    isStaticLibraryAPI  () const override ;
        bool    isDynamicLibraryAPI () const override ;
        bool    isAPICommandType    () const override ;

        StringRef getSelfMangling() const override ;
        StringRef getMangling    () const override ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 程序集定义
     */
    class ProgSetDecl : public TagDecl {
    private:
        DeclList<FileVariableDecl>  file_static_variables_;
        DeclList<FunctionDecl>      function_decls_;

    public:
        explicit ProgSetDecl(IdentDef *name) ;

    public:
        void appendFileStaticVari(FileVariableDecl *variable) ;
        void appendFunctionDecl  (FunctionDecl *functionDecl) ;

        FileVariableDecl *  getFileVariableDecl (const StringRef &name) const ;
        FunctionDecl *      getFunctionDecl     (const StringRef &name) const ;

        const DeclList<FileVariableDecl> &  fileVariables   () const ;
        const DeclList<FunctionDecl> &      functions       () const ;

        std::vector<FunctorDecl *> getFuncSignatures() ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

        TagDecl * findDeclWithNameString(const StringRef &name) const override ;
        TypeDecl* getType () const override ;

        StringRef getSelfMangling() const override ;

    public:
        int Visit(class Visitor &visitor) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 表达式引用类型
     */
    enum class ExprUsage {
        kUnknown,
        kAsLeftValue,
        kAsRightValue,
    };

    /**
     * 语句基类
     */
    class Statement : public Node {
    protected:
        virtual ExprUsage getSubExprAccessType(const Expression *expr) const = 0;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        virtual bool replaceChild(Node *origin, Node *goal) ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 赋值语句
     */
    class AssignStmt : public Statement {
    private:
        NameComponent   * lhs_ = nullptr;
        Expression      * rhs_ = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    private:
        void setLHS(NameComponent * lhs) ;
        void setRHS(Expression *    rhs) ;

    public:
        AssignStmt(NameComponent *lhs, Expression *rhs) ;

    public:
        NameComponent * getLHS() const ;
        Expression *    getRHS() const ;

        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 控制语句
     */
    class ControlStmt : public Statement {
    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 循环控制语句
     */
    class LoopControlStmt : public ControlStmt {
    public:
        SEMATIC_ANALYSIS_INTERNAL

        LoopStatement *getControlledLoop() ;  // 根据在语法树中的位置计算最近一层的循环结构

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;
    };

    /**
     * 到循环尾
     */
    class ContinueStmt : public LoopControlStmt {
    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 跳出循环
     */
    class BreakStmt : public LoopControlStmt {
    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 返回
     */
    class ReturnStmt : public ControlStmt {
    private:
        Expression *return_value_ = nullptr;

    private:
        void setReturnValue(Expression *returnValue) ;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        explicit ReturnStmt(Expression *returnValue) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

        Expression * getReturnValue() const ;

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 包含多种条件分支表达式
     * 如果、如果真、判断
     */
    class IfStmt : public Statement {
    public:
        typedef std::pair<Expression *, Statement *> BranchTy ;
    private:
        // 选择分支，每个pair第一个元素为测试表达式，第二个元素为相应的语句块
        std::vector<BranchTy> switches_;
        // 默认分支
        Statement* default_statement_ = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        IfStmt(const std::vector<BranchTy> &branches, Statement *defaultBranchBody = nullptr) ;

    public:
        void        appendBranch    (Expression *condition, Statement *statement) ;
        void        setDefault      (Statement *statement) ;
        void        setConditionAt  (size_t idx, Expression *condition) ;
        void        setBranchBodyAt (size_t idx, Statement *body) ;

        size_t      branchesCount   () const ;              // 包括default分支在内的分支个数
        Expression *conditionAt     (size_t idx) const ;
        Statement * branchBodyAt    (size_t idx) const ;
        Statement * defaultBody     () const ;

        const std::vector<BranchTy> &expressionSwitches() ;

        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;

        void replaceConditionAt (size_t idx, Expression *condition) ;
        void replaceBranchBodyAt(size_t idx, Statement *statement) ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 循环语句基本结构
     */
    class LoopStatement : public Statement {
    private:
        Statement *loop_body_ = nullptr;

    private:
        void setLoopBody(Statement *loopBody) ;

    public:
        LoopStatement(Statement *loopBody) ;

    public:
        Statement * getLoopBody() const ;

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        SEMATIC_ANALYSIS_INTERNAL
    };

    /**
     * 描述先判断后执行的While-Loop结构
     */
    class WhileStmt : public LoopStatement {
    private:
        Expression *condition_ = nullptr;

    private:
        void setLoopCondition(Expression *condition) ;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        WhileStmt(Expression *condition, Statement *loopBody) ;

    public:
        Expression *getLoopCondition() const ;

        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 描述计次循环的范围迭代循环结构
     */
    class RangeForStmt : public LoopStatement {
    private:
        Expression *    range_size_ = nullptr;
        NameComponent * loop_vari_  = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        RangeForStmt(Expression *rangeSize, NameComponent *loopVari, Statement *loopBody) ;

    public:
        void setRangeSize    (Expression *      rangeSize) ;
        void setLoopVariable (NameComponent *   loopVari) ;

        Expression *    getRangeSize () const ;
        NameComponent * getLoopVari  () const ;

        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 描述计步循环的范围迭代循环结构
     */
    class ForStmt : public LoopStatement {
    private:
        Expression *    start_value_ = nullptr;
        Expression *    stop_value_  = nullptr;
        Expression *    step_value_  = nullptr;
        NameComponent * loop_vari_   = nullptr;

    private:
        void setStartValue(Expression *     startValue) ;
        void setStopValue (Expression *     stopValue)  ;
        void setStepValue (Expression *     stepValue)  ;
        void setLoopVari  (NameComponent *  loopVari) ;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        ForStmt(Expression *startValue, Expression *stopValue, Expression *stepValue, NameComponent *loopVari, Statement *loopBody) ;

    public:
        Expression *    getStartValue () const ;
        Expression *    getStopValue  () const ;
        Expression *    getStepValue  () const ;
        NameComponent * getLoopVari   () const ;

        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 描述先执行后判断的Do-While循环结构
     */
    class DoWhileStmt : public LoopStatement {
    private:
        Expression *condition_ = nullptr;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        DoWhileStmt(Expression *condition, Statement *loopBody) ;

    public:
        void setCondition(Expression *condition) ;
        Expression *getCondition() const ;

        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 语句块
     */
    class StatementBlock : public Statement {
    private:
        std::vector<Statement *> statements_;

    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        StatementBlock(const std::vector<Statement *> &statement_list) ;

    public:
        void appendStatement(Statement *statement) ;
        const std::vector<Statement *> &getStatements() const ;
        bool replaceStatement(Statement *origin, Statement *stmt) ;
        void replaceStatements(const std::vector<Statement *> &statements) ;
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 表达式基类
     * 在这里，表达式被视作一种特殊的语句。
     */
    class Expression : public Statement {
    protected:
        virtual TypeDecl *getExpressionTypeInternal() const = 0 ;

        virtual bool VerifyExpressionInternal() = 0 ;

    public:
        bool        VerifyExpression () ;
        TypeDecl *  getExpressionType() const ;

        ExprUsage   getLRType     () const ;    // 获取表达式自身的引用类型，依赖父节点的 getSubExprAccessType 实现
        bool        isLeftUsage   () const ;    // 本表达式具有左值属性
        bool        isRightUsage  () const ;    // 本表达式具有右值属性

        // 创建类型转换将表达式转换为目标类型
        // 如果无需转换则返回原表达式
        // 如果无法转换则返回空指针
        virtual Expression *castTo(TypeDecl *targetType) ;

        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 单个命名组件
     */
    class NameComponent : public Expression {
    public:
        bool                VerifyExpressionInternal() override;
        virtual IdentRefer *getBaseId() const = 0;    // 获取组件的确切名称对象

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 普通名称组件
     */
    class IdentRefer : public NameComponent {
    private:
        // 引用目标
        IdentDef *reference_ = nullptr;
        // 前缀
        NameComponent *prefix_ = nullptr;

    protected:
        bool        VerifyExpressionInternal    () override;
        ExprUsage   getSubExprAccessType        (const Expression *expr) const override ;
        TypeDecl *  getExpressionTypeInternal   ()                       const override ;   // 该物件的数据类型

    public:
        explicit IdentRefer(IdentDef *referenceTo, NameComponent * prefix) ;

    public:
        IdentDef *      def         () const ;  // 计算并返回名称定义

        IdentRefer *    getBaseId   () const override ;
        TagDecl *       getDecl     () const ;  // 获取被引用的定义
        NameComponent * prefix      () const ;  // 获取前缀

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 数组引用组件
     * 一个组件仅表示一个维度，多维数组由多层ArrayIndex嵌套。
     */
    class ArrayIndex : public NameComponent {
    private:
        // 索引对象
        NameComponent *base_ = nullptr;
        // 索引表达式
        Expression *index_   = nullptr;

    protected:
        bool        VerifyExpressionInternal    () override;
        ExprUsage   getSubExprAccessType        (const Expression *expr) const override ;
        TypeDecl *  getExpressionTypeInternal   ()                       const override ;   // 元素的数据类型

    public:
        ArrayIndex(NameComponent *baseComponent, Expression *indexExpression) ;

    public:
        NameComponent * getBaseComponent    () const ;
        void            setBaseComponent    (NameComponent *baseComponent) ;
        void            setIndexExpr        (Expression *indexExpr) ;

        /*
         * 获取数组索引组件的真实基对象
         * 例如：
         * arrayIndex[1][2][3][1]->arrayIndex
         * func()[1][3]->func()
         */
        NameComponent * getIndexBase() const ;
        IdentRefer *    getBaseId   () const override ;     // 获取IndexBased的IdRef
        Expression *    getIndex    () const ;

        /*
         * 获取可索引类型的元素类型
         * 例如：
         * 整数型数组返回整数型
         * 字节集返回字节型
         */
        TypeDecl * getElementTy() const ;

        /*
         * 获取索引下标列表
         */
        ErrOr<std::vector<Expression *>> getIndexesList() const ;

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 函数调用组件
     */
    class FunctionCall : public NameComponent {
    private:
        IdentRefer *              name_ = nullptr;
        std::vector<Expression *> arguments_;

    private:
        bool matchFunctor   (FunctorDecl *  functorDecl) const ;    // 检查实参列表是否匹配指定可调用对象原型

        void setName            (IdentRefer * name) ;
        void setArgumentAt      (size_t idx, Expression *argument) ;
        void setArguments       (const std::vector<Expression *> &arguments) ;
        void appendArgument     (Expression *   argument) ;

    protected:
        bool        VerifyExpressionInternal    () override ;
        ExprUsage   getSubExprAccessType        (const Expression *expr) const override ;
        TypeDecl *  getExpressionTypeInternal   ()                       const override ;   // 返回值的数据类型

    public:
        FunctionCall(IdentRefer *name, FunctorDecl *callee, const std::vector<Expression *> &arguments) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

        IdentRefer *                getName             () const ;
        IdentRefer *                getBaseId           () const override ;
        FunctorDecl *               getCallee           () const ;
        size_t                      getArgumentsCount   () const ;
        Expression *                getArgumentAt       (size_t idx) const ;

              std::vector<Expression *> & getArguments  () ;
        const std::vector<Expression *> & getArguments  () const ;

        bool    isPartOfArgument (      Expression *expr) const ;    // 判定表达式是否为实参，依赖 IndexOfArgument 实现
        bool    isPartOfArgument (const Expression *expr) const ;    // 判定表达式是否为实参，依赖 IndexOfArgument 实现
        int     indexOfArgument  (      Expression *expr) const ;    // 若表达式是实参则返回是第几个参数，否则返回-1
        int     indexOfArgument  (const Expression *expr) const ;    // 若表达式是实参则返回是第几个参数，否则返回-1

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 类型转换
     */
    class TypeConvert : public Expression {
    private:
        enum ConvertType { kCTImplicit, kCTExplicit };  // 转换模式
        ConvertType convert_type_ = ConvertType::kCTImplicit;

        Expression * from_expression_ = nullptr;     // 被转换表达式
        TypeDecl *   target_type_     = nullptr;     // 目标类型

    protected:
        bool        VerifyExpressionInternal    ()        override ;
        TypeDecl *  getExpressionTypeInternal   ()  const override ;

    private:
        void setFromExpression(Expression *expression) ;
        void setTargetType    (TypeDecl *  targetType) ;

        bool isTypeConvertValid() const ;

    public:
        TypeConvert(TypeDecl *targetType, Expression *fromExpression) ;

        ExprUsage   getSubExprAccessType    (const Expression *expr) const override ;
        SEMATIC_ANALYSIS_INTERNAL

        Expression *getSourceExpr () const ;
        TypeDecl *  getSourceType () const ;
        TypeDecl *  getTargetType () const ;

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 有运算符的表达式
     */
    class OperatedExpression : public Expression {
    private:
        OperatorType operator_type_ = OperatorType(OperatorType::Opt::kOptNone);
        /*
         * 可选运算符：
         * 一元：-
         * 二元：* / \ % + - != == < > <= >= ?= && ||
         */
        TString operator_;

    public:
        explicit OperatedExpression(const OperatorType &opt) ;

    public:
        void setOperatorText            (const TString &            operatorText) ;
        void setOperator                (const OperatorType &       opt) ;
        void setOperator                (const OperatorType::Opt &  opt) ;
        const OperatorType &getOperator () const ;

    public:
        VariTypeDecl *promoteType(VariTypeDecl *typeA, VariTypeDecl *typeB) const ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 一元表达式
     */
    class UnaryExpression : public OperatedExpression {
    private:
        Expression *operand_value_ = nullptr;

    protected:
        bool            VerifyExpressionInternal    () override ;
        ExprUsage       getSubExprAccessType        (const Expression *expr) const override ;
        TypeDecl *      getExpressionTypeInternal   ()  const override ;

    public:
        UnaryExpression(const OperatorType &opt, Expression *operand) ;

    private:
        void setOperand(Expression *operand) ;

    public:
        Expression *    getOperand          () ;
        bool            isUnaryOperateValid () const ;   // 检查一元运算是否合法，该断言主要判断一元表达式中操作数是否可以通过运算符计算

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 二元表达式
     */
    class BinaryExpression : public OperatedExpression {
    private:
        Expression *lhs_ = nullptr;
        Expression *rhs_ = nullptr;

    protected:
        bool            VerifyExpressionInternal    () override ;
        ExprUsage       getSubExprAccessType        (const Expression *expr) const override ;
        TypeDecl *      getExpressionTypeInternal   () const override ;

    public:
        BinaryExpression(const OperatorType &opt, Expression *lhs, Expression *rhs) ;

    private:
        void    setLHS(Expression *lhsExpr) ;
        void    setRHS(Expression *rhsExpr) ;

    public:
        Expression *    getLHS() ;
        Expression *    getRHS() ;
        bool            isBinaryOperateValid         () const ;   // 检查二元运算是否合法，该断言主要判断二元表达式中左右子式是否可以通过运算符计算
        VariTypeDecl *  getBinaryOperateUpgradeType  () const ;   // 获取二元表达式左右子式提升后的类型，为空则表示无法提升

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 函数求地址
     */
    class FuncAddrExpression : public Expression {
    private:
        FunctorDecl *callee_ = nullptr;

    protected:
        bool        VerifyExpressionInternal    () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;
        void        setCallee                   (FunctorDecl *callee) ;

    public:
        explicit FuncAddrExpression(FunctorDecl *callee) ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;
        FunctorDecl *getCallee() const ;

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 常量值基类
     * 值基类可以表示所有的常量
     */
    class Value : public Expression {
    protected:
        ExprUsage getSubExprAccessType(const Expression *expr) const override ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 字节集字面量
     */
    class ValueOfDataSet : public Value {
    private:
        std::vector<Expression *> elements_;

    protected:
        bool        VerifyExpressionInternal    () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    private:
        void appendElement(Expression *element) ;

    public:
        explicit ValueOfDataSet(const std::vector<Expression *> &dataSet) ;

        const std::vector<Expression *> &elements() const ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 日期时间字面量
     */
    class ValueOfDatetime : public Value {
    private:
        time_t time_ = 0;

    protected:
        bool        VerifyExpressionInternal    () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    private:
        void setTime(time_t time) ;

    public:
        explicit ValueOfDatetime(time_t time) ;
        time_t getTime() const ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 布尔字面量
     */
    class ValueOfBool : public Value {
    private:
        bool value_ = false;

    protected:
        bool        VerifyExpressionInternal    () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    private:
        void setBool(bool boolValue) ;

    public:
        ValueOfBool(bool boolValue) ;
        bool Value() const ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 数值字面量
     */
    class ValueOfDecimal : public Value {
    private:
        union {
            int   int_val_ = 0;
            float float_val_;
        };
        enum type { kInt, kFloat } type_ = type::kInt;

    protected:
        bool        VerifyExpressionInternal    () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    private:
        void setIntValue  (int   value) ;
        void setFloatValue(float value) ;

    public:
        explicit ValueOfDecimal(int   value) ;
        explicit ValueOfDecimal(float value) ;

    public:
        bool    isIntValue  () const ;
        bool    isFloatValue() const ;
        int     getAsInt    () const ;
        float   getAsFloat  () const ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /**
     * 字符串字面量
     */
    class ValueOfString : public Value {
    private:
        TString string_literal_;

    protected:
        bool        VerifyExpressionInternal    () override ;
        TypeDecl *  getExpressionTypeInternal   () const override ;

    private:
        void setStringLiteral(const TString &literal) ;

    public:
        explicit ValueOfString(const TString &literal) ;
        const TString &Value() const ;

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        int Visit(class Visitor &visitor) override ;
        bool replaceChild(Node *origin, Node *goal) override ;

    public:
        static const NodeType GetClassId () ;

    };

    /*
     * 翻译单元
     * 翻译单元结构将所有可编译数据打包，提供一致的索引方式，同时应对可能的名称冲突。
     */
    class TranslateUnit : public Node {
    private:
        unsigned int                edition_ = 0;   // 语法版本号
        std::vector<SourceFile *>   source_files_;  // 资源文件列表（包括全局变量定义、数据结构定义、类模块定义、DLL接口定义、子程序集合、宏资源）
        FunctorDecl *               main_entry_ = nullptr;  // 程序入口

        NamedOrderDict<BuiltinType *>                   named_builtin_type_map_;    // 内建类型命名索引
        ordered_map<EnumOfBuiltinType, BuiltinType *>   builtin_type_map_;          // 内建类型索引

    private:
        void setMainEnrty(FunctorDecl *functorDecl) ;   // 设置主入口函数

    public:
        SEMATIC_ANALYSIS_INTERNAL

    public:
        void    appendSourceFile(SourceFile* sourceFile) ;  // 简单的将文件添加到资源列表中
        bool    merge(TranslateUnit *other) ;   // 兼容性检查、冲突检查，并合并其它翻译单元

    public:
        FunctorDecl *           getFunctor      (const StringRef &name) const ; // 在文件清单中查找函数原型声明
        ProgSetDecl *           getProgSet      (const StringRef &name) const ; // 在文件清单中查找程序集和程序集中的公开函数声明
        TypeDecl *              getType         (const StringRef &name) const ; // 在文件清单中查找类型
        GlobalVariableDecl *    getGlobalVari   (const StringRef &name) const ; // 在文件清单中查找全局变量
        MacroDecl *             getMacro        (const StringRef &name) const ; // 在文件清单中查找宏定义

        std::vector<FunctorDecl *>          getFunctorList          () const ;
        std::vector<FunctionDecl *>         getFunctionList         () const ;
        std::vector<VariTypeDecl *>         getVariTypeList         () const ;
        std::vector<GlobalVariableDecl *>   getGlobalVariableList   () const ;
        std::vector<FileVariableDecl *>     getFileVariableList     () const ;
        std::vector<MacroDecl *>            getMacroList            () const ;

    public:
        void     setSourceEdition(unsigned edition) ;
        unsigned getSourceEdition() const           ;

        const std::vector<SourceFile *> &getSourceFiles() const ;

        FunctorDecl *getMainEntry() const ;

    private:
        bool RegistBuiltinType(BuiltinType *builtinType);

    public:
        TranslateUnit() ;
        ~TranslateUnit() ;
        bool InitBuiltinTypes();

    public:
        BuiltinType *           getBuiltinTy    (EnumOfBuiltinType enumOfBuiltinType) const ;
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
        int Visit(class Visitor &visitor) override ;

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
        return Node::Create<NodeTy, Args...>(ast_context, std::forward<Args>(args)...);
    }
}

#endif //REXLANG_NODEDECL_H
