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

using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
using IToken = Antlr4.Runtime.IToken;

/// <summary>
/// This interface defines a complete generic visitor for a parse tree produced
/// by <see cref="openeParser"/>.
/// </summary>
/// <typeparam name="Result">The return type of the visit operation.</typeparam>
[System.CodeDom.Compiler.GeneratedCode("ANTLR", "4.7.2")]
[System.CLSCompliant(false)]
public interface IopeneVisitor<Result> : IParseTreeVisitor<Result> {
	/// <summary>
	/// Visit a parse tree produced by <see cref="openeParser.opene_src"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitOpene_src([NotNull] openeParser.Opene_srcContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="openeParser.edition_spec"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitEdition_spec([NotNull] openeParser.Edition_specContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="openeParser.library_list_opt"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitLibrary_list_opt([NotNull] openeParser.Library_list_optContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="openeParser.library_spec"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitLibrary_spec([NotNull] openeParser.Library_specContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="openeParser.prog_set_name"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitProg_set_name([NotNull] openeParser.Prog_set_nameContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="openeParser.prog_set_variable_decl_opt"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitProg_set_variable_decl_opt([NotNull] openeParser.Prog_set_variable_decl_optContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="openeParser.variable_decl"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitVariable_decl([NotNull] openeParser.Variable_declContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="openeParser.dimension_decl"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitDimension_decl([NotNull] openeParser.Dimension_declContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="openeParser.sub_program_opt"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitSub_program_opt([NotNull] openeParser.Sub_program_optContext context);
}
