
// Generated from /mnt/d/Project/OpenELanguage/Compiler/opene_compiler/openeLang.g4 by ANTLR 4.7.2


#include "openeLangListener.h"
#include "openeLangVisitor.h"

#include "openeLangParser.h"


using namespace antlrcpp;
using namespace opene;
using namespace antlr4;

openeLangParser::openeLangParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

openeLangParser::~openeLangParser() {
  delete _interpreter;
}

std::string openeLangParser::getGrammarFileName() const {
  return "openeLang.g4";
}

const std::vector<std::string>& openeLangParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& openeLangParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- Opene_srcContext ------------------------------------------------------------------

openeLangParser::Opene_srcContext::Opene_srcContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeLangParser::Edition_specContext* openeLangParser::Opene_srcContext::edition_spec() {
  return getRuleContext<openeLangParser::Edition_specContext>(0);
}

tree::TerminalNode* openeLangParser::Opene_srcContext::NEWLINE() {
  return getToken(openeLangParser::NEWLINE, 0);
}

openeLangParser::Src_contentContext* openeLangParser::Opene_srcContext::src_content() {
  return getRuleContext<openeLangParser::Src_contentContext>(0);
}

tree::TerminalNode* openeLangParser::Opene_srcContext::EOF() {
  return getToken(openeLangParser::EOF, 0);
}


size_t openeLangParser::Opene_srcContext::getRuleIndex() const {
  return openeLangParser::RuleOpene_src;
}

void openeLangParser::Opene_srcContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOpene_src(this);
}

void openeLangParser::Opene_srcContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOpene_src(this);
}


antlrcpp::Any openeLangParser::Opene_srcContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitOpene_src(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Opene_srcContext* openeLangParser::opene_src() {
  Opene_srcContext *_localctx = _tracker.createInstance<Opene_srcContext>(_ctx, getState());
  enterRule(_localctx, 0, openeLangParser::RuleOpene_src);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(72);
    edition_spec();
    setState(73);
    match(openeLangParser::NEWLINE);
    setState(74);
    src_content();
    setState(75);
    match(openeLangParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Src_contentContext ------------------------------------------------------------------

openeLangParser::Src_contentContext::Src_contentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeLangParser::Program_set_fileContext* openeLangParser::Src_contentContext::program_set_file() {
  return getRuleContext<openeLangParser::Program_set_fileContext>(0);
}

openeLangParser::Data_structure_fileContext* openeLangParser::Src_contentContext::data_structure_file() {
  return getRuleContext<openeLangParser::Data_structure_fileContext>(0);
}

openeLangParser::Global_variable_fileContext* openeLangParser::Src_contentContext::global_variable_file() {
  return getRuleContext<openeLangParser::Global_variable_fileContext>(0);
}

openeLangParser::Dll_define_fileContext* openeLangParser::Src_contentContext::dll_define_file() {
  return getRuleContext<openeLangParser::Dll_define_fileContext>(0);
}


size_t openeLangParser::Src_contentContext::getRuleIndex() const {
  return openeLangParser::RuleSrc_content;
}

void openeLangParser::Src_contentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSrc_content(this);
}

void openeLangParser::Src_contentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSrc_content(this);
}


antlrcpp::Any openeLangParser::Src_contentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitSrc_content(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Src_contentContext* openeLangParser::src_content() {
  Src_contentContext *_localctx = _tracker.createInstance<Src_contentContext>(_ctx, getState());
  enterRule(_localctx, 2, openeLangParser::RuleSrc_content);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(81);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(77);
      program_set_file();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(78);
      data_structure_file();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(79);
      global_variable_file();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(80);
      dll_define_file();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Program_set_fileContext ------------------------------------------------------------------

openeLangParser::Program_set_fileContext::Program_set_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeLangParser::Prog_setContext* openeLangParser::Program_set_fileContext::prog_set() {
  return getRuleContext<openeLangParser::Prog_setContext>(0);
}

std::vector<tree::TerminalNode *> openeLangParser::Program_set_fileContext::NEWLINE() {
  return getTokens(openeLangParser::NEWLINE);
}

tree::TerminalNode* openeLangParser::Program_set_fileContext::NEWLINE(size_t i) {
  return getToken(openeLangParser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> openeLangParser::Program_set_fileContext::IDENTIFIER() {
  return getTokens(openeLangParser::IDENTIFIER);
}

tree::TerminalNode* openeLangParser::Program_set_fileContext::IDENTIFIER(size_t i) {
  return getToken(openeLangParser::IDENTIFIER, i);
}


size_t openeLangParser::Program_set_fileContext::getRuleIndex() const {
  return openeLangParser::RuleProgram_set_file;
}

void openeLangParser::Program_set_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram_set_file(this);
}

void openeLangParser::Program_set_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram_set_file(this);
}


antlrcpp::Any openeLangParser::Program_set_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitProgram_set_file(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Program_set_fileContext* openeLangParser::program_set_file() {
  Program_set_fileContext *_localctx = _tracker.createInstance<Program_set_fileContext>(_ctx, getState());
  enterRule(_localctx, 4, openeLangParser::RuleProgram_set_file);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__0) {
      setState(83);
      match(openeLangParser::T__0);
      setState(84);
      dynamic_cast<Program_set_fileContext *>(_localctx)->identifierToken = match(openeLangParser::IDENTIFIER);
      dynamic_cast<Program_set_fileContext *>(_localctx)->libraries.push_back(dynamic_cast<Program_set_fileContext *>(_localctx)->identifierToken);
      setState(85);
      match(openeLangParser::NEWLINE);
      setState(90);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(91);
    prog_set();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Data_structure_fileContext ------------------------------------------------------------------

openeLangParser::Data_structure_fileContext::Data_structure_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeLangParser::Struct_declareContext *> openeLangParser::Data_structure_fileContext::struct_declare() {
  return getRuleContexts<openeLangParser::Struct_declareContext>();
}

openeLangParser::Struct_declareContext* openeLangParser::Data_structure_fileContext::struct_declare(size_t i) {
  return getRuleContext<openeLangParser::Struct_declareContext>(i);
}


size_t openeLangParser::Data_structure_fileContext::getRuleIndex() const {
  return openeLangParser::RuleData_structure_file;
}

void openeLangParser::Data_structure_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterData_structure_file(this);
}

void openeLangParser::Data_structure_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitData_structure_file(this);
}


antlrcpp::Any openeLangParser::Data_structure_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitData_structure_file(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Data_structure_fileContext* openeLangParser::data_structure_file() {
  Data_structure_fileContext *_localctx = _tracker.createInstance<Data_structure_fileContext>(_ctx, getState());
  enterRule(_localctx, 6, openeLangParser::RuleData_structure_file);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__5) {
      setState(93);
      struct_declare();
      setState(98);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Global_variable_fileContext ------------------------------------------------------------------

openeLangParser::Global_variable_fileContext::Global_variable_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeLangParser::Global_variable_listContext* openeLangParser::Global_variable_fileContext::global_variable_list() {
  return getRuleContext<openeLangParser::Global_variable_listContext>(0);
}


size_t openeLangParser::Global_variable_fileContext::getRuleIndex() const {
  return openeLangParser::RuleGlobal_variable_file;
}

void openeLangParser::Global_variable_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_variable_file(this);
}

void openeLangParser::Global_variable_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_variable_file(this);
}


antlrcpp::Any openeLangParser::Global_variable_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitGlobal_variable_file(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Global_variable_fileContext* openeLangParser::global_variable_file() {
  Global_variable_fileContext *_localctx = _tracker.createInstance<Global_variable_fileContext>(_ctx, getState());
  enterRule(_localctx, 8, openeLangParser::RuleGlobal_variable_file);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(99);
    global_variable_list();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dll_define_fileContext ------------------------------------------------------------------

openeLangParser::Dll_define_fileContext::Dll_define_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeLangParser::Dll_commandContext *> openeLangParser::Dll_define_fileContext::dll_command() {
  return getRuleContexts<openeLangParser::Dll_commandContext>();
}

openeLangParser::Dll_commandContext* openeLangParser::Dll_define_fileContext::dll_command(size_t i) {
  return getRuleContext<openeLangParser::Dll_commandContext>(i);
}


size_t openeLangParser::Dll_define_fileContext::getRuleIndex() const {
  return openeLangParser::RuleDll_define_file;
}

void openeLangParser::Dll_define_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDll_define_file(this);
}

void openeLangParser::Dll_define_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDll_define_file(this);
}


antlrcpp::Any openeLangParser::Dll_define_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitDll_define_file(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Dll_define_fileContext* openeLangParser::dll_define_file() {
  Dll_define_fileContext *_localctx = _tracker.createInstance<Dll_define_fileContext>(_ctx, getState());
  enterRule(_localctx, 10, openeLangParser::RuleDll_define_file);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(104);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__1) {
      setState(101);
      dll_command();
      setState(106);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dll_commandContext ------------------------------------------------------------------

openeLangParser::Dll_commandContext::Dll_commandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> openeLangParser::Dll_commandContext::NEWLINE() {
  return getTokens(openeLangParser::NEWLINE);
}

tree::TerminalNode* openeLangParser::Dll_commandContext::NEWLINE(size_t i) {
  return getToken(openeLangParser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> openeLangParser::Dll_commandContext::IDENTIFIER() {
  return getTokens(openeLangParser::IDENTIFIER);
}

tree::TerminalNode* openeLangParser::Dll_commandContext::IDENTIFIER(size_t i) {
  return getToken(openeLangParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> openeLangParser::Dll_commandContext::STRING_LITERAL() {
  return getTokens(openeLangParser::STRING_LITERAL);
}

tree::TerminalNode* openeLangParser::Dll_commandContext::STRING_LITERAL(size_t i) {
  return getToken(openeLangParser::STRING_LITERAL, i);
}

openeLangParser::Table_commentContext* openeLangParser::Dll_commandContext::table_comment() {
  return getRuleContext<openeLangParser::Table_commentContext>(0);
}

std::vector<openeLangParser::Parameter_declContext *> openeLangParser::Dll_commandContext::parameter_decl() {
  return getRuleContexts<openeLangParser::Parameter_declContext>();
}

openeLangParser::Parameter_declContext* openeLangParser::Dll_commandContext::parameter_decl(size_t i) {
  return getRuleContext<openeLangParser::Parameter_declContext>(i);
}


size_t openeLangParser::Dll_commandContext::getRuleIndex() const {
  return openeLangParser::RuleDll_command;
}

void openeLangParser::Dll_commandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDll_command(this);
}

void openeLangParser::Dll_commandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDll_command(this);
}


antlrcpp::Any openeLangParser::Dll_commandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitDll_command(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Dll_commandContext* openeLangParser::dll_command() {
  Dll_commandContext *_localctx = _tracker.createInstance<Dll_commandContext>(_ctx, getState());
  enterRule(_localctx, 12, openeLangParser::RuleDll_command);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(107);
    match(openeLangParser::T__1);
    setState(108);
    dynamic_cast<Dll_commandContext *>(_localctx)->name = match(openeLangParser::IDENTIFIER);
    setState(109);
    match(openeLangParser::T__2);
    setState(111);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeLangParser::IDENTIFIER) {
      setState(110);
      dynamic_cast<Dll_commandContext *>(_localctx)->type = match(openeLangParser::IDENTIFIER);
    }
    setState(113);
    match(openeLangParser::T__2);
    setState(115);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeLangParser::STRING_LITERAL) {
      setState(114);
      dynamic_cast<Dll_commandContext *>(_localctx)->file = match(openeLangParser::STRING_LITERAL);
    }
    setState(117);
    match(openeLangParser::T__2);
    setState(118);
    dynamic_cast<Dll_commandContext *>(_localctx)->cmd = match(openeLangParser::STRING_LITERAL);
    setState(121);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeLangParser::T__2) {
      setState(119);
      match(openeLangParser::T__2);
      setState(120);
      table_comment();
    }
    setState(123);
    match(openeLangParser::NEWLINE);
    setState(127);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__11) {
      setState(124);
      parameter_decl();
      setState(129);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(133);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::NEWLINE) {
      setState(130);
      match(openeLangParser::NEWLINE);
      setState(135);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Global_variable_listContext ------------------------------------------------------------------

openeLangParser::Global_variable_listContext::Global_variable_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeLangParser::Global_variable_itemContext *> openeLangParser::Global_variable_listContext::global_variable_item() {
  return getRuleContexts<openeLangParser::Global_variable_itemContext>();
}

openeLangParser::Global_variable_itemContext* openeLangParser::Global_variable_listContext::global_variable_item(size_t i) {
  return getRuleContext<openeLangParser::Global_variable_itemContext>(i);
}


size_t openeLangParser::Global_variable_listContext::getRuleIndex() const {
  return openeLangParser::RuleGlobal_variable_list;
}

void openeLangParser::Global_variable_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_variable_list(this);
}

void openeLangParser::Global_variable_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_variable_list(this);
}


antlrcpp::Any openeLangParser::Global_variable_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitGlobal_variable_list(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Global_variable_listContext* openeLangParser::global_variable_list() {
  Global_variable_listContext *_localctx = _tracker.createInstance<Global_variable_listContext>(_ctx, getState());
  enterRule(_localctx, 14, openeLangParser::RuleGlobal_variable_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__3) {
      setState(136);
      global_variable_item();
      setState(141);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Global_variable_itemContext ------------------------------------------------------------------

openeLangParser::Global_variable_itemContext::Global_variable_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeLangParser::Global_variable_itemContext::NEWLINE() {
  return getToken(openeLangParser::NEWLINE, 0);
}

std::vector<tree::TerminalNode *> openeLangParser::Global_variable_itemContext::IDENTIFIER() {
  return getTokens(openeLangParser::IDENTIFIER);
}

tree::TerminalNode* openeLangParser::Global_variable_itemContext::IDENTIFIER(size_t i) {
  return getToken(openeLangParser::IDENTIFIER, i);
}

openeLangParser::Table_commentContext* openeLangParser::Global_variable_itemContext::table_comment() {
  return getRuleContext<openeLangParser::Table_commentContext>(0);
}

tree::TerminalNode* openeLangParser::Global_variable_itemContext::STRING_LITERAL() {
  return getToken(openeLangParser::STRING_LITERAL, 0);
}


size_t openeLangParser::Global_variable_itemContext::getRuleIndex() const {
  return openeLangParser::RuleGlobal_variable_item;
}

void openeLangParser::Global_variable_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_variable_item(this);
}

void openeLangParser::Global_variable_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_variable_item(this);
}


antlrcpp::Any openeLangParser::Global_variable_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitGlobal_variable_item(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Global_variable_itemContext* openeLangParser::global_variable_item() {
  Global_variable_itemContext *_localctx = _tracker.createInstance<Global_variable_itemContext>(_ctx, getState());
  enterRule(_localctx, 16, openeLangParser::RuleGlobal_variable_item);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    match(openeLangParser::T__3);
    setState(143);
    dynamic_cast<Global_variable_itemContext *>(_localctx)->name = match(openeLangParser::IDENTIFIER);
    setState(164);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeLangParser::T__2) {
      setState(144);
      match(openeLangParser::T__2);
      setState(146);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::IDENTIFIER) {
        setState(145);
        dynamic_cast<Global_variable_itemContext *>(_localctx)->type = match(openeLangParser::IDENTIFIER);
      }
      setState(162);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__2) {
        setState(148);
        match(openeLangParser::T__2);
        setState(150);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::IDENTIFIER) {
          setState(149);
          dynamic_cast<Global_variable_itemContext *>(_localctx)->access = match(openeLangParser::IDENTIFIER);
        }
        setState(160);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::T__2) {
          setState(152);
          match(openeLangParser::T__2);
          setState(154);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == openeLangParser::STRING_LITERAL) {
            setState(153);
            dynamic_cast<Global_variable_itemContext *>(_localctx)->dimension = match(openeLangParser::STRING_LITERAL);
          }
          setState(158);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == openeLangParser::T__2) {
            setState(156);
            match(openeLangParser::T__2);
            setState(157);
            table_comment();
          }
        }
      }
    }
    setState(166);
    match(openeLangParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Edition_specContext ------------------------------------------------------------------

openeLangParser::Edition_specContext::Edition_specContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeLangParser::Edition_specContext::INTEGER_LITERAL() {
  return getToken(openeLangParser::INTEGER_LITERAL, 0);
}


size_t openeLangParser::Edition_specContext::getRuleIndex() const {
  return openeLangParser::RuleEdition_spec;
}

void openeLangParser::Edition_specContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdition_spec(this);
}

void openeLangParser::Edition_specContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdition_spec(this);
}


antlrcpp::Any openeLangParser::Edition_specContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitEdition_spec(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Edition_specContext* openeLangParser::edition_spec() {
  Edition_specContext *_localctx = _tracker.createInstance<Edition_specContext>(_ctx, getState());
  enterRule(_localctx, 18, openeLangParser::RuleEdition_spec);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(168);
    match(openeLangParser::T__4);
    setState(169);
    match(openeLangParser::INTEGER_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_declareContext ------------------------------------------------------------------

openeLangParser::Struct_declareContext::Struct_declareContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> openeLangParser::Struct_declareContext::NEWLINE() {
  return getTokens(openeLangParser::NEWLINE);
}

tree::TerminalNode* openeLangParser::Struct_declareContext::NEWLINE(size_t i) {
  return getToken(openeLangParser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> openeLangParser::Struct_declareContext::IDENTIFIER() {
  return getTokens(openeLangParser::IDENTIFIER);
}

tree::TerminalNode* openeLangParser::Struct_declareContext::IDENTIFIER(size_t i) {
  return getToken(openeLangParser::IDENTIFIER, i);
}

std::vector<openeLangParser::Member_vari_declContext *> openeLangParser::Struct_declareContext::member_vari_decl() {
  return getRuleContexts<openeLangParser::Member_vari_declContext>();
}

openeLangParser::Member_vari_declContext* openeLangParser::Struct_declareContext::member_vari_decl(size_t i) {
  return getRuleContext<openeLangParser::Member_vari_declContext>(i);
}

openeLangParser::Table_commentContext* openeLangParser::Struct_declareContext::table_comment() {
  return getRuleContext<openeLangParser::Table_commentContext>(0);
}


size_t openeLangParser::Struct_declareContext::getRuleIndex() const {
  return openeLangParser::RuleStruct_declare;
}

void openeLangParser::Struct_declareContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_declare(this);
}

void openeLangParser::Struct_declareContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_declare(this);
}


antlrcpp::Any openeLangParser::Struct_declareContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitStruct_declare(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Struct_declareContext* openeLangParser::struct_declare() {
  Struct_declareContext *_localctx = _tracker.createInstance<Struct_declareContext>(_ctx, getState());
  enterRule(_localctx, 20, openeLangParser::RuleStruct_declare);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(171);
    match(openeLangParser::T__5);
    setState(172);
    dynamic_cast<Struct_declareContext *>(_localctx)->name = match(openeLangParser::IDENTIFIER);
    setState(181);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeLangParser::T__2) {
      setState(173);
      match(openeLangParser::T__2);
      setState(175);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::IDENTIFIER) {
        setState(174);
        dynamic_cast<Struct_declareContext *>(_localctx)->access = match(openeLangParser::IDENTIFIER);
      }
      setState(179);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__2) {
        setState(177);
        match(openeLangParser::T__2);
        setState(178);
        table_comment();
      }
    }
    setState(183);
    match(openeLangParser::NEWLINE);
    setState(188);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__6) {
      setState(184);
      match(openeLangParser::T__6);
      setState(185);
      dynamic_cast<Struct_declareContext *>(_localctx)->member_vari_declContext = member_vari_decl();
      dynamic_cast<Struct_declareContext *>(_localctx)->struct_mems.push_back(dynamic_cast<Struct_declareContext *>(_localctx)->member_vari_declContext);
      setState(190);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(194);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::NEWLINE) {
      setState(191);
      match(openeLangParser::NEWLINE);
      setState(196);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Table_commentContext ------------------------------------------------------------------

openeLangParser::Table_commentContext::Table_commentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeLangParser::Table_commentContext::getRuleIndex() const {
  return openeLangParser::RuleTable_comment;
}

void openeLangParser::Table_commentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTable_comment(this);
}

void openeLangParser::Table_commentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTable_comment(this);
}


