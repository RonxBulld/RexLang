
// Generated from /mnt/e/Project/RexLang/Compiler/rexlang_compiler/rexLang.g4 by ANTLR 4.7.2


#include "rexLangListener.h"
#include "rexLangVisitor.h"

#include "rexLangParser.h"


using namespace antlrcpp;
using namespace rexlang;
using namespace antlr4;

rexLangParser::rexLangParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

rexLangParser::~rexLangParser() {
  delete _interpreter;
}

std::string rexLangParser::getGrammarFileName() const {
  return "rexLang.g4";
}

const std::vector<std::string>& rexLangParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& rexLangParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- Rexlang_srcContext ------------------------------------------------------------------

rexLangParser::Rexlang_srcContext::Rexlang_srcContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

rexLangParser::Edition_specContext* rexLangParser::Rexlang_srcContext::edition_spec() {
  return getRuleContext<rexLangParser::Edition_specContext>(0);
}

rexLangParser::Src_contentContext* rexLangParser::Rexlang_srcContext::src_content() {
  return getRuleContext<rexLangParser::Src_contentContext>(0);
}

tree::TerminalNode* rexLangParser::Rexlang_srcContext::EOF() {
  return getToken(rexLangParser::EOF, 0);
}

std::vector<tree::TerminalNode *> rexLangParser::Rexlang_srcContext::NEWLINE() {
  return getTokens(rexLangParser::NEWLINE);
}

tree::TerminalNode* rexLangParser::Rexlang_srcContext::NEWLINE(size_t i) {
  return getToken(rexLangParser::NEWLINE, i);
}


size_t rexLangParser::Rexlang_srcContext::getRuleIndex() const {
  return rexLangParser::RuleRexlang_src;
}

void rexLangParser::Rexlang_srcContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRexlang_src(this);
}

void rexLangParser::Rexlang_srcContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRexlang_src(this);
}


antlrcpp::Any rexLangParser::Rexlang_srcContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitRexlang_src(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Rexlang_srcContext* rexLangParser::rexlang_src() {
  Rexlang_srcContext *_localctx = _tracker.createInstance<Rexlang_srcContext>(_ctx, getState());
  enterRule(_localctx, 0, rexLangParser::RuleRexlang_src);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(78);
    edition_spec();
    setState(82);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(79);
        match(rexLangParser::NEWLINE); 
      }
      setState(84);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
    setState(85);
    src_content();
    setState(89);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::NEWLINE) {
      setState(86);
      match(rexLangParser::NEWLINE);
      setState(91);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(92);
    match(rexLangParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Src_contentContext ------------------------------------------------------------------

rexLangParser::Src_contentContext::Src_contentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

rexLangParser::Program_set_fileContext* rexLangParser::Src_contentContext::program_set_file() {
  return getRuleContext<rexLangParser::Program_set_fileContext>(0);
}

rexLangParser::Data_structure_fileContext* rexLangParser::Src_contentContext::data_structure_file() {
  return getRuleContext<rexLangParser::Data_structure_fileContext>(0);
}

rexLangParser::Global_variable_fileContext* rexLangParser::Src_contentContext::global_variable_file() {
  return getRuleContext<rexLangParser::Global_variable_fileContext>(0);
}

rexLangParser::Dll_define_fileContext* rexLangParser::Src_contentContext::dll_define_file() {
  return getRuleContext<rexLangParser::Dll_define_fileContext>(0);
}


size_t rexLangParser::Src_contentContext::getRuleIndex() const {
  return rexLangParser::RuleSrc_content;
}

void rexLangParser::Src_contentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSrc_content(this);
}

void rexLangParser::Src_contentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSrc_content(this);
}


antlrcpp::Any rexLangParser::Src_contentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitSrc_content(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Src_contentContext* rexLangParser::src_content() {
  Src_contentContext *_localctx = _tracker.createInstance<Src_contentContext>(_ctx, getState());
  enterRule(_localctx, 2, rexLangParser::RuleSrc_content);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(98);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(94);
      program_set_file();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(95);
      data_structure_file();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(96);
      global_variable_file();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(97);
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

rexLangParser::Program_set_fileContext::Program_set_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

rexLangParser::Prog_setContext* rexLangParser::Program_set_fileContext::prog_set() {
  return getRuleContext<rexLangParser::Prog_setContext>(0);
}

std::vector<tree::TerminalNode *> rexLangParser::Program_set_fileContext::NEWLINE() {
  return getTokens(rexLangParser::NEWLINE);
}

tree::TerminalNode* rexLangParser::Program_set_fileContext::NEWLINE(size_t i) {
  return getToken(rexLangParser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> rexLangParser::Program_set_fileContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Program_set_fileContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}


size_t rexLangParser::Program_set_fileContext::getRuleIndex() const {
  return rexLangParser::RuleProgram_set_file;
}

void rexLangParser::Program_set_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram_set_file(this);
}

void rexLangParser::Program_set_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram_set_file(this);
}


antlrcpp::Any rexLangParser::Program_set_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitProgram_set_file(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Program_set_fileContext* rexLangParser::program_set_file() {
  Program_set_fileContext *_localctx = _tracker.createInstance<Program_set_fileContext>(_ctx, getState());
  enterRule(_localctx, 4, rexLangParser::RuleProgram_set_file);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(105);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::T__0) {
      setState(100);
      match(rexLangParser::T__0);
      setState(101);
      dynamic_cast<Program_set_fileContext *>(_localctx)->identifierToken = match(rexLangParser::IDENTIFIER);
      dynamic_cast<Program_set_fileContext *>(_localctx)->libraries.push_back(dynamic_cast<Program_set_fileContext *>(_localctx)->identifierToken);
      setState(102);
      match(rexLangParser::NEWLINE);
      setState(107);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(111);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::NEWLINE) {
      setState(108);
      match(rexLangParser::NEWLINE);
      setState(113);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(114);
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

rexLangParser::Data_structure_fileContext::Data_structure_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<rexLangParser::Struct_declareContext *> rexLangParser::Data_structure_fileContext::struct_declare() {
  return getRuleContexts<rexLangParser::Struct_declareContext>();
}

rexLangParser::Struct_declareContext* rexLangParser::Data_structure_fileContext::struct_declare(size_t i) {
  return getRuleContext<rexLangParser::Struct_declareContext>(i);
}


size_t rexLangParser::Data_structure_fileContext::getRuleIndex() const {
  return rexLangParser::RuleData_structure_file;
}

void rexLangParser::Data_structure_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterData_structure_file(this);
}

void rexLangParser::Data_structure_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitData_structure_file(this);
}


antlrcpp::Any rexLangParser::Data_structure_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitData_structure_file(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Data_structure_fileContext* rexLangParser::data_structure_file() {
  Data_structure_fileContext *_localctx = _tracker.createInstance<Data_structure_fileContext>(_ctx, getState());
  enterRule(_localctx, 6, rexLangParser::RuleData_structure_file);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::T__6) {
      setState(116);
      struct_declare();
      setState(121);
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

rexLangParser::Global_variable_fileContext::Global_variable_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

rexLangParser::Global_variable_listContext* rexLangParser::Global_variable_fileContext::global_variable_list() {
  return getRuleContext<rexLangParser::Global_variable_listContext>(0);
}


size_t rexLangParser::Global_variable_fileContext::getRuleIndex() const {
  return rexLangParser::RuleGlobal_variable_file;
}

void rexLangParser::Global_variable_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_variable_file(this);
}

void rexLangParser::Global_variable_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_variable_file(this);
}


antlrcpp::Any rexLangParser::Global_variable_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitGlobal_variable_file(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Global_variable_fileContext* rexLangParser::global_variable_file() {
  Global_variable_fileContext *_localctx = _tracker.createInstance<Global_variable_fileContext>(_ctx, getState());
  enterRule(_localctx, 8, rexLangParser::RuleGlobal_variable_file);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
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

rexLangParser::Dll_define_fileContext::Dll_define_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<rexLangParser::Dll_commandContext *> rexLangParser::Dll_define_fileContext::dll_command() {
  return getRuleContexts<rexLangParser::Dll_commandContext>();
}

rexLangParser::Dll_commandContext* rexLangParser::Dll_define_fileContext::dll_command(size_t i) {
  return getRuleContext<rexLangParser::Dll_commandContext>(i);
}

std::vector<rexLangParser::Lib_commandContext *> rexLangParser::Dll_define_fileContext::lib_command() {
  return getRuleContexts<rexLangParser::Lib_commandContext>();
}

rexLangParser::Lib_commandContext* rexLangParser::Dll_define_fileContext::lib_command(size_t i) {
  return getRuleContext<rexLangParser::Lib_commandContext>(i);
}


size_t rexLangParser::Dll_define_fileContext::getRuleIndex() const {
  return rexLangParser::RuleDll_define_file;
}

void rexLangParser::Dll_define_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDll_define_file(this);
}

void rexLangParser::Dll_define_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDll_define_file(this);
}


antlrcpp::Any rexLangParser::Dll_define_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitDll_define_file(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Dll_define_fileContext* rexLangParser::dll_define_file() {
  Dll_define_fileContext *_localctx = _tracker.createInstance<Dll_define_fileContext>(_ctx, getState());
  enterRule(_localctx, 10, rexLangParser::RuleDll_define_file);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(136);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(127);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == rexLangParser::T__1) {
        setState(124);
        dll_command();
        setState(129);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(133);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == rexLangParser::T__3) {
        setState(130);
        lib_command();
        setState(135);
        _errHandler->sync(this);
        _la = _input->LA(1);
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

//----------------- Dll_commandContext ------------------------------------------------------------------

rexLangParser::Dll_commandContext::Dll_commandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> rexLangParser::Dll_commandContext::NEWLINE() {
  return getTokens(rexLangParser::NEWLINE);
}

tree::TerminalNode* rexLangParser::Dll_commandContext::NEWLINE(size_t i) {
  return getToken(rexLangParser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> rexLangParser::Dll_commandContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Dll_commandContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> rexLangParser::Dll_commandContext::STRING_LITERAL() {
  return getTokens(rexLangParser::STRING_LITERAL);
}

tree::TerminalNode* rexLangParser::Dll_commandContext::STRING_LITERAL(size_t i) {
  return getToken(rexLangParser::STRING_LITERAL, i);
}

rexLangParser::Parameter_decl_listContext* rexLangParser::Dll_commandContext::parameter_decl_list() {
  return getRuleContext<rexLangParser::Parameter_decl_listContext>(0);
}

rexLangParser::Table_commentContext* rexLangParser::Dll_commandContext::table_comment() {
  return getRuleContext<rexLangParser::Table_commentContext>(0);
}


size_t rexLangParser::Dll_commandContext::getRuleIndex() const {
  return rexLangParser::RuleDll_command;
}

void rexLangParser::Dll_commandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDll_command(this);
}

void rexLangParser::Dll_commandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDll_command(this);
}


antlrcpp::Any rexLangParser::Dll_commandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitDll_command(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Dll_commandContext* rexLangParser::dll_command() {
  Dll_commandContext *_localctx = _tracker.createInstance<Dll_commandContext>(_ctx, getState());
  enterRule(_localctx, 12, rexLangParser::RuleDll_command);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(138);
    match(rexLangParser::T__1);
    setState(139);
    dynamic_cast<Dll_commandContext *>(_localctx)->name = match(rexLangParser::IDENTIFIER);
    setState(140);
    match(rexLangParser::T__2);
    setState(142);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::IDENTIFIER) {
      setState(141);
      dynamic_cast<Dll_commandContext *>(_localctx)->type = match(rexLangParser::IDENTIFIER);
    }
    setState(144);
    match(rexLangParser::T__2);
    setState(146);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::STRING_LITERAL) {
      setState(145);
      dynamic_cast<Dll_commandContext *>(_localctx)->file = match(rexLangParser::STRING_LITERAL);
    }
    setState(148);
    match(rexLangParser::T__2);
    setState(149);
    dynamic_cast<Dll_commandContext *>(_localctx)->cmd = match(rexLangParser::STRING_LITERAL);
    setState(150);
    match(rexLangParser::T__2);
    setState(154);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::IDENTIFIER) {
      setState(151);
      dynamic_cast<Dll_commandContext *>(_localctx)->identifierToken = match(rexLangParser::IDENTIFIER);
      dynamic_cast<Dll_commandContext *>(_localctx)->attributes.push_back(dynamic_cast<Dll_commandContext *>(_localctx)->identifierToken);
      setState(156);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(159);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__2) {
      setState(157);
      match(rexLangParser::T__2);
      setState(158);
      table_comment();
    }
    setState(161);
    match(rexLangParser::NEWLINE);
    setState(162);
    dynamic_cast<Dll_commandContext *>(_localctx)->params = parameter_decl_list();
    setState(166);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(163);
        match(rexLangParser::NEWLINE); 
      }
      setState(168);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Lib_commandContext ------------------------------------------------------------------

rexLangParser::Lib_commandContext::Lib_commandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> rexLangParser::Lib_commandContext::NEWLINE() {
  return getTokens(rexLangParser::NEWLINE);
}

tree::TerminalNode* rexLangParser::Lib_commandContext::NEWLINE(size_t i) {
  return getToken(rexLangParser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> rexLangParser::Lib_commandContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Lib_commandContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> rexLangParser::Lib_commandContext::STRING_LITERAL() {
  return getTokens(rexLangParser::STRING_LITERAL);
}

tree::TerminalNode* rexLangParser::Lib_commandContext::STRING_LITERAL(size_t i) {
  return getToken(rexLangParser::STRING_LITERAL, i);
}

rexLangParser::Parameter_decl_listContext* rexLangParser::Lib_commandContext::parameter_decl_list() {
  return getRuleContext<rexLangParser::Parameter_decl_listContext>(0);
}

rexLangParser::Table_commentContext* rexLangParser::Lib_commandContext::table_comment() {
  return getRuleContext<rexLangParser::Table_commentContext>(0);
}


size_t rexLangParser::Lib_commandContext::getRuleIndex() const {
  return rexLangParser::RuleLib_command;
}

void rexLangParser::Lib_commandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLib_command(this);
}

void rexLangParser::Lib_commandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLib_command(this);
}


antlrcpp::Any rexLangParser::Lib_commandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitLib_command(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Lib_commandContext* rexLangParser::lib_command() {
  Lib_commandContext *_localctx = _tracker.createInstance<Lib_commandContext>(_ctx, getState());
  enterRule(_localctx, 14, rexLangParser::RuleLib_command);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(169);
    match(rexLangParser::T__3);
    setState(170);
    dynamic_cast<Lib_commandContext *>(_localctx)->name = match(rexLangParser::IDENTIFIER);
    setState(171);
    match(rexLangParser::T__2);
    setState(173);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::IDENTIFIER) {
      setState(172);
      dynamic_cast<Lib_commandContext *>(_localctx)->type = match(rexLangParser::IDENTIFIER);
    }
    setState(175);
    match(rexLangParser::T__2);
    setState(177);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::STRING_LITERAL) {
      setState(176);
      dynamic_cast<Lib_commandContext *>(_localctx)->file = match(rexLangParser::STRING_LITERAL);
    }
    setState(179);
    match(rexLangParser::T__2);
    setState(180);
    dynamic_cast<Lib_commandContext *>(_localctx)->cmd = match(rexLangParser::STRING_LITERAL);
    setState(181);
    match(rexLangParser::T__2);
    setState(185);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::IDENTIFIER) {
      setState(182);
      dynamic_cast<Lib_commandContext *>(_localctx)->identifierToken = match(rexLangParser::IDENTIFIER);
      dynamic_cast<Lib_commandContext *>(_localctx)->attributes.push_back(dynamic_cast<Lib_commandContext *>(_localctx)->identifierToken);
      setState(187);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(190);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__2) {
      setState(188);
      match(rexLangParser::T__2);
      setState(189);
      table_comment();
    }
    setState(192);
    match(rexLangParser::NEWLINE);
    setState(193);
    dynamic_cast<Lib_commandContext *>(_localctx)->params = parameter_decl_list();
    setState(197);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(194);
        match(rexLangParser::NEWLINE); 
      }
      setState(199);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
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

rexLangParser::Global_variable_listContext::Global_variable_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<rexLangParser::Global_variable_itemContext *> rexLangParser::Global_variable_listContext::global_variable_item() {
  return getRuleContexts<rexLangParser::Global_variable_itemContext>();
}

rexLangParser::Global_variable_itemContext* rexLangParser::Global_variable_listContext::global_variable_item(size_t i) {
  return getRuleContext<rexLangParser::Global_variable_itemContext>(i);
}


size_t rexLangParser::Global_variable_listContext::getRuleIndex() const {
  return rexLangParser::RuleGlobal_variable_list;
}

void rexLangParser::Global_variable_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_variable_list(this);
}

void rexLangParser::Global_variable_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_variable_list(this);
}


antlrcpp::Any rexLangParser::Global_variable_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitGlobal_variable_list(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Global_variable_listContext* rexLangParser::global_variable_list() {
  Global_variable_listContext *_localctx = _tracker.createInstance<Global_variable_listContext>(_ctx, getState());
  enterRule(_localctx, 16, rexLangParser::RuleGlobal_variable_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::T__4) {
      setState(200);
      global_variable_item();
      setState(205);
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

rexLangParser::Global_variable_itemContext::Global_variable_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* rexLangParser::Global_variable_itemContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}

std::vector<tree::TerminalNode *> rexLangParser::Global_variable_itemContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Global_variable_itemContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}

rexLangParser::Table_commentContext* rexLangParser::Global_variable_itemContext::table_comment() {
  return getRuleContext<rexLangParser::Table_commentContext>(0);
}

tree::TerminalNode* rexLangParser::Global_variable_itemContext::STRING_LITERAL() {
  return getToken(rexLangParser::STRING_LITERAL, 0);
}


size_t rexLangParser::Global_variable_itemContext::getRuleIndex() const {
  return rexLangParser::RuleGlobal_variable_item;
}

void rexLangParser::Global_variable_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_variable_item(this);
}

void rexLangParser::Global_variable_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_variable_item(this);
}


antlrcpp::Any rexLangParser::Global_variable_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitGlobal_variable_item(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Global_variable_itemContext* rexLangParser::global_variable_item() {
  Global_variable_itemContext *_localctx = _tracker.createInstance<Global_variable_itemContext>(_ctx, getState());
  enterRule(_localctx, 18, rexLangParser::RuleGlobal_variable_item);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(206);
    match(rexLangParser::T__4);
    setState(207);
    dynamic_cast<Global_variable_itemContext *>(_localctx)->name = match(rexLangParser::IDENTIFIER);
    setState(228);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__2) {
      setState(208);
      match(rexLangParser::T__2);
      setState(210);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::IDENTIFIER) {
        setState(209);
        dynamic_cast<Global_variable_itemContext *>(_localctx)->type = match(rexLangParser::IDENTIFIER);
      }
      setState(226);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__2) {
        setState(212);
        match(rexLangParser::T__2);
        setState(214);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::IDENTIFIER) {
          setState(213);
          dynamic_cast<Global_variable_itemContext *>(_localctx)->access = match(rexLangParser::IDENTIFIER);
        }
        setState(224);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::T__2) {
          setState(216);
          match(rexLangParser::T__2);
          setState(218);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == rexLangParser::STRING_LITERAL) {
            setState(217);
            dynamic_cast<Global_variable_itemContext *>(_localctx)->dimension = match(rexLangParser::STRING_LITERAL);
          }
          setState(222);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == rexLangParser::T__2) {
            setState(220);
            match(rexLangParser::T__2);
            setState(221);
            table_comment();
          }
        }
      }
    }
    setState(230);
    match(rexLangParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Edition_specContext ------------------------------------------------------------------

rexLangParser::Edition_specContext::Edition_specContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* rexLangParser::Edition_specContext::INTEGER_LITERAL() {
  return getToken(rexLangParser::INTEGER_LITERAL, 0);
}

tree::TerminalNode* rexLangParser::Edition_specContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}


size_t rexLangParser::Edition_specContext::getRuleIndex() const {
  return rexLangParser::RuleEdition_spec;
}

void rexLangParser::Edition_specContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdition_spec(this);
}

void rexLangParser::Edition_specContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdition_spec(this);
}


antlrcpp::Any rexLangParser::Edition_specContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitEdition_spec(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Edition_specContext* rexLangParser::edition_spec() {
  Edition_specContext *_localctx = _tracker.createInstance<Edition_specContext>(_ctx, getState());
  enterRule(_localctx, 20, rexLangParser::RuleEdition_spec);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(232);
    match(rexLangParser::T__5);
    setState(233);
    match(rexLangParser::INTEGER_LITERAL);
    setState(234);
    match(rexLangParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_declareContext ------------------------------------------------------------------

rexLangParser::Struct_declareContext::Struct_declareContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> rexLangParser::Struct_declareContext::NEWLINE() {
  return getTokens(rexLangParser::NEWLINE);
}

tree::TerminalNode* rexLangParser::Struct_declareContext::NEWLINE(size_t i) {
  return getToken(rexLangParser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> rexLangParser::Struct_declareContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Struct_declareContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}

std::vector<rexLangParser::Member_vari_declContext *> rexLangParser::Struct_declareContext::member_vari_decl() {
  return getRuleContexts<rexLangParser::Member_vari_declContext>();
}

rexLangParser::Member_vari_declContext* rexLangParser::Struct_declareContext::member_vari_decl(size_t i) {
  return getRuleContext<rexLangParser::Member_vari_declContext>(i);
}

rexLangParser::Table_commentContext* rexLangParser::Struct_declareContext::table_comment() {
  return getRuleContext<rexLangParser::Table_commentContext>(0);
}


size_t rexLangParser::Struct_declareContext::getRuleIndex() const {
  return rexLangParser::RuleStruct_declare;
}

void rexLangParser::Struct_declareContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_declare(this);
}

void rexLangParser::Struct_declareContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_declare(this);
}


antlrcpp::Any rexLangParser::Struct_declareContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitStruct_declare(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Struct_declareContext* rexLangParser::struct_declare() {
  Struct_declareContext *_localctx = _tracker.createInstance<Struct_declareContext>(_ctx, getState());
  enterRule(_localctx, 22, rexLangParser::RuleStruct_declare);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(236);
    match(rexLangParser::T__6);
    setState(237);
    dynamic_cast<Struct_declareContext *>(_localctx)->name = match(rexLangParser::IDENTIFIER);
    setState(246);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__2) {
      setState(238);
      match(rexLangParser::T__2);
      setState(240);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::IDENTIFIER) {
        setState(239);
        dynamic_cast<Struct_declareContext *>(_localctx)->access = match(rexLangParser::IDENTIFIER);
      }
      setState(244);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__2) {
        setState(242);
        match(rexLangParser::T__2);
        setState(243);
        table_comment();
      }
    }
    setState(248);
    match(rexLangParser::NEWLINE);
    setState(253);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::T__7) {
      setState(249);
      match(rexLangParser::T__7);
      setState(250);
      dynamic_cast<Struct_declareContext *>(_localctx)->member_vari_declContext = member_vari_decl();
      dynamic_cast<Struct_declareContext *>(_localctx)->struct_mems.push_back(dynamic_cast<Struct_declareContext *>(_localctx)->member_vari_declContext);
      setState(255);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(259);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(256);
        match(rexLangParser::NEWLINE); 
      }
      setState(261);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
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

