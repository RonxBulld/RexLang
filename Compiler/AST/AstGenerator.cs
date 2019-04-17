using System;
using System.Collections.Generic;
using Antlr4.Runtime.Tree;

namespace Compiler.AST
{
    internal class OpenEAstVisitor : openeBaseVisitor<AstNode>
    {
        private readonly ErrorManager errorManager;

        public OpenEAstVisitor(ref ErrorManager errorManager)
        {
            this.errorManager = errorManager;
        }

        public AstNode Error()
        {
            throw new Exception("Parse error.");
            return null;
        }

        public override AstNode VisitOpene_src(openeParser.Opene_srcContext context)
        {
            var compile_unit = new PCompileUnit();
            // Version
            if (Visit(context.edition_spec()) is PNumber version)
                compile_unit.Version = version.Value;
            else
                return Error();

            // Library list
            if (Visit(context.library_list_opt()) is PLibraries libraries)
                compile_unit.Libraries = libraries.Libraries;
            else
                return Error();

            if (Visit(context.prog_set()) is PProgramSet program_set)
            {
                // Program set name
                compile_unit.ProgramSetName = program_set.ProgramSetName;
                // Program set local variables
                compile_unit.VariableDecls = program_set.VariableDecls;
                // Program set functions
                compile_unit.Functions = program_set.Functions;
            }
            else
            {
                return Error();
            }

            return compile_unit;
        }

        public override AstNode VisitEdition_spec(openeParser.Edition_specContext context)
        {
            var ver = Convert.ToInt32(context.INTEGER_LITERAL().GetText());
            if (ver != 2)
            {
                errorManager.VersionFailed(2, ver);
                return Error();
            }

            var version_node = new PNumber();
            version_node.Value = ver;
            return version_node;
        }

        public override AstNode VisitLibrary_list_opt(openeParser.Library_list_optContext context)
        {
            var library_list = new List<string>();
            foreach (var lib in context.library_spec())
            {
                var library = Visit(lib) as PLibrary;
                if (library == null) return Error();

                library_list.Add(library.Library);
            }

            return new PLibraries(library_list);
        }

        public override AstNode VisitLibrary_spec(openeParser.Library_specContext context)
        {
            string library = context.IDENTIFIER().GetText();
            return new PLibrary(library);
        }

        public override AstNode VisitProg_set(openeParser.Prog_setContext context)
        {
            var program_set = new PProgramSet();
            // Program set name
            program_set.ProgramSetName = context.IDENTIFIER().GetText();
            // Program set local variable declare list
            if (Visit(context.prog_set_variable_decl_opt()) is PVariableDeclList variable_decl_list)
                program_set.VariableDecls = variable_decl_list.VariableDecls;
            else
                return Error();

            // Program set function list
            if (Visit(context.sub_program_opt()) is PFunctionList function_list) program_set.Functions = function_list.Functions;

            return program_set;
        }

        public override AstNode VisitProg_set_variable_decl_opt(openeParser.Prog_set_variable_decl_optContext context)
        {
            var variable_decl_list = new PVariableDeclList();
            foreach (var decl_context in context.prog_set_variable_decl())
            {
                var decl = Visit(decl_context) as PVariableDecl;
                variable_decl_list.VariableDecls.Add(decl);
            }

            return variable_decl_list;
        }

        public override AstNode VisitProg_set_variable_decl(openeParser.Prog_set_variable_declContext context)
        {
            return Visit(context.variable_decl());
        }

        public override AstNode VisitVariable_decl(openeParser.Variable_declContext context)
        {
            var variable_decl = new PVariableDecl();
            // Variable name.
            if (Visit(context.variable_name()) is PVariableName variable_name)
                variable_decl.VariableName = variable_name.Name;
            else
                return Error();
            // Variable type.
            if (Visit(context.variable_type()) is PVariableTypeName variable_type_name)
                variable_decl.VariableType = variable_type_name.Name;
            else
                return Error();
            // Variable dimension.
            if (context.dimension_decl() != null && context.dimension_decl().IsEmpty == false)
            {
                if (Visit(context.dimension_decl()) is PDimensionDecl dimension_decl)
                    variable_decl.Dimensions = dimension_decl.Dimension;
                else
                    return Error();
            }

            return variable_decl;
        }

