//
// Created by rex on 2020/1/25.
//

#include <cassert>

#include "TypeAssert.h"
#include "ASTUtility.h"

namespace rexlang {

    /**********************************************************
     * 运算符类型的断言
     **********************************************************/

    OperatorType::OperatorType(Opt opt) : opt_(opt) { }

    bool OperatorType::IsUnaryOpt() const {
        switch (opt_) {
            case Opt::kOptSub:
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::IsBinaryOpt() const {
        switch (opt_) {
            case Opt::kOptAdd:
            case Opt::kOptSub:
            case Opt::kOptMul:
            case Opt::kOptDiv:
            case Opt::kOptFullDiv:
            case Opt::kOptMod:
            case Opt::kOptEqual:
            case Opt::kOptNotEqual:
            case Opt::kOptGreatThan:
            case Opt::kOptLessThan:
            case Opt::kOptGreatEqual:
            case Opt::kOptLessEqual:
            case Opt::kOptLikeEqual:
            case Opt::kOptAnd:
            case Opt::kOptOr:
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::IsNumericalOpt() const {
        switch (opt_) {
            case Opt::kOptAdd:
            case Opt::kOptSub:
            case Opt::kOptMul:
            case Opt::kOptDiv:
            case Opt::kOptFullDiv:
            case Opt::kOptMod:
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::IsEqualOrNotOpt() const {
        switch (opt_) {
            case Opt::kOptEqual:
            case Opt::kOptNotEqual:
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::IsRelationalOpt() const{
        switch (opt_) {
            case Opt::kOptEqual:
            case Opt::kOptNotEqual:
            case Opt::kOptGreatThan:
            case Opt::kOptLessThan:
            case Opt::kOptGreatEqual:
            case Opt::kOptLessEqual:
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::IsExtraRelOpt() const {
        switch (opt_) {
            case Opt::kOptEqual:
            case Opt::kOptNotEqual:
            case Opt::kOptGreatThan:
            case Opt::kOptLessThan:
            case Opt::kOptGreatEqual:
            case Opt::kOptLessEqual:
            case Opt::kOptLikeEqual:
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::IsBooleanOpt() const {
        switch (opt_) {
            case Opt::kOptAnd:
            case Opt::kOptOr:
                return true;
            default:
                return false;
        }
    }

    OperatorType::Opt OperatorType::GetOperate() const {
        return opt_;
    }

    /**********************************************************
     * 内置分类的特定类型断言
     **********************************************************/

    bool    VariTypeDecl        :: isVoidType           () const { return false; }
    bool    VariTypeDecl        :: isCommonType         () const { return false; }
    bool    VariTypeDecl        :: isCharType           () const { return false; }
    bool    VariTypeDecl        :: isIntegerType        () const { return false; }
    bool    VariTypeDecl        :: isFloatType          () const { return false; }
    bool    VariTypeDecl        :: isBoolType           () const { return false; }
    bool    VariTypeDecl        :: isStringType         () const { return false; }
    bool    VariTypeDecl        :: isDataSetType        () const { return false; }
    bool    VariTypeDecl        :: isShortType          () const { return false; }
    bool    VariTypeDecl        :: isLongType           () const { return false; }
    bool    VariTypeDecl        :: isDatetimeType       () const { return false; }
    bool    VariTypeDecl        :: isFuncPtrType        () const { return false; }
    bool    VariTypeDecl        :: isDoubleType         () const { return false; }
    bool    VariTypeDecl        :: isStructType         () const { return false; }
    bool    VariTypeDecl        :: isExternBooleanType  () const { return false; }
    bool    VariTypeDecl        :: isNumerical          () const { return false; }
    bool    VariTypeDecl        :: isIntegerClass       () const { return false; }
    bool    VariTypeDecl        :: isArray              () const { return false; }

    bool    BuiltinVoidType     :: isVoidType           () const { return true; }
    bool    BuiltinCommonType   :: isCommonType         () const { return true; }
    bool    BuiltinCharType     :: isCharType           () const { return true; }
    bool    BuiltinIntegerType  :: isIntegerType        () const { return true; }
    bool    BuiltinFloatType    :: isFloatType          () const { return true; }
    bool    BuiltinBoolType     :: isBoolType           () const { return true; }
    bool    BuiltinStringType   :: isStringType         () const { return true; }
    bool    BuiltinDataSetType  :: isDataSetType        () const { return true; }
    bool    BuiltinShortType    :: isShortType          () const { return true; }
    bool    BuiltinLongType     :: isLongType           () const { return true; }
    bool    BuiltinDatetimeType :: isDatetimeType       () const { return true; }
    bool    BuiltinFuncPtrType  :: isFuncPtrType        () const { return true; }
    bool    BuiltinDoubleType   :: isDoubleType         () const { return true; }
    bool    StructureDecl       :: isStructType         () const { return true; }
    bool    ArrayDecl           :: isArray              () const { return true; }

    bool BuiltinTypeDecl::isExternBooleanType() const {
        if (this->isBoolType()) { return true; }
        if (this->isNumerical()) { return true; }
        if (this->isFuncPtrType()) { return true; }
        return false;
    }

    bool BuiltinTypeDecl::isNumerical() const {
        if (this->isIntegerClass()) { return true; }
        if (this->isFloatType()) { return true; }
        if (this->isDoubleType()) { return true; }
        return false;
    }

    bool BuiltinTypeDecl::isIntegerClass() const {
        if (this->isCharType()) { return true; }
        if (this->isIntegerType()) { return true; }
        if (this->isShortType()) { return true; }
        if (this->isLongType()) { return true; }
        return false;
    }

    /**********************************************************
     * 文件类型断言
     **********************************************************/

    bool SourceFile::isProgramSetFile    () const { return false; }
    bool SourceFile::isGlobalVariableFile() const { return false; }
    bool SourceFile::isDataStructureFile () const { return false; }
    bool SourceFile::isAPIDeclareFile    () const { return false; }

    bool ProgramSetFile    ::isProgramSetFile    () const { return true; }
    bool GlobalVariableFile::isGlobalVariableFile() const { return true; }
    bool DataStructureFile ::isDataStructureFile () const { return true; }
    bool APIDeclareFile    ::isAPIDeclareFile    () const { return true; }

    /**********************************************************
     * 符号特性提取
     **********************************************************/

    bool     ParameterDecl::isNullable         () const { return is_nullable_; }
    bool     ParameterDecl::isArray            () const { return is_array_; }

    bool ParameterDecl::shouldBeReference() const {
             if (this->is_reference_)                   { return true; }
        else if (this->isArray())                       { return true; }
        else if (this->getTypeDecl()->isStringType())   { return true; }
        else if (this->getTypeDecl()->isDataSetType())  { return true; }
        else if (this->getTypeDecl()->isStructType())   { return true; }
        else                                            { return false; }
    }

    /**********************************************************
     * 计算有效性判定
     **********************************************************/

    bool VariTypeDecl::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    // 数组类型不接受任何二元运算

    bool ArrayDecl::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    // 结构体类型不接受任何二元运算

    bool StructureDecl::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    // 数值型的二元操作，仅要求另一个操作数也具有数值性即可

    bool BuiltinCharType    ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }
    bool BuiltinIntegerType ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }
    bool BuiltinShortType   ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }
    bool BuiltinLongType    ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }
    bool BuiltinFloatType   ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }
    bool BuiltinDoubleType  ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }

    // 字符串型仅接受其它字节集型的扩展关系运算、加法运算

    bool BuiltinStringType::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->isDataSetType()) { return false; }
        if (opt.IsExtraRelOpt())         { return true; }
        switch (opt.GetOperate()) {
            case OperatorType::Opt::kOptAdd:
                return true;
            default:
                return false;
        }
    }

    // 字节集型仅接受其它字节集型的扩展关系运算、加法运算

    bool BuiltinDataSetType::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->isDataSetType()) { return false; }
        if (opt.IsExtraRelOpt())         { return true; }
        switch (opt.GetOperate()) {
            case OperatorType::Opt::kOptAdd:
                return true;
            default:
                return false;
        }
    }

    // 逻辑型仅接受其它逻辑型的布尔运算和相等关系运算

    bool BuiltinBoolType::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->isBoolType()) { return false; }
        if (opt.IsBooleanOpt())       { return true; }
        if (opt.IsEqualOrNotOpt())    { return true; }
        return false;
    }