rexLangParser::Table_commentContext::Table_commentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t rexLangParser::Table_commentContext::getRuleIndex() const {
  return rexLangParser::RuleTable_comment;
}

void rexLangParser::Table_commentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTable_comment(this);
}

void rexLangParser::Table_commentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTable_comment(this);
}


antlrcpp::Any rexLangParser::Table_commentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitTable_comment(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Table_commentContext* rexLangParser::table_comment() {
  Table_commentContext *_localctx = _tracker.createInstance<Table_commentContext>(_ctx, getState());
  enterRule(_localctx, 24, rexLangParser::RuleTable_comment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(265);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(262);
        dynamic_cast<Table_commentContext *>(_localctx)->comment = matchWildcard(); 
      }
      setState(267);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
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

rexLangParser::Prog_setContext::Prog_setContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> rexLangParser::Prog_setContext::NEWLINE() {
  return getTokens(rexLangParser::NEWLINE);
}

tree::TerminalNode* rexLangParser::Prog_setContext::NEWLINE(size_t i) {
  return getToken(rexLangParser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> rexLangParser::Prog_setContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Prog_setContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}

std::vector<rexLangParser::File_vari_declContext *> rexLangParser::Prog_setContext::file_vari_decl() {
  return getRuleContexts<rexLangParser::File_vari_declContext>();
}

rexLangParser::File_vari_declContext* rexLangParser::Prog_setContext::file_vari_decl(size_t i) {
  return getRuleContext<rexLangParser::File_vari_declContext>(i);
}

std::vector<rexLangParser::Sub_programContext *> rexLangParser::Prog_setContext::sub_program() {
  return getRuleContexts<rexLangParser::Sub_programContext>();
}

rexLangParser::Sub_programContext* rexLangParser::Prog_setContext::sub_program(size_t i) {
  return getRuleContext<rexLangParser::Sub_programContext>(i);
}

rexLangParser::Table_commentContext* rexLangParser::Prog_setContext::table_comment() {
  return getRuleContext<rexLangParser::Table_commentContext>(0);
}


size_t rexLangParser::Prog_setContext::getRuleIndex() const {
  return rexLangParser::RuleProg_set;
}

void rexLangParser::Prog_setContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg_set(this);
}

void rexLangParser::Prog_setContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg_set(this);
}


antlrcpp::Any rexLangParser::Prog_setContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitProg_set(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Prog_setContext* rexLangParser::prog_set() {
  Prog_setContext *_localctx = _tracker.createInstance<Prog_setContext>(_ctx, getState());
  enterRule(_localctx, 26, rexLangParser::RuleProg_set);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(268);
    match(rexLangParser::T__8);
    setState(269);
    dynamic_cast<Prog_setContext *>(_localctx)->name = match(rexLangParser::IDENTIFIER);
    setState(284);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__2) {
      setState(270);
      match(rexLangParser::T__2);
      setState(272);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::IDENTIFIER) {
        setState(271);
        dynamic_cast<Prog_setContext *>(_localctx)->base = match(rexLangParser::IDENTIFIER);
      }
      setState(282);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__2) {
        setState(274);
        match(rexLangParser::T__2);
        setState(276);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::IDENTIFIER) {
          setState(275);
          dynamic_cast<Prog_setContext *>(_localctx)->access = match(rexLangParser::IDENTIFIER);
        }
        setState(280);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::T__2) {
          setState(278);
          match(rexLangParser::T__2);
          setState(279);
          table_comment();
        }
      }
    }
    setState(286);
    match(rexLangParser::NEWLINE);
    setState(291);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::T__9) {
      setState(287);
      match(rexLangParser::T__9);
      setState(288);
      dynamic_cast<Prog_setContext *>(_localctx)->file_vari_declContext = file_vari_decl();
      dynamic_cast<Prog_setContext *>(_localctx)->prog_set_varis.push_back(dynamic_cast<Prog_setContext *>(_localctx)->file_vari_declContext);
      setState(293);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(309);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(297);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == rexLangParser::NEWLINE) {
          setState(294);
          match(rexLangParser::NEWLINE);
          setState(299);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(300);
        dynamic_cast<Prog_setContext *>(_localctx)->sub_programContext = sub_program();
        dynamic_cast<Prog_setContext *>(_localctx)->functions.push_back(dynamic_cast<Prog_setContext *>(_localctx)->sub_programContext);
        setState(304);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(301);
            match(rexLangParser::NEWLINE); 
          }
          setState(306);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
        } 
      }
      setState(311);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
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

rexLangParser::Variable_declContext::Variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* rexLangParser::Variable_declContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}

std::vector<tree::TerminalNode *> rexLangParser::Variable_declContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Variable_declContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}

rexLangParser::Table_commentContext* rexLangParser::Variable_declContext::table_comment() {
  return getRuleContext<rexLangParser::Table_commentContext>(0);
}

tree::TerminalNode* rexLangParser::Variable_declContext::STRING_LITERAL() {
  return getToken(rexLangParser::STRING_LITERAL, 0);
}


size_t rexLangParser::Variable_declContext::getRuleIndex() const {
  return rexLangParser::RuleVariable_decl;
}

void rexLangParser::Variable_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable_decl(this);
}

void rexLangParser::Variable_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable_decl(this);
}


antlrcpp::Any rexLangParser::Variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitVariable_decl(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Variable_declContext* rexLangParser::variable_decl() {
  Variable_declContext *_localctx = _tracker.createInstance<Variable_declContext>(_ctx, getState());
  enterRule(_localctx, 28, rexLangParser::RuleVariable_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
    dynamic_cast<Variable_declContext *>(_localctx)->name = match(rexLangParser::IDENTIFIER);
    setState(334);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__2) {
      setState(313);
      match(rexLangParser::T__2);
      setState(315);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::IDENTIFIER) {
        setState(314);
        dynamic_cast<Variable_declContext *>(_localctx)->type = match(rexLangParser::IDENTIFIER);
      }
      setState(332);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__2) {
        setState(317);
        match(rexLangParser::T__2);
        setState(321);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == rexLangParser::IDENTIFIER) {
          setState(318);
          dynamic_cast<Variable_declContext *>(_localctx)->identifierToken = match(rexLangParser::IDENTIFIER);
          dynamic_cast<Variable_declContext *>(_localctx)->attributes.push_back(dynamic_cast<Variable_declContext *>(_localctx)->identifierToken);
          setState(323);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(324);
        match(rexLangParser::T__2);
        setState(326);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::STRING_LITERAL) {
          setState(325);
          dynamic_cast<Variable_declContext *>(_localctx)->dimension = match(rexLangParser::STRING_LITERAL);
        }
        setState(330);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::T__2) {
          setState(328);
          match(rexLangParser::T__2);
          setState(329);
          table_comment();
        }
      }
    }
    setState(336);
    match(rexLangParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Member_vari_declContext ------------------------------------------------------------------

rexLangParser::Member_vari_declContext::Member_vari_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

rexLangParser::Variable_declContext* rexLangParser::Member_vari_declContext::variable_decl() {
  return getRuleContext<rexLangParser::Variable_declContext>(0);
}


size_t rexLangParser::Member_vari_declContext::getRuleIndex() const {
  return rexLangParser::RuleMember_vari_decl;
}

void rexLangParser::Member_vari_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMember_vari_decl(this);
}

void rexLangParser::Member_vari_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMember_vari_decl(this);
}


antlrcpp::Any rexLangParser::Member_vari_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitMember_vari_decl(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Member_vari_declContext* rexLangParser::member_vari_decl() {
  Member_vari_declContext *_localctx = _tracker.createInstance<Member_vari_declContext>(_ctx, getState());
  enterRule(_localctx, 30, rexLangParser::RuleMember_vari_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(338);
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

rexLangParser::File_vari_declContext::File_vari_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

rexLangParser::Variable_declContext* rexLangParser::File_vari_declContext::variable_decl() {
  return getRuleContext<rexLangParser::Variable_declContext>(0);
}


size_t rexLangParser::File_vari_declContext::getRuleIndex() const {
  return rexLangParser::RuleFile_vari_decl;
}

void rexLangParser::File_vari_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile_vari_decl(this);
}

void rexLangParser::File_vari_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile_vari_decl(this);
}


antlrcpp::Any rexLangParser::File_vari_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitFile_vari_decl(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::File_vari_declContext* rexLangParser::file_vari_decl() {
  File_vari_declContext *_localctx = _tracker.createInstance<File_vari_declContext>(_ctx, getState());
  enterRule(_localctx, 32, rexLangParser::RuleFile_vari_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(340);
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

rexLangParser::Sub_programContext::Sub_programContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* rexLangParser::Sub_programContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}

rexLangParser::Statement_listContext* rexLangParser::Sub_programContext::statement_list() {
  return getRuleContext<rexLangParser::Statement_listContext>(0);
}

std::vector<tree::TerminalNode *> rexLangParser::Sub_programContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Sub_programContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}

rexLangParser::Parameter_decl_listContext* rexLangParser::Sub_programContext::parameter_decl_list() {
  return getRuleContext<rexLangParser::Parameter_decl_listContext>(0);
}

std::vector<rexLangParser::Local_variable_declContext *> rexLangParser::Sub_programContext::local_variable_decl() {
  return getRuleContexts<rexLangParser::Local_variable_declContext>();
}

rexLangParser::Local_variable_declContext* rexLangParser::Sub_programContext::local_variable_decl(size_t i) {
  return getRuleContext<rexLangParser::Local_variable_declContext>(i);
}

rexLangParser::Table_commentContext* rexLangParser::Sub_programContext::table_comment() {
  return getRuleContext<rexLangParser::Table_commentContext>(0);
}


size_t rexLangParser::Sub_programContext::getRuleIndex() const {
  return rexLangParser::RuleSub_program;
}

void rexLangParser::Sub_programContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSub_program(this);
}

void rexLangParser::Sub_programContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSub_program(this);
}


antlrcpp::Any rexLangParser::Sub_programContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitSub_program(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Sub_programContext* rexLangParser::sub_program() {
  Sub_programContext *_localctx = _tracker.createInstance<Sub_programContext>(_ctx, getState());
  enterRule(_localctx, 34, rexLangParser::RuleSub_program);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(342);
    match(rexLangParser::T__10);
    setState(343);
    dynamic_cast<Sub_programContext *>(_localctx)->name = match(rexLangParser::IDENTIFIER);
    setState(358);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__2) {
      setState(344);
      match(rexLangParser::T__2);
      setState(346);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::IDENTIFIER) {
        setState(345);
        dynamic_cast<Sub_programContext *>(_localctx)->type = match(rexLangParser::IDENTIFIER);
      }
      setState(356);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__2) {
        setState(348);
        match(rexLangParser::T__2);
        setState(350);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::IDENTIFIER) {
          setState(349);
          dynamic_cast<Sub_programContext *>(_localctx)->access = match(rexLangParser::IDENTIFIER);
        }
        setState(354);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::T__2) {
          setState(352);
          match(rexLangParser::T__2);
          setState(353);
          table_comment();
        }
      }
    }
    setState(360);
    match(rexLangParser::NEWLINE);
    setState(361);
    dynamic_cast<Sub_programContext *>(_localctx)->params = parameter_decl_list();
    setState(365);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::T__12) {
      setState(362);
      dynamic_cast<Sub_programContext *>(_localctx)->local_variable_declContext = local_variable_decl();
      dynamic_cast<Sub_programContext *>(_localctx)->local_vari.push_back(dynamic_cast<Sub_programContext *>(_localctx)->local_variable_declContext);
      setState(367);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(368);
    statement_list();
    setState(370);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__11) {
      setState(369);
      match(rexLangParser::T__11);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Local_variable_declContext ------------------------------------------------------------------

rexLangParser::Local_variable_declContext::Local_variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* rexLangParser::Local_variable_declContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}

std::vector<tree::TerminalNode *> rexLangParser::Local_variable_declContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Local_variable_declContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}

rexLangParser::Table_commentContext* rexLangParser::Local_variable_declContext::table_comment() {
  return getRuleContext<rexLangParser::Table_commentContext>(0);
}

tree::TerminalNode* rexLangParser::Local_variable_declContext::STRING_LITERAL() {
  return getToken(rexLangParser::STRING_LITERAL, 0);
}


size_t rexLangParser::Local_variable_declContext::getRuleIndex() const {
  return rexLangParser::RuleLocal_variable_decl;
}

void rexLangParser::Local_variable_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocal_variable_decl(this);
}

void rexLangParser::Local_variable_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocal_variable_decl(this);
}


antlrcpp::Any rexLangParser::Local_variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitLocal_variable_decl(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Local_variable_declContext* rexLangParser::local_variable_decl() {
  Local_variable_declContext *_localctx = _tracker.createInstance<Local_variable_declContext>(_ctx, getState());
  enterRule(_localctx, 36, rexLangParser::RuleLocal_variable_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(372);
    match(rexLangParser::T__12);
    setState(373);
    dynamic_cast<Local_variable_declContext *>(_localctx)->name = match(rexLangParser::IDENTIFIER);
    setState(394);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__2) {
      setState(374);
      match(rexLangParser::T__2);
      setState(376);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::IDENTIFIER) {
        setState(375);
        dynamic_cast<Local_variable_declContext *>(_localctx)->type = match(rexLangParser::IDENTIFIER);
      }
      setState(392);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__2) {
        setState(378);
        match(rexLangParser::T__2);
        setState(380);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::IDENTIFIER) {
          setState(379);
          dynamic_cast<Local_variable_declContext *>(_localctx)->attribute = match(rexLangParser::IDENTIFIER);
        }
        setState(390);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::T__2) {
          setState(382);
          match(rexLangParser::T__2);
          setState(384);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == rexLangParser::STRING_LITERAL) {
            setState(383);
            dynamic_cast<Local_variable_declContext *>(_localctx)->dimension = match(rexLangParser::STRING_LITERAL);
          }
          setState(388);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == rexLangParser::T__2) {
            setState(386);
            match(rexLangParser::T__2);
            setState(387);
            table_comment();
          }
        }
      }
    }
    setState(396);
    match(rexLangParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Parameter_decl_listContext ------------------------------------------------------------------

rexLangParser::Parameter_decl_listContext::Parameter_decl_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<rexLangParser::Parameter_declContext *> rexLangParser::Parameter_decl_listContext::parameter_decl() {
  return getRuleContexts<rexLangParser::Parameter_declContext>();
}

rexLangParser::Parameter_declContext* rexLangParser::Parameter_decl_listContext::parameter_decl(size_t i) {
  return getRuleContext<rexLangParser::Parameter_declContext>(i);
}

rexLangParser::Vari_parameter_declContext* rexLangParser::Parameter_decl_listContext::vari_parameter_decl() {
  return getRuleContext<rexLangParser::Vari_parameter_declContext>(0);
}


size_t rexLangParser::Parameter_decl_listContext::getRuleIndex() const {
  return rexLangParser::RuleParameter_decl_list;
}

void rexLangParser::Parameter_decl_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter_decl_list(this);
}

void rexLangParser::Parameter_decl_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter_decl_list(this);
}


antlrcpp::Any rexLangParser::Parameter_decl_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitParameter_decl_list(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Parameter_decl_listContext* rexLangParser::parameter_decl_list() {
  Parameter_decl_listContext *_localctx = _tracker.createInstance<Parameter_decl_listContext>(_ctx, getState());
  enterRule(_localctx, 38, rexLangParser::RuleParameter_decl_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(401);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(398);
        parameter_decl(); 
      }
      setState(403);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
    }
    setState(405);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__13) {
      setState(404);
      vari_parameter_decl();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Parameter_declContext ------------------------------------------------------------------

rexLangParser::Parameter_declContext::Parameter_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* rexLangParser::Parameter_declContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}

std::vector<tree::TerminalNode *> rexLangParser::Parameter_declContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Parameter_declContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}

rexLangParser::Table_commentContext* rexLangParser::Parameter_declContext::table_comment() {
  return getRuleContext<rexLangParser::Table_commentContext>(0);
}


size_t rexLangParser::Parameter_declContext::getRuleIndex() const {
  return rexLangParser::RuleParameter_decl;
}

void rexLangParser::Parameter_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter_decl(this);
}

void rexLangParser::Parameter_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter_decl(this);
}


antlrcpp::Any rexLangParser::Parameter_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitParameter_decl(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Parameter_declContext* rexLangParser::parameter_decl() {
  Parameter_declContext *_localctx = _tracker.createInstance<Parameter_declContext>(_ctx, getState());
  enterRule(_localctx, 40, rexLangParser::RuleParameter_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(407);
    match(rexLangParser::T__13);
    setState(408);
    dynamic_cast<Parameter_declContext *>(_localctx)->name = match(rexLangParser::IDENTIFIER);
    setState(409);
    match(rexLangParser::T__2);
    setState(410);
    dynamic_cast<Parameter_declContext *>(_localctx)->type = match(rexLangParser::IDENTIFIER);
    setState(422);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__2) {
      setState(411);
      match(rexLangParser::T__2);
      setState(415);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == rexLangParser::IDENTIFIER) {
        setState(412);
        dynamic_cast<Parameter_declContext *>(_localctx)->identifierToken = match(rexLangParser::IDENTIFIER);
        dynamic_cast<Parameter_declContext *>(_localctx)->attributes.push_back(dynamic_cast<Parameter_declContext *>(_localctx)->identifierToken);
        setState(417);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(420);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__2) {
        setState(418);
        match(rexLangParser::T__2);
        setState(419);
        table_comment();
      }
    }
    setState(424);
    match(rexLangParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Vari_parameter_declContext ------------------------------------------------------------------

rexLangParser::Vari_parameter_declContext::Vari_parameter_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* rexLangParser::Vari_parameter_declContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}

std::vector<tree::TerminalNode *> rexLangParser::Vari_parameter_declContext::IDENTIFIER() {
  return getTokens(rexLangParser::IDENTIFIER);
}

tree::TerminalNode* rexLangParser::Vari_parameter_declContext::IDENTIFIER(size_t i) {
  return getToken(rexLangParser::IDENTIFIER, i);
}

rexLangParser::Table_commentContext* rexLangParser::Vari_parameter_declContext::table_comment() {
  return getRuleContext<rexLangParser::Table_commentContext>(0);
}


size_t rexLangParser::Vari_parameter_declContext::getRuleIndex() const {
  return rexLangParser::RuleVari_parameter_decl;
}

void rexLangParser::Vari_parameter_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVari_parameter_decl(this);
}

void rexLangParser::Vari_parameter_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVari_parameter_decl(this);
}


antlrcpp::Any rexLangParser::Vari_parameter_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitVari_parameter_decl(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Vari_parameter_declContext* rexLangParser::vari_parameter_decl() {
  Vari_parameter_declContext *_localctx = _tracker.createInstance<Vari_parameter_declContext>(_ctx, getState());
  enterRule(_localctx, 42, rexLangParser::RuleVari_parameter_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(426);
    match(rexLangParser::T__13);
    setState(427);
    dynamic_cast<Vari_parameter_declContext *>(_localctx)->name = match(rexLangParser::T__14);
    setState(428);
    match(rexLangParser::T__2);
    setState(429);
    dynamic_cast<Vari_parameter_declContext *>(_localctx)->type = match(rexLangParser::IDENTIFIER);
    setState(441);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == rexLangParser::T__2) {
      setState(430);
      match(rexLangParser::T__2);
      setState(434);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == rexLangParser::IDENTIFIER) {
        setState(431);
        dynamic_cast<Vari_parameter_declContext *>(_localctx)->identifierToken = match(rexLangParser::IDENTIFIER);
        dynamic_cast<Vari_parameter_declContext *>(_localctx)->attributes.push_back(dynamic_cast<Vari_parameter_declContext *>(_localctx)->identifierToken);
        setState(436);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(439);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__2) {
        setState(437);
        match(rexLangParser::T__2);
        setState(438);
        table_comment();
      }
    }
    setState(443);
    match(rexLangParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Statement_listContext ------------------------------------------------------------------

rexLangParser::Statement_listContext::Statement_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> rexLangParser::Statement_listContext::NEWLINE() {
  return getTokens(rexLangParser::NEWLINE);
}

tree::TerminalNode* rexLangParser::Statement_listContext::NEWLINE(size_t i) {
  return getToken(rexLangParser::NEWLINE, i);
}

std::vector<rexLangParser::StatementContext *> rexLangParser::Statement_listContext::statement() {
  return getRuleContexts<rexLangParser::StatementContext>();
}

rexLangParser::StatementContext* rexLangParser::Statement_listContext::statement(size_t i) {
  return getRuleContext<rexLangParser::StatementContext>(i);
}


size_t rexLangParser::Statement_listContext::getRuleIndex() const {
  return rexLangParser::RuleStatement_list;
}

void rexLangParser::Statement_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement_list(this);
}

void rexLangParser::Statement_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement_list(this);
}