        public override AstNode VisitVariable_comment(openeParser.Variable_commentContext context)
        {
            throw new NotImplementedException();
        }

        public override AstNode VisitVariable_comment_element(openeParser.Variable_comment_elementContext context)
        {
            throw new NotImplementedException();
        }

        public override AstNode VisitVariable_name(openeParser.Variable_nameContext context)
        {
            return new PVariableName(context.IDENTIFIER().GetText());
        }

        public override AstNode VisitVariable_type(openeParser.Variable_typeContext context)
        {
            return new PVariableTypeName(context.IDENTIFIER().GetText());
        }

        public override AstNode VisitDimension_decl(openeParser.Dimension_declContext context)
        {
            var dimension_decl = new PDimensionDecl();
            var dimension = Convert.ToInt32(context.INTEGER_LITERAL().GetText());
            if (dimension < 0)
            {
                if (errorManager.DimensionMustMoreThanZero(dimension))
                    dimension = 0;
                else
                    return Error();
            }

            dimension_decl.Dimension.Add(dimension);
            return dimension_decl;
        }

        public override AstNode VisitSub_program_opt(openeParser.Sub_program_optContext context)
        {
            var function_list = new PFunctionList();
            foreach (var func_node in context.sub_program())
                if (Visit(func_node) is PFunction func)
                    function_list.Functions.Add(func);

            return function_list;
        }

        public override AstNode VisitSub_program(openeParser.Sub_programContext context)
        {
            var function = new PFunction();
            // name
            function.Name = context.IDENTIFIER().GetText();
            // return type
            if (context.variable_type() == null || context.variable_type().IsEmpty)
            {
                function.ReturnType = null;
            }
            else
            {
                if (Visit(context.variable_type()) is PVariableTypeName variable_type_name)
                    function.ReturnType = variable_type_name.Name;
                else
                    return Error();
            }

            // parameter list
            if (Visit(context.parameter_decl_list()) is PVariableDeclList parameter_decl_list)
                function.ParameterDecls = parameter_decl_list.VariableDecls;
            else
                return Error();

            // local variable list
            function.LocalVariableDecls = new List<PVariableDecl>();
            foreach (var local_variable_decl_context in context.local_variable_decl())
                if (Visit(local_variable_decl_context) is PVariableDecl local_variable_decl)
                    function.LocalVariableDecls.Add(local_variable_decl);
                else
                    return Error();

            // statement list
            if (Visit(context.statement_list()) is PStatementList statement_list)
                function.Statements = statement_list.Statements;
            else
                return Error();

            return function;
        }

        public override AstNode VisitParameter_decl_list(openeParser.Parameter_decl_listContext context)
        {
            var variable_decl_list = new PVariableDeclList();
            foreach (var parameter_decl_context in context.parameter_decl())
                if (Visit(parameter_decl_context) is PVariableDecl variable_decl)
                    variable_decl_list.VariableDecls.Add(variable_decl);
                else
                    return Error();

            return variable_decl_list;
        }

        public override AstNode VisitParameter_decl(openeParser.Parameter_declContext context)
        {
            return Visit(context.variable_decl());
        }

        public override AstNode VisitLocal_variable_decl(openeParser.Local_variable_declContext context)
        {
            return Visit(context.variable_decl());
        }

        public override AstNode VisitStatement_list(openeParser.Statement_listContext context)
        {
            var statement_list = new PStatementList();
            foreach (var statement_context in context.statement())
            {
                AstNode node = Visit(statement_context);
                if (node is PStatement statement)
                    statement_list.Statements.Add(statement);
                else
                    return Error();
            }

            return statement_list;
        }

