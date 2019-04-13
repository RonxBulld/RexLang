using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Antlr4.Runtime;
using Antlr4.Runtime.Tree;

namespace Compiler
{
    class Program
    {
        static void Main(string[] args)
        {
            String input = "";
            ICharStream stream = CharStreams.fromstring(input);
            ITokenSource lexer = new openeLexer(stream);
            ITokenStream tokens = new CommonTokenStream(lexer);
            openeParser parser = new openeParser(tokens);
            parser.BuildParseTree = true;
            IParseTree tree = parser.opene_src();
            AstGenerator generator = new AstGenerator();
            ErrorManager errorManager = new ErrorManager();
            generator.GenerateAst(tree, ref errorManager);
        }
    }
}