antlrcpp::Any rexLangParser::Statement_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitStatement_list(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Statement_listContext* rexLangParser::statement_list() {
  Statement_listContext *_localctx = _tracker.createInstance<Statement_listContext>(_ctx, getState());
  enterRule(_localctx, 44, rexLangParser::RuleStatement_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(451);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(446);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 16) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 16)) & ((1ULL << (rexLangParser::T__15 - 16))
          | (1ULL << (rexLangParser::T__16 - 16))
          | (1ULL << (rexLangParser::T__21 - 16))
          | (1ULL << (rexLangParser::T__23 - 16))
          | (1ULL << (rexLangParser::T__25 - 16))
          | (1ULL << (rexLangParser::T__27 - 16))
          | (1ULL << (rexLangParser::T__29 - 16))
          | (1ULL << (rexLangParser::T__32 - 16))
          | (1ULL << (rexLangParser::T__34 - 16))
          | (1ULL << (rexLangParser::T__35 - 16))
          | (1ULL << (rexLangParser::T__36 - 16))
          | (1ULL << (rexLangParser::T__37 - 16))
          | (1ULL << (rexLangParser::T__39 - 16))
          | (1ULL << (rexLangParser::T__41 - 16))
          | (1ULL << (rexLangParser::T__52 - 16))
          | (1ULL << (rexLangParser::T__53 - 16))
          | (1ULL << (rexLangParser::T__54 - 16))
          | (1ULL << (rexLangParser::T__55 - 16))
          | (1ULL << (rexLangParser::K_SUB_OPT - 16))
          | (1ULL << (rexLangParser::INTEGER_LITERAL - 16))
          | (1ULL << (rexLangParser::FLOAT_LITERAL - 16))
          | (1ULL << (rexLangParser::IDENTIFIER - 16))
          | (1ULL << (rexLangParser::STRING_LITERAL - 16)))) != 0)) {
          setState(445);
          dynamic_cast<Statement_listContext *>(_localctx)->statementContext = statement();
          dynamic_cast<Statement_listContext *>(_localctx)->stmts.push_back(dynamic_cast<Statement_listContext *>(_localctx)->statementContext);
        }
        setState(448);
        match(rexLangParser::NEWLINE); 
      }
      setState(453);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
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

rexLangParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t rexLangParser::StatementContext::getRuleIndex() const {
  return rexLangParser::RuleStatement;
}

void rexLangParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SwitchStatementContext ------------------------------------------------------------------

rexLangParser::Switch_statementContext* rexLangParser::SwitchStatementContext::switch_statement() {
  return getRuleContext<rexLangParser::Switch_statementContext>(0);
}

rexLangParser::SwitchStatementContext::SwitchStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void rexLangParser::SwitchStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitchStatement(this);
}
void rexLangParser::SwitchStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitchStatement(this);
}

antlrcpp::Any rexLangParser::SwitchStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitSwitchStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpressionStatementContext ------------------------------------------------------------------

rexLangParser::ExpressionContext* rexLangParser::ExpressionStatementContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

rexLangParser::ExpressionStatementContext::ExpressionStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void rexLangParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}
void rexLangParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}

antlrcpp::Any rexLangParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ControlStatementContext ------------------------------------------------------------------

rexLangParser::Control_statementContext* rexLangParser::ControlStatementContext::control_statement() {
  return getRuleContext<rexLangParser::Control_statementContext>(0);
}

rexLangParser::ControlStatementContext::ControlStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void rexLangParser::ControlStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterControlStatement(this);
}
void rexLangParser::ControlStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitControlStatement(this);
}

antlrcpp::Any rexLangParser::ControlStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitControlStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConditionStatementContext ------------------------------------------------------------------

rexLangParser::Condition_statementContext* rexLangParser::ConditionStatementContext::condition_statement() {
  return getRuleContext<rexLangParser::Condition_statementContext>(0);
}

rexLangParser::ConditionStatementContext::ConditionStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void rexLangParser::ConditionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionStatement(this);
}
void rexLangParser::ConditionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionStatement(this);
}

antlrcpp::Any rexLangParser::ConditionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitConditionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LoopStatementContext ------------------------------------------------------------------

rexLangParser::Loop_statementContext* rexLangParser::LoopStatementContext::loop_statement() {
  return getRuleContext<rexLangParser::Loop_statementContext>(0);
}

rexLangParser::LoopStatementContext::LoopStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void rexLangParser::LoopStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoopStatement(this);
}
void rexLangParser::LoopStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoopStatement(this);
}

antlrcpp::Any rexLangParser::LoopStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitLoopStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStatementContext ------------------------------------------------------------------

rexLangParser::Hierarchy_identifierContext* rexLangParser::AssignStatementContext::hierarchy_identifier() {
  return getRuleContext<rexLangParser::Hierarchy_identifierContext>(0);
}

rexLangParser::ExpressionContext* rexLangParser::AssignStatementContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

tree::TerminalNode* rexLangParser::AssignStatementContext::K_ASSIGN_OPT() {
  return getToken(rexLangParser::K_ASSIGN_OPT, 0);
}

tree::TerminalNode* rexLangParser::AssignStatementContext::K_AECOM_OPT() {
  return getToken(rexLangParser::K_AECOM_OPT, 0);
}

rexLangParser::AssignStatementContext::AssignStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void rexLangParser::AssignStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignStatement(this);
}
void rexLangParser::AssignStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignStatement(this);
}

antlrcpp::Any rexLangParser::AssignStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitAssignStatement(this);
  else
    return visitor->visitChildren(this);
}
rexLangParser::StatementContext* rexLangParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 46, rexLangParser::RuleStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(463);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<rexLangParser::ConditionStatementContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(454);
      condition_statement();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<rexLangParser::AssignStatementContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(455);
      hierarchy_identifier();
      setState(456);
      _la = _input->LA(1);
      if (!(_la == rexLangParser::K_AECOM_OPT

      || _la == rexLangParser::K_ASSIGN_OPT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(457);
      expression(0);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<rexLangParser::ExpressionStatementContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(459);
      expression(0);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<rexLangParser::LoopStatementContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(460);
      loop_statement();
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<rexLangParser::SwitchStatementContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(461);
      switch_statement();
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<rexLangParser::ControlStatementContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(462);
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

rexLangParser::Switch_statementContext::Switch_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> rexLangParser::Switch_statementContext::NEWLINE() {
  return getTokens(rexLangParser::NEWLINE);
}

tree::TerminalNode* rexLangParser::Switch_statementContext::NEWLINE(size_t i) {
  return getToken(rexLangParser::NEWLINE, i);
}

std::vector<rexLangParser::ExpressionContext *> rexLangParser::Switch_statementContext::expression() {
  return getRuleContexts<rexLangParser::ExpressionContext>();
}

rexLangParser::ExpressionContext* rexLangParser::Switch_statementContext::expression(size_t i) {
  return getRuleContext<rexLangParser::ExpressionContext>(i);
}

std::vector<rexLangParser::Statement_listContext *> rexLangParser::Switch_statementContext::statement_list() {
  return getRuleContexts<rexLangParser::Statement_listContext>();
}

rexLangParser::Statement_listContext* rexLangParser::Switch_statementContext::statement_list(size_t i) {
  return getRuleContext<rexLangParser::Statement_listContext>(i);
}


size_t rexLangParser::Switch_statementContext::getRuleIndex() const {
  return rexLangParser::RuleSwitch_statement;
}

void rexLangParser::Switch_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitch_statement(this);
}

void rexLangParser::Switch_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitch_statement(this);
}


antlrcpp::Any rexLangParser::Switch_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitSwitch_statement(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Switch_statementContext* rexLangParser::switch_statement() {
  Switch_statementContext *_localctx = _tracker.createInstance<Switch_statementContext>(_ctx, getState());
  enterRule(_localctx, 48, rexLangParser::RuleSwitch_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(465);
    match(rexLangParser::T__15);
    setState(466);
    match(rexLangParser::T__16);
    setState(467);
    dynamic_cast<Switch_statementContext *>(_localctx)->major_condition_expr = expression(0);
    setState(468);
    match(rexLangParser::T__17);
    setState(469);
    match(rexLangParser::NEWLINE);
    setState(470);
    dynamic_cast<Switch_statementContext *>(_localctx)->major_cond_body = statement_list();
    setState(480);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == rexLangParser::T__18) {
      setState(471);
      match(rexLangParser::T__18);
      setState(472);
      match(rexLangParser::T__16);
      setState(473);
      dynamic_cast<Switch_statementContext *>(_localctx)->expressionContext = expression(0);
      dynamic_cast<Switch_statementContext *>(_localctx)->minor_condition_expr.push_back(dynamic_cast<Switch_statementContext *>(_localctx)->expressionContext);
      setState(474);
      match(rexLangParser::T__17);
      setState(475);
      match(rexLangParser::NEWLINE);
      setState(476);
      dynamic_cast<Switch_statementContext *>(_localctx)->statement_listContext = statement_list();
      dynamic_cast<Switch_statementContext *>(_localctx)->minor_cond_body.push_back(dynamic_cast<Switch_statementContext *>(_localctx)->statement_listContext);
      setState(482);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(483);
    match(rexLangParser::T__19);
    setState(484);
    match(rexLangParser::NEWLINE);
    setState(485);
    dynamic_cast<Switch_statementContext *>(_localctx)->default_body = statement_list();
    setState(486);
    match(rexLangParser::T__20);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Loop_statementContext ------------------------------------------------------------------

rexLangParser::Loop_statementContext::Loop_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t rexLangParser::Loop_statementContext::getRuleIndex() const {
  return rexLangParser::RuleLoop_statement;
}

void rexLangParser::Loop_statementContext::copyFrom(Loop_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RangeForContext ------------------------------------------------------------------

tree::TerminalNode* rexLangParser::RangeForContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}

rexLangParser::ExpressionContext* rexLangParser::RangeForContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

rexLangParser::Statement_listContext* rexLangParser::RangeForContext::statement_list() {
  return getRuleContext<rexLangParser::Statement_listContext>(0);
}

rexLangParser::Hierarchy_identifierContext* rexLangParser::RangeForContext::hierarchy_identifier() {
  return getRuleContext<rexLangParser::Hierarchy_identifierContext>(0);
}

rexLangParser::RangeForContext::RangeForContext(Loop_statementContext *ctx) { copyFrom(ctx); }

void rexLangParser::RangeForContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRangeFor(this);
}
void rexLangParser::RangeForContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRangeFor(this);
}

antlrcpp::Any rexLangParser::RangeForContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitRangeFor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForContext ------------------------------------------------------------------

tree::TerminalNode* rexLangParser::ForContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}

std::vector<rexLangParser::ExpressionContext *> rexLangParser::ForContext::expression() {
  return getRuleContexts<rexLangParser::ExpressionContext>();
}

rexLangParser::ExpressionContext* rexLangParser::ForContext::expression(size_t i) {
  return getRuleContext<rexLangParser::ExpressionContext>(i);
}

rexLangParser::Statement_listContext* rexLangParser::ForContext::statement_list() {
  return getRuleContext<rexLangParser::Statement_listContext>(0);
}

rexLangParser::Hierarchy_identifierContext* rexLangParser::ForContext::hierarchy_identifier() {
  return getRuleContext<rexLangParser::Hierarchy_identifierContext>(0);
}

rexLangParser::ForContext::ForContext(Loop_statementContext *ctx) { copyFrom(ctx); }

void rexLangParser::ForContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor(this);
}
void rexLangParser::ForContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor(this);
}

antlrcpp::Any rexLangParser::ForContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitFor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DoWhileContext ------------------------------------------------------------------

tree::TerminalNode* rexLangParser::DoWhileContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}

rexLangParser::Statement_listContext* rexLangParser::DoWhileContext::statement_list() {
  return getRuleContext<rexLangParser::Statement_listContext>(0);
}

rexLangParser::ExpressionContext* rexLangParser::DoWhileContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

rexLangParser::DoWhileContext::DoWhileContext(Loop_statementContext *ctx) { copyFrom(ctx); }

void rexLangParser::DoWhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDoWhile(this);
}
void rexLangParser::DoWhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDoWhile(this);
}

antlrcpp::Any rexLangParser::DoWhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitDoWhile(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileContext ------------------------------------------------------------------

tree::TerminalNode* rexLangParser::WhileContext::NEWLINE() {
  return getToken(rexLangParser::NEWLINE, 0);
}

rexLangParser::ExpressionContext* rexLangParser::WhileContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

rexLangParser::Statement_listContext* rexLangParser::WhileContext::statement_list() {
  return getRuleContext<rexLangParser::Statement_listContext>(0);
}

rexLangParser::WhileContext::WhileContext(Loop_statementContext *ctx) { copyFrom(ctx); }

void rexLangParser::WhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhile(this);
}
void rexLangParser::WhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhile(this);
}

antlrcpp::Any rexLangParser::WhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitWhile(this);
  else
    return visitor->visitChildren(this);
}
rexLangParser::Loop_statementContext* rexLangParser::loop_statement() {
  Loop_statementContext *_localctx = _tracker.createInstance<Loop_statementContext>(_ctx, getState());
  enterRule(_localctx, 50, rexLangParser::RuleLoop_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(540);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case rexLangParser::T__21: {
        _localctx = dynamic_cast<Loop_statementContext *>(_tracker.createInstance<rexLangParser::WhileContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(488);
        match(rexLangParser::T__21);
        setState(489);
        match(rexLangParser::T__16);
        setState(490);
        dynamic_cast<WhileContext *>(_localctx)->condition_expr = expression(0);
        setState(491);
        match(rexLangParser::T__17);
        setState(492);
        match(rexLangParser::NEWLINE);
        setState(493);
        dynamic_cast<WhileContext *>(_localctx)->loop_body = statement_list();
        setState(494);
        match(rexLangParser::T__22);
        setState(495);
        match(rexLangParser::T__16);
        setState(496);
        match(rexLangParser::T__17);
        break;
      }

      case rexLangParser::T__23: {
        _localctx = dynamic_cast<Loop_statementContext *>(_tracker.createInstance<rexLangParser::RangeForContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(498);
        match(rexLangParser::T__23);
        setState(499);
        match(rexLangParser::T__16);
        setState(500);
        dynamic_cast<RangeForContext *>(_localctx)->times_expr = expression(0);
        setState(501);
        match(rexLangParser::T__2);
        setState(503);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::IDENTIFIER) {
          setState(502);
          dynamic_cast<RangeForContext *>(_localctx)->loop_variable = hierarchy_identifier();
        }
        setState(505);
        match(rexLangParser::T__17);
        setState(506);
        match(rexLangParser::NEWLINE);
        setState(507);
        dynamic_cast<RangeForContext *>(_localctx)->loop_body = statement_list();
        setState(508);
        match(rexLangParser::T__24);
        setState(509);
        match(rexLangParser::T__16);
        setState(510);
        match(rexLangParser::T__17);
        break;
      }

      case rexLangParser::T__25: {
        _localctx = dynamic_cast<Loop_statementContext *>(_tracker.createInstance<rexLangParser::ForContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(512);
        match(rexLangParser::T__25);
        setState(513);
        match(rexLangParser::T__16);
        setState(514);
        dynamic_cast<ForContext *>(_localctx)->loop_start = expression(0);
        setState(515);
        match(rexLangParser::T__2);
        setState(516);
        dynamic_cast<ForContext *>(_localctx)->loop_end = expression(0);
        setState(517);
        match(rexLangParser::T__2);
        setState(518);
        dynamic_cast<ForContext *>(_localctx)->loop_step = expression(0);
        setState(521);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::T__2) {
          setState(519);
          match(rexLangParser::T__2);
          setState(520);
          dynamic_cast<ForContext *>(_localctx)->loop_variable = hierarchy_identifier();
        }
        setState(523);
        match(rexLangParser::T__17);
        setState(524);
        match(rexLangParser::NEWLINE);
        setState(525);
        dynamic_cast<ForContext *>(_localctx)->loop_body = statement_list();
        setState(526);
        match(rexLangParser::T__26);
        setState(527);
        match(rexLangParser::T__16);
        setState(528);
        match(rexLangParser::T__17);
        break;
      }

      case rexLangParser::T__27: {
        _localctx = dynamic_cast<Loop_statementContext *>(_tracker.createInstance<rexLangParser::DoWhileContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(530);
        match(rexLangParser::T__27);
        setState(531);
        match(rexLangParser::T__16);
        setState(532);
        match(rexLangParser::T__17);
        setState(533);
        match(rexLangParser::NEWLINE);
        setState(534);
        dynamic_cast<DoWhileContext *>(_localctx)->loop_body = statement_list();
        setState(535);
        match(rexLangParser::T__28);
        setState(536);
        match(rexLangParser::T__16);
        setState(537);
        dynamic_cast<DoWhileContext *>(_localctx)->condition_expr = expression(0);
        setState(538);
        match(rexLangParser::T__17);
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

rexLangParser::Condition_statementContext::Condition_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t rexLangParser::Condition_statementContext::getRuleIndex() const {
  return rexLangParser::RuleCondition_statement;
}

void rexLangParser::Condition_statementContext::copyFrom(Condition_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IfStmtContext ------------------------------------------------------------------

rexLangParser::ExpressionContext* rexLangParser::IfStmtContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

std::vector<rexLangParser::Statement_listContext *> rexLangParser::IfStmtContext::statement_list() {
  return getRuleContexts<rexLangParser::Statement_listContext>();
}

rexLangParser::Statement_listContext* rexLangParser::IfStmtContext::statement_list(size_t i) {
  return getRuleContext<rexLangParser::Statement_listContext>(i);
}

rexLangParser::IfStmtContext::IfStmtContext(Condition_statementContext *ctx) { copyFrom(ctx); }

void rexLangParser::IfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStmt(this);
}
void rexLangParser::IfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStmt(this);
}

antlrcpp::Any rexLangParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfTrueStmtContext ------------------------------------------------------------------

rexLangParser::ExpressionContext* rexLangParser::IfTrueStmtContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

rexLangParser::Statement_listContext* rexLangParser::IfTrueStmtContext::statement_list() {
  return getRuleContext<rexLangParser::Statement_listContext>(0);
}

rexLangParser::IfTrueStmtContext::IfTrueStmtContext(Condition_statementContext *ctx) { copyFrom(ctx); }

void rexLangParser::IfTrueStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfTrueStmt(this);
}
void rexLangParser::IfTrueStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfTrueStmt(this);
}

antlrcpp::Any rexLangParser::IfTrueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitIfTrueStmt(this);
  else
    return visitor->visitChildren(this);
}
rexLangParser::Condition_statementContext* rexLangParser::condition_statement() {
  Condition_statementContext *_localctx = _tracker.createInstance<Condition_statementContext>(_ctx, getState());
  enterRule(_localctx, 52, rexLangParser::RuleCondition_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(560);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case rexLangParser::T__29: {
        _localctx = dynamic_cast<Condition_statementContext *>(_tracker.createInstance<rexLangParser::IfStmtContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(542);
        match(rexLangParser::T__29);
        setState(543);
        match(rexLangParser::T__16);
        setState(544);
        dynamic_cast<IfStmtContext *>(_localctx)->condition_expr = expression(0);
        setState(545);
        match(rexLangParser::T__17);
        setState(546);
        dynamic_cast<IfStmtContext *>(_localctx)->true_stmt_list = statement_list();
        setState(549);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == rexLangParser::T__30) {
          setState(547);
          match(rexLangParser::T__30);
          setState(548);
          dynamic_cast<IfStmtContext *>(_localctx)->false_stmt_list = statement_list();
        }
        setState(551);
        match(rexLangParser::T__31);
        break;
      }

      case rexLangParser::T__32: {
        _localctx = dynamic_cast<Condition_statementContext *>(_tracker.createInstance<rexLangParser::IfTrueStmtContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(553);
        match(rexLangParser::T__32);
        setState(554);
        match(rexLangParser::T__16);
        setState(555);
        dynamic_cast<IfTrueStmtContext *>(_localctx)->condition_expr = expression(0);
        setState(556);
        match(rexLangParser::T__17);
        setState(557);
        dynamic_cast<IfTrueStmtContext *>(_localctx)->true_stmt_list = statement_list();
        setState(558);
        match(rexLangParser::T__33);
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

rexLangParser::Control_statementContext::Control_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t rexLangParser::Control_statementContext::getRuleIndex() const {
  return rexLangParser::RuleControl_statement;
}

void rexLangParser::Control_statementContext::copyFrom(Control_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ContinueStmtContext ------------------------------------------------------------------

rexLangParser::ContinueStmtContext::ContinueStmtContext(Control_statementContext *ctx) { copyFrom(ctx); }

void rexLangParser::ContinueStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStmt(this);
}
void rexLangParser::ContinueStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStmt(this);
}

antlrcpp::Any rexLangParser::ContinueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitContinueStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExitStmtContext ------------------------------------------------------------------

rexLangParser::ExitStmtContext::ExitStmtContext(Control_statementContext *ctx) { copyFrom(ctx); }

void rexLangParser::ExitStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExitStmt(this);
}
void rexLangParser::ExitStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExitStmt(this);
}

antlrcpp::Any rexLangParser::ExitStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitExitStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStmtContext ------------------------------------------------------------------

rexLangParser::BreakStmtContext::BreakStmtContext(Control_statementContext *ctx) { copyFrom(ctx); }

void rexLangParser::BreakStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStmt(this);
}
void rexLangParser::BreakStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStmt(this);
}

antlrcpp::Any rexLangParser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStmtContext ------------------------------------------------------------------

