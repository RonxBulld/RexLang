﻿using System;
using System.IO;
using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using Compiler.AST;

namespace Compiler
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            Console.WriteLine("Start compile...");
            var input = "../../oe_src/window_program_set1.txt";
            input = File.ReadAllText(input);
            var stream = CharStreams.fromstring(input);
            openeLexer lexer = new openeLexer(stream);
            var tokens = new CommonTokenStream(lexer);
            openeParser parser = new openeParser(tokens);
            parser.BuildParseTree = true;
            IParseTree tree = parser.opene_src();
            var generator = new AstGenerator();
            var errorManager = new ErrorManager();
            var root = generator.GenerateAst(tree, ref errorManager);
        }
    }
}