antlrcpp::Any openeLangParser::Table_commentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitTable_comment(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Table_commentContext* openeLangParser::table_comment() {
  Table_commentContext *_localctx = _tracker.createInstance<Table_commentContext>(_ctx, getState());
  enterRule(_localctx, 22, openeLangParser::RuleTable_comment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(200);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(197);
        dynamic_cast<Table_commentContext *>(_localctx)->comment = matchWildcard(); 
      }
      setState(202);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prog_setContext ------------------------------------------------------------------

openeLangParser::Prog_setContext::Prog_setContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> openeLangParser::Prog_setContext::NEWLINE() {
  return getTokens(openeLangParser::NEWLINE);
}

tree::TerminalNode* openeLangParser::Prog_setContext::NEWLINE(size_t i) {
  return getToken(openeLangParser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> openeLangParser::Prog_setContext::IDENTIFIER() {
  return getTokens(openeLangParser::IDENTIFIER);
}

tree::TerminalNode* openeLangParser::Prog_setContext::IDENTIFIER(size_t i) {
  return getToken(openeLangParser::IDENTIFIER, i);
}

std::vector<openeLangParser::File_vari_declContext *> openeLangParser::Prog_setContext::file_vari_decl() {
  return getRuleContexts<openeLangParser::File_vari_declContext>();
}

openeLangParser::File_vari_declContext* openeLangParser::Prog_setContext::file_vari_decl(size_t i) {
  return getRuleContext<openeLangParser::File_vari_declContext>(i);
}

std::vector<openeLangParser::Sub_programContext *> openeLangParser::Prog_setContext::sub_program() {
  return getRuleContexts<openeLangParser::Sub_programContext>();
}

openeLangParser::Sub_programContext* openeLangParser::Prog_setContext::sub_program(size_t i) {
  return getRuleContext<openeLangParser::Sub_programContext>(i);
}

openeLangParser::Table_commentContext* openeLangParser::Prog_setContext::table_comment() {
  return getRuleContext<openeLangParser::Table_commentContext>(0);
}


size_t openeLangParser::Prog_setContext::getRuleIndex() const {
  return openeLangParser::RuleProg_set;
}

void openeLangParser::Prog_setContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg_set(this);
}

void openeLangParser::Prog_setContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg_set(this);
}


antlrcpp::Any openeLangParser::Prog_setContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitProg_set(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Prog_setContext* openeLangParser::prog_set() {
  Prog_setContext *_localctx = _tracker.createInstance<Prog_setContext>(_ctx, getState());
  enterRule(_localctx, 24, openeLangParser::RuleProg_set);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(203);
    match(openeLangParser::T__7);
    setState(204);
    dynamic_cast<Prog_setContext *>(_localctx)->name = match(openeLangParser::IDENTIFIER);
    setState(219);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeLangParser::T__2) {
      setState(205);
      match(openeLangParser::T__2);
      setState(207);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::IDENTIFIER) {
        setState(206);
        dynamic_cast<Prog_setContext *>(_localctx)->base = match(openeLangParser::IDENTIFIER);
      }
      setState(217);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__2) {
        setState(209);
        match(openeLangParser::T__2);
        setState(211);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::IDENTIFIER) {
          setState(210);
          dynamic_cast<Prog_setContext *>(_localctx)->access = match(openeLangParser::IDENTIFIER);
        }
        setState(215);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::T__2) {
          setState(213);
          match(openeLangParser::T__2);
          setState(214);
          table_comment();
        }
      }
    }
    setState(221);
    match(openeLangParser::NEWLINE);
    setState(226);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__8) {
      setState(222);
      match(openeLangParser::T__8);
      setState(223);
      dynamic_cast<Prog_setContext *>(_localctx)->file_vari_declContext = file_vari_decl();
      dynamic_cast<Prog_setContext *>(_localctx)->prog_set_varis.push_back(dynamic_cast<Prog_setContext *>(_localctx)->file_vari_declContext);
      setState(228);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(244);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__9 || _la == openeLangParser::NEWLINE) {
      setState(232);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == openeLangParser::NEWLINE) {
        setState(229);
        match(openeLangParser::NEWLINE);
        setState(234);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(235);
      dynamic_cast<Prog_setContext *>(_localctx)->sub_programContext = sub_program();
      dynamic_cast<Prog_setContext *>(_localctx)->functions.push_back(dynamic_cast<Prog_setContext *>(_localctx)->sub_programContext);
      setState(239);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(236);
          match(openeLangParser::NEWLINE); 
        }
        setState(241);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
      }
      setState(246);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_declContext ------------------------------------------------------------------

openeLangParser::Variable_declContext::Variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeLangParser::Variable_declContext::NEWLINE() {
  return getToken(openeLangParser::NEWLINE, 0);
}

std::vector<tree::TerminalNode *> openeLangParser::Variable_declContext::IDENTIFIER() {
  return getTokens(openeLangParser::IDENTIFIER);
}

tree::TerminalNode* openeLangParser::Variable_declContext::IDENTIFIER(size_t i) {
  return getToken(openeLangParser::IDENTIFIER, i);
}

openeLangParser::Table_commentContext* openeLangParser::Variable_declContext::table_comment() {
  return getRuleContext<openeLangParser::Table_commentContext>(0);
}

tree::TerminalNode* openeLangParser::Variable_declContext::STRING_LITERAL() {
  return getToken(openeLangParser::STRING_LITERAL, 0);
}


size_t openeLangParser::Variable_declContext::getRuleIndex() const {
  return openeLangParser::RuleVariable_decl;
}

void openeLangParser::Variable_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable_decl(this);
}

void openeLangParser::Variable_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable_decl(this);
}


antlrcpp::Any openeLangParser::Variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitVariable_decl(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Variable_declContext* openeLangParser::variable_decl() {
  Variable_declContext *_localctx = _tracker.createInstance<Variable_declContext>(_ctx, getState());
  enterRule(_localctx, 26, openeLangParser::RuleVariable_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(247);
    dynamic_cast<Variable_declContext *>(_localctx)->name = match(openeLangParser::IDENTIFIER);
    setState(263);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeLangParser::T__2) {
      setState(248);
      match(openeLangParser::T__2);
      setState(250);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::IDENTIFIER) {
        setState(249);
        dynamic_cast<Variable_declContext *>(_localctx)->type = match(openeLangParser::IDENTIFIER);
      }
      setState(261);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__2) {
        setState(252);
        match(openeLangParser::T__2);
        setState(253);
        match(openeLangParser::T__2);
        setState(255);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::STRING_LITERAL) {
          setState(254);
          dynamic_cast<Variable_declContext *>(_localctx)->dimension = match(openeLangParser::STRING_LITERAL);
        }
        setState(259);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::T__2) {
          setState(257);
          match(openeLangParser::T__2);
          setState(258);
          table_comment();
        }
      }
    }
    setState(265);
    match(openeLangParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Member_vari_declContext ------------------------------------------------------------------

openeLangParser::Member_vari_declContext::Member_vari_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeLangParser::Variable_declContext* openeLangParser::Member_vari_declContext::variable_decl() {
  return getRuleContext<openeLangParser::Variable_declContext>(0);
}


size_t openeLangParser::Member_vari_declContext::getRuleIndex() const {
  return openeLangParser::RuleMember_vari_decl;
}

void openeLangParser::Member_vari_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMember_vari_decl(this);
}

void openeLangParser::Member_vari_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMember_vari_decl(this);
}


antlrcpp::Any openeLangParser::Member_vari_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitMember_vari_decl(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Member_vari_declContext* openeLangParser::member_vari_decl() {
  Member_vari_declContext *_localctx = _tracker.createInstance<Member_vari_declContext>(_ctx, getState());
  enterRule(_localctx, 28, openeLangParser::RuleMember_vari_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(267);
    variable_decl();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- File_vari_declContext ------------------------------------------------------------------

openeLangParser::File_vari_declContext::File_vari_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeLangParser::Variable_declContext* openeLangParser::File_vari_declContext::variable_decl() {
  return getRuleContext<openeLangParser::Variable_declContext>(0);
}


size_t openeLangParser::File_vari_declContext::getRuleIndex() const {
  return openeLangParser::RuleFile_vari_decl;
}

void openeLangParser::File_vari_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile_vari_decl(this);
}

void openeLangParser::File_vari_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile_vari_decl(this);
}


antlrcpp::Any openeLangParser::File_vari_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitFile_vari_decl(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::File_vari_declContext* openeLangParser::file_vari_decl() {
  File_vari_declContext *_localctx = _tracker.createInstance<File_vari_declContext>(_ctx, getState());
  enterRule(_localctx, 30, openeLangParser::RuleFile_vari_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(269);
    variable_decl();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sub_programContext ------------------------------------------------------------------

openeLangParser::Sub_programContext::Sub_programContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeLangParser::Sub_programContext::NEWLINE() {
  return getToken(openeLangParser::NEWLINE, 0);
}

openeLangParser::Statement_listContext* openeLangParser::Sub_programContext::statement_list() {
  return getRuleContext<openeLangParser::Statement_listContext>(0);
}

std::vector<tree::TerminalNode *> openeLangParser::Sub_programContext::IDENTIFIER() {
  return getTokens(openeLangParser::IDENTIFIER);
}

tree::TerminalNode* openeLangParser::Sub_programContext::IDENTIFIER(size_t i) {
  return getToken(openeLangParser::IDENTIFIER, i);
}

std::vector<openeLangParser::Parameter_declContext *> openeLangParser::Sub_programContext::parameter_decl() {
  return getRuleContexts<openeLangParser::Parameter_declContext>();
}

openeLangParser::Parameter_declContext* openeLangParser::Sub_programContext::parameter_decl(size_t i) {
  return getRuleContext<openeLangParser::Parameter_declContext>(i);
}

std::vector<openeLangParser::Local_variable_declContext *> openeLangParser::Sub_programContext::local_variable_decl() {
  return getRuleContexts<openeLangParser::Local_variable_declContext>();
}

openeLangParser::Local_variable_declContext* openeLangParser::Sub_programContext::local_variable_decl(size_t i) {
  return getRuleContext<openeLangParser::Local_variable_declContext>(i);
}

openeLangParser::Table_commentContext* openeLangParser::Sub_programContext::table_comment() {
  return getRuleContext<openeLangParser::Table_commentContext>(0);
}


size_t openeLangParser::Sub_programContext::getRuleIndex() const {
  return openeLangParser::RuleSub_program;
}

void openeLangParser::Sub_programContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSub_program(this);
}

void openeLangParser::Sub_programContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSub_program(this);
}


antlrcpp::Any openeLangParser::Sub_programContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitSub_program(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Sub_programContext* openeLangParser::sub_program() {
  Sub_programContext *_localctx = _tracker.createInstance<Sub_programContext>(_ctx, getState());
  enterRule(_localctx, 32, openeLangParser::RuleSub_program);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(271);
    match(openeLangParser::T__9);
    setState(272);
    dynamic_cast<Sub_programContext *>(_localctx)->name = match(openeLangParser::IDENTIFIER);
    setState(287);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeLangParser::T__2) {
      setState(273);
      match(openeLangParser::T__2);
      setState(275);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::IDENTIFIER) {
        setState(274);
        dynamic_cast<Sub_programContext *>(_localctx)->type = match(openeLangParser::IDENTIFIER);
      }
      setState(285);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__2) {
        setState(277);
        match(openeLangParser::T__2);
        setState(279);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::IDENTIFIER) {
          setState(278);
          dynamic_cast<Sub_programContext *>(_localctx)->access = match(openeLangParser::IDENTIFIER);
        }
        setState(283);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::T__2) {
          setState(281);
          match(openeLangParser::T__2);
          setState(282);
          table_comment();
        }
      }
    }
    setState(289);
    match(openeLangParser::NEWLINE);
    setState(293);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__11) {
      setState(290);
      dynamic_cast<Sub_programContext *>(_localctx)->parameter_declContext = parameter_decl();
      dynamic_cast<Sub_programContext *>(_localctx)->params.push_back(dynamic_cast<Sub_programContext *>(_localctx)->parameter_declContext);
      setState(295);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(299);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__10) {
      setState(296);
      dynamic_cast<Sub_programContext *>(_localctx)->local_variable_declContext = local_variable_decl();
      dynamic_cast<Sub_programContext *>(_localctx)->local_vari.push_back(dynamic_cast<Sub_programContext *>(_localctx)->local_variable_declContext);
      setState(301);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(302);
    statement_list();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Local_variable_declContext ------------------------------------------------------------------

openeLangParser::Local_variable_declContext::Local_variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeLangParser::Local_variable_declContext::NEWLINE() {
  return getToken(openeLangParser::NEWLINE, 0);
}

std::vector<tree::TerminalNode *> openeLangParser::Local_variable_declContext::IDENTIFIER() {
  return getTokens(openeLangParser::IDENTIFIER);
}

tree::TerminalNode* openeLangParser::Local_variable_declContext::IDENTIFIER(size_t i) {
  return getToken(openeLangParser::IDENTIFIER, i);
}

openeLangParser::Table_commentContext* openeLangParser::Local_variable_declContext::table_comment() {
  return getRuleContext<openeLangParser::Table_commentContext>(0);
}

tree::TerminalNode* openeLangParser::Local_variable_declContext::STRING_LITERAL() {
  return getToken(openeLangParser::STRING_LITERAL, 0);
}


size_t openeLangParser::Local_variable_declContext::getRuleIndex() const {
  return openeLangParser::RuleLocal_variable_decl;
}

void openeLangParser::Local_variable_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocal_variable_decl(this);
}

void openeLangParser::Local_variable_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocal_variable_decl(this);
}


antlrcpp::Any openeLangParser::Local_variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitLocal_variable_decl(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Local_variable_declContext* openeLangParser::local_variable_decl() {
  Local_variable_declContext *_localctx = _tracker.createInstance<Local_variable_declContext>(_ctx, getState());
  enterRule(_localctx, 34, openeLangParser::RuleLocal_variable_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(304);
    match(openeLangParser::T__10);
    setState(305);
    dynamic_cast<Local_variable_declContext *>(_localctx)->name = match(openeLangParser::IDENTIFIER);
    setState(326);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeLangParser::T__2) {
      setState(306);
      match(openeLangParser::T__2);
      setState(308);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::IDENTIFIER) {
        setState(307);
        dynamic_cast<Local_variable_declContext *>(_localctx)->type = match(openeLangParser::IDENTIFIER);
      }
      setState(324);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__2) {
        setState(310);
        match(openeLangParser::T__2);
        setState(312);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::IDENTIFIER) {
          setState(311);
          dynamic_cast<Local_variable_declContext *>(_localctx)->attribute = match(openeLangParser::IDENTIFIER);
        }
        setState(322);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::T__2) {
          setState(314);
          match(openeLangParser::T__2);
          setState(316);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == openeLangParser::STRING_LITERAL) {
            setState(315);
            dynamic_cast<Local_variable_declContext *>(_localctx)->dimension = match(openeLangParser::STRING_LITERAL);
          }
          setState(320);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == openeLangParser::T__2) {
            setState(318);
            match(openeLangParser::T__2);
            setState(319);
            table_comment();
          }
        }
      }
    }
    setState(328);
    match(openeLangParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Parameter_declContext ------------------------------------------------------------------

openeLangParser::Parameter_declContext::Parameter_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeLangParser::Parameter_declContext::NEWLINE() {
  return getToken(openeLangParser::NEWLINE, 0);
}

std::vector<tree::TerminalNode *> openeLangParser::Parameter_declContext::IDENTIFIER() {
  return getTokens(openeLangParser::IDENTIFIER);
}

tree::TerminalNode* openeLangParser::Parameter_declContext::IDENTIFIER(size_t i) {
  return getToken(openeLangParser::IDENTIFIER, i);
}

openeLangParser::Table_commentContext* openeLangParser::Parameter_declContext::table_comment() {
  return getRuleContext<openeLangParser::Table_commentContext>(0);
}


size_t openeLangParser::Parameter_declContext::getRuleIndex() const {
  return openeLangParser::RuleParameter_decl;
}

void openeLangParser::Parameter_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter_decl(this);
}

void openeLangParser::Parameter_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter_decl(this);
}


antlrcpp::Any openeLangParser::Parameter_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitParameter_decl(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Parameter_declContext* openeLangParser::parameter_decl() {
  Parameter_declContext *_localctx = _tracker.createInstance<Parameter_declContext>(_ctx, getState());
  enterRule(_localctx, 36, openeLangParser::RuleParameter_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(330);
    match(openeLangParser::T__11);
    setState(331);
    dynamic_cast<Parameter_declContext *>(_localctx)->name = match(openeLangParser::IDENTIFIER);
    setState(332);
    match(openeLangParser::T__2);
    setState(333);
    dynamic_cast<Parameter_declContext *>(_localctx)->type = match(openeLangParser::IDENTIFIER);
    setState(345);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeLangParser::T__2) {
      setState(334);
      match(openeLangParser::T__2);
      setState(338);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == openeLangParser::IDENTIFIER) {
        setState(335);
        dynamic_cast<Parameter_declContext *>(_localctx)->identifierToken = match(openeLangParser::IDENTIFIER);
        dynamic_cast<Parameter_declContext *>(_localctx)->attributes.push_back(dynamic_cast<Parameter_declContext *>(_localctx)->identifierToken);
        setState(340);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(343);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__2) {
        setState(341);
        match(openeLangParser::T__2);
        setState(342);
        table_comment();
      }
    }
    setState(347);
    match(openeLangParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Statement_listContext ------------------------------------------------------------------

openeLangParser::Statement_listContext::Statement_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> openeLangParser::Statement_listContext::NEWLINE() {
  return getTokens(openeLangParser::NEWLINE);
}

tree::TerminalNode* openeLangParser::Statement_listContext::NEWLINE(size_t i) {
  return getToken(openeLangParser::NEWLINE, i);
}

std::vector<openeLangParser::StatementContext *> openeLangParser::Statement_listContext::statement() {
  return getRuleContexts<openeLangParser::StatementContext>();
}

openeLangParser::StatementContext* openeLangParser::Statement_listContext::statement(size_t i) {
  return getRuleContext<openeLangParser::StatementContext>(i);
}


size_t openeLangParser::Statement_listContext::getRuleIndex() const {
  return openeLangParser::RuleStatement_list;
}

void openeLangParser::Statement_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement_list(this);
}

void openeLangParser::Statement_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement_list(this);
}


antlrcpp::Any openeLangParser::Statement_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitStatement_list(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Statement_listContext* openeLangParser::statement_list() {
  Statement_listContext *_localctx = _tracker.createInstance<Statement_listContext>(_ctx, getState());
  enterRule(_localctx, 38, openeLangParser::RuleStatement_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(355);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(350);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 13) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 13)) & ((1ULL << (openeLangParser::T__12 - 13))
          | (1ULL << (openeLangParser::T__13 - 13))
          | (1ULL << (openeLangParser::T__18 - 13))
          | (1ULL << (openeLangParser::T__20 - 13))
          | (1ULL << (openeLangParser::T__22 - 13))
          | (1ULL << (openeLangParser::T__24 - 13))
          | (1ULL << (openeLangParser::T__26 - 13))
          | (1ULL << (openeLangParser::T__29 - 13))
          | (1ULL << (openeLangParser::T__31 - 13))
          | (1ULL << (openeLangParser::T__32 - 13))
          | (1ULL << (openeLangParser::T__33 - 13))
          | (1ULL << (openeLangParser::T__34 - 13))
          | (1ULL << (openeLangParser::T__36 - 13))
          | (1ULL << (openeLangParser::T__38 - 13))
          | (1ULL << (openeLangParser::T__49 - 13))
          | (1ULL << (openeLangParser::T__50 - 13))
          | (1ULL << (openeLangParser::T__51 - 13))
          | (1ULL << (openeLangParser::T__52 - 13))
          | (1ULL << (openeLangParser::K_SUB_OPT - 13))
          | (1ULL << (openeLangParser::INTEGER_LITERAL - 13))
          | (1ULL << (openeLangParser::FLOAT_LITERAL - 13))
          | (1ULL << (openeLangParser::IDENTIFIER - 13))
          | (1ULL << (openeLangParser::STRING_LITERAL - 13)))) != 0)) {
          setState(349);
          dynamic_cast<Statement_listContext *>(_localctx)->statementContext = statement();
          dynamic_cast<Statement_listContext *>(_localctx)->stmts.push_back(dynamic_cast<Statement_listContext *>(_localctx)->statementContext);
        }
        setState(352);
        match(openeLangParser::NEWLINE); 
      }
      setState(357);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

openeLangParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeLangParser::StatementContext::getRuleIndex() const {
  return openeLangParser::RuleStatement;
}

void openeLangParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SwitchStatementContext ------------------------------------------------------------------

openeLangParser::Switch_statementContext* openeLangParser::SwitchStatementContext::switch_statement() {
  return getRuleContext<openeLangParser::Switch_statementContext>(0);
}

openeLangParser::SwitchStatementContext::SwitchStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void openeLangParser::SwitchStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitchStatement(this);
}
void openeLangParser::SwitchStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitchStatement(this);
}

antlrcpp::Any openeLangParser::SwitchStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitSwitchStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpressionStatementContext ------------------------------------------------------------------

openeLangParser::ExpressionContext* openeLangParser::ExpressionStatementContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

openeLangParser::ExpressionStatementContext::ExpressionStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void openeLangParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}
void openeLangParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}

antlrcpp::Any openeLangParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ControlStatementContext ------------------------------------------------------------------

openeLangParser::Control_statementContext* openeLangParser::ControlStatementContext::control_statement() {
  return getRuleContext<openeLangParser::Control_statementContext>(0);
}

openeLangParser::ControlStatementContext::ControlStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void openeLangParser::ControlStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterControlStatement(this);
}
void openeLangParser::ControlStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitControlStatement(this);
}

antlrcpp::Any openeLangParser::ControlStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitControlStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConditionStatementContext ------------------------------------------------------------------

openeLangParser::Condition_statementContext* openeLangParser::ConditionStatementContext::condition_statement() {
  return getRuleContext<openeLangParser::Condition_statementContext>(0);
}

openeLangParser::ConditionStatementContext::ConditionStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void openeLangParser::ConditionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionStatement(this);
}
void openeLangParser::ConditionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionStatement(this);
}

antlrcpp::Any openeLangParser::ConditionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitConditionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LoopStatementContext ------------------------------------------------------------------

openeLangParser::Loop_statementContext* openeLangParser::LoopStatementContext::loop_statement() {
  return getRuleContext<openeLangParser::Loop_statementContext>(0);
}

openeLangParser::LoopStatementContext::LoopStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void openeLangParser::LoopStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoopStatement(this);
}
void openeLangParser::LoopStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoopStatement(this);
}

antlrcpp::Any openeLangParser::LoopStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitLoopStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStatementContext ------------------------------------------------------------------

openeLangParser::Hierarchy_identifierContext* openeLangParser::AssignStatementContext::hierarchy_identifier() {
  return getRuleContext<openeLangParser::Hierarchy_identifierContext>(0);
}

openeLangParser::ExpressionContext* openeLangParser::AssignStatementContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

tree::TerminalNode* openeLangParser::AssignStatementContext::K_ASSIGN_OPT() {
  return getToken(openeLangParser::K_ASSIGN_OPT, 0);
}

tree::TerminalNode* openeLangParser::AssignStatementContext::K_AECOM_OPT() {
  return getToken(openeLangParser::K_AECOM_OPT, 0);
}

openeLangParser::AssignStatementContext::AssignStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void openeLangParser::AssignStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignStatement(this);
}
void openeLangParser::AssignStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignStatement(this);
}

antlrcpp::Any openeLangParser::AssignStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitAssignStatement(this);
  else
    return visitor->visitChildren(this);
}
openeLangParser::StatementContext* openeLangParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 40, openeLangParser::RuleStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(367);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<openeLangParser::ConditionStatementContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(358);
      condition_statement();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<openeLangParser::AssignStatementContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(359);
      hierarchy_identifier();
      setState(360);
      _la = _input->LA(1);
      if (!(_la == openeLangParser::K_AECOM_OPT

      || _la == openeLangParser::K_ASSIGN_OPT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(361);
      expression(0);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<openeLangParser::ExpressionStatementContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(363);
      expression(0);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<openeLangParser::LoopStatementContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(364);
      loop_statement();
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<openeLangParser::SwitchStatementContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(365);
      switch_statement();
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<openeLangParser::ControlStatementContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(366);
      control_statement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Switch_statementContext ------------------------------------------------------------------

openeLangParser::Switch_statementContext::Switch_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> openeLangParser::Switch_statementContext::NEWLINE() {
  return getTokens(openeLangParser::NEWLINE);
}

tree::TerminalNode* openeLangParser::Switch_statementContext::NEWLINE(size_t i) {
  return getToken(openeLangParser::NEWLINE, i);
}

std::vector<openeLangParser::ExpressionContext *> openeLangParser::Switch_statementContext::expression() {
  return getRuleContexts<openeLangParser::ExpressionContext>();
}

openeLangParser::ExpressionContext* openeLangParser::Switch_statementContext::expression(size_t i) {
  return getRuleContext<openeLangParser::ExpressionContext>(i);
}

std::vector<openeLangParser::Statement_listContext *> openeLangParser::Switch_statementContext::statement_list() {
  return getRuleContexts<openeLangParser::Statement_listContext>();
}

openeLangParser::Statement_listContext* openeLangParser::Switch_statementContext::statement_list(size_t i) {
  return getRuleContext<openeLangParser::Statement_listContext>(i);
}


size_t openeLangParser::Switch_statementContext::getRuleIndex() const {
  return openeLangParser::RuleSwitch_statement;
}

void openeLangParser::Switch_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitch_statement(this);
}

void openeLangParser::Switch_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitch_statement(this);
}


antlrcpp::Any openeLangParser::Switch_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitSwitch_statement(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Switch_statementContext* openeLangParser::switch_statement() {
  Switch_statementContext *_localctx = _tracker.createInstance<Switch_statementContext>(_ctx, getState());
  enterRule(_localctx, 42, openeLangParser::RuleSwitch_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(369);
    match(openeLangParser::T__12);
    setState(370);
    match(openeLangParser::T__13);
    setState(371);
    dynamic_cast<Switch_statementContext *>(_localctx)->major_condition_expr = expression(0);
    setState(372);
    match(openeLangParser::T__14);
    setState(373);
    match(openeLangParser::NEWLINE);
    setState(374);
    dynamic_cast<Switch_statementContext *>(_localctx)->major_cond_body = statement_list();
    setState(384);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeLangParser::T__15) {
      setState(375);
      match(openeLangParser::T__15);
      setState(376);
      match(openeLangParser::T__13);
      setState(377);
      dynamic_cast<Switch_statementContext *>(_localctx)->expressionContext = expression(0);
      dynamic_cast<Switch_statementContext *>(_localctx)->minor_condition_expr.push_back(dynamic_cast<Switch_statementContext *>(_localctx)->expressionContext);
      setState(378);
      match(openeLangParser::T__14);
      setState(379);
      match(openeLangParser::NEWLINE);
      setState(380);
      dynamic_cast<Switch_statementContext *>(_localctx)->statement_listContext = statement_list();
      dynamic_cast<Switch_statementContext *>(_localctx)->minor_cond_body.push_back(dynamic_cast<Switch_statementContext *>(_localctx)->statement_listContext);
      setState(386);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(387);
    match(openeLangParser::T__16);
    setState(388);
    match(openeLangParser::NEWLINE);
    setState(389);
    dynamic_cast<Switch_statementContext *>(_localctx)->default_body = statement_list();
    setState(390);
    match(openeLangParser::T__17);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Loop_statementContext ------------------------------------------------------------------

openeLangParser::Loop_statementContext::Loop_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeLangParser::Loop_statementContext::getRuleIndex() const {
  return openeLangParser::RuleLoop_statement;
}

void openeLangParser::Loop_statementContext::copyFrom(Loop_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RangeForContext ------------------------------------------------------------------

tree::TerminalNode* openeLangParser::RangeForContext::NEWLINE() {
  return getToken(openeLangParser::NEWLINE, 0);
}

openeLangParser::ExpressionContext* openeLangParser::RangeForContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

openeLangParser::Statement_listContext* openeLangParser::RangeForContext::statement_list() {
  return getRuleContext<openeLangParser::Statement_listContext>(0);
}

openeLangParser::Hierarchy_identifierContext* openeLangParser::RangeForContext::hierarchy_identifier() {
  return getRuleContext<openeLangParser::Hierarchy_identifierContext>(0);
}

openeLangParser::RangeForContext::RangeForContext(Loop_statementContext *ctx) { copyFrom(ctx); }

void openeLangParser::RangeForContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRangeFor(this);
}
void openeLangParser::RangeForContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRangeFor(this);
}

antlrcpp::Any openeLangParser::RangeForContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitRangeFor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForContext ------------------------------------------------------------------

tree::TerminalNode* openeLangParser::ForContext::NEWLINE() {
  return getToken(openeLangParser::NEWLINE, 0);
}

std::vector<openeLangParser::ExpressionContext *> openeLangParser::ForContext::expression() {
  return getRuleContexts<openeLangParser::ExpressionContext>();
}

openeLangParser::ExpressionContext* openeLangParser::ForContext::expression(size_t i) {
  return getRuleContext<openeLangParser::ExpressionContext>(i);
}

openeLangParser::Statement_listContext* openeLangParser::ForContext::statement_list() {
  return getRuleContext<openeLangParser::Statement_listContext>(0);
}

openeLangParser::Hierarchy_identifierContext* openeLangParser::ForContext::hierarchy_identifier() {
  return getRuleContext<openeLangParser::Hierarchy_identifierContext>(0);
}

openeLangParser::ForContext::ForContext(Loop_statementContext *ctx) { copyFrom(ctx); }

void openeLangParser::ForContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor(this);
}
void openeLangParser::ForContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor(this);
}

antlrcpp::Any openeLangParser::ForContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitFor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DoWhileContext ------------------------------------------------------------------

tree::TerminalNode* openeLangParser::DoWhileContext::NEWLINE() {
  return getToken(openeLangParser::NEWLINE, 0);
}

openeLangParser::Statement_listContext* openeLangParser::DoWhileContext::statement_list() {
  return getRuleContext<openeLangParser::Statement_listContext>(0);
}

openeLangParser::ExpressionContext* openeLangParser::DoWhileContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

openeLangParser::DoWhileContext::DoWhileContext(Loop_statementContext *ctx) { copyFrom(ctx); }

void openeLangParser::DoWhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDoWhile(this);
}
void openeLangParser::DoWhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDoWhile(this);
}

antlrcpp::Any openeLangParser::DoWhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitDoWhile(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileContext ------------------------------------------------------------------

tree::TerminalNode* openeLangParser::WhileContext::NEWLINE() {
  return getToken(openeLangParser::NEWLINE, 0);
}

openeLangParser::ExpressionContext* openeLangParser::WhileContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

openeLangParser::Statement_listContext* openeLangParser::WhileContext::statement_list() {
  return getRuleContext<openeLangParser::Statement_listContext>(0);
}

openeLangParser::WhileContext::WhileContext(Loop_statementContext *ctx) { copyFrom(ctx); }

void openeLangParser::WhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhile(this);
}
void openeLangParser::WhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhile(this);
}

antlrcpp::Any openeLangParser::WhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitWhile(this);
  else
    return visitor->visitChildren(this);
}
openeLangParser::Loop_statementContext* openeLangParser::loop_statement() {
  Loop_statementContext *_localctx = _tracker.createInstance<Loop_statementContext>(_ctx, getState());
  enterRule(_localctx, 44, openeLangParser::RuleLoop_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(444);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeLangParser::T__18: {
        _localctx = dynamic_cast<Loop_statementContext *>(_tracker.createInstance<openeLangParser::WhileContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(392);
        match(openeLangParser::T__18);
        setState(393);
        match(openeLangParser::T__13);
        setState(394);
        dynamic_cast<WhileContext *>(_localctx)->condition_expr = expression(0);
        setState(395);
        match(openeLangParser::T__14);
        setState(396);
        match(openeLangParser::NEWLINE);
        setState(397);
        dynamic_cast<WhileContext *>(_localctx)->loop_body = statement_list();
        setState(398);
        match(openeLangParser::T__19);
        setState(399);
        match(openeLangParser::T__13);
        setState(400);
        match(openeLangParser::T__14);
        break;
      }

      case openeLangParser::T__20: {
        _localctx = dynamic_cast<Loop_statementContext *>(_tracker.createInstance<openeLangParser::RangeForContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(402);
        match(openeLangParser::T__20);
        setState(403);
        match(openeLangParser::T__13);
        setState(404);
        dynamic_cast<RangeForContext *>(_localctx)->times_expr = expression(0);
        setState(405);
        match(openeLangParser::T__2);
        setState(407);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::IDENTIFIER) {
          setState(406);
          dynamic_cast<RangeForContext *>(_localctx)->loop_variable = hierarchy_identifier();
        }
        setState(409);
        match(openeLangParser::T__14);
        setState(410);
        match(openeLangParser::NEWLINE);
        setState(411);
        dynamic_cast<RangeForContext *>(_localctx)->loop_body = statement_list();
        setState(412);
        match(openeLangParser::T__21);
        setState(413);
        match(openeLangParser::T__13);
        setState(414);
        match(openeLangParser::T__14);
        break;
      }

      case openeLangParser::T__22: {
        _localctx = dynamic_cast<Loop_statementContext *>(_tracker.createInstance<openeLangParser::ForContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(416);
        match(openeLangParser::T__22);
        setState(417);
        match(openeLangParser::T__13);
        setState(418);
        dynamic_cast<ForContext *>(_localctx)->loop_start = expression(0);
        setState(419);
        match(openeLangParser::T__2);
        setState(420);
        dynamic_cast<ForContext *>(_localctx)->loop_end = expression(0);
        setState(421);
        match(openeLangParser::T__2);
        setState(422);
        dynamic_cast<ForContext *>(_localctx)->loop_step = expression(0);
        setState(425);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::T__2) {
          setState(423);
          match(openeLangParser::T__2);
          setState(424);
          dynamic_cast<ForContext *>(_localctx)->loop_variable = hierarchy_identifier();
        }
        setState(427);
        match(openeLangParser::T__14);
        setState(428);
        match(openeLangParser::NEWLINE);
        setState(429);
        dynamic_cast<ForContext *>(_localctx)->loop_body = statement_list();
        setState(430);
        match(openeLangParser::T__23);
        setState(431);
        match(openeLangParser::T__13);
        setState(432);
        match(openeLangParser::T__14);
        break;
      }

      case openeLangParser::T__24: {
        _localctx = dynamic_cast<Loop_statementContext *>(_tracker.createInstance<openeLangParser::DoWhileContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(434);
        match(openeLangParser::T__24);
        setState(435);
        match(openeLangParser::T__13);
        setState(436);
        match(openeLangParser::T__14);
        setState(437);
        match(openeLangParser::NEWLINE);
        setState(438);
        dynamic_cast<DoWhileContext *>(_localctx)->loop_body = statement_list();
        setState(439);
        match(openeLangParser::T__25);
        setState(440);
        match(openeLangParser::T__13);
        setState(441);
        dynamic_cast<DoWhileContext *>(_localctx)->condition_expr = expression(0);
        setState(442);
        match(openeLangParser::T__14);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Condition_statementContext ------------------------------------------------------------------

openeLangParser::Condition_statementContext::Condition_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeLangParser::Condition_statementContext::getRuleIndex() const {
  return openeLangParser::RuleCondition_statement;
}

void openeLangParser::Condition_statementContext::copyFrom(Condition_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IfStmtContext ------------------------------------------------------------------

openeLangParser::ExpressionContext* openeLangParser::IfStmtContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

std::vector<openeLangParser::Statement_listContext *> openeLangParser::IfStmtContext::statement_list() {
  return getRuleContexts<openeLangParser::Statement_listContext>();
}

openeLangParser::Statement_listContext* openeLangParser::IfStmtContext::statement_list(size_t i) {
  return getRuleContext<openeLangParser::Statement_listContext>(i);
}

openeLangParser::IfStmtContext::IfStmtContext(Condition_statementContext *ctx) { copyFrom(ctx); }

void openeLangParser::IfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStmt(this);
}
void openeLangParser::IfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStmt(this);
}

antlrcpp::Any openeLangParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfTrueStmtContext ------------------------------------------------------------------

openeLangParser::ExpressionContext* openeLangParser::IfTrueStmtContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

openeLangParser::Statement_listContext* openeLangParser::IfTrueStmtContext::statement_list() {
  return getRuleContext<openeLangParser::Statement_listContext>(0);
}

openeLangParser::IfTrueStmtContext::IfTrueStmtContext(Condition_statementContext *ctx) { copyFrom(ctx); }

void openeLangParser::IfTrueStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfTrueStmt(this);
}
void openeLangParser::IfTrueStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfTrueStmt(this);
}

antlrcpp::Any openeLangParser::IfTrueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitIfTrueStmt(this);
  else
    return visitor->visitChildren(this);
}
openeLangParser::Condition_statementContext* openeLangParser::condition_statement() {
  Condition_statementContext *_localctx = _tracker.createInstance<Condition_statementContext>(_ctx, getState());
  enterRule(_localctx, 46, openeLangParser::RuleCondition_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(464);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeLangParser::T__26: {
        _localctx = dynamic_cast<Condition_statementContext *>(_tracker.createInstance<openeLangParser::IfStmtContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(446);
        match(openeLangParser::T__26);
        setState(447);
        match(openeLangParser::T__13);
        setState(448);
        dynamic_cast<IfStmtContext *>(_localctx)->condition_expr = expression(0);
        setState(449);
        match(openeLangParser::T__14);
        setState(450);
        dynamic_cast<IfStmtContext *>(_localctx)->true_stmt_list = statement_list();
        setState(453);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeLangParser::T__27) {
          setState(451);
          match(openeLangParser::T__27);
          setState(452);
          dynamic_cast<IfStmtContext *>(_localctx)->false_stmt_list = statement_list();
        }
        setState(455);
        match(openeLangParser::T__28);
        break;
      }

      case openeLangParser::T__29: {
        _localctx = dynamic_cast<Condition_statementContext *>(_tracker.createInstance<openeLangParser::IfTrueStmtContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(457);
        match(openeLangParser::T__29);
        setState(458);
        match(openeLangParser::T__13);
        setState(459);
        dynamic_cast<IfTrueStmtContext *>(_localctx)->condition_expr = expression(0);
        setState(460);
        match(openeLangParser::T__14);
        setState(461);
        dynamic_cast<IfTrueStmtContext *>(_localctx)->true_stmt_list = statement_list();
        setState(462);
        match(openeLangParser::T__30);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Control_statementContext ------------------------------------------------------------------

openeLangParser::Control_statementContext::Control_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeLangParser::Control_statementContext::getRuleIndex() const {
  return openeLangParser::RuleControl_statement;
}

void openeLangParser::Control_statementContext::copyFrom(Control_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ContinueStmtContext ------------------------------------------------------------------

openeLangParser::ContinueStmtContext::ContinueStmtContext(Control_statementContext *ctx) { copyFrom(ctx); }

void openeLangParser::ContinueStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStmt(this);
}
void openeLangParser::ContinueStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStmt(this);
}

antlrcpp::Any openeLangParser::ContinueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitContinueStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExitStmtContext ------------------------------------------------------------------

openeLangParser::ExitStmtContext::ExitStmtContext(Control_statementContext *ctx) { copyFrom(ctx); }

void openeLangParser::ExitStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExitStmt(this);
}
void openeLangParser::ExitStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExitStmt(this);
}

antlrcpp::Any openeLangParser::ExitStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitExitStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStmtContext ------------------------------------------------------------------

openeLangParser::BreakStmtContext::BreakStmtContext(Control_statementContext *ctx) { copyFrom(ctx); }

void openeLangParser::BreakStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStmt(this);
}
void openeLangParser::BreakStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStmt(this);
}

antlrcpp::Any openeLangParser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStmtContext ------------------------------------------------------------------

openeLangParser::ExpressionContext* openeLangParser::ReturnStmtContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

