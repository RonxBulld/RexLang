using System;
using System.Collections.Generic;

namespace Compiler.AST
{
    public enum ValueType
    {
        Character,
        Short,
        Integer,
        Long,
        Float,
        Double,
        Bool,
        DateTime,
        String,
        CharSet,
        FuncPtr,
        UserDefined
    }

    public class PExpression : PStatement
    {
    }

    public class PValue : PExpression
    {
        public bool BoolValue;
        public char CharacterValue = '\0';
        public List<PExpression> CharSetValue;
        public DateTime DateTimeValue;
        public double DoubleValue = 0.0;
        public float FloatValue;
        public uint FuncPtrValue = 0;
        public int IntegerValue;
        public long LongValue = 0;
        public short ShortValue = 0;
        public string StringValue;

        public ValueType Type = ValueType.Integer;
        public string UserDefinedName = null;

        private dynamic GetValue()
        {
            switch (Type)
            {
                case ValueType.Character: return CharacterValue;
                case ValueType.Short: return ShortValue;
                case ValueType.Integer: return IntegerValue;
                case ValueType.Long: return LongValue;
                case ValueType.Float: return FloatValue;
                case ValueType.Double: return DoubleValue;
                case ValueType.DateTime: return DateTimeValue;
                case ValueType.Bool: return BoolValue;
                case ValueType.String: return StringValue;
                case ValueType.CharSet: return CharSetValue;
                case ValueType.UserDefined: return FuncPtrValue;
                default:
                    throw new Exception("unrecognized type-" + Type);
            }
        }
    }

    public class PNumber : PExpression
    {
        private readonly PValue _value = new PValue {Type = ValueType.Integer};

        public int Value
        {
            get => _value.IntegerValue;
            set => _value.IntegerValue = value;
        }
    }

    public class PString : PExpression
    {
        private readonly PValue _value = new PValue {Type = ValueType.String};

        public string Value
        {
            get => _value.StringValue;
            set => _value.StringValue = value;
        }
    }

    public class PBool : PExpression
    {
        private readonly PValue _value = new PValue {Type = ValueType.Bool};

        public bool Value
        {
            get => _value.BoolValue;
            set => _value.BoolValue = value;
        }
    }

    public class PFloatNumber : PExpression
    {
        private readonly PValue _value = new PValue {Type = ValueType.Float};

        public float Value
        {
            get => _value.FloatValue;
            set => _value.FloatValue = value;
        }
    }

    public class PNameComponentList : PExpression
    {
        public List<PNameComponent> Components = new List<PNameComponent>();
    }

    public class PMacroValue : PExpression
    {
        public string Name = "";
    }

    public enum UnaryOpt
    {
        Positive,
        Negative
    }

    public class PUnaryExpr : PExpression
    {
        public static readonly Dictionary<int, UnaryOpt> LexOptMap = new Dictionary<int, UnaryOpt>
        {
            {openeLexer.K_ADD_OPT, UnaryOpt.Positive},
            {openeLexer.K_SUB_OPT, UnaryOpt.Negative}
        };

        public PExpression Expression = null;
        public UnaryOpt Opt = UnaryOpt.Positive;
    }

    public enum BinaryOpt
    {
        Add,
        Sub,
        Mul,
        Div,
        FullDiv,
        Mod,
        NotEqual,
        Equal,
        Less,
        Great,
        LessEqual,
        GreatEqual,
        LikeEqual,
        LogicAnd,
        LogicOr
    }

    public class PBinaryExpr : PExpression
    {
        public static readonly Dictionary<int, BinaryOpt> LexOptMap = new Dictionary<int, BinaryOpt>
        {
            // 四则
            {openeLexer.K_MUL_OPT, BinaryOpt.Mul},
            {openeLexer.K_DIV_OPT, BinaryOpt.Div},
            {openeLexer.K_FULL_DIV_OPT, BinaryOpt.FullDiv},
            {openeLexer.K_MOD_OPT, BinaryOpt.Mod},
            {openeLexer.K_ADD_OPT, BinaryOpt.Add},
            {openeLexer.K_SUB_OPT, BinaryOpt.Sub},
            // 比较
            {openeLexer.K_NOT_EQUAL_OPT, BinaryOpt.NotEqual},
            {openeLexer.K_EQUAL_OPT, BinaryOpt.Equal},
            {openeLexer.K_AECOM_OPT, BinaryOpt.Equal},
            {openeLexer.K_LESS_OPT, BinaryOpt.Less},
            {openeLexer.K_GREAT_OPT, BinaryOpt.Great},
            {openeLexer.K_LESS_EQU_OPT, BinaryOpt.LessEqual},
            {openeLexer.K_GREAT_EQU_OPT, BinaryOpt.GreatEqual},
            {openeLexer.K_LIKE_EQU_OPT, BinaryOpt.LikeEqual},
            // 逻辑
            {openeLexer.K_AND_OPT, BinaryOpt.LogicAnd},
            {openeLexer.K_OR_OPT, BinaryOpt.LogicOr}
        };

        public PExpression LExpression = null;
        public BinaryOpt Opt = BinaryOpt.Add;
        public PExpression RExpression = null;
    }
}