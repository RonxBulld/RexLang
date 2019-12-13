
// Generated from openeParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"


namespace opene {


class  openeParser : public antlr4::Parser {
public:
  enum {
    K_VERSION = 1, K_LIBRARY = 2, K_PROGRAM_SET = 3, K_PROGRAM_SET_VARIABLE = 4, 
    K_LOCAL_VARIABLE = 5, K_GLOBAL_VARIABLE = 6, K_DLL_DEFINE = 7, K_MEMBER_VARIABLE = 8, 
    K_PARAMETER = 9, K_SUB_PROGRAM = 10, K_STRUCTURE = 11, K_IF_TRUE = 12, 
    K_END_IF_TRUE = 13, K_IF = 14, K_ELSE = 15, K_END_IF = 16, K_WHILE = 17, 
    K_WHILE_END = 18, K_FOR = 19, K_FOR_END = 20, K_TRUE = 21, K_FALSE = 22, 
    K_ADD_OPT = 23, K_SUB_OPT = 24, K_MUL_OPT = 25, K_DIV_OPT = 26, K_FULL_DIV_OPT = 27, 
    K_MOD_OPT = 28, K_AECOM_OPT = 29, K_ASSIGN_OPT = 30, K_EQUAL_OPT = 31, 
    K_NOT_EQUAL_OPT = 32, K_GREAT_OPT = 33, K_LESS_OPT = 34, K_GREAT_EQU_OPT = 35, 
    K_LESS_EQU_OPT = 36, K_LIKE_EQU_OPT = 37, K_OR_OPT = 38, K_AND_OPT = 39, 
    COMMA = 40, LBRACK = 41, RBRACK = 42, LSQUBRACK = 43, RSQUBRACK = 44, 
    SHARP = 45, ADDRESS = 46, DQUOTE = 47, DOT = 48, INTEGER_LITERAL = 49, 
    FLOAT_LITERAL = 50, IDENTIFIER = 51, WHITESPACE = 52, NEWLINE = 53, 
    STRING_LITERAL = 54, OTHER_CHAR = 55, TABLE_END = 56, TABLE_ITEM = 57, 
    TABLE_WS = 58, TABLE_COMMA = 59
  };

  enum {
    RuleOpene_src = 0, RuleSrc_content = 1, RuleProgram_set_file = 2, RuleData_structure_file = 3, 
    RuleGlobal_variable_file = 4, RuleDll_define_file = 5, RuleDll_command = 6, 
    RuleGlobal_variable_list = 7, RuleGlobal_variable_item = 8, RuleEdition_spec = 9, 
    RuleStruct_declare = 10, RuleTable_comment = 11, RuleMember_list = 12, 
    RuleMember_item = 13, RuleLibrary_list_opt = 14, RuleLibrary_spec = 15, 
    RuleProg_set = 16, RuleProg_set_variable_decl_opt = 17, RuleProg_set_variable_decl = 18, 
    RuleVariable_decl = 19, RuleVariable_comment = 20, RuleVariable_comment_element = 21, 
    RuleVariable_name = 22, RuleVariable_type = 23, RuleDimension_decl = 24, 
    RuleSub_program_opt = 25, RuleSub_program = 26, RuleParameter_decl_list = 27, 
    RuleParameter_decl = 28, RuleLocal_variable_decl = 29, RuleStatement_list = 30, 
    RuleStatement = 31, RuleLoop_statement = 32, RuleCondition_statement = 33, 
    RuleCondition_statement_else = 34, RuleHierarchy_identifier = 35, RuleName_component = 36, 
    RuleExpression = 37, RuleMacro_value = 38, RuleFunc_ptr = 39, RuleBool_value = 40, 
    RuleNumber = 41, RuleString_value = 42
  };

  openeParser(antlr4::TokenStream *input);
  ~openeParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class Opene_srcContext;
  class Src_contentContext;
  class Program_set_fileContext;
  class Data_structure_fileContext;
  class Global_variable_fileContext;
  class Dll_define_fileContext;
  class Dll_commandContext;
  class Global_variable_listContext;
  class Global_variable_itemContext;
  class Edition_specContext;
  class Struct_declareContext;
  class Table_commentContext;
  class Member_listContext;
  class Member_itemContext;
  class Library_list_optContext;
  class Library_specContext;
  class Prog_setContext;
  class Prog_set_variable_decl_optContext;
  class Prog_set_variable_declContext;
  class Variable_declContext;
  class Variable_commentContext;
  class Variable_comment_elementContext;
  class Variable_nameContext;
  class Variable_typeContext;
  class Dimension_declContext;
  class Sub_program_optContext;
  class Sub_programContext;
  class Parameter_decl_listContext;
  class Parameter_declContext;
  class Local_variable_declContext;
  class Statement_listContext;
  class StatementContext;
  class Loop_statementContext;
  class Condition_statementContext;
  class Condition_statement_elseContext;
  class Hierarchy_identifierContext;
  class Name_componentContext;
  class ExpressionContext;
  class Macro_valueContext;
  class Func_ptrContext;
  class Bool_valueContext;
  class NumberContext;
  class String_valueContext; 

