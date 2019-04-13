using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
            PVersion version = Visit(context.edition_spec()) as PVersion;
            if (version == null)
            {
                return null;
            }
            PCompileUnit compileUnit = new PCompileUnit();
            compileUnit.Version = version;
            PLibraries libraries = Visit(context.library_list_opt()) as PLibraries;
            compileUnit.Libraries = libraries;
            PProgramSet programSet = Visit(context.prog_set()) as PProgramSet;
            compileUnit.ProgramSet = programSet;
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
            PVersion versionNode = new PVersion(ver);
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
            programSet.ProgramSetName = context.IDENTIFIER().GetText();
            PVariableDeclList variableDeclList = Visit(context.prog_set_variable_decl_opt()) as PVariableDeclList;
            if (variableDeclList == null)
                return null;
            programSet.VariableDecls = variableDeclList.VariableDecls;
            // TODO: 编写 sub_program_opt 的构建代码
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
            throw new NotImplementedException();
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
            throw new NotImplementedException();
        }

        public AstNode VisitSub_program(openeParser.Sub_programContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitParameter_decl_list(openeParser.Parameter_decl_listContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitParameter_decl(openeParser.Parameter_declContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitLocal_variable_decl(openeParser.Local_variable_declContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitStatement_list(openeParser.Statement_listContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitStatement(openeParser.StatementContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitCondition_statement(openeParser.Condition_statementContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitCondition_start_word(openeParser.Condition_start_wordContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitCondition_end_word(openeParser.Condition_end_wordContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitCondition_statement_else(openeParser.Condition_statement_elseContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitHierarchy_identifier(openeParser.Hierarchy_identifierContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitName_component(openeParser.Name_componentContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitExpression(openeParser.ExpressionContext context)
        {
            throw new NotImplementedException();
        }

        public AstNode VisitNumber(openeParser.NumberContext context)
        {
            throw new NotImplementedException();
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
