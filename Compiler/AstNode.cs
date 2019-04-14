using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Compiler
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
        };
        public string Name = "";
        public ComponentType Type = ComponentType.Identifier;
        public List<PExpression> Expressions = new List<PExpression>();
    }

    public class PCompileUnit : AstNode
    {
        public int Version = 0;
        public List<string> Libraries = new List<string>();
        public string ProgramSetName = "";
        public List<PVariableDecl> VariableDecls = new List<PVariableDecl>();
        public List<PFunction> Functions = new List<PFunction>();
    }

    public class PLibraries : AstNode
    {
        private List<string> _libraries = new List<string>();
        public List<string> Libraries => _libraries;
        public PLibraries(List<string> libraries)
        {
            this._libraries = libraries;
        }
    }

    public class PLibrary : AstNode
    {
        private string _library = "";
        public string Library => _library;
        public PLibrary(string library)
        {
            this._library = library;
        }
    }

    public class PProgramSet : AstNode
    {
        public string ProgramSetName;
        public List<PVariableDecl> VariableDecls;
        public List<PFunction> Functions;
    }

    public class PVariableDecl : AstNode
    {
        public string VariableName;
        public string VariableType;
        public List<int> Dimensions;
    }

    public class PVariableName : AstNode
    {
        private string _name;
        public string Name => _name;
        public PVariableName(string name)
        {
            this._name = name;
        }
    }

    public class PVariableTypeName : AstNode
    {
        private string _name;
        public string Name => _name;
        public PVariableTypeName(string name)
        {
            this._name = name;
        }
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
        public string Name;
        public string ReturnType;
        public List<PVariableDecl> ParameterDecls = new List<PVariableDecl>();
        public List<PVariableDecl> LocalVariableDecls = new List<PVariableDecl>();
        public List<PStatement> Statements = new List<PStatement>();
    }

    public class PFunctionList : AstNode
    {
        public List<PFunction> Functions = new List<PFunction>();
    }
}