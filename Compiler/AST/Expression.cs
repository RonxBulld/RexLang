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
        UserDefined,
    }

    public class PExpression : AstNode
    {

    }

    public class PValue : PExpression
    {

        public ValueType Type = ValueType.Integer;
        public char CharacterValue = '\0';
        public short ShortValue = 0;
        public int IntegerValue = 0;
        public long LongValue = 0;
        public float FloatValue = 0.0f;
        public double DoubleValue = 0.0;
        public bool BoolValue = false;
        public DateTime DateTimeValue;
        public string StringValue = null;
        public List<PExpression> CharSetValue;
        public UInt32 FuncPtrValue = 0;
        public string UserDefinedName = null;

        dynamic GetValue()
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
        private PValue _value = new PValue() { Type = ValueType.Integer };

        public int Value
        {
            get => _value.IntegerValue;
            set => _value.IntegerValue = value;
        }
    }

    public class PString : PExpression
    {
        private PValue _value = new PValue() { Type = ValueType.String };

        public string Value
        {
            get => _value.StringValue;
            set => _value.StringValue = value;
        }
    }

    public class PBool : PExpression
    {
        private PValue _value = new PValue() { Type = ValueType.Bool };

        public bool Value
        {
            get => _value.BoolValue;
            set => _value.BoolValue = value;
        }
    }

    public class PFloatNumber : PExpression
    {
        private PValue _value = new PValue() {Type = ValueType.Float};

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

    public class PUnaryExpr : PExpression
    {
        public enum UnaryOpt
        {
            Positive,
            Negative
        }

        public UnaryOpt Opt = UnaryOpt.Positive;
        public PExpression Expression = null;
    }

    public class PBinaryExpr : PExpression
    {
        public enum BinaryOpt
        {
            Add, Sub, Mul, Div, Mod
        }

        public BinaryOpt Opt = BinaryOpt.Add;
        public PExpression LExpression = null;
        public PExpression RExpression = null;
    }

}