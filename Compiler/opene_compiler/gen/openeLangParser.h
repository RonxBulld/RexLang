
// Generated from /mnt/d/Project/OpenELanguage/Compiler/opene_compiler/openeLang.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"


namespace opene {


class  openeLangParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, K_ADD_OPT = 55, K_SUB_OPT = 56, 
    K_MUL_OPT = 57, K_DIV_OPT = 58, K_FULL_DIV_OPT = 59, K_MOD_OPT = 60, 
    K_AECOM_OPT = 61, K_ASSIGN_OPT = 62, K_EQUAL_OPT = 63, K_NOT_EQUAL_OPT = 64, 
    K_GREAT_OPT = 65, K_LESS_OPT = 66, K_GREAT_EQU_OPT = 67, K_LESS_EQU_OPT = 68, 
    K_LIKE_EQU_OPT = 69, K_OR_OPT = 70, K_AND_OPT = 71, INTEGER_LITERAL = 72, 
    FLOAT_LITERAL = 73, IDENTIFIER = 74, WHITESPACE = 75, NEWLINE = 76, 
    STRING_LITERAL = 77, OTHER_CHAR = 78
  };

  enum {
    RuleOpene_src = 0, RuleSrc_content = 1, RuleProgram_set_file = 2, RuleData_structure_file = 3, 
    RuleGlobal_variable_file = 4, RuleDll_define_file = 5, RuleDll_command = 6, 
    RuleLib_command = 7, RuleGlobal_variable_list = 8, RuleGlobal_variable_item = 9, 
    RuleEdition_spec = 10, RuleStruct_declare = 11, RuleTable_comment = 12, 
    RuleProg_set = 13, RuleVariable_decl = 14, RuleMember_vari_decl = 15, 
    RuleFile_vari_decl = 16, RuleSub_program = 17, RuleLocal_variable_decl = 18, 
    RuleParameter_decl = 19, RuleStatement_list = 20, RuleStatement = 21, 
    RuleSwitch_statement = 22, RuleLoop_statement = 23, RuleCondition_statement = 24, 
    RuleControl_statement = 25, RuleHierarchy_identifier = 26, RuleName_component = 27, 
    RuleExpression = 28, RuleData_set_value = 29, RuleDatetime_value = 30, 
    RuleDatetime_value_core = 31, RuleMacro_value = 32, RuleFunc_ptr = 33, 
    RuleBool_value = 34, RuleNumber = 35, RuleString_value = 36
  };

  openeLangParser(antlr4::TokenStream *input);
  ~openeLangParser();

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
  class Lib_commandContext;
  class Global_variable_listContext;
  class Global_variable_itemContext;
  class Edition_specContext;
  class Struct_declareContext;
  class Table_commentContext;
  class Prog_setContext;
  class Variable_declContext;
  class Member_vari_declContext;
  class File_vari_declContext;
  class Sub_programContext;
  class Local_variable_declContext;
  class Parameter_declContext;
  class Statement_listContext;
  class StatementContext;
  class Switch_statementContext;
  class Loop_statementContext;
  class Condition_statementContext;
  class Control_statementContext;
  class Hierarchy_identifierContext;
  class Name_componentContext;
  class ExpressionContext;
  class Data_set_valueContext;
  class Datetime_valueContext;
  class Datetime_value_coreContext;
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
    antlr4::Token *identifierToken = nullptr;;
    std::vector<antlr4::Token *> libraries;;
    Program_set_fileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Prog_setContext *prog_set();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);

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
    std::vector<Lib_commandContext *> lib_command();
    Lib_commandContext* lib_command(size_t i);

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
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STRING_LITERAL();
    antlr4::tree::TerminalNode* STRING_LITERAL(size_t i);
    Table_commentContext *table_comment();
    std::vector<Parameter_declContext *> parameter_decl();
    Parameter_declContext* parameter_decl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Dll_commandContext* dll_command();

  class  Lib_commandContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *file = nullptr;;
    antlr4::Token *cmd = nullptr;;
    Lib_commandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STRING_LITERAL();
    antlr4::tree::TerminalNode* STRING_LITERAL(size_t i);
    Table_commentContext *table_comment();
    std::vector<Parameter_declContext *> parameter_decl();
    Parameter_declContext* parameter_decl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Lib_commandContext* lib_command();

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
    antlr4::tree::TerminalNode *NEWLINE();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    Table_commentContext *table_comment();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Global_variable_itemContext* global_variable_item();

  class  Edition_specContext : public antlr4::ParserRuleContext {
  public:
    Edition_specContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
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
    openeLangParser::Member_vari_declContext *member_vari_declContext = nullptr;;
    std::vector<Member_vari_declContext *> struct_mems;;
    Struct_declareContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<Member_vari_declContext *> member_vari_decl();
    Member_vari_declContext* member_vari_decl(size_t i);
    Table_commentContext *table_comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_declareContext* struct_declare();

  class  Table_commentContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *comment = nullptr;;
    Table_commentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Table_commentContext* table_comment();

  class  Prog_setContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *base = nullptr;;
    antlr4::Token *access = nullptr;;
    openeLangParser::File_vari_declContext *file_vari_declContext = nullptr;;
    std::vector<File_vari_declContext *> prog_set_varis;;
    openeLangParser::Sub_programContext *sub_programContext = nullptr;;
    std::vector<Sub_programContext *> functions;;
    Prog_setContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<File_vari_declContext *> file_vari_decl();
    File_vari_declContext* file_vari_decl(size_t i);
    std::vector<Sub_programContext *> sub_program();
    Sub_programContext* sub_program(size_t i);
    Table_commentContext *table_comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Prog_setContext* prog_set();

  class  Variable_declContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *dimension = nullptr;;
    Variable_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEWLINE();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    Table_commentContext *table_comment();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_declContext* variable_decl();

  class  Member_vari_declContext : public antlr4::ParserRuleContext {
  public:
    Member_vari_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Variable_declContext *variable_decl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Member_vari_declContext* member_vari_decl();

  class  File_vari_declContext : public antlr4::ParserRuleContext {
  public:
    File_vari_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Variable_declContext *variable_decl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  File_vari_declContext* file_vari_decl();

  class  Sub_programContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *access = nullptr;;
    openeLangParser::Parameter_declContext *parameter_declContext = nullptr;;
    std::vector<Parameter_declContext *> params;;
    openeLangParser::Local_variable_declContext *local_variable_declContext = nullptr;;
    std::vector<Local_variable_declContext *> local_vari;;
    Sub_programContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEWLINE();
    Statement_listContext *statement_list();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<Parameter_declContext *> parameter_decl();
    Parameter_declContext* parameter_decl(size_t i);
    std::vector<Local_variable_declContext *> local_variable_decl();
    Local_variable_declContext* local_variable_decl(size_t i);
    Table_commentContext *table_comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sub_programContext* sub_program();

  class  Local_variable_declContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *attribute = nullptr;;
    antlr4::Token *dimension = nullptr;;
    Local_variable_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEWLINE();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    Table_commentContext *table_comment();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Local_variable_declContext* local_variable_decl();

  class  Parameter_declContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;;
    antlr4::Token *type = nullptr;;
    antlr4::Token *identifierToken = nullptr;;
    std::vector<antlr4::Token *> attributes;;
    Parameter_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEWLINE();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    Table_commentContext *table_comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Parameter_declContext* parameter_decl();

  class  Statement_listContext : public antlr4::ParserRuleContext {
  public:
    openeLangParser::StatementContext *statementContext = nullptr;;
    std::vector<StatementContext *> stmts;;
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
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SwitchStatementContext : public StatementContext {
  public:
    SwitchStatementContext(StatementContext *ctx);

    Switch_statementContext *switch_statement();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExpressionStatementContext : public StatementContext {
  public:
    ExpressionStatementContext(StatementContext *ctx);

    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ControlStatementContext : public StatementContext {
  public:
    ControlStatementContext(StatementContext *ctx);

    Control_statementContext *control_statement();
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

  class  Switch_statementContext : public antlr4::ParserRuleContext {
  public:
    openeLangParser::ExpressionContext *major_condition_expr = nullptr;;
    openeLangParser::Statement_listContext *major_cond_body = nullptr;;
    openeLangParser::ExpressionContext *expressionContext = nullptr;;
    std::vector<ExpressionContext *> minor_condition_expr;;
    openeLangParser::Statement_listContext *statement_listContext = nullptr;;
    std::vector<Statement_listContext *> minor_cond_body;;
    openeLangParser::Statement_listContext *default_body = nullptr;;
    Switch_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<Statement_listContext *> statement_list();
    Statement_listContext* statement_list(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Switch_statementContext* switch_statement();

  class  Loop_statementContext : public antlr4::ParserRuleContext {
  public:
    Loop_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Loop_statementContext() = default;
    void copyFrom(Loop_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  RangeForContext : public Loop_statementContext {
  public:
    RangeForContext(Loop_statementContext *ctx);

    openeLangParser::ExpressionContext *times_expr = nullptr;
    openeLangParser::Hierarchy_identifierContext *loop_variable = nullptr;
    openeLangParser::Statement_listContext *loop_body = nullptr;
    antlr4::tree::TerminalNode *NEWLINE();
    ExpressionContext *expression();
    Statement_listContext *statement_list();
    Hierarchy_identifierContext *hierarchy_identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ForContext : public Loop_statementContext {
  public:
    ForContext(Loop_statementContext *ctx);

    openeLangParser::ExpressionContext *loop_start = nullptr;
    openeLangParser::ExpressionContext *loop_end = nullptr;
    openeLangParser::ExpressionContext *loop_step = nullptr;
    openeLangParser::Hierarchy_identifierContext *loop_variable = nullptr;
    openeLangParser::Statement_listContext *loop_body = nullptr;
    antlr4::tree::TerminalNode *NEWLINE();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    Statement_listContext *statement_list();
    Hierarchy_identifierContext *hierarchy_identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DoWhileContext : public Loop_statementContext {
  public:
    DoWhileContext(Loop_statementContext *ctx);

    openeLangParser::Statement_listContext *loop_body = nullptr;
    openeLangParser::ExpressionContext *condition_expr = nullptr;
    antlr4::tree::TerminalNode *NEWLINE();
    Statement_listContext *statement_list();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WhileContext : public Loop_statementContext {
  public:
    WhileContext(Loop_statementContext *ctx);

    openeLangParser::ExpressionContext *condition_expr = nullptr;
    openeLangParser::Statement_listContext *loop_body = nullptr;
    antlr4::tree::TerminalNode *NEWLINE();
    ExpressionContext *expression();
    Statement_listContext *statement_list();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Loop_statementContext* loop_statement();

  class  Condition_statementContext : public antlr4::ParserRuleContext {
  public:
    Condition_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Condition_statementContext() = default;
    void copyFrom(Condition_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IfStmtContext : public Condition_statementContext {
  public:
    IfStmtContext(Condition_statementContext *ctx);

    openeLangParser::ExpressionContext *condition_expr = nullptr;
    openeLangParser::Statement_listContext *true_stmt_list = nullptr;
    openeLangParser::Statement_listContext *false_stmt_list = nullptr;
    ExpressionContext *expression();
    std::vector<Statement_listContext *> statement_list();
    Statement_listContext* statement_list(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfTrueStmtContext : public Condition_statementContext {
  public:
    IfTrueStmtContext(Condition_statementContext *ctx);

    openeLangParser::ExpressionContext *condition_expr = nullptr;
    openeLangParser::Statement_listContext *true_stmt_list = nullptr;
    ExpressionContext *expression();
    Statement_listContext *statement_list();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Condition_statementContext* condition_statement();

  class  Control_statementContext : public antlr4::ParserRuleContext {
  public:
    Control_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Control_statementContext() = default;
    void copyFrom(Control_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ContinueStmtContext : public Control_statementContext {
  public:
    ContinueStmtContext(Control_statementContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExitStmtContext : public Control_statementContext {
  public:
    ExitStmtContext(Control_statementContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BreakStmtContext : public Control_statementContext {
  public:
    BreakStmtContext(Control_statementContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ReturnStmtContext : public Control_statementContext {
  public:
    ReturnStmtContext(Control_statementContext *ctx);

    openeLangParser::ExpressionContext *return_expr = nullptr;
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Control_statementContext* control_statement();

  class  Hierarchy_identifierContext : public antlr4::ParserRuleContext {
  public:
    openeLangParser::Name_componentContext *name_componentContext = nullptr;;
    std::vector<Name_componentContext *> components;;
    Hierarchy_identifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Name_componentContext *> name_component();
    Name_componentContext* name_component(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Hierarchy_identifierContext* hierarchy_identifier();

  class  Name_componentContext : public antlr4::ParserRuleContext {
  public:
    Name_componentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Name_componentContext() = default;
    void copyFrom(Name_componentContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FuncCallContext : public Name_componentContext {
  public:
    FuncCallContext(Name_componentContext *ctx);

    openeLangParser::ExpressionContext *expressionContext = nullptr;
    std::vector<ExpressionContext *> arguments;
    Name_componentContext *name_component();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdentifierContext : public Name_componentContext {
  public:
    IdentifierContext(Name_componentContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayIndexContext : public Name_componentContext {
  public:
    ArrayIndexContext(Name_componentContext *ctx);

    Name_componentContext *name_component();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Name_componentContext* name_component();
  Name_componentContext* name_component(int precedence);
  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BracketContext : public ExpressionContext {
  public:
    BracketContext(ExpressionContext *ctx);

    ExpressionContext *expression();
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
    Datetime_valueContext *datetime_value();
    Data_set_valueContext *data_set_value();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BinaryExprContext : public ExpressionContext {
  public:
    BinaryExprContext(ExpressionContext *ctx);

    openeLangParser::ExpressionContext *lval = nullptr;
    antlr4::Token *opt = nullptr;
    openeLangParser::ExpressionContext *rval = nullptr;
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
  class  Data_set_valueContext : public antlr4::ParserRuleContext {
  public:
    openeLangParser::ExpressionContext *expressionContext = nullptr;;
    std::vector<ExpressionContext *> elems;;
    Data_set_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Data_set_valueContext* data_set_value();

  class  Datetime_valueContext : public antlr4::ParserRuleContext {
  public:
    Datetime_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Datetime_value_coreContext *datetime_value_core();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Datetime_valueContext* datetime_value();

  class  Datetime_value_coreContext : public antlr4::ParserRuleContext {
  public:
    Datetime_value_coreContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Datetime_value_coreContext() = default;
    void copyFrom(Datetime_value_coreContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DatetimeSeparateBySlashColonContext : public Datetime_value_coreContext {
  public:
    DatetimeSeparateBySlashColonContext(Datetime_value_coreContext *ctx);

    antlr4::Token *year = nullptr;
    antlr4::Token *month = nullptr;
    antlr4::Token *day = nullptr;
    antlr4::Token *hour = nullptr;
    antlr4::Token *minute = nullptr;
    antlr4::Token *second = nullptr;
    std::vector<antlr4::tree::TerminalNode *> INTEGER_LITERAL();
    antlr4::tree::TerminalNode* INTEGER_LITERAL(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DatetimePureNumberContext : public Datetime_value_coreContext {
  public:
    DatetimePureNumberContext(Datetime_value_coreContext *ctx);

    antlr4::Token *time = nullptr;
    antlr4::tree::TerminalNode *INTEGER_LITERAL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DatetimeSeparateBySlashContext : public Datetime_value_coreContext {
  public:
    DatetimeSeparateBySlashContext(Datetime_value_coreContext *ctx);

    antlr4::Token *year = nullptr;
    antlr4::Token *month = nullptr;
    antlr4::Token *day = nullptr;
    antlr4::Token *hour = nullptr;
    antlr4::Token *minute = nullptr;
    antlr4::Token *second = nullptr;
    std::vector<antlr4::tree::TerminalNode *> INTEGER_LITERAL();
    antlr4::tree::TerminalNode* INTEGER_LITERAL(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DatetimeSeparateByBarColonContext : public Datetime_value_coreContext {
  public:
    DatetimeSeparateByBarColonContext(Datetime_value_coreContext *ctx);

    antlr4::Token *year = nullptr;
    antlr4::Token *month = nullptr;
    antlr4::Token *day = nullptr;
    antlr4::Token *hour = nullptr;
    antlr4::Token *minute = nullptr;
    antlr4::Token *second = nullptr;
    std::vector<antlr4::tree::TerminalNode *> INTEGER_LITERAL();
    antlr4::tree::TerminalNode* INTEGER_LITERAL(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DatetimeSeparateByBarContext : public Datetime_value_coreContext {
  public:
    DatetimeSeparateByBarContext(Datetime_value_coreContext *ctx);

    antlr4::Token *year = nullptr;
    antlr4::Token *month = nullptr;
    antlr4::Token *day = nullptr;
    antlr4::Token *hour = nullptr;
    antlr4::Token *minute = nullptr;
    antlr4::Token *second = nullptr;
    std::vector<antlr4::tree::TerminalNode *> INTEGER_LITERAL();
    antlr4::tree::TerminalNode* INTEGER_LITERAL(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DatetimeSeparateByChineseContext : public Datetime_value_coreContext {
  public:
    DatetimeSeparateByChineseContext(Datetime_value_coreContext *ctx);

    antlr4::Token *year = nullptr;
    antlr4::Token *month = nullptr;
    antlr4::Token *day = nullptr;
    antlr4::Token *hour = nullptr;
    antlr4::Token *minute = nullptr;
    antlr4::Token *second = nullptr;
    std::vector<antlr4::tree::TerminalNode *> INTEGER_LITERAL();
    antlr4::tree::TerminalNode* INTEGER_LITERAL(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Datetime_value_coreContext* datetime_value_core();

  class  Macro_valueContext : public antlr4::ParserRuleContext {
  public:
    Macro_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
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
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Func_ptrContext* func_ptr();

  class  Bool_valueContext : public antlr4::ParserRuleContext {
  public:
    Bool_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Bool_valueContext() = default;
    void copyFrom(Bool_valueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BoolValueTrueContext : public Bool_valueContext {
  public:
    BoolValueTrueContext(Bool_valueContext *ctx);

    antlr4::Token *bval = nullptr;
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BoolValueFalseContext : public Bool_valueContext {
  public:
    BoolValueFalseContext(Bool_valueContext *ctx);

    antlr4::Token *bval = nullptr;
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Bool_valueContext* bool_value();

  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    NumberContext() = default;
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
