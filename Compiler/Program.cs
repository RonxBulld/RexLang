﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using Compiler.AST;

namespace Compiler
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Start compile...");
            string input = "../../oe_src/window_program_set1.txt";
            input = File.ReadAllText(input);
            ICharStream stream = CharStreams.fromstring(input);
            openeLexer lexer = new openeLexer(stream);
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            openeParser parser = new openeParser(tokens);
            parser.BuildParseTree = true;
            IParseTree tree = parser.opene_src();
            AstGenerator generator = new AstGenerator();
            ErrorManager errorManager = new ErrorManager();
            generator.GenerateAst(tree, ref errorManager);
        }
    }
}