openeLangParser::ReturnStmtContext::ReturnStmtContext(Control_statementContext *ctx) { copyFrom(ctx); }

void openeLangParser::ReturnStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStmt(this);
}
void openeLangParser::ReturnStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStmt(this);
}

antlrcpp::Any openeLangParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}
openeLangParser::Control_statementContext* openeLangParser::control_statement() {
  Control_statementContext *_localctx = _tracker.createInstance<Control_statementContext>(_ctx, getState());
  enterRule(_localctx, 48, openeLangParser::RuleControl_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(481);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeLangParser::T__31: {
        _localctx = dynamic_cast<Control_statementContext *>(_tracker.createInstance<openeLangParser::ContinueStmtContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(466);
        match(openeLangParser::T__31);
        setState(467);
        match(openeLangParser::T__13);
        setState(468);
        match(openeLangParser::T__14);
        break;
      }

      case openeLangParser::T__32: {
        _localctx = dynamic_cast<Control_statementContext *>(_tracker.createInstance<openeLangParser::BreakStmtContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(469);
        match(openeLangParser::T__32);
        setState(470);
        match(openeLangParser::T__13);
        setState(471);
        match(openeLangParser::T__14);
        break;
      }

      case openeLangParser::T__33: {
        _localctx = dynamic_cast<Control_statementContext *>(_tracker.createInstance<openeLangParser::ReturnStmtContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(472);
        match(openeLangParser::T__33);
        setState(473);
        match(openeLangParser::T__13);
        setState(475);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 14) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 14)) & ((1ULL << (openeLangParser::T__13 - 14))
          | (1ULL << (openeLangParser::T__36 - 14))
          | (1ULL << (openeLangParser::T__38 - 14))
          | (1ULL << (openeLangParser::T__49 - 14))
          | (1ULL << (openeLangParser::T__50 - 14))
          | (1ULL << (openeLangParser::T__51 - 14))
          | (1ULL << (openeLangParser::T__52 - 14))
          | (1ULL << (openeLangParser::K_SUB_OPT - 14))
          | (1ULL << (openeLangParser::INTEGER_LITERAL - 14))
          | (1ULL << (openeLangParser::FLOAT_LITERAL - 14))
          | (1ULL << (openeLangParser::IDENTIFIER - 14))
          | (1ULL << (openeLangParser::STRING_LITERAL - 14)))) != 0)) {
          setState(474);
          dynamic_cast<ReturnStmtContext *>(_localctx)->return_expr = expression(0);
        }
        setState(477);
        match(openeLangParser::T__14);
        break;
      }

      case openeLangParser::T__34: {
        _localctx = dynamic_cast<Control_statementContext *>(_tracker.createInstance<openeLangParser::ExitStmtContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(478);
        match(openeLangParser::T__34);
        setState(479);
        match(openeLangParser::T__13);
        setState(480);
        match(openeLangParser::T__14);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Hierarchy_identifierContext ------------------------------------------------------------------

openeLangParser::Hierarchy_identifierContext::Hierarchy_identifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeLangParser::Name_componentContext *> openeLangParser::Hierarchy_identifierContext::name_component() {
  return getRuleContexts<openeLangParser::Name_componentContext>();
}

openeLangParser::Name_componentContext* openeLangParser::Hierarchy_identifierContext::name_component(size_t i) {
  return getRuleContext<openeLangParser::Name_componentContext>(i);
}


size_t openeLangParser::Hierarchy_identifierContext::getRuleIndex() const {
  return openeLangParser::RuleHierarchy_identifier;
}

void openeLangParser::Hierarchy_identifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHierarchy_identifier(this);
}

void openeLangParser::Hierarchy_identifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHierarchy_identifier(this);
}


antlrcpp::Any openeLangParser::Hierarchy_identifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitHierarchy_identifier(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Hierarchy_identifierContext* openeLangParser::hierarchy_identifier() {
  Hierarchy_identifierContext *_localctx = _tracker.createInstance<Hierarchy_identifierContext>(_ctx, getState());
  enterRule(_localctx, 50, openeLangParser::RuleHierarchy_identifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(483);
    dynamic_cast<Hierarchy_identifierContext *>(_localctx)->name_componentContext = name_component(0);
    dynamic_cast<Hierarchy_identifierContext *>(_localctx)->components.push_back(dynamic_cast<Hierarchy_identifierContext *>(_localctx)->name_componentContext);
    setState(488);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(484);
        match(openeLangParser::T__35);
        setState(485);
        dynamic_cast<Hierarchy_identifierContext *>(_localctx)->name_componentContext = name_component(0);
        dynamic_cast<Hierarchy_identifierContext *>(_localctx)->components.push_back(dynamic_cast<Hierarchy_identifierContext *>(_localctx)->name_componentContext); 
      }
      setState(490);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Name_componentContext ------------------------------------------------------------------

openeLangParser::Name_componentContext::Name_componentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeLangParser::Name_componentContext::getRuleIndex() const {
  return openeLangParser::RuleName_component;
}

void openeLangParser::Name_componentContext::copyFrom(Name_componentContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FuncCallContext ------------------------------------------------------------------

openeLangParser::Name_componentContext* openeLangParser::FuncCallContext::name_component() {
  return getRuleContext<openeLangParser::Name_componentContext>(0);
}

std::vector<openeLangParser::ExpressionContext *> openeLangParser::FuncCallContext::expression() {
  return getRuleContexts<openeLangParser::ExpressionContext>();
}

openeLangParser::ExpressionContext* openeLangParser::FuncCallContext::expression(size_t i) {
  return getRuleContext<openeLangParser::ExpressionContext>(i);
}

openeLangParser::FuncCallContext::FuncCallContext(Name_componentContext *ctx) { copyFrom(ctx); }

void openeLangParser::FuncCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCall(this);
}
void openeLangParser::FuncCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCall(this);
}

antlrcpp::Any openeLangParser::FuncCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitFuncCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentifierContext ------------------------------------------------------------------

tree::TerminalNode* openeLangParser::IdentifierContext::IDENTIFIER() {
  return getToken(openeLangParser::IDENTIFIER, 0);
}

openeLangParser::IdentifierContext::IdentifierContext(Name_componentContext *ctx) { copyFrom(ctx); }

void openeLangParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}
void openeLangParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}

antlrcpp::Any openeLangParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayIndexContext ------------------------------------------------------------------

openeLangParser::Name_componentContext* openeLangParser::ArrayIndexContext::name_component() {
  return getRuleContext<openeLangParser::Name_componentContext>(0);
}

openeLangParser::ExpressionContext* openeLangParser::ArrayIndexContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

openeLangParser::ArrayIndexContext::ArrayIndexContext(Name_componentContext *ctx) { copyFrom(ctx); }

void openeLangParser::ArrayIndexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayIndex(this);
}
void openeLangParser::ArrayIndexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayIndex(this);
}

antlrcpp::Any openeLangParser::ArrayIndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitArrayIndex(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Name_componentContext* openeLangParser::name_component() {
   return name_component(0);
}

openeLangParser::Name_componentContext* openeLangParser::name_component(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  openeLangParser::Name_componentContext *_localctx = _tracker.createInstance<Name_componentContext>(_ctx, parentState);
  openeLangParser::Name_componentContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, openeLangParser::RuleName_component, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<IdentifierContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(492);
    match(openeLangParser::IDENTIFIER);
    _ctx->stop = _input->LT(-1);
    setState(516);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(514);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<FuncCallContext>(_tracker.createInstance<Name_componentContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleName_component);
          setState(494);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(495);
          match(openeLangParser::T__13);
          setState(497);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (((((_la - 14) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 14)) & ((1ULL << (openeLangParser::T__13 - 14))
            | (1ULL << (openeLangParser::T__36 - 14))
            | (1ULL << (openeLangParser::T__38 - 14))
            | (1ULL << (openeLangParser::T__49 - 14))
            | (1ULL << (openeLangParser::T__50 - 14))
            | (1ULL << (openeLangParser::T__51 - 14))
            | (1ULL << (openeLangParser::T__52 - 14))
            | (1ULL << (openeLangParser::K_SUB_OPT - 14))
            | (1ULL << (openeLangParser::INTEGER_LITERAL - 14))
            | (1ULL << (openeLangParser::FLOAT_LITERAL - 14))
            | (1ULL << (openeLangParser::IDENTIFIER - 14))
            | (1ULL << (openeLangParser::STRING_LITERAL - 14)))) != 0)) {
            setState(496);
            dynamic_cast<FuncCallContext *>(_localctx)->expressionContext = expression(0);
            dynamic_cast<FuncCallContext *>(_localctx)->arguments.push_back(dynamic_cast<FuncCallContext *>(_localctx)->expressionContext);
          }
          setState(505);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == openeLangParser::T__2) {
            setState(499);
            match(openeLangParser::T__2);
            setState(501);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (((((_la - 14) & ~ 0x3fULL) == 0) &&
              ((1ULL << (_la - 14)) & ((1ULL << (openeLangParser::T__13 - 14))
              | (1ULL << (openeLangParser::T__36 - 14))
              | (1ULL << (openeLangParser::T__38 - 14))
              | (1ULL << (openeLangParser::T__49 - 14))
              | (1ULL << (openeLangParser::T__50 - 14))
              | (1ULL << (openeLangParser::T__51 - 14))
              | (1ULL << (openeLangParser::T__52 - 14))
              | (1ULL << (openeLangParser::K_SUB_OPT - 14))
              | (1ULL << (openeLangParser::INTEGER_LITERAL - 14))
              | (1ULL << (openeLangParser::FLOAT_LITERAL - 14))
              | (1ULL << (openeLangParser::IDENTIFIER - 14))
              | (1ULL << (openeLangParser::STRING_LITERAL - 14)))) != 0)) {
              setState(500);
              dynamic_cast<FuncCallContext *>(_localctx)->expressionContext = expression(0);
              dynamic_cast<FuncCallContext *>(_localctx)->arguments.push_back(dynamic_cast<FuncCallContext *>(_localctx)->expressionContext);
            }
            setState(507);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(508);
          match(openeLangParser::T__14);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ArrayIndexContext>(_tracker.createInstance<Name_componentContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleName_component);
          setState(509);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(510);
          match(openeLangParser::T__36);
          setState(511);
          expression(0);
          setState(512);
          match(openeLangParser::T__37);
          break;
        }

        } 
      }
      setState(518);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

openeLangParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeLangParser::ExpressionContext::getRuleIndex() const {
  return openeLangParser::RuleExpression;
}

void openeLangParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BracketContext ------------------------------------------------------------------

openeLangParser::ExpressionContext* openeLangParser::BracketContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

openeLangParser::BracketContext::BracketContext(ExpressionContext *ctx) { copyFrom(ctx); }

void openeLangParser::BracketContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBracket(this);
}
void openeLangParser::BracketContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBracket(this);
}

antlrcpp::Any openeLangParser::BracketContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitBracket(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OptElementContext ------------------------------------------------------------------

openeLangParser::NumberContext* openeLangParser::OptElementContext::number() {
  return getRuleContext<openeLangParser::NumberContext>(0);
}

openeLangParser::Bool_valueContext* openeLangParser::OptElementContext::bool_value() {
  return getRuleContext<openeLangParser::Bool_valueContext>(0);
}

openeLangParser::Macro_valueContext* openeLangParser::OptElementContext::macro_value() {
  return getRuleContext<openeLangParser::Macro_valueContext>(0);
}

openeLangParser::String_valueContext* openeLangParser::OptElementContext::string_value() {
  return getRuleContext<openeLangParser::String_valueContext>(0);
}

openeLangParser::Hierarchy_identifierContext* openeLangParser::OptElementContext::hierarchy_identifier() {
  return getRuleContext<openeLangParser::Hierarchy_identifierContext>(0);
}

openeLangParser::Func_ptrContext* openeLangParser::OptElementContext::func_ptr() {
  return getRuleContext<openeLangParser::Func_ptrContext>(0);
}

openeLangParser::Datetime_valueContext* openeLangParser::OptElementContext::datetime_value() {
  return getRuleContext<openeLangParser::Datetime_valueContext>(0);
}

openeLangParser::Data_set_valueContext* openeLangParser::OptElementContext::data_set_value() {
  return getRuleContext<openeLangParser::Data_set_valueContext>(0);
}

openeLangParser::OptElementContext::OptElementContext(ExpressionContext *ctx) { copyFrom(ctx); }

void openeLangParser::OptElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOptElement(this);
}
void openeLangParser::OptElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOptElement(this);
}

antlrcpp::Any openeLangParser::OptElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitOptElement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryExprContext ------------------------------------------------------------------

std::vector<openeLangParser::ExpressionContext *> openeLangParser::BinaryExprContext::expression() {
  return getRuleContexts<openeLangParser::ExpressionContext>();
}

openeLangParser::ExpressionContext* openeLangParser::BinaryExprContext::expression(size_t i) {
  return getRuleContext<openeLangParser::ExpressionContext>(i);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_MUL_OPT() {
  return getToken(openeLangParser::K_MUL_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_DIV_OPT() {
  return getToken(openeLangParser::K_DIV_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_FULL_DIV_OPT() {
  return getToken(openeLangParser::K_FULL_DIV_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_MOD_OPT() {
  return getToken(openeLangParser::K_MOD_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_ADD_OPT() {
  return getToken(openeLangParser::K_ADD_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_SUB_OPT() {
  return getToken(openeLangParser::K_SUB_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_NOT_EQUAL_OPT() {
  return getToken(openeLangParser::K_NOT_EQUAL_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_EQUAL_OPT() {
  return getToken(openeLangParser::K_EQUAL_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_AECOM_OPT() {
  return getToken(openeLangParser::K_AECOM_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_LESS_OPT() {
  return getToken(openeLangParser::K_LESS_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_GREAT_OPT() {
  return getToken(openeLangParser::K_GREAT_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_LESS_EQU_OPT() {
  return getToken(openeLangParser::K_LESS_EQU_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_GREAT_EQU_OPT() {
  return getToken(openeLangParser::K_GREAT_EQU_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_LIKE_EQU_OPT() {
  return getToken(openeLangParser::K_LIKE_EQU_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_AND_OPT() {
  return getToken(openeLangParser::K_AND_OPT, 0);
}

tree::TerminalNode* openeLangParser::BinaryExprContext::K_OR_OPT() {
  return getToken(openeLangParser::K_OR_OPT, 0);
}

openeLangParser::BinaryExprContext::BinaryExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void openeLangParser::BinaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBinaryExpr(this);
}
void openeLangParser::BinaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBinaryExpr(this);
}

antlrcpp::Any openeLangParser::BinaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitBinaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprContext ------------------------------------------------------------------

openeLangParser::ExpressionContext* openeLangParser::UnaryExprContext::expression() {
  return getRuleContext<openeLangParser::ExpressionContext>(0);
}

tree::TerminalNode* openeLangParser::UnaryExprContext::K_SUB_OPT() {
  return getToken(openeLangParser::K_SUB_OPT, 0);
}

openeLangParser::UnaryExprContext::UnaryExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void openeLangParser::UnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpr(this);
}
void openeLangParser::UnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpr(this);
}

antlrcpp::Any openeLangParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::ExpressionContext* openeLangParser::expression() {
   return expression(0);
}

openeLangParser::ExpressionContext* openeLangParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  openeLangParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  openeLangParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, openeLangParser::RuleExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(534);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeLangParser::T__13: {
        _localctx = _tracker.createInstance<BracketContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(520);
        match(openeLangParser::T__13);
        setState(521);
        expression(0);
        setState(522);
        match(openeLangParser::T__14);
        break;
      }

      case openeLangParser::K_SUB_OPT: {
        _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(524);
        dynamic_cast<UnaryExprContext *>(_localctx)->opt = match(openeLangParser::K_SUB_OPT);
        setState(525);
        expression(25);
        break;
      }

      case openeLangParser::INTEGER_LITERAL:
      case openeLangParser::FLOAT_LITERAL: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(526);
        number();
        break;
      }

      case openeLangParser::T__51:
      case openeLangParser::T__52: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(527);
        bool_value();
        break;
      }

      case openeLangParser::T__49: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(528);
        macro_value();
        break;
      }

      case openeLangParser::STRING_LITERAL: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(529);
        string_value();
        break;
      }

      case openeLangParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(530);
        hierarchy_identifier();
        break;
      }

      case openeLangParser::T__50: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(531);
        func_ptr();
        break;
      }

      case openeLangParser::T__36: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(532);
        datetime_value();
        break;
      }

      case openeLangParser::T__38: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(533);
        data_set_value();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(586);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(584);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(536);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(537);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_MUL_OPT);
          setState(538);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(25);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(539);

          if (!(precpred(_ctx, 23))) throw FailedPredicateException(this, "precpred(_ctx, 23)");
          setState(540);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_DIV_OPT);
          setState(541);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(24);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(542);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(543);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_FULL_DIV_OPT);
          setState(544);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(23);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(545);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(546);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_MOD_OPT);
          setState(547);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(22);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(548);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(549);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_ADD_OPT);
          setState(550);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(21);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(551);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(552);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_SUB_OPT);
          setState(553);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(20);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(554);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(555);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_NOT_EQUAL_OPT);
          setState(556);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(19);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(557);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(558);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_EQUAL_OPT);
          setState(559);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(18);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(560);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(561);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_AECOM_OPT);
          setState(562);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(17);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(563);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(564);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_LESS_OPT);
          setState(565);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(16);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(566);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(567);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_GREAT_OPT);
          setState(568);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(15);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(569);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(570);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_LESS_EQU_OPT);
          setState(571);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(14);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(572);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(573);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_GREAT_EQU_OPT);
          setState(574);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(13);
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(575);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(576);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_LIKE_EQU_OPT);
          setState(577);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(12);
          break;
        }

        case 15: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(578);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(579);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_AND_OPT);
          setState(580);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(11);
          break;
        }

        case 16: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(581);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(582);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeLangParser::K_OR_OPT);
          setState(583);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(10);
          break;
        }

        } 
      }
      setState(588);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Data_set_valueContext ------------------------------------------------------------------

openeLangParser::Data_set_valueContext::Data_set_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeLangParser::ExpressionContext *> openeLangParser::Data_set_valueContext::expression() {
  return getRuleContexts<openeLangParser::ExpressionContext>();
}

openeLangParser::ExpressionContext* openeLangParser::Data_set_valueContext::expression(size_t i) {
  return getRuleContext<openeLangParser::ExpressionContext>(i);
}


size_t openeLangParser::Data_set_valueContext::getRuleIndex() const {
  return openeLangParser::RuleData_set_value;
}

void openeLangParser::Data_set_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterData_set_value(this);
}

void openeLangParser::Data_set_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitData_set_value(this);
}


antlrcpp::Any openeLangParser::Data_set_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitData_set_value(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Data_set_valueContext* openeLangParser::data_set_value() {
  Data_set_valueContext *_localctx = _tracker.createInstance<Data_set_valueContext>(_ctx, getState());
  enterRule(_localctx, 56, openeLangParser::RuleData_set_value);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(589);
    match(openeLangParser::T__38);
    setState(598);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 14) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 14)) & ((1ULL << (openeLangParser::T__13 - 14))
      | (1ULL << (openeLangParser::T__36 - 14))
      | (1ULL << (openeLangParser::T__38 - 14))
      | (1ULL << (openeLangParser::T__49 - 14))
      | (1ULL << (openeLangParser::T__50 - 14))
      | (1ULL << (openeLangParser::T__51 - 14))
      | (1ULL << (openeLangParser::T__52 - 14))
      | (1ULL << (openeLangParser::K_SUB_OPT - 14))
      | (1ULL << (openeLangParser::INTEGER_LITERAL - 14))
      | (1ULL << (openeLangParser::FLOAT_LITERAL - 14))
      | (1ULL << (openeLangParser::IDENTIFIER - 14))
      | (1ULL << (openeLangParser::STRING_LITERAL - 14)))) != 0)) {
      setState(590);
      dynamic_cast<Data_set_valueContext *>(_localctx)->expressionContext = expression(0);
      dynamic_cast<Data_set_valueContext *>(_localctx)->elems.push_back(dynamic_cast<Data_set_valueContext *>(_localctx)->expressionContext);
      setState(595);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == openeLangParser::T__2) {
        setState(591);
        match(openeLangParser::T__2);
        setState(592);
        dynamic_cast<Data_set_valueContext *>(_localctx)->expressionContext = expression(0);
        dynamic_cast<Data_set_valueContext *>(_localctx)->elems.push_back(dynamic_cast<Data_set_valueContext *>(_localctx)->expressionContext);
        setState(597);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(600);
    match(openeLangParser::T__39);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Datetime_valueContext ------------------------------------------------------------------

openeLangParser::Datetime_valueContext::Datetime_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeLangParser::Datetime_value_coreContext* openeLangParser::Datetime_valueContext::datetime_value_core() {
  return getRuleContext<openeLangParser::Datetime_value_coreContext>(0);
}


size_t openeLangParser::Datetime_valueContext::getRuleIndex() const {
  return openeLangParser::RuleDatetime_value;
}

void openeLangParser::Datetime_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetime_value(this);
}