  class  Opene_srcContext : public antlr4::ParserRuleContext {
  public:
    Opene_srcContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Edition_specContext *edition_spec();
    antlr4::tree::TerminalNode *NEWLINE();
    Src_contentContext *src_content();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Opene_srcContext* opene_src();

  class  Src_contentContext : public antlr4::ParserRuleContext {
  public:
    Src_contentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Program_set_fileContext *program_set_file();
    Data_structure_fileContext *data_structure_file();
    Global_variable_fileContext *global_variable_file();
    Dll_define_fileContext *dll_define_file();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Src_contentContext* src_content();

  class  Program_set_fileContext : public antlr4::ParserRuleContext {
  public:
    Program_set_fileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Library_list_optContext *library_list_opt();
    Prog_setContext *prog_set();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Program_set_fileContext* program_set_file();

  class  Data_structure_fileContext : public antlr4::ParserRuleContext {
  public:
    Data_structure_fileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Struct_declareContext *> struct_declare();
    Struct_declareContext* struct_declare(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Data_structure_fileContext* data_structure_file();

  class  Global_variable_fileContext : public antlr4::ParserRuleContext {
  public:
    Global_variable_fileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Global_variable_listContext *global_variable_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Global_variable_fileContext* global_variable_file();

  class  Dll_define_fileContext : public antlr4::ParserRuleContext {
  public:
    Dll_define_fileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Dll_commandContext *> dll_command();
    Dll_commandContext* dll_command(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Dll_define_fileContext* dll_define_file();

  class  Dll_commandContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *file = nullptr;;
    antlr4::Token *cmd = nullptr;;
    Dll_commandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_DLL_DEFINE();
    std::vector<antlr4::tree::TerminalNode *> TABLE_COMMA();
    antlr4::tree::TerminalNode* TABLE_COMMA(size_t i);
    antlr4::tree::TerminalNode *TABLE_END();
    std::vector<antlr4::tree::TerminalNode *> TABLE_ITEM();
    antlr4::tree::TerminalNode* TABLE_ITEM(size_t i);
    Table_commentContext *table_comment();
    std::vector<Parameter_declContext *> parameter_decl();
    Parameter_declContext* parameter_decl(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Dll_commandContext* dll_command();

  class  Global_variable_listContext : public antlr4::ParserRuleContext {
  public:
    Global_variable_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Global_variable_itemContext *> global_variable_item();
    Global_variable_itemContext* global_variable_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Global_variable_listContext* global_variable_list();

  class  Global_variable_itemContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *access = nullptr;;
    antlr4::Token *dimension = nullptr;;
    Global_variable_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_GLOBAL_VARIABLE();
    antlr4::tree::TerminalNode *TABLE_END();
    std::vector<antlr4::tree::TerminalNode *> TABLE_ITEM();
    antlr4::tree::TerminalNode* TABLE_ITEM(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TABLE_COMMA();
    antlr4::tree::TerminalNode* TABLE_COMMA(size_t i);
    Table_commentContext *table_comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Global_variable_itemContext* global_variable_item();

  class  Edition_specContext : public antlr4::ParserRuleContext {
  public:
    Edition_specContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_VERSION();
    antlr4::tree::TerminalNode *INTEGER_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Edition_specContext* edition_spec();

  class  Struct_declareContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *access = nullptr;;
    Struct_declareContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_STRUCTURE();
    antlr4::tree::TerminalNode *TABLE_END();
    Member_listContext *member_list();
    std::vector<antlr4::tree::TerminalNode *> TABLE_ITEM();
    antlr4::tree::TerminalNode* TABLE_ITEM(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TABLE_COMMA();
    antlr4::tree::TerminalNode* TABLE_COMMA(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    Table_commentContext *table_comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_declareContext* struct_declare();

  class  Table_commentContext : public antlr4::ParserRuleContext {
  public:
    Table_commentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> TABLE_COMMA();
    antlr4::tree::TerminalNode* TABLE_COMMA(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TABLE_ITEM();
    antlr4::tree::TerminalNode* TABLE_ITEM(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_commentContext* table_comment();

  class  Member_listContext : public antlr4::ParserRuleContext {
  public:
    Member_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Member_itemContext *> member_item();
    Member_itemContext* member_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Member_listContext* member_list();

  class  Member_itemContext : public antlr4::ParserRuleContext {
  public:
    Member_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_MEMBER_VARIABLE();
    Variable_declContext *variable_decl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Member_itemContext* member_item();

  class  Library_list_optContext : public antlr4::ParserRuleContext {
  public:
    Library_list_optContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Library_specContext *> library_spec();
    Library_specContext* library_spec(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Library_list_optContext* library_list_opt();

  class  Library_specContext : public antlr4::ParserRuleContext {
  public:
    Library_specContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_LIBRARY();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *NEWLINE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Library_specContext* library_spec();

  class  Prog_setContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *base = nullptr;;
    antlr4::Token *access = nullptr;;
    Prog_setContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_PROGRAM_SET();
    antlr4::tree::TerminalNode *TABLE_END();
    Prog_set_variable_decl_optContext *prog_set_variable_decl_opt();
    Sub_program_optContext *sub_program_opt();
    std::vector<antlr4::tree::TerminalNode *> TABLE_ITEM();
    antlr4::tree::TerminalNode* TABLE_ITEM(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TABLE_COMMA();
    antlr4::tree::TerminalNode* TABLE_COMMA(size_t i);
    Table_commentContext *table_comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Prog_setContext* prog_set();

  class  Prog_set_variable_decl_optContext : public antlr4::ParserRuleContext {
  public:
    Prog_set_variable_decl_optContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Prog_set_variable_declContext *> prog_set_variable_decl();
    Prog_set_variable_declContext* prog_set_variable_decl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Prog_set_variable_decl_optContext* prog_set_variable_decl_opt();

  class  Prog_set_variable_declContext : public antlr4::ParserRuleContext {
  public:
    Prog_set_variable_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_PROGRAM_SET_VARIABLE();
    Variable_declContext *variable_decl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Prog_set_variable_declContext* prog_set_variable_decl();

  class  Variable_declContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *dimension = nullptr;;
    Variable_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TABLE_END();
    std::vector<antlr4::tree::TerminalNode *> TABLE_ITEM();
    antlr4::tree::TerminalNode* TABLE_ITEM(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TABLE_COMMA();
    antlr4::tree::TerminalNode* TABLE_COMMA(size_t i);
    Table_commentContext *table_comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_declContext* variable_decl();

  class  Variable_commentContext : public antlr4::ParserRuleContext {
  public:
    Variable_commentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Variable_comment_elementContext *> variable_comment_element();
    Variable_comment_elementContext* variable_comment_element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_commentContext* variable_comment();

  class  Variable_comment_elementContext : public antlr4::ParserRuleContext {
  public:
    Variable_comment_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *OTHER_CHAR();
    antlr4::tree::TerminalNode *COMMA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_comment_elementContext* variable_comment_element();

  class  Variable_nameContext : public antlr4::ParserRuleContext {
  public:
    Variable_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_nameContext* variable_name();

  class  Variable_typeContext : public antlr4::ParserRuleContext {
  public:
    Variable_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_typeContext* variable_type();

  class  Dimension_declContext : public antlr4::ParserRuleContext {
  public:
    Dimension_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> DQUOTE();
    antlr4::tree::TerminalNode* DQUOTE(size_t i);
    antlr4::tree::TerminalNode *INTEGER_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Dimension_declContext* dimension_decl();

  class  Sub_program_optContext : public antlr4::ParserRuleContext {
  public:
    Sub_program_optContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Sub_programContext *> sub_program();
    Sub_programContext* sub_program(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sub_program_optContext* sub_program_opt();

  class  Sub_programContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *access = nullptr;;
    Sub_programContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_SUB_PROGRAM();
    antlr4::tree::TerminalNode *TABLE_END();
    Parameter_decl_listContext *parameter_decl_list();
    Statement_listContext *statement_list();
    std::vector<antlr4::tree::TerminalNode *> TABLE_ITEM();
    antlr4::tree::TerminalNode* TABLE_ITEM(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TABLE_COMMA();
    antlr4::tree::TerminalNode* TABLE_COMMA(size_t i);
    std::vector<Local_variable_declContext *> local_variable_decl();
    Local_variable_declContext* local_variable_decl(size_t i);
    Table_commentContext *table_comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sub_programContext* sub_program();

  class  Parameter_decl_listContext : public antlr4::ParserRuleContext {
  public:
    Parameter_decl_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Parameter_declContext *> parameter_decl();
    Parameter_declContext* parameter_decl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Parameter_decl_listContext* parameter_decl_list();

  class  Parameter_declContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *attributes = nullptr;;
    Parameter_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_PARAMETER();
    std::vector<antlr4::tree::TerminalNode *> TABLE_COMMA();
    antlr4::tree::TerminalNode* TABLE_COMMA(size_t i);
    antlr4::tree::TerminalNode *TABLE_END();
    std::vector<antlr4::tree::TerminalNode *> TABLE_ITEM();
    antlr4::tree::TerminalNode* TABLE_ITEM(size_t i);
    Table_commentContext *table_comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Parameter_declContext* parameter_decl();

  class  Local_variable_declContext : public antlr4::ParserRuleContext {
  public:
    Local_variable_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_LOCAL_VARIABLE();
    Variable_declContext *variable_decl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Local_variable_declContext* local_variable_decl();

  class  Statement_listContext : public antlr4::ParserRuleContext {
  public:
    Statement_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Statement_listContext* statement_list();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatementContext() : antlr4::ParserRuleContext() { }
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExpressionStatementContext : public StatementContext {
  public:
    ExpressionStatementContext(StatementContext *ctx);

    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConditionStatementContext : public StatementContext {
  public:
    ConditionStatementContext(StatementContext *ctx);

    Condition_statementContext *condition_statement();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LoopStatementContext : public StatementContext {
  public:
    LoopStatementContext(StatementContext *ctx);

    Loop_statementContext *loop_statement();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignStatementContext : public StatementContext {
  public:
    AssignStatementContext(StatementContext *ctx);

    Hierarchy_identifierContext *hierarchy_identifier();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *K_ASSIGN_OPT();
    antlr4::tree::TerminalNode *K_AECOM_OPT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StatementContext* statement();

  class  Loop_statementContext : public antlr4::ParserRuleContext {
  public:
    Loop_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Loop_statementContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Loop_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ForContext : public Loop_statementContext {
  public:
    ForContext(Loop_statementContext *ctx);

    antlr4::tree::TerminalNode *K_FOR();
    std::vector<antlr4::tree::TerminalNode *> LBRACK();
    antlr4::tree::TerminalNode* LBRACK(size_t i);
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *COMMA();
    std::vector<antlr4::tree::TerminalNode *> RBRACK();
    antlr4::tree::TerminalNode* RBRACK(size_t i);
    Statement_listContext *statement_list();
    antlr4::tree::TerminalNode *K_FOR_END();
    antlr4::tree::TerminalNode *IDENTIFIER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WhileContext : public Loop_statementContext {
  public:
    WhileContext(Loop_statementContext *ctx);

    antlr4::tree::TerminalNode *K_WHILE();
    std::vector<antlr4::tree::TerminalNode *> LBRACK();
    antlr4::tree::TerminalNode* LBRACK(size_t i);
    ExpressionContext *expression();
    std::vector<antlr4::tree::TerminalNode *> RBRACK();
    antlr4::tree::TerminalNode* RBRACK(size_t i);
    Statement_listContext *statement_list();
    antlr4::tree::TerminalNode *K_WHILE_END();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Loop_statementContext* loop_statement();

  class  Condition_statementContext : public antlr4::ParserRuleContext {
  public:
    Condition_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Condition_statementContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Condition_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IfStmtContext : public Condition_statementContext {
  public:
    IfStmtContext(Condition_statementContext *ctx);

    antlr4::tree::TerminalNode *K_IF();
    antlr4::tree::TerminalNode *LBRACK();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRACK();
    Statement_listContext *statement_list();
    antlr4::tree::TerminalNode *K_END_IF();
    Condition_statement_elseContext *condition_statement_else();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfTrueStmtContext : public Condition_statementContext {
  public:
    IfTrueStmtContext(Condition_statementContext *ctx);

    antlr4::tree::TerminalNode *K_IF_TRUE();
    antlr4::tree::TerminalNode *LBRACK();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRACK();
    Statement_listContext *statement_list();
    antlr4::tree::TerminalNode *K_END_IF_TRUE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Condition_statementContext* condition_statement();

  class  Condition_statement_elseContext : public antlr4::ParserRuleContext {
  public:
    Condition_statement_elseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_ELSE();
    Statement_listContext *statement_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Condition_statement_elseContext* condition_statement_else();

  class  Hierarchy_identifierContext : public antlr4::ParserRuleContext {
  public:
    Hierarchy_identifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Name_componentContext *> name_component();
    Name_componentContext* name_component(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Hierarchy_identifierContext* hierarchy_identifier();

  class  Name_componentContext : public antlr4::ParserRuleContext {
  public:
    Name_componentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Name_componentContext() : antlr4::ParserRuleContext() { }
    void copyFrom(Name_componentContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IdentifierContext : public Name_componentContext {
  public:
    IdentifierContext(Name_componentContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FuncCallWithArguContext : public Name_componentContext {
  public:
    FuncCallWithArguContext(Name_componentContext *ctx);

    Name_componentContext *name_component();
    antlr4::tree::TerminalNode *LBRACK();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *RBRACK();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FuncCallWithoutArguContext : public Name_componentContext {
  public:
    FuncCallWithoutArguContext(Name_componentContext *ctx);

    Name_componentContext *name_component();
    antlr4::tree::TerminalNode *LBRACK();
    antlr4::tree::TerminalNode *RBRACK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayIndexContext : public Name_componentContext {
  public:
    ArrayIndexContext(Name_componentContext *ctx);

    Name_componentContext *name_component();
    antlr4::tree::TerminalNode *LSQUBRACK();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RSQUBRACK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Name_componentContext* name_component();
  Name_componentContext* name_component(int precedence);
  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() : antlr4::ParserRuleContext() { }
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BracketContext : public ExpressionContext {
  public:
    BracketContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *LBRACK();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRACK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OptElementContext : public ExpressionContext {
  public:
    OptElementContext(ExpressionContext *ctx);

    NumberContext *number();
    Bool_valueContext *bool_value();
    Macro_valueContext *macro_value();
    String_valueContext *string_value();
    Hierarchy_identifierContext *hierarchy_identifier();
    Func_ptrContext *func_ptr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BinaryExprContext : public ExpressionContext {
  public:
    BinaryExprContext(ExpressionContext *ctx);

    openeParser::ExpressionContext *lval = nullptr;
    antlr4::Token *opt = nullptr;
    openeParser::ExpressionContext *rval = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *K_MUL_OPT();
    antlr4::tree::TerminalNode *K_DIV_OPT();
    antlr4::tree::TerminalNode *K_FULL_DIV_OPT();
    antlr4::tree::TerminalNode *K_MOD_OPT();
    antlr4::tree::TerminalNode *K_ADD_OPT();
    antlr4::tree::TerminalNode *K_SUB_OPT();
    antlr4::tree::TerminalNode *K_NOT_EQUAL_OPT();
    antlr4::tree::TerminalNode *K_EQUAL_OPT();
    antlr4::tree::TerminalNode *K_AECOM_OPT();
    antlr4::tree::TerminalNode *K_LESS_OPT();
    antlr4::tree::TerminalNode *K_GREAT_OPT();
    antlr4::tree::TerminalNode *K_LESS_EQU_OPT();
    antlr4::tree::TerminalNode *K_GREAT_EQU_OPT();
    antlr4::tree::TerminalNode *K_LIKE_EQU_OPT();
    antlr4::tree::TerminalNode *K_AND_OPT();
    antlr4::tree::TerminalNode *K_OR_OPT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryExprContext : public ExpressionContext {
  public:
    UnaryExprContext(ExpressionContext *ctx);

    antlr4::Token *opt = nullptr;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *K_SUB_OPT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  Macro_valueContext : public antlr4::ParserRuleContext {
  public:
    Macro_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SHARP();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Macro_valueContext* macro_value();

  class  Func_ptrContext : public antlr4::ParserRuleContext {
  public:
    Func_ptrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ADDRESS();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Func_ptrContext* func_ptr();

  class  Bool_valueContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *bval = nullptr;;
    Bool_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_TRUE();
    antlr4::tree::TerminalNode *K_FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Bool_valueContext* bool_value();

  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    NumberContext() : antlr4::ParserRuleContext() { }
    void copyFrom(NumberContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FloatContext : public NumberContext {
  public:
    FloatContext(NumberContext *ctx);

    antlr4::tree::TerminalNode *FLOAT_LITERAL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntContext : public NumberContext {
  public:
    IntContext(NumberContext *ctx);

    antlr4::tree::TerminalNode *INTEGER_LITERAL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  NumberContext* number();

  class  String_valueContext : public antlr4::ParserRuleContext {
  public:
    String_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  String_valueContext* string_value();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool name_componentSempred(Name_componentContext *_localctx, size_t predicateIndex);
  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace opene
