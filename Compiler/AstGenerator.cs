using System;
using System.Collections.Generic;
using Antlr4.Runtime;
using Antlr4.Runtime.Tree;

namespace Compiler
{
    class OpenEAstVisitor : IopeneVisitor<AstNode>
    {
        private ErrorManager errorManager = null;

        public OpenEAstVisitor(ref ErrorManager errorManager)
        {
            this.errorManager = errorManager;
        }

        public AstNode VisitOpene_src(openeParser.Opene_srcContext context)
        {
            PCompileUnit compileUnit = new PCompileUnit();
            // Edtion
            if (Visit(context.edition_spec()) is PNumber version)
            {
                compileUnit.Version = version.IntegerValue;
            }
            else
            {
                return null;
            }

            // Library list
            if (Visit(context.library_list_opt()) is PLibraries libraries)
            {
                compileUnit.Libraries = libraries.Libraries;
            }
            else
            {
                return null;
            }

            if (Visit(context.prog_set()) is PProgramSet programSet)
            {
                // Program set name
                compileUnit.ProgramSetName = programSet.ProgramSetName;
                // Program set local variables
                compileUnit.VariableDecls = programSet.VariableDecls;
                // Program set functions
                compileUnit.Functions = programSet.Functions;
            }
            else
            {
                return null;
            }

            return compileUnit;
        }

        public AstNode VisitEdition_spec(openeParser.Edition_specContext context)
        {
            int ver = Convert.ToInt32(context.INTEGER_LITERAL().GetText());
            if (ver != 2)
            {
                this.errorManager.VersionFailed(2, ver);
                return null;
            }

            PNumber versionNode = new PNumber();
            versionNode.IntegerValue = ver;
            return versionNode;
        }

        public AstNode VisitLibrary_list_opt(openeParser.Library_list_optContext context)
        {
            List<string> libraryList = new List<string>();
            foreach (var lib in context.library_spec())
            {
                PLibrary library = Visit(lib) as PLibrary;
                if (library == null)
                {
                    return null;
                }

                libraryList.Add(library.Library);
            }

            return new PLibraries(libraryList);
        }

        public AstNode VisitLibrary_spec(openeParser.Library_specContext context)
        {
            string library = context.IDENTIFIER().GetText();
            return new PLibrary(library);
        }

        public AstNode VisitProg_set(openeParser.Prog_setContext context)
        {
            PProgramSet programSet = new PProgramSet();
            // Program set name
            programSet.ProgramSetName = context.IDENTIFIER().GetText();
            // Program set local variable declare list
            if (Visit(context.prog_set_variable_decl_opt()) is PVariableDeclList variableDeclList)
            {
                programSet.VariableDecls = variableDeclList.VariableDecls;
            }
            else
            {
                return null;
            }

            // Program set function list
            if (Visit(context.sub_program_opt()) is PFunctionList functionList)
            {
                programSet.Functions = functionList.Functions;
            }

            return programSet;
        }

        public AstNode VisitProg_set_variable_decl_opt(openeParser.Prog_set_variable_decl_optContext context)
        {
            PVariableDeclList variableDeclList = new PVariableDeclList();
            foreach (var declContext in context.prog_set_variable_decl())
            {
                PVariableDecl decl = Visit(declContext) as PVariableDecl;
                variableDeclList.VariableDecls.Add(decl);
            }

            return variableDeclList;
        }

        public AstNode VisitProg_set_variable_decl(openeParser.Prog_set_variable_declContext context)
        {
            return Visit(context.variable_decl());
        }

        public AstNode VisitVariable_decl(openeParser.Variable_declContext context)
        {
            PVariableDecl variableDecl = new PVariableDecl();

            if (Visit(context.variable_name()) is PVariableName variableName)
                variableDecl.VariableName = variableName.Name;
            else
                return null;

            if (Visit(context.variable_type()) is PVariableTypeName variableTypeName)
                variableDecl.VariableType = variableTypeName.Name;
            else
                return null;

            if (Visit(context.dimension_decl()) is PDimensionDecl dimensionDecl)
                variableDecl.Dimensions = dimensionDecl.Dimension;
            else
                return null;

            return variableDecl;
        }