void openeLangParser::Datetime_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetime_value(this);
}


antlrcpp::Any openeLangParser::Datetime_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitDatetime_value(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Datetime_valueContext* openeLangParser::datetime_value() {
  Datetime_valueContext *_localctx = _tracker.createInstance<Datetime_valueContext>(_ctx, getState());
  enterRule(_localctx, 58, openeLangParser::RuleDatetime_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(602);
    match(openeLangParser::T__36);
    setState(603);
    datetime_value_core();
    setState(604);
    match(openeLangParser::T__37);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Datetime_value_coreContext ------------------------------------------------------------------

openeLangParser::Datetime_value_coreContext::Datetime_value_coreContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeLangParser::Datetime_value_coreContext::getRuleIndex() const {
  return openeLangParser::RuleDatetime_value_core;
}

void openeLangParser::Datetime_value_coreContext::copyFrom(Datetime_value_coreContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DatetimeSeparateBySlashColonContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> openeLangParser::DatetimeSeparateBySlashColonContext::INTEGER_LITERAL() {
  return getTokens(openeLangParser::INTEGER_LITERAL);
}

tree::TerminalNode* openeLangParser::DatetimeSeparateBySlashColonContext::INTEGER_LITERAL(size_t i) {
  return getToken(openeLangParser::INTEGER_LITERAL, i);
}

openeLangParser::DatetimeSeparateBySlashColonContext::DatetimeSeparateBySlashColonContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void openeLangParser::DatetimeSeparateBySlashColonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimeSeparateBySlashColon(this);
}
void openeLangParser::DatetimeSeparateBySlashColonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimeSeparateBySlashColon(this);
}

antlrcpp::Any openeLangParser::DatetimeSeparateBySlashColonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitDatetimeSeparateBySlashColon(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimePureNumberContext ------------------------------------------------------------------

tree::TerminalNode* openeLangParser::DatetimePureNumberContext::INTEGER_LITERAL() {
  return getToken(openeLangParser::INTEGER_LITERAL, 0);
}

openeLangParser::DatetimePureNumberContext::DatetimePureNumberContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void openeLangParser::DatetimePureNumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimePureNumber(this);
}
void openeLangParser::DatetimePureNumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimePureNumber(this);
}

antlrcpp::Any openeLangParser::DatetimePureNumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitDatetimePureNumber(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimeSeparateBySlashContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> openeLangParser::DatetimeSeparateBySlashContext::INTEGER_LITERAL() {
  return getTokens(openeLangParser::INTEGER_LITERAL);
}

tree::TerminalNode* openeLangParser::DatetimeSeparateBySlashContext::INTEGER_LITERAL(size_t i) {
  return getToken(openeLangParser::INTEGER_LITERAL, i);
}

openeLangParser::DatetimeSeparateBySlashContext::DatetimeSeparateBySlashContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void openeLangParser::DatetimeSeparateBySlashContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimeSeparateBySlash(this);
}
void openeLangParser::DatetimeSeparateBySlashContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimeSeparateBySlash(this);
}

antlrcpp::Any openeLangParser::DatetimeSeparateBySlashContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitDatetimeSeparateBySlash(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimeSeparateByBarColonContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> openeLangParser::DatetimeSeparateByBarColonContext::INTEGER_LITERAL() {
  return getTokens(openeLangParser::INTEGER_LITERAL);
}

tree::TerminalNode* openeLangParser::DatetimeSeparateByBarColonContext::INTEGER_LITERAL(size_t i) {
  return getToken(openeLangParser::INTEGER_LITERAL, i);
}

openeLangParser::DatetimeSeparateByBarColonContext::DatetimeSeparateByBarColonContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void openeLangParser::DatetimeSeparateByBarColonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimeSeparateByBarColon(this);
}
void openeLangParser::DatetimeSeparateByBarColonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimeSeparateByBarColon(this);
}

antlrcpp::Any openeLangParser::DatetimeSeparateByBarColonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitDatetimeSeparateByBarColon(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimeSeparateByBarContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> openeLangParser::DatetimeSeparateByBarContext::INTEGER_LITERAL() {
  return getTokens(openeLangParser::INTEGER_LITERAL);
}

tree::TerminalNode* openeLangParser::DatetimeSeparateByBarContext::INTEGER_LITERAL(size_t i) {
  return getToken(openeLangParser::INTEGER_LITERAL, i);
}

openeLangParser::DatetimeSeparateByBarContext::DatetimeSeparateByBarContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void openeLangParser::DatetimeSeparateByBarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimeSeparateByBar(this);
}
void openeLangParser::DatetimeSeparateByBarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimeSeparateByBar(this);
}

antlrcpp::Any openeLangParser::DatetimeSeparateByBarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitDatetimeSeparateByBar(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimeSeparateByChineseContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> openeLangParser::DatetimeSeparateByChineseContext::INTEGER_LITERAL() {
  return getTokens(openeLangParser::INTEGER_LITERAL);
}

tree::TerminalNode* openeLangParser::DatetimeSeparateByChineseContext::INTEGER_LITERAL(size_t i) {
  return getToken(openeLangParser::INTEGER_LITERAL, i);
}

openeLangParser::DatetimeSeparateByChineseContext::DatetimeSeparateByChineseContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void openeLangParser::DatetimeSeparateByChineseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimeSeparateByChinese(this);
}
void openeLangParser::DatetimeSeparateByChineseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimeSeparateByChinese(this);
}

antlrcpp::Any openeLangParser::DatetimeSeparateByChineseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitDatetimeSeparateByChinese(this);
  else
    return visitor->visitChildren(this);
}
openeLangParser::Datetime_value_coreContext* openeLangParser::datetime_value_core() {
  Datetime_value_coreContext *_localctx = _tracker.createInstance<Datetime_value_coreContext>(_ctx, getState());
  enterRule(_localctx, 60, openeLangParser::RuleDatetime_value_core);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(673);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<openeLangParser::DatetimePureNumberContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(606);
      dynamic_cast<DatetimePureNumberContext *>(_localctx)->time = match(openeLangParser::INTEGER_LITERAL);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<openeLangParser::DatetimeSeparateByChineseContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(607);
      dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->year = match(openeLangParser::INTEGER_LITERAL);
      setState(608);
      match(openeLangParser::T__40);
      setState(609);
      dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->month = match(openeLangParser::INTEGER_LITERAL);
      setState(610);
      match(openeLangParser::T__41);
      setState(611);
      dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->day = match(openeLangParser::INTEGER_LITERAL);
      setState(612);
      match(openeLangParser::T__42);
      setState(619);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::INTEGER_LITERAL) {
        setState(613);
        dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->hour = match(openeLangParser::INTEGER_LITERAL);
        setState(614);
        match(openeLangParser::T__43);
        setState(615);
        dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->minute = match(openeLangParser::INTEGER_LITERAL);
        setState(616);
        match(openeLangParser::T__44);
        setState(617);
        dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->second = match(openeLangParser::INTEGER_LITERAL);
        setState(618);
        match(openeLangParser::T__45);
      }
      break;
    }

    case 3: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<openeLangParser::DatetimeSeparateBySlashContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(621);
      dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->year = match(openeLangParser::INTEGER_LITERAL);
      setState(622);
      match(openeLangParser::T__46);
      setState(623);
      dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->month = match(openeLangParser::INTEGER_LITERAL);
      setState(624);
      match(openeLangParser::T__46);
      setState(625);
      dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->day = match(openeLangParser::INTEGER_LITERAL);
      setState(632);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__46) {
        setState(626);
        match(openeLangParser::T__46);
        setState(627);
        dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->hour = match(openeLangParser::INTEGER_LITERAL);
        setState(628);
        match(openeLangParser::T__46);
        setState(629);
        dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->minute = match(openeLangParser::INTEGER_LITERAL);
        setState(630);
        match(openeLangParser::T__46);
        setState(631);
        dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->second = match(openeLangParser::INTEGER_LITERAL);
      }
      break;
    }

    case 4: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<openeLangParser::DatetimeSeparateBySlashColonContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(634);
      dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->year = match(openeLangParser::INTEGER_LITERAL);
      setState(635);
      match(openeLangParser::T__46);
      setState(636);
      dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->month = match(openeLangParser::INTEGER_LITERAL);
      setState(637);
      match(openeLangParser::T__46);
      setState(638);
      dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->day = match(openeLangParser::INTEGER_LITERAL);
      setState(645);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__46) {
        setState(639);
        match(openeLangParser::T__46);
        setState(640);
        dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->hour = match(openeLangParser::INTEGER_LITERAL);
        setState(641);
        match(openeLangParser::T__47);
        setState(642);
        dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->minute = match(openeLangParser::INTEGER_LITERAL);
        setState(643);
        match(openeLangParser::T__47);
        setState(644);
        dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->second = match(openeLangParser::INTEGER_LITERAL);
      }
      break;
    }

    case 5: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<openeLangParser::DatetimeSeparateByBarContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(647);
      dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->year = match(openeLangParser::INTEGER_LITERAL);
      setState(648);
      match(openeLangParser::T__48);
      setState(649);
      dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->month = match(openeLangParser::INTEGER_LITERAL);
      setState(650);
      match(openeLangParser::T__48);
      setState(651);
      dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->day = match(openeLangParser::INTEGER_LITERAL);
      setState(658);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__48) {
        setState(652);
        match(openeLangParser::T__48);
        setState(653);
        dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->hour = match(openeLangParser::INTEGER_LITERAL);
        setState(654);
        match(openeLangParser::T__48);
        setState(655);
        dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->minute = match(openeLangParser::INTEGER_LITERAL);
        setState(656);
        match(openeLangParser::T__48);
        setState(657);
        dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->second = match(openeLangParser::INTEGER_LITERAL);
      }
      break;
    }

    case 6: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<openeLangParser::DatetimeSeparateByBarColonContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(660);
      dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->year = match(openeLangParser::INTEGER_LITERAL);
      setState(661);
      match(openeLangParser::T__48);
      setState(662);
      dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->month = match(openeLangParser::INTEGER_LITERAL);
      setState(663);
      match(openeLangParser::T__48);
      setState(664);
      dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->day = match(openeLangParser::INTEGER_LITERAL);
      setState(671);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeLangParser::T__48) {
        setState(665);
        match(openeLangParser::T__48);
        setState(666);
        dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->hour = match(openeLangParser::INTEGER_LITERAL);
        setState(667);
        match(openeLangParser::T__47);
        setState(668);
        dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->minute = match(openeLangParser::INTEGER_LITERAL);
        setState(669);
        match(openeLangParser::T__47);
        setState(670);
        dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->second = match(openeLangParser::INTEGER_LITERAL);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Macro_valueContext ------------------------------------------------------------------

openeLangParser::Macro_valueContext::Macro_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeLangParser::Macro_valueContext::IDENTIFIER() {
  return getToken(openeLangParser::IDENTIFIER, 0);
}


size_t openeLangParser::Macro_valueContext::getRuleIndex() const {
  return openeLangParser::RuleMacro_value;
}

void openeLangParser::Macro_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMacro_value(this);
}

void openeLangParser::Macro_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMacro_value(this);
}


