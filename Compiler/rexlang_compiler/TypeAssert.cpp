/*
 * 文件包含各种类型的性质判定，目前已有：
 * 运算符：
 *      运算符一元、二元判定；
 *      运算符性质判定；
 *      运算有效性判定；
 * 内置类型：
 *      内置类型断言判定；
 *      内置类型转换判定；
 * 文件类型：
 *      文件类型断言判定；
 * 符号特性：
 *      形式参数特性判定；
 *      成员变量特性判定；
 * 可调用对象库：
 *      可调用对象库类型判定；
 * 类型通用：
 *      类型一致性判定；
 *
 * Rex
 * 2020/1/25
 */

#include <cassert>

#include "ASTUtility.h"

namespace rexlang {

    /*===---------------------------------------===*
     * 运算符类型的断言
     *===---------------------------------------===*/

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

    bool OperatorType::isIllegal() const {
        return opt_ == Opt::kOptNone;
    }

    /**********************************************************
     * 内置类型断言
     **********************************************************/

    bool    TypeDecl            :: isBuiltinType        () const { return false; }
    bool    TypeDecl            :: isVoidType           () const { return false; }
    bool    TypeDecl            :: isCommonType         () const { return false; }
    bool    TypeDecl            :: isCharType           () const { return false; }
    bool    TypeDecl            :: isIntegerType        () const { return false; }
    bool    TypeDecl            :: isFloatType          () const { return false; }
    bool    TypeDecl            :: isBoolType           () const { return false; }
    bool    TypeDecl            :: isStringType         () const { return false; }
    bool    TypeDecl            :: isDataSetType        () const { return false; }
    bool    TypeDecl            :: isShortType          () const { return false; }
    bool    TypeDecl            :: isLongType           () const { return false; }
    bool    TypeDecl            :: isDatetimeType       () const { return false; }
    bool    TypeDecl            :: isFuncPtrType        () const { return false; }
    bool    TypeDecl            :: isDoubleType         () const { return false; }
    bool    TypeDecl            :: isStructType         () const { return false; }
    bool    TypeDecl            :: isExtendBooleanType  () const { return false; }
    bool    TypeDecl            :: isNumerical          () const { return false; }
    bool    TypeDecl            :: isIntegerCategory    () const { return false; }
    bool    TypeDecl            :: isArrayType          () const { return false; }
    bool    TypeDecl            :: isFunctionType       () const { return false; }
    bool    TypeDecl            :: isAPICommandType     () const { return false; }
    bool    TypeDecl            :: isReferenceType      () const { return false; }

    bool    BuiltinTypeDecl     :: isBuiltinType        () const { return true; }
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
    bool    ArrayDecl           :: isArrayType          () const { return true; }
    bool    FunctionDecl        :: isFunctionType       () const { return true; }
    bool    APICommandDecl      :: isAPICommandType     () const { return true; }
    bool    ReferenceType       :: isReferenceType      () const { return true; }

    bool BuiltinTypeDecl::isExtendBooleanType() const {
        if (this->isBoolType())    { return true; }
        if (this->isNumerical())   { return true; }
        if (this->isFuncPtrType()) { return true; }
        return false;
    }

    bool BuiltinTypeDecl::isNumerical() const {
        if (this->isIntegerCategory()) { return true; }
        if (this->isFloatType())       { return true; }
        if (this->isDoubleType())      { return true; }
        return false;
    }

    bool BuiltinTypeDecl::isIntegerCategory() const {
        if (this->isCharType())    { return true; }
        if (this->isIntegerType()) { return true; }
        if (this->isShortType())   { return true; }
        if (this->isLongType())    { return true; }
        return false;
    }

    /**********************************************************
     * 文件类型断言
     **********************************************************/

    bool SourceFile::isProgramSetFile    () const { return false; }
    bool SourceFile::isGlobalVariableFile() const { return false; }
    bool SourceFile::isDataStructureFile () const { return false; }
    bool SourceFile::isAPIDeclareFile    () const { return false; }
    bool SourceFile::isMacroDeclareFile  () const { return false; }