        public override AstNode VisitAssignStatement(openeParser.AssignStatementContext context)
        {
            var assign_statement = new PAssignStatement();
            if (Visit(context.hierarchy_identifier()) is PExpression lexpression)
                assign_statement.LExpression = lexpression;
            else
                return Error();

            if (Visit(context.expression()) is PExpression rexpression)
                assign_statement.RExpression = rexpression;
            else
                return Error();

            return assign_statement;
        }

        public override AstNode VisitWhile(openeParser.WhileContext context)
        {
            // Loop condition.
            var while_statement = new PWhileStatement();
            if (Visit(context.expression()) is PExpression expression)
                while_statement.ConditionExpression = expression;
            else
                return Error();
            // Loop body.
            if (Visit(context.statement_list()) is PStatementList statement_list)
                while_statement.StatementList = statement_list;
            else
                return Error();

            return while_statement;
        }

        public override AstNode VisitFor(openeParser.ForContext context)
        {
            var for_statement = new PForStatement();
            // For loop count.
            if (Visit(context.expression()) is PExpression expression)
                for_statement.LoopCount = expression;
            else
                return Error();
            // For loop counter.
            if (context.IDENTIFIER() != null) for_statement.Counter = context.IDENTIFIER().GetText();

            return for_statement;
        }

        public override AstNode VisitIfStmt(openeParser.IfStmtContext context)
        {
            var if_statement = new PIfStatement();
            // Condition expression
            if_statement.ConditionExpression = Visit(context.expression()) as PExpression;
            if (if_statement.ConditionExpression == null)
                return Error();
            // True statement list
            if_statement.TrueStatementList = Visit(context.statement_list()) as PStatementList;
            if (if_statement.TrueStatementList == null)
                return Error();
            // Else statement list
            if (context.condition_statement_else() != null && context.condition_statement_else().IsEmpty == false)
            {
                if_statement.FalseStatementList = Visit(context.condition_statement_else()) as PStatementList;
                if (if_statement.FalseStatementList == null)
                    return Error();
            }

            return if_statement;
        }

        public override AstNode VisitIfTrueStmt(openeParser.IfTrueStmtContext context)
        {
            var if_statement = new PIfStatement();
            // Condition expression
            if_statement.ConditionExpression = Visit(context.expression()) as PExpression;
            if (if_statement.ConditionExpression == null)
                return Error();
            // True statement list
            if_statement.TrueStatementList = Visit(context.statement_list()) as PStatementList;
            if (if_statement.TrueStatementList == null)
                return Error();
            if_statement.FalseStatementList = null;
            return if_statement;
        }

        public override AstNode VisitCondition_statement_else(openeParser.Condition_statement_elseContext context)
        {
            return Visit(context.statement_list());
        }

        public override AstNode VisitHierarchy_identifier(openeParser.Hierarchy_identifierContext context)
        {
            var component_list = new PNameComponentList();
            foreach (var name_component_context in context.name_component())
                if (Visit(name_component_context) is PNameComponent component)
                    component_list.Components.Add(component);
                else
                    return Error();

            return component_list;
        }

        public override AstNode VisitIdentifier(openeParser.IdentifierContext context)
        {
            var component = new PNameComponent();
            component.Type = PNameComponent.ComponentType.Identifier;
            component.Name = context.IDENTIFIER().GetText();
            return component;
        }

        public override AstNode VisitFuncCallWithoutArgu(openeParser.FuncCallWithoutArguContext context)
        {
            var component = new PNameComponent();
            component.Type = PNameComponent.ComponentType.FuncCall;
            component.Name = context.IDENTIFIER().GetText();
            return component;
        }

