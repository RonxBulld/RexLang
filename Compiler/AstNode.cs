using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Compiler
{
    class AstNode
    {
    }

    class PVersion : AstNode
    {
        private int _version = 0;

        public int Version => _version;

        public PVersion(int version)
        {
            this._version = version;
        }
    }

    class PCompileUnit : AstNode
    {
        public PVersion Version;

        public PLibraries Libraries;

        public PProgramSet ProgramSet;

    }

    class PLibraries : AstNode
    {
        private List<string> _libraries;

        public List<string> Libraries => _libraries;

        public PLibraries(List<string> libraries)
        {
            this._libraries = libraries;
        }
    }

    class PLibrary : AstNode
    {
        private string _library;

        public string Library => _library;

        public PLibrary(string library)
        {
            this._library = library;
        }
    }

    class PProgramSet : AstNode
    {
        public string ProgramSetName;
        public List<PVariableDecl> VariableDecls;
    }

    class PVariableDecl : AstNode
    {
        public string VariableName;
        public string VariableType;
        public List<int> Dimensions;
    }

    class PVariableName : AstNode
    {
        private string _name;

        public string Name => _name;

        public PVariableName(string name)
        {
            this._name = name;
        }
    }

    class PVariableTypeName : AstNode
    {
        private string _name;

        public string Name => _name;

        public PVariableTypeName(string name)
        {
            this._name = name;
        }
    }

    class PDimensionDecl : AstNode
    {
        public List<int> Dimension;
    }

    class PVariableDeclList : AstNode
    {
        public List<PVariableDecl> VariableDecls;
    }
}
