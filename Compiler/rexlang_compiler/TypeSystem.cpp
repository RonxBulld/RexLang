//
// Created by rex on 2020/1/31.
//

#include "rtti.h"

namespace rexlang {

    BuiltinTypeDecl::BuiltinTypeDecl(const char *typeName, EnumOfBuiltinType typeEnum) {
        TString ts_name;
        ts_name.string_ = StringPool::Create(typeName);
        ts_name.location_ = 0;
        this->setName(ts_name);

        (void) typeEnum;
    }

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
    const NodeType BuiltinTypeDecl      ::GetClassId() { return NodeType::kNTyBuiltinTypeDecl; }
    const NodeType StructureDecl        ::GetClassId() { return NodeType::kNTyStructureDecl; }
    const NodeType ArrayDecl            ::GetClassId() { return NodeType::kNTyArrayDecl; }
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
    const NodeType ExitStmt             ::GetClassId() { return NodeType::kNTyExitStmt; }
    const NodeType IfStmt               ::GetClassId() { return NodeType::kNTyIfStmt; }
    const NodeType WhileStmt            ::GetClassId() { return NodeType::kNTyWhileStmt; }
    const NodeType RangeForStmt         ::GetClassId() { return NodeType::kNTyRangeForStmt; }
    const NodeType ForStmt              ::GetClassId() { return NodeType::kNTyForStmt; }
    const NodeType DoWhileStmt          ::GetClassId() { return NodeType::kNTyDoWhileStmt; }
    const NodeType StatementBlock       ::GetClassId() { return NodeType::kNTyStatementBlock; }
    const NodeType Expression           ::GetClassId() { return NodeType::kNTyExpression; }
    const NodeType HierarchyIdentifier  ::GetClassId() { return NodeType::kNTyHierarchyIdentifier; }
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

