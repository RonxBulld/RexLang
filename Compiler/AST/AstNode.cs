using System.Collections.Generic;

namespace Compiler.AST
{
    public class AstNode
    {
    }

    public class PNameComponent : AstNode
    {
        public enum ComponentType
        {
            Identifier,
            FuncCall,
            ArrayIndex
        }

        public List<PExpression> Expressions = new List<PExpression>();
        public string Name = "";
        public ComponentType Type = ComponentType.Identifier;
    }

    public class PCompileUnit : AstNode
    {
        public List<PFunction> Functions = new List<PFunction>();
        public List<string> Libraries = new List<string>();
        public string ProgramSetName = "";
        public List<PVariableDecl> VariableDecls = new List<PVariableDecl>();
        public int Version = 0;
    }

    public class PLibraries : AstNode
    {
        public PLibraries(List<string> libraries)
        {
            Libraries = libraries;
        }

        public List<string> Libraries { get; } = new List<string>();
    }

    public class PLibrary : AstNode
    {
        public PLibrary(string library)
        {
            Library = library;
        }

        public string Library { get; } = "";
    }

    public class PProgramSet : AstNode
    {
        public List<PFunction> Functions;
        public string ProgramSetName;
        public List<PVariableDecl> VariableDecls;
    }

    public class PVariableDecl : AstNode
    {
        public List<int> Dimensions;
        public string VariableName;
        public string VariableType;
    }

    public class PVariableName : AstNode
    {
        public PVariableName(string name)
        {
            Name = name;
        }

        public string Name { get; }
    }

    public class PVariableTypeName : AstNode
    {
        public PVariableTypeName(string name)
        {
            Name = name;
        }

        public string Name { get; }
    }

    public class PDimensionDecl : AstNode
    {
        public List<int> Dimension = new List<int>();
    }

    public class PVariableDeclList : AstNode
    {
        public List<PVariableDecl> VariableDecls = new List<PVariableDecl>();
    }

    public class PFunction : AstNode
    {
        public List<PVariableDecl> LocalVariableDecls = new List<PVariableDecl>();
        public string Name;
        public List<PVariableDecl> ParameterDecls = new List<PVariableDecl>();
        public string ReturnType;
        public List<PStatement> Statements = new List<PStatement>();
    }

    public class PFunctionList : AstNode
    {
        public List<PFunction> Functions = new List<PFunction>();
    }
}