rexLangParser::ExpressionContext* rexLangParser::ReturnStmtContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

rexLangParser::ReturnStmtContext::ReturnStmtContext(Control_statementContext *ctx) { copyFrom(ctx); }

void rexLangParser::ReturnStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStmt(this);
}
void rexLangParser::ReturnStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStmt(this);
}

antlrcpp::Any rexLangParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}
rexLangParser::Control_statementContext* rexLangParser::control_statement() {
  Control_statementContext *_localctx = _tracker.createInstance<Control_statementContext>(_ctx, getState());
  enterRule(_localctx, 54, rexLangParser::RuleControl_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(577);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case rexLangParser::T__34: {
        _localctx = dynamic_cast<Control_statementContext *>(_tracker.createInstance<rexLangParser::ContinueStmtContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(562);
        match(rexLangParser::T__34);
        setState(563);
        match(rexLangParser::T__16);
        setState(564);
        match(rexLangParser::T__17);
        break;
      }

      case rexLangParser::T__35: {
        _localctx = dynamic_cast<Control_statementContext *>(_tracker.createInstance<rexLangParser::BreakStmtContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(565);
        match(rexLangParser::T__35);
        setState(566);
        match(rexLangParser::T__16);
        setState(567);
        match(rexLangParser::T__17);
        break;
      }

      case rexLangParser::T__36: {
        _localctx = dynamic_cast<Control_statementContext *>(_tracker.createInstance<rexLangParser::ReturnStmtContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(568);
        match(rexLangParser::T__36);
        setState(569);
        match(rexLangParser::T__16);
        setState(571);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 17) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 17)) & ((1ULL << (rexLangParser::T__16 - 17))
          | (1ULL << (rexLangParser::T__39 - 17))
          | (1ULL << (rexLangParser::T__41 - 17))
          | (1ULL << (rexLangParser::T__52 - 17))
          | (1ULL << (rexLangParser::T__53 - 17))
          | (1ULL << (rexLangParser::T__54 - 17))
          | (1ULL << (rexLangParser::T__55 - 17))
          | (1ULL << (rexLangParser::K_SUB_OPT - 17))
          | (1ULL << (rexLangParser::INTEGER_LITERAL - 17))
          | (1ULL << (rexLangParser::FLOAT_LITERAL - 17))
          | (1ULL << (rexLangParser::IDENTIFIER - 17))
          | (1ULL << (rexLangParser::STRING_LITERAL - 17)))) != 0)) {
          setState(570);
          dynamic_cast<ReturnStmtContext *>(_localctx)->return_expr = expression(0);
        }
        setState(573);
        match(rexLangParser::T__17);
        break;
      }

      case rexLangParser::T__37: {
        _localctx = dynamic_cast<Control_statementContext *>(_tracker.createInstance<rexLangParser::ExitStmtContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(574);
        match(rexLangParser::T__37);
        setState(575);
        match(rexLangParser::T__16);
        setState(576);
        match(rexLangParser::T__17);
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

rexLangParser::Hierarchy_identifierContext::Hierarchy_identifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<rexLangParser::Name_componentContext *> rexLangParser::Hierarchy_identifierContext::name_component() {
  return getRuleContexts<rexLangParser::Name_componentContext>();
}

rexLangParser::Name_componentContext* rexLangParser::Hierarchy_identifierContext::name_component(size_t i) {
  return getRuleContext<rexLangParser::Name_componentContext>(i);
}


size_t rexLangParser::Hierarchy_identifierContext::getRuleIndex() const {
  return rexLangParser::RuleHierarchy_identifier;
}

void rexLangParser::Hierarchy_identifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHierarchy_identifier(this);
}

void rexLangParser::Hierarchy_identifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHierarchy_identifier(this);
}


antlrcpp::Any rexLangParser::Hierarchy_identifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitHierarchy_identifier(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Hierarchy_identifierContext* rexLangParser::hierarchy_identifier() {
  Hierarchy_identifierContext *_localctx = _tracker.createInstance<Hierarchy_identifierContext>(_ctx, getState());
  enterRule(_localctx, 56, rexLangParser::RuleHierarchy_identifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(579);
    dynamic_cast<Hierarchy_identifierContext *>(_localctx)->name_componentContext = name_component(0);
    dynamic_cast<Hierarchy_identifierContext *>(_localctx)->components.push_back(dynamic_cast<Hierarchy_identifierContext *>(_localctx)->name_componentContext);
    setState(584);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(580);
        match(rexLangParser::T__38);
        setState(581);
        dynamic_cast<Hierarchy_identifierContext *>(_localctx)->name_componentContext = name_component(0);
        dynamic_cast<Hierarchy_identifierContext *>(_localctx)->components.push_back(dynamic_cast<Hierarchy_identifierContext *>(_localctx)->name_componentContext); 
      }
      setState(586);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
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

rexLangParser::Name_componentContext::Name_componentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t rexLangParser::Name_componentContext::getRuleIndex() const {
  return rexLangParser::RuleName_component;
}

void rexLangParser::Name_componentContext::copyFrom(Name_componentContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FuncCallContext ------------------------------------------------------------------

rexLangParser::Name_componentContext* rexLangParser::FuncCallContext::name_component() {
  return getRuleContext<rexLangParser::Name_componentContext>(0);
}

std::vector<rexLangParser::ExpressionContext *> rexLangParser::FuncCallContext::expression() {
  return getRuleContexts<rexLangParser::ExpressionContext>();
}

rexLangParser::ExpressionContext* rexLangParser::FuncCallContext::expression(size_t i) {
  return getRuleContext<rexLangParser::ExpressionContext>(i);
}

rexLangParser::FuncCallContext::FuncCallContext(Name_componentContext *ctx) { copyFrom(ctx); }

void rexLangParser::FuncCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCall(this);
}
void rexLangParser::FuncCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCall(this);
}

antlrcpp::Any rexLangParser::FuncCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitFuncCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentifierContext ------------------------------------------------------------------

tree::TerminalNode* rexLangParser::IdentifierContext::IDENTIFIER() {
  return getToken(rexLangParser::IDENTIFIER, 0);
}

rexLangParser::IdentifierContext::IdentifierContext(Name_componentContext *ctx) { copyFrom(ctx); }

void rexLangParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}
void rexLangParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}

antlrcpp::Any rexLangParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayIndexContext ------------------------------------------------------------------

rexLangParser::Name_componentContext* rexLangParser::ArrayIndexContext::name_component() {
  return getRuleContext<rexLangParser::Name_componentContext>(0);
}

rexLangParser::ExpressionContext* rexLangParser::ArrayIndexContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

rexLangParser::ArrayIndexContext::ArrayIndexContext(Name_componentContext *ctx) { copyFrom(ctx); }

void rexLangParser::ArrayIndexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayIndex(this);
}
void rexLangParser::ArrayIndexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayIndex(this);
}

antlrcpp::Any rexLangParser::ArrayIndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitArrayIndex(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Name_componentContext* rexLangParser::name_component() {
   return name_component(0);
}

rexLangParser::Name_componentContext* rexLangParser::name_component(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  rexLangParser::Name_componentContext *_localctx = _tracker.createInstance<Name_componentContext>(_ctx, parentState);
  rexLangParser::Name_componentContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, rexLangParser::RuleName_component, precedence);

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

    setState(588);
    match(rexLangParser::IDENTIFIER);
    _ctx->stop = _input->LT(-1);
    setState(612);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(610);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<FuncCallContext>(_tracker.createInstance<Name_componentContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleName_component);
          setState(590);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(591);
          match(rexLangParser::T__16);
          setState(593);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (((((_la - 17) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 17)) & ((1ULL << (rexLangParser::T__16 - 17))
            | (1ULL << (rexLangParser::T__39 - 17))
            | (1ULL << (rexLangParser::T__41 - 17))
            | (1ULL << (rexLangParser::T__52 - 17))
            | (1ULL << (rexLangParser::T__53 - 17))
            | (1ULL << (rexLangParser::T__54 - 17))
            | (1ULL << (rexLangParser::T__55 - 17))
            | (1ULL << (rexLangParser::K_SUB_OPT - 17))
            | (1ULL << (rexLangParser::INTEGER_LITERAL - 17))
            | (1ULL << (rexLangParser::FLOAT_LITERAL - 17))
            | (1ULL << (rexLangParser::IDENTIFIER - 17))
            | (1ULL << (rexLangParser::STRING_LITERAL - 17)))) != 0)) {
            setState(592);
            dynamic_cast<FuncCallContext *>(_localctx)->expressionContext = expression(0);
            dynamic_cast<FuncCallContext *>(_localctx)->arguments.push_back(dynamic_cast<FuncCallContext *>(_localctx)->expressionContext);
          }
          setState(601);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == rexLangParser::T__2) {
            setState(595);
            match(rexLangParser::T__2);
            setState(597);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (((((_la - 17) & ~ 0x3fULL) == 0) &&
              ((1ULL << (_la - 17)) & ((1ULL << (rexLangParser::T__16 - 17))
              | (1ULL << (rexLangParser::T__39 - 17))
              | (1ULL << (rexLangParser::T__41 - 17))
              | (1ULL << (rexLangParser::T__52 - 17))
              | (1ULL << (rexLangParser::T__53 - 17))
              | (1ULL << (rexLangParser::T__54 - 17))
              | (1ULL << (rexLangParser::T__55 - 17))
              | (1ULL << (rexLangParser::K_SUB_OPT - 17))
              | (1ULL << (rexLangParser::INTEGER_LITERAL - 17))
              | (1ULL << (rexLangParser::FLOAT_LITERAL - 17))
              | (1ULL << (rexLangParser::IDENTIFIER - 17))
              | (1ULL << (rexLangParser::STRING_LITERAL - 17)))) != 0)) {
              setState(596);
              dynamic_cast<FuncCallContext *>(_localctx)->expressionContext = expression(0);
              dynamic_cast<FuncCallContext *>(_localctx)->arguments.push_back(dynamic_cast<FuncCallContext *>(_localctx)->expressionContext);
            }
            setState(603);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(604);
          match(rexLangParser::T__17);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ArrayIndexContext>(_tracker.createInstance<Name_componentContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleName_component);
          setState(605);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(606);
          match(rexLangParser::T__39);
          setState(607);
          expression(0);
          setState(608);
          match(rexLangParser::T__40);
          break;
        }

        } 
      }
      setState(614);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx);
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

rexLangParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t rexLangParser::ExpressionContext::getRuleIndex() const {
  return rexLangParser::RuleExpression;
}

void rexLangParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BracketContext ------------------------------------------------------------------

rexLangParser::ExpressionContext* rexLangParser::BracketContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

rexLangParser::BracketContext::BracketContext(ExpressionContext *ctx) { copyFrom(ctx); }

void rexLangParser::BracketContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBracket(this);
}
void rexLangParser::BracketContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBracket(this);
}

antlrcpp::Any rexLangParser::BracketContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitBracket(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OptElementContext ------------------------------------------------------------------

rexLangParser::NumberContext* rexLangParser::OptElementContext::number() {
  return getRuleContext<rexLangParser::NumberContext>(0);
}

rexLangParser::Bool_valueContext* rexLangParser::OptElementContext::bool_value() {
  return getRuleContext<rexLangParser::Bool_valueContext>(0);
}

rexLangParser::Macro_valueContext* rexLangParser::OptElementContext::macro_value() {
  return getRuleContext<rexLangParser::Macro_valueContext>(0);
}

rexLangParser::String_valueContext* rexLangParser::OptElementContext::string_value() {
  return getRuleContext<rexLangParser::String_valueContext>(0);
}

rexLangParser::Hierarchy_identifierContext* rexLangParser::OptElementContext::hierarchy_identifier() {
  return getRuleContext<rexLangParser::Hierarchy_identifierContext>(0);
}

rexLangParser::Func_ptrContext* rexLangParser::OptElementContext::func_ptr() {
  return getRuleContext<rexLangParser::Func_ptrContext>(0);
}

rexLangParser::Datetime_valueContext* rexLangParser::OptElementContext::datetime_value() {
  return getRuleContext<rexLangParser::Datetime_valueContext>(0);
}

rexLangParser::Data_set_valueContext* rexLangParser::OptElementContext::data_set_value() {
  return getRuleContext<rexLangParser::Data_set_valueContext>(0);
}

rexLangParser::OptElementContext::OptElementContext(ExpressionContext *ctx) { copyFrom(ctx); }

void rexLangParser::OptElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOptElement(this);
}
void rexLangParser::OptElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOptElement(this);
}

antlrcpp::Any rexLangParser::OptElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitOptElement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryExprContext ------------------------------------------------------------------

std::vector<rexLangParser::ExpressionContext *> rexLangParser::BinaryExprContext::expression() {
  return getRuleContexts<rexLangParser::ExpressionContext>();
}

rexLangParser::ExpressionContext* rexLangParser::BinaryExprContext::expression(size_t i) {
  return getRuleContext<rexLangParser::ExpressionContext>(i);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_MUL_OPT() {
  return getToken(rexLangParser::K_MUL_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_DIV_OPT() {
  return getToken(rexLangParser::K_DIV_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_FULL_DIV_OPT() {
  return getToken(rexLangParser::K_FULL_DIV_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_MOD_OPT() {
  return getToken(rexLangParser::K_MOD_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_ADD_OPT() {
  return getToken(rexLangParser::K_ADD_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_SUB_OPT() {
  return getToken(rexLangParser::K_SUB_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_NOT_EQUAL_OPT() {
  return getToken(rexLangParser::K_NOT_EQUAL_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_EQUAL_OPT() {
  return getToken(rexLangParser::K_EQUAL_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_AECOM_OPT() {
  return getToken(rexLangParser::K_AECOM_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_LESS_OPT() {
  return getToken(rexLangParser::K_LESS_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_GREAT_OPT() {
  return getToken(rexLangParser::K_GREAT_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_LESS_EQU_OPT() {
  return getToken(rexLangParser::K_LESS_EQU_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_GREAT_EQU_OPT() {
  return getToken(rexLangParser::K_GREAT_EQU_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_LIKE_EQU_OPT() {
  return getToken(rexLangParser::K_LIKE_EQU_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_AND_OPT() {
  return getToken(rexLangParser::K_AND_OPT, 0);
}

tree::TerminalNode* rexLangParser::BinaryExprContext::K_OR_OPT() {
  return getToken(rexLangParser::K_OR_OPT, 0);
}

rexLangParser::BinaryExprContext::BinaryExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void rexLangParser::BinaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBinaryExpr(this);
}
void rexLangParser::BinaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBinaryExpr(this);
}

antlrcpp::Any rexLangParser::BinaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitBinaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprContext ------------------------------------------------------------------

rexLangParser::ExpressionContext* rexLangParser::UnaryExprContext::expression() {
  return getRuleContext<rexLangParser::ExpressionContext>(0);
}

tree::TerminalNode* rexLangParser::UnaryExprContext::K_SUB_OPT() {
  return getToken(rexLangParser::K_SUB_OPT, 0);
}

rexLangParser::UnaryExprContext::UnaryExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void rexLangParser::UnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpr(this);
}
void rexLangParser::UnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpr(this);
}

antlrcpp::Any rexLangParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::ExpressionContext* rexLangParser::expression() {
   return expression(0);
}

rexLangParser::ExpressionContext* rexLangParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  rexLangParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  rexLangParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, rexLangParser::RuleExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(630);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case rexLangParser::T__16: {
        _localctx = _tracker.createInstance<BracketContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(616);
        match(rexLangParser::T__16);
        setState(617);
        expression(0);
        setState(618);
        match(rexLangParser::T__17);
        break;
      }

      case rexLangParser::K_SUB_OPT: {
        _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(620);
        dynamic_cast<UnaryExprContext *>(_localctx)->opt = match(rexLangParser::K_SUB_OPT);
        setState(621);
        expression(25);
        break;
      }

      case rexLangParser::INTEGER_LITERAL:
      case rexLangParser::FLOAT_LITERAL: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(622);
        number();
        break;
      }

      case rexLangParser::T__54:
      case rexLangParser::T__55: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(623);
        bool_value();
        break;
      }

      case rexLangParser::T__52: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(624);
        macro_value();
        break;
      }

      case rexLangParser::STRING_LITERAL: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(625);
        string_value();
        break;
      }

      case rexLangParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(626);
        hierarchy_identifier();
        break;
      }

      case rexLangParser::T__53: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(627);
        func_ptr();
        break;
      }

      case rexLangParser::T__39: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(628);
        datetime_value();
        break;
      }

      case rexLangParser::T__41: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(629);
        data_set_value();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(682);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 89, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(680);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(632);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(633);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_MUL_OPT);
          setState(634);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(25);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(635);

          if (!(precpred(_ctx, 23))) throw FailedPredicateException(this, "precpred(_ctx, 23)");
          setState(636);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_DIV_OPT);
          setState(637);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(24);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(638);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(639);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_FULL_DIV_OPT);
          setState(640);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(23);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(641);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(642);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_MOD_OPT);
          setState(643);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(22);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(644);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(645);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_ADD_OPT);
          setState(646);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(21);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(647);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(648);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_SUB_OPT);
          setState(649);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(20);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(650);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(651);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_NOT_EQUAL_OPT);
          setState(652);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(19);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(653);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(654);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_EQUAL_OPT);
          setState(655);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(18);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(656);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(657);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_AECOM_OPT);
          setState(658);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(17);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(659);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(660);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_LESS_OPT);
          setState(661);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(16);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(662);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(663);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_GREAT_OPT);
          setState(664);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(15);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(665);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(666);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_LESS_EQU_OPT);
          setState(667);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(14);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(668);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(669);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_GREAT_EQU_OPT);
          setState(670);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(13);
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(671);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(672);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_LIKE_EQU_OPT);
          setState(673);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(12);
          break;
        }

        case 15: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(674);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(675);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_AND_OPT);
          setState(676);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(11);
          break;
        }

        case 16: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(677);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(678);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(rexLangParser::K_OR_OPT);
          setState(679);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(10);
          break;
        }

        } 
      }
      setState(684);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 89, _ctx);
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

rexLangParser::Data_set_valueContext::Data_set_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<rexLangParser::ExpressionContext *> rexLangParser::Data_set_valueContext::expression() {
  return getRuleContexts<rexLangParser::ExpressionContext>();
}

rexLangParser::ExpressionContext* rexLangParser::Data_set_valueContext::expression(size_t i) {
  return getRuleContext<rexLangParser::ExpressionContext>(i);
}


size_t rexLangParser::Data_set_valueContext::getRuleIndex() const {
  return rexLangParser::RuleData_set_value;
}

void rexLangParser::Data_set_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterData_set_value(this);
}

void rexLangParser::Data_set_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitData_set_value(this);
}


antlrcpp::Any rexLangParser::Data_set_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitData_set_value(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Data_set_valueContext* rexLangParser::data_set_value() {
  Data_set_valueContext *_localctx = _tracker.createInstance<Data_set_valueContext>(_ctx, getState());
  enterRule(_localctx, 62, rexLangParser::RuleData_set_value);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(685);
    match(rexLangParser::T__41);
    setState(694);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 17) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 17)) & ((1ULL << (rexLangParser::T__16 - 17))
      | (1ULL << (rexLangParser::T__39 - 17))
      | (1ULL << (rexLangParser::T__41 - 17))
      | (1ULL << (rexLangParser::T__52 - 17))
      | (1ULL << (rexLangParser::T__53 - 17))
      | (1ULL << (rexLangParser::T__54 - 17))
      | (1ULL << (rexLangParser::T__55 - 17))
      | (1ULL << (rexLangParser::K_SUB_OPT - 17))
      | (1ULL << (rexLangParser::INTEGER_LITERAL - 17))
      | (1ULL << (rexLangParser::FLOAT_LITERAL - 17))
      | (1ULL << (rexLangParser::IDENTIFIER - 17))
      | (1ULL << (rexLangParser::STRING_LITERAL - 17)))) != 0)) {
      setState(686);
      dynamic_cast<Data_set_valueContext *>(_localctx)->expressionContext = expression(0);
      dynamic_cast<Data_set_valueContext *>(_localctx)->elems.push_back(dynamic_cast<Data_set_valueContext *>(_localctx)->expressionContext);
      setState(691);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == rexLangParser::T__2) {
        setState(687);
        match(rexLangParser::T__2);
        setState(688);
        dynamic_cast<Data_set_valueContext *>(_localctx)->expressionContext = expression(0);
        dynamic_cast<Data_set_valueContext *>(_localctx)->elems.push_back(dynamic_cast<Data_set_valueContext *>(_localctx)->expressionContext);
        setState(693);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(696);
    match(rexLangParser::T__42);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Datetime_valueContext ------------------------------------------------------------------

rexLangParser::Datetime_valueContext::Datetime_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

rexLangParser::Datetime_value_coreContext* rexLangParser::Datetime_valueContext::datetime_value_core() {
  return getRuleContext<rexLangParser::Datetime_value_coreContext>(0);
}


size_t rexLangParser::Datetime_valueContext::getRuleIndex() const {
  return rexLangParser::RuleDatetime_value;
}

void rexLangParser::Datetime_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetime_value(this);
}

void rexLangParser::Datetime_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetime_value(this);
}


