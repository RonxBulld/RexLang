//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     ANTLR Version: 4.7.2
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from D:/Project/OpenELanguage/Compiler\opene.g4 by ANTLR 4.7.2

// Unreachable code detected
#pragma warning disable 0162
// The variable '...' is assigned but its value is never used
#pragma warning disable 0219
// Missing XML comment for publicly visible type or member '...'
#pragma warning disable 1591
// Ambiguous reference in cref attribute
#pragma warning disable 419

using System;
using System.IO;
using System.Text;
using Antlr4.Runtime;
using Antlr4.Runtime.Atn;
using Antlr4.Runtime.Misc;
using DFA = Antlr4.Runtime.Dfa.DFA;

[System.CodeDom.Compiler.GeneratedCode("ANTLR", "4.7.2")]
[System.CLSCompliant(false)]
public partial class openeLexer : Lexer {
	protected static DFA[] decisionToDFA;
	protected static PredictionContextCache sharedContextCache = new PredictionContextCache();
	public const int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		K_VERSION=10, K_LIBRARY=11, K_PROGRAM_SET=12, K_PROGRAM_SET_VARIABLE=13, 
		K_LOCAL_VARIABLE=14, K_PARAMETER=15, K_SUB_PROGRAM=16, K_IF_TRUE=17, K_IF_TRUE_END=18, 
		K_IF=19, K_ELSE=20, K_END_IF=21, K_WHILE=22, K_WHILE_END=23, K_FOR=24, 
		K_FOR_END=25, K_TRUE=26, K_FALSE=27, K_ADD_OPT=28, K_SUB_OPT=29, K_MUL_OPT=30, 
		K_DIV_OPT=31, K_ASSIGN_OPT=32, K_NOT_EQUAL_OPT=33, K_OR_OPT=34, INTEGER_LITERAL=35, 
		FLOAT_LITERAL=36, IDENTIFIER=37, WHITESPACE=38, NEWLINE=39, STRING_LITERAL=40, 
		CODE_COMMIT=41, OTHER_CHAR=42;
	public static string[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static string[] modeNames = {
		"DEFAULT_MODE"
	};

	public static readonly string[] ruleNames = {
		"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
		"K_VERSION", "K_LIBRARY", "K_PROGRAM_SET", "K_PROGRAM_SET_VARIABLE", "K_LOCAL_VARIABLE", 
		"K_PARAMETER", "K_SUB_PROGRAM", "K_IF_TRUE", "K_IF_TRUE_END", "K_IF", 
		"K_ELSE", "K_END_IF", "K_WHILE", "K_WHILE_END", "K_FOR", "K_FOR_END", 
		"K_TRUE", "K_FALSE", "K_ADD_OPT", "K_SUB_OPT", "K_MUL_OPT", "K_DIV_OPT", 
		"K_ASSIGN_OPT", "K_NOT_EQUAL_OPT", "K_OR_OPT", "INTEGER_LITERAL", "FLOAT_LITERAL", 
		"UNICODE_CHAR", "IDENTIFIER", "WHITESPACE", "NEWLINE", "STRING_LITERAL", 
		"CODE_COMMIT", "OTHER_CHAR"
	};


	public openeLexer(ICharStream input)
	: this(input, Console.Out, Console.Error) { }

	public openeLexer(ICharStream input, TextWriter output, TextWriter errorOutput)
	: base(input, output, errorOutput)
	{
		Interpreter = new LexerATNSimulator(this, _ATN, decisionToDFA, sharedContextCache);
	}

	private static readonly string[] _LiteralNames = {
		null, "','", "'\"'", "'('", "')'", "'.'", "'['", "']'", "'-'", "'#'", 
		"'.\u7248\u672C'", "'.\u652F\u6301\u5E93'", "'.\u7A0B\u5E8F\u96C6'", "'.\u7A0B\u5E8F\u96C6\u53D8\u91CF'", 
		"'.\u5C40\u90E8\u53D8\u91CF'", "'.\u53C2\u6570'", "'.\u5B50\u7A0B\u5E8F'", 
		"'.\u5982\u679C\u771F'", "'.\u5982\u679C\u771F\u7ED3\u675F'", "'.\u5982\u679C'", 
		"'.\u5426\u5219'", "'.\u5982\u679C\u7ED3\u675F'", "'.\u5224\u65AD\u5FAA\u73AF\u9996'", 
		"'.\u5224\u65AD\u5FAA\u73AF\u5C3E'", "'.\u8BA1\u6B21\u5FAA\u73AF\u9996'", 
		"'.\u8BA1\u6B21\u5FAA\u73AF\u5C3E'", "'\u771F'", "'\u5047'", "'\uFF0B'", 
		"'\uFF0D'", "'\u00D7'", "'\u00F7'", "'\uFF1D'", "'\u2260'", "'\u6216'"
	};
	private static readonly string[] _SymbolicNames = {
		null, null, null, null, null, null, null, null, null, null, "K_VERSION", 
		"K_LIBRARY", "K_PROGRAM_SET", "K_PROGRAM_SET_VARIABLE", "K_LOCAL_VARIABLE", 
		"K_PARAMETER", "K_SUB_PROGRAM", "K_IF_TRUE", "K_IF_TRUE_END", "K_IF", 
		"K_ELSE", "K_END_IF", "K_WHILE", "K_WHILE_END", "K_FOR", "K_FOR_END", 
		"K_TRUE", "K_FALSE", "K_ADD_OPT", "K_SUB_OPT", "K_MUL_OPT", "K_DIV_OPT", 
		"K_ASSIGN_OPT", "K_NOT_EQUAL_OPT", "K_OR_OPT", "INTEGER_LITERAL", "FLOAT_LITERAL", 
		"IDENTIFIER", "WHITESPACE", "NEWLINE", "STRING_LITERAL", "CODE_COMMIT", 
		"OTHER_CHAR"
	};
	public static readonly IVocabulary DefaultVocabulary = new Vocabulary(_LiteralNames, _SymbolicNames);

	[NotNull]
	public override IVocabulary Vocabulary
	{
		get
		{
			return DefaultVocabulary;
		}
	}

	public override string GrammarFileName { get { return "opene.g4"; } }

	public override string[] RuleNames { get { return ruleNames; } }

	public override string[] ChannelNames { get { return channelNames; } }

	public override string[] ModeNames { get { return modeNames; } }

	public override string SerializedAtn { get { return new string(_serializedATN); } }

	static openeLexer() {
		decisionToDFA = new DFA[_ATN.NumberOfDecisions];
		for (int i = 0; i < _ATN.NumberOfDecisions; i++) {
			decisionToDFA[i] = new DFA(_ATN.GetDecisionState(i), i);
		}
	}
	private static char[] _serializedATN = {
		'\x3', '\x608B', '\xA72A', '\x8133', '\xB9ED', '\x417C', '\x3BE7', '\x7786', 
		'\x5964', '\x2', ',', '\x117', '\b', '\x1', '\x4', '\x2', '\t', '\x2', 
		'\x4', '\x3', '\t', '\x3', '\x4', '\x4', '\t', '\x4', '\x4', '\x5', '\t', 
		'\x5', '\x4', '\x6', '\t', '\x6', '\x4', '\a', '\t', '\a', '\x4', '\b', 
		'\t', '\b', '\x4', '\t', '\t', '\t', '\x4', '\n', '\t', '\n', '\x4', '\v', 
		'\t', '\v', '\x4', '\f', '\t', '\f', '\x4', '\r', '\t', '\r', '\x4', '\xE', 
		'\t', '\xE', '\x4', '\xF', '\t', '\xF', '\x4', '\x10', '\t', '\x10', '\x4', 
		'\x11', '\t', '\x11', '\x4', '\x12', '\t', '\x12', '\x4', '\x13', '\t', 
		'\x13', '\x4', '\x14', '\t', '\x14', '\x4', '\x15', '\t', '\x15', '\x4', 
		'\x16', '\t', '\x16', '\x4', '\x17', '\t', '\x17', '\x4', '\x18', '\t', 
		'\x18', '\x4', '\x19', '\t', '\x19', '\x4', '\x1A', '\t', '\x1A', '\x4', 
		'\x1B', '\t', '\x1B', '\x4', '\x1C', '\t', '\x1C', '\x4', '\x1D', '\t', 
		'\x1D', '\x4', '\x1E', '\t', '\x1E', '\x4', '\x1F', '\t', '\x1F', '\x4', 
		' ', '\t', ' ', '\x4', '!', '\t', '!', '\x4', '\"', '\t', '\"', '\x4', 
		'#', '\t', '#', '\x4', '$', '\t', '$', '\x4', '%', '\t', '%', '\x4', '&', 
		'\t', '&', '\x4', '\'', '\t', '\'', '\x4', '(', '\t', '(', '\x4', ')', 
		'\t', ')', '\x4', '*', '\t', '*', '\x4', '+', '\t', '+', '\x4', ',', '\t', 
		',', '\x3', '\x2', '\x3', '\x2', '\x3', '\x3', '\x3', '\x3', '\x3', '\x4', 
		'\x3', '\x4', '\x3', '\x5', '\x3', '\x5', '\x3', '\x6', '\x3', '\x6', 
		'\x3', '\a', '\x3', '\a', '\x3', '\b', '\x3', '\b', '\x3', '\t', '\x3', 
		'\t', '\x3', '\n', '\x3', '\n', '\x3', '\v', '\x3', '\v', '\x3', '\v', 
		'\x3', '\v', '\x3', '\f', '\x3', '\f', '\x3', '\f', '\x3', '\f', '\x3', 
		'\f', '\x3', '\r', '\x3', '\r', '\x3', '\r', '\x3', '\r', '\x3', '\r', 
		'\x3', '\xE', '\x3', '\xE', '\x3', '\xE', '\x3', '\xE', '\x3', '\xE', 
		'\x3', '\xE', '\x3', '\xE', '\x3', '\xF', '\x3', '\xF', '\x3', '\xF', 
		'\x3', '\xF', '\x3', '\xF', '\x3', '\xF', '\x3', '\x10', '\x3', '\x10', 
		'\x3', '\x10', '\x3', '\x10', '\x3', '\x11', '\x3', '\x11', '\x3', '\x11', 
		'\x3', '\x11', '\x3', '\x11', '\x3', '\x12', '\x3', '\x12', '\x3', '\x12', 
		'\x3', '\x12', '\x3', '\x12', '\x3', '\x13', '\x3', '\x13', '\x3', '\x13', 
		'\x3', '\x13', '\x3', '\x13', '\x3', '\x13', '\x3', '\x13', '\x3', '\x14', 
		'\x3', '\x14', '\x3', '\x14', '\x3', '\x14', '\x3', '\x15', '\x3', '\x15', 
		'\x3', '\x15', '\x3', '\x15', '\x3', '\x16', '\x3', '\x16', '\x3', '\x16', 
		'\x3', '\x16', '\x3', '\x16', '\x3', '\x16', '\x3', '\x17', '\x3', '\x17', 
		'\x3', '\x17', '\x3', '\x17', '\x3', '\x17', '\x3', '\x17', '\x3', '\x17', 
		'\x3', '\x18', '\x3', '\x18', '\x3', '\x18', '\x3', '\x18', '\x3', '\x18', 
		'\x3', '\x18', '\x3', '\x18', '\x3', '\x19', '\x3', '\x19', '\x3', '\x19', 
		'\x3', '\x19', '\x3', '\x19', '\x3', '\x19', '\x3', '\x19', '\x3', '\x1A', 
		'\x3', '\x1A', '\x3', '\x1A', '\x3', '\x1A', '\x3', '\x1A', '\x3', '\x1A', 
		'\x3', '\x1A', '\x3', '\x1B', '\x3', '\x1B', '\x3', '\x1C', '\x3', '\x1C', 
		'\x3', '\x1D', '\x3', '\x1D', '\x3', '\x1E', '\x3', '\x1E', '\x3', '\x1F', 
		'\x3', '\x1F', '\x3', ' ', '\x3', ' ', '\x3', '!', '\x3', '!', '\x3', 
		'\"', '\x3', '\"', '\x3', '#', '\x3', '#', '\x3', '$', '\x6', '$', '\xD9', 
		'\n', '$', '\r', '$', '\xE', '$', '\xDA', '\x3', '%', '\x5', '%', '\xDE', 
		'\n', '%', '\x3', '%', '\x3', '%', '\x3', '%', '\x3', '%', '\x3', '%', 
		'\x5', '%', '\xE5', '\n', '%', '\x5', '%', '\xE7', '\n', '%', '\x3', '&', 
		'\x3', '&', '\x3', '\'', '\x3', '\'', '\x6', '\'', '\xED', '\n', '\'', 
		'\r', '\'', '\xE', '\'', '\xEE', '\x3', '(', '\x6', '(', '\xF2', '\n', 
		'(', '\r', '(', '\xE', '(', '\xF3', '\x3', '(', '\x3', '(', '\x3', ')', 
		'\x5', ')', '\xF9', '\n', ')', '\x3', ')', '\x3', ')', '\x3', ')', '\x3', 
		')', '\x3', '*', '\x3', '*', '\a', '*', '\x101', '\n', '*', '\f', '*', 
		'\xE', '*', '\x104', '\v', '*', '\x3', '*', '\x3', '*', '\x3', '+', '\x3', 
		'+', '\a', '+', '\x10A', '\n', '+', '\f', '+', '\xE', '+', '\x10D', '\v', 
		'+', '\x3', '+', '\x5', '+', '\x110', '\n', '+', '\x3', '+', '\x3', '+', 
		'\x3', '+', '\x3', '+', '\x3', ',', '\x3', ',', '\x4', '\x102', '\x10B', 
		'\x2', '-', '\x3', '\x3', '\x5', '\x4', '\a', '\x5', '\t', '\x6', '\v', 
		'\a', '\r', '\b', '\xF', '\t', '\x11', '\n', '\x13', '\v', '\x15', '\f', 
		'\x17', '\r', '\x19', '\xE', '\x1B', '\xF', '\x1D', '\x10', '\x1F', '\x11', 
		'!', '\x12', '#', '\x13', '%', '\x14', '\'', '\x15', ')', '\x16', '+', 
		'\x17', '-', '\x18', '/', '\x19', '\x31', '\x1A', '\x33', '\x1B', '\x35', 
		'\x1C', '\x37', '\x1D', '\x39', '\x1E', ';', '\x1F', '=', ' ', '?', '!', 
		'\x41', '\"', '\x43', '#', '\x45', '$', 'G', '%', 'I', '&', 'K', '\x2', 
		'M', '\'', 'O', '(', 'Q', ')', 'S', '*', 'U', '+', 'W', ',', '\x3', '\x2', 
		'\x5', '\x4', '\x2', '\x4E02', '\x9FA7', '\xF902', '\xFA2F', '\x6', '\x2', 
		'\x32', ';', '\x43', '\\', '\x61', '\x61', '\x63', '|', '\x4', '\x2', 
		'\v', '\v', '\"', '\"', '\x2', '\x120', '\x2', '\x3', '\x3', '\x2', '\x2', 
		'\x2', '\x2', '\x5', '\x3', '\x2', '\x2', '\x2', '\x2', '\a', '\x3', '\x2', 
		'\x2', '\x2', '\x2', '\t', '\x3', '\x2', '\x2', '\x2', '\x2', '\v', '\x3', 
		'\x2', '\x2', '\x2', '\x2', '\r', '\x3', '\x2', '\x2', '\x2', '\x2', '\xF', 
		'\x3', '\x2', '\x2', '\x2', '\x2', '\x11', '\x3', '\x2', '\x2', '\x2', 
		'\x2', '\x13', '\x3', '\x2', '\x2', '\x2', '\x2', '\x15', '\x3', '\x2', 
		'\x2', '\x2', '\x2', '\x17', '\x3', '\x2', '\x2', '\x2', '\x2', '\x19', 
		'\x3', '\x2', '\x2', '\x2', '\x2', '\x1B', '\x3', '\x2', '\x2', '\x2', 
		'\x2', '\x1D', '\x3', '\x2', '\x2', '\x2', '\x2', '\x1F', '\x3', '\x2', 
		'\x2', '\x2', '\x2', '!', '\x3', '\x2', '\x2', '\x2', '\x2', '#', '\x3', 
		'\x2', '\x2', '\x2', '\x2', '%', '\x3', '\x2', '\x2', '\x2', '\x2', '\'', 
		'\x3', '\x2', '\x2', '\x2', '\x2', ')', '\x3', '\x2', '\x2', '\x2', '\x2', 
		'+', '\x3', '\x2', '\x2', '\x2', '\x2', '-', '\x3', '\x2', '\x2', '\x2', 
		'\x2', '/', '\x3', '\x2', '\x2', '\x2', '\x2', '\x31', '\x3', '\x2', '\x2', 
		'\x2', '\x2', '\x33', '\x3', '\x2', '\x2', '\x2', '\x2', '\x35', '\x3', 
		'\x2', '\x2', '\x2', '\x2', '\x37', '\x3', '\x2', '\x2', '\x2', '\x2', 
		'\x39', '\x3', '\x2', '\x2', '\x2', '\x2', ';', '\x3', '\x2', '\x2', '\x2', 
		'\x2', '=', '\x3', '\x2', '\x2', '\x2', '\x2', '?', '\x3', '\x2', '\x2', 
		'\x2', '\x2', '\x41', '\x3', '\x2', '\x2', '\x2', '\x2', '\x43', '\x3', 
		'\x2', '\x2', '\x2', '\x2', '\x45', '\x3', '\x2', '\x2', '\x2', '\x2', 
		'G', '\x3', '\x2', '\x2', '\x2', '\x2', 'I', '\x3', '\x2', '\x2', '\x2', 
		'\x2', 'M', '\x3', '\x2', '\x2', '\x2', '\x2', 'O', '\x3', '\x2', '\x2', 
		'\x2', '\x2', 'Q', '\x3', '\x2', '\x2', '\x2', '\x2', 'S', '\x3', '\x2', 
		'\x2', '\x2', '\x2', 'U', '\x3', '\x2', '\x2', '\x2', '\x2', 'W', '\x3', 
		'\x2', '\x2', '\x2', '\x3', 'Y', '\x3', '\x2', '\x2', '\x2', '\x5', '[', 
		'\x3', '\x2', '\x2', '\x2', '\a', ']', '\x3', '\x2', '\x2', '\x2', '\t', 
		'_', '\x3', '\x2', '\x2', '\x2', '\v', '\x61', '\x3', '\x2', '\x2', '\x2', 
		'\r', '\x63', '\x3', '\x2', '\x2', '\x2', '\xF', '\x65', '\x3', '\x2', 
		'\x2', '\x2', '\x11', 'g', '\x3', '\x2', '\x2', '\x2', '\x13', 'i', '\x3', 
		'\x2', '\x2', '\x2', '\x15', 'k', '\x3', '\x2', '\x2', '\x2', '\x17', 
		'o', '\x3', '\x2', '\x2', '\x2', '\x19', 't', '\x3', '\x2', '\x2', '\x2', 
		'\x1B', 'y', '\x3', '\x2', '\x2', '\x2', '\x1D', '\x80', '\x3', '\x2', 
		'\x2', '\x2', '\x1F', '\x86', '\x3', '\x2', '\x2', '\x2', '!', '\x8A', 
		'\x3', '\x2', '\x2', '\x2', '#', '\x8F', '\x3', '\x2', '\x2', '\x2', '%', 
		'\x94', '\x3', '\x2', '\x2', '\x2', '\'', '\x9B', '\x3', '\x2', '\x2', 
		'\x2', ')', '\x9F', '\x3', '\x2', '\x2', '\x2', '+', '\xA3', '\x3', '\x2', 
		'\x2', '\x2', '-', '\xA9', '\x3', '\x2', '\x2', '\x2', '/', '\xB0', '\x3', 
		'\x2', '\x2', '\x2', '\x31', '\xB7', '\x3', '\x2', '\x2', '\x2', '\x33', 
		'\xBE', '\x3', '\x2', '\x2', '\x2', '\x35', '\xC5', '\x3', '\x2', '\x2', 
		'\x2', '\x37', '\xC7', '\x3', '\x2', '\x2', '\x2', '\x39', '\xC9', '\x3', 
		'\x2', '\x2', '\x2', ';', '\xCB', '\x3', '\x2', '\x2', '\x2', '=', '\xCD', 
		'\x3', '\x2', '\x2', '\x2', '?', '\xCF', '\x3', '\x2', '\x2', '\x2', '\x41', 
		'\xD1', '\x3', '\x2', '\x2', '\x2', '\x43', '\xD3', '\x3', '\x2', '\x2', 
		'\x2', '\x45', '\xD5', '\x3', '\x2', '\x2', '\x2', 'G', '\xD8', '\x3', 
		'\x2', '\x2', '\x2', 'I', '\xE6', '\x3', '\x2', '\x2', '\x2', 'K', '\xE8', 
		'\x3', '\x2', '\x2', '\x2', 'M', '\xEC', '\x3', '\x2', '\x2', '\x2', 'O', 
		'\xF1', '\x3', '\x2', '\x2', '\x2', 'Q', '\xF8', '\x3', '\x2', '\x2', 
		'\x2', 'S', '\xFE', '\x3', '\x2', '\x2', '\x2', 'U', '\x107', '\x3', '\x2', 
		'\x2', '\x2', 'W', '\x115', '\x3', '\x2', '\x2', '\x2', 'Y', 'Z', '\a', 
		'.', '\x2', '\x2', 'Z', '\x4', '\x3', '\x2', '\x2', '\x2', '[', '\\', 
		'\a', '$', '\x2', '\x2', '\\', '\x6', '\x3', '\x2', '\x2', '\x2', ']', 
		'^', '\a', '*', '\x2', '\x2', '^', '\b', '\x3', '\x2', '\x2', '\x2', '_', 
		'`', '\a', '+', '\x2', '\x2', '`', '\n', '\x3', '\x2', '\x2', '\x2', '\x61', 
		'\x62', '\a', '\x30', '\x2', '\x2', '\x62', '\f', '\x3', '\x2', '\x2', 
		'\x2', '\x63', '\x64', '\a', ']', '\x2', '\x2', '\x64', '\xE', '\x3', 
		'\x2', '\x2', '\x2', '\x65', '\x66', '\a', '_', '\x2', '\x2', '\x66', 
		'\x10', '\x3', '\x2', '\x2', '\x2', 'g', 'h', '\a', '/', '\x2', '\x2', 
		'h', '\x12', '\x3', '\x2', '\x2', '\x2', 'i', 'j', '\a', '%', '\x2', '\x2', 
		'j', '\x14', '\x3', '\x2', '\x2', '\x2', 'k', 'l', '\a', '\x30', '\x2', 
		'\x2', 'l', 'm', '\a', '\x724A', '\x2', '\x2', 'm', 'n', '\a', '\x672E', 
		'\x2', '\x2', 'n', '\x16', '\x3', '\x2', '\x2', '\x2', 'o', 'p', '\a', 
		'\x30', '\x2', '\x2', 'p', 'q', '\a', '\x6531', '\x2', '\x2', 'q', 'r', 
		'\a', '\x6303', '\x2', '\x2', 'r', 's', '\a', '\x5E95', '\x2', '\x2', 
		's', '\x18', '\x3', '\x2', '\x2', '\x2', 't', 'u', '\a', '\x30', '\x2', 
		'\x2', 'u', 'v', '\a', '\x7A0D', '\x2', '\x2', 'v', 'w', '\a', '\x5E91', 
		'\x2', '\x2', 'w', 'x', '\a', '\x96C8', '\x2', '\x2', 'x', '\x1A', '\x3', 
		'\x2', '\x2', '\x2', 'y', 'z', '\a', '\x30', '\x2', '\x2', 'z', '{', '\a', 
		'\x7A0D', '\x2', '\x2', '{', '|', '\a', '\x5E91', '\x2', '\x2', '|', '}', 
		'\a', '\x96C8', '\x2', '\x2', '}', '~', '\a', '\x53DA', '\x2', '\x2', 
		'~', '\x7F', '\a', '\x91D1', '\x2', '\x2', '\x7F', '\x1C', '\x3', '\x2', 
		'\x2', '\x2', '\x80', '\x81', '\a', '\x30', '\x2', '\x2', '\x81', '\x82', 
		'\a', '\x5C42', '\x2', '\x2', '\x82', '\x83', '\a', '\x90EA', '\x2', '\x2', 
		'\x83', '\x84', '\a', '\x53DA', '\x2', '\x2', '\x84', '\x85', '\a', '\x91D1', 
		'\x2', '\x2', '\x85', '\x1E', '\x3', '\x2', '\x2', '\x2', '\x86', '\x87', 
		'\a', '\x30', '\x2', '\x2', '\x87', '\x88', '\a', '\x53C4', '\x2', '\x2', 
		'\x88', '\x89', '\a', '\x6572', '\x2', '\x2', '\x89', ' ', '\x3', '\x2', 
		'\x2', '\x2', '\x8A', '\x8B', '\a', '\x30', '\x2', '\x2', '\x8B', '\x8C', 
		'\a', '\x5B52', '\x2', '\x2', '\x8C', '\x8D', '\a', '\x7A0D', '\x2', '\x2', 
		'\x8D', '\x8E', '\a', '\x5E91', '\x2', '\x2', '\x8E', '\"', '\x3', '\x2', 
		'\x2', '\x2', '\x8F', '\x90', '\a', '\x30', '\x2', '\x2', '\x90', '\x91', 
		'\a', '\x5984', '\x2', '\x2', '\x91', '\x92', '\a', '\x679E', '\x2', '\x2', 
		'\x92', '\x93', '\a', '\x7721', '\x2', '\x2', '\x93', '$', '\x3', '\x2', 
		'\x2', '\x2', '\x94', '\x95', '\a', '\x30', '\x2', '\x2', '\x95', '\x96', 
		'\a', '\x5984', '\x2', '\x2', '\x96', '\x97', '\a', '\x679E', '\x2', '\x2', 
		'\x97', '\x98', '\a', '\x7721', '\x2', '\x2', '\x98', '\x99', '\a', '\x7ED5', 
		'\x2', '\x2', '\x99', '\x9A', '\a', '\x6761', '\x2', '\x2', '\x9A', '&', 
		'\x3', '\x2', '\x2', '\x2', '\x9B', '\x9C', '\a', '\x30', '\x2', '\x2', 
		'\x9C', '\x9D', '\a', '\x5984', '\x2', '\x2', '\x9D', '\x9E', '\a', '\x679E', 
		'\x2', '\x2', '\x9E', '(', '\x3', '\x2', '\x2', '\x2', '\x9F', '\xA0', 
		'\a', '\x30', '\x2', '\x2', '\xA0', '\xA1', '\a', '\x5428', '\x2', '\x2', 
		'\xA1', '\xA2', '\a', '\x521B', '\x2', '\x2', '\xA2', '*', '\x3', '\x2', 
		'\x2', '\x2', '\xA3', '\xA4', '\a', '\x30', '\x2', '\x2', '\xA4', '\xA5', 
		'\a', '\x5984', '\x2', '\x2', '\xA5', '\xA6', '\a', '\x679E', '\x2', '\x2', 
		'\xA6', '\xA7', '\a', '\x7ED5', '\x2', '\x2', '\xA7', '\xA8', '\a', '\x6761', 
		'\x2', '\x2', '\xA8', ',', '\x3', '\x2', '\x2', '\x2', '\xA9', '\xAA', 
		'\a', '\x30', '\x2', '\x2', '\xAA', '\xAB', '\a', '\x5226', '\x2', '\x2', 
		'\xAB', '\xAC', '\a', '\x65AF', '\x2', '\x2', '\xAC', '\xAD', '\a', '\x5FAC', 
		'\x2', '\x2', '\xAD', '\xAE', '\a', '\x73B1', '\x2', '\x2', '\xAE', '\xAF', 
		'\a', '\x9998', '\x2', '\x2', '\xAF', '.', '\x3', '\x2', '\x2', '\x2', 
		'\xB0', '\xB1', '\a', '\x30', '\x2', '\x2', '\xB1', '\xB2', '\a', '\x5226', 
		'\x2', '\x2', '\xB2', '\xB3', '\a', '\x65AF', '\x2', '\x2', '\xB3', '\xB4', 
		'\a', '\x5FAC', '\x2', '\x2', '\xB4', '\xB5', '\a', '\x73B1', '\x2', '\x2', 
		'\xB5', '\xB6', '\a', '\x5C40', '\x2', '\x2', '\xB6', '\x30', '\x3', '\x2', 
		'\x2', '\x2', '\xB7', '\xB8', '\a', '\x30', '\x2', '\x2', '\xB8', '\xB9', 
		'\a', '\x8BA3', '\x2', '\x2', '\xB9', '\xBA', '\a', '\x6B23', '\x2', '\x2', 
		'\xBA', '\xBB', '\a', '\x5FAC', '\x2', '\x2', '\xBB', '\xBC', '\a', '\x73B1', 
		'\x2', '\x2', '\xBC', '\xBD', '\a', '\x9998', '\x2', '\x2', '\xBD', '\x32', 
		'\x3', '\x2', '\x2', '\x2', '\xBE', '\xBF', '\a', '\x30', '\x2', '\x2', 
		'\xBF', '\xC0', '\a', '\x8BA3', '\x2', '\x2', '\xC0', '\xC1', '\a', '\x6B23', 
		'\x2', '\x2', '\xC1', '\xC2', '\a', '\x5FAC', '\x2', '\x2', '\xC2', '\xC3', 
		'\a', '\x73B1', '\x2', '\x2', '\xC3', '\xC4', '\a', '\x5C40', '\x2', '\x2', 
		'\xC4', '\x34', '\x3', '\x2', '\x2', '\x2', '\xC5', '\xC6', '\a', '\x7721', 
		'\x2', '\x2', '\xC6', '\x36', '\x3', '\x2', '\x2', '\x2', '\xC7', '\xC8', 
		'\a', '\x5049', '\x2', '\x2', '\xC8', '\x38', '\x3', '\x2', '\x2', '\x2', 
		'\xC9', '\xCA', '\a', '\xFF0D', '\x2', '\x2', '\xCA', ':', '\x3', '\x2', 
		'\x2', '\x2', '\xCB', '\xCC', '\a', '\xFF0F', '\x2', '\x2', '\xCC', '<', 
		'\x3', '\x2', '\x2', '\x2', '\xCD', '\xCE', '\a', '\xD9', '\x2', '\x2', 
		'\xCE', '>', '\x3', '\x2', '\x2', '\x2', '\xCF', '\xD0', '\a', '\xF9', 
		'\x2', '\x2', '\xD0', '@', '\x3', '\x2', '\x2', '\x2', '\xD1', '\xD2', 
		'\a', '\xFF1F', '\x2', '\x2', '\xD2', '\x42', '\x3', '\x2', '\x2', '\x2', 
		'\xD3', '\xD4', '\a', '\x2262', '\x2', '\x2', '\xD4', '\x44', '\x3', '\x2', 
		'\x2', '\x2', '\xD5', '\xD6', '\a', '\x6218', '\x2', '\x2', '\xD6', '\x46', 
		'\x3', '\x2', '\x2', '\x2', '\xD7', '\xD9', '\x4', '\x32', ';', '\x2', 
		'\xD8', '\xD7', '\x3', '\x2', '\x2', '\x2', '\xD9', '\xDA', '\x3', '\x2', 
		'\x2', '\x2', '\xDA', '\xD8', '\x3', '\x2', '\x2', '\x2', '\xDA', '\xDB', 
		'\x3', '\x2', '\x2', '\x2', '\xDB', 'H', '\x3', '\x2', '\x2', '\x2', '\xDC', 
		'\xDE', '\x5', 'G', '$', '\x2', '\xDD', '\xDC', '\x3', '\x2', '\x2', '\x2', 
		'\xDD', '\xDE', '\x3', '\x2', '\x2', '\x2', '\xDE', '\xDF', '\x3', '\x2', 
		'\x2', '\x2', '\xDF', '\xE0', '\a', '\x30', '\x2', '\x2', '\xE0', '\xE7', 
		'\x5', 'G', '$', '\x2', '\xE1', '\xE2', '\x5', 'G', '$', '\x2', '\xE2', 
		'\xE4', '\a', '\x30', '\x2', '\x2', '\xE3', '\xE5', '\x5', 'G', '$', '\x2', 
		'\xE4', '\xE3', '\x3', '\x2', '\x2', '\x2', '\xE4', '\xE5', '\x3', '\x2', 
		'\x2', '\x2', '\xE5', '\xE7', '\x3', '\x2', '\x2', '\x2', '\xE6', '\xDD', 
		'\x3', '\x2', '\x2', '\x2', '\xE6', '\xE1', '\x3', '\x2', '\x2', '\x2', 
		'\xE7', 'J', '\x3', '\x2', '\x2', '\x2', '\xE8', '\xE9', '\t', '\x2', 
		'\x2', '\x2', '\xE9', 'L', '\x3', '\x2', '\x2', '\x2', '\xEA', '\xED', 
		'\t', '\x3', '\x2', '\x2', '\xEB', '\xED', '\x5', 'K', '&', '\x2', '\xEC', 
		'\xEA', '\x3', '\x2', '\x2', '\x2', '\xEC', '\xEB', '\x3', '\x2', '\x2', 
		'\x2', '\xED', '\xEE', '\x3', '\x2', '\x2', '\x2', '\xEE', '\xEC', '\x3', 
		'\x2', '\x2', '\x2', '\xEE', '\xEF', '\x3', '\x2', '\x2', '\x2', '\xEF', 
		'N', '\x3', '\x2', '\x2', '\x2', '\xF0', '\xF2', '\t', '\x4', '\x2', '\x2', 
		'\xF1', '\xF0', '\x3', '\x2', '\x2', '\x2', '\xF2', '\xF3', '\x3', '\x2', 
		'\x2', '\x2', '\xF3', '\xF1', '\x3', '\x2', '\x2', '\x2', '\xF3', '\xF4', 
		'\x3', '\x2', '\x2', '\x2', '\xF4', '\xF5', '\x3', '\x2', '\x2', '\x2', 
		'\xF5', '\xF6', '\b', '(', '\x2', '\x2', '\xF6', 'P', '\x3', '\x2', '\x2', 
		'\x2', '\xF7', '\xF9', '\a', '\xF', '\x2', '\x2', '\xF8', '\xF7', '\x3', 
		'\x2', '\x2', '\x2', '\xF8', '\xF9', '\x3', '\x2', '\x2', '\x2', '\xF9', 
		'\xFA', '\x3', '\x2', '\x2', '\x2', '\xFA', '\xFB', '\a', '\f', '\x2', 
		'\x2', '\xFB', '\xFC', '\x3', '\x2', '\x2', '\x2', '\xFC', '\xFD', '\b', 
		')', '\x2', '\x2', '\xFD', 'R', '\x3', '\x2', '\x2', '\x2', '\xFE', '\x102', 
		'\a', '\x201E', '\x2', '\x2', '\xFF', '\x101', '\v', '\x2', '\x2', '\x2', 
		'\x100', '\xFF', '\x3', '\x2', '\x2', '\x2', '\x101', '\x104', '\x3', 
		'\x2', '\x2', '\x2', '\x102', '\x103', '\x3', '\x2', '\x2', '\x2', '\x102', 
		'\x100', '\x3', '\x2', '\x2', '\x2', '\x103', '\x105', '\x3', '\x2', '\x2', 
		'\x2', '\x104', '\x102', '\x3', '\x2', '\x2', '\x2', '\x105', '\x106', 
		'\a', '\x201F', '\x2', '\x2', '\x106', 'T', '\x3', '\x2', '\x2', '\x2', 
		'\x107', '\x10B', '\a', ')', '\x2', '\x2', '\x108', '\x10A', '\v', '\x2', 
		'\x2', '\x2', '\x109', '\x108', '\x3', '\x2', '\x2', '\x2', '\x10A', '\x10D', 
		'\x3', '\x2', '\x2', '\x2', '\x10B', '\x10C', '\x3', '\x2', '\x2', '\x2', 
		'\x10B', '\x109', '\x3', '\x2', '\x2', '\x2', '\x10C', '\x10F', '\x3', 
		'\x2', '\x2', '\x2', '\x10D', '\x10B', '\x3', '\x2', '\x2', '\x2', '\x10E', 
		'\x110', '\a', '\xF', '\x2', '\x2', '\x10F', '\x10E', '\x3', '\x2', '\x2', 
		'\x2', '\x10F', '\x110', '\x3', '\x2', '\x2', '\x2', '\x110', '\x111', 
		'\x3', '\x2', '\x2', '\x2', '\x111', '\x112', '\a', '\f', '\x2', '\x2', 
		'\x112', '\x113', '\x3', '\x2', '\x2', '\x2', '\x113', '\x114', '\b', 
		'+', '\x2', '\x2', '\x114', 'V', '\x3', '\x2', '\x2', '\x2', '\x115', 
		'\x116', '\v', '\x2', '\x2', '\x2', '\x116', 'X', '\x3', '\x2', '\x2', 
		'\x2', '\xE', '\x2', '\xDA', '\xDD', '\xE4', '\xE6', '\xEC', '\xEE', '\xF3', 
		'\xF8', '\x102', '\x10B', '\x10F', '\x3', '\b', '\x2', '\x2',
	};

	public static readonly ATN _ATN =
		new ATNDeserializer().Deserialize(_serializedATN);


}