antlrcpp::Any openeLangParser::Macro_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitMacro_value(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Macro_valueContext* openeLangParser::macro_value() {
  Macro_valueContext *_localctx = _tracker.createInstance<Macro_valueContext>(_ctx, getState());
  enterRule(_localctx, 62, openeLangParser::RuleMacro_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(675);
    match(openeLangParser::T__49);
    setState(676);
    match(openeLangParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_ptrContext ------------------------------------------------------------------

openeLangParser::Func_ptrContext::Func_ptrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeLangParser::Func_ptrContext::IDENTIFIER() {
  return getToken(openeLangParser::IDENTIFIER, 0);
}


size_t openeLangParser::Func_ptrContext::getRuleIndex() const {
  return openeLangParser::RuleFunc_ptr;
}

void openeLangParser::Func_ptrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_ptr(this);
}

void openeLangParser::Func_ptrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_ptr(this);
}


antlrcpp::Any openeLangParser::Func_ptrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitFunc_ptr(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::Func_ptrContext* openeLangParser::func_ptr() {
  Func_ptrContext *_localctx = _tracker.createInstance<Func_ptrContext>(_ctx, getState());
  enterRule(_localctx, 64, openeLangParser::RuleFunc_ptr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(678);
    match(openeLangParser::T__50);
    setState(679);
    match(openeLangParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bool_valueContext ------------------------------------------------------------------

openeLangParser::Bool_valueContext::Bool_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeLangParser::Bool_valueContext::getRuleIndex() const {
  return openeLangParser::RuleBool_value;
}

void openeLangParser::Bool_valueContext::copyFrom(Bool_valueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BoolValueTrueContext ------------------------------------------------------------------

openeLangParser::BoolValueTrueContext::BoolValueTrueContext(Bool_valueContext *ctx) { copyFrom(ctx); }

void openeLangParser::BoolValueTrueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolValueTrue(this);
}
void openeLangParser::BoolValueTrueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolValueTrue(this);
}

antlrcpp::Any openeLangParser::BoolValueTrueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitBoolValueTrue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BoolValueFalseContext ------------------------------------------------------------------

openeLangParser::BoolValueFalseContext::BoolValueFalseContext(Bool_valueContext *ctx) { copyFrom(ctx); }

void openeLangParser::BoolValueFalseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolValueFalse(this);
}
void openeLangParser::BoolValueFalseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolValueFalse(this);
}

antlrcpp::Any openeLangParser::BoolValueFalseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitBoolValueFalse(this);
  else
    return visitor->visitChildren(this);
}
openeLangParser::Bool_valueContext* openeLangParser::bool_value() {
  Bool_valueContext *_localctx = _tracker.createInstance<Bool_valueContext>(_ctx, getState());
  enterRule(_localctx, 66, openeLangParser::RuleBool_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(683);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeLangParser::T__51: {
        _localctx = dynamic_cast<Bool_valueContext *>(_tracker.createInstance<openeLangParser::BoolValueTrueContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(681);
        dynamic_cast<BoolValueTrueContext *>(_localctx)->bval = match(openeLangParser::T__51);
        break;
      }

      case openeLangParser::T__52: {
        _localctx = dynamic_cast<Bool_valueContext *>(_tracker.createInstance<openeLangParser::BoolValueFalseContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(682);
        dynamic_cast<BoolValueFalseContext *>(_localctx)->bval = match(openeLangParser::T__52);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

openeLangParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeLangParser::NumberContext::getRuleIndex() const {
  return openeLangParser::RuleNumber;
}

void openeLangParser::NumberContext::copyFrom(NumberContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FloatContext ------------------------------------------------------------------

tree::TerminalNode* openeLangParser::FloatContext::FLOAT_LITERAL() {
  return getToken(openeLangParser::FLOAT_LITERAL, 0);
}

openeLangParser::FloatContext::FloatContext(NumberContext *ctx) { copyFrom(ctx); }

void openeLangParser::FloatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloat(this);
}
void openeLangParser::FloatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloat(this);
}

antlrcpp::Any openeLangParser::FloatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitFloat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntContext ------------------------------------------------------------------

tree::TerminalNode* openeLangParser::IntContext::INTEGER_LITERAL() {
  return getToken(openeLangParser::INTEGER_LITERAL, 0);
}

openeLangParser::IntContext::IntContext(NumberContext *ctx) { copyFrom(ctx); }

void openeLangParser::IntContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInt(this);
}
void openeLangParser::IntContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInt(this);
}

antlrcpp::Any openeLangParser::IntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitInt(this);
  else
    return visitor->visitChildren(this);
}
openeLangParser::NumberContext* openeLangParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 68, openeLangParser::RuleNumber);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(687);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeLangParser::INTEGER_LITERAL: {
        _localctx = dynamic_cast<NumberContext *>(_tracker.createInstance<openeLangParser::IntContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(685);
        match(openeLangParser::INTEGER_LITERAL);
        break;
      }

      case openeLangParser::FLOAT_LITERAL: {
        _localctx = dynamic_cast<NumberContext *>(_tracker.createInstance<openeLangParser::FloatContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(686);
        match(openeLangParser::FLOAT_LITERAL);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- String_valueContext ------------------------------------------------------------------

openeLangParser::String_valueContext::String_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeLangParser::String_valueContext::STRING_LITERAL() {
  return getToken(openeLangParser::STRING_LITERAL, 0);
}


size_t openeLangParser::String_valueContext::getRuleIndex() const {
  return openeLangParser::RuleString_value;
}

void openeLangParser::String_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterString_value(this);
}

void openeLangParser::String_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitString_value(this);
}


antlrcpp::Any openeLangParser::String_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeLangVisitor*>(visitor))
    return parserVisitor->visitString_value(this);
  else
    return visitor->visitChildren(this);
}

openeLangParser::String_valueContext* openeLangParser::string_value() {
  String_valueContext *_localctx = _tracker.createInstance<String_valueContext>(_ctx, getState());
  enterRule(_localctx, 70, openeLangParser::RuleString_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(689);
    match(openeLangParser::STRING_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool openeLangParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 26: return name_componentSempred(dynamic_cast<Name_componentContext *>(context), predicateIndex);
    case 27: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool openeLangParser::name_componentSempred(Name_componentContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool openeLangParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 24);
    case 3: return precpred(_ctx, 23);
    case 4: return precpred(_ctx, 22);
    case 5: return precpred(_ctx, 21);
    case 6: return precpred(_ctx, 20);
    case 7: return precpred(_ctx, 19);
    case 8: return precpred(_ctx, 18);
    case 9: return precpred(_ctx, 17);
    case 10: return precpred(_ctx, 16);
    case 11: return precpred(_ctx, 15);
    case 12: return precpred(_ctx, 14);
    case 13: return precpred(_ctx, 13);
    case 14: return precpred(_ctx, 12);
    case 15: return precpred(_ctx, 11);
    case 16: return precpred(_ctx, 10);
    case 17: return precpred(_ctx, 9);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> openeLangParser::_decisionToDFA;
atn::PredictionContextCache openeLangParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN openeLangParser::_atn;
std::vector<uint16_t> openeLangParser::_serializedATN;

std::vector<std::string> openeLangParser::_ruleNames = {
  "opene_src", "src_content", "program_set_file", "data_structure_file", 
  "global_variable_file", "dll_define_file", "dll_command", "global_variable_list", 
  "global_variable_item", "edition_spec", "struct_declare", "table_comment", 
  "prog_set", "variable_decl", "member_vari_decl", "file_vari_decl", "sub_program", 
  "local_variable_decl", "parameter_decl", "statement_list", "statement", 
  "switch_statement", "loop_statement", "condition_statement", "control_statement", 
  "hierarchy_identifier", "name_component", "expression", "data_set_value", 
  "datetime_value", "datetime_value_core", "macro_value", "func_ptr", "bool_value", 
  "number", "string_value"
};

std::vector<std::string> openeLangParser::_literalNames = {
  "", "'.\u652F\u6301\u5E93'", "'.DLL\u547D\u4EE4'", "','", "'.\u5168\u5C40\u53D8\u91CF'", 
  "'.\u7248\u672C'", "'.\u6570\u636E\u7C7B\u578B'", "'.\u6210\u5458'", "'.\u7A0B\u5E8F\u96C6'", 
  "'.\u7A0B\u5E8F\u96C6\u53D8\u91CF'", "'.\u5B50\u7A0B\u5E8F'", "'.\u5C40\u90E8\u53D8\u91CF'", 
  "'.\u53C2\u6570'", "'.\u5224\u65AD\u5F00\u59CB'", "'('", "')'", "'.\u5224\u65AD'", 
  "'.\u9ED8\u8BA4'", "'.\u5224\u65AD\u7ED3\u675F'", "'.\u5224\u65AD\u5FAA\u73AF\u9996'", 
  "'.\u5224\u65AD\u5FAA\u73AF\u5C3E'", "'.\u8BA1\u6B21\u5FAA\u73AF\u9996'", 
  "'.\u8BA1\u6B21\u5FAA\u73AF\u5C3E'", "'.\u53D8\u91CF\u5FAA\u73AF\u9996'", 
  "'.\u53D8\u91CF\u5FAA\u73AF\u5C3E'", "'.\u5FAA\u73AF\u5224\u65AD\u9996'", 
  "'.\u5FAA\u73AF\u5224\u65AD\u5C3E'", "'.\u5982\u679C'", "'.\u5426\u5219'", 
  "'.\u5982\u679C\u7ED3\u675F'", "'.\u5982\u679C\u771F'", "'.\u5982\u679C\u771F\u7ED3\u675F'", 
  "'\u5230\u5FAA\u73AF\u5C3E'", "'\u8DF3\u51FA\u5FAA\u73AF'", "'\u8FD4\u56DE'", 
  "'\u7ED3\u675F'", "'.'", "'['", "']'", "'{'", "'}'", "'\u5E74'", "'\u6708'", 
  "'\u65E5'", "'\u65F6'", "'\u5206'", "'\u79D2'", "'/'", "':'", "'-'", "'#'", 
  "'&'", "'\u771F'", "'\u5047'", "", "", "", "", "", "", "'\uFF1D'", "'='", 
  "'=='"
};

std::vector<std::string> openeLangParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "K_ADD_OPT", "K_SUB_OPT", "K_MUL_OPT", "K_DIV_OPT", "K_FULL_DIV_OPT", 
  "K_MOD_OPT", "K_AECOM_OPT", "K_ASSIGN_OPT", "K_EQUAL_OPT", "K_NOT_EQUAL_OPT", 
  "K_GREAT_OPT", "K_LESS_OPT", "K_GREAT_EQU_OPT", "K_LESS_EQU_OPT", "K_LIKE_EQU_OPT", 
  "K_OR_OPT", "K_AND_OPT", "INTEGER_LITERAL", "FLOAT_LITERAL", "IDENTIFIER", 
  "WHITESPACE", "NEWLINE", "STRING_LITERAL", "OTHER_CHAR"
};

dfa::Vocabulary openeLangParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> openeLangParser::_tokenNames;

openeLangParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x4f, 0x2b6, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x54, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x7, 0x4, 0x59, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x5c, 0xb, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x7, 0x5, 0x61, 0xa, 0x5, 0xc, 0x5, 0xe, 
    0x5, 0x64, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x7, 0x7, 0x69, 0xa, 
    0x7, 0xc, 0x7, 0xe, 0x7, 0x6c, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x5, 0x8, 0x72, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x76, 
    0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x7c, 0xa, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x80, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 
    0x83, 0xb, 0x8, 0x3, 0x8, 0x7, 0x8, 0x86, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 
    0x89, 0xb, 0x8, 0x3, 0x9, 0x7, 0x9, 0x8c, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 
    0x8f, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x95, 
    0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x99, 0xa, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x5, 0xa, 0x9d, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0xa1, 0xa, 
    0xa, 0x5, 0xa, 0xa3, 0xa, 0xa, 0x5, 0xa, 0xa5, 0xa, 0xa, 0x5, 0xa, 0xa7, 
    0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0xb2, 0xa, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x5, 0xc, 0xb6, 0xa, 0xc, 0x5, 0xc, 0xb8, 0xa, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x7, 0xc, 0xbd, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0xc0, 0xb, 
    0xc, 0x3, 0xc, 0x7, 0xc, 0xc3, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0xc6, 0xb, 
    0xc, 0x3, 0xd, 0x7, 0xd, 0xc9, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xcc, 0xb, 
    0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0xd2, 0xa, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0xd6, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 
    0xe, 0xda, 0xa, 0xe, 0x5, 0xe, 0xdc, 0xa, 0xe, 0x5, 0xe, 0xde, 0xa, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0xe3, 0xa, 0xe, 0xc, 0xe, 
    0xe, 0xe, 0xe6, 0xb, 0xe, 0x3, 0xe, 0x7, 0xe, 0xe9, 0xa, 0xe, 0xc, 0xe, 
    0xe, 0xe, 0xec, 0xb, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0xf0, 0xa, 0xe, 
    0xc, 0xe, 0xe, 0xe, 0xf3, 0xb, 0xe, 0x7, 0xe, 0xf5, 0xa, 0xe, 0xc, 0xe, 
    0xe, 0xe, 0xf8, 0xb, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0xfd, 
    0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x102, 0xa, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x5, 0xf, 0x106, 0xa, 0xf, 0x5, 0xf, 0x108, 0xa, 0xf, 
    0x5, 0xf, 0x10a, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 
    0x12, 0x116, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x11a, 0xa, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x11e, 0xa, 0x12, 0x5, 0x12, 
    0x120, 0xa, 0x12, 0x5, 0x12, 0x122, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x7, 0x12, 0x126, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0x129, 0xb, 0x12, 
    0x3, 0x12, 0x7, 0x12, 0x12c, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0x12f, 
    0xb, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x5, 0x13, 0x137, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 
    0x13b, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x13f, 0xa, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x143, 0xa, 0x13, 0x5, 0x13, 0x145, 
    0xa, 0x13, 0x5, 0x13, 0x147, 0xa, 0x13, 0x5, 0x13, 0x149, 0xa, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x3, 0x14, 0x7, 0x14, 0x153, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 
    0x156, 0xb, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x15a, 0xa, 0x14, 
    0x5, 0x14, 0x15c, 0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x5, 0x15, 
    0x161, 0xa, 0x15, 0x3, 0x15, 0x7, 0x15, 0x164, 0xa, 0x15, 0xc, 0x15, 
    0xe, 0x15, 0x167, 0xb, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x172, 
    0xa, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x7, 0x17, 0x181, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 0x184, 
    0xb, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x3, 0x18, 0x5, 0x18, 0x19a, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x5, 0x18, 0x1ac, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x5, 0x18, 0x1bf, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x1c8, 0xa, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x1d3, 0xa, 0x19, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 
    0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x1de, 0xa, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x1e4, 0xa, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x7, 0x1b, 0x1e9, 0xa, 0x1b, 0xc, 0x1b, 0xe, 0x1b, 0x1ec, 
    0xb, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 
    0x1c, 0x5, 0x1c, 0x1f4, 0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 
    0x1f8, 0xa, 0x1c, 0x7, 0x1c, 0x1fa, 0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 
    0x1fd, 0xb, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x7, 0x1c, 0x205, 0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 0x208, 
    0xb, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x219, 0xa, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x7, 0x1d, 0x24b, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 
    0x24e, 0xb, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 
    0x254, 0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 0x257, 0xb, 0x1e, 0x5, 0x1e, 
    0x259, 0xa, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 
    0x3, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x5, 0x20, 0x26e, 0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x5, 0x20, 0x27b, 0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x288, 0xa, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x295, 0xa, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x2a2, 
    0xa, 0x20, 0x5, 0x20, 0x2a4, 0xa, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 0x2ae, 
    0xa, 0x23, 0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x2b2, 0xa, 0x24, 0x3, 0x25, 
    0x3, 0x25, 0x3, 0x25, 0x3, 0xca, 0x4, 0x36, 0x38, 0x26, 0x2, 0x4, 0x6, 
    0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 
    0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 
    0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x2, 0x3, 0x3, 
    0x2, 0x3e, 0x3f, 0x2, 0x309, 0x2, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4, 0x53, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x8, 0x62, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0x65, 0x3, 0x2, 0x2, 0x2, 0xc, 0x6a, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x10, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x90, 0x3, 0x2, 0x2, 0x2, 0x14, 0xaa, 0x3, 0x2, 0x2, 0x2, 0x16, 0xad, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0xca, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xcd, 0x3, 
    0x2, 0x2, 0x2, 0x1c, 0xf9, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x10d, 0x3, 0x2, 
    0x2, 0x2, 0x20, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x22, 0x111, 0x3, 0x2, 0x2, 
    0x2, 0x24, 0x132, 0x3, 0x2, 0x2, 0x2, 0x26, 0x14c, 0x3, 0x2, 0x2, 0x2, 
    0x28, 0x165, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x171, 0x3, 0x2, 0x2, 0x2, 0x2c, 
    0x173, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x1be, 0x3, 0x2, 0x2, 0x2, 0x30, 0x1d2, 
    0x3, 0x2, 0x2, 0x2, 0x32, 0x1e3, 0x3, 0x2, 0x2, 0x2, 0x34, 0x1e5, 0x3, 
    0x2, 0x2, 0x2, 0x36, 0x1ed, 0x3, 0x2, 0x2, 0x2, 0x38, 0x218, 0x3, 0x2, 
    0x2, 0x2, 0x3a, 0x24f, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x25c, 0x3, 0x2, 0x2, 
    0x2, 0x3e, 0x2a3, 0x3, 0x2, 0x2, 0x2, 0x40, 0x2a5, 0x3, 0x2, 0x2, 0x2, 
    0x42, 0x2a8, 0x3, 0x2, 0x2, 0x2, 0x44, 0x2ad, 0x3, 0x2, 0x2, 0x2, 0x46, 
    0x2b1, 0x3, 0x2, 0x2, 0x2, 0x48, 0x2b3, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 
    0x5, 0x14, 0xb, 0x2, 0x4b, 0x4c, 0x7, 0x4d, 0x2, 0x2, 0x4c, 0x4d, 0x5, 
    0x4, 0x3, 0x2, 0x4d, 0x4e, 0x7, 0x2, 0x2, 0x3, 0x4e, 0x3, 0x3, 0x2, 
    0x2, 0x2, 0x4f, 0x54, 0x5, 0x6, 0x4, 0x2, 0x50, 0x54, 0x5, 0x8, 0x5, 
    0x2, 0x51, 0x54, 0x5, 0xa, 0x6, 0x2, 0x52, 0x54, 0x5, 0xc, 0x7, 0x2, 
    0x53, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x53, 0x50, 0x3, 0x2, 0x2, 0x2, 0x53, 
    0x51, 0x3, 0x2, 0x2, 0x2, 0x53, 0x52, 0x3, 0x2, 0x2, 0x2, 0x54, 0x5, 
    0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x7, 0x3, 0x2, 0x2, 0x56, 0x57, 0x7, 
    0x4b, 0x2, 0x2, 0x57, 0x59, 0x7, 0x4d, 0x2, 0x2, 0x58, 0x55, 0x3, 0x2, 
    0x2, 0x2, 0x59, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x58, 0x3, 0x2, 0x2, 
    0x2, 0x5a, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5d, 0x3, 0x2, 0x2, 0x2, 
    0x5c, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x5, 0x1a, 0xe, 0x2, 0x5e, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x61, 0x5, 0x16, 0xc, 0x2, 0x60, 0x5f, 
    0x3, 0x2, 0x2, 0x2, 0x61, 0x64, 0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 0x3, 
    0x2, 0x2, 0x2, 0x62, 0x63, 0x3, 0x2, 0x2, 0x2, 0x63, 0x9, 0x3, 0x2, 
    0x2, 0x2, 0x64, 0x62, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 0x5, 0x10, 0x9, 
    0x2, 0x66, 0xb, 0x3, 0x2, 0x2, 0x2, 0x67, 0x69, 0x5, 0xe, 0x8, 0x2, 
    0x68, 0x67, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6a, 
    0x68, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6b, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x6c, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x7, 
    0x4, 0x2, 0x2, 0x6e, 0x6f, 0x7, 0x4b, 0x2, 0x2, 0x6f, 0x71, 0x7, 0x5, 
    0x2, 0x2, 0x70, 0x72, 0x7, 0x4b, 0x2, 0x2, 0x71, 0x70, 0x3, 0x2, 0x2, 
    0x2, 0x71, 0x72, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x3, 0x2, 0x2, 0x2, 
    0x73, 0x75, 0x7, 0x5, 0x2, 0x2, 0x74, 0x76, 0x7, 0x4e, 0x2, 0x2, 0x75, 
    0x74, 0x3, 0x2, 0x2, 0x2, 0x75, 0x76, 0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 
    0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 0x7, 0x5, 0x2, 0x2, 0x78, 0x7b, 0x7, 
    0x4e, 0x2, 0x2, 0x79, 0x7a, 0x7, 0x5, 0x2, 0x2, 0x7a, 0x7c, 0x5, 0x18, 
    0xd, 0x2, 0x7b, 0x79, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7c, 0x3, 0x2, 0x2, 
    0x2, 0x7c, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x81, 0x7, 0x4d, 0x2, 0x2, 
    0x7e, 0x80, 0x5, 0x26, 0x14, 0x2, 0x7f, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x80, 
    0x83, 0x3, 0x2, 0x2, 0x2, 0x81, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 
    0x3, 0x2, 0x2, 0x2, 0x82, 0x87, 0x3, 0x2, 0x2, 0x2, 0x83, 0x81, 0x3, 
    0x2, 0x2, 0x2, 0x84, 0x86, 0x7, 0x4d, 0x2, 0x2, 0x85, 0x84, 0x3, 0x2, 
    0x2, 0x2, 0x86, 0x89, 0x3, 0x2, 0x2, 0x2, 0x87, 0x85, 0x3, 0x2, 0x2, 
    0x2, 0x87, 0x88, 0x3, 0x2, 0x2, 0x2, 0x88, 0xf, 0x3, 0x2, 0x2, 0x2, 
    0x89, 0x87, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8c, 0x5, 0x12, 0xa, 0x2, 0x8b, 
    0x8a, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8b, 
    0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x11, 0x3, 
    0x2, 0x2, 0x2, 0x8f, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x7, 0x6, 
    0x2, 0x2, 0x91, 0xa6, 0x7, 0x4b, 0x2, 0x2, 0x92, 0x94, 0x7, 0x5, 0x2, 
    0x2, 0x93, 0x95, 0x7, 0x4b, 0x2, 0x2, 0x94, 0x93, 0x3, 0x2, 0x2, 0x2, 
    0x94, 0x95, 0x3, 0x2, 0x2, 0x2, 0x95, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x96, 
    0x98, 0x7, 0x5, 0x2, 0x2, 0x97, 0x99, 0x7, 0x4b, 0x2, 0x2, 0x98, 0x97, 
    0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x3, 0x2, 0x2, 0x2, 0x99, 0xa2, 0x3, 
    0x2, 0x2, 0x2, 0x9a, 0x9c, 0x7, 0x5, 0x2, 0x2, 0x9b, 0x9d, 0x7, 0x4e, 
    0x2, 0x2, 0x9c, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x3, 0x2, 0x2, 
    0x2, 0x9d, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x5, 0x2, 0x2, 
    0x9f, 0xa1, 0x5, 0x18, 0xd, 0x2, 0xa0, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa0, 
    0xa1, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa2, 0x9a, 
    0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa5, 0x3, 
    0x2, 0x2, 0x2, 0xa4, 0x96, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa5, 0x3, 0x2, 
    0x2, 0x2, 0xa5, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa6, 0x92, 0x3, 0x2, 0x2, 
    0x2, 0xa6, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa8, 0x3, 0x2, 0x2, 0x2, 
    0xa8, 0xa9, 0x7, 0x4d, 0x2, 0x2, 0xa9, 0x13, 0x3, 0x2, 0x2, 0x2, 0xaa, 
    0xab, 0x7, 0x7, 0x2, 0x2, 0xab, 0xac, 0x7, 0x49, 0x2, 0x2, 0xac, 0x15, 
    0x3, 0x2, 0x2, 0x2, 0xad, 0xae, 0x7, 0x8, 0x2, 0x2, 0xae, 0xb7, 0x7, 
    0x4b, 0x2, 0x2, 0xaf, 0xb1, 0x7, 0x5, 0x2, 0x2, 0xb0, 0xb2, 0x7, 0x4b, 
    0x2, 0x2, 0xb1, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb2, 0x3, 0x2, 0x2, 
    0x2, 0xb2, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb4, 0x7, 0x5, 0x2, 0x2, 
    0xb4, 0xb6, 0x5, 0x18, 0xd, 0x2, 0xb5, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb5, 
    0xb6, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xaf, 
    0x3, 0x2, 0x2, 0x2, 0xb7, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb9, 0x3, 
    0x2, 0x2, 0x2, 0xb9, 0xbe, 0x7, 0x4d, 0x2, 0x2, 0xba, 0xbb, 0x7, 0x9, 
    0x2, 0x2, 0xbb, 0xbd, 0x5, 0x1e, 0x10, 0x2, 0xbc, 0xba, 0x3, 0x2, 0x2, 
    0x2, 0xbd, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbc, 0x3, 0x2, 0x2, 0x2, 
    0xbe, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xc0, 
    0xbe, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc3, 0x7, 0x4d, 0x2, 0x2, 0xc2, 0xc1, 
    0x3, 0x2, 0x2, 0x2, 0xc3, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc2, 0x3, 
    0x2, 0x2, 0x2, 0xc4, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc5, 0x17, 0x3, 0x2, 
    0x2, 0x2, 0xc6, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc9, 0xb, 0x2, 0x2, 
    0x2, 0xc8, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xcc, 0x3, 0x2, 0x2, 0x2, 
    0xca, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xca, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xcb, 
    0x19, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xca, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 
    0x7, 0xa, 0x2, 0x2, 0xce, 0xdd, 0x7, 0x4b, 0x2, 0x2, 0xcf, 0xd1, 0x7, 
    0x5, 0x2, 0x2, 0xd0, 0xd2, 0x7, 0x4b, 0x2, 0x2, 0xd1, 0xd0, 0x3, 0x2, 
    0x2, 0x2, 0xd1, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xdb, 0x3, 0x2, 0x2, 
    0x2, 0xd3, 0xd5, 0x7, 0x5, 0x2, 0x2, 0xd4, 0xd6, 0x7, 0x4b, 0x2, 0x2, 
    0xd5, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd6, 
    0xd9, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd8, 0x7, 0x5, 0x2, 0x2, 0xd8, 0xda, 
    0x5, 0x18, 0xd, 0x2, 0xd9, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x3, 
    0x2, 0x2, 0x2, 0xda, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xd3, 0x3, 0x2, 
    0x2, 0x2, 0xdb, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xde, 0x3, 0x2, 0x2, 
    0x2, 0xdd, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xde, 0x3, 0x2, 0x2, 0x2, 
    0xde, 0xdf, 0x3, 0x2, 0x2, 0x2, 0xdf, 0xe4, 0x7, 0x4d, 0x2, 0x2, 0xe0, 
    0xe1, 0x7, 0xb, 0x2, 0x2, 0xe1, 0xe3, 0x5, 0x20, 0x11, 0x2, 0xe2, 0xe0, 
    0x3, 0x2, 0x2, 0x2, 0xe3, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe2, 0x3, 
    0x2, 0x2, 0x2, 0xe4, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xf6, 0x3, 0x2, 
    0x2, 0x2, 0xe6, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe9, 0x7, 0x4d, 0x2, 
    0x2, 0xe8, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xec, 0x3, 0x2, 0x2, 0x2, 
    0xea, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xea, 0xeb, 0x3, 0x2, 0x2, 0x2, 0xeb, 
    0xed, 0x3, 0x2, 0x2, 0x2, 0xec, 0xea, 0x3, 0x2, 0x2, 0x2, 0xed, 0xf1, 
    0x5, 0x22, 0x12, 0x2, 0xee, 0xf0, 0x7, 0x4d, 0x2, 0x2, 0xef, 0xee, 0x3, 
    0x2, 0x2, 0x2, 0xf0, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xef, 0x3, 0x2, 
    0x2, 0x2, 0xf1, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf5, 0x3, 0x2, 0x2, 
    0x2, 0xf3, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xea, 0x3, 0x2, 0x2, 0x2, 
    0xf5, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xf6, 
    0xf7, 0x3, 0x2, 0x2, 0x2, 0xf7, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf6, 
    0x3, 0x2, 0x2, 0x2, 0xf9, 0x109, 0x7, 0x4b, 0x2, 0x2, 0xfa, 0xfc, 0x7, 
    0x5, 0x2, 0x2, 0xfb, 0xfd, 0x7, 0x4b, 0x2, 0x2, 0xfc, 0xfb, 0x3, 0x2, 
    0x2, 0x2, 0xfc, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xfd, 0x107, 0x3, 0x2, 0x2, 
    0x2, 0xfe, 0xff, 0x7, 0x5, 0x2, 0x2, 0xff, 0x101, 0x7, 0x5, 0x2, 0x2, 
    0x100, 0x102, 0x7, 0x4e, 0x2, 0x2, 0x101, 0x100, 0x3, 0x2, 0x2, 0x2, 
    0x101, 0x102, 0x3, 0x2, 0x2, 0x2, 0x102, 0x105, 0x3, 0x2, 0x2, 0x2, 
    0x103, 0x104, 0x7, 0x5, 0x2, 0x2, 0x104, 0x106, 0x5, 0x18, 0xd, 0x2, 
    0x105, 0x103, 0x3, 0x2, 0x2, 0x2, 0x105, 0x106, 0x3, 0x2, 0x2, 0x2, 
    0x106, 0x108, 0x3, 0x2, 0x2, 0x2, 0x107, 0xfe, 0x3, 0x2, 0x2, 0x2, 0x107, 
    0x108, 0x3, 0x2, 0x2, 0x2, 0x108, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x109, 
    0xfa, 0x3, 0x2, 0x2, 0x2, 0x109, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10b, 
    0x3, 0x2, 0x2, 0x2, 0x10b, 0x10c, 0x7, 0x4d, 0x2, 0x2, 0x10c, 0x1d, 
    0x3, 0x2, 0x2, 0x2, 0x10d, 0x10e, 0x5, 0x1c, 0xf, 0x2, 0x10e, 0x1f, 
    0x3, 0x2, 0x2, 0x2, 0x10f, 0x110, 0x5, 0x1c, 0xf, 0x2, 0x110, 0x21, 
    0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 0x7, 0xc, 0x2, 0x2, 0x112, 0x121, 
    0x7, 0x4b, 0x2, 0x2, 0x113, 0x115, 0x7, 0x5, 0x2, 0x2, 0x114, 0x116, 
    0x7, 0x4b, 0x2, 0x2, 0x115, 0x114, 0x3, 0x2, 0x2, 0x2, 0x115, 0x116, 
    0x3, 0x2, 0x2, 0x2, 0x116, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x117, 0x119, 
    0x7, 0x5, 0x2, 0x2, 0x118, 0x11a, 0x7, 0x4b, 0x2, 0x2, 0x119, 0x118, 
    0x3, 0x2, 0x2, 0x2, 0x119, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x11d, 
    0x3, 0x2, 0x2, 0x2, 0x11b, 0x11c, 0x7, 0x5, 0x2, 0x2, 0x11c, 0x11e, 
    0x5, 0x18, 0xd, 0x2, 0x11d, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11e, 
    0x3, 0x2, 0x2, 0x2, 0x11e, 0x120, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x117, 
    0x3, 0x2, 0x2, 0x2, 0x11f, 0x120, 0x3, 0x2, 0x2, 0x2, 0x120, 0x122, 
    0x3, 0x2, 0x2, 0x2, 0x121, 0x113, 0x3, 0x2, 0x2, 0x2, 0x121, 0x122, 
    0x3, 0x2, 0x2, 0x2, 0x122, 0x123, 0x3, 0x2, 0x2, 0x2, 0x123, 0x127, 
    0x7, 0x4d, 0x2, 0x2, 0x124, 0x126, 0x5, 0x26, 0x14, 0x2, 0x125, 0x124, 
    0x3, 0x2, 0x2, 0x2, 0x126, 0x129, 0x3, 0x2, 0x2, 0x2, 0x127, 0x125, 
    0x3, 0x2, 0x2, 0x2, 0x127, 0x128, 0x3, 0x2, 0x2, 0x2, 0x128, 0x12d, 
    0x3, 0x2, 0x2, 0x2, 0x129, 0x127, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12c, 
    0x5, 0x24, 0x13, 0x2, 0x12b, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12c, 0x12f, 
    0x3, 0x2, 0x2, 0x2, 0x12d, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x12e, 
    0x3, 0x2, 0x2, 0x2, 0x12e, 0x130, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x12d, 
    0x3, 0x2, 0x2, 0x2, 0x130, 0x131, 0x5, 0x28, 0x15, 0x2, 0x131, 0x23, 
    0x3, 0x2, 0x2, 0x2, 0x132, 0x133, 0x7, 0xd, 0x2, 0x2, 0x133, 0x148, 
    0x7, 0x4b, 0x2, 0x2, 0x134, 0x136, 0x7, 0x5, 0x2, 0x2, 0x135, 0x137, 
    0x7, 0x4b, 0x2, 0x2, 0x136, 0x135, 0x3, 0x2, 0x2, 0x2, 0x136, 0x137, 
    0x3, 0x2, 0x2, 0x2, 0x137, 0x146, 0x3, 0x2, 0x2, 0x2, 0x138, 0x13a, 
    0x7, 0x5, 0x2, 0x2, 0x139, 0x13b, 0x7, 0x4b, 0x2, 0x2, 0x13a, 0x139, 
    0x3, 0x2, 0x2, 0x2, 0x13a, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x144, 
    0x3, 0x2, 0x2, 0x2, 0x13c, 0x13e, 0x7, 0x5, 0x2, 0x2, 0x13d, 0x13f, 
    0x7, 0x4e, 0x2, 0x2, 0x13e, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13e, 0x13f, 
    0x3, 0x2, 0x2, 0x2, 0x13f, 0x142, 0x3, 0x2, 0x2, 0x2, 0x140, 0x141, 
    0x7, 0x5, 0x2, 0x2, 0x141, 0x143, 0x5, 0x18, 0xd, 0x2, 0x142, 0x140, 
    0x3, 0x2, 0x2, 0x2, 0x142, 0x143, 0x3, 0x2, 0x2, 0x2, 0x143, 0x145, 
    0x3, 0x2, 0x2, 0x2, 0x144, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x144, 0x145, 
    0x3, 0x2, 0x2, 0x2, 0x145, 0x147, 0x3, 0x2, 0x2, 0x2, 0x146, 0x138, 
    0x3, 0x2, 0x2, 0x2, 0x146, 0x147, 0x3, 0x2, 0x2, 0x2, 0x147, 0x149, 
    0x3, 0x2, 0x2, 0x2, 0x148, 0x134, 0x3, 0x2, 0x2, 0x2, 0x148, 0x149, 
    0x3, 0x2, 0x2, 0x2, 0x149, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x14b, 
    0x7, 0x4d, 0x2, 0x2, 0x14b, 0x25, 0x3, 0x2, 0x2, 0x2, 0x14c, 0x14d, 
    0x7, 0xe, 0x2, 0x2, 0x14d, 0x14e, 0x7, 0x4b, 0x2, 0x2, 0x14e, 0x14f, 
    0x7, 0x5, 0x2, 0x2, 0x14f, 0x15b, 0x7, 0x4b, 0x2, 0x2, 0x150, 0x154, 
    0x7, 0x5, 0x2, 0x2, 0x151, 0x153, 0x7, 0x4b, 0x2, 0x2, 0x152, 0x151, 
    0x3, 0x2, 0x2, 0x2, 0x153, 0x156, 0x3, 0x2, 0x2, 0x2, 0x154, 0x152, 
    0x3, 0x2, 0x2, 0x2, 0x154, 0x155, 0x3, 0x2, 0x2, 0x2, 0x155, 0x159, 
    0x3, 0x2, 0x2, 0x2, 0x156, 0x154, 0x3, 0x2, 0x2, 0x2, 0x157, 0x158, 
    0x7, 0x5, 0x2, 0x2, 0x158, 0x15a, 0x5, 0x18, 0xd, 0x2, 0x159, 0x157, 
    0x3, 0x2, 0x2, 0x2, 0x159, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x15c, 
    0x3, 0x2, 0x2, 0x2, 0x15b, 0x150, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x15c, 
    0x3, 0x2, 0x2, 0x2, 0x15c, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x15e, 
    0x7, 0x4d, 0x2, 0x2, 0x15e, 0x27, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x161, 
    0x5, 0x2a, 0x16, 0x2, 0x160, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x160, 0x161, 
    0x3, 0x2, 0x2, 0x2, 0x161, 0x162, 0x3, 0x2, 0x2, 0x2, 0x162, 0x164, 
    0x7, 0x4d, 0x2, 0x2, 0x163, 0x160, 0x3, 0x2, 0x2, 0x2, 0x164, 0x167, 
    0x3, 0x2, 0x2, 0x2, 0x165, 0x163, 0x3, 0x2, 0x2, 0x2, 0x165, 0x166, 
    0x3, 0x2, 0x2, 0x2, 0x166, 0x29, 0x3, 0x2, 0x2, 0x2, 0x167, 0x165, 0x3, 
    0x2, 0x2, 0x2, 0x168, 0x172, 0x5, 0x30, 0x19, 0x2, 0x169, 0x16a, 0x5, 
    0x34, 0x1b, 0x2, 0x16a, 0x16b, 0x9, 0x2, 0x2, 0x2, 0x16b, 0x16c, 0x5, 
    0x38, 0x1d, 0x2, 0x16c, 0x172, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x172, 0x5, 
    0x38, 0x1d, 0x2, 0x16e, 0x172, 0x5, 0x2e, 0x18, 0x2, 0x16f, 0x172, 0x5, 
    0x2c, 0x17, 0x2, 0x170, 0x172, 0x5, 0x32, 0x1a, 0x2, 0x171, 0x168, 0x3, 
    0x2, 0x2, 0x2, 0x171, 0x169, 0x3, 0x2, 0x2, 0x2, 0x171, 0x16d, 0x3, 
    0x2, 0x2, 0x2, 0x171, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x171, 0x16f, 0x3, 
    0x2, 0x2, 0x2, 0x171, 0x170, 0x3, 0x2, 0x2, 0x2, 0x172, 0x2b, 0x3, 0x2, 
    0x2, 0x2, 0x173, 0x174, 0x7, 0xf, 0x2, 0x2, 0x174, 0x175, 0x7, 0x10, 
    0x2, 0x2, 0x175, 0x176, 0x5, 0x38, 0x1d, 0x2, 0x176, 0x177, 0x7, 0x11, 
    0x2, 0x2, 0x177, 0x178, 0x7, 0x4d, 0x2, 0x2, 0x178, 0x182, 0x5, 0x28, 
    0x15, 0x2, 0x179, 0x17a, 0x7, 0x12, 0x2, 0x2, 0x17a, 0x17b, 0x7, 0x10, 
    0x2, 0x2, 0x17b, 0x17c, 0x5, 0x38, 0x1d, 0x2, 0x17c, 0x17d, 0x7, 0x11, 
    0x2, 0x2, 0x17d, 0x17e, 0x7, 0x4d, 0x2, 0x2, 0x17e, 0x17f, 0x5, 0x28, 
    0x15, 0x2, 0x17f, 0x181, 0x3, 0x2, 0x2, 0x2, 0x180, 0x179, 0x3, 0x2, 
    0x2, 0x2, 0x181, 0x184, 0x3, 0x2, 0x2, 0x2, 0x182, 0x180, 0x3, 0x2, 
    0x2, 0x2, 0x182, 0x183, 0x3, 0x2, 0x2, 0x2, 0x183, 0x185, 0x3, 0x2, 
    0x2, 0x2, 0x184, 0x182, 0x3, 0x2, 0x2, 0x2, 0x185, 0x186, 0x7, 0x13, 
    0x2, 0x2, 0x186, 0x187, 0x7, 0x4d, 0x2, 0x2, 0x187, 0x188, 0x5, 0x28, 
    0x15, 0x2, 0x188, 0x189, 0x7, 0x14, 0x2, 0x2, 0x189, 0x2d, 0x3, 0x2, 
    0x2, 0x2, 0x18a, 0x18b, 0x7, 0x15, 0x2, 0x2, 0x18b, 0x18c, 0x7, 0x10, 
    0x2, 0x2, 0x18c, 0x18d, 0x5, 0x38, 0x1d, 0x2, 0x18d, 0x18e, 0x7, 0x11, 
    0x2, 0x2, 0x18e, 0x18f, 0x7, 0x4d, 0x2, 0x2, 0x18f, 0x190, 0x5, 0x28, 
    0x15, 0x2, 0x190, 0x191, 0x7, 0x16, 0x2, 0x2, 0x191, 0x192, 0x7, 0x10, 
    0x2, 0x2, 0x192, 0x193, 0x7, 0x11, 0x2, 0x2, 0x193, 0x1bf, 0x3, 0x2, 
    0x2, 0x2, 0x194, 0x195, 0x7, 0x17, 0x2, 0x2, 0x195, 0x196, 0x7, 0x10, 
    0x2, 0x2, 0x196, 0x197, 0x5, 0x38, 0x1d, 0x2, 0x197, 0x199, 0x7, 0x5, 
    0x2, 0x2, 0x198, 0x19a, 0x5, 0x34, 0x1b, 0x2, 0x199, 0x198, 0x3, 0x2, 
    0x2, 0x2, 0x199, 0x19a, 0x3, 0x2, 0x2, 0x2, 0x19a, 0x19b, 0x3, 0x2, 
    0x2, 0x2, 0x19b, 0x19c, 0x7, 0x11, 0x2, 0x2, 0x19c, 0x19d, 0x7, 0x4d, 
    0x2, 0x2, 0x19d, 0x19e, 0x5, 0x28, 0x15, 0x2, 0x19e, 0x19f, 0x7, 0x18, 
    0x2, 0x2, 0x19f, 0x1a0, 0x7, 0x10, 0x2, 0x2, 0x1a0, 0x1a1, 0x7, 0x11, 
    0x2, 0x2, 0x1a1, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x1a3, 0x7, 0x19, 
    0x2, 0x2, 0x1a3, 0x1a4, 0x7, 0x10, 0x2, 0x2, 0x1a4, 0x1a5, 0x5, 0x38, 
    0x1d, 0x2, 0x1a5, 0x1a6, 0x7, 0x5, 0x2, 0x2, 0x1a6, 0x1a7, 0x5, 0x38, 
    0x1d, 0x2, 0x1a7, 0x1a8, 0x7, 0x5, 0x2, 0x2, 0x1a8, 0x1ab, 0x5, 0x38, 
    0x1d, 0x2, 0x1a9, 0x1aa, 0x7, 0x5, 0x2, 0x2, 0x1aa, 0x1ac, 0x5, 0x34, 
    0x1b, 0x2, 0x1ab, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1ac, 0x3, 0x2, 
    0x2, 0x2, 0x1ac, 0x1ad, 0x3, 0x2, 0x2, 0x2, 0x1ad, 0x1ae, 0x7, 0x11, 
    0x2, 0x2, 0x1ae, 0x1af, 0x7, 0x4d, 0x2, 0x2, 0x1af, 0x1b0, 0x5, 0x28, 
    0x15, 0x2, 0x1b0, 0x1b1, 0x7, 0x1a, 0x2, 0x2, 0x1b1, 0x1b2, 0x7, 0x10, 
    0x2, 0x2, 0x1b2, 0x1b3, 0x7, 0x11, 0x2, 0x2, 0x1b3, 0x1bf, 0x3, 0x2, 
    0x2, 0x2, 0x1b4, 0x1b5, 0x7, 0x1b, 0x2, 0x2, 0x1b5, 0x1b6, 0x7, 0x10, 
    0x2, 0x2, 0x1b6, 0x1b7, 0x7, 0x11, 0x2, 0x2, 0x1b7, 0x1b8, 0x7, 0x4d, 
    0x2, 0x2, 0x1b8, 0x1b9, 0x5, 0x28, 0x15, 0x2, 0x1b9, 0x1ba, 0x7, 0x1c, 
    0x2, 0x2, 0x1ba, 0x1bb, 0x7, 0x10, 0x2, 0x2, 0x1bb, 0x1bc, 0x5, 0x38, 
    0x1d, 0x2, 0x1bc, 0x1bd, 0x7, 0x11, 0x2, 0x2, 0x1bd, 0x1bf, 0x3, 0x2, 
    0x2, 0x2, 0x1be, 0x18a, 0x3, 0x2, 0x2, 0x2, 0x1be, 0x194, 0x3, 0x2, 
    0x2, 0x2, 0x1be, 0x1a2, 0x3, 0x2, 0x2, 0x2, 0x1be, 0x1b4, 0x3, 0x2, 
    0x2, 0x2, 0x1bf, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x1c1, 0x7, 0x1d, 
    0x2, 0x2, 0x1c1, 0x1c2, 0x7, 0x10, 0x2, 0x2, 0x1c2, 0x1c3, 0x5, 0x38, 
    0x1d, 0x2, 0x1c3, 0x1c4, 0x7, 0x11, 0x2, 0x2, 0x1c4, 0x1c7, 0x5, 0x28, 
    0x15, 0x2, 0x1c5, 0x1c6, 0x7, 0x1e, 0x2, 0x2, 0x1c6, 0x1c8, 0x5, 0x28, 
    0x15, 0x2, 0x1c7, 0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c7, 0x1c8, 0x3, 0x2, 
    0x2, 0x2, 0x1c8, 0x1c9, 0x3, 0x2, 0x2, 0x2, 0x1c9, 0x1ca, 0x7, 0x1f, 
    0x2, 0x2, 0x1ca, 0x1d3, 0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1cc, 0x7, 0x20, 
    0x2, 0x2, 0x1cc, 0x1cd, 0x7, 0x10, 0x2, 0x2, 0x1cd, 0x1ce, 0x5, 0x38, 
    0x1d, 0x2, 0x1ce, 0x1cf, 0x7, 0x11, 0x2, 0x2, 0x1cf, 0x1d0, 0x5, 0x28, 
    0x15, 0x2, 0x1d0, 0x1d1, 0x7, 0x21, 0x2, 0x2, 0x1d1, 0x1d3, 0x3, 0x2, 
    0x2, 0x2, 0x1d2, 0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1d2, 0x1cb, 0x3, 0x2, 
    0x2, 0x2, 0x1d3, 0x31, 0x3, 0x2, 0x2, 0x2, 0x1d4, 0x1d5, 0x7, 0x22, 
    0x2, 0x2, 0x1d5, 0x1d6, 0x7, 0x10, 0x2, 0x2, 0x1d6, 0x1e4, 0x7, 0x11, 
    0x2, 0x2, 0x1d7, 0x1d8, 0x7, 0x23, 0x2, 0x2, 0x1d8, 0x1d9, 0x7, 0x10, 
    0x2, 0x2, 0x1d9, 0x1e4, 0x7, 0x11, 0x2, 0x2, 0x1da, 0x1db, 0x7, 0x24, 
    0x2, 0x2, 0x1db, 0x1dd, 0x7, 0x10, 0x2, 0x2, 0x1dc, 0x1de, 0x5, 0x38, 
    0x1d, 0x2, 0x1dd, 0x1dc, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1de, 0x3, 0x2, 
    0x2, 0x2, 0x1de, 0x1df, 0x3, 0x2, 0x2, 0x2, 0x1df, 0x1e4, 0x7, 0x11, 
    0x2, 0x2, 0x1e0, 0x1e1, 0x7, 0x25, 0x2, 0x2, 0x1e1, 0x1e2, 0x7, 0x10, 
    0x2, 0x2, 0x1e2, 0x1e4, 0x7, 0x11, 0x2, 0x2, 0x1e3, 0x1d4, 0x3, 0x2, 
    0x2, 0x2, 0x1e3, 0x1d7, 0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1da, 0x3, 0x2, 
    0x2, 0x2, 0x1e3, 0x1e0, 0x3, 0x2, 0x2, 0x2, 0x1e4, 0x33, 0x3, 0x2, 0x2, 
    0x2, 0x1e5, 0x1ea, 0x5, 0x36, 0x1c, 0x2, 0x1e6, 0x1e7, 0x7, 0x26, 0x2, 
    0x2, 0x1e7, 0x1e9, 0x5, 0x36, 0x1c, 0x2, 0x1e8, 0x1e6, 0x3, 0x2, 0x2, 
    0x2, 0x1e9, 0x1ec, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1e8, 0x3, 0x2, 0x2, 
    0x2, 0x1ea, 0x1eb, 0x3, 0x2, 0x2, 0x2, 0x1eb, 0x35, 0x3, 0x2, 0x2, 0x2, 
    0x1ec, 0x1ea, 0x3, 0x2, 0x2, 0x2, 0x1ed, 0x1ee, 0x8, 0x1c, 0x1, 0x2, 
    0x1ee, 0x1ef, 0x7, 0x4b, 0x2, 0x2, 0x1ef, 0x206, 0x3, 0x2, 0x2, 0x2, 
    0x1f0, 0x1f1, 0xc, 0x4, 0x2, 0x2, 0x1f1, 0x1f3, 0x7, 0x10, 0x2, 0x2, 
    0x1f2, 0x1f4, 0x5, 0x38, 0x1d, 0x2, 0x1f3, 0x1f2, 0x3, 0x2, 0x2, 0x2, 
    0x1f3, 0x1f4, 0x3, 0x2, 0x2, 0x2, 0x1f4, 0x1fb, 0x3, 0x2, 0x2, 0x2, 
    0x1f5, 0x1f7, 0x7, 0x5, 0x2, 0x2, 0x1f6, 0x1f8, 0x5, 0x38, 0x1d, 0x2, 
    0x1f7, 0x1f6, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1f8, 0x3, 0x2, 0x2, 0x2, 
    0x1f8, 0x1fa, 0x3, 0x2, 0x2, 0x2, 0x1f9, 0x1f5, 0x3, 0x2, 0x2, 0x2, 
    0x1fa, 0x1fd, 0x3, 0x2, 0x2, 0x2, 0x1fb, 0x1f9, 0x3, 0x2, 0x2, 0x2, 
    0x1fb, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1fe, 0x3, 0x2, 0x2, 0x2, 
    0x1fd, 0x1fb, 0x3, 0x2, 0x2, 0x2, 0x1fe, 0x205, 0x7, 0x11, 0x2, 0x2, 
    0x1ff, 0x200, 0xc, 0x3, 0x2, 0x2, 0x200, 0x201, 0x7, 0x27, 0x2, 0x2, 
    0x201, 0x202, 0x5, 0x38, 0x1d, 0x2, 0x202, 0x203, 0x7, 0x28, 0x2, 0x2, 
    0x203, 0x205, 0x3, 0x2, 0x2, 0x2, 0x204, 0x1f0, 0x3, 0x2, 0x2, 0x2, 
    0x204, 0x1ff, 0x3, 0x2, 0x2, 0x2, 0x205, 0x208, 0x3, 0x2, 0x2, 0x2, 
    0x206, 0x204, 0x3, 0x2, 0x2, 0x2, 0x206, 0x207, 0x3, 0x2, 0x2, 0x2, 
    0x207, 0x37, 0x3, 0x2, 0x2, 0x2, 0x208, 0x206, 0x3, 0x2, 0x2, 0x2, 0x209, 
    0x20a, 0x8, 0x1d, 0x1, 0x2, 0x20a, 0x20b, 0x7, 0x10, 0x2, 0x2, 0x20b, 
    0x20c, 0x5, 0x38, 0x1d, 0x2, 0x20c, 0x20d, 0x7, 0x11, 0x2, 0x2, 0x20d, 
    0x219, 0x3, 0x2, 0x2, 0x2, 0x20e, 0x20f, 0x7, 0x39, 0x2, 0x2, 0x20f, 
    0x219, 0x5, 0x38, 0x1d, 0x1b, 0x210, 0x219, 0x5, 0x46, 0x24, 0x2, 0x211, 
    0x219, 0x5, 0x44, 0x23, 0x2, 0x212, 0x219, 0x5, 0x40, 0x21, 0x2, 0x213, 
    0x219, 0x5, 0x48, 0x25, 0x2, 0x214, 0x219, 0x5, 0x34, 0x1b, 0x2, 0x215, 
    0x219, 0x5, 0x42, 0x22, 0x2, 0x216, 0x219, 0x5, 0x3c, 0x1f, 0x2, 0x217, 
    0x219, 0x5, 0x3a, 0x1e, 0x2, 0x218, 0x209, 0x3, 0x2, 0x2, 0x2, 0x218, 
    0x20e, 0x3, 0x2, 0x2, 0x2, 0x218, 0x210, 0x3, 0x2, 0x2, 0x2, 0x218, 
    0x211, 0x3, 0x2, 0x2, 0x2, 0x218, 0x212, 0x3, 0x2, 0x2, 0x2, 0x218, 
    0x213, 0x3, 0x2, 0x2, 0x2, 0x218, 0x214, 0x3, 0x2, 0x2, 0x2, 0x218, 
    0x215, 0x3, 0x2, 0x2, 0x2, 0x218, 0x216, 0x3, 0x2, 0x2, 0x2, 0x218, 
    0x217, 0x3, 0x2, 0x2, 0x2, 0x219, 0x24c, 0x3, 0x2, 0x2, 0x2, 0x21a, 
    0x21b, 0xc, 0x1a, 0x2, 0x2, 0x21b, 0x21c, 0x7, 0x3a, 0x2, 0x2, 0x21c, 
    0x24b, 0x5, 0x38, 0x1d, 0x1b, 0x21d, 0x21e, 0xc, 0x19, 0x2, 0x2, 0x21e, 
    0x21f, 0x7, 0x3b, 0x2, 0x2, 0x21f, 0x24b, 0x5, 0x38, 0x1d, 0x1a, 0x220, 
    0x221, 0xc, 0x18, 0x2, 0x2, 0x221, 0x222, 0x7, 0x3c, 0x2, 0x2, 0x222, 
    0x24b, 0x5, 0x38, 0x1d, 0x19, 0x223, 0x224, 0xc, 0x17, 0x2, 0x2, 0x224, 
    0x225, 0x7, 0x3d, 0x2, 0x2, 0x225, 0x24b, 0x5, 0x38, 0x1d, 0x18, 0x226, 
    0x227, 0xc, 0x16, 0x2, 0x2, 0x227, 0x228, 0x7, 0x38, 0x2, 0x2, 0x228, 
    0x24b, 0x5, 0x38, 0x1d, 0x17, 0x229, 0x22a, 0xc, 0x15, 0x2, 0x2, 0x22a, 
    0x22b, 0x7, 0x39, 0x2, 0x2, 0x22b, 0x24b, 0x5, 0x38, 0x1d, 0x16, 0x22c, 
    0x22d, 0xc, 0x14, 0x2, 0x2, 0x22d, 0x22e, 0x7, 0x41, 0x2, 0x2, 0x22e, 
    0x24b, 0x5, 0x38, 0x1d, 0x15, 0x22f, 0x230, 0xc, 0x13, 0x2, 0x2, 0x230, 
    0x231, 0x7, 0x40, 0x2, 0x2, 0x231, 0x24b, 0x5, 0x38, 0x1d, 0x14, 0x232, 
    0x233, 0xc, 0x12, 0x2, 0x2, 0x233, 0x234, 0x7, 0x3e, 0x2, 0x2, 0x234, 
    0x24b, 0x5, 0x38, 0x1d, 0x13, 0x235, 0x236, 0xc, 0x11, 0x2, 0x2, 0x236, 
    0x237, 0x7, 0x43, 0x2, 0x2, 0x237, 0x24b, 0x5, 0x38, 0x1d, 0x12, 0x238, 
    0x239, 0xc, 0x10, 0x2, 0x2, 0x239, 0x23a, 0x7, 0x42, 0x2, 0x2, 0x23a, 
    0x24b, 0x5, 0x38, 0x1d, 0x11, 0x23b, 0x23c, 0xc, 0xf, 0x2, 0x2, 0x23c, 
    0x23d, 0x7, 0x45, 0x2, 0x2, 0x23d, 0x24b, 0x5, 0x38, 0x1d, 0x10, 0x23e, 
    0x23f, 0xc, 0xe, 0x2, 0x2, 0x23f, 0x240, 0x7, 0x44, 0x2, 0x2, 0x240, 
    0x24b, 0x5, 0x38, 0x1d, 0xf, 0x241, 0x242, 0xc, 0xd, 0x2, 0x2, 0x242, 
    0x243, 0x7, 0x46, 0x2, 0x2, 0x243, 0x24b, 0x5, 0x38, 0x1d, 0xe, 0x244, 
    0x245, 0xc, 0xc, 0x2, 0x2, 0x245, 0x246, 0x7, 0x48, 0x2, 0x2, 0x246, 
    0x24b, 0x5, 0x38, 0x1d, 0xd, 0x247, 0x248, 0xc, 0xb, 0x2, 0x2, 0x248, 
    0x249, 0x7, 0x47, 0x2, 0x2, 0x249, 0x24b, 0x5, 0x38, 0x1d, 0xc, 0x24a, 
    0x21a, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x24a, 
    0x220, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x223, 0x3, 0x2, 0x2, 0x2, 0x24a, 
    0x226, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x229, 0x3, 0x2, 0x2, 0x2, 0x24a, 
    0x22c, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x22f, 0x3, 0x2, 0x2, 0x2, 0x24a, 
    0x232, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x235, 0x3, 0x2, 0x2, 0x2, 0x24a, 
    0x238, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x23b, 0x3, 0x2, 0x2, 0x2, 0x24a, 
    0x23e, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x241, 0x3, 0x2, 0x2, 0x2, 0x24a, 
    0x244, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x247, 0x3, 0x2, 0x2, 0x2, 0x24b, 
    0x24e, 0x3, 0x2, 0x2, 0x2, 0x24c, 0x24a, 0x3, 0x2, 0x2, 0x2, 0x24c, 
    0x24d, 0x3, 0x2, 0x2, 0x2, 0x24d, 0x39, 0x3, 0x2, 0x2, 0x2, 0x24e, 0x24c, 
    0x3, 0x2, 0x2, 0x2, 0x24f, 0x258, 0x7, 0x29, 0x2, 0x2, 0x250, 0x255, 
    0x5, 0x38, 0x1d, 0x2, 0x251, 0x252, 0x7, 0x5, 0x2, 0x2, 0x252, 0x254, 
    0x5, 0x38, 0x1d, 0x2, 0x253, 0x251, 0x3, 0x2, 0x2, 0x2, 0x254, 0x257, 
    0x3, 0x2, 0x2, 0x2, 0x255, 0x253, 0x3, 0x2, 0x2, 0x2, 0x255, 0x256, 
    0x3, 0x2, 0x2, 0x2, 0x256, 0x259, 0x3, 0x2, 0x2, 0x2, 0x257, 0x255, 
    0x3, 0x2, 0x2, 0x2, 0x258, 0x250, 0x3, 0x2, 0x2, 0x2, 0x258, 0x259, 
    0x3, 0x2, 0x2, 0x2, 0x259, 0x25a, 0x3, 0x2, 0x2, 0x2, 0x25a, 0x25b, 
    0x7, 0x2a, 0x2, 0x2, 0x25b, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x25c, 0x25d, 
    0x7, 0x27, 0x2, 0x2, 0x25d, 0x25e, 0x5, 0x3e, 0x20, 0x2, 0x25e, 0x25f, 
    0x7, 0x28, 0x2, 0x2, 0x25f, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x260, 0x2a4, 
    0x7, 0x49, 0x2, 0x2, 0x261, 0x262, 0x7, 0x49, 0x2, 0x2, 0x262, 0x263, 
    0x7, 0x2b, 0x2, 0x2, 0x263, 0x264, 0x7, 0x49, 0x2, 0x2, 0x264, 0x265, 
    0x7, 0x2c, 0x2, 0x2, 0x265, 0x266, 0x7, 0x49, 0x2, 0x2, 0x266, 0x26d, 
    0x7, 0x2d, 0x2, 0x2, 0x267, 0x268, 0x7, 0x49, 0x2, 0x2, 0x268, 0x269, 
    0x7, 0x2e, 0x2, 0x2, 0x269, 0x26a, 0x7, 0x49, 0x2, 0x2, 0x26a, 0x26b, 
    0x7, 0x2f, 0x2, 0x2, 0x26b, 0x26c, 0x7, 0x49, 0x2, 0x2, 0x26c, 0x26e, 
    0x7, 0x30, 0x2, 0x2, 0x26d, 0x267, 0x3, 0x2, 0x2, 0x2, 0x26d, 0x26e, 
    0x3, 0x2, 0x2, 0x2, 0x26e, 0x2a4, 0x3, 0x2, 0x2, 0x2, 0x26f, 0x270, 
    0x7, 0x49, 0x2, 0x2, 0x270, 0x271, 0x7, 0x31, 0x2, 0x2, 0x271, 0x272, 
    0x7, 0x49, 0x2, 0x2, 0x272, 0x273, 0x7, 0x31, 0x2, 0x2, 0x273, 0x27a, 
    0x7, 0x49, 0x2, 0x2, 0x274, 0x275, 0x7, 0x31, 0x2, 0x2, 0x275, 0x276, 
    0x7, 0x49, 0x2, 0x2, 0x276, 0x277, 0x7, 0x31, 0x2, 0x2, 0x277, 0x278, 
    0x7, 0x49, 0x2, 0x2, 0x278, 0x279, 0x7, 0x31, 0x2, 0x2, 0x279, 0x27b, 
    0x7, 0x49, 0x2, 0x2, 0x27a, 0x274, 0x3, 0x2, 0x2, 0x2, 0x27a, 0x27b, 
    0x3, 0x2, 0x2, 0x2, 0x27b, 0x2a4, 0x3, 0x2, 0x2, 0x2, 0x27c, 0x27d, 
    0x7, 0x49, 0x2, 0x2, 0x27d, 0x27e, 0x7, 0x31, 0x2, 0x2, 0x27e, 0x27f, 
    0x7, 0x49, 0x2, 0x2, 0x27f, 0x280, 0x7, 0x31, 0x2, 0x2, 0x280, 0x287, 
    0x7, 0x49, 0x2, 0x2, 0x281, 0x282, 0x7, 0x31, 0x2, 0x2, 0x282, 0x283, 
    0x7, 0x49, 0x2, 0x2, 0x283, 0x284, 0x7, 0x32, 0x2, 0x2, 0x284, 0x285, 
    0x7, 0x49, 0x2, 0x2, 0x285, 0x286, 0x7, 0x32, 0x2, 0x2, 0x286, 0x288, 
    0x7, 0x49, 0x2, 0x2, 0x287, 0x281, 0x3, 0x2, 0x2, 0x2, 0x287, 0x288, 
    0x3, 0x2, 0x2, 0x2, 0x288, 0x2a4, 0x3, 0x2, 0x2, 0x2, 0x289, 0x28a, 
    0x7, 0x49, 0x2, 0x2, 0x28a, 0x28b, 0x7, 0x33, 0x2, 0x2, 0x28b, 0x28c, 
    0x7, 0x49, 0x2, 0x2, 0x28c, 0x28d, 0x7, 0x33, 0x2, 0x2, 0x28d, 0x294, 
    0x7, 0x49, 0x2, 0x2, 0x28e, 0x28f, 0x7, 0x33, 0x2, 0x2, 0x28f, 0x290, 
    0x7, 0x49, 0x2, 0x2, 0x290, 0x291, 0x7, 0x33, 0x2, 0x2, 0x291, 0x292, 
    0x7, 0x49, 0x2, 0x2, 0x292, 0x293, 0x7, 0x33, 0x2, 0x2, 0x293, 0x295, 
    0x7, 0x49, 0x2, 0x2, 0x294, 0x28e, 0x3, 0x2, 0x2, 0x2, 0x294, 0x295, 
    0x3, 0x2, 0x2, 0x2, 0x295, 0x2a4, 0x3, 0x2, 0x2, 0x2, 0x296, 0x297, 
    0x7, 0x49, 0x2, 0x2, 0x297, 0x298, 0x7, 0x33, 0x2, 0x2, 0x298, 0x299, 
    0x7, 0x49, 0x2, 0x2, 0x299, 0x29a, 0x7, 0x33, 0x2, 0x2, 0x29a, 0x2a1, 
    0x7, 0x49, 0x2, 0x2, 0x29b, 0x29c, 0x7, 0x33, 0x2, 0x2, 0x29c, 0x29d, 
    0x7, 0x49, 0x2, 0x2, 0x29d, 0x29e, 0x7, 0x32, 0x2, 0x2, 0x29e, 0x29f, 
    0x7, 0x49, 0x2, 0x2, 0x29f, 0x2a0, 0x7, 0x32, 0x2, 0x2, 0x2a0, 0x2a2, 
    0x7, 0x49, 0x2, 0x2, 0x2a1, 0x29b, 0x3, 0x2, 0x2, 0x2, 0x2a1, 0x2a2, 
    0x3, 0x2, 0x2, 0x2, 0x2a2, 0x2a4, 0x3, 0x2, 0x2, 0x2, 0x2a3, 0x260, 
    0x3, 0x2, 0x2, 0x2, 0x2a3, 0x261, 0x3, 0x2, 0x2, 0x2, 0x2a3, 0x26f, 
    0x3, 0x2, 0x2, 0x2, 0x2a3, 0x27c, 0x3, 0x2, 0x2, 0x2, 0x2a3, 0x289, 
    0x3, 0x2, 0x2, 0x2, 0x2a3, 0x296, 0x3, 0x2, 0x2, 0x2, 0x2a4, 0x3f, 0x3, 
    0x2, 0x2, 0x2, 0x2a5, 0x2a6, 0x7, 0x34, 0x2, 0x2, 0x2a6, 0x2a7, 0x7, 
    0x4b, 0x2, 0x2, 0x2a7, 0x41, 0x3, 0x2, 0x2, 0x2, 0x2a8, 0x2a9, 0x7, 
    0x35, 0x2, 0x2, 0x2a9, 0x2aa, 0x7, 0x4b, 0x2, 0x2, 0x2aa, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x2ab, 0x2ae, 0x7, 0x36, 0x2, 0x2, 0x2ac, 0x2ae, 0x7, 
    0x37, 0x2, 0x2, 0x2ad, 0x2ab, 0x3, 0x2, 0x2, 0x2, 0x2ad, 0x2ac, 0x3, 
    0x2, 0x2, 0x2, 0x2ae, 0x45, 0x3, 0x2, 0x2, 0x2, 0x2af, 0x2b2, 0x7, 0x49, 
    0x2, 0x2, 0x2b0, 0x2b2, 0x7, 0x4a, 0x2, 0x2, 0x2b1, 0x2af, 0x3, 0x2, 
    0x2, 0x2, 0x2b1, 0x2b0, 0x3, 0x2, 0x2, 0x2, 0x2b2, 0x47, 0x3, 0x2, 0x2, 
    0x2, 0x2b3, 0x2b4, 0x7, 0x4e, 0x2, 0x2, 0x2b4, 0x49, 0x3, 0x2, 0x2, 
    0x2, 0x56, 0x53, 0x5a, 0x62, 0x6a, 0x71, 0x75, 0x7b, 0x81, 0x87, 0x8d, 
    0x94, 0x98, 0x9c, 0xa0, 0xa2, 0xa4, 0xa6, 0xb1, 0xb5, 0xb7, 0xbe, 0xc4, 
    0xca, 0xd1, 0xd5, 0xd9, 0xdb, 0xdd, 0xe4, 0xea, 0xf1, 0xf6, 0xfc, 0x101, 
    0x105, 0x107, 0x109, 0x115, 0x119, 0x11d, 0x11f, 0x121, 0x127, 0x12d, 
    0x136, 0x13a, 0x13e, 0x142, 0x144, 0x146, 0x148, 0x154, 0x159, 0x15b, 
    0x160, 0x165, 0x171, 0x182, 0x199, 0x1ab, 0x1be, 0x1c7, 0x1d2, 0x1dd, 
    0x1e3, 0x1ea, 0x1f3, 0x1f7, 0x1fb, 0x204, 0x206, 0x218, 0x24a, 0x24c, 
    0x255, 0x258, 0x26d, 0x27a, 0x287, 0x294, 0x2a1, 0x2a3, 0x2ad, 0x2b1, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

openeLangParser::Initializer openeLangParser::_init;
