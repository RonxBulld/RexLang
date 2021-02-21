//
// Created by rex on 2020/1/31.
//

#include "rtti.h"

namespace rexlang {

    /************************************************
     * 定义每个节点的 GetClassId 返回值
     ************************************************/

    const NodeType SourceFile           ::GetClassId() { return NodeType::kNTySourceFile; }
    const NodeType ProgramSetFile       ::GetClassId() { return NodeType::kNTyProgramSetFile; }
    const NodeType GlobalVariableFile   ::GetClassId() { return NodeType::kNTyGlobalVariableFile; }
    const NodeType DataStructureFile    ::GetClassId() { return NodeType::kNTyDataStructureFile; }
    const NodeType APIDeclareFile       ::GetClassId() { return NodeType::kNTyAPIDeclareFile; }
    const NodeType MacroDeclareFile     ::GetClassId() { return NodeType::kNTyMacroDeclareFile; }
    const NodeType IdentDef             ::GetClassId() { return NodeType::kNTyIdentDef; }
    const NodeType Decl                 ::GetClassId() { return NodeType::kNTyDecl; }
    const NodeType TagDecl              ::GetClassId() { return NodeType::kNTyTagDecl; }
    const NodeType BaseVariDecl         ::GetClassId() { return NodeType::kNTyBaseVariDecl; }
    const NodeType ParameterDecl        ::GetClassId() { return NodeType::kNTyParameterDecl; }
    const NodeType MacroDecl            ::GetClassId() { return NodeType::kNTyMacroDecl; }
    const NodeType VariableDecl         ::GetClassId() { return NodeType::kNTyVariableDecl; }
    const NodeType GlobalVariableDecl   ::GetClassId() { return NodeType::kNTyGlobalVariableDecl; }
    const NodeType MemberVariableDecl   ::GetClassId() { return NodeType::kNTyMemberVariableDecl; }
    const NodeType FileVariableDecl     ::GetClassId() { return NodeType::kNTyFileVariableDecl; }
    const NodeType LocalVariableDecl    ::GetClassId() { return NodeType::kNTyLocalVariableDecl; }
    const NodeType TypeDecl             ::GetClassId() { return NodeType::kNTyTypeDecl; }
    const NodeType VariTypeDecl         ::GetClassId() { return NodeType::kNTyVariTypeDecl; }
    const NodeType ReferenceType        ::GetClassId() { return NodeType::kNTyReferenceType; }
    const NodeType BuiltinType          ::GetClassId() { return NodeType::kNTyBuiltinType; }
    const NodeType StructureDecl        ::GetClassId() { return NodeType::kNTyStructureDecl; }
    const NodeType ArrayType            ::GetClassId() { return NodeType::kNTyArrayType; }
    const NodeType FunctorDecl          ::GetClassId() { return NodeType::kNTyFunctorDecl; }
    const NodeType FunctionDecl         ::GetClassId() { return NodeType::kNTyFunctionDecl; }
    const NodeType APICommandDecl       ::GetClassId() { return NodeType::kNTyAPICommandDecl; }
    const NodeType ProgSetDecl          ::GetClassId() { return NodeType::kNTyProgSetDecl; }
    const NodeType Statement            ::GetClassId() { return NodeType::kNTyStatement; }
    const NodeType AssignStmt           ::GetClassId() { return NodeType::kNTyAssignStmt; }
    const NodeType ControlStmt          ::GetClassId() { return NodeType::kNTyControlStmt; }
    const NodeType LoopControlStmt      ::GetClassId() { return NodeType::kNTyLoopControlStmt; }
    const NodeType ContinueStmt         ::GetClassId() { return NodeType::kNTyContinueStmt; }
    const NodeType BreakStmt            ::GetClassId() { return NodeType::kNTyBreakStmt; }
    const NodeType ReturnStmt           ::GetClassId() { return NodeType::kNTyReturnStmt; }
    const NodeType IfStmt               ::GetClassId() { return NodeType::kNTyIfStmt; }
    const NodeType WhileStmt            ::GetClassId() { return NodeType::kNTyWhileStmt; }
    const NodeType RangeForStmt         ::GetClassId() { return NodeType::kNTyRangeForStmt; }
    const NodeType ForStmt              ::GetClassId() { return NodeType::kNTyForStmt; }
    const NodeType DoWhileStmt          ::GetClassId() { return NodeType::kNTyDoWhileStmt; }
    const NodeType StatementBlock       ::GetClassId() { return NodeType::kNTyStatementBlock; }
    const NodeType Expression           ::GetClassId() { return NodeType::kNTyExpression; }
    const NodeType NameComponent        ::GetClassId() { return NodeType::kNTyNameComponent; }
    const NodeType IdentRefer           ::GetClassId() { return NodeType::kNTyIdentRefer; }
    const NodeType ArrayIndex           ::GetClassId() { return NodeType::kNTyArrayIndex; }
    const NodeType FunctionCall         ::GetClassId() { return NodeType::kNTyFunctionCall; }
    const NodeType TypeConvert          ::GetClassId() { return NodeType::kNTyTypeConvert; }
    const NodeType OperatedExpression   ::GetClassId() { return NodeType::kNTyOperatorExpression; }
    const NodeType UnaryExpression      ::GetClassId() { return NodeType::kNTyUnaryExpression; }
    const NodeType BinaryExpression     ::GetClassId() { return NodeType::kNTyBinaryExpression; }
    const NodeType Value                ::GetClassId() { return NodeType::kNTyValue; }
    const NodeType ValueOfDataSet       ::GetClassId() { return NodeType::kNTyValueOfDataSet; }
    const NodeType ValueOfDatetime      ::GetClassId() { return NodeType::kNTyValueOfDatetime; }
    const NodeType FuncAddrExpression   ::GetClassId() { return NodeType::kNTyFuncAddrExpression; }
    const NodeType ValueOfBool          ::GetClassId() { return NodeType::kNTyValueOfBool; }
    const NodeType ValueOfDecimal       ::GetClassId() { return NodeType::kNTyValueOfDecimal; }
    const NodeType ValueOfString        ::GetClassId() { return NodeType::kNTyValueOfString; }
    const NodeType TranslateUnit        ::GetClassId() { return NodeType::kNTyTranslateUnit; }

