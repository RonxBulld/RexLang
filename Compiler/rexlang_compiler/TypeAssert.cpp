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

    bool OperatorType::isUnaryOpt() const {
        switch (opt_) {
            case Opt::kOptSub:          /* -  */
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::isBinaryOpt() const {
        switch (opt_) {
            case Opt::kOptAdd:          /* +  */
            case Opt::kOptSub:          /* -  */
            case Opt::kOptMul:          /* *  */
            case Opt::kOptDiv:          /* /  */
            case Opt::kOptFullDiv:      /* \  */
            case Opt::kOptMod:          /* %  */
            case Opt::kOptEqual:        /* == */
            case Opt::kOptNotEqual:     /* != */
            case Opt::kOptGreatThan:    /* >  */
            case Opt::kOptLessThan:     /* <  */
            case Opt::kOptGreatEqual:   /* >= */
            case Opt::kOptLessEqual:    /* <= */
            case Opt::kOptLikeEqual:    /* ?= */
            case Opt::kOptAnd:          /* && */
            case Opt::kOptOr:           /* || */
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::isNumericalOpt() const {
        switch (opt_) {
            case Opt::kOptAdd:          /* +  */
            case Opt::kOptSub:          /* -  */
            case Opt::kOptMul:          /* *  */
            case Opt::kOptDiv:          /* /  */
            case Opt::kOptFullDiv:      /* \  */
            case Opt::kOptMod:          /* %  */
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::isEqualOrNotOpt() const {
        switch (opt_) {
            case Opt::kOptEqual:        /* == */
            case Opt::kOptNotEqual:     /* != */
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::isRelationalOpt() const{
        switch (opt_) {
            case Opt::kOptEqual:        /* == */
            case Opt::kOptNotEqual:     /* != */
            case Opt::kOptGreatThan:    /* >  */
            case Opt::kOptLessThan:     /* <  */
            case Opt::kOptGreatEqual:   /* >= */
            case Opt::kOptLessEqual:    /* <= */
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::isExtraRelOpt() const {
        switch (opt_) {
            case Opt::kOptEqual:        /* == */
            case Opt::kOptNotEqual:     /* != */
            case Opt::kOptGreatThan:    /* >  */
            case Opt::kOptLessThan:     /* <  */
            case Opt::kOptGreatEqual:   /* >= */
            case Opt::kOptLessEqual:    /* <= */
            case Opt::kOptLikeEqual:    /* ?= */
                return true;
            default:
                return false;
        }
    }

    bool OperatorType::isBooleanOpt() const {
        switch (opt_) {
            case Opt::kOptAnd:          /* && */
            case Opt::kOptOr:           /* || */
                return true;
            default:
                return false;
        }
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
        if (opt.isExtraRelOpt())         { return true; }
        switch (opt.getOperate()) {
            case OperatorType::Opt::kOptAdd:
                return true;
            default:
                return false;
        }
    }

    // 字节集型仅接受其它字节集型的扩展关系运算、加法运算

    bool BuiltinDataSetType::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->isDataSetType()) { return false; }
        if (opt.isExtraRelOpt())         { return true; }
        switch (opt.getOperate()) {
            case OperatorType::Opt::kOptAdd:
                return true;
            default:
                return false;
        }
    }

    // 逻辑型仅接受其它逻辑型的布尔运算和相等关系运算

    bool BuiltinBoolType::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->isBoolType()) { return false; }
        if (opt.isBooleanOpt())       { return true; }
        if (opt.isEqualOrNotOpt())    { return true; }
        return false;
    }

    // 日期时间型仅接受其它日期时间型的加减运算

    bool BuiltinDatetimeType::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->isDatetimeType()) { return false; }
        switch (opt.getOperate()) {
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
     *
     **********************************************************/

    bool BinaryExpression::IsBinaryOperateValid() const {
        // 只有内置类型才能执行二元运算
        BuiltinTypeDecl *lhsBuiltinType = this->lhs_->as<BuiltinTypeDecl>();
        BuiltinTypeDecl *rhsBuiltinType = this->rhs_->as<BuiltinTypeDecl>();
        if (lhsBuiltinType == nullptr || rhsBuiltinType == nullptr) {
            assert(false);
            return false;
        }
        return lhsBuiltinType->isBinOptValid(getOperator(), rhsBuiltinType);
    }

}