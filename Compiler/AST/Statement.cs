using System.Collections.Generic;

namespace Compiler.AST
{
    public class PStatement : AstNode
    {
    }

    public class PStatementList : AstNode
    {
        public List<PStatement> Statements;

        public PStatementList()
        {
            Statements = new List<PStatement>();
        }
    }

    public class PIfStatement : PStatement
    {
        public PExpression ConditionExpression = null;
        public PStatementList FalseStatementList = null;
        public PStatementList TrueStatementList = null;
    }

    public class PWhileStatement : PStatement
    {
        public PExpression ConditionExpression = null;
        public PStatementList StatementList = null;
    }

    public class PForStatement : PStatement
    {
        public string Counter = null;
        public PExpression LoopCount = null;
    }

    public class PAssignStatement : PStatement
    {
        public PExpression LExpression = null;
        public PExpression RExpression = null;
    }
}