antlrcpp::Any rexLangParser::Datetime_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitDatetime_value(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Datetime_valueContext* rexLangParser::datetime_value() {
  Datetime_valueContext *_localctx = _tracker.createInstance<Datetime_valueContext>(_ctx, getState());
  enterRule(_localctx, 64, rexLangParser::RuleDatetime_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(698);
    match(rexLangParser::T__39);
    setState(699);
    datetime_value_core();
    setState(700);
    match(rexLangParser::T__40);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Datetime_value_coreContext ------------------------------------------------------------------

rexLangParser::Datetime_value_coreContext::Datetime_value_coreContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t rexLangParser::Datetime_value_coreContext::getRuleIndex() const {
  return rexLangParser::RuleDatetime_value_core;
}

void rexLangParser::Datetime_value_coreContext::copyFrom(Datetime_value_coreContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DatetimeSeparateBySlashColonContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> rexLangParser::DatetimeSeparateBySlashColonContext::INTEGER_LITERAL() {
  return getTokens(rexLangParser::INTEGER_LITERAL);
}

tree::TerminalNode* rexLangParser::DatetimeSeparateBySlashColonContext::INTEGER_LITERAL(size_t i) {
  return getToken(rexLangParser::INTEGER_LITERAL, i);
}

rexLangParser::DatetimeSeparateBySlashColonContext::DatetimeSeparateBySlashColonContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void rexLangParser::DatetimeSeparateBySlashColonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimeSeparateBySlashColon(this);
}
void rexLangParser::DatetimeSeparateBySlashColonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimeSeparateBySlashColon(this);
}

antlrcpp::Any rexLangParser::DatetimeSeparateBySlashColonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitDatetimeSeparateBySlashColon(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimePureNumberContext ------------------------------------------------------------------

tree::TerminalNode* rexLangParser::DatetimePureNumberContext::INTEGER_LITERAL() {
  return getToken(rexLangParser::INTEGER_LITERAL, 0);
}

rexLangParser::DatetimePureNumberContext::DatetimePureNumberContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void rexLangParser::DatetimePureNumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimePureNumber(this);
}
void rexLangParser::DatetimePureNumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimePureNumber(this);
}

antlrcpp::Any rexLangParser::DatetimePureNumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitDatetimePureNumber(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimeSeparateBySlashContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> rexLangParser::DatetimeSeparateBySlashContext::INTEGER_LITERAL() {
  return getTokens(rexLangParser::INTEGER_LITERAL);
}

tree::TerminalNode* rexLangParser::DatetimeSeparateBySlashContext::INTEGER_LITERAL(size_t i) {
  return getToken(rexLangParser::INTEGER_LITERAL, i);
}

rexLangParser::DatetimeSeparateBySlashContext::DatetimeSeparateBySlashContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void rexLangParser::DatetimeSeparateBySlashContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimeSeparateBySlash(this);
}
void rexLangParser::DatetimeSeparateBySlashContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimeSeparateBySlash(this);
}

antlrcpp::Any rexLangParser::DatetimeSeparateBySlashContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitDatetimeSeparateBySlash(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimeSeparateByBarColonContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> rexLangParser::DatetimeSeparateByBarColonContext::INTEGER_LITERAL() {
  return getTokens(rexLangParser::INTEGER_LITERAL);
}

tree::TerminalNode* rexLangParser::DatetimeSeparateByBarColonContext::INTEGER_LITERAL(size_t i) {
  return getToken(rexLangParser::INTEGER_LITERAL, i);
}

rexLangParser::DatetimeSeparateByBarColonContext::DatetimeSeparateByBarColonContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void rexLangParser::DatetimeSeparateByBarColonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimeSeparateByBarColon(this);
}
void rexLangParser::DatetimeSeparateByBarColonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimeSeparateByBarColon(this);
}

antlrcpp::Any rexLangParser::DatetimeSeparateByBarColonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitDatetimeSeparateByBarColon(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimeSeparateByBarContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> rexLangParser::DatetimeSeparateByBarContext::INTEGER_LITERAL() {
  return getTokens(rexLangParser::INTEGER_LITERAL);
}

tree::TerminalNode* rexLangParser::DatetimeSeparateByBarContext::INTEGER_LITERAL(size_t i) {
  return getToken(rexLangParser::INTEGER_LITERAL, i);
}

rexLangParser::DatetimeSeparateByBarContext::DatetimeSeparateByBarContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void rexLangParser::DatetimeSeparateByBarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimeSeparateByBar(this);
}
void rexLangParser::DatetimeSeparateByBarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimeSeparateByBar(this);
}

antlrcpp::Any rexLangParser::DatetimeSeparateByBarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitDatetimeSeparateByBar(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DatetimeSeparateByChineseContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> rexLangParser::DatetimeSeparateByChineseContext::INTEGER_LITERAL() {
  return getTokens(rexLangParser::INTEGER_LITERAL);
}

tree::TerminalNode* rexLangParser::DatetimeSeparateByChineseContext::INTEGER_LITERAL(size_t i) {
  return getToken(rexLangParser::INTEGER_LITERAL, i);
}

rexLangParser::DatetimeSeparateByChineseContext::DatetimeSeparateByChineseContext(Datetime_value_coreContext *ctx) { copyFrom(ctx); }

void rexLangParser::DatetimeSeparateByChineseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatetimeSeparateByChinese(this);
}
void rexLangParser::DatetimeSeparateByChineseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatetimeSeparateByChinese(this);
}

antlrcpp::Any rexLangParser::DatetimeSeparateByChineseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitDatetimeSeparateByChinese(this);
  else
    return visitor->visitChildren(this);
}
rexLangParser::Datetime_value_coreContext* rexLangParser::datetime_value_core() {
  Datetime_value_coreContext *_localctx = _tracker.createInstance<Datetime_value_coreContext>(_ctx, getState());
  enterRule(_localctx, 66, rexLangParser::RuleDatetime_value_core);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(769);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 97, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<rexLangParser::DatetimePureNumberContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(702);
      dynamic_cast<DatetimePureNumberContext *>(_localctx)->time = match(rexLangParser::INTEGER_LITERAL);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<rexLangParser::DatetimeSeparateByChineseContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(703);
      dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->year = match(rexLangParser::INTEGER_LITERAL);
      setState(704);
      match(rexLangParser::T__43);
      setState(705);
      dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->month = match(rexLangParser::INTEGER_LITERAL);
      setState(706);
      match(rexLangParser::T__44);
      setState(707);
      dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->day = match(rexLangParser::INTEGER_LITERAL);
      setState(708);
      match(rexLangParser::T__45);
      setState(715);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::INTEGER_LITERAL) {
        setState(709);
        dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->hour = match(rexLangParser::INTEGER_LITERAL);
        setState(710);
        match(rexLangParser::T__46);
        setState(711);
        dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->minute = match(rexLangParser::INTEGER_LITERAL);
        setState(712);
        match(rexLangParser::T__47);
        setState(713);
        dynamic_cast<DatetimeSeparateByChineseContext *>(_localctx)->second = match(rexLangParser::INTEGER_LITERAL);
        setState(714);
        match(rexLangParser::T__48);
      }
      break;
    }

    case 3: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<rexLangParser::DatetimeSeparateBySlashContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(717);
      dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->year = match(rexLangParser::INTEGER_LITERAL);
      setState(718);
      match(rexLangParser::T__49);
      setState(719);
      dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->month = match(rexLangParser::INTEGER_LITERAL);
      setState(720);
      match(rexLangParser::T__49);
      setState(721);
      dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->day = match(rexLangParser::INTEGER_LITERAL);
      setState(728);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__49) {
        setState(722);
        match(rexLangParser::T__49);
        setState(723);
        dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->hour = match(rexLangParser::INTEGER_LITERAL);
        setState(724);
        match(rexLangParser::T__49);
        setState(725);
        dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->minute = match(rexLangParser::INTEGER_LITERAL);
        setState(726);
        match(rexLangParser::T__49);
        setState(727);
        dynamic_cast<DatetimeSeparateBySlashContext *>(_localctx)->second = match(rexLangParser::INTEGER_LITERAL);
      }
      break;
    }

    case 4: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<rexLangParser::DatetimeSeparateBySlashColonContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(730);
      dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->year = match(rexLangParser::INTEGER_LITERAL);
      setState(731);
      match(rexLangParser::T__49);
      setState(732);
      dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->month = match(rexLangParser::INTEGER_LITERAL);
      setState(733);
      match(rexLangParser::T__49);
      setState(734);
      dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->day = match(rexLangParser::INTEGER_LITERAL);
      setState(741);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__49) {
        setState(735);
        match(rexLangParser::T__49);
        setState(736);
        dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->hour = match(rexLangParser::INTEGER_LITERAL);
        setState(737);
        match(rexLangParser::T__50);
        setState(738);
        dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->minute = match(rexLangParser::INTEGER_LITERAL);
        setState(739);
        match(rexLangParser::T__50);
        setState(740);
        dynamic_cast<DatetimeSeparateBySlashColonContext *>(_localctx)->second = match(rexLangParser::INTEGER_LITERAL);
      }
      break;
    }

    case 5: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<rexLangParser::DatetimeSeparateByBarContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(743);
      dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->year = match(rexLangParser::INTEGER_LITERAL);
      setState(744);
      match(rexLangParser::T__51);
      setState(745);
      dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->month = match(rexLangParser::INTEGER_LITERAL);
      setState(746);
      match(rexLangParser::T__51);
      setState(747);
      dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->day = match(rexLangParser::INTEGER_LITERAL);
      setState(754);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__51) {
        setState(748);
        match(rexLangParser::T__51);
        setState(749);
        dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->hour = match(rexLangParser::INTEGER_LITERAL);
        setState(750);
        match(rexLangParser::T__51);
        setState(751);
        dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->minute = match(rexLangParser::INTEGER_LITERAL);
        setState(752);
        match(rexLangParser::T__51);
        setState(753);
        dynamic_cast<DatetimeSeparateByBarContext *>(_localctx)->second = match(rexLangParser::INTEGER_LITERAL);
      }
      break;
    }

    case 6: {
      _localctx = dynamic_cast<Datetime_value_coreContext *>(_tracker.createInstance<rexLangParser::DatetimeSeparateByBarColonContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(756);
      dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->year = match(rexLangParser::INTEGER_LITERAL);
      setState(757);
      match(rexLangParser::T__51);
      setState(758);
      dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->month = match(rexLangParser::INTEGER_LITERAL);
      setState(759);
      match(rexLangParser::T__51);
      setState(760);
      dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->day = match(rexLangParser::INTEGER_LITERAL);
      setState(767);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == rexLangParser::T__51) {
        setState(761);
        match(rexLangParser::T__51);
        setState(762);
        dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->hour = match(rexLangParser::INTEGER_LITERAL);
        setState(763);
        match(rexLangParser::T__50);
        setState(764);
        dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->minute = match(rexLangParser::INTEGER_LITERAL);
        setState(765);
        match(rexLangParser::T__50);
        setState(766);
        dynamic_cast<DatetimeSeparateByBarColonContext *>(_localctx)->second = match(rexLangParser::INTEGER_LITERAL);
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

rexLangParser::Macro_valueContext::Macro_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* rexLangParser::Macro_valueContext::IDENTIFIER() {
  return getToken(rexLangParser::IDENTIFIER, 0);
}


size_t rexLangParser::Macro_valueContext::getRuleIndex() const {
  return rexLangParser::RuleMacro_value;
}

void rexLangParser::Macro_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMacro_value(this);
}

void rexLangParser::Macro_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMacro_value(this);
}