        public AstNode VisitVariable_comment(openeParser.Variable_commentContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitVariable_comment_element(openeParser.Variable_comment_elementContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitVariable_name(openeParser.Variable_nameContext context)
        {
            return new PVariableName(context.IDENTIFIER().GetText());
        }

        public AstNode VisitVariable_type(openeParser.Variable_typeContext context)
        {
            return new PVariableTypeName(context.IDENTIFIER().GetText());
        }

        public AstNode VisitDimension_decl(openeParser.Dimension_declContext context)
        {
            PDimensionDecl dimensionDecl = new PDimensionDecl();
            int dimension = Convert.ToInt32(context.INTEGER_LITERAL().GetText());
            if (dimension < 0)
            {
                if (this.errorManager.DimensionMustMoreThanZero(dimension))
                    dimension = 0;
                else
                    return null;
            }

            dimensionDecl.Dimension.Add(dimension);
            return dimensionDecl;
        }

        public AstNode VisitSub_program_opt(openeParser.Sub_program_optContext context)
        {
            PFunctionList functionList = new PFunctionList();
            foreach (var funcNode in context.sub_program())
            {
                if (Visit(funcNode) is PFunction func)
                {
                    functionList.Functions.Add(func);
                }
            }

            return functionList;
        }

        public AstNode VisitSub_program(openeParser.Sub_programContext context)
        {
            PFunction function = new PFunction();
            // name
            function.Name = context.IDENTIFIER().GetText();
            // return type
            if (context.variable_type().IsEmpty)
            {
                function.ReturnType = null;
            }
            else
            {
                if (Visit(context.variable_type()) is PVariableTypeName variableTypeName)
                {
                    function.ReturnType = variableTypeName.Name;
                }
                else
                {
                    return null;
                }
            }

            // parameter list
            if (Visit(context.parameter_decl_list()) is PVariableDeclList parameterDeclList)
            {
                function.ParameterDecls = parameterDeclList.VariableDecls;
            }
            else
            {
                return null;
            }

            // local variable list
            function.LocalVariableDecls = new List<PVariableDecl>();
            foreach (var localVariableDeclContext in context.local_variable_decl())
            {
                if (Visit(localVariableDeclContext) is PVariableDecl localVariableDecl)
                {
                    function.LocalVariableDecls.Add(localVariableDecl);
                }
                else
                {
                    return null;
                }
            }

            // statement list
            if (Visit(context.statement_list()) is PStatementList statementList)
            {
                function.Statements = statementList.Statements;
            }
            else
            {
                return null;
            }

            return function;
        }

        public AstNode VisitParameter_decl_list(openeParser.Parameter_decl_listContext context)
        {
            PVariableDeclList variableDeclList = new PVariableDeclList();
            foreach (var parameterDeclContext in context.parameter_decl())
            {
                if (Visit(parameterDeclContext) is PVariableDecl variableDecl)
                {
                    variableDeclList.VariableDecls.Add(variableDecl);
                }
                else
                {
                    return null;
                }
            }

            return variableDeclList;
        }

        public AstNode VisitParameter_decl(openeParser.Parameter_declContext context)
        {
            return Visit(context.variable_decl());
        }

        public AstNode VisitLocal_variable_decl(openeParser.Local_variable_declContext context)
        {
            return Visit(context.variable_decl());
        }

        public AstNode VisitStatement_list(openeParser.Statement_listContext context)
        {
            PStatementList statementList = new PStatementList();
            foreach (var statementContext in context.statement())
            {
                if (Visit(statementContext) is PStatement statement)
                {
                    statementList.Statements.Add(statement);
                }
                else
                {
                    return null;
                }
            }

            return statementList;
        }

        public AstNode VisitStatement(openeParser.StatementContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitIfStmt(openeParser.IfStmtContext context)
        {
            PIfStatement ifStatement = new PIfStatement();
            // Condition expression
            ifStatement.ConditionExpression = Visit(context.expression()) as PExpression;
            if (ifStatement.ConditionExpression == null)
                return null;
            // True statement list
            ifStatement.TrueStatementList = Visit(context.statement_list()) as PStatementList;
            if (ifStatement.TrueStatementList == null)
                return null;
            // Else statement list
            if (context.condition_statement_else().IsEmpty == false)
            {
                ifStatement.FalseStatementList = Visit(context.condition_statement_else()) as PStatementList;
                if (ifStatement.FalseStatementList == null)
                    return null;
            }

            return ifStatement;
        }

        public AstNode VisitIfTrueStmt(openeParser.IfTrueStmtContext context)
        {
            PIfStatement ifStatement = new PIfStatement();
            // Condition expression
            ifStatement.ConditionExpression = Visit(context.expression()) as PExpression;
            if (ifStatement.ConditionExpression == null)
                return null;
            // True statement list
            ifStatement.TrueStatementList = Visit(context.statement_list()) as PStatementList;
            if (ifStatement.TrueStatementList == null)
                return null;
            ifStatement.FalseStatementList = null;
            return ifStatement;
        }

        public AstNode VisitCondition_statement_else(openeParser.Condition_statement_elseContext context)
        {
            return Visit(context.statement_list());
        }

        public AstNode VisitHierarchy_identifier(openeParser.Hierarchy_identifierContext context)
        {
            PNameComponentList componentList = new PNameComponentList();
            foreach (var nameComponentContext in context.name_component())
            {
                if (Visit(nameComponentContext) is PNameComponent component)
                {
                    componentList.Components.Add(component);
                }
                else
                {
                    return null;
                }
            }

            return componentList;
        }

        public AstNode VisitIdentifier(openeParser.IdentifierContext context)
        {
            PNameComponent component = new PNameComponent();
            component.Type = PNameComponent.ComponentType.Identifier;
            component.Name = context.IDENTIFIER().GetText();
            return component;
        }

        public AstNode VisitFuncCallWithoutArgu(openeParser.FuncCallWithoutArguContext context)
        {
            PNameComponent component = new PNameComponent();
            component.Type = PNameComponent.ComponentType.FuncCall;
            component.Name = context.IDENTIFIER().GetText();
            return component;
        }

        public AstNode VisitFuncCallWithArgu(openeParser.FuncCallWithArguContext context)
        {
            PNameComponent component = new PNameComponent();
            component.Type = PNameComponent.ComponentType.FuncCall;
            component.Name = context.IDENTIFIER().GetText();
            foreach (var expressionContext in context.expression())
            {
                if (Visit(expressionContext) is PExpression expression)
                {
                    component.Expressions.Add(expression);
                }
                else
                {
                    return null;
                }
            }

            return component;
        }

        public AstNode VisitArrayIndex(openeParser.ArrayIndexContext context)
        {
            PNameComponent component = new PNameComponent();
            component.Type = PNameComponent.ComponentType.ArrayIndex;
            component.Name = context.IDENTIFIER().GetText();
            if (Visit(context.expression()) is PExpression expression)
            {
                component.Expressions.Add(expression);
            }
            else
            {
                return null;
            }

            return component;
        }

        public AstNode VisitBracket(openeParser.BracketContext context)
        {
            return Visit(context.expression());
        }

        public AstNode VisitOptElement(openeParser.OptElementContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitBinaryExpr(openeParser.BinaryExprContext context)
        {
            PBinaryExpr binaryExpr = new PBinaryExpr();
            // Binary expression operate code.
            switch (context.opt.Type)
            {
                case openeLexer.K_ADD_OPT:
                    binaryExpr.Opt = PBinaryExpr.BinaryOpt.Add;
                    break;
                case openeLexer.K_SUB_OPT:
                    binaryExpr.Opt = PBinaryExpr.BinaryOpt.Sub;
                    break;
                case openeLexer.K_MUL_OPT:
                    binaryExpr.Opt = PBinaryExpr.BinaryOpt.Mul;
                    break;
                case openeLexer.K_DIV_OPT:
                    binaryExpr.Opt = PBinaryExpr.BinaryOpt.Div;
                    break;
                default:
                    throw new Exception("no such binary opt=" + context.opt.Type);
            }
            // Check if 2 expression.
            if (context.expression().Length != 2)
            {
                return null;
            }
            // Left value expression.
            if (Visit(context.expression(0)) is PExpression lexpression)
            {
                binaryExpr.LExpression = lexpression;
            }
            else
            {
                return null;
            }
            // Right value expression.
            if (Visit(context.expression(1)) is PExpression rexpression)
            {
                binaryExpr.RExpression = rexpression;
            }
            else
            {
                return null;
            }

            return binaryExpr;
        }

        public AstNode VisitUnaryExpr(openeParser.UnaryExprContext context)
        {
            PUnaryExpr unaryExpr = new PUnaryExpr();
            // Unary expression operate code.
            switch (context.opt.Type)
            {
                case '-':
                    break;
                default:
                    throw new Exception("no such unary opt=" + context.opt.Type);
                    break;
            }

            if (Visit(context.expression()) is PExpression expression)
            {
                unaryExpr.Expression = expression;
            }
            else
            {
                return null;
            }

            return unaryExpr;
        }

        public AstNode VisitMacro_value(openeParser.Macro_valueContext context)
        {
            PMacroValue macroValue = new PMacroValue();
            macroValue.Name = context.IDENTIFIER().GetText();
            return macroValue;
        }

        public AstNode VisitString_value(openeParser.String_valueContext context)
        {
            PString stringValue = new PString();
            stringValue.Value = context.STRING_LITERAL().GetText();
            return stringValue;
        }

        public AstNode VisitBool_value(openeParser.Bool_valueContext context)
        {
            PBool boolValue = new PBool();
            if (context.bval.Type == openeLexer.K_TRUE)
            {
                boolValue.Value = true;
            }
            else if (context.bval.Type == openeLexer.K_FALSE)
            {
                boolValue.Value = false;
            }
            else
            {
                throw new Exception("no such bool value=" + context.bval);
                return null;
            }

            return boolValue;
        }

        public AstNode VisitInt(openeParser.IntContext context)
        {
            PNumber numberValue = new PNumber();
            numberValue.Type = PNumber.NumberType.Integer;
            numberValue.IntegerValue = Convert.ToInt32(context.INTEGER_LITERAL().GetText());
            return numberValue;
        }

        public AstNode VisitFloat(openeParser.FloatContext context)
        {
            PNumber numberValue = new PNumber();
            numberValue.Type = PNumber.NumberType.Float;
            numberValue.FloatValue = Convert.ToSingle(context.FLOAT_LITERAL().GetText());
            return numberValue;
        }

        public AstNode Visit(IParseTree tree)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitChildren(IRuleNode node)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitTerminal(ITerminalNode node)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitErrorNode(IErrorNode node)
        {
            throw new NotImplementedException();
        }
    }

    class AstGenerator
    {
        public AstNode GenerateAst(IParseTree parseTree, ref ErrorManager errorManager)
        {
            IopeneVisitor<AstNode> visitor = new OpenEAstVisitor(ref errorManager);
            AstNode ast = visitor.Visit(parseTree);
            return ast;
        }
    }
}