    bool ProgramSetFile    ::isProgramSetFile    () const { return true; }
    bool GlobalVariableFile::isGlobalVariableFile() const { return true; }
    bool DataStructureFile ::isDataStructureFile () const { return true; }
    bool APIDeclareFile    ::isAPIDeclareFile    () const { return true; }
    bool MacroDeclareFile  ::isMacroDeclareFile  () const { return true; }

    /**********************************************************
     * 符号特性提取
     **********************************************************/

    bool ParameterDecl::isNullable() const { return is_nullable_; }

    bool ParameterDecl::shouldBeReference() const {
        TypeDecl *param_type = getType();
             if (param_type->isReferenceType ()) { return true; }
        else if (param_type->isArrayType     ()) { return true; }
        else if (param_type->isStringType    ()) { return true; }
        else if (param_type->isDataSetType   ()) { return true; }
        else if (param_type->isStructType    ()) { return true; }
        else                                     { return false; }
    }

    bool MemberVariableDecl::shouldBeReference() const {
        TypeDecl *param_type = getType();
             if (param_type->isReferenceType ()) { return true; }
        else if (param_type->isArrayType     ()) { return true; }
        else if (param_type->isStringType    ()) { return true; }
        else if (param_type->isDataSetType   ()) { return true; }
        else if (param_type->isStructType    ()) { return true; }
        else                                     { return false; }
    }

    /*===-----------------------------------------------------===*
     * 计算有效性判定
     *===-----------------------------------------------------===*/

    bool TypeDecl::isUnyOptValid(OperatorType opt) const { return false; }
    bool TypeDecl::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    bool UnaryExpression::isUnaryOperateValid() const {
        BuiltinTypeDecl *oprBuiltinType = this->operand_value_->getExpressionType()->as<BuiltinTypeDecl>();
        if (oprBuiltinType == nullptr) {
            assert(false);
            return false;
        }
        return oprBuiltinType->isUnyOptValid(getOperator());
    }

    bool BinaryExpression::isBinaryOperateValid() const {
        // 只有内置类型才能执行二元运算
        BuiltinTypeDecl *lhsBuiltinType = this->lhs_->getExpressionType()->as<BuiltinTypeDecl>();
        BuiltinTypeDecl *rhsBuiltinType = this->rhs_->getExpressionType()->as<BuiltinTypeDecl>();
        if (lhsBuiltinType == nullptr || rhsBuiltinType == nullptr) {
            assert(false);
            return false;
        }
        return lhsBuiltinType->isBinOptValid(getOperator(), rhsBuiltinType);
    }

    /*===-----------------------------------------------------===*
     * 只有数值型接受一元求反操作
     */

    bool BuiltinCharType    ::isUnyOptValid(OperatorType opt) const { return opt.getOperate() == OperatorType::Opt::kOptSub; }
    bool BuiltinIntegerType ::isUnyOptValid(OperatorType opt) const { return opt.getOperate() == OperatorType::Opt::kOptSub; }
    bool BuiltinShortType   ::isUnyOptValid(OperatorType opt) const { return opt.getOperate() == OperatorType::Opt::kOptSub; }
    bool BuiltinLongType    ::isUnyOptValid(OperatorType opt) const { return opt.getOperate() == OperatorType::Opt::kOptSub; }
    bool BuiltinFloatType   ::isUnyOptValid(OperatorType opt) const { return opt.getOperate() == OperatorType::Opt::kOptSub; }
    bool BuiltinDoubleType  ::isUnyOptValid(OperatorType opt) const { return opt.getOperate() == OperatorType::Opt::kOptSub; }

    /*===-----------------------------------------------------===*
     * 数组类型不接受任何二元运算
     */

    bool ArrayDecl::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    /*===-----------------------------------------------------===*
     * 结构体类型不接受任何二元运算
     */