    // 日期时间型仅接受其它日期时间型的加减运算

    bool BuiltinDatetimeType::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->isDatetimeType()) { return false; }
        switch (opt.GetOperate()) {
            case OperatorType::Opt::kOptAdd:
            case OperatorType::Opt::kOptSub:
                return true;
            default:
                return false;
        }
    }

    // 函数指针不接受任何二元运算

    bool BuiltinFuncPtrType::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    /**********************************************************
     * 可调用对象库类型断言
     **********************************************************/

    bool FunctionDecl::isStaticLibraryAPI  () const { return false; }
    bool FunctionDecl::isDynamicLibraryAPI () const { return false; }

    bool APICommandDecl::isStaticLibraryAPI  () const { return library_type_ == LibraryType::kLTStatic; }
    bool APICommandDecl::isDynamicLibraryAPI () const { return library_type_ == LibraryType::kLTDynamic; }

    /**********************************************************
     * 赋值有效性判定
     **********************************************************/

    bool VariTypeDecl::isAssginFromValid(TypeDecl *fromType) const { return false; }

    /**********************************************************
     * 计算结果类型推导
     **********************************************************/

    /**********************************************************
     *
     **********************************************************/

    class ValidMarixOpt {
    private:
        /*
         * 类型有效运算矩阵
         */
        std::set<OperatorType> TypeValidMatrix[(size_t)EnumOfBuiltinType::kBTypeEND][(size_t)EnumOfBuiltinType::kBTypeEND];
        /*
         * 类型提升矩阵
         */
        EnumOfBuiltinType TypeUpgradeMatrix[(size_t)EnumOfBuiltinType::kBTypeEND][(size_t)EnumOfBuiltinType::kBTypeEND];

        /**
         * @brief 添加有效运算符信息
         * @param l 左值类型
         * @param r 右值类型
         * @param enumOfBuiltinType 运算符
         * @param commutativeLaw 符合交换律
         */
        void AddValid(EnumOfBuiltinType l, EnumOfBuiltinType r, OperatorType enumOfBuiltinType, bool commutativeLaw = true) {
            TypeValidMatrix[(size_t)l][(size_t)r].insert(enumOfBuiltinType);
            if (commutativeLaw) {
                TypeValidMatrix[(size_t)r][(size_t)l].insert(enumOfBuiltinType);
            }
        }

        void AddValids(std::set<EnumOfBuiltinType> ls, std::set<EnumOfBuiltinType> rs, std::set<OperatorType> enumOfBuiltinTypes, bool commutativeLaw = true) {
            for (EnumOfBuiltinType l : ls) {
                for (EnumOfBuiltinType r : rs) {
                    for (OperatorType t : enumOfBuiltinTypes) {
                        this->AddValid(l, r, t, commutativeLaw);
                    }
                }
            }
        }

        /**
         * @brief 添加类型提升信息
         * @param l 左值类型
         * @param r 右值类型
         * @param result 处理结果类型
         * @param commutativeLaw 符合交换律
         */
        void AddUpgrade(EnumOfBuiltinType l, EnumOfBuiltinType r, EnumOfBuiltinType result, bool commutativeLaw = true) {
            TypeUpgradeMatrix[(size_t)l][(size_t)r] = result;
            if (commutativeLaw) {
                TypeUpgradeMatrix[(size_t)r][(size_t)l] = result;
            }
        }

        void AddUpgrades(std::set<EnumOfBuiltinType> ls, std::set<EnumOfBuiltinType> rs, EnumOfBuiltinType result, bool commutativeLaw = true) {
            for (EnumOfBuiltinType l : ls) {
                for (EnumOfBuiltinType r : rs) {
                    AddUpgrade(l, r, result, commutativeLaw);
                }
            }
        }

    public:
        ValidMarixOpt() {
            // 简化命名
            EnumOfBuiltinType C = EnumOfBuiltinType::kBTypeChar;
            EnumOfBuiltinType I = EnumOfBuiltinType::kBTypeInteger;
            EnumOfBuiltinType F = EnumOfBuiltinType::kBTypeFloat;
            EnumOfBuiltinType B = EnumOfBuiltinType::kBTypeBool;
            EnumOfBuiltinType S = EnumOfBuiltinType::kBTypeString;
            EnumOfBuiltinType A = EnumOfBuiltinType::kBTypeDataSet;
            EnumOfBuiltinType H = EnumOfBuiltinType::kBTypeShort;
            EnumOfBuiltinType L = EnumOfBuiltinType::kBTypeLong;
            EnumOfBuiltinType T = EnumOfBuiltinType::kBTypeDatetime;
            EnumOfBuiltinType N = EnumOfBuiltinType::kBTypeFuncPtr;
            EnumOfBuiltinType D = EnumOfBuiltinType::kBTypeDouble;
            OperatorType ADD       = OperatorType::Opt::kOptAdd;
            OperatorType SUB       = OperatorType::Opt::kOptSub;
            OperatorType MUL       = OperatorType::Opt::kOptMul;
            OperatorType DIV       = OperatorType::Opt::kOptDiv;
            OperatorType FULLDIV   = OperatorType::Opt::kOptFullDiv;
            OperatorType MOD       = OperatorType::Opt::kOptMod;
            OperatorType EQU       = OperatorType::Opt::kOptEqual;
            OperatorType NEQ       = OperatorType::Opt::kOptNotEqual;
            OperatorType GT        = OperatorType::Opt::kOptGreatThan;
            OperatorType LT        = OperatorType::Opt::kOptLessThan;
            OperatorType GE        = OperatorType::Opt::kOptGreatEqual;
            OperatorType LE        = OperatorType::Opt::kOptLessEqual;
            OperatorType LIKE      = OperatorType::Opt::kOptLikeEqual;
            OperatorType AND       = OperatorType::Opt::kOptAnd;
            OperatorType OR        = OperatorType::Opt::kOptOr;
            this->AddValids({C, I, F, H, L, D}, {C, I, F, H, L, D}, {ADD, SUB, MUL, DIV, FULLDIV, MOD, EQU, NEQ, GT, LT, GE, LE});
            this->AddValids({B}, {B}, {AND, OR});
            this->AddValids({S}, {S}, {ADD, LIKE});
            this->AddValids({A}, {A}, {ADD});
            this->AddValids({T}, {}, {});
            this->AddValids({N}, {}, {});
            /*
             * 类型提升图
             * C→H→I→L
             *     ↓ ↓
             *     F→D
             * 类型提升矩阵
             *    C H I L F D
             *  C C
             *  H H H
             *  I I I I
             *  L L L L L
             *  F F F F D F
             *  D D D D D D D
             */
            this->AddUpgrades({C}, {C}, C);
            this->AddUpgrades({H}, {C, H}, H);
            this->AddUpgrades({I}, {C, H, I}, I);
            this->AddUpgrades({L}, {C, H, I, L}, L);
            this->AddUpgrades({F}, {C, H, I, F}, F);
            this->AddUpgrade(F, L, D);
            this->AddUpgrades({D}, {C, H, I, L, F, D}, D);
        }

        bool OperateValid(EnumOfBuiltinType l, EnumOfBuiltinType r, OperatorType operatorType) const {
            const std::set<OperatorType> &valid_set = TypeValidMatrix[(size_t)l][(size_t)r];
            return valid_set.find(operatorType) != valid_set.end();
        }

        EnumOfBuiltinType TypeUpgrade(EnumOfBuiltinType l, EnumOfBuiltinType r) const {
            return TypeUpgradeMatrix[(size_t)l][(size_t)r];
        }
    } type_matrix;

    bool BinaryExpression::IsBinaryOperateValid() const {
        // 只有内置类型才能执行二元运算
        BuiltinTypeDecl *lhsBuiltinType = this->lhs_->as<BuiltinTypeDecl>();
        BuiltinTypeDecl *rhsBuiltinType = this->rhs_->as<BuiltinTypeDecl>();
        if (lhsBuiltinType == nullptr || rhsBuiltinType == nullptr) {
            return false;
        }
        return lhsBuiltinType->isBinOptValid(getOperator(), rhsBuiltinType);
    }

    EnumOfBuiltinType TypeAssert::ResultOfTypeUpgrade(EnumOfBuiltinType ltype, EnumOfBuiltinType rtype) {
        return type_matrix.TypeUpgrade(ltype, rtype);
    }

    bool TypeAssert::ExpressionIsLValue(Expression *expression) {
        return expression->is<HierarchyIdentifier>();
    }

    bool TypeAssert::IsCompareOperator(OperatorType operatorType) {
        switch (operatorType) {
            case OperatorType::kOptEqual:
            case OperatorType::kOptNotEqual:
            case OperatorType::kOptGreatThan:
            case OperatorType::kOptLessThan:
            case OperatorType::kOptGreatEqual:
            case OperatorType::kOptLessEqual:
            case OperatorType::kOptLikeEqual:
                return true;
            default:
                return false;
        }
    }
}