        public override AstNode VisitFuncCallWithArgu(openeParser.FuncCallWithArguContext context)
        {
            var component = new PNameComponent();
            component.Type = PNameComponent.ComponentType.FuncCall;
            component.Name = context.IDENTIFIER().GetText();
            foreach (var expression_context in context.expression())
                if (Visit(expression_context) is PExpression expression)
                    component.Expressions.Add(expression);
                else
                    return Error();

            return component;
        }

        public override AstNode VisitArrayIndex(openeParser.ArrayIndexContext context)
        {
            var component = new PNameComponent();
            component.Type = PNameComponent.ComponentType.ArrayIndex;
            component.Name = context.IDENTIFIER().GetText();
            if (Visit(context.expression()) is PExpression expression)
                component.Expressions.Add(expression);
            else
                return Error();

            return component;
        }

        public override AstNode VisitBracket(openeParser.BracketContext context)
        {
            return Visit(context.expression());
        }

        public override AstNode VisitBinaryExpr(openeParser.BinaryExprContext context)
        {
            var binary_expr = new PBinaryExpr();
            // Binary expression operate code.
            var type_valid = PBinaryExpr.LexOptMap.ContainsKey(context.opt.Type);
            if (type_valid == false)
            {
                errorManager.OperatorIsInvalid(context.opt.Text);
                return Error();
            }

            binary_expr.Opt = PBinaryExpr.LexOptMap[context.opt.Type];
            // Check if 2 expression.
            if (context.expression().Length != 2) return Error();
            // Left value expression.
            if (Visit(context.expression(0)) is PExpression lexpression)
                binary_expr.LExpression = lexpression;
            else
                return Error();
            // Right value expression.
            if (Visit(context.expression(1)) is PExpression rexpression)
                binary_expr.RExpression = rexpression;
            else
                return Error();

            return binary_expr;
        }

        public override AstNode VisitUnaryExpr(openeParser.UnaryExprContext context)
        {
            var unary_expr = new PUnaryExpr();
            // Unary expression operate code.
            var type_valid = PUnaryExpr.LexOptMap.ContainsKey(context.opt.Type);
            if (type_valid == false)
            {
                errorManager.OperatorIsInvalid(context.opt.Text);
                return Error();
            }

            unary_expr.Opt = PUnaryExpr.LexOptMap[context.opt.Type];
            // Unary expression.
            if (Visit(context.expression()) is PExpression expression)
                unary_expr.Expression = expression;
            else
                return Error();

            return unary_expr;
        }

        public override AstNode VisitMacro_value(openeParser.Macro_valueContext context)
        {
            var macro_value = new PMacroValue();
            macro_value.Name = context.IDENTIFIER().GetText();
            return macro_value;
        }

        public override AstNode VisitString_value(openeParser.String_valueContext context)
        {
            var string_value = new PString();
            string_value.Value = context.STRING_LITERAL().GetText();
            return string_value;
        }

        public override AstNode VisitBool_value(openeParser.Bool_valueContext context)
        {
            var bool_value = new PBool();
            if (context.bval.Type == openeLexer.K_TRUE)
                bool_value.Value = true;
            else if (context.bval.Type == openeLexer.K_FALSE)
                bool_value.Value = false;
            else
                throw new Exception("no such bool value=" + context.bval);

            return bool_value;
        }

        public override AstNode VisitInt(openeParser.IntContext context)
        {
            var value_value = new PNumber();
            value_value.Value = Convert.ToInt32(context.INTEGER_LITERAL().GetText());
            return value_value;
        }

        public override AstNode VisitFloat(openeParser.FloatContext context)
        {
            var value_value = new PFloatNumber();
            value_value.Value = Convert.ToSingle(context.FLOAT_LITERAL().GetText());
            return value_value;
        }
    }

    internal class AstGenerator
    {
        public AstNode GenerateAst(IParseTree parseTree, ref ErrorManager errorManager)
        {
            IopeneVisitor<AstNode> visitor = new OpenEAstVisitor(ref errorManager);
            AstNode ast = visitor.Visit(parseTree);
            return ast;
        }
    }
}