    BuiltinVoidType    ::BuiltinVoidType    () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinCommonType  ::BuiltinCommonType  () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinCharType    ::BuiltinCharType    () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinIntegerType ::BuiltinIntegerType () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinFloatType   ::BuiltinFloatType   () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinBoolType    ::BuiltinBoolType    () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinStringType  ::BuiltinStringType  () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinDataSetType ::BuiltinDataSetType () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinShortType   ::BuiltinShortType   () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinLongType    ::BuiltinLongType    () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinDatetimeType::BuiltinDatetimeType() : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinFuncPtrType ::BuiltinFuncPtrType () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }
    BuiltinDoubleType  ::BuiltinDoubleType  () : BuiltinTypeDecl(TypeText(), BuiltinType()) { }

    /************************************************
     * 内建类型 BuiltinType 返回值
     ************************************************/

    EnumOfBuiltinType BuiltinVoidType    ::BuiltinType() { return EnumOfBuiltinType::kBTypeVoid;     }
    EnumOfBuiltinType BuiltinCommonType  ::BuiltinType() { return EnumOfBuiltinType::kBTypeCommon;   }
    EnumOfBuiltinType BuiltinCharType    ::BuiltinType() { return EnumOfBuiltinType::kBTypeChar;     }
    EnumOfBuiltinType BuiltinIntegerType ::BuiltinType() { return EnumOfBuiltinType::kBTypeInteger;  }
    EnumOfBuiltinType BuiltinFloatType   ::BuiltinType() { return EnumOfBuiltinType::kBTypeFloat;    }
    EnumOfBuiltinType BuiltinBoolType    ::BuiltinType() { return EnumOfBuiltinType::kBTypeBool;     }
    EnumOfBuiltinType BuiltinStringType  ::BuiltinType() { return EnumOfBuiltinType::kBTypeString;   }
    EnumOfBuiltinType BuiltinDataSetType ::BuiltinType() { return EnumOfBuiltinType::kBTypeDataSet;  }
    EnumOfBuiltinType BuiltinShortType   ::BuiltinType() { return EnumOfBuiltinType::kBTypeShort;    }
    EnumOfBuiltinType BuiltinLongType    ::BuiltinType() { return EnumOfBuiltinType::kBTypeLong;     }
    EnumOfBuiltinType BuiltinDatetimeType::BuiltinType() { return EnumOfBuiltinType::kBTypeDatetime; }
    EnumOfBuiltinType BuiltinFuncPtrType ::BuiltinType() { return EnumOfBuiltinType::kBTypeFuncPtr;  }
    EnumOfBuiltinType BuiltinDoubleType  ::BuiltinType() { return EnumOfBuiltinType::kBTypeDouble;   }

    /**********************************************************
     * 获取内置类型枚举
     **********************************************************/

    EnumOfBuiltinType  BuiltinVoidType    ::GetBuiltinType () const { return BuiltinVoidType    ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinCommonType  ::GetBuiltinType () const { return BuiltinCommonType  ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinCharType    ::GetBuiltinType () const { return BuiltinCharType    ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinIntegerType ::GetBuiltinType () const { return BuiltinIntegerType ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinFloatType   ::GetBuiltinType () const { return BuiltinFloatType   ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinBoolType    ::GetBuiltinType () const { return BuiltinBoolType    ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinStringType  ::GetBuiltinType () const { return BuiltinStringType  ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinDataSetType ::GetBuiltinType () const { return BuiltinDataSetType ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinShortType   ::GetBuiltinType () const { return BuiltinShortType   ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinLongType    ::GetBuiltinType () const { return BuiltinLongType    ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinDatetimeType::GetBuiltinType () const { return BuiltinDatetimeType::BuiltinType(); }
    EnumOfBuiltinType  BuiltinFuncPtrType ::GetBuiltinType () const { return BuiltinFuncPtrType ::BuiltinType(); }
    EnumOfBuiltinType  BuiltinDoubleType  ::GetBuiltinType () const { return BuiltinDoubleType  ::BuiltinType(); }

    /************************************************
     * 定义内建类型节点的 TypeText 返回值
     ************************************************/

    const char * BuiltinVoidType    ::TypeText() { return u8"<空类型>";    }
    const char * BuiltinCommonType  ::TypeText() { return u8"通用型";      }
    const char * BuiltinCharType    ::TypeText() { return u8"字节型";      }
    const char * BuiltinIntegerType ::TypeText() { return u8"整数型";      }
    const char * BuiltinFloatType   ::TypeText() { return u8"小数型";      }
    const char * BuiltinBoolType    ::TypeText() { return u8"逻辑型";      }
    const char * BuiltinStringType  ::TypeText() { return u8"文本型";      }
    const char * BuiltinDataSetType ::TypeText() { return u8"字节集";      }
    const char * BuiltinShortType   ::TypeText() { return u8"短整型";      }
    const char * BuiltinLongType    ::TypeText() { return u8"长整数型";     }
    const char * BuiltinDatetimeType::TypeText() { return u8"日期时间型";    }
    const char * BuiltinFuncPtrType ::TypeText() { return u8"子程序指针";    }
    const char * BuiltinDoubleType  ::TypeText() { return u8"双精度小数型";   }

    /************************************************
     * 定义内建类型节点的 GetTypeText 返回值
     ************************************************/

    const char * BuiltinVoidType    ::GetTypeText() const { return BuiltinVoidType    ::TypeText(); }
    const char * BuiltinCommonType  ::GetTypeText() const { return BuiltinCommonType  ::TypeText(); }
    const char * BuiltinCharType    ::GetTypeText() const { return BuiltinCharType    ::TypeText(); }
    const char * BuiltinIntegerType ::GetTypeText() const { return BuiltinIntegerType ::TypeText(); }
    const char * BuiltinFloatType   ::GetTypeText() const { return BuiltinFloatType   ::TypeText(); }
    const char * BuiltinBoolType    ::GetTypeText() const { return BuiltinBoolType    ::TypeText(); }
    const char * BuiltinStringType  ::GetTypeText() const { return BuiltinStringType  ::TypeText(); }
    const char * BuiltinDataSetType ::GetTypeText() const { return BuiltinDataSetType ::TypeText(); }
    const char * BuiltinShortType   ::GetTypeText() const { return BuiltinShortType   ::TypeText(); }
    const char * BuiltinLongType    ::GetTypeText() const { return BuiltinLongType    ::TypeText(); }
    const char * BuiltinDatetimeType::GetTypeText() const { return BuiltinDatetimeType::TypeText(); }
    const char * BuiltinFuncPtrType ::GetTypeText() const { return BuiltinFuncPtrType ::TypeText(); }
    const char * BuiltinDoubleType  ::GetTypeText() const { return BuiltinDoubleType  ::TypeText(); }

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
    bool ArrayDecl          ::isIndexable() const { return true; }

    TypeDecl *TypeDecl           ::evalIndexedElementTy() const { return nullptr; }
    TypeDecl *BuiltinStringType  ::evalIndexedElementTy() const { return this->getTranslateUnit()->getCharTy(); }
    TypeDecl *BuiltinDataSetType ::evalIndexedElementTy() const { return this->getTranslateUnit()->getCharTy(); }
    TypeDecl *ArrayDecl          ::evalIndexedElementTy() const { assert(base_type_); return base_type_; }

    /************************************************
     * 获取定义的索引维度
     ************************************************/

    std::vector<size_t> TypeDecl           ::getDimensions() const { return {}; }
    std::vector<size_t> BuiltinStringType  ::getDimensions() const { return {0}; }
    std::vector<size_t> BuiltinDataSetType ::getDimensions() const { return {0}; }
    std::vector<size_t> ArrayDecl          ::getDimensions() const { return this->dimensions_; }

    /**********************************************************
     * 维度数量是否可变
     * 数组变量的维度数总是可变的
     * 字符串和字节集维度总是固定为1
     **********************************************************/

    bool TypeDecl           ::isFixedDimensions() const { return true; }
    bool ArrayDecl          ::isFixedDimensions() const { return false; }
    bool BuiltinStringType  ::isFixedDimensions() const { return true; }
    bool BuiltinDataSetType ::isFixedDimensions() const { return true; }

    /************************************************
     * 注册及获取一个翻译单元中的内建类型
     ************************************************/

    BuiltinTypeDecl *TranslateUnit::getBuiltinTy(EnumOfBuiltinType enumOfBuiltinType) const {
        BuiltinTypeDecl *BT = builtin_type_map_.at(enumOfBuiltinType);
        assert(BT);
        return BT;
    }
    BuiltinVoidType *     TranslateUnit::getVoidTy     () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinVoidType    ::BuiltinType()); assert(BT); return (BuiltinVoidType *    ) BT; }
    BuiltinCommonType *   TranslateUnit::getCommonTy   () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinCommonType  ::BuiltinType()); assert(BT); return (BuiltinCommonType *  ) BT; }
    BuiltinCharType *     TranslateUnit::getCharTy     () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinCharType    ::BuiltinType()); assert(BT); return (BuiltinCharType *    ) BT; }
    BuiltinIntegerType *  TranslateUnit::getIntegerTy  () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinIntegerType ::BuiltinType()); assert(BT); return (BuiltinIntegerType * ) BT; }
    BuiltinFloatType *    TranslateUnit::getFloatTy    () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinFloatType   ::BuiltinType()); assert(BT); return (BuiltinFloatType *   ) BT; }
    BuiltinBoolType *     TranslateUnit::getBoolTy     () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinBoolType    ::BuiltinType()); assert(BT); return (BuiltinBoolType *    ) BT; }
    BuiltinStringType *   TranslateUnit::getStringTy   () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinStringType  ::BuiltinType()); assert(BT); return (BuiltinStringType *  ) BT; }
    BuiltinDataSetType *  TranslateUnit::getDataSetTy  () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinDataSetType ::BuiltinType()); assert(BT); return (BuiltinDataSetType * ) BT; }
    BuiltinShortType *    TranslateUnit::getShortTy    () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinShortType   ::BuiltinType()); assert(BT); return (BuiltinShortType *   ) BT; }
    BuiltinLongType *     TranslateUnit::getLongTy     () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinLongType    ::BuiltinType()); assert(BT); return (BuiltinLongType *    ) BT; }
    BuiltinDatetimeType * TranslateUnit::getDatetimeTy () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinDatetimeType::BuiltinType()); assert(BT); return (BuiltinDatetimeType *) BT; }
    BuiltinFuncPtrType *  TranslateUnit::getFuncPtrTy  () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinFuncPtrType ::BuiltinType()); assert(BT); return (BuiltinFuncPtrType * ) BT; }
    BuiltinDoubleType *   TranslateUnit::getDoubleTy   () const { BuiltinTypeDecl *BT = builtin_type_map_.at(BuiltinDoubleType  ::BuiltinType()); assert(BT); return (BuiltinDoubleType *  ) BT; }

    bool TranslateUnit::RegistBuiltinType(BuiltinTypeDecl *builtinTypeDecl) {
        named_builtin_type_map_[StringPool::Create(builtinTypeDecl->GetTypeText())] = builtinTypeDecl;
        builtin_type_map_      [builtinTypeDecl->GetBuiltinType()]                  = builtinTypeDecl;
        return true;
    }

    bool TranslateUnit::InitBuiltinTypes() {
        auto ctx = this->getAstContext();
        RegistBuiltinType(CreateNode<BuiltinVoidType    >(ctx));
        RegistBuiltinType(CreateNode<BuiltinCommonType  >(ctx));
        RegistBuiltinType(CreateNode<BuiltinCharType    >(ctx));
        RegistBuiltinType(CreateNode<BuiltinIntegerType >(ctx));
        RegistBuiltinType(CreateNode<BuiltinFloatType   >(ctx));
        RegistBuiltinType(CreateNode<BuiltinBoolType    >(ctx));
        RegistBuiltinType(CreateNode<BuiltinStringType  >(ctx));
        RegistBuiltinType(CreateNode<BuiltinDataSetType >(ctx));
        RegistBuiltinType(CreateNode<BuiltinShortType   >(ctx));
        RegistBuiltinType(CreateNode<BuiltinLongType    >(ctx));
        RegistBuiltinType(CreateNode<BuiltinDatetimeType>(ctx));
        RegistBuiltinType(CreateNode<BuiltinFuncPtrType >(ctx));
        RegistBuiltinType(CreateNode<BuiltinDoubleType  >(ctx));
        return true;
    }


    /************************************************
     * 类型提取
     ************************************************/

    TypeDecl * ReferenceType::getPointee() const {
        if (pointee_type_) {
            return pointee_type_;
        }
        else {
            return rtti::dyn_cast<TypeDecl>(type_name_->getDecl());
        }
    }

    /******************************************
     * NameComponent 族
     ******************************************/

    TypeDecl * BaseVariDecl::getType() const { return type_ ? type_ : rtti::dyn_cast<TypeDecl>(type_name_->getDecl()); }
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

}