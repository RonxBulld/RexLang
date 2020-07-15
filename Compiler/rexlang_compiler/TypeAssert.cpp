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

    bool    VariTypeDecl        :: IsVoidType           () const { return false; }
    bool    VariTypeDecl        :: IsCommonType         () const { return false; }
    bool    VariTypeDecl        :: IsCharType           () const { return false; }
    bool    VariTypeDecl        :: IsIntegerType        () const { return false; }
    bool    VariTypeDecl        :: IsFloatType          () const { return false; }
    bool    VariTypeDecl        :: IsBoolType           () const { return false; }
    bool    VariTypeDecl        :: IsStringType         () const { return false; }
    bool    VariTypeDecl        :: IsDataSetType        () const { return false; }
    bool    VariTypeDecl        :: IsShortType          () const { return false; }
    bool    VariTypeDecl        :: IsLongType           () const { return false; }
    bool    VariTypeDecl        :: IsDatetimeType       () const { return false; }
    bool    VariTypeDecl        :: IsFuncPtrType        () const { return false; }
    bool    VariTypeDecl        :: IsDoubleType         () const { return false; }
    bool    VariTypeDecl        :: IsStructType         () const { return false; }
    bool    VariTypeDecl        :: IsExternBooleanType  () const { return false; }
    bool    VariTypeDecl        :: IsNumerical          () const { return false; }
    bool    VariTypeDecl        :: IsIntegerClass       () const { return false; }
    bool    VariTypeDecl        :: IsArray              () const { return false; }

    bool    BuiltinVoidType     :: IsVoidType           () const { return true; }
    bool    BuiltinCommonType   :: IsCommonType         () const { return true; }
    bool    BuiltinCharType     :: IsCharType           () const { return true; }
    bool    BuiltinIntegerType  :: IsIntegerType        () const { return true; }
    bool    BuiltinFloatType    :: IsFloatType          () const { return true; }
    bool    BuiltinBoolType     :: IsBoolType           () const { return true; }
    bool    BuiltinStringType   :: IsStringType         () const { return true; }
    bool    BuiltinDataSetType  :: IsDataSetType        () const { return true; }
    bool    BuiltinShortType    :: IsShortType          () const { return true; }
    bool    BuiltinLongType     :: IsLongType           () const { return true; }
    bool    BuiltinDatetimeType :: IsDatetimeType       () const { return true; }
    bool    BuiltinFuncPtrType  :: IsFuncPtrType        () const { return true; }
    bool    BuiltinDoubleType   :: IsDoubleType         () const { return true; }
    bool    StructureDecl       :: IsStructType         () const { return true; }
    bool    ArrayDecl           :: IsArray              () const { return true; }

    bool BuiltinTypeDecl::IsExternBooleanType() const {
        if (this->IsBoolType   ()) { return true; }
        if (this->IsNumerical  ()) { return true; }
        if (this->IsFuncPtrType()) { return true; }
        return false;
    }

    bool BuiltinTypeDecl::IsNumerical() const {
        if (this->IsIntegerClass()) { return true; }
        if (this->IsFloatType   ()) { return true; }
        if (this->IsDoubleType  ()) { return true; }
        return false;
    }

    bool BuiltinTypeDecl::IsIntegerClass() const {
        if (this->IsCharType   ()) { return true; }
        if (this->IsIntegerType()) { return true; }
        if (this->IsShortType  ()) { return true; }
        if (this->IsLongType   ()) { return true; }
        return false;
    }

    /**********************************************************
     * 符号特性提取
     **********************************************************/

    bool ParameterDecl::ShouldBeReference() const {
             if (this->is_reference_)                   { return true; }
        else if (this->is_array)                        { return true; }
        else if (this->GetTypeDecl()->IsStringType())   { return true; }
        else if (this->GetTypeDecl()->IsDataSetType())  { return true; }
        else if (this->GetTypeDecl()->IsStructType())   { return true; }
        else                                            { return false; }
    }

    /**********************************************************
     * 计算有效性判定
     **********************************************************/

    bool VariTypeDecl::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    // 数组类型不接受任何二元运算

    bool ArrayDecl::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    // 结构体类型不接受任何二元运算

    bool StructureDecl::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    // 数值型的二元操作，仅要求另一个操作数也具有数值性即可

    bool BuiltinCharType    ::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->IsNumerical(); }
    bool BuiltinIntegerType ::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->IsNumerical(); }
    bool BuiltinShortType   ::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->IsNumerical(); }
    bool BuiltinLongType    ::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->IsNumerical(); }
    bool BuiltinFloatType   ::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->IsNumerical(); }
    bool BuiltinDoubleType  ::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->IsNumerical(); }

    // 字符串型仅接受其它字节集型的扩展关系运算、加法运算

    bool BuiltinStringType::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->IsDataSetType()) { return false; }
        if (opt.IsExtraRelOpt())         { return true; }
        switch (opt.GetOperate()) {
            case OperatorType::Opt::kOptAdd:
                return true;
            default:
                return false;
        }
    }

    // 字节集型仅接受其它字节集型的扩展关系运算、加法运算

    bool BuiltinDataSetType::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->IsDataSetType()) { return false; }
        if (opt.IsExtraRelOpt())         { return true; }
        switch (opt.GetOperate()) {
            case OperatorType::Opt::kOptAdd:
                return true;
            default:
                return false;
        }
    }

    // 逻辑型仅接受其它逻辑型的布尔运算和相等关系运算

    bool BuiltinBoolType::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->IsBoolType()) { return false; }
        if (opt.IsBooleanOpt())       { return true; }
        if (opt.IsEqualOrNotOpt())    { return true; }
        return false;
    }

    // 日期时间型仅接受其它日期时间型的加减运算

    bool BuiltinDatetimeType::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->IsDatetimeType()) { return false; }
        switch (opt.GetOperate()) {
            case OperatorType::Opt::kOptAdd:
            case OperatorType::Opt::kOptSub:
                return true;
            default:
                return false;
        }
    }

    // 函数指针不接受任何二元运算

    bool BuiltinFuncPtrType::IsBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    /**********************************************************
     * 可调用对象库类型断言
     **********************************************************/

    bool FunctionDecl::IsStaticLibraryAPI  () const { return false; }
    bool FunctionDecl::IsDynamicLibraryAPI () const { return false; }

    bool APICommandDecl::IsStaticLibraryAPI  () const { return library_type_ == LibraryType::kLTStatic; }
    bool APICommandDecl::IsDynamicLibraryAPI () const { return library_type_ == LibraryType::kLTDynamic; }

    /**********************************************************
     * 赋值有效性判定
     **********************************************************/

    bool VariTypeDecl::IsAssginFromValid(TypeDecl *fromType) const { return false; }

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
        return lhsBuiltinType->IsBinOptValid(GetOpt(), rhsBuiltinType);
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