    bool StructureDecl::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    /*===-----------------------------------------------------===*
     * 数值型的二元操作，仅要求另一个操作数也具有数值性即可
     */

    bool BuiltinCharType    ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }
    bool BuiltinIntegerType ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }
    bool BuiltinShortType   ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }
    bool BuiltinLongType    ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }
    bool BuiltinFloatType   ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }
    bool BuiltinDoubleType  ::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return otherType->isNumerical(); }

    /*===-----------------------------------------------------===*
     * 字符串型仅接受其它字节集型的扩展关系运算、加法运算
     */

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

    /*===-----------------------------------------------------===*
     * 字节集型仅接受其它字节集型的扩展关系运算、加法运算
     */

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

    /*===-----------------------------------------------------===*
     * 逻辑型仅接受其它逻辑型的布尔运算和相等关系运算
     */

    bool BuiltinBoolType::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const {
        if (!otherType->isBoolType()) { return false; }
        if (opt.isBooleanOpt())       { return true; }
        if (opt.isEqualOrNotOpt())    { return true; }
        return false;
    }

    /*===-----------------------------------------------------===*
     * 日期时间型仅接受其它日期时间型的加减运算
     */

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

    /*===-----------------------------------------------------===*
     * 函数指针不接受任何二元运算
     */

    bool BuiltinFuncPtrType::isBinOptValid(OperatorType opt, VariTypeDecl *otherType) const { return false; }

    /*===-----------------------------------------------------===*
     * 类型比较判定
     *===-----------------------------------------------------===*/

    bool  TypeDecl ::compareTo(TypeDecl *otherType) const { return otherType == this; }
    bool  ArrayDecl::compareTo(TypeDecl *otherType) const {
        if (!otherType->isArrayType()) { return false; }
        TypeDecl *this_elem_ty = evalIndexedElementTy();
        TypeDecl *other_elem_ty = otherType->evalIndexedElementTy();
        if (this_elem_ty && other_elem_ty && this_elem_ty->compareTo(other_elem_ty)) { return true; }
        return false;
    }

    /*===-----------------------------------------------------===*
     * 类型转换判定
     *===-----------------------------------------------------===*/

    bool TypeConvert::isTypeConvertValid() const {

        // 目前只有数值型类型可以互相之间转换

        TypeDecl *source_type = from_expression_->getExpressionType();
        if (source_type->isNumerical() && target_type_->isNumerical()) {
            return true;
        } else {
            assert(false);
            return false;
        }

    }

    /*===-----------------------------------------------------===*
     * 赋值有效性判定
     *===-----------------------------------------------------===*/

    bool TypeDecl::isAssginValidFrom(TypeDecl *fromType) const {
        // 1. 数值型之间可以相互赋值
        if (isNumerical() && fromType->isNumerical()) { return true; }
        // 2. 非内置类型要求类型必须一致
        if (isBuiltinType() || fromType->isBuiltinType()) { return compareTo(fromType); }
        // 3. 内置类型非数值型要求必须一致
        if (!isNumerical() || !fromType->isNumerical()) { return compareTo(fromType); }
        return false;
    }

    bool FunctorDecl::isAssginValidFrom(TypeDecl *fromType) const {
        /*
         * 可调用对象总是不可赋值的
         */
        return false;
    }

    bool ArrayDecl::isAssginValidFrom(TypeDecl *fromType) const {
        /*
         * 判定数组的可赋值等价于判定数组类型一致性
         */
        return compareTo(fromType);
    }

    /*===-----------------------------------------------------===*
     * 可调用对象库类型断言
     *===-----------------------------------------------------===*/

    bool FunctionDecl::isStaticLibraryAPI  () const { return false; }
    bool FunctionDecl::isDynamicLibraryAPI () const { return false; }

    bool APICommandDecl::isStaticLibraryAPI  () const { return library_type_ == LibraryType::kLTStatic; }
    bool APICommandDecl::isDynamicLibraryAPI () const { return library_type_ == LibraryType::kLTDynamic; }

}