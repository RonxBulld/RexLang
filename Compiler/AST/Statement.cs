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
            this.Statements = new List<PStatement>();
        }
    }

    public class PIfStatement : PStatement
    {
        public PExpression ConditionExpression = null;
        public PStatementList TrueStatementList = null;
        public PStatementList FalseStatementList = null;
    }

    public class PWhileStatement : PStatement
    {
        public PExpression ConditionExpression = null;
        public PStatementList StatementList = null;
    }

    public class PForStatement : PStatement
    {
        public PExpression LoopCount = null;
        public string Counter = null;
    }
}