    /************************************************
     * 内建类型构造函数
     ************************************************/

    BuiltinVoidType    ::BuiltinVoidType    (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinCommonType  ::BuiltinCommonType  (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinCharType    ::BuiltinCharType    (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinIntegerType ::BuiltinIntegerType (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinFloatType   ::BuiltinFloatType   (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinBoolType    ::BuiltinBoolType    (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinStringType  ::BuiltinStringType  (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinDataSetType ::BuiltinDataSetType (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinShortType   ::BuiltinShortType   (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinLongType    ::BuiltinLongType    (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinDatetimeType::BuiltinDatetimeType(IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinFuncPtrType ::BuiltinFuncPtrType (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }
    BuiltinDoubleType  ::BuiltinDoubleType  (IdentDef *typeName) : BuiltinType(typeName, builtinType()) { }

    /************************************************
     * 内建类型 BuiltinType 返回值
     ************************************************/

    EnumOfBuiltinType BuiltinVoidType    ::builtinType() { return EnumOfBuiltinType::kBTypeVoid;     }
    EnumOfBuiltinType BuiltinCommonType  ::builtinType() { return EnumOfBuiltinType::kBTypeCommon;   }
    EnumOfBuiltinType BuiltinCharType    ::builtinType() { return EnumOfBuiltinType::kBTypeChar;     }
    EnumOfBuiltinType BuiltinIntegerType ::builtinType() { return EnumOfBuiltinType::kBTypeInteger;  }
    EnumOfBuiltinType BuiltinFloatType   ::builtinType() { return EnumOfBuiltinType::kBTypeFloat;    }
    EnumOfBuiltinType BuiltinBoolType    ::builtinType() { return EnumOfBuiltinType::kBTypeBool;     }
    EnumOfBuiltinType BuiltinStringType  ::builtinType() { return EnumOfBuiltinType::kBTypeString;   }
    EnumOfBuiltinType BuiltinDataSetType ::builtinType() { return EnumOfBuiltinType::kBTypeDataSet;  }
    EnumOfBuiltinType BuiltinShortType   ::builtinType() { return EnumOfBuiltinType::kBTypeShort;    }
    EnumOfBuiltinType BuiltinLongType    ::builtinType() { return EnumOfBuiltinType::kBTypeLong;     }
    EnumOfBuiltinType BuiltinDatetimeType::builtinType() { return EnumOfBuiltinType::kBTypeDatetime; }
    EnumOfBuiltinType BuiltinFuncPtrType ::builtinType() { return EnumOfBuiltinType::kBTypeFuncPtr;  }
    EnumOfBuiltinType BuiltinDoubleType  ::builtinType() { return EnumOfBuiltinType::kBTypeDouble;   }

    /**********************************************************
     * 获取内置类型枚举
     **********************************************************/

    EnumOfBuiltinType  BuiltinVoidType    ::GetBuiltinType () const { return BuiltinVoidType    ::builtinType(); }
    EnumOfBuiltinType  BuiltinCommonType  ::GetBuiltinType () const { return BuiltinCommonType  ::builtinType(); }
    EnumOfBuiltinType  BuiltinCharType    ::GetBuiltinType () const { return BuiltinCharType    ::builtinType(); }
    EnumOfBuiltinType  BuiltinIntegerType ::GetBuiltinType () const { return BuiltinIntegerType ::builtinType(); }
    EnumOfBuiltinType  BuiltinFloatType   ::GetBuiltinType () const { return BuiltinFloatType   ::builtinType(); }
    EnumOfBuiltinType  BuiltinBoolType    ::GetBuiltinType () const { return BuiltinBoolType    ::builtinType(); }
    EnumOfBuiltinType  BuiltinStringType  ::GetBuiltinType () const { return BuiltinStringType  ::builtinType(); }
    EnumOfBuiltinType  BuiltinDataSetType ::GetBuiltinType () const { return BuiltinDataSetType ::builtinType(); }
    EnumOfBuiltinType  BuiltinShortType   ::GetBuiltinType () const { return BuiltinShortType   ::builtinType(); }
    EnumOfBuiltinType  BuiltinLongType    ::GetBuiltinType () const { return BuiltinLongType    ::builtinType(); }
    EnumOfBuiltinType  BuiltinDatetimeType::GetBuiltinType () const { return BuiltinDatetimeType::builtinType(); }
    EnumOfBuiltinType  BuiltinFuncPtrType ::GetBuiltinType () const { return BuiltinFuncPtrType ::builtinType(); }
    EnumOfBuiltinType  BuiltinDoubleType  ::GetBuiltinType () const { return BuiltinDoubleType  ::builtinType(); }

    /************************************************
     * 定义内建类型节点的 typeText 返回值
     ************************************************/

    const char * BuiltinVoidType    ::typeText() { return u8"<空类型>";    }
    const char * BuiltinCommonType  ::typeText() { return u8"通用型";      }
    const char * BuiltinCharType    ::typeText() { return u8"字节型";      }
    const char * BuiltinIntegerType ::typeText() { return u8"整数型";      }
    const char * BuiltinFloatType   ::typeText() { return u8"小数型";      }
    const char * BuiltinBoolType    ::typeText() { return u8"逻辑型";      }
    const char * BuiltinStringType  ::typeText() { return u8"文本型";      }
    const char * BuiltinDataSetType ::typeText() { return u8"字节集";      }
    const char * BuiltinShortType   ::typeText() { return u8"短整型";      }
    const char * BuiltinLongType    ::typeText() { return u8"长整数型";     }
    const char * BuiltinDatetimeType::typeText() { return u8"日期时间型";    }
    const char * BuiltinFuncPtrType ::typeText() { return u8"子程序指针";    }
    const char * BuiltinDoubleType  ::typeText() { return u8"双精度小数型";   }

    /************************************************
     * 定义内建类型节点的 GetTypeText 返回值
     ************************************************/

    const char * BuiltinVoidType    ::GetTypeText() const { return BuiltinVoidType    ::typeText(); }
    const char * BuiltinCommonType  ::GetTypeText() const { return BuiltinCommonType  ::typeText(); }
    const char * BuiltinCharType    ::GetTypeText() const { return BuiltinCharType    ::typeText(); }
    const char * BuiltinIntegerType ::GetTypeText() const { return BuiltinIntegerType ::typeText(); }
    const char * BuiltinFloatType   ::GetTypeText() const { return BuiltinFloatType   ::typeText(); }
    const char * BuiltinBoolType    ::GetTypeText() const { return BuiltinBoolType    ::typeText(); }
    const char * BuiltinStringType  ::GetTypeText() const { return BuiltinStringType  ::typeText(); }
    const char * BuiltinDataSetType ::GetTypeText() const { return BuiltinDataSetType ::typeText(); }
    const char * BuiltinShortType   ::GetTypeText() const { return BuiltinShortType   ::typeText(); }
    const char * BuiltinLongType    ::GetTypeText() const { return BuiltinLongType    ::typeText(); }
    const char * BuiltinDatetimeType::GetTypeText() const { return BuiltinDatetimeType::typeText(); }
    const char * BuiltinFuncPtrType ::GetTypeText() const { return BuiltinFuncPtrType ::typeText(); }
    const char * BuiltinDoubleType  ::GetTypeText() const { return BuiltinDoubleType  ::typeText(); }

    /************************************************
     * 类型的可调用性
     ************************************************/

    bool TypeDecl   ::isCallable() const { return false; }
    bool FunctorDecl::isCallable() const { return true; }

    /************************************************
     * 类型的可索引性及索引元素类型
     ************************************************/

    bool TypeDecl           ::isIndexable() const { return false; }
    bool BuiltinStringType  ::isIndexable() const { return true; }
    bool BuiltinDataSetType ::isIndexable() const { return true; }
    bool ArrayType          ::isIndexable() const { return true; }

    TypeDecl *TypeDecl           ::evalIndexedElementTy() const { return nullptr; }
    TypeDecl *BuiltinStringType  ::evalIndexedElementTy() const { return this->getTranslateUnit()->getCharTy(); }
    TypeDecl *BuiltinDataSetType ::evalIndexedElementTy() const { return this->getTranslateUnit()->getCharTy(); }
    TypeDecl *ArrayType          ::evalIndexedElementTy() const { assert(base_type_); return base_type_; }

    /************************************************
     * 获取定义的索引维度
     ************************************************/

    std::vector<size_t> TypeDecl           ::getDimensions() const { return {}; }
    std::vector<size_t> BuiltinStringType  ::getDimensions() const { return {0}; }
    std::vector<size_t> BuiltinDataSetType ::getDimensions() const { return {0}; }
    std::vector<size_t> ArrayType          ::getDimensions() const { return this->dimensions_; }

    /**********************************************************
     * 维度数量是否可变
     * 数组变量的维度数总是可变的
     * 字符串和字节集维度总是固定为1
     **********************************************************/

    bool TypeDecl           ::isFixedDimensions() const { return true; }
    bool ArrayType          ::isFixedDimensions() const { return false; }
    bool BuiltinStringType  ::isFixedDimensions() const { return true; }
    bool BuiltinDataSetType ::isFixedDimensions() const { return true; }

    /************************************************
     * 注册及获取一个翻译单元中的内建类型
     ************************************************/

    BuiltinType *TranslateUnit::getBuiltinTy(EnumOfBuiltinType enumOfBuiltinType) const {
        BuiltinType *BT = builtin_type_map_.at(enumOfBuiltinType);
        assert(BT);
        return BT;
    }
    BuiltinVoidType *     TranslateUnit::getVoidTy     () const { BuiltinType *BT = builtin_type_map_.at(BuiltinVoidType    ::builtinType()); assert(BT); return (BuiltinVoidType *    ) BT; }
    BuiltinCommonType *   TranslateUnit::getCommonTy   () const { BuiltinType *BT = builtin_type_map_.at(BuiltinCommonType  ::builtinType()); assert(BT); return (BuiltinCommonType *  ) BT; }
    BuiltinCharType *     TranslateUnit::getCharTy     () const { BuiltinType *BT = builtin_type_map_.at(BuiltinCharType    ::builtinType()); assert(BT); return (BuiltinCharType *    ) BT; }
    BuiltinIntegerType *  TranslateUnit::getIntegerTy  () const { BuiltinType *BT = builtin_type_map_.at(BuiltinIntegerType ::builtinType()); assert(BT); return (BuiltinIntegerType * ) BT; }
    BuiltinFloatType *    TranslateUnit::getFloatTy    () const { BuiltinType *BT = builtin_type_map_.at(BuiltinFloatType   ::builtinType()); assert(BT); return (BuiltinFloatType *   ) BT; }
    BuiltinBoolType *     TranslateUnit::getBoolTy     () const { BuiltinType *BT = builtin_type_map_.at(BuiltinBoolType    ::builtinType()); assert(BT); return (BuiltinBoolType *    ) BT; }
    BuiltinStringType *   TranslateUnit::getStringTy   () const { BuiltinType *BT = builtin_type_map_.at(BuiltinStringType  ::builtinType()); assert(BT); return (BuiltinStringType *  ) BT; }
    BuiltinDataSetType *  TranslateUnit::getDataSetTy  () const { BuiltinType *BT = builtin_type_map_.at(BuiltinDataSetType ::builtinType()); assert(BT); return (BuiltinDataSetType * ) BT; }
    BuiltinShortType *    TranslateUnit::getShortTy    () const { BuiltinType *BT = builtin_type_map_.at(BuiltinShortType   ::builtinType()); assert(BT); return (BuiltinShortType *   ) BT; }
    BuiltinLongType *     TranslateUnit::getLongTy     () const { BuiltinType *BT = builtin_type_map_.at(BuiltinLongType    ::builtinType()); assert(BT); return (BuiltinLongType *    ) BT; }
    BuiltinDatetimeType * TranslateUnit::getDatetimeTy () const { BuiltinType *BT = builtin_type_map_.at(BuiltinDatetimeType::builtinType()); assert(BT); return (BuiltinDatetimeType *) BT; }
    BuiltinFuncPtrType *  TranslateUnit::getFuncPtrTy  () const { BuiltinType *BT = builtin_type_map_.at(BuiltinFuncPtrType ::builtinType()); assert(BT); return (BuiltinFuncPtrType * ) BT; }
    BuiltinDoubleType *   TranslateUnit::getDoubleTy   () const { BuiltinType *BT = builtin_type_map_.at(BuiltinDoubleType  ::builtinType()); assert(BT); return (BuiltinDoubleType *  ) BT; }

    bool TranslateUnit::RegistBuiltinType(BuiltinType *builtinType) {
        named_builtin_type_map_[StringPool::Create(builtinType->GetTypeText())] = builtinType;
        builtin_type_map_      [builtinType->GetBuiltinType()]                  = builtinType;
        return true;
    }

    bool TranslateUnit::InitBuiltinTypes() {
        auto ctx = this->getAstContext();
        assert(ctx);
        RegistBuiltinType(CreateNode<BuiltinVoidType    >(ctx, CreateNode<IdentDef>(ctx, BuiltinVoidType    ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinCommonType  >(ctx, CreateNode<IdentDef>(ctx, BuiltinCommonType  ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinCharType    >(ctx, CreateNode<IdentDef>(ctx, BuiltinCharType    ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinIntegerType >(ctx, CreateNode<IdentDef>(ctx, BuiltinIntegerType ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinFloatType   >(ctx, CreateNode<IdentDef>(ctx, BuiltinFloatType   ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinBoolType    >(ctx, CreateNode<IdentDef>(ctx, BuiltinBoolType    ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinStringType  >(ctx, CreateNode<IdentDef>(ctx, BuiltinStringType  ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinDataSetType >(ctx, CreateNode<IdentDef>(ctx, BuiltinDataSetType ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinShortType   >(ctx, CreateNode<IdentDef>(ctx, BuiltinShortType   ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinLongType    >(ctx, CreateNode<IdentDef>(ctx, BuiltinLongType    ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinDatetimeType>(ctx, CreateNode<IdentDef>(ctx, BuiltinDatetimeType::typeText())));
        RegistBuiltinType(CreateNode<BuiltinFuncPtrType >(ctx, CreateNode<IdentDef>(ctx, BuiltinFuncPtrType ::typeText())));
        RegistBuiltinType(CreateNode<BuiltinDoubleType  >(ctx, CreateNode<IdentDef>(ctx, BuiltinDoubleType  ::typeText())));
        return true;
    }


    /************************************************
     * 类型提取
     ************************************************/

    TypeDecl * ReferenceType::getPointee() const {
        assert(pointee_type_);
        return pointee_type_;
    }

    /******************************************
     * NameComponent 族
     ******************************************/

    TypeDecl * BaseVariDecl::getType() const { assert(type_); return type_; }
    TypeDecl * TypeDecl    ::getType() const { return const_cast<TypeDecl *>(this); }
    TypeDecl * ProgSetDecl ::getType() const { return nullptr; }

    TypeDecl * ArrayIndex::getElementTy() const {
        TypeDecl *type = getBaseId()->getExpressionType();
        if (VariTypeDecl *vari_type_decl = type->as<VariTypeDecl>()) {
            if (vari_type_decl->isIndexable()) {
                return vari_type_decl->evalIndexedElementTy();
            }
            else {
                assert(false);
                return nullptr;
            }
        }
        else {
            assert(false);
            return nullptr;
        }
    }

    /******************************************
     * TypeConvert
     ******************************************/

    Expression * TypeConvert::getSourceExpr () const { assert(from_expression_); return from_expression_; }
    TypeDecl *   TypeConvert::getSourceType () const { return from_expression_->getExpressionType(); }
    TypeDecl *   TypeConvert::getTargetType () const { assert(target_type_);     return target_type_; }

    /******************************************
     * 类型提升
     ******************************************/

    TypeDecl *TypeDecl::promoteType(TypeDecl *otherType) const { return nullptr; }

    VariTypeDecl *OperatedExpression::promoteType(VariTypeDecl *typeA, VariTypeDecl *typeB) const {
        assert(typeA);
        if (typeB) {
            return rtti::dyn_cast<VariTypeDecl>(typeA->promoteType(typeB));
        } else {
            return typeA;
        }
    }

    /*===-----------------------------------------------------===*
     * Void 不和任何类型共类型
     */

    TypeDecl *BuiltinVoidType::promoteType(TypeDecl *otherType) const {
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 通用型 暂时不和任何类型共类型
     */

    TypeDecl *BuiltinCommonType::promoteType(TypeDecl *otherType) const {
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 字符型
     * Char->Char
     * Short->Short
     * Int->Int
     * Long->Long
     * Float->Double
     * Double->Double
     */

    TypeDecl *BuiltinCharType::promoteType(TypeDecl *otherType) const {
        TranslateUnit *TU = getTranslateUnit();
        assert(TU);
        if (otherType->isCharType())    { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isShortType())   { return otherType; }
        if (otherType->isIntegerType()) { return otherType; }
        if (otherType->isLongType())    { return otherType; }
        if (otherType->isFloatType())   { return TU->getDoubleTy(); }
        if (otherType->isDoubleType())  { return TU->getDoubleTy(); }
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 短整型
     * Char->Short
     * Short->Short
     * Int->Int
     * Long->Long
     * Float->Double
     * Double->Double
     */

    TypeDecl *BuiltinShortType::promoteType(TypeDecl *otherType) const {
        TranslateUnit *TU = getTranslateUnit();
        assert(TU);
        if (otherType->isCharType())    { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isShortType())   { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isIntegerType()) { return otherType; }
        if (otherType->isLongType())    { return otherType; }
        if (otherType->isFloatType())   { return TU->getDoubleTy(); }
        if (otherType->isDoubleType())  { return TU->getDoubleTy(); }
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 整数型
     * Char->Int
     * Short->Int
     * Int->Int
     * Long->Long
     * Float->Double
     * Double->Double
     */

    TypeDecl *BuiltinIntegerType::promoteType(TypeDecl *otherType) const {
        TranslateUnit *TU = getTranslateUnit();
        assert(TU);
        if (otherType->isCharType())    { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isShortType())   { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isIntegerType()) { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isLongType())    { return otherType; }
        if (otherType->isFloatType())   { return TU->getDoubleTy(); }
        if (otherType->isDoubleType())  { return TU->getDoubleTy(); }
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 长整数型
     * Char->Long
     * Short->Long
     * Int->Long
     * Long->Long
     * Float->Double
     * Double->Double
     */

    TypeDecl *BuiltinLongType::promoteType(TypeDecl *otherType) const {
        TranslateUnit *TU = getTranslateUnit();
        assert(TU);
        if (otherType->isCharType())    { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isShortType())   { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isIntegerType()) { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isLongType())    { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isFloatType())   { return TU->getDoubleTy(); }
        if (otherType->isDoubleType())  { return TU->getDoubleTy(); }
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 小数型
     * Char->Double
     * Short->Double
     * Int->Double
     * Long->Double
     * Float->Float
     * Double->Double
     */

    TypeDecl *BuiltinFloatType::promoteType(TypeDecl *otherType) const {
        TranslateUnit *TU = getTranslateUnit();
        assert(TU);
        if (otherType->isCharType())    { return TU->getDoubleTy(); }
        if (otherType->isShortType())   { return TU->getDoubleTy(); }
        if (otherType->isIntegerType()) { return TU->getDoubleTy(); }
        if (otherType->isLongType())    { return TU->getDoubleTy(); }
        if (otherType->isFloatType())   { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isDoubleType())  { return TU->getDoubleTy(); }
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 双精度浮点型
     * Char->Double
     * Short->Double
     * Int->Double
     * Long->Double
     * Float->Double
     * Double->Double
     */

    TypeDecl *BuiltinDoubleType::promoteType(TypeDecl *otherType) const {
        TranslateUnit *TU = getTranslateUnit();
        assert(TU);
        if (otherType->isCharType())    { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isShortType())   { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isIntegerType()) { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isLongType())    { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isFloatType())   { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        if (otherType->isDoubleType())  { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 布尔型
     * Bool->Bool
     */

    TypeDecl *BuiltinBoolType::promoteType(TypeDecl *otherType) const {
        if (otherType->isBoolType()) { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 文本型
     * String->String
     */

    TypeDecl *BuiltinStringType::promoteType(TypeDecl *otherType) const {
        if (otherType->isStringType()) { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 字节集型
     * DataSet->DataSet
     */

    TypeDecl *BuiltinDataSetType::promoteType(TypeDecl *otherType) const {
        if (otherType->isDataSetType()) { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 字节集型
     * Datetime->Datetime
     */

    TypeDecl *BuiltinDatetimeType::promoteType(TypeDecl *otherType) const {
        if (otherType->isDatetimeType()) { return const_cast<TypeDecl *>(static_cast<const TypeDecl *>(this)); }
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 函数指针 暂时不和任何类型共类型
     */

    TypeDecl *BuiltinFuncPtrType::promoteType(TypeDecl *otherType) const {
        assert(false);
        return nullptr;
    }

    /*===-----------------------------------------------------===*
     * 结构体 暂时不和任何类型共类型
     */

    TypeDecl *StructureDecl::promoteType(TypeDecl *otherType) const {
        assert(false);
        return nullptr;
    }

    /******************************************
     * BinaryExpression
     ******************************************/

    VariTypeDecl *BinaryExpression::getBinaryOperateUpgradeType() const {
        if (!isBinaryOperateValid()) {
            assert(false);
            return nullptr;
        }

        VariTypeDecl *lhs_type = rtti::dyn_cast<VariTypeDecl>(lhs_->getExpressionType());
        assert(lhs_type);
        VariTypeDecl *rhs_type = rtti::dyn_cast<VariTypeDecl>(rhs_->getExpressionType());
        assert(rhs_type);

        return promoteType(lhs_type, rhs_type);
    }

}