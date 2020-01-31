//
// Created by rex on 2020/1/25.
//

#include "TypeAssert.h"

namespace opene {
    bool TypeAssert::IsCharType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeChar;
        }
        return false;
    }

    bool TypeAssert::IsIntegerType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger;
        }
        return false;
    }

    bool TypeAssert::IsFloatType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFloat;
        }
        return false;
    }

    bool TypeAssert::IsBoolType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool;
        }
        return false;
    }

    bool TypeAssert::IsStringType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString;
        }
        return false;
    }

    bool TypeAssert::IsDataSetType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet;
        }
        return false;
    }

    bool TypeAssert::IsShortType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeShort;
        }
        return false;
    }

    bool TypeAssert::IsLongType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeLong;
        }
        return false;
    }

    bool TypeAssert::IsDatatimeType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatetime;
        }
        return false;
    }

    bool TypeAssert::IsFuncPtrType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFuncPtr;
        }
        return false;
    }

    bool TypeAssert::IsDoubleType(const TypeDecl * typeDecl) {
        if (const BuiltinTypeDecl * builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
            return builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDouble;
        }
        return false;
    }

    bool TypeAssert::IsExternBooleanType(const TypeDecl * typeDecl) {
        if (TypeAssert::IsCharType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsIntegerType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsFloatType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsBoolType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsShortType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsLongType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsFuncPtrType(typeDecl)) {
            return true;
        } else if (TypeAssert::IsDoubleType(typeDecl)) {
            return true;
        } else {
            return false;
        }
    }

    bool TypeAssert::IsAssignableBetweenType(const TypeDecl * lhs_type, const TypeDecl * rhs_type) {
        // TODO:
        // 1. 至少有一个是数组
        // 1.1. 两者都是数组则判定基础类型
        // 1.2. 其中一个是数组则不可赋值
        // 2. 其中之一是内置类型
        // 2.1. 两者都是内置类型
        // 2.1.1. 一致则可赋值
        // 2.1.2. 左值类型兼容右值类型则可赋值
        // 2.2. 其它情况皆不可赋值
        // 3. 两者类型一致则可赋值
        // 4. 其余情况皆不可赋值
    }

    bool TypeAssert::IsAssignable(const BaseVariDecl *lhs, const BaseVariDecl *rhs) {
        // TODO:
        return false;
    }

    bool TypeAssert::IsNumerical(const TypeDecl *typeDecl) {
        if (TypeAssert::IsIntegerType(typeDecl)) { return true; }
        if (TypeAssert::IsFloatType(typeDecl)) { return true; }
        if (TypeAssert::IsShortType(typeDecl)) { return true; }
        if (TypeAssert::IsLongType(typeDecl)) { return true; }
        if (TypeAssert::IsDoubleType(typeDecl)) { return true; }
        return false;
    }

    class ValidMarixOpt {
    private:
        std::set<_OperatorExpression::OperatorType> TypeValidMatrix[(size_t)BuiltinTypeDecl::EnumOfBuiltinType::kBTtypeEND][(size_t)BuiltinTypeDecl::EnumOfBuiltinType::kBTtypeEND];

        void AddOpt(
                BuiltinTypeDecl::EnumOfBuiltinType l,    // 左值类型
                BuiltinTypeDecl::EnumOfBuiltinType r,    // 右值类型
                _OperatorExpression::OperatorType enumOfBuiltinType,   // 运算符
                bool commutativeLaw = true              // 符合交换律
                ) {
            TypeValidMatrix[(size_t)l][(size_t)r].insert(enumOfBuiltinType);
            if (commutativeLaw) {
                TypeValidMatrix[(size_t)r][(size_t)l].insert(enumOfBuiltinType);
            }
        }

        void AddOpts(
                std::set<BuiltinTypeDecl::EnumOfBuiltinType> ls,
                std::set<BuiltinTypeDecl::EnumOfBuiltinType> rs,
                std::set<_OperatorExpression::OperatorType> enumOfBuiltinTypes,
                bool commutativeLaw = true
                ) {
            for (BuiltinTypeDecl::EnumOfBuiltinType l : ls) {
                for (BuiltinTypeDecl::EnumOfBuiltinType r : rs) {
                    for (_OperatorExpression::OperatorType t : enumOfBuiltinTypes) {
                        this->AddOpt(l, r, t, commutativeLaw);
                    }
                }
            }
        }

    public:
        ValidMarixOpt() {
            // 简化命名
            BuiltinTypeDecl::EnumOfBuiltinType C = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeChar;
            BuiltinTypeDecl::EnumOfBuiltinType I = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeInteger;
            BuiltinTypeDecl::EnumOfBuiltinType F = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFloat;
            BuiltinTypeDecl::EnumOfBuiltinType B = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeBool;
            BuiltinTypeDecl::EnumOfBuiltinType S = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString;
            BuiltinTypeDecl::EnumOfBuiltinType A = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet;
            BuiltinTypeDecl::EnumOfBuiltinType H = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeShort;
            BuiltinTypeDecl::EnumOfBuiltinType L = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeLong;
            BuiltinTypeDecl::EnumOfBuiltinType T = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDatetime;
            BuiltinTypeDecl::EnumOfBuiltinType N = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeFuncPtr;
            BuiltinTypeDecl::EnumOfBuiltinType D = BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDouble;
            _OperatorExpression::OperatorType ADD       = _OperatorExpression::OperatorType::kOptAdd;
            _OperatorExpression::OperatorType SUB       = _OperatorExpression::OperatorType::kOptSub;
            _OperatorExpression::OperatorType MUL       = _OperatorExpression::OperatorType::kOptMul;
            _OperatorExpression::OperatorType DIV       = _OperatorExpression::OperatorType::kOptDiv;
            _OperatorExpression::OperatorType FULLDIV   = _OperatorExpression::OperatorType::kOptFullDiv;
            _OperatorExpression::OperatorType MOD       = _OperatorExpression::OperatorType::kOptMod;
            _OperatorExpression::OperatorType EQU       = _OperatorExpression::OperatorType::kOptEqual;
            _OperatorExpression::OperatorType NEQ       = _OperatorExpression::OperatorType::kOptNotEqual;
            _OperatorExpression::OperatorType GT        = _OperatorExpression::OperatorType::kOptGreatThan;
            _OperatorExpression::OperatorType LT        = _OperatorExpression::OperatorType::kOptLessThan;
            _OperatorExpression::OperatorType GE        = _OperatorExpression::OperatorType::kOptGreatEqual;
            _OperatorExpression::OperatorType LE        = _OperatorExpression::OperatorType::kOptLessEqual;
            _OperatorExpression::OperatorType LIKE      = _OperatorExpression::OperatorType::kOptLikeEqual;
            _OperatorExpression::OperatorType AND       = _OperatorExpression::OperatorType::kOptAnd;
            _OperatorExpression::OperatorType OR        = _OperatorExpression::OperatorType::kOptOr;
            this->AddOpts({C, I, F, H, L, D}, {C, I, F, H, L, D}, {ADD, SUB, MUL, DIV, FULLDIV, MOD, EQU, NEQ, GT, LT, GE, LE});
            this->AddOpts({B}, {B}, {AND, OR});
            this->AddOpts({S}, {S}, {ADD, LIKE});
            this->AddOpts({A}, {A}, {ADD});
            this->AddOpts({T}, {}, {});
            this->AddOpts({N}, {}, {});
        }

        bool OperateValid(BuiltinTypeDecl::EnumOfBuiltinType l, BuiltinTypeDecl::EnumOfBuiltinType r, _OperatorExpression::OperatorType operatorType) const {
            const std::set<_OperatorExpression::OperatorType> &valid_set = TypeValidMatrix[(size_t)l][(size_t)r];
            return valid_set.find(operatorType) != valid_set.end();
        }
    } valid_matrix_opt;

    bool TypeAssert::IsBinaryOperationValid(TypeDecl *lhsType, TypeDecl *rhsType, _OperatorExpression::OperatorType operatorType) {
        // 只有内置类型才能执行二元运算
        BuiltinTypeDecl *lhsBuiltinType = lhsType->as<BuiltinTypeDecl>();
        BuiltinTypeDecl *rhsBuiltinType = rhsType->as<BuiltinTypeDecl>();
        if (lhsBuiltinType == nullptr || rhsBuiltinType == nullptr) {
            return false;
        }
        BuiltinTypeDecl::EnumOfBuiltinType lhsBTEnum = lhsBuiltinType->built_in_type_;
        BuiltinTypeDecl::EnumOfBuiltinType rhsBTEnum = rhsBuiltinType->built_in_type_;
        return valid_matrix_opt.OperateValid(lhsBTEnum, rhsBTEnum, operatorType);
    }
}