antlrcpp::Any rexLangParser::Macro_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitMacro_value(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Macro_valueContext* rexLangParser::macro_value() {
  Macro_valueContext *_localctx = _tracker.createInstance<Macro_valueContext>(_ctx, getState());
  enterRule(_localctx, 68, rexLangParser::RuleMacro_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(771);
    match(rexLangParser::T__52);
    setState(772);
    match(rexLangParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_ptrContext ------------------------------------------------------------------

rexLangParser::Func_ptrContext::Func_ptrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* rexLangParser::Func_ptrContext::IDENTIFIER() {
  return getToken(rexLangParser::IDENTIFIER, 0);
}


size_t rexLangParser::Func_ptrContext::getRuleIndex() const {
  return rexLangParser::RuleFunc_ptr;
}

void rexLangParser::Func_ptrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_ptr(this);
}

void rexLangParser::Func_ptrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_ptr(this);
}


antlrcpp::Any rexLangParser::Func_ptrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitFunc_ptr(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::Func_ptrContext* rexLangParser::func_ptr() {
  Func_ptrContext *_localctx = _tracker.createInstance<Func_ptrContext>(_ctx, getState());
  enterRule(_localctx, 70, rexLangParser::RuleFunc_ptr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(774);
    match(rexLangParser::T__53);
    setState(775);
    match(rexLangParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bool_valueContext ------------------------------------------------------------------

rexLangParser::Bool_valueContext::Bool_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t rexLangParser::Bool_valueContext::getRuleIndex() const {
  return rexLangParser::RuleBool_value;
}

void rexLangParser::Bool_valueContext::copyFrom(Bool_valueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BoolValueTrueContext ------------------------------------------------------------------

rexLangParser::BoolValueTrueContext::BoolValueTrueContext(Bool_valueContext *ctx) { copyFrom(ctx); }

void rexLangParser::BoolValueTrueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolValueTrue(this);
}
void rexLangParser::BoolValueTrueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolValueTrue(this);
}

antlrcpp::Any rexLangParser::BoolValueTrueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitBoolValueTrue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BoolValueFalseContext ------------------------------------------------------------------

rexLangParser::BoolValueFalseContext::BoolValueFalseContext(Bool_valueContext *ctx) { copyFrom(ctx); }

void rexLangParser::BoolValueFalseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolValueFalse(this);
}
void rexLangParser::BoolValueFalseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolValueFalse(this);
}

antlrcpp::Any rexLangParser::BoolValueFalseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitBoolValueFalse(this);
  else
    return visitor->visitChildren(this);
}
rexLangParser::Bool_valueContext* rexLangParser::bool_value() {
  Bool_valueContext *_localctx = _tracker.createInstance<Bool_valueContext>(_ctx, getState());
  enterRule(_localctx, 72, rexLangParser::RuleBool_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(779);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case rexLangParser::T__54: {
        _localctx = dynamic_cast<Bool_valueContext *>(_tracker.createInstance<rexLangParser::BoolValueTrueContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(777);
        dynamic_cast<BoolValueTrueContext *>(_localctx)->bval = match(rexLangParser::T__54);
        break;
      }

      case rexLangParser::T__55: {
        _localctx = dynamic_cast<Bool_valueContext *>(_tracker.createInstance<rexLangParser::BoolValueFalseContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(778);
        dynamic_cast<BoolValueFalseContext *>(_localctx)->bval = match(rexLangParser::T__55);
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

rexLangParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t rexLangParser::NumberContext::getRuleIndex() const {
  return rexLangParser::RuleNumber;
}

void rexLangParser::NumberContext::copyFrom(NumberContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FloatContext ------------------------------------------------------------------

tree::TerminalNode* rexLangParser::FloatContext::FLOAT_LITERAL() {
  return getToken(rexLangParser::FLOAT_LITERAL, 0);
}

rexLangParser::FloatContext::FloatContext(NumberContext *ctx) { copyFrom(ctx); }

void rexLangParser::FloatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloat(this);
}
void rexLangParser::FloatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloat(this);
}

antlrcpp::Any rexLangParser::FloatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitFloat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntContext ------------------------------------------------------------------

tree::TerminalNode* rexLangParser::IntContext::INTEGER_LITERAL() {
  return getToken(rexLangParser::INTEGER_LITERAL, 0);
}

rexLangParser::IntContext::IntContext(NumberContext *ctx) { copyFrom(ctx); }

void rexLangParser::IntContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInt(this);
}
void rexLangParser::IntContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInt(this);
}

antlrcpp::Any rexLangParser::IntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitInt(this);
  else
    return visitor->visitChildren(this);
}
rexLangParser::NumberContext* rexLangParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 74, rexLangParser::RuleNumber);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(783);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case rexLangParser::INTEGER_LITERAL: {
        _localctx = dynamic_cast<NumberContext *>(_tracker.createInstance<rexLangParser::IntContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(781);
        match(rexLangParser::INTEGER_LITERAL);
        break;
      }

      case rexLangParser::FLOAT_LITERAL: {
        _localctx = dynamic_cast<NumberContext *>(_tracker.createInstance<rexLangParser::FloatContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(782);
        match(rexLangParser::FLOAT_LITERAL);
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

rexLangParser::String_valueContext::String_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* rexLangParser::String_valueContext::STRING_LITERAL() {
  return getToken(rexLangParser::STRING_LITERAL, 0);
}


size_t rexLangParser::String_valueContext::getRuleIndex() const {
  return rexLangParser::RuleString_value;
}

void rexLangParser::String_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterString_value(this);
}

void rexLangParser::String_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<rexLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitString_value(this);
}


antlrcpp::Any rexLangParser::String_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<rexLangVisitor*>(visitor))
    return parserVisitor->visitString_value(this);
  else
    return visitor->visitChildren(this);
}

rexLangParser::String_valueContext* rexLangParser::string_value() {
  String_valueContext *_localctx = _tracker.createInstance<String_valueContext>(_ctx, getState());
  enterRule(_localctx, 76, rexLangParser::RuleString_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(785);
    match(rexLangParser::STRING_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool rexLangParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 29: return name_componentSempred(dynamic_cast<Name_componentContext *>(context), predicateIndex);
    case 30: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool rexLangParser::name_componentSempred(Name_componentContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool rexLangParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
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
std::vector<dfa::DFA> rexLangParser::_decisionToDFA;
atn::PredictionContextCache rexLangParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN rexLangParser::_atn;
std::vector<uint16_t> rexLangParser::_serializedATN;

std::vector<std::string> rexLangParser::_ruleNames = {
  "rexlang_src", "src_content", "program_set_file", "data_structure_file", 
  "global_variable_file", "dll_define_file", "dll_command", "lib_command", 
  "global_variable_list", "global_variable_item", "edition_spec", "struct_declare", 
  "table_comment", "prog_set", "variable_decl", "member_vari_decl", "file_vari_decl", 
  "sub_program", "local_variable_decl", "parameter_decl_list", "parameter_decl", 
  "vari_parameter_decl", "statement_list", "statement", "switch_statement", 
  "loop_statement", "condition_statement", "control_statement", "hierarchy_identifier", 
  "name_component", "expression", "data_set_value", "datetime_value", "datetime_value_core", 
  "macro_value", "func_ptr", "bool_value", "number", "string_value"
};

std::vector<std::string> rexLangParser::_literalNames = {
  "", "'.\u652F\u6301\u5E93'", "'.DLL\u547D\u4EE4'", "','", "'.LIB\u547D\u4EE4'", 
  "'.\u5168\u5C40\u53D8\u91CF'", "'.\u7248\u672C'", "'.\u6570\u636E\u7C7B\u578B'", 
  "'.\u6210\u5458'", "'.\u7A0B\u5E8F\u96C6'", "'.\u7A0B\u5E8F\u96C6\u53D8\u91CF'", 
  "'.\u5B50\u7A0B\u5E8F'", "'.\u5B50\u7A0B\u5E8F\u7ED3\u675F'", "'.\u5C40\u90E8\u53D8\u91CF'", 
  "'.\u53C2\u6570'", "'...'", "'.\u5224\u65AD\u5F00\u59CB'", "'('", "')'", 
  "'.\u5224\u65AD'", "'.\u9ED8\u8BA4'", "'.\u5224\u65AD\u7ED3\u675F'", "'.\u5224\u65AD\u5FAA\u73AF\u9996'", 
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

std::vector<std::string> rexLangParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "K_ADD_OPT", "K_SUB_OPT", "K_MUL_OPT", "K_DIV_OPT", "K_FULL_DIV_OPT", 
  "K_MOD_OPT", "K_AECOM_OPT", "K_ASSIGN_OPT", "K_EQUAL_OPT", "K_NOT_EQUAL_OPT", 
  "K_GREAT_OPT", "K_LESS_OPT", "K_GREAT_EQU_OPT", "K_LESS_EQU_OPT", "K_LIKE_EQU_OPT", 
  "K_OR_OPT", "K_AND_OPT", "INTEGER_LITERAL", "FLOAT_LITERAL", "IDENTIFIER", 
  "WHITESPACE", "NEWLINE", "STRING_LITERAL", "OTHER_CHAR"
};

dfa::Vocabulary rexLangParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> rexLangParser::_tokenNames;

rexLangParser::Initializer::Initializer() {
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
    0x3, 0x52, 0x316, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
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
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x53, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x56, 
    0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x5a, 0xa, 0x2, 0xc, 0x2, 0xe, 
    0x2, 0x5d, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x5, 0x3, 0x65, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 
    0x4, 0x6a, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x6d, 0xb, 0x4, 0x3, 0x4, 0x7, 
    0x4, 0x70, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x73, 0xb, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x5, 0x7, 0x5, 0x78, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x7b, 0xb, 
    0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x7, 0x7, 0x80, 0xa, 0x7, 0xc, 0x7, 
    0xe, 0x7, 0x83, 0xb, 0x7, 0x3, 0x7, 0x7, 0x7, 0x86, 0xa, 0x7, 0xc, 0x7, 
    0xe, 0x7, 0x89, 0xb, 0x7, 0x5, 0x7, 0x8b, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x91, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 
    0x8, 0x95, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 
    0x9b, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x9e, 0xb, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x5, 0x8, 0xa2, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0xa7, 
    0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0xaa, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x5, 0x9, 0xb0, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 
    0xb4, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0xba, 
    0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0xbd, 0xb, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 
    0x9, 0xc1, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0xc6, 0xa, 
    0x9, 0xc, 0x9, 0xe, 0x9, 0xc9, 0xb, 0x9, 0x3, 0xa, 0x7, 0xa, 0xcc, 0xa, 
    0xa, 0xc, 0xa, 0xe, 0xa, 0xcf, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x5, 0xb, 0xd5, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0xd9, 
    0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0xdd, 0xa, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x5, 0xb, 0xe1, 0xa, 0xb, 0x5, 0xb, 0xe3, 0xa, 0xb, 0x5, 0xb, 0xe5, 
    0xa, 0xb, 0x5, 0xb, 0xe7, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 
    0xd, 0xf3, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xf7, 0xa, 0xd, 0x5, 
    0xd, 0xf9, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0xfe, 0xa, 
    0xd, 0xc, 0xd, 0xe, 0xd, 0x101, 0xb, 0xd, 0x3, 0xd, 0x7, 0xd, 0x104, 
    0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x107, 0xb, 0xd, 0x3, 0xe, 0x7, 0xe, 0x10a, 
    0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x10d, 0xb, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x5, 0xf, 0x113, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 
    0x117, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x11b, 0xa, 0xf, 0x5, 
    0xf, 0x11d, 0xa, 0xf, 0x5, 0xf, 0x11f, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 
    0x3, 0xf, 0x7, 0xf, 0x124, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0x127, 0xb, 
    0xf, 0x3, 0xf, 0x7, 0xf, 0x12a, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0x12d, 
    0xb, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0x131, 0xa, 0xf, 0xc, 0xf, 0xe, 
    0xf, 0x134, 0xb, 0xf, 0x7, 0xf, 0x136, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 
    0x139, 0xb, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x13e, 
    0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 0x7, 0x10, 0x142, 0xa, 0x10, 0xc, 0x10, 
    0xe, 0x10, 0x145, 0xb, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x149, 
    0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x14d, 0xa, 0x10, 0x5, 0x10, 
    0x14f, 0xa, 0x10, 0x5, 0x10, 0x151, 0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x5, 0x13, 0x15d, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x5, 0x13, 0x161, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x165, 
    0xa, 0x13, 0x5, 0x13, 0x167, 0xa, 0x13, 0x5, 0x13, 0x169, 0xa, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0x16e, 0xa, 0x13, 0xc, 0x13, 
    0xe, 0x13, 0x171, 0xb, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x175, 
    0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x17b, 
    0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x17f, 0xa, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x5, 0x14, 0x183, 0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 
    0x187, 0xa, 0x14, 0x5, 0x14, 0x189, 0xa, 0x14, 0x5, 0x14, 0x18b, 0xa, 
    0x14, 0x5, 0x14, 0x18d, 0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 
    0x7, 0x15, 0x192, 0xa, 0x15, 0xc, 0x15, 0xe, 0x15, 0x195, 0xb, 0x15, 
    0x3, 0x15, 0x5, 0x15, 0x198, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x7, 0x16, 0x1a0, 0xa, 0x16, 0xc, 0x16, 
    0xe, 0x16, 0x1a3, 0xb, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x1a7, 
    0xa, 0x16, 0x5, 0x16, 0x1a9, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x7, 0x17, 0x1b3, 
    0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 0x1b6, 0xb, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x5, 0x17, 0x1ba, 0xa, 0x17, 0x5, 0x17, 0x1bc, 0xa, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x18, 0x5, 0x18, 0x1c1, 0xa, 0x18, 0x3, 0x18, 0x7, 0x18, 
    0x1c4, 0xa, 0x18, 0xc, 0x18, 0xe, 0x18, 0x1c7, 0xb, 0x18, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x5, 0x19, 0x1d2, 0xa, 0x19, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 
    0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x7, 0x1a, 0x1e1, 
    0xa, 0x1a, 0xc, 0x1a, 0xe, 0x1a, 0x1e4, 0xb, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x1fa, 
    0xa, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x20c, 0xa, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x21f, 0xa, 0x1b, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 
    0x1c, 0x5, 0x1c, 0x228, 0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 
    0x1c, 0x233, 0xa, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x23e, 
    0xa, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x244, 
    0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 0x249, 0xa, 0x1e, 
    0xc, 0x1e, 0xe, 0x1e, 0x24c, 0xb, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 
    0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x254, 0xa, 0x1f, 0x3, 0x1f, 
    0x3, 0x1f, 0x5, 0x1f, 0x258, 0xa, 0x1f, 0x7, 0x1f, 0x25a, 0xa, 0x1f, 
    0xc, 0x1f, 0xe, 0x1f, 0x25d, 0xb, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 
    0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x7, 0x1f, 0x265, 0xa, 0x1f, 0xc, 0x1f, 
    0xe, 0x1f, 0x268, 0xb, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x279, 
    0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x7, 0x20, 0x2ab, 0xa, 0x20, 
    0xc, 0x20, 0xe, 0x20, 0x2ae, 0xb, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x21, 0x7, 0x21, 0x2b4, 0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 0x2b7, 
    0xb, 0x21, 0x5, 0x21, 0x2b9, 0xa, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 0x2ce, 0xa, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 0x2db, 0xa, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 0x2e8, 
    0xa, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 
    0x2f5, 0xa, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 
    0x23, 0x302, 0xa, 0x23, 0x5, 0x23, 0x304, 0xa, 0x23, 0x3, 0x24, 0x3, 
    0x24, 0x3, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x26, 0x3, 0x26, 
    0x5, 0x26, 0x30e, 0xa, 0x26, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x312, 
    0xa, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x10b, 0x4, 0x3c, 0x3e, 
    0x29, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
    0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 
    0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 
    0x4a, 0x4c, 0x4e, 0x2, 0x3, 0x3, 0x2, 0x41, 0x42, 0x2, 0x376, 0x2, 0x50, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x64, 0x3, 0x2, 0x2, 0x2, 0x6, 0x6b, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x79, 0x3, 0x2, 0x2, 0x2, 0xa, 0x7c, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x8a, 0x3, 0x2, 0x2, 0x2, 0xe, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0xab, 0x3, 0x2, 0x2, 0x2, 0x12, 0xcd, 0x3, 0x2, 0x2, 0x2, 0x14, 0xd0, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0xea, 0x3, 0x2, 0x2, 0x2, 0x18, 0xee, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x10e, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x20, 0x154, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0x156, 0x3, 0x2, 0x2, 0x2, 0x24, 0x158, 0x3, 0x2, 0x2, 0x2, 
    0x26, 0x176, 0x3, 0x2, 0x2, 0x2, 0x28, 0x193, 0x3, 0x2, 0x2, 0x2, 0x2a, 
    0x199, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x1ac, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x1c5, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0x1d1, 0x3, 0x2, 0x2, 0x2, 0x32, 0x1d3, 0x3, 
    0x2, 0x2, 0x2, 0x34, 0x21e, 0x3, 0x2, 0x2, 0x2, 0x36, 0x232, 0x3, 0x2, 
    0x2, 0x2, 0x38, 0x243, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x245, 0x3, 0x2, 0x2, 
    0x2, 0x3c, 0x24d, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x278, 0x3, 0x2, 0x2, 0x2, 
    0x40, 0x2af, 0x3, 0x2, 0x2, 0x2, 0x42, 0x2bc, 0x3, 0x2, 0x2, 0x2, 0x44, 
    0x303, 0x3, 0x2, 0x2, 0x2, 0x46, 0x305, 0x3, 0x2, 0x2, 0x2, 0x48, 0x308, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x30d, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x311, 0x3, 
    0x2, 0x2, 0x2, 0x4e, 0x313, 0x3, 0x2, 0x2, 0x2, 0x50, 0x54, 0x5, 0x16, 
    0xc, 0x2, 0x51, 0x53, 0x7, 0x50, 0x2, 0x2, 0x52, 0x51, 0x3, 0x2, 0x2, 
    0x2, 0x53, 0x56, 0x3, 0x2, 0x2, 0x2, 0x54, 0x52, 0x3, 0x2, 0x2, 0x2, 
    0x54, 0x55, 0x3, 0x2, 0x2, 0x2, 0x55, 0x57, 0x3, 0x2, 0x2, 0x2, 0x56, 
    0x54, 0x3, 0x2, 0x2, 0x2, 0x57, 0x5b, 0x5, 0x4, 0x3, 0x2, 0x58, 0x5a, 
    0x7, 0x50, 0x2, 0x2, 0x59, 0x58, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5d, 0x3, 
    0x2, 0x2, 0x2, 0x5b, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5c, 0x3, 0x2, 
    0x2, 0x2, 0x5c, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5b, 0x3, 0x2, 0x2, 
    0x2, 0x5e, 0x5f, 0x7, 0x2, 0x2, 0x3, 0x5f, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x60, 0x65, 0x5, 0x6, 0x4, 0x2, 0x61, 0x65, 0x5, 0x8, 0x5, 0x2, 0x62, 
    0x65, 0x5, 0xa, 0x6, 0x2, 0x63, 0x65, 0x5, 0xc, 0x7, 0x2, 0x64, 0x60, 
    0x3, 0x2, 0x2, 0x2, 0x64, 0x61, 0x3, 0x2, 0x2, 0x2, 0x64, 0x62, 0x3, 
    0x2, 0x2, 0x2, 0x64, 0x63, 0x3, 0x2, 0x2, 0x2, 0x65, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x66, 0x67, 0x7, 0x3, 0x2, 0x2, 0x67, 0x68, 0x7, 0x4e, 0x2, 
    0x2, 0x68, 0x6a, 0x7, 0x50, 0x2, 0x2, 0x69, 0x66, 0x3, 0x2, 0x2, 0x2, 
    0x6a, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6b, 
    0x6c, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x71, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6b, 
    0x3, 0x2, 0x2, 0x2, 0x6e, 0x70, 0x7, 0x50, 0x2, 0x2, 0x6f, 0x6e, 0x3, 
    0x2, 0x2, 0x2, 0x70, 0x73, 0x3, 0x2, 0x2, 0x2, 0x71, 0x6f, 0x3, 0x2, 
    0x2, 0x2, 0x71, 0x72, 0x3, 0x2, 0x2, 0x2, 0x72, 0x74, 0x3, 0x2, 0x2, 
    0x2, 0x73, 0x71, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x5, 0x1c, 0xf, 0x2, 
    0x75, 0x7, 0x3, 0x2, 0x2, 0x2, 0x76, 0x78, 0x5, 0x18, 0xd, 0x2, 0x77, 
    0x76, 0x3, 0x2, 0x2, 0x2, 0x78, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x79, 0x77, 
    0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x7b, 0x79, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x5, 0x12, 
    0xa, 0x2, 0x7d, 0xb, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x80, 0x5, 0xe, 0x8, 
    0x2, 0x7f, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x80, 0x83, 0x3, 0x2, 0x2, 0x2, 
    0x81, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x3, 0x2, 0x2, 0x2, 0x82, 
    0x8b, 0x3, 0x2, 0x2, 0x2, 0x83, 0x81, 0x3, 0x2, 0x2, 0x2, 0x84, 0x86, 
    0x5, 0x10, 0x9, 0x2, 0x85, 0x84, 0x3, 0x2, 0x2, 0x2, 0x86, 0x89, 0x3, 
    0x2, 0x2, 0x2, 0x87, 0x85, 0x3, 0x2, 0x2, 0x2, 0x87, 0x88, 0x3, 0x2, 
    0x2, 0x2, 0x88, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x89, 0x87, 0x3, 0x2, 0x2, 
    0x2, 0x8a, 0x81, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x87, 0x3, 0x2, 0x2, 0x2, 
    0x8b, 0xd, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x7, 0x4, 0x2, 0x2, 0x8d, 
    0x8e, 0x7, 0x4e, 0x2, 0x2, 0x8e, 0x90, 0x7, 0x5, 0x2, 0x2, 0x8f, 0x91, 
    0x7, 0x4e, 0x2, 0x2, 0x90, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x3, 
    0x2, 0x2, 0x2, 0x91, 0x92, 0x3, 0x2, 0x2, 0x2, 0x92, 0x94, 0x7, 0x5, 
    0x2, 0x2, 0x93, 0x95, 0x7, 0x51, 0x2, 0x2, 0x94, 0x93, 0x3, 0x2, 0x2, 
    0x2, 0x94, 0x95, 0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 0x3, 0x2, 0x2, 0x2, 
    0x96, 0x97, 0x7, 0x5, 0x2, 0x2, 0x97, 0x98, 0x7, 0x51, 0x2, 0x2, 0x98, 
    0x9c, 0x7, 0x5, 0x2, 0x2, 0x99, 0x9b, 0x7, 0x4e, 0x2, 0x2, 0x9a, 0x99, 
    0x3, 0x2, 0x2, 0x2, 0x9b, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9a, 0x3, 
    0x2, 0x2, 0x2, 0x9c, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x9d, 0xa1, 0x3, 0x2, 
    0x2, 0x2, 0x9e, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x9f, 0xa0, 0x7, 0x5, 0x2, 
    0x2, 0xa0, 0xa2, 0x5, 0x1a, 0xe, 0x2, 0xa1, 0x9f, 0x3, 0x2, 0x2, 0x2, 
    0xa1, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa3, 
    0xa4, 0x7, 0x50, 0x2, 0x2, 0xa4, 0xa8, 0x5, 0x28, 0x15, 0x2, 0xa5, 0xa7, 
    0x7, 0x50, 0x2, 0x2, 0xa6, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xaa, 0x3, 
    0x2, 0x2, 0x2, 0xa8, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x3, 0x2, 
    0x2, 0x2, 0xa9, 0xf, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xa8, 0x3, 0x2, 0x2, 
    0x2, 0xab, 0xac, 0x7, 0x6, 0x2, 0x2, 0xac, 0xad, 0x7, 0x4e, 0x2, 0x2, 
    0xad, 0xaf, 0x7, 0x5, 0x2, 0x2, 0xae, 0xb0, 0x7, 0x4e, 0x2, 0x2, 0xaf, 
    0xae, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 
    0x3, 0x2, 0x2, 0x2, 0xb1, 0xb3, 0x7, 0x5, 0x2, 0x2, 0xb2, 0xb4, 0x7, 
    0x51, 0x2, 0x2, 0xb3, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb4, 0x3, 0x2, 
    0x2, 0x2, 0xb4, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb6, 0x7, 0x5, 0x2, 
    0x2, 0xb6, 0xb7, 0x7, 0x51, 0x2, 0x2, 0xb7, 0xbb, 0x7, 0x5, 0x2, 0x2, 
    0xb8, 0xba, 0x7, 0x4e, 0x2, 0x2, 0xb9, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xba, 
    0xbd, 0x3, 0x2, 0x2, 0x2, 0xbb, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xbb, 0xbc, 
    0x3, 0x2, 0x2, 0x2, 0xbc, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbb, 0x3, 
    0x2, 0x2, 0x2, 0xbe, 0xbf, 0x7, 0x5, 0x2, 0x2, 0xbf, 0xc1, 0x5, 0x1a, 
    0xe, 0x2, 0xc0, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xc1, 0x3, 0x2, 0x2, 
    0x2, 0xc1, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc3, 0x7, 0x50, 0x2, 0x2, 
    0xc3, 0xc7, 0x5, 0x28, 0x15, 0x2, 0xc4, 0xc6, 0x7, 0x50, 0x2, 0x2, 0xc5, 
    0xc4, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc5, 
    0x3, 0x2, 0x2, 0x2, 0xc7, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xc8, 0x11, 0x3, 
    0x2, 0x2, 0x2, 0xc9, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcc, 0x5, 0x14, 
    0xb, 0x2, 0xcb, 0xca, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xcf, 0x3, 0x2, 0x2, 
    0x2, 0xcd, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 0x3, 0x2, 0x2, 0x2, 
    0xce, 0x13, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xd0, 
    0xd1, 0x7, 0x7, 0x2, 0x2, 0xd1, 0xe6, 0x7, 0x4e, 0x2, 0x2, 0xd2, 0xd4, 
    0x7, 0x5, 0x2, 0x2, 0xd3, 0xd5, 0x7, 0x4e, 0x2, 0x2, 0xd4, 0xd3, 0x3, 
    0x2, 0x2, 0x2, 0xd4, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xe4, 0x3, 0x2, 
    0x2, 0x2, 0xd6, 0xd8, 0x7, 0x5, 0x2, 0x2, 0xd7, 0xd9, 0x7, 0x4e, 0x2, 
    0x2, 0xd8, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd9, 0x3, 0x2, 0x2, 0x2, 
    0xd9, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xda, 0xdc, 0x7, 0x5, 0x2, 0x2, 0xdb, 
    0xdd, 0x7, 0x51, 0x2, 0x2, 0xdc, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdd, 
    0x3, 0x2, 0x2, 0x2, 0xdd, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xde, 0xdf, 0x7, 
    0x5, 0x2, 0x2, 0xdf, 0xe1, 0x5, 0x1a, 0xe, 0x2, 0xe0, 0xde, 0x3, 0x2, 
    0x2, 0x2, 0xe0, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe3, 0x3, 0x2, 0x2, 
    0x2, 0xe2, 0xda, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe3, 0x3, 0x2, 0x2, 0x2, 
    0xe3, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xe4, 
    0xe5, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xd2, 
    0x3, 0x2, 0x2, 0x2, 0xe6, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe8, 0x3, 
    0x2, 0x2, 0x2, 0xe8, 0xe9, 0x7, 0x50, 0x2, 0x2, 0xe9, 0x15, 0x3, 0x2, 
    0x2, 0x2, 0xea, 0xeb, 0x7, 0x8, 0x2, 0x2, 0xeb, 0xec, 0x7, 0x4c, 0x2, 
    0x2, 0xec, 0xed, 0x7, 0x50, 0x2, 0x2, 0xed, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0xee, 0xef, 0x7, 0x9, 0x2, 0x2, 0xef, 0xf8, 0x7, 0x4e, 0x2, 0x2, 0xf0, 
    0xf2, 0x7, 0x5, 0x2, 0x2, 0xf1, 0xf3, 0x7, 0x4e, 0x2, 0x2, 0xf2, 0xf1, 
    0x3, 0x2, 0x2, 0x2, 0xf2, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf3, 0xf6, 0x3, 
    0x2, 0x2, 0x2, 0xf4, 0xf5, 0x7, 0x5, 0x2, 0x2, 0xf5, 0xf7, 0x5, 0x1a, 
    0xe, 0x2, 0xf6, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf7, 0x3, 0x2, 0x2, 
    0x2, 0xf7, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf0, 0x3, 0x2, 0x2, 0x2, 
    0xf8, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xfa, 
    0xff, 0x7, 0x50, 0x2, 0x2, 0xfb, 0xfc, 0x7, 0xa, 0x2, 0x2, 0xfc, 0xfe, 
    0x5, 0x20, 0x11, 0x2, 0xfd, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xfe, 0x101, 0x3, 
    0x2, 0x2, 0x2, 0xff, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xff, 0x100, 0x3, 0x2, 
    0x2, 0x2, 0x100, 0x105, 0x3, 0x2, 0x2, 0x2, 0x101, 0xff, 0x3, 0x2, 0x2, 
    0x2, 0x102, 0x104, 0x7, 0x50, 0x2, 0x2, 0x103, 0x102, 0x3, 0x2, 0x2, 
    0x2, 0x104, 0x107, 0x3, 0x2, 0x2, 0x2, 0x105, 0x103, 0x3, 0x2, 0x2, 
    0x2, 0x105, 0x106, 0x3, 0x2, 0x2, 0x2, 0x106, 0x19, 0x3, 0x2, 0x2, 0x2, 
    0x107, 0x105, 0x3, 0x2, 0x2, 0x2, 0x108, 0x10a, 0xb, 0x2, 0x2, 0x2, 
    0x109, 0x108, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10d, 0x3, 0x2, 0x2, 0x2, 
    0x10b, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x109, 0x3, 0x2, 0x2, 0x2, 
    0x10c, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x10e, 
    0x10f, 0x7, 0xb, 0x2, 0x2, 0x10f, 0x11e, 0x7, 0x4e, 0x2, 0x2, 0x110, 
    0x112, 0x7, 0x5, 0x2, 0x2, 0x111, 0x113, 0x7, 0x4e, 0x2, 0x2, 0x112, 
    0x111, 0x3, 0x2, 0x2, 0x2, 0x112, 0x113, 0x3, 0x2, 0x2, 0x2, 0x113, 
    0x11c, 0x3, 0x2, 0x2, 0x2, 0x114, 0x116, 0x7, 0x5, 0x2, 0x2, 0x115, 
    0x117, 0x7, 0x4e, 0x2, 0x2, 0x116, 0x115, 0x3, 0x2, 0x2, 0x2, 0x116, 
    0x117, 0x3, 0x2, 0x2, 0x2, 0x117, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x118, 
    0x119, 0x7, 0x5, 0x2, 0x2, 0x119, 0x11b, 0x5, 0x1a, 0xe, 0x2, 0x11a, 
    0x118, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x11b, 
    0x11d, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x114, 0x3, 0x2, 0x2, 0x2, 0x11c, 
    0x11d, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x11e, 
    0x110, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x11f, 
    0x120, 0x3, 0x2, 0x2, 0x2, 0x120, 0x125, 0x7, 0x50, 0x2, 0x2, 0x121, 
    0x122, 0x7, 0xc, 0x2, 0x2, 0x122, 0x124, 0x5, 0x22, 0x12, 0x2, 0x123, 
    0x121, 0x3, 0x2, 0x2, 0x2, 0x124, 0x127, 0x3, 0x2, 0x2, 0x2, 0x125, 
    0x123, 0x3, 0x2, 0x2, 0x2, 0x125, 0x126, 0x3, 0x2, 0x2, 0x2, 0x126, 
    0x137, 0x3, 0x2, 0x2, 0x2, 0x127, 0x125, 0x3, 0x2, 0x2, 0x2, 0x128, 
    0x12a, 0x7, 0x50, 0x2, 0x2, 0x129, 0x128, 0x3, 0x2, 0x2, 0x2, 0x12a, 
    0x12d, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x129, 0x3, 0x2, 0x2, 0x2, 0x12b, 
    0x12c, 0x3, 0x2, 0x2, 0x2, 0x12c, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x12d, 
    0x12b, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x132, 0x5, 0x24, 0x13, 0x2, 0x12f, 
    0x131, 0x7, 0x50, 0x2, 0x2, 0x130, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x131, 
    0x134, 0x3, 0x2, 0x2, 0x2, 0x132, 0x130, 0x3, 0x2, 0x2, 0x2, 0x132, 
    0x133, 0x3, 0x2, 0x2, 0x2, 0x133, 0x136, 0x3, 0x2, 0x2, 0x2, 0x134, 
    0x132, 0x3, 0x2, 0x2, 0x2, 0x135, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x136, 
    0x139, 0x3, 0x2, 0x2, 0x2, 0x137, 0x135, 0x3, 0x2, 0x2, 0x2, 0x137, 
    0x138, 0x3, 0x2, 0x2, 0x2, 0x138, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x139, 0x137, 
    0x3, 0x2, 0x2, 0x2, 0x13a, 0x150, 0x7, 0x4e, 0x2, 0x2, 0x13b, 0x13d, 
    0x7, 0x5, 0x2, 0x2, 0x13c, 0x13e, 0x7, 0x4e, 0x2, 0x2, 0x13d, 0x13c, 
    0x3, 0x2, 0x2, 0x2, 0x13d, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x13e, 0x14e, 
    0x3, 0x2, 0x2, 0x2, 0x13f, 0x143, 0x7, 0x5, 0x2, 0x2, 0x140, 0x142, 
    0x7, 0x4e, 0x2, 0x2, 0x141, 0x140, 0x3, 0x2, 0x2, 0x2, 0x142, 0x145, 
    0x3, 0x2, 0x2, 0x2, 0x143, 0x141, 0x3, 0x2, 0x2, 0x2, 0x143, 0x144, 
    0x3, 0x2, 0x2, 0x2, 0x144, 0x146, 0x3, 0x2, 0x2, 0x2, 0x145, 0x143, 
    0x3, 0x2, 0x2, 0x2, 0x146, 0x148, 0x7, 0x5, 0x2, 0x2, 0x147, 0x149, 
    0x7, 0x51, 0x2, 0x2, 0x148, 0x147, 0x3, 0x2, 0x2, 0x2, 0x148, 0x149, 
    0x3, 0x2, 0x2, 0x2, 0x149, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x14b, 
    0x7, 0x5, 0x2, 0x2, 0x14b, 0x14d, 0x5, 0x1a, 0xe, 0x2, 0x14c, 0x14a, 
    0x3, 0x2, 0x2, 0x2, 0x14c, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x14f, 
    0x3, 0x2, 0x2, 0x2, 0x14e, 0x13f, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 
    0x3, 0x2, 0x2, 0x2, 0x14f, 0x151, 0x3, 0x2, 0x2, 0x2, 0x150, 0x13b, 
    0x3, 0x2, 0x2, 0x2, 0x150, 0x151, 0x3, 0x2, 0x2, 0x2, 0x151, 0x152, 
    0x3, 0x2, 0x2, 0x2, 0x152, 0x153, 0x7, 0x50, 0x2, 0x2, 0x153, 0x1f, 
    0x3, 0x2, 0x2, 0x2, 0x154, 0x155, 0x5, 0x1e, 0x10, 0x2, 0x155, 0x21, 
    0x3, 0x2, 0x2, 0x2, 0x156, 0x157, 0x5, 0x1e, 0x10, 0x2, 0x157, 0x23, 
    0x3, 0x2, 0x2, 0x2, 0x158, 0x159, 0x7, 0xd, 0x2, 0x2, 0x159, 0x168, 
    0x7, 0x4e, 0x2, 0x2, 0x15a, 0x15c, 0x7, 0x5, 0x2, 0x2, 0x15b, 0x15d, 
    0x7, 0x4e, 0x2, 0x2, 0x15c, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x15c, 0x15d, 
    0x3, 0x2, 0x2, 0x2, 0x15d, 0x166, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x160, 
    0x7, 0x5, 0x2, 0x2, 0x15f, 0x161, 0x7, 0x4e, 0x2, 0x2, 0x160, 0x15f, 
    0x3, 0x2, 0x2, 0x2, 0x160, 0x161, 0x3, 0x2, 0x2, 0x2, 0x161, 0x164, 
    0x3, 0x2, 0x2, 0x2, 0x162, 0x163, 0x7, 0x5, 0x2, 0x2, 0x163, 0x165, 
    0x5, 0x1a, 0xe, 0x2, 0x164, 0x162, 0x3, 0x2, 0x2, 0x2, 0x164, 0x165, 
    0x3, 0x2, 0x2, 0x2, 0x165, 0x167, 0x3, 0x2, 0x2, 0x2, 0x166, 0x15e, 
    0x3, 0x2, 0x2, 0x2, 0x166, 0x167, 0x3, 0x2, 0x2, 0x2, 0x167, 0x169, 
    0x3, 0x2, 0x2, 0x2, 0x168, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 
    0x3, 0x2, 0x2, 0x2, 0x169, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x16b, 
    0x7, 0x50, 0x2, 0x2, 0x16b, 0x16f, 0x5, 0x28, 0x15, 0x2, 0x16c, 0x16e, 
    0x5, 0x26, 0x14, 0x2, 0x16d, 0x16c, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x171, 
    0x3, 0x2, 0x2, 0x2, 0x16f, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x170, 
    0x3, 0x2, 0x2, 0x2, 0x170, 0x172, 0x3, 0x2, 0x2, 0x2, 0x171, 0x16f, 
    0x3, 0x2, 0x2, 0x2, 0x172, 0x174, 0x5, 0x2e, 0x18, 0x2, 0x173, 0x175, 
    0x7, 0xe, 0x2, 0x2, 0x174, 0x173, 0x3, 0x2, 0x2, 0x2, 0x174, 0x175, 
    0x3, 0x2, 0x2, 0x2, 0x175, 0x25, 0x3, 0x2, 0x2, 0x2, 0x176, 0x177, 0x7, 
    0xf, 0x2, 0x2, 0x177, 0x18c, 0x7, 0x4e, 0x2, 0x2, 0x178, 0x17a, 0x7, 
    0x5, 0x2, 0x2, 0x179, 0x17b, 0x7, 0x4e, 0x2, 0x2, 0x17a, 0x179, 0x3, 
    0x2, 0x2, 0x2, 0x17a, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x18a, 0x3, 
    0x2, 0x2, 0x2, 0x17c, 0x17e, 0x7, 0x5, 0x2, 0x2, 0x17d, 0x17f, 0x7, 
    0x4e, 0x2, 0x2, 0x17e, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x17f, 0x3, 
    0x2, 0x2, 0x2, 0x17f, 0x188, 0x3, 0x2, 0x2, 0x2, 0x180, 0x182, 0x7, 
    0x5, 0x2, 0x2, 0x181, 0x183, 0x7, 0x51, 0x2, 0x2, 0x182, 0x181, 0x3, 
    0x2, 0x2, 0x2, 0x182, 0x183, 0x3, 0x2, 0x2, 0x2, 0x183, 0x186, 0x3, 
    0x2, 0x2, 0x2, 0x184, 0x185, 0x7, 0x5, 0x2, 0x2, 0x185, 0x187, 0x5, 
    0x1a, 0xe, 0x2, 0x186, 0x184, 0x3, 0x2, 0x2, 0x2, 0x186, 0x187, 0x3, 
    0x2, 0x2, 0x2, 0x187, 0x189, 0x3, 0x2, 0x2, 0x2, 0x188, 0x180, 0x3, 
    0x2, 0x2, 0x2, 0x188, 0x189, 0x3, 0x2, 0x2, 0x2, 0x189, 0x18b, 0x3, 
    0x2, 0x2, 0x2, 0x18a, 0x17c, 0x3, 0x2, 0x2, 0x2, 0x18a, 0x18b, 0x3, 
    0x2, 0x2, 0x2, 0x18b, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x18c, 0x178, 0x3, 
    0x2, 0x2, 0x2, 0x18c, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x18e, 0x3, 
    0x2, 0x2, 0x2, 0x18e, 0x18f, 0x7, 0x50, 0x2, 0x2, 0x18f, 0x27, 0x3, 
    0x2, 0x2, 0x2, 0x190, 0x192, 0x5, 0x2a, 0x16, 0x2, 0x191, 0x190, 0x3, 
    0x2, 0x2, 0x2, 0x192, 0x195, 0x3, 0x2, 0x2, 0x2, 0x193, 0x191, 0x3, 
    0x2, 0x2, 0x2, 0x193, 0x194, 0x3, 0x2, 0x2, 0x2, 0x194, 0x197, 0x3, 
    0x2, 0x2, 0x2, 0x195, 0x193, 0x3, 0x2, 0x2, 0x2, 0x196, 0x198, 0x5, 
    0x2c, 0x17, 0x2, 0x197, 0x196, 0x3, 0x2, 0x2, 0x2, 0x197, 0x198, 0x3, 
    0x2, 0x2, 0x2, 0x198, 0x29, 0x3, 0x2, 0x2, 0x2, 0x199, 0x19a, 0x7, 0x10, 
    0x2, 0x2, 0x19a, 0x19b, 0x7, 0x4e, 0x2, 0x2, 0x19b, 0x19c, 0x7, 0x5, 
    0x2, 0x2, 0x19c, 0x1a8, 0x7, 0x4e, 0x2, 0x2, 0x19d, 0x1a1, 0x7, 0x5, 
    0x2, 0x2, 0x19e, 0x1a0, 0x7, 0x4e, 0x2, 0x2, 0x19f, 0x19e, 0x3, 0x2, 
    0x2, 0x2, 0x1a0, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x19f, 0x3, 0x2, 
    0x2, 0x2, 0x1a1, 0x1a2, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x1a6, 0x3, 0x2, 
    0x2, 0x2, 0x1a3, 0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a5, 0x7, 0x5, 
    0x2, 0x2, 0x1a5, 0x1a7, 0x5, 0x1a, 0xe, 0x2, 0x1a6, 0x1a4, 0x3, 0x2, 
    0x2, 0x2, 0x1a6, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1a7, 0x1a9, 0x3, 0x2, 
    0x2, 0x2, 0x1a8, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x1a8, 0x1a9, 0x3, 0x2, 
    0x2, 0x2, 0x1a9, 0x1aa, 0x3, 0x2, 0x2, 0x2, 0x1aa, 0x1ab, 0x7, 0x50, 
    0x2, 0x2, 0x1ab, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x1ac, 0x1ad, 0x7, 0x10, 
    0x2, 0x2, 0x1ad, 0x1ae, 0x7, 0x11, 0x2, 0x2, 0x1ae, 0x1af, 0x7, 0x5, 
    0x2, 0x2, 0x1af, 0x1bb, 0x7, 0x4e, 0x2, 0x2, 0x1b0, 0x1b4, 0x7, 0x5, 
    0x2, 0x2, 0x1b1, 0x1b3, 0x7, 0x4e, 0x2, 0x2, 0x1b2, 0x1b1, 0x3, 0x2, 
    0x2, 0x2, 0x1b3, 0x1b6, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b2, 0x3, 0x2, 
    0x2, 0x2, 0x1b4, 0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1b5, 0x1b9, 0x3, 0x2, 
    0x2, 0x2, 0x1b6, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1b8, 0x7, 0x5, 
    0x2, 0x2, 0x1b8, 0x1ba, 0x5, 0x1a, 0xe, 0x2, 0x1b9, 0x1b7, 0x3, 0x2, 
    0x2, 0x2, 0x1b9, 0x1ba, 0x3, 0x2, 0x2, 0x2, 0x1ba, 0x1bc, 0x3, 0x2, 
    0x2, 0x2, 0x1bb, 0x1b0, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bc, 0x3, 0x2, 
    0x2, 0x2, 0x1bc, 0x1bd, 0x3, 0x2, 0x2, 0x2, 0x1bd, 0x1be, 0x7, 0x50, 
    0x2, 0x2, 0x1be, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x1bf, 0x1c1, 0x5, 0x30, 
    0x19, 0x2, 0x1c0, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x1c1, 0x3, 0x2, 
    0x2, 0x2, 0x1c1, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c2, 0x1c4, 0x7, 0x50, 
    0x2, 0x2, 0x1c3, 0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1c4, 0x1c7, 0x3, 0x2, 
    0x2, 0x2, 0x1c5, 0x1c3, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1c6, 0x3, 0x2, 
    0x2, 0x2, 0x1c6, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x1c7, 0x1c5, 0x3, 0x2, 0x2, 
    0x2, 0x1c8, 0x1d2, 0x5, 0x36, 0x1c, 0x2, 0x1c9, 0x1ca, 0x5, 0x3a, 0x1e, 
    0x2, 0x1ca, 0x1cb, 0x9, 0x2, 0x2, 0x2, 0x1cb, 0x1cc, 0x5, 0x3e, 0x20, 
    0x2, 0x1cc, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x1cd, 0x1d2, 0x5, 0x3e, 0x20, 
    0x2, 0x1ce, 0x1d2, 0x5, 0x34, 0x1b, 0x2, 0x1cf, 0x1d2, 0x5, 0x32, 0x1a, 
    0x2, 0x1d0, 0x1d2, 0x5, 0x38, 0x1d, 0x2, 0x1d1, 0x1c8, 0x3, 0x2, 0x2, 
    0x2, 0x1d1, 0x1c9, 0x3, 0x2, 0x2, 0x2, 0x1d1, 0x1cd, 0x3, 0x2, 0x2, 
    0x2, 0x1d1, 0x1ce, 0x3, 0x2, 0x2, 0x2, 0x1d1, 0x1cf, 0x3, 0x2, 0x2, 
    0x2, 0x1d1, 0x1d0, 0x3, 0x2, 0x2, 0x2, 0x1d2, 0x31, 0x3, 0x2, 0x2, 0x2, 
    0x1d3, 0x1d4, 0x7, 0x12, 0x2, 0x2, 0x1d4, 0x1d5, 0x7, 0x13, 0x2, 0x2, 
    0x1d5, 0x1d6, 0x5, 0x3e, 0x20, 0x2, 0x1d6, 0x1d7, 0x7, 0x14, 0x2, 0x2, 
    0x1d7, 0x1d8, 0x7, 0x50, 0x2, 0x2, 0x1d8, 0x1e2, 0x5, 0x2e, 0x18, 0x2, 
    0x1d9, 0x1da, 0x7, 0x15, 0x2, 0x2, 0x1da, 0x1db, 0x7, 0x13, 0x2, 0x2, 
    0x1db, 0x1dc, 0x5, 0x3e, 0x20, 0x2, 0x1dc, 0x1dd, 0x7, 0x14, 0x2, 0x2, 
    0x1dd, 0x1de, 0x7, 0x50, 0x2, 0x2, 0x1de, 0x1df, 0x5, 0x2e, 0x18, 0x2, 
    0x1df, 0x1e1, 0x3, 0x2, 0x2, 0x2, 0x1e0, 0x1d9, 0x3, 0x2, 0x2, 0x2, 
    0x1e1, 0x1e4, 0x3, 0x2, 0x2, 0x2, 0x1e2, 0x1e0, 0x3, 0x2, 0x2, 0x2, 
    0x1e2, 0x1e3, 0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e5, 0x3, 0x2, 0x2, 0x2, 
    0x1e4, 0x1e2, 0x3, 0x2, 0x2, 0x2, 0x1e5, 0x1e6, 0x7, 0x16, 0x2, 0x2, 
    0x1e6, 0x1e7, 0x7, 0x50, 0x2, 0x2, 0x1e7, 0x1e8, 0x5, 0x2e, 0x18, 0x2, 
    0x1e8, 0x1e9, 0x7, 0x17, 0x2, 0x2, 0x1e9, 0x33, 0x3, 0x2, 0x2, 0x2, 
    0x1ea, 0x1eb, 0x7, 0x18, 0x2, 0x2, 0x1eb, 0x1ec, 0x7, 0x13, 0x2, 0x2, 
    0x1ec, 0x1ed, 0x5, 0x3e, 0x20, 0x2, 0x1ed, 0x1ee, 0x7, 0x14, 0x2, 0x2, 
    0x1ee, 0x1ef, 0x7, 0x50, 0x2, 0x2, 0x1ef, 0x1f0, 0x5, 0x2e, 0x18, 0x2, 
    0x1f0, 0x1f1, 0x7, 0x19, 0x2, 0x2, 0x1f1, 0x1f2, 0x7, 0x13, 0x2, 0x2, 
    0x1f2, 0x1f3, 0x7, 0x14, 0x2, 0x2, 0x1f3, 0x21f, 0x3, 0x2, 0x2, 0x2, 
    0x1f4, 0x1f5, 0x7, 0x1a, 0x2, 0x2, 0x1f5, 0x1f6, 0x7, 0x13, 0x2, 0x2, 
    0x1f6, 0x1f7, 0x5, 0x3e, 0x20, 0x2, 0x1f7, 0x1f9, 0x7, 0x5, 0x2, 0x2, 
    0x1f8, 0x1fa, 0x5, 0x3a, 0x1e, 0x2, 0x1f9, 0x1f8, 0x3, 0x2, 0x2, 0x2, 
    0x1f9, 0x1fa, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fb, 0x3, 0x2, 0x2, 0x2, 
    0x1fb, 0x1fc, 0x7, 0x14, 0x2, 0x2, 0x1fc, 0x1fd, 0x7, 0x50, 0x2, 0x2, 
    0x1fd, 0x1fe, 0x5, 0x2e, 0x18, 0x2, 0x1fe, 0x1ff, 0x7, 0x1b, 0x2, 0x2, 
    0x1ff, 0x200, 0x7, 0x13, 0x2, 0x2, 0x200, 0x201, 0x7, 0x14, 0x2, 0x2, 
    0x201, 0x21f, 0x3, 0x2, 0x2, 0x2, 0x202, 0x203, 0x7, 0x1c, 0x2, 0x2, 
    0x203, 0x204, 0x7, 0x13, 0x2, 0x2, 0x204, 0x205, 0x5, 0x3e, 0x20, 0x2, 
    0x205, 0x206, 0x7, 0x5, 0x2, 0x2, 0x206, 0x207, 0x5, 0x3e, 0x20, 0x2, 
    0x207, 0x208, 0x7, 0x5, 0x2, 0x2, 0x208, 0x20b, 0x5, 0x3e, 0x20, 0x2, 
    0x209, 0x20a, 0x7, 0x5, 0x2, 0x2, 0x20a, 0x20c, 0x5, 0x3a, 0x1e, 0x2, 
    0x20b, 0x209, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x20c, 0x3, 0x2, 0x2, 0x2, 
    0x20c, 0x20d, 0x3, 0x2, 0x2, 0x2, 0x20d, 0x20e, 0x7, 0x14, 0x2, 0x2, 
    0x20e, 0x20f, 0x7, 0x50, 0x2, 0x2, 0x20f, 0x210, 0x5, 0x2e, 0x18, 0x2, 
    0x210, 0x211, 0x7, 0x1d, 0x2, 0x2, 0x211, 0x212, 0x7, 0x13, 0x2, 0x2, 
    0x212, 0x213, 0x7, 0x14, 0x2, 0x2, 0x213, 0x21f, 0x3, 0x2, 0x2, 0x2, 
    0x214, 0x215, 0x7, 0x1e, 0x2, 0x2, 0x215, 0x216, 0x7, 0x13, 0x2, 0x2, 
    0x216, 0x217, 0x7, 0x14, 0x2, 0x2, 0x217, 0x218, 0x7, 0x50, 0x2, 0x2, 
    0x218, 0x219, 0x5, 0x2e, 0x18, 0x2, 0x219, 0x21a, 0x7, 0x1f, 0x2, 0x2, 
    0x21a, 0x21b, 0x7, 0x13, 0x2, 0x2, 0x21b, 0x21c, 0x5, 0x3e, 0x20, 0x2, 
    0x21c, 0x21d, 0x7, 0x14, 0x2, 0x2, 0x21d, 0x21f, 0x3, 0x2, 0x2, 0x2, 
    0x21e, 0x1ea, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x1f4, 0x3, 0x2, 0x2, 0x2, 
    0x21e, 0x202, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x214, 0x3, 0x2, 0x2, 0x2, 
    0x21f, 0x35, 0x3, 0x2, 0x2, 0x2, 0x220, 0x221, 0x7, 0x20, 0x2, 0x2, 
    0x221, 0x222, 0x7, 0x13, 0x2, 0x2, 0x222, 0x223, 0x5, 0x3e, 0x20, 0x2, 
    0x223, 0x224, 0x7, 0x14, 0x2, 0x2, 0x224, 0x227, 0x5, 0x2e, 0x18, 0x2, 
    0x225, 0x226, 0x7, 0x21, 0x2, 0x2, 0x226, 0x228, 0x5, 0x2e, 0x18, 0x2, 
    0x227, 0x225, 0x3, 0x2, 0x2, 0x2, 0x227, 0x228, 0x3, 0x2, 0x2, 0x2, 
    0x228, 0x229, 0x3, 0x2, 0x2, 0x2, 0x229, 0x22a, 0x7, 0x22, 0x2, 0x2, 
    0x22a, 0x233, 0x3, 0x2, 0x2, 0x2, 0x22b, 0x22c, 0x7, 0x23, 0x2, 0x2, 
    0x22c, 0x22d, 0x7, 0x13, 0x2, 0x2, 0x22d, 0x22e, 0x5, 0x3e, 0x20, 0x2, 
    0x22e, 0x22f, 0x7, 0x14, 0x2, 0x2, 0x22f, 0x230, 0x5, 0x2e, 0x18, 0x2, 
    0x230, 0x231, 0x7, 0x24, 0x2, 0x2, 0x231, 0x233, 0x3, 0x2, 0x2, 0x2, 
    0x232, 0x220, 0x3, 0x2, 0x2, 0x2, 0x232, 0x22b, 0x3, 0x2, 0x2, 0x2, 
    0x233, 0x37, 0x3, 0x2, 0x2, 0x2, 0x234, 0x235, 0x7, 0x25, 0x2, 0x2, 
    0x235, 0x236, 0x7, 0x13, 0x2, 0x2, 0x236, 0x244, 0x7, 0x14, 0x2, 0x2, 
    0x237, 0x238, 0x7, 0x26, 0x2, 0x2, 0x238, 0x239, 0x7, 0x13, 0x2, 0x2, 
    0x239, 0x244, 0x7, 0x14, 0x2, 0x2, 0x23a, 0x23b, 0x7, 0x27, 0x2, 0x2, 
    0x23b, 0x23d, 0x7, 0x13, 0x2, 0x2, 0x23c, 0x23e, 0x5, 0x3e, 0x20, 0x2, 
    0x23d, 0x23c, 0x3, 0x2, 0x2, 0x2, 0x23d, 0x23e, 0x3, 0x2, 0x2, 0x2, 
    0x23e, 0x23f, 0x3, 0x2, 0x2, 0x2, 0x23f, 0x244, 0x7, 0x14, 0x2, 0x2, 
    0x240, 0x241, 0x7, 0x28, 0x2, 0x2, 0x241, 0x242, 0x7, 0x13, 0x2, 0x2, 
    0x242, 0x244, 0x7, 0x14, 0x2, 0x2, 0x243, 0x234, 0x3, 0x2, 0x2, 0x2, 
    0x243, 0x237, 0x3, 0x2, 0x2, 0x2, 0x243, 0x23a, 0x3, 0x2, 0x2, 0x2, 
    0x243, 0x240, 0x3, 0x2, 0x2, 0x2, 0x244, 0x39, 0x3, 0x2, 0x2, 0x2, 0x245, 
    0x24a, 0x5, 0x3c, 0x1f, 0x2, 0x246, 0x247, 0x7, 0x29, 0x2, 0x2, 0x247, 
    0x249, 0x5, 0x3c, 0x1f, 0x2, 0x248, 0x246, 0x3, 0x2, 0x2, 0x2, 0x249, 
    0x24c, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x248, 0x3, 0x2, 0x2, 0x2, 0x24a, 
    0x24b, 0x3, 0x2, 0x2, 0x2, 0x24b, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x24c, 0x24a, 
    0x3, 0x2, 0x2, 0x2, 0x24d, 0x24e, 0x8, 0x1f, 0x1, 0x2, 0x24e, 0x24f, 
    0x7, 0x4e, 0x2, 0x2, 0x24f, 0x266, 0x3, 0x2, 0x2, 0x2, 0x250, 0x251, 
    0xc, 0x4, 0x2, 0x2, 0x251, 0x253, 0x7, 0x13, 0x2, 0x2, 0x252, 0x254, 
    0x5, 0x3e, 0x20, 0x2, 0x253, 0x252, 0x3, 0x2, 0x2, 0x2, 0x253, 0x254, 
    0x3, 0x2, 0x2, 0x2, 0x254, 0x25b, 0x3, 0x2, 0x2, 0x2, 0x255, 0x257, 
    0x7, 0x5, 0x2, 0x2, 0x256, 0x258, 0x5, 0x3e, 0x20, 0x2, 0x257, 0x256, 
    0x3, 0x2, 0x2, 0x2, 0x257, 0x258, 0x3, 0x2, 0x2, 0x2, 0x258, 0x25a, 
    0x3, 0x2, 0x2, 0x2, 0x259, 0x255, 0x3, 0x2, 0x2, 0x2, 0x25a, 0x25d, 
    0x3, 0x2, 0x2, 0x2, 0x25b, 0x259, 0x3, 0x2, 0x2, 0x2, 0x25b, 0x25c, 
    0x3, 0x2, 0x2, 0x2, 0x25c, 0x25e, 0x3, 0x2, 0x2, 0x2, 0x25d, 0x25b, 
    0x3, 0x2, 0x2, 0x2, 0x25e, 0x265, 0x7, 0x14, 0x2, 0x2, 0x25f, 0x260, 
    0xc, 0x3, 0x2, 0x2, 0x260, 0x261, 0x7, 0x2a, 0x2, 0x2, 0x261, 0x262, 
    0x5, 0x3e, 0x20, 0x2, 0x262, 0x263, 0x7, 0x2b, 0x2, 0x2, 0x263, 0x265, 
    0x3, 0x2, 0x2, 0x2, 0x264, 0x250, 0x3, 0x2, 0x2, 0x2, 0x264, 0x25f, 
    0x3, 0x2, 0x2, 0x2, 0x265, 0x268, 0x3, 0x2, 0x2, 0x2, 0x266, 0x264, 
    0x3, 0x2, 0x2, 0x2, 0x266, 0x267, 0x3, 0x2, 0x2, 0x2, 0x267, 0x3d, 0x3, 
    0x2, 0x2, 0x2, 0x268, 0x266, 0x3, 0x2, 0x2, 0x2, 0x269, 0x26a, 0x8, 
    0x20, 0x1, 0x2, 0x26a, 0x26b, 0x7, 0x13, 0x2, 0x2, 0x26b, 0x26c, 0x5, 
    0x3e, 0x20, 0x2, 0x26c, 0x26d, 0x7, 0x14, 0x2, 0x2, 0x26d, 0x279, 0x3, 
    0x2, 0x2, 0x2, 0x26e, 0x26f, 0x7, 0x3c, 0x2, 0x2, 0x26f, 0x279, 0x5, 
    0x3e, 0x20, 0x1b, 0x270, 0x279, 0x5, 0x4c, 0x27, 0x2, 0x271, 0x279, 
    0x5, 0x4a, 0x26, 0x2, 0x272, 0x279, 0x5, 0x46, 0x24, 0x2, 0x273, 0x279, 
    0x5, 0x4e, 0x28, 0x2, 0x274, 0x279, 0x5, 0x3a, 0x1e, 0x2, 0x275, 0x279, 
    0x5, 0x48, 0x25, 0x2, 0x276, 0x279, 0x5, 0x42, 0x22, 0x2, 0x277, 0x279, 
    0x5, 0x40, 0x21, 0x2, 0x278, 0x269, 0x3, 0x2, 0x2, 0x2, 0x278, 0x26e, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x270, 0x3, 0x2, 0x2, 0x2, 0x278, 0x271, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x272, 0x3, 0x2, 0x2, 0x2, 0x278, 0x273, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x274, 0x3, 0x2, 0x2, 0x2, 0x278, 0x275, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x276, 0x3, 0x2, 0x2, 0x2, 0x278, 0x277, 
    0x3, 0x2, 0x2, 0x2, 0x279, 0x2ac, 0x3, 0x2, 0x2, 0x2, 0x27a, 0x27b, 
    0xc, 0x1a, 0x2, 0x2, 0x27b, 0x27c, 0x7, 0x3d, 0x2, 0x2, 0x27c, 0x2ab, 
    0x5, 0x3e, 0x20, 0x1b, 0x27d, 0x27e, 0xc, 0x19, 0x2, 0x2, 0x27e, 0x27f, 
    0x7, 0x3e, 0x2, 0x2, 0x27f, 0x2ab, 0x5, 0x3e, 0x20, 0x1a, 0x280, 0x281, 
    0xc, 0x18, 0x2, 0x2, 0x281, 0x282, 0x7, 0x3f, 0x2, 0x2, 0x282, 0x2ab, 
    0x5, 0x3e, 0x20, 0x19, 0x283, 0x284, 0xc, 0x17, 0x2, 0x2, 0x284, 0x285, 
    0x7, 0x40, 0x2, 0x2, 0x285, 0x2ab, 0x5, 0x3e, 0x20, 0x18, 0x286, 0x287, 
    0xc, 0x16, 0x2, 0x2, 0x287, 0x288, 0x7, 0x3b, 0x2, 0x2, 0x288, 0x2ab, 
    0x5, 0x3e, 0x20, 0x17, 0x289, 0x28a, 0xc, 0x15, 0x2, 0x2, 0x28a, 0x28b, 
    0x7, 0x3c, 0x2, 0x2, 0x28b, 0x2ab, 0x5, 0x3e, 0x20, 0x16, 0x28c, 0x28d, 
    0xc, 0x14, 0x2, 0x2, 0x28d, 0x28e, 0x7, 0x44, 0x2, 0x2, 0x28e, 0x2ab, 
    0x5, 0x3e, 0x20, 0x15, 0x28f, 0x290, 0xc, 0x13, 0x2, 0x2, 0x290, 0x291, 
    0x7, 0x43, 0x2, 0x2, 0x291, 0x2ab, 0x5, 0x3e, 0x20, 0x14, 0x292, 0x293, 
    0xc, 0x12, 0x2, 0x2, 0x293, 0x294, 0x7, 0x41, 0x2, 0x2, 0x294, 0x2ab, 
    0x5, 0x3e, 0x20, 0x13, 0x295, 0x296, 0xc, 0x11, 0x2, 0x2, 0x296, 0x297, 
    0x7, 0x46, 0x2, 0x2, 0x297, 0x2ab, 0x5, 0x3e, 0x20, 0x12, 0x298, 0x299, 
    0xc, 0x10, 0x2, 0x2, 0x299, 0x29a, 0x7, 0x45, 0x2, 0x2, 0x29a, 0x2ab, 
    0x5, 0x3e, 0x20, 0x11, 0x29b, 0x29c, 0xc, 0xf, 0x2, 0x2, 0x29c, 0x29d, 
    0x7, 0x48, 0x2, 0x2, 0x29d, 0x2ab, 0x5, 0x3e, 0x20, 0x10, 0x29e, 0x29f, 
    0xc, 0xe, 0x2, 0x2, 0x29f, 0x2a0, 0x7, 0x47, 0x2, 0x2, 0x2a0, 0x2ab, 
    0x5, 0x3e, 0x20, 0xf, 0x2a1, 0x2a2, 0xc, 0xd, 0x2, 0x2, 0x2a2, 0x2a3, 
    0x7, 0x49, 0x2, 0x2, 0x2a3, 0x2ab, 0x5, 0x3e, 0x20, 0xe, 0x2a4, 0x2a5, 
    0xc, 0xc, 0x2, 0x2, 0x2a5, 0x2a6, 0x7, 0x4b, 0x2, 0x2, 0x2a6, 0x2ab, 
    0x5, 0x3e, 0x20, 0xd, 0x2a7, 0x2a8, 0xc, 0xb, 0x2, 0x2, 0x2a8, 0x2a9, 
    0x7, 0x4a, 0x2, 0x2, 0x2a9, 0x2ab, 0x5, 0x3e, 0x20, 0xc, 0x2aa, 0x27a, 
    0x3, 0x2, 0x2, 0x2, 0x2aa, 0x27d, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x280, 
    0x3, 0x2, 0x2, 0x2, 0x2aa, 0x283, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x286, 
    0x3, 0x2, 0x2, 0x2, 0x2aa, 0x289, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x28c, 
    0x3, 0x2, 0x2, 0x2, 0x2aa, 0x28f, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x292, 
    0x3, 0x2, 0x2, 0x2, 0x2aa, 0x295, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x298, 
    0x3, 0x2, 0x2, 0x2, 0x2aa, 0x29b, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x29e, 
    0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2a1, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2a4, 
    0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2a7, 0x3, 0x2, 0x2, 0x2, 0x2ab, 0x2ae, 
    0x3, 0x2, 0x2, 0x2, 0x2ac, 0x2aa, 0x3, 0x2, 0x2, 0x2, 0x2ac, 0x2ad, 
    0x3, 0x2, 0x2, 0x2, 0x2ad, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x2ae, 0x2ac, 0x3, 
    0x2, 0x2, 0x2, 0x2af, 0x2b8, 0x7, 0x2c, 0x2, 0x2, 0x2b0, 0x2b5, 0x5, 
    0x3e, 0x20, 0x2, 0x2b1, 0x2b2, 0x7, 0x5, 0x2, 0x2, 0x2b2, 0x2b4, 0x5, 
    0x3e, 0x20, 0x2, 0x2b3, 0x2b1, 0x3, 0x2, 0x2, 0x2, 0x2b4, 0x2b7, 0x3, 
    0x2, 0x2, 0x2, 0x2b5, 0x2b3, 0x3, 0x2, 0x2, 0x2, 0x2b5, 0x2b6, 0x3, 
    0x2, 0x2, 0x2, 0x2b6, 0x2b9, 0x3, 0x2, 0x2, 0x2, 0x2b7, 0x2b5, 0x3, 
    0x2, 0x2, 0x2, 0x2b8, 0x2b0, 0x3, 0x2, 0x2, 0x2, 0x2b8, 0x2b9, 0x3, 
    0x2, 0x2, 0x2, 0x2b9, 0x2ba, 0x3, 0x2, 0x2, 0x2, 0x2ba, 0x2bb, 0x7, 
    0x2d, 0x2, 0x2, 0x2bb, 0x41, 0x3, 0x2, 0x2, 0x2, 0x2bc, 0x2bd, 0x7, 
    0x2a, 0x2, 0x2, 0x2bd, 0x2be, 0x5, 0x44, 0x23, 0x2, 0x2be, 0x2bf, 0x7, 
    0x2b, 0x2, 0x2, 0x2bf, 0x43, 0x3, 0x2, 0x2, 0x2, 0x2c0, 0x304, 0x7, 
    0x4c, 0x2, 0x2, 0x2c1, 0x2c2, 0x7, 0x4c, 0x2, 0x2, 0x2c2, 0x2c3, 0x7, 
    0x2e, 0x2, 0x2, 0x2c3, 0x2c4, 0x7, 0x4c, 0x2, 0x2, 0x2c4, 0x2c5, 0x7, 
    0x2f, 0x2, 0x2, 0x2c5, 0x2c6, 0x7, 0x4c, 0x2, 0x2, 0x2c6, 0x2cd, 0x7, 
    0x30, 0x2, 0x2, 0x2c7, 0x2c8, 0x7, 0x4c, 0x2, 0x2, 0x2c8, 0x2c9, 0x7, 
    0x31, 0x2, 0x2, 0x2c9, 0x2ca, 0x7, 0x4c, 0x2, 0x2, 0x2ca, 0x2cb, 0x7, 
    0x32, 0x2, 0x2, 0x2cb, 0x2cc, 0x7, 0x4c, 0x2, 0x2, 0x2cc, 0x2ce, 0x7, 
    0x33, 0x2, 0x2, 0x2cd, 0x2c7, 0x3, 0x2, 0x2, 0x2, 0x2cd, 0x2ce, 0x3, 
    0x2, 0x2, 0x2, 0x2ce, 0x304, 0x3, 0x2, 0x2, 0x2, 0x2cf, 0x2d0, 0x7, 
    0x4c, 0x2, 0x2, 0x2d0, 0x2d1, 0x7, 0x34, 0x2, 0x2, 0x2d1, 0x2d2, 0x7, 
    0x4c, 0x2, 0x2, 0x2d2, 0x2d3, 0x7, 0x34, 0x2, 0x2, 0x2d3, 0x2da, 0x7, 
    0x4c, 0x2, 0x2, 0x2d4, 0x2d5, 0x7, 0x34, 0x2, 0x2, 0x2d5, 0x2d6, 0x7, 
    0x4c, 0x2, 0x2, 0x2d6, 0x2d7, 0x7, 0x34, 0x2, 0x2, 0x2d7, 0x2d8, 0x7, 
    0x4c, 0x2, 0x2, 0x2d8, 0x2d9, 0x7, 0x34, 0x2, 0x2, 0x2d9, 0x2db, 0x7, 
    0x4c, 0x2, 0x2, 0x2da, 0x2d4, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2db, 0x3, 
    0x2, 0x2, 0x2, 0x2db, 0x304, 0x3, 0x2, 0x2, 0x2, 0x2dc, 0x2dd, 0x7, 
    0x4c, 0x2, 0x2, 0x2dd, 0x2de, 0x7, 0x34, 0x2, 0x2, 0x2de, 0x2df, 0x7, 
    0x4c, 0x2, 0x2, 0x2df, 0x2e0, 0x7, 0x34, 0x2, 0x2, 0x2e0, 0x2e7, 0x7, 
    0x4c, 0x2, 0x2, 0x2e1, 0x2e2, 0x7, 0x34, 0x2, 0x2, 0x2e2, 0x2e3, 0x7, 
    0x4c, 0x2, 0x2, 0x2e3, 0x2e4, 0x7, 0x35, 0x2, 0x2, 0x2e4, 0x2e5, 0x7, 
    0x4c, 0x2, 0x2, 0x2e5, 0x2e6, 0x7, 0x35, 0x2, 0x2, 0x2e6, 0x2e8, 0x7, 
    0x4c, 0x2, 0x2, 0x2e7, 0x2e1, 0x3, 0x2, 0x2, 0x2, 0x2e7, 0x2e8, 0x3, 
    0x2, 0x2, 0x2, 0x2e8, 0x304, 0x3, 0x2, 0x2, 0x2, 0x2e9, 0x2ea, 0x7, 
    0x4c, 0x2, 0x2, 0x2ea, 0x2eb, 0x7, 0x36, 0x2, 0x2, 0x2eb, 0x2ec, 0x7, 
    0x4c, 0x2, 0x2, 0x2ec, 0x2ed, 0x7, 0x36, 0x2, 0x2, 0x2ed, 0x2f4, 0x7, 
    0x4c, 0x2, 0x2, 0x2ee, 0x2ef, 0x7, 0x36, 0x2, 0x2, 0x2ef, 0x2f0, 0x7, 
    0x4c, 0x2, 0x2, 0x2f0, 0x2f1, 0x7, 0x36, 0x2, 0x2, 0x2f1, 0x2f2, 0x7, 
    0x4c, 0x2, 0x2, 0x2f2, 0x2f3, 0x7, 0x36, 0x2, 0x2, 0x2f3, 0x2f5, 0x7, 
    0x4c, 0x2, 0x2, 0x2f4, 0x2ee, 0x3, 0x2, 0x2, 0x2, 0x2f4, 0x2f5, 0x3, 
    0x2, 0x2, 0x2, 0x2f5, 0x304, 0x3, 0x2, 0x2, 0x2, 0x2f6, 0x2f7, 0x7, 
    0x4c, 0x2, 0x2, 0x2f7, 0x2f8, 0x7, 0x36, 0x2, 0x2, 0x2f8, 0x2f9, 0x7, 
    0x4c, 0x2, 0x2, 0x2f9, 0x2fa, 0x7, 0x36, 0x2, 0x2, 0x2fa, 0x301, 0x7, 
    0x4c, 0x2, 0x2, 0x2fb, 0x2fc, 0x7, 0x36, 0x2, 0x2, 0x2fc, 0x2fd, 0x7, 
    0x4c, 0x2, 0x2, 0x2fd, 0x2fe, 0x7, 0x35, 0x2, 0x2, 0x2fe, 0x2ff, 0x7, 
    0x4c, 0x2, 0x2, 0x2ff, 0x300, 0x7, 0x35, 0x2, 0x2, 0x300, 0x302, 0x7, 
    0x4c, 0x2, 0x2, 0x301, 0x2fb, 0x3, 0x2, 0x2, 0x2, 0x301, 0x302, 0x3, 
    0x2, 0x2, 0x2, 0x302, 0x304, 0x3, 0x2, 0x2, 0x2, 0x303, 0x2c0, 0x3, 
    0x2, 0x2, 0x2, 0x303, 0x2c1, 0x3, 0x2, 0x2, 0x2, 0x303, 0x2cf, 0x3, 
    0x2, 0x2, 0x2, 0x303, 0x2dc, 0x3, 0x2, 0x2, 0x2, 0x303, 0x2e9, 0x3, 
    0x2, 0x2, 0x2, 0x303, 0x2f6, 0x3, 0x2, 0x2, 0x2, 0x304, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0x305, 0x306, 0x7, 0x37, 0x2, 0x2, 0x306, 0x307, 0x7, 0x4e, 
    0x2, 0x2, 0x307, 0x47, 0x3, 0x2, 0x2, 0x2, 0x308, 0x309, 0x7, 0x38, 
    0x2, 0x2, 0x309, 0x30a, 0x7, 0x4e, 0x2, 0x2, 0x30a, 0x49, 0x3, 0x2, 
    0x2, 0x2, 0x30b, 0x30e, 0x7, 0x39, 0x2, 0x2, 0x30c, 0x30e, 0x7, 0x3a, 
    0x2, 0x2, 0x30d, 0x30b, 0x3, 0x2, 0x2, 0x2, 0x30d, 0x30c, 0x3, 0x2, 
    0x2, 0x2, 0x30e, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x30f, 0x312, 0x7, 0x4c, 
    0x2, 0x2, 0x310, 0x312, 0x7, 0x4d, 0x2, 0x2, 0x311, 0x30f, 0x3, 0x2, 
    0x2, 0x2, 0x311, 0x310, 0x3, 0x2, 0x2, 0x2, 0x312, 0x4d, 0x3, 0x2, 0x2, 
    0x2, 0x313, 0x314, 0x7, 0x51, 0x2, 0x2, 0x314, 0x4f, 0x3, 0x2, 0x2, 
    0x2, 0x66, 0x54, 0x5b, 0x64, 0x6b, 0x71, 0x79, 0x81, 0x87, 0x8a, 0x90, 
    0x94, 0x9c, 0xa1, 0xa8, 0xaf, 0xb3, 0xbb, 0xc0, 0xc7, 0xcd, 0xd4, 0xd8, 
    0xdc, 0xe0, 0xe2, 0xe4, 0xe6, 0xf2, 0xf6, 0xf8, 0xff, 0x105, 0x10b, 
    0x112, 0x116, 0x11a, 0x11c, 0x11e, 0x125, 0x12b, 0x132, 0x137, 0x13d, 
    0x143, 0x148, 0x14c, 0x14e, 0x150, 0x15c, 0x160, 0x164, 0x166, 0x168, 
    0x16f, 0x174, 0x17a, 0x17e, 0x182, 0x186, 0x188, 0x18a, 0x18c, 0x193, 
    0x197, 0x1a1, 0x1a6, 0x1a8, 0x1b4, 0x1b9, 0x1bb, 0x1c0, 0x1c5, 0x1d1, 
    0x1e2, 0x1f9, 0x20b, 0x21e, 0x227, 0x232, 0x23d, 0x243, 0x24a, 0x253, 
    0x257, 0x25b, 0x264, 0x266, 0x278, 0x2aa, 0x2ac, 0x2b5, 0x2b8, 0x2cd, 
    0x2da, 0x2e7, 0x2f4, 0x301, 0x303, 0x30d, 0x311, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

rexLangParser::Initializer rexLangParser::_init;
