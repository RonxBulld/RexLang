//
// Created by rex on 2020/1/25.
//

#include <cassert>

#include "TypeAssert.h"
#include "ASTUtility.h"

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
        if (TypeAssert::IsBoolType(typeDecl)) { return true; }
        if (TypeAssert::IsNumerical(typeDecl)) { return true; }
        if (TypeAssert::IsFuncPtrType(typeDecl)) { return true; }
        return false;
    }

    bool TypeAssert::IsNumerical(const TypeDecl *typeDecl) {
        if (TypeAssert::IsIntegerClass(typeDecl)) { return true; }
        if (TypeAssert::IsFloatType(typeDecl)) { return true; }
        if (TypeAssert::IsDoubleType(typeDecl)) { return true; }
        return false;
    }

    bool TypeAssert::IsIntegerClass(const TypeDecl *typeDecl) {
        if (TypeAssert::IsCharType(typeDecl)) { return true; }
        if (TypeAssert::IsIntegerType(typeDecl)) { return true; }
        if (TypeAssert::IsShortType(typeDecl)) { return true; }
        if (TypeAssert::IsLongType(typeDecl)) { return true; }
        return false;
    }

    class ValidMarixOpt {
    private:
        /*
         * 类型有效运算矩阵
         */
        std::set<_OperatorExpression::OperatorType> TypeValidMatrix[(size_t)BuiltinTypeDecl::EnumOfBuiltinType::kBTtypeEND][(size_t)BuiltinTypeDecl::EnumOfBuiltinType::kBTtypeEND];
        /*
         * 类型提升矩阵
         */
        BuiltinTypeDecl::EnumOfBuiltinType TypeUpgradeMatrix[(size_t)BuiltinTypeDecl::EnumOfBuiltinType::kBTtypeEND][(size_t)BuiltinTypeDecl::EnumOfBuiltinType::kBTtypeEND];

        /**
         * @brief 添加有效运算符信息
         * @param l 左值类型
         * @param r 右值类型
         * @param enumOfBuiltinType 运算符
         * @param commutativeLaw 符合交换律
         */
        void AddValid(BuiltinTypeDecl::EnumOfBuiltinType l, BuiltinTypeDecl::EnumOfBuiltinType r, _OperatorExpression::OperatorType enumOfBuiltinType, bool commutativeLaw = true) {
            TypeValidMatrix[(size_t)l][(size_t)r].insert(enumOfBuiltinType);
            if (commutativeLaw) {
                TypeValidMatrix[(size_t)r][(size_t)l].insert(enumOfBuiltinType);
            }
        }

        void AddValids(std::set<BuiltinTypeDecl::EnumOfBuiltinType> ls, std::set<BuiltinTypeDecl::EnumOfBuiltinType> rs, std::set<_OperatorExpression::OperatorType> enumOfBuiltinTypes, bool commutativeLaw = true) {
            for (BuiltinTypeDecl::EnumOfBuiltinType l : ls) {
                for (BuiltinTypeDecl::EnumOfBuiltinType r : rs) {
                    for (_OperatorExpression::OperatorType t : enumOfBuiltinTypes) {
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
        void AddUpgrade(BuiltinTypeDecl::EnumOfBuiltinType l, BuiltinTypeDecl::EnumOfBuiltinType r, BuiltinTypeDecl::EnumOfBuiltinType result, bool commutativeLaw = true) {
            TypeUpgradeMatrix[(size_t)l][(size_t)r] = result;
            if (commutativeLaw) {
                TypeUpgradeMatrix[(size_t)r][(size_t)l] = result;
            }
        }

        void AddUpgrades(std::set<BuiltinTypeDecl::EnumOfBuiltinType> ls, std::set<BuiltinTypeDecl::EnumOfBuiltinType> rs, BuiltinTypeDecl::EnumOfBuiltinType result, bool commutativeLaw = true) {
            for (BuiltinTypeDecl::EnumOfBuiltinType l : ls) {
                for (BuiltinTypeDecl::EnumOfBuiltinType r : rs) {
                    AddUpgrade(l, r, result, commutativeLaw);
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
            this->AddValids({C, I, F, H, L, D}, {C, I, F, H, L, D}, {ADD, SUB, MUL, DIV, FULLDIV, MOD, EQU, NEQ, GT, LT, GE, LE});
            this->AddValids({B}, {B}, {AND, OR});
            this->AddValids({S}, {S}, {ADD, LIKE});
            this->AddValids({A}, {A}, {ADD});
            this->AddValids({T}, {}, {});
            this->AddValids({N}, {}, {});
            /*
             * 类型提升图
             * C→H→I→L
             *      ↓ ↓
             *      F→D
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

        bool OperateValid(BuiltinTypeDecl::EnumOfBuiltinType l, BuiltinTypeDecl::EnumOfBuiltinType r, _OperatorExpression::OperatorType operatorType) const {
            const std::set<_OperatorExpression::OperatorType> &valid_set = TypeValidMatrix[(size_t)l][(size_t)r];
            return valid_set.find(operatorType) != valid_set.end();
        }

        BuiltinTypeDecl::EnumOfBuiltinType TypeUpgrade(BuiltinTypeDecl::EnumOfBuiltinType l, BuiltinTypeDecl::EnumOfBuiltinType r) const {
            return TypeUpgradeMatrix[(size_t)l][(size_t)r];
        }
    } type_matrix;

    bool TypeAssert::IsBinaryOperationValid(TypeDecl *lhsType, TypeDecl *rhsType, _OperatorExpression::OperatorType operatorType) {
        // 只有内置类型才能执行二元运算
        BuiltinTypeDecl *lhsBuiltinType = lhsType->as<BuiltinTypeDecl>();
        BuiltinTypeDecl *rhsBuiltinType = rhsType->as<BuiltinTypeDecl>();
        if (lhsBuiltinType == nullptr || rhsBuiltinType == nullptr) {
            return false;
        }
        BuiltinTypeDecl::EnumOfBuiltinType lhsBTEnum = lhsBuiltinType->built_in_type_;
        BuiltinTypeDecl::EnumOfBuiltinType rhsBTEnum = rhsBuiltinType->built_in_type_;
        return type_matrix.OperateValid(lhsBTEnum, rhsBTEnum, operatorType);
    }

    BuiltinTypeDecl::EnumOfBuiltinType TypeAssert::ResultOfTypeUpgrade(BuiltinTypeDecl::EnumOfBuiltinType ltype, BuiltinTypeDecl::EnumOfBuiltinType rtype) {
        return type_matrix.TypeUpgrade(ltype, rtype);
    }

    bool TypeAssert::ExpressionIsLValue(Expression *expression) {
        return expression->is<HierarchyIdentifier>();
    }
}