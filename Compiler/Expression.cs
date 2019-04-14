using System.Collections.Generic;

namespace Compiler
{
    public class PExpression : AstNode
    {

    }

    public class PNumber : PExpression
    {
        public enum NumberType
        {
            Integer,
            Float,
            Double
        }

        public NumberType Type = NumberType.Integer;
        public int IntegerValue = 0;
        public float FloatValue = 0.0f;
        public double DoubleValue = 0.0;
    }

    public class PString : PExpression
    {
        public string Value = "";
    }

    public class PBool : PExpression
    {
        public bool Value = false;
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