
// Generated from openeParser.g4 by ANTLR 4.7.1


#include "openeParserListener.h"
#include "openeParserVisitor.h"

#include "openeParser.h"


using namespace antlrcpp;
using namespace opene;
using namespace antlr4;

openeParser::openeParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

openeParser::~openeParser() {
  delete _interpreter;
}

std::string openeParser::getGrammarFileName() const {
  return "openeParser.g4";
}

const std::vector<std::string>& openeParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& openeParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- Opene_srcContext ------------------------------------------------------------------

openeParser::Opene_srcContext::Opene_srcContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeParser::Edition_specContext* openeParser::Opene_srcContext::edition_spec() {
  return getRuleContext<openeParser::Edition_specContext>(0);
}

tree::TerminalNode* openeParser::Opene_srcContext::NEWLINE() {
  return getToken(openeParser::NEWLINE, 0);
}

openeParser::Src_contentContext* openeParser::Opene_srcContext::src_content() {
  return getRuleContext<openeParser::Src_contentContext>(0);
}

tree::TerminalNode* openeParser::Opene_srcContext::EOF() {
  return getToken(openeParser::EOF, 0);
}


size_t openeParser::Opene_srcContext::getRuleIndex() const {
  return openeParser::RuleOpene_src;
}

void openeParser::Opene_srcContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOpene_src(this);
}

void openeParser::Opene_srcContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOpene_src(this);
}


antlrcpp::Any openeParser::Opene_srcContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitOpene_src(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Opene_srcContext* openeParser::opene_src() {
  Opene_srcContext *_localctx = _tracker.createInstance<Opene_srcContext>(_ctx, getState());
  enterRule(_localctx, 0, openeParser::RuleOpene_src);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    edition_spec();
    setState(87);
    match(openeParser::NEWLINE);
    setState(88);
    src_content();
    setState(89);
    match(openeParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Src_contentContext ------------------------------------------------------------------

openeParser::Src_contentContext::Src_contentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeParser::Program_set_fileContext* openeParser::Src_contentContext::program_set_file() {
  return getRuleContext<openeParser::Program_set_fileContext>(0);
}

openeParser::Data_structure_fileContext* openeParser::Src_contentContext::data_structure_file() {
  return getRuleContext<openeParser::Data_structure_fileContext>(0);
}

openeParser::Global_variable_fileContext* openeParser::Src_contentContext::global_variable_file() {
  return getRuleContext<openeParser::Global_variable_fileContext>(0);
}

openeParser::Dll_define_fileContext* openeParser::Src_contentContext::dll_define_file() {
  return getRuleContext<openeParser::Dll_define_fileContext>(0);
}


size_t openeParser::Src_contentContext::getRuleIndex() const {
  return openeParser::RuleSrc_content;
}

void openeParser::Src_contentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSrc_content(this);
}

void openeParser::Src_contentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSrc_content(this);
}


antlrcpp::Any openeParser::Src_contentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitSrc_content(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Src_contentContext* openeParser::src_content() {
  Src_contentContext *_localctx = _tracker.createInstance<Src_contentContext>(_ctx, getState());
  enterRule(_localctx, 2, openeParser::RuleSrc_content);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(95);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(91);
      program_set_file();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(92);
      data_structure_file();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(93);
      global_variable_file();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(94);
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

openeParser::Program_set_fileContext::Program_set_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeParser::Library_list_optContext* openeParser::Program_set_fileContext::library_list_opt() {
  return getRuleContext<openeParser::Library_list_optContext>(0);
}

openeParser::Prog_setContext* openeParser::Program_set_fileContext::prog_set() {
  return getRuleContext<openeParser::Prog_setContext>(0);
}


size_t openeParser::Program_set_fileContext::getRuleIndex() const {
  return openeParser::RuleProgram_set_file;
}

void openeParser::Program_set_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram_set_file(this);
}

void openeParser::Program_set_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram_set_file(this);
}


antlrcpp::Any openeParser::Program_set_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitProgram_set_file(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Program_set_fileContext* openeParser::program_set_file() {
  Program_set_fileContext *_localctx = _tracker.createInstance<Program_set_fileContext>(_ctx, getState());
  enterRule(_localctx, 4, openeParser::RuleProgram_set_file);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
    library_list_opt();
    setState(98);
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

openeParser::Data_structure_fileContext::Data_structure_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeParser::Struct_declareContext *> openeParser::Data_structure_fileContext::struct_declare() {
  return getRuleContexts<openeParser::Struct_declareContext>();
}

openeParser::Struct_declareContext* openeParser::Data_structure_fileContext::struct_declare(size_t i) {
  return getRuleContext<openeParser::Struct_declareContext>(i);
}


size_t openeParser::Data_structure_fileContext::getRuleIndex() const {
  return openeParser::RuleData_structure_file;
}

void openeParser::Data_structure_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterData_structure_file(this);
}

void openeParser::Data_structure_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitData_structure_file(this);
}


antlrcpp::Any openeParser::Data_structure_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitData_structure_file(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Data_structure_fileContext* openeParser::data_structure_file() {
  Data_structure_fileContext *_localctx = _tracker.createInstance<Data_structure_fileContext>(_ctx, getState());
  enterRule(_localctx, 6, openeParser::RuleData_structure_file);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::K_STRUCTURE) {
      setState(100);
      struct_declare();
      setState(105);
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

openeParser::Global_variable_fileContext::Global_variable_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

openeParser::Global_variable_listContext* openeParser::Global_variable_fileContext::global_variable_list() {
  return getRuleContext<openeParser::Global_variable_listContext>(0);
}


size_t openeParser::Global_variable_fileContext::getRuleIndex() const {
  return openeParser::RuleGlobal_variable_file;
}

void openeParser::Global_variable_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_variable_file(this);
}

void openeParser::Global_variable_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_variable_file(this);
}


antlrcpp::Any openeParser::Global_variable_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitGlobal_variable_file(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Global_variable_fileContext* openeParser::global_variable_file() {
  Global_variable_fileContext *_localctx = _tracker.createInstance<Global_variable_fileContext>(_ctx, getState());
  enterRule(_localctx, 8, openeParser::RuleGlobal_variable_file);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
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

openeParser::Dll_define_fileContext::Dll_define_fileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeParser::Dll_commandContext *> openeParser::Dll_define_fileContext::dll_command() {
  return getRuleContexts<openeParser::Dll_commandContext>();
}

openeParser::Dll_commandContext* openeParser::Dll_define_fileContext::dll_command(size_t i) {
  return getRuleContext<openeParser::Dll_commandContext>(i);
}


size_t openeParser::Dll_define_fileContext::getRuleIndex() const {
  return openeParser::RuleDll_define_file;
}

void openeParser::Dll_define_fileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDll_define_file(this);
}

void openeParser::Dll_define_fileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDll_define_file(this);
}


antlrcpp::Any openeParser::Dll_define_fileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitDll_define_file(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Dll_define_fileContext* openeParser::dll_define_file() {
  Dll_define_fileContext *_localctx = _tracker.createInstance<Dll_define_fileContext>(_ctx, getState());
  enterRule(_localctx, 10, openeParser::RuleDll_define_file);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::K_DLL_DEFINE) {
      setState(108);
      dll_command();
      setState(113);
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

openeParser::Dll_commandContext::Dll_commandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Dll_commandContext::K_DLL_DEFINE() {
  return getToken(openeParser::K_DLL_DEFINE, 0);
}

std::vector<tree::TerminalNode *> openeParser::Dll_commandContext::TABLE_COMMA() {
  return getTokens(openeParser::TABLE_COMMA);
}

tree::TerminalNode* openeParser::Dll_commandContext::TABLE_COMMA(size_t i) {
  return getToken(openeParser::TABLE_COMMA, i);
}

tree::TerminalNode* openeParser::Dll_commandContext::TABLE_END() {
  return getToken(openeParser::TABLE_END, 0);
}

std::vector<tree::TerminalNode *> openeParser::Dll_commandContext::TABLE_ITEM() {
  return getTokens(openeParser::TABLE_ITEM);
}

tree::TerminalNode* openeParser::Dll_commandContext::TABLE_ITEM(size_t i) {
  return getToken(openeParser::TABLE_ITEM, i);
}

openeParser::Table_commentContext* openeParser::Dll_commandContext::table_comment() {
  return getRuleContext<openeParser::Table_commentContext>(0);
}

std::vector<openeParser::Parameter_declContext *> openeParser::Dll_commandContext::parameter_decl() {
  return getRuleContexts<openeParser::Parameter_declContext>();
}

openeParser::Parameter_declContext* openeParser::Dll_commandContext::parameter_decl(size_t i) {
  return getRuleContext<openeParser::Parameter_declContext>(i);
}

std::vector<tree::TerminalNode *> openeParser::Dll_commandContext::NEWLINE() {
  return getTokens(openeParser::NEWLINE);
}

tree::TerminalNode* openeParser::Dll_commandContext::NEWLINE(size_t i) {
  return getToken(openeParser::NEWLINE, i);
}


size_t openeParser::Dll_commandContext::getRuleIndex() const {
  return openeParser::RuleDll_command;
}

void openeParser::Dll_commandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDll_command(this);
}

void openeParser::Dll_commandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDll_command(this);
}


antlrcpp::Any openeParser::Dll_commandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitDll_command(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Dll_commandContext* openeParser::dll_command() {
  Dll_commandContext *_localctx = _tracker.createInstance<Dll_commandContext>(_ctx, getState());
  enterRule(_localctx, 12, openeParser::RuleDll_command);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    match(openeParser::K_DLL_DEFINE);
    setState(115);
    dynamic_cast<Dll_commandContext *>(_localctx)->name = match(openeParser::TABLE_ITEM);
    setState(116);
    match(openeParser::TABLE_COMMA);
    setState(118);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeParser::TABLE_ITEM) {
      setState(117);
      dynamic_cast<Dll_commandContext *>(_localctx)->type = match(openeParser::TABLE_ITEM);
    }
    setState(120);
    match(openeParser::TABLE_COMMA);
    setState(122);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeParser::TABLE_ITEM) {
      setState(121);
      dynamic_cast<Dll_commandContext *>(_localctx)->file = match(openeParser::TABLE_ITEM);
    }
    setState(124);
    match(openeParser::TABLE_COMMA);
    setState(125);
    dynamic_cast<Dll_commandContext *>(_localctx)->cmd = match(openeParser::TABLE_ITEM);
    setState(128);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeParser::TABLE_COMMA) {
      setState(126);
      match(openeParser::TABLE_COMMA);
      setState(127);
      table_comment();
    }
    setState(130);
    match(openeParser::TABLE_END);
    setState(134);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::K_PARAMETER) {
      setState(131);
      parameter_decl();
      setState(136);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(140);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::NEWLINE) {
      setState(137);
      match(openeParser::NEWLINE);
      setState(142);
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

openeParser::Global_variable_listContext::Global_variable_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeParser::Global_variable_itemContext *> openeParser::Global_variable_listContext::global_variable_item() {
  return getRuleContexts<openeParser::Global_variable_itemContext>();
}

openeParser::Global_variable_itemContext* openeParser::Global_variable_listContext::global_variable_item(size_t i) {
  return getRuleContext<openeParser::Global_variable_itemContext>(i);
}


size_t openeParser::Global_variable_listContext::getRuleIndex() const {
  return openeParser::RuleGlobal_variable_list;
}

void openeParser::Global_variable_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_variable_list(this);
}

void openeParser::Global_variable_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_variable_list(this);
}


antlrcpp::Any openeParser::Global_variable_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitGlobal_variable_list(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Global_variable_listContext* openeParser::global_variable_list() {
  Global_variable_listContext *_localctx = _tracker.createInstance<Global_variable_listContext>(_ctx, getState());
  enterRule(_localctx, 14, openeParser::RuleGlobal_variable_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::K_GLOBAL_VARIABLE) {
      setState(143);
      global_variable_item();
      setState(148);
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

openeParser::Global_variable_itemContext::Global_variable_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Global_variable_itemContext::K_GLOBAL_VARIABLE() {
  return getToken(openeParser::K_GLOBAL_VARIABLE, 0);
}

tree::TerminalNode* openeParser::Global_variable_itemContext::TABLE_END() {
  return getToken(openeParser::TABLE_END, 0);
}

std::vector<tree::TerminalNode *> openeParser::Global_variable_itemContext::TABLE_ITEM() {
  return getTokens(openeParser::TABLE_ITEM);
}

tree::TerminalNode* openeParser::Global_variable_itemContext::TABLE_ITEM(size_t i) {
  return getToken(openeParser::TABLE_ITEM, i);
}

std::vector<tree::TerminalNode *> openeParser::Global_variable_itemContext::TABLE_COMMA() {
  return getTokens(openeParser::TABLE_COMMA);
}

tree::TerminalNode* openeParser::Global_variable_itemContext::TABLE_COMMA(size_t i) {
  return getToken(openeParser::TABLE_COMMA, i);
}

openeParser::Table_commentContext* openeParser::Global_variable_itemContext::table_comment() {
  return getRuleContext<openeParser::Table_commentContext>(0);
}


size_t openeParser::Global_variable_itemContext::getRuleIndex() const {
  return openeParser::RuleGlobal_variable_item;
}

void openeParser::Global_variable_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_variable_item(this);
}

void openeParser::Global_variable_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_variable_item(this);
}


antlrcpp::Any openeParser::Global_variable_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitGlobal_variable_item(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Global_variable_itemContext* openeParser::global_variable_item() {
  Global_variable_itemContext *_localctx = _tracker.createInstance<Global_variable_itemContext>(_ctx, getState());
  enterRule(_localctx, 16, openeParser::RuleGlobal_variable_item);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
    match(openeParser::K_GLOBAL_VARIABLE);
    setState(150);
    dynamic_cast<Global_variable_itemContext *>(_localctx)->name = match(openeParser::TABLE_ITEM);
    setState(171);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeParser::TABLE_COMMA) {
      setState(151);
      match(openeParser::TABLE_COMMA);
      setState(153);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_ITEM) {
        setState(152);
        dynamic_cast<Global_variable_itemContext *>(_localctx)->type = match(openeParser::TABLE_ITEM);
      }
      setState(169);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_COMMA) {
        setState(155);
        match(openeParser::TABLE_COMMA);
        setState(157);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeParser::TABLE_ITEM) {
          setState(156);
          dynamic_cast<Global_variable_itemContext *>(_localctx)->access = match(openeParser::TABLE_ITEM);
        }
        setState(167);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeParser::TABLE_COMMA) {
          setState(159);
          match(openeParser::TABLE_COMMA);
          setState(161);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == openeParser::TABLE_ITEM) {
            setState(160);
            dynamic_cast<Global_variable_itemContext *>(_localctx)->dimension = match(openeParser::TABLE_ITEM);
          }
          setState(165);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == openeParser::TABLE_COMMA) {
            setState(163);
            match(openeParser::TABLE_COMMA);
            setState(164);
            table_comment();
          }
        }
      }
    }
    setState(173);
    match(openeParser::TABLE_END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Edition_specContext ------------------------------------------------------------------

openeParser::Edition_specContext::Edition_specContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Edition_specContext::K_VERSION() {
  return getToken(openeParser::K_VERSION, 0);
}

tree::TerminalNode* openeParser::Edition_specContext::INTEGER_LITERAL() {
  return getToken(openeParser::INTEGER_LITERAL, 0);
}


size_t openeParser::Edition_specContext::getRuleIndex() const {
  return openeParser::RuleEdition_spec;
}

void openeParser::Edition_specContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdition_spec(this);
}

void openeParser::Edition_specContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdition_spec(this);
}


antlrcpp::Any openeParser::Edition_specContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitEdition_spec(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Edition_specContext* openeParser::edition_spec() {
  Edition_specContext *_localctx = _tracker.createInstance<Edition_specContext>(_ctx, getState());
  enterRule(_localctx, 18, openeParser::RuleEdition_spec);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    match(openeParser::K_VERSION);
    setState(176);
    match(openeParser::INTEGER_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_declareContext ------------------------------------------------------------------

openeParser::Struct_declareContext::Struct_declareContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Struct_declareContext::K_STRUCTURE() {
  return getToken(openeParser::K_STRUCTURE, 0);
}

tree::TerminalNode* openeParser::Struct_declareContext::TABLE_END() {
  return getToken(openeParser::TABLE_END, 0);
}

openeParser::Member_listContext* openeParser::Struct_declareContext::member_list() {
  return getRuleContext<openeParser::Member_listContext>(0);
}

std::vector<tree::TerminalNode *> openeParser::Struct_declareContext::TABLE_ITEM() {
  return getTokens(openeParser::TABLE_ITEM);
}

tree::TerminalNode* openeParser::Struct_declareContext::TABLE_ITEM(size_t i) {
  return getToken(openeParser::TABLE_ITEM, i);
}

std::vector<tree::TerminalNode *> openeParser::Struct_declareContext::TABLE_COMMA() {
  return getTokens(openeParser::TABLE_COMMA);
}

tree::TerminalNode* openeParser::Struct_declareContext::TABLE_COMMA(size_t i) {
  return getToken(openeParser::TABLE_COMMA, i);
}

std::vector<tree::TerminalNode *> openeParser::Struct_declareContext::NEWLINE() {
  return getTokens(openeParser::NEWLINE);
}

tree::TerminalNode* openeParser::Struct_declareContext::NEWLINE(size_t i) {
  return getToken(openeParser::NEWLINE, i);
}

openeParser::Table_commentContext* openeParser::Struct_declareContext::table_comment() {
  return getRuleContext<openeParser::Table_commentContext>(0);
}


size_t openeParser::Struct_declareContext::getRuleIndex() const {
  return openeParser::RuleStruct_declare;
}

void openeParser::Struct_declareContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_declare(this);
}

void openeParser::Struct_declareContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_declare(this);
}


antlrcpp::Any openeParser::Struct_declareContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitStruct_declare(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Struct_declareContext* openeParser::struct_declare() {
  Struct_declareContext *_localctx = _tracker.createInstance<Struct_declareContext>(_ctx, getState());
  enterRule(_localctx, 20, openeParser::RuleStruct_declare);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(178);
    match(openeParser::K_STRUCTURE);
    setState(179);
    dynamic_cast<Struct_declareContext *>(_localctx)->name = match(openeParser::TABLE_ITEM);
    setState(188);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeParser::TABLE_COMMA) {
      setState(180);
      match(openeParser::TABLE_COMMA);
      setState(182);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_ITEM) {
        setState(181);
        dynamic_cast<Struct_declareContext *>(_localctx)->access = match(openeParser::TABLE_ITEM);
      }
      setState(186);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_COMMA) {
        setState(184);
        match(openeParser::TABLE_COMMA);
        setState(185);
        table_comment();
      }
    }
    setState(190);
    match(openeParser::TABLE_END);
    setState(191);
    member_list();
    setState(195);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::NEWLINE) {
      setState(192);
      match(openeParser::NEWLINE);
      setState(197);
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

openeParser::Table_commentContext::Table_commentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> openeParser::Table_commentContext::TABLE_COMMA() {
  return getTokens(openeParser::TABLE_COMMA);
}

tree::TerminalNode* openeParser::Table_commentContext::TABLE_COMMA(size_t i) {
  return getToken(openeParser::TABLE_COMMA, i);
}

std::vector<tree::TerminalNode *> openeParser::Table_commentContext::TABLE_ITEM() {
  return getTokens(openeParser::TABLE_ITEM);
}

tree::TerminalNode* openeParser::Table_commentContext::TABLE_ITEM(size_t i) {
  return getToken(openeParser::TABLE_ITEM, i);
}


size_t openeParser::Table_commentContext::getRuleIndex() const {
  return openeParser::RuleTable_comment;
}

void openeParser::Table_commentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTable_comment(this);
}

void openeParser::Table_commentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTable_comment(this);
}


antlrcpp::Any openeParser::Table_commentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitTable_comment(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Table_commentContext* openeParser::table_comment() {
  Table_commentContext *_localctx = _tracker.createInstance<Table_commentContext>(_ctx, getState());
  enterRule(_localctx, 22, openeParser::RuleTable_comment);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::TABLE_ITEM

    || _la == openeParser::TABLE_COMMA) {
      setState(198);
      _la = _input->LA(1);
      if (!(_la == openeParser::TABLE_ITEM

      || _la == openeParser::TABLE_COMMA)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(203);
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

//----------------- Member_listContext ------------------------------------------------------------------

openeParser::Member_listContext::Member_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeParser::Member_itemContext *> openeParser::Member_listContext::member_item() {
  return getRuleContexts<openeParser::Member_itemContext>();
}

openeParser::Member_itemContext* openeParser::Member_listContext::member_item(size_t i) {
  return getRuleContext<openeParser::Member_itemContext>(i);
}


size_t openeParser::Member_listContext::getRuleIndex() const {
  return openeParser::RuleMember_list;
}

void openeParser::Member_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMember_list(this);
}

void openeParser::Member_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMember_list(this);
}


antlrcpp::Any openeParser::Member_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitMember_list(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Member_listContext* openeParser::member_list() {
  Member_listContext *_localctx = _tracker.createInstance<Member_listContext>(_ctx, getState());
  enterRule(_localctx, 24, openeParser::RuleMember_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::K_MEMBER_VARIABLE) {
      setState(204);
      member_item();
      setState(209);
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

//----------------- Member_itemContext ------------------------------------------------------------------

openeParser::Member_itemContext::Member_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Member_itemContext::K_MEMBER_VARIABLE() {
  return getToken(openeParser::K_MEMBER_VARIABLE, 0);
}

openeParser::Variable_declContext* openeParser::Member_itemContext::variable_decl() {
  return getRuleContext<openeParser::Variable_declContext>(0);
}


size_t openeParser::Member_itemContext::getRuleIndex() const {
  return openeParser::RuleMember_item;
}

void openeParser::Member_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMember_item(this);
}

void openeParser::Member_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMember_item(this);
}


antlrcpp::Any openeParser::Member_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitMember_item(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Member_itemContext* openeParser::member_item() {
  Member_itemContext *_localctx = _tracker.createInstance<Member_itemContext>(_ctx, getState());
  enterRule(_localctx, 26, openeParser::RuleMember_item);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(210);
    match(openeParser::K_MEMBER_VARIABLE);
    setState(211);
    variable_decl();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Library_list_optContext ------------------------------------------------------------------

openeParser::Library_list_optContext::Library_list_optContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeParser::Library_specContext *> openeParser::Library_list_optContext::library_spec() {
  return getRuleContexts<openeParser::Library_specContext>();
}

openeParser::Library_specContext* openeParser::Library_list_optContext::library_spec(size_t i) {
  return getRuleContext<openeParser::Library_specContext>(i);
}


size_t openeParser::Library_list_optContext::getRuleIndex() const {
  return openeParser::RuleLibrary_list_opt;
}

void openeParser::Library_list_optContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLibrary_list_opt(this);
}

void openeParser::Library_list_optContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLibrary_list_opt(this);
}


antlrcpp::Any openeParser::Library_list_optContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitLibrary_list_opt(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Library_list_optContext* openeParser::library_list_opt() {
  Library_list_optContext *_localctx = _tracker.createInstance<Library_list_optContext>(_ctx, getState());
  enterRule(_localctx, 28, openeParser::RuleLibrary_list_opt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(216);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::K_LIBRARY) {
      setState(213);
      library_spec();
      setState(218);
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

//----------------- Library_specContext ------------------------------------------------------------------

openeParser::Library_specContext::Library_specContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Library_specContext::K_LIBRARY() {
  return getToken(openeParser::K_LIBRARY, 0);
}

tree::TerminalNode* openeParser::Library_specContext::IDENTIFIER() {
  return getToken(openeParser::IDENTIFIER, 0);
}

tree::TerminalNode* openeParser::Library_specContext::NEWLINE() {
  return getToken(openeParser::NEWLINE, 0);
}


size_t openeParser::Library_specContext::getRuleIndex() const {
  return openeParser::RuleLibrary_spec;
}

void openeParser::Library_specContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLibrary_spec(this);
}

void openeParser::Library_specContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLibrary_spec(this);
}


antlrcpp::Any openeParser::Library_specContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitLibrary_spec(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Library_specContext* openeParser::library_spec() {
  Library_specContext *_localctx = _tracker.createInstance<Library_specContext>(_ctx, getState());
  enterRule(_localctx, 30, openeParser::RuleLibrary_spec);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    match(openeParser::K_LIBRARY);
    setState(220);
    match(openeParser::IDENTIFIER);
    setState(221);
    match(openeParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prog_setContext ------------------------------------------------------------------

openeParser::Prog_setContext::Prog_setContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Prog_setContext::K_PROGRAM_SET() {
  return getToken(openeParser::K_PROGRAM_SET, 0);
}

tree::TerminalNode* openeParser::Prog_setContext::TABLE_END() {
  return getToken(openeParser::TABLE_END, 0);
}

openeParser::Prog_set_variable_decl_optContext* openeParser::Prog_setContext::prog_set_variable_decl_opt() {
  return getRuleContext<openeParser::Prog_set_variable_decl_optContext>(0);
}

openeParser::Sub_program_optContext* openeParser::Prog_setContext::sub_program_opt() {
  return getRuleContext<openeParser::Sub_program_optContext>(0);
}

std::vector<tree::TerminalNode *> openeParser::Prog_setContext::TABLE_ITEM() {
  return getTokens(openeParser::TABLE_ITEM);
}

tree::TerminalNode* openeParser::Prog_setContext::TABLE_ITEM(size_t i) {
  return getToken(openeParser::TABLE_ITEM, i);
}

std::vector<tree::TerminalNode *> openeParser::Prog_setContext::TABLE_COMMA() {
  return getTokens(openeParser::TABLE_COMMA);
}

tree::TerminalNode* openeParser::Prog_setContext::TABLE_COMMA(size_t i) {
  return getToken(openeParser::TABLE_COMMA, i);
}

openeParser::Table_commentContext* openeParser::Prog_setContext::table_comment() {
  return getRuleContext<openeParser::Table_commentContext>(0);
}


size_t openeParser::Prog_setContext::getRuleIndex() const {
  return openeParser::RuleProg_set;
}

void openeParser::Prog_setContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg_set(this);
}

void openeParser::Prog_setContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg_set(this);
}


antlrcpp::Any openeParser::Prog_setContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitProg_set(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Prog_setContext* openeParser::prog_set() {
  Prog_setContext *_localctx = _tracker.createInstance<Prog_setContext>(_ctx, getState());
  enterRule(_localctx, 32, openeParser::RuleProg_set);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    match(openeParser::K_PROGRAM_SET);
    setState(224);
    dynamic_cast<Prog_setContext *>(_localctx)->name = match(openeParser::TABLE_ITEM);
    setState(239);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeParser::TABLE_COMMA) {
      setState(225);
      match(openeParser::TABLE_COMMA);
      setState(227);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_ITEM) {
        setState(226);
        dynamic_cast<Prog_setContext *>(_localctx)->base = match(openeParser::TABLE_ITEM);
      }
      setState(237);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_COMMA) {
        setState(229);
        match(openeParser::TABLE_COMMA);
        setState(231);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeParser::TABLE_ITEM) {
          setState(230);
          dynamic_cast<Prog_setContext *>(_localctx)->access = match(openeParser::TABLE_ITEM);
        }
        setState(235);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeParser::TABLE_COMMA) {
          setState(233);
          match(openeParser::TABLE_COMMA);
          setState(234);
          table_comment();
        }
      }
    }
    setState(241);
    match(openeParser::TABLE_END);
    setState(242);
    prog_set_variable_decl_opt();
    setState(243);
    sub_program_opt();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prog_set_variable_decl_optContext ------------------------------------------------------------------

openeParser::Prog_set_variable_decl_optContext::Prog_set_variable_decl_optContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeParser::Prog_set_variable_declContext *> openeParser::Prog_set_variable_decl_optContext::prog_set_variable_decl() {
  return getRuleContexts<openeParser::Prog_set_variable_declContext>();
}

openeParser::Prog_set_variable_declContext* openeParser::Prog_set_variable_decl_optContext::prog_set_variable_decl(size_t i) {
  return getRuleContext<openeParser::Prog_set_variable_declContext>(i);
}


size_t openeParser::Prog_set_variable_decl_optContext::getRuleIndex() const {
  return openeParser::RuleProg_set_variable_decl_opt;
}

void openeParser::Prog_set_variable_decl_optContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg_set_variable_decl_opt(this);
}

void openeParser::Prog_set_variable_decl_optContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg_set_variable_decl_opt(this);
}


antlrcpp::Any openeParser::Prog_set_variable_decl_optContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitProg_set_variable_decl_opt(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Prog_set_variable_decl_optContext* openeParser::prog_set_variable_decl_opt() {
  Prog_set_variable_decl_optContext *_localctx = _tracker.createInstance<Prog_set_variable_decl_optContext>(_ctx, getState());
  enterRule(_localctx, 34, openeParser::RuleProg_set_variable_decl_opt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(248);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::K_PROGRAM_SET_VARIABLE) {
      setState(245);
      prog_set_variable_decl();
      setState(250);
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

//----------------- Prog_set_variable_declContext ------------------------------------------------------------------

openeParser::Prog_set_variable_declContext::Prog_set_variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Prog_set_variable_declContext::K_PROGRAM_SET_VARIABLE() {
  return getToken(openeParser::K_PROGRAM_SET_VARIABLE, 0);
}

openeParser::Variable_declContext* openeParser::Prog_set_variable_declContext::variable_decl() {
  return getRuleContext<openeParser::Variable_declContext>(0);
}


size_t openeParser::Prog_set_variable_declContext::getRuleIndex() const {
  return openeParser::RuleProg_set_variable_decl;
}

void openeParser::Prog_set_variable_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg_set_variable_decl(this);
}

void openeParser::Prog_set_variable_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg_set_variable_decl(this);
}


antlrcpp::Any openeParser::Prog_set_variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitProg_set_variable_decl(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Prog_set_variable_declContext* openeParser::prog_set_variable_decl() {
  Prog_set_variable_declContext *_localctx = _tracker.createInstance<Prog_set_variable_declContext>(_ctx, getState());
  enterRule(_localctx, 36, openeParser::RuleProg_set_variable_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(251);
    match(openeParser::K_PROGRAM_SET_VARIABLE);
    setState(252);
    variable_decl();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_declContext ------------------------------------------------------------------

openeParser::Variable_declContext::Variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Variable_declContext::TABLE_END() {
  return getToken(openeParser::TABLE_END, 0);
}

std::vector<tree::TerminalNode *> openeParser::Variable_declContext::TABLE_ITEM() {
  return getTokens(openeParser::TABLE_ITEM);
}

tree::TerminalNode* openeParser::Variable_declContext::TABLE_ITEM(size_t i) {
  return getToken(openeParser::TABLE_ITEM, i);
}

std::vector<tree::TerminalNode *> openeParser::Variable_declContext::TABLE_COMMA() {
  return getTokens(openeParser::TABLE_COMMA);
}

tree::TerminalNode* openeParser::Variable_declContext::TABLE_COMMA(size_t i) {
  return getToken(openeParser::TABLE_COMMA, i);
}

openeParser::Table_commentContext* openeParser::Variable_declContext::table_comment() {
  return getRuleContext<openeParser::Table_commentContext>(0);
}


size_t openeParser::Variable_declContext::getRuleIndex() const {
  return openeParser::RuleVariable_decl;
}

void openeParser::Variable_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable_decl(this);
}

void openeParser::Variable_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable_decl(this);
}


antlrcpp::Any openeParser::Variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitVariable_decl(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Variable_declContext* openeParser::variable_decl() {
  Variable_declContext *_localctx = _tracker.createInstance<Variable_declContext>(_ctx, getState());
  enterRule(_localctx, 38, openeParser::RuleVariable_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    dynamic_cast<Variable_declContext *>(_localctx)->name = match(openeParser::TABLE_ITEM);
    setState(270);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeParser::TABLE_COMMA) {
      setState(255);
      match(openeParser::TABLE_COMMA);
      setState(257);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_ITEM) {
        setState(256);
        dynamic_cast<Variable_declContext *>(_localctx)->type = match(openeParser::TABLE_ITEM);
      }
      setState(268);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_COMMA) {
        setState(259);
        match(openeParser::TABLE_COMMA);
        setState(260);
        match(openeParser::TABLE_COMMA);
        setState(262);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeParser::TABLE_ITEM) {
          setState(261);
          dynamic_cast<Variable_declContext *>(_localctx)->dimension = match(openeParser::TABLE_ITEM);
        }
        setState(266);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeParser::TABLE_COMMA) {
          setState(264);
          match(openeParser::TABLE_COMMA);
          setState(265);
          table_comment();
        }
      }
    }
    setState(272);
    match(openeParser::TABLE_END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_commentContext ------------------------------------------------------------------

openeParser::Variable_commentContext::Variable_commentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeParser::Variable_comment_elementContext *> openeParser::Variable_commentContext::variable_comment_element() {
  return getRuleContexts<openeParser::Variable_comment_elementContext>();
}

openeParser::Variable_comment_elementContext* openeParser::Variable_commentContext::variable_comment_element(size_t i) {
  return getRuleContext<openeParser::Variable_comment_elementContext>(i);
}


size_t openeParser::Variable_commentContext::getRuleIndex() const {
  return openeParser::RuleVariable_comment;
}

void openeParser::Variable_commentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable_comment(this);
}

void openeParser::Variable_commentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable_comment(this);
}


antlrcpp::Any openeParser::Variable_commentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitVariable_comment(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Variable_commentContext* openeParser::variable_comment() {
  Variable_commentContext *_localctx = _tracker.createInstance<Variable_commentContext>(_ctx, getState());
  enterRule(_localctx, 40, openeParser::RuleVariable_comment);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(277);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << openeParser::COMMA)
      | (1ULL << openeParser::IDENTIFIER)
      | (1ULL << openeParser::OTHER_CHAR))) != 0)) {
      setState(274);
      variable_comment_element();
      setState(279);
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

//----------------- Variable_comment_elementContext ------------------------------------------------------------------

openeParser::Variable_comment_elementContext::Variable_comment_elementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Variable_comment_elementContext::IDENTIFIER() {
  return getToken(openeParser::IDENTIFIER, 0);
}

tree::TerminalNode* openeParser::Variable_comment_elementContext::OTHER_CHAR() {
  return getToken(openeParser::OTHER_CHAR, 0);
}

tree::TerminalNode* openeParser::Variable_comment_elementContext::COMMA() {
  return getToken(openeParser::COMMA, 0);
}


size_t openeParser::Variable_comment_elementContext::getRuleIndex() const {
  return openeParser::RuleVariable_comment_element;
}

void openeParser::Variable_comment_elementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable_comment_element(this);
}

void openeParser::Variable_comment_elementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable_comment_element(this);
}


antlrcpp::Any openeParser::Variable_comment_elementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitVariable_comment_element(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Variable_comment_elementContext* openeParser::variable_comment_element() {
  Variable_comment_elementContext *_localctx = _tracker.createInstance<Variable_comment_elementContext>(_ctx, getState());
  enterRule(_localctx, 42, openeParser::RuleVariable_comment_element);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(280);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << openeParser::COMMA)
      | (1ULL << openeParser::IDENTIFIER)
      | (1ULL << openeParser::OTHER_CHAR))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_nameContext ------------------------------------------------------------------

openeParser::Variable_nameContext::Variable_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Variable_nameContext::IDENTIFIER() {
  return getToken(openeParser::IDENTIFIER, 0);
}


size_t openeParser::Variable_nameContext::getRuleIndex() const {
  return openeParser::RuleVariable_name;
}

void openeParser::Variable_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable_name(this);
}

void openeParser::Variable_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable_name(this);
}


antlrcpp::Any openeParser::Variable_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitVariable_name(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Variable_nameContext* openeParser::variable_name() {
  Variable_nameContext *_localctx = _tracker.createInstance<Variable_nameContext>(_ctx, getState());
  enterRule(_localctx, 44, openeParser::RuleVariable_name);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    match(openeParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_typeContext ------------------------------------------------------------------

openeParser::Variable_typeContext::Variable_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Variable_typeContext::IDENTIFIER() {
  return getToken(openeParser::IDENTIFIER, 0);
}


size_t openeParser::Variable_typeContext::getRuleIndex() const {
  return openeParser::RuleVariable_type;
}

void openeParser::Variable_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable_type(this);
}

void openeParser::Variable_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable_type(this);
}


antlrcpp::Any openeParser::Variable_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitVariable_type(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Variable_typeContext* openeParser::variable_type() {
  Variable_typeContext *_localctx = _tracker.createInstance<Variable_typeContext>(_ctx, getState());
  enterRule(_localctx, 46, openeParser::RuleVariable_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(284);
    match(openeParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dimension_declContext ------------------------------------------------------------------

openeParser::Dimension_declContext::Dimension_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> openeParser::Dimension_declContext::DQUOTE() {
  return getTokens(openeParser::DQUOTE);
}

tree::TerminalNode* openeParser::Dimension_declContext::DQUOTE(size_t i) {
  return getToken(openeParser::DQUOTE, i);
}

tree::TerminalNode* openeParser::Dimension_declContext::INTEGER_LITERAL() {
  return getToken(openeParser::INTEGER_LITERAL, 0);
}


size_t openeParser::Dimension_declContext::getRuleIndex() const {
  return openeParser::RuleDimension_decl;
}

void openeParser::Dimension_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDimension_decl(this);
}

void openeParser::Dimension_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDimension_decl(this);
}


antlrcpp::Any openeParser::Dimension_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitDimension_decl(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Dimension_declContext* openeParser::dimension_decl() {
  Dimension_declContext *_localctx = _tracker.createInstance<Dimension_declContext>(_ctx, getState());
  enterRule(_localctx, 48, openeParser::RuleDimension_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(286);
    match(openeParser::DQUOTE);
    setState(287);
    match(openeParser::INTEGER_LITERAL);
    setState(288);
    match(openeParser::DQUOTE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sub_program_optContext ------------------------------------------------------------------

openeParser::Sub_program_optContext::Sub_program_optContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeParser::Sub_programContext *> openeParser::Sub_program_optContext::sub_program() {
  return getRuleContexts<openeParser::Sub_programContext>();
}

openeParser::Sub_programContext* openeParser::Sub_program_optContext::sub_program(size_t i) {
  return getRuleContext<openeParser::Sub_programContext>(i);
}

std::vector<tree::TerminalNode *> openeParser::Sub_program_optContext::NEWLINE() {
  return getTokens(openeParser::NEWLINE);
}

tree::TerminalNode* openeParser::Sub_program_optContext::NEWLINE(size_t i) {
  return getToken(openeParser::NEWLINE, i);
}


size_t openeParser::Sub_program_optContext::getRuleIndex() const {
  return openeParser::RuleSub_program_opt;
}

void openeParser::Sub_program_optContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSub_program_opt(this);
}

void openeParser::Sub_program_optContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSub_program_opt(this);
}


antlrcpp::Any openeParser::Sub_program_optContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitSub_program_opt(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Sub_program_optContext* openeParser::sub_program_opt() {
  Sub_program_optContext *_localctx = _tracker.createInstance<Sub_program_optContext>(_ctx, getState());
  enterRule(_localctx, 50, openeParser::RuleSub_program_opt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(305);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::K_SUB_PROGRAM

    || _la == openeParser::NEWLINE) {
      setState(293);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == openeParser::NEWLINE) {
        setState(290);
        match(openeParser::NEWLINE);
        setState(295);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(296);
      sub_program();
      setState(300);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(297);
          match(openeParser::NEWLINE); 
        }
        setState(302);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
      }
      setState(307);
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

//----------------- Sub_programContext ------------------------------------------------------------------

openeParser::Sub_programContext::Sub_programContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Sub_programContext::K_SUB_PROGRAM() {
  return getToken(openeParser::K_SUB_PROGRAM, 0);
}

tree::TerminalNode* openeParser::Sub_programContext::TABLE_END() {
  return getToken(openeParser::TABLE_END, 0);
}

openeParser::Parameter_decl_listContext* openeParser::Sub_programContext::parameter_decl_list() {
  return getRuleContext<openeParser::Parameter_decl_listContext>(0);
}

openeParser::Statement_listContext* openeParser::Sub_programContext::statement_list() {
  return getRuleContext<openeParser::Statement_listContext>(0);
}

std::vector<tree::TerminalNode *> openeParser::Sub_programContext::TABLE_ITEM() {
  return getTokens(openeParser::TABLE_ITEM);
}

tree::TerminalNode* openeParser::Sub_programContext::TABLE_ITEM(size_t i) {
  return getToken(openeParser::TABLE_ITEM, i);
}

std::vector<tree::TerminalNode *> openeParser::Sub_programContext::TABLE_COMMA() {
  return getTokens(openeParser::TABLE_COMMA);
}

tree::TerminalNode* openeParser::Sub_programContext::TABLE_COMMA(size_t i) {
  return getToken(openeParser::TABLE_COMMA, i);
}

std::vector<openeParser::Local_variable_declContext *> openeParser::Sub_programContext::local_variable_decl() {
  return getRuleContexts<openeParser::Local_variable_declContext>();
}

openeParser::Local_variable_declContext* openeParser::Sub_programContext::local_variable_decl(size_t i) {
  return getRuleContext<openeParser::Local_variable_declContext>(i);
}

openeParser::Table_commentContext* openeParser::Sub_programContext::table_comment() {
  return getRuleContext<openeParser::Table_commentContext>(0);
}


size_t openeParser::Sub_programContext::getRuleIndex() const {
  return openeParser::RuleSub_program;
}

void openeParser::Sub_programContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSub_program(this);
}

void openeParser::Sub_programContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSub_program(this);
}


antlrcpp::Any openeParser::Sub_programContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitSub_program(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Sub_programContext* openeParser::sub_program() {
  Sub_programContext *_localctx = _tracker.createInstance<Sub_programContext>(_ctx, getState());
  enterRule(_localctx, 52, openeParser::RuleSub_program);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(308);
    match(openeParser::K_SUB_PROGRAM);
    setState(309);
    dynamic_cast<Sub_programContext *>(_localctx)->name = match(openeParser::TABLE_ITEM);
    setState(324);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeParser::TABLE_COMMA) {
      setState(310);
      match(openeParser::TABLE_COMMA);
      setState(312);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_ITEM) {
        setState(311);
        dynamic_cast<Sub_programContext *>(_localctx)->type = match(openeParser::TABLE_ITEM);
      }
      setState(322);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_COMMA) {
        setState(314);
        match(openeParser::TABLE_COMMA);
        setState(316);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeParser::TABLE_ITEM) {
          setState(315);
          dynamic_cast<Sub_programContext *>(_localctx)->access = match(openeParser::TABLE_ITEM);
        }
        setState(320);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeParser::TABLE_COMMA) {
          setState(318);
          match(openeParser::TABLE_COMMA);
          setState(319);
          table_comment();
        }
      }
    }
    setState(326);
    match(openeParser::TABLE_END);
    setState(327);
    parameter_decl_list();
    setState(331);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::K_LOCAL_VARIABLE) {
      setState(328);
      local_variable_decl();
      setState(333);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(334);
    statement_list();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Parameter_decl_listContext ------------------------------------------------------------------

openeParser::Parameter_decl_listContext::Parameter_decl_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeParser::Parameter_declContext *> openeParser::Parameter_decl_listContext::parameter_decl() {
  return getRuleContexts<openeParser::Parameter_declContext>();
}

openeParser::Parameter_declContext* openeParser::Parameter_decl_listContext::parameter_decl(size_t i) {
  return getRuleContext<openeParser::Parameter_declContext>(i);
}


size_t openeParser::Parameter_decl_listContext::getRuleIndex() const {
  return openeParser::RuleParameter_decl_list;
}

void openeParser::Parameter_decl_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter_decl_list(this);
}

void openeParser::Parameter_decl_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter_decl_list(this);
}


antlrcpp::Any openeParser::Parameter_decl_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitParameter_decl_list(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Parameter_decl_listContext* openeParser::parameter_decl_list() {
  Parameter_decl_listContext *_localctx = _tracker.createInstance<Parameter_decl_listContext>(_ctx, getState());
  enterRule(_localctx, 54, openeParser::RuleParameter_decl_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(339);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == openeParser::K_PARAMETER) {
      setState(336);
      parameter_decl();
      setState(341);
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

//----------------- Parameter_declContext ------------------------------------------------------------------

openeParser::Parameter_declContext::Parameter_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Parameter_declContext::K_PARAMETER() {
  return getToken(openeParser::K_PARAMETER, 0);
}

std::vector<tree::TerminalNode *> openeParser::Parameter_declContext::TABLE_COMMA() {
  return getTokens(openeParser::TABLE_COMMA);
}

tree::TerminalNode* openeParser::Parameter_declContext::TABLE_COMMA(size_t i) {
  return getToken(openeParser::TABLE_COMMA, i);
}

tree::TerminalNode* openeParser::Parameter_declContext::TABLE_END() {
  return getToken(openeParser::TABLE_END, 0);
}

std::vector<tree::TerminalNode *> openeParser::Parameter_declContext::TABLE_ITEM() {
  return getTokens(openeParser::TABLE_ITEM);
}

tree::TerminalNode* openeParser::Parameter_declContext::TABLE_ITEM(size_t i) {
  return getToken(openeParser::TABLE_ITEM, i);
}

openeParser::Table_commentContext* openeParser::Parameter_declContext::table_comment() {
  return getRuleContext<openeParser::Table_commentContext>(0);
}


size_t openeParser::Parameter_declContext::getRuleIndex() const {
  return openeParser::RuleParameter_decl;
}

void openeParser::Parameter_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter_decl(this);
}

void openeParser::Parameter_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter_decl(this);
}


antlrcpp::Any openeParser::Parameter_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitParameter_decl(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Parameter_declContext* openeParser::parameter_decl() {
  Parameter_declContext *_localctx = _tracker.createInstance<Parameter_declContext>(_ctx, getState());
  enterRule(_localctx, 56, openeParser::RuleParameter_decl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(342);
    match(openeParser::K_PARAMETER);
    setState(343);
    dynamic_cast<Parameter_declContext *>(_localctx)->name = match(openeParser::TABLE_ITEM);
    setState(344);
    match(openeParser::TABLE_COMMA);
    setState(345);
    dynamic_cast<Parameter_declContext *>(_localctx)->type = match(openeParser::TABLE_ITEM);
    setState(357);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == openeParser::TABLE_COMMA) {
      setState(346);
      match(openeParser::TABLE_COMMA);
      setState(350);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == openeParser::TABLE_ITEM) {
        setState(347);
        dynamic_cast<Parameter_declContext *>(_localctx)->attributes = match(openeParser::TABLE_ITEM);
        setState(352);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(355);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == openeParser::TABLE_COMMA) {
        setState(353);
        match(openeParser::TABLE_COMMA);
        setState(354);
        table_comment();
      }
    }
    setState(359);
    match(openeParser::TABLE_END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Local_variable_declContext ------------------------------------------------------------------

openeParser::Local_variable_declContext::Local_variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Local_variable_declContext::K_LOCAL_VARIABLE() {
  return getToken(openeParser::K_LOCAL_VARIABLE, 0);
}

openeParser::Variable_declContext* openeParser::Local_variable_declContext::variable_decl() {
  return getRuleContext<openeParser::Variable_declContext>(0);
}


size_t openeParser::Local_variable_declContext::getRuleIndex() const {
  return openeParser::RuleLocal_variable_decl;
}

void openeParser::Local_variable_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocal_variable_decl(this);
}

void openeParser::Local_variable_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocal_variable_decl(this);
}


antlrcpp::Any openeParser::Local_variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitLocal_variable_decl(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Local_variable_declContext* openeParser::local_variable_decl() {
  Local_variable_declContext *_localctx = _tracker.createInstance<Local_variable_declContext>(_ctx, getState());
  enterRule(_localctx, 58, openeParser::RuleLocal_variable_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(361);
    match(openeParser::K_LOCAL_VARIABLE);
    setState(362);
    variable_decl();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Statement_listContext ------------------------------------------------------------------

openeParser::Statement_listContext::Statement_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> openeParser::Statement_listContext::NEWLINE() {
  return getTokens(openeParser::NEWLINE);
}

tree::TerminalNode* openeParser::Statement_listContext::NEWLINE(size_t i) {
  return getToken(openeParser::NEWLINE, i);
}

std::vector<openeParser::StatementContext *> openeParser::Statement_listContext::statement() {
  return getRuleContexts<openeParser::StatementContext>();
}

openeParser::StatementContext* openeParser::Statement_listContext::statement(size_t i) {
  return getRuleContext<openeParser::StatementContext>(i);
}


size_t openeParser::Statement_listContext::getRuleIndex() const {
  return openeParser::RuleStatement_list;
}

void openeParser::Statement_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement_list(this);
}

void openeParser::Statement_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement_list(this);
}


antlrcpp::Any openeParser::Statement_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitStatement_list(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Statement_listContext* openeParser::statement_list() {
  Statement_listContext *_localctx = _tracker.createInstance<Statement_listContext>(_ctx, getState());
  enterRule(_localctx, 60, openeParser::RuleStatement_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(370);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(365);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << openeParser::K_IF_TRUE)
          | (1ULL << openeParser::K_IF)
          | (1ULL << openeParser::K_WHILE)
          | (1ULL << openeParser::K_FOR)
          | (1ULL << openeParser::K_TRUE)
          | (1ULL << openeParser::K_FALSE)
          | (1ULL << openeParser::K_SUB_OPT)
          | (1ULL << openeParser::LBRACK)
          | (1ULL << openeParser::SHARP)
          | (1ULL << openeParser::ADDRESS)
          | (1ULL << openeParser::INTEGER_LITERAL)
          | (1ULL << openeParser::FLOAT_LITERAL)
          | (1ULL << openeParser::IDENTIFIER)
          | (1ULL << openeParser::STRING_LITERAL))) != 0)) {
          setState(364);
          statement();
        }
        setState(367);
        match(openeParser::NEWLINE); 
      }
      setState(372);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
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

openeParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeParser::StatementContext::getRuleIndex() const {
  return openeParser::RuleStatement;
}

void openeParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

openeParser::ExpressionContext* openeParser::ExpressionStatementContext::expression() {
  return getRuleContext<openeParser::ExpressionContext>(0);
}

openeParser::ExpressionStatementContext::ExpressionStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void openeParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}
void openeParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}

antlrcpp::Any openeParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConditionStatementContext ------------------------------------------------------------------

openeParser::Condition_statementContext* openeParser::ConditionStatementContext::condition_statement() {
  return getRuleContext<openeParser::Condition_statementContext>(0);
}

openeParser::ConditionStatementContext::ConditionStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void openeParser::ConditionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionStatement(this);
}
void openeParser::ConditionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionStatement(this);
}

antlrcpp::Any openeParser::ConditionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitConditionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LoopStatementContext ------------------------------------------------------------------

openeParser::Loop_statementContext* openeParser::LoopStatementContext::loop_statement() {
  return getRuleContext<openeParser::Loop_statementContext>(0);
}

openeParser::LoopStatementContext::LoopStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void openeParser::LoopStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoopStatement(this);
}
void openeParser::LoopStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoopStatement(this);
}

antlrcpp::Any openeParser::LoopStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitLoopStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStatementContext ------------------------------------------------------------------

openeParser::Hierarchy_identifierContext* openeParser::AssignStatementContext::hierarchy_identifier() {
  return getRuleContext<openeParser::Hierarchy_identifierContext>(0);
}

openeParser::ExpressionContext* openeParser::AssignStatementContext::expression() {
  return getRuleContext<openeParser::ExpressionContext>(0);
}

tree::TerminalNode* openeParser::AssignStatementContext::K_ASSIGN_OPT() {
  return getToken(openeParser::K_ASSIGN_OPT, 0);
}

tree::TerminalNode* openeParser::AssignStatementContext::K_AECOM_OPT() {
  return getToken(openeParser::K_AECOM_OPT, 0);
}

openeParser::AssignStatementContext::AssignStatementContext(StatementContext *ctx) { copyFrom(ctx); }

void openeParser::AssignStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignStatement(this);
}
void openeParser::AssignStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignStatement(this);
}

antlrcpp::Any openeParser::AssignStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitAssignStatement(this);
  else
    return visitor->visitChildren(this);
}
openeParser::StatementContext* openeParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 62, openeParser::RuleStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(380);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<openeParser::ConditionStatementContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(373);
      condition_statement();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<openeParser::AssignStatementContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(374);
      hierarchy_identifier();
      setState(375);
      _la = _input->LA(1);
      if (!(_la == openeParser::K_AECOM_OPT

      || _la == openeParser::K_ASSIGN_OPT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(376);
      expression(0);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<openeParser::ExpressionStatementContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(378);
      expression(0);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<openeParser::LoopStatementContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(379);
      loop_statement();
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

//----------------- Loop_statementContext ------------------------------------------------------------------

openeParser::Loop_statementContext::Loop_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeParser::Loop_statementContext::getRuleIndex() const {
  return openeParser::RuleLoop_statement;
}

void openeParser::Loop_statementContext::copyFrom(Loop_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ForContext ------------------------------------------------------------------

tree::TerminalNode* openeParser::ForContext::K_FOR() {
  return getToken(openeParser::K_FOR, 0);
}

std::vector<tree::TerminalNode *> openeParser::ForContext::LBRACK() {
  return getTokens(openeParser::LBRACK);
}

tree::TerminalNode* openeParser::ForContext::LBRACK(size_t i) {
  return getToken(openeParser::LBRACK, i);
}

openeParser::ExpressionContext* openeParser::ForContext::expression() {
  return getRuleContext<openeParser::ExpressionContext>(0);
}

tree::TerminalNode* openeParser::ForContext::COMMA() {
  return getToken(openeParser::COMMA, 0);
}

std::vector<tree::TerminalNode *> openeParser::ForContext::RBRACK() {
  return getTokens(openeParser::RBRACK);
}

tree::TerminalNode* openeParser::ForContext::RBRACK(size_t i) {
  return getToken(openeParser::RBRACK, i);
}

openeParser::Statement_listContext* openeParser::ForContext::statement_list() {
  return getRuleContext<openeParser::Statement_listContext>(0);
}

tree::TerminalNode* openeParser::ForContext::K_FOR_END() {
  return getToken(openeParser::K_FOR_END, 0);
}

tree::TerminalNode* openeParser::ForContext::IDENTIFIER() {
  return getToken(openeParser::IDENTIFIER, 0);
}

openeParser::ForContext::ForContext(Loop_statementContext *ctx) { copyFrom(ctx); }

void openeParser::ForContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor(this);
}
void openeParser::ForContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor(this);
}

antlrcpp::Any openeParser::ForContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitFor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileContext ------------------------------------------------------------------

tree::TerminalNode* openeParser::WhileContext::K_WHILE() {
  return getToken(openeParser::K_WHILE, 0);
}

std::vector<tree::TerminalNode *> openeParser::WhileContext::LBRACK() {
  return getTokens(openeParser::LBRACK);
}

tree::TerminalNode* openeParser::WhileContext::LBRACK(size_t i) {
  return getToken(openeParser::LBRACK, i);
}

openeParser::ExpressionContext* openeParser::WhileContext::expression() {
  return getRuleContext<openeParser::ExpressionContext>(0);
}

std::vector<tree::TerminalNode *> openeParser::WhileContext::RBRACK() {
  return getTokens(openeParser::RBRACK);
}

tree::TerminalNode* openeParser::WhileContext::RBRACK(size_t i) {
  return getToken(openeParser::RBRACK, i);
}

openeParser::Statement_listContext* openeParser::WhileContext::statement_list() {
  return getRuleContext<openeParser::Statement_listContext>(0);
}

tree::TerminalNode* openeParser::WhileContext::K_WHILE_END() {
  return getToken(openeParser::K_WHILE_END, 0);
}

openeParser::WhileContext::WhileContext(Loop_statementContext *ctx) { copyFrom(ctx); }

void openeParser::WhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhile(this);
}
void openeParser::WhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhile(this);
}

antlrcpp::Any openeParser::WhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitWhile(this);
  else
    return visitor->visitChildren(this);
}
openeParser::Loop_statementContext* openeParser::loop_statement() {
  Loop_statementContext *_localctx = _tracker.createInstance<Loop_statementContext>(_ctx, getState());
  enterRule(_localctx, 64, openeParser::RuleLoop_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(404);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeParser::K_WHILE: {
        _localctx = dynamic_cast<Loop_statementContext *>(_tracker.createInstance<openeParser::WhileContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(382);
        match(openeParser::K_WHILE);
        setState(383);
        match(openeParser::LBRACK);
        setState(384);
        expression(0);
        setState(385);
        match(openeParser::RBRACK);
        setState(386);
        statement_list();
        setState(387);
        match(openeParser::K_WHILE_END);
        setState(388);
        match(openeParser::LBRACK);
        setState(389);
        match(openeParser::RBRACK);
        break;
      }

      case openeParser::K_FOR: {
        _localctx = dynamic_cast<Loop_statementContext *>(_tracker.createInstance<openeParser::ForContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(391);
        match(openeParser::K_FOR);
        setState(392);
        match(openeParser::LBRACK);
        setState(393);
        expression(0);
        setState(394);
        match(openeParser::COMMA);
        setState(396);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeParser::IDENTIFIER) {
          setState(395);
          match(openeParser::IDENTIFIER);
        }
        setState(398);
        match(openeParser::RBRACK);
        setState(399);
        statement_list();
        setState(400);
        match(openeParser::K_FOR_END);
        setState(401);
        match(openeParser::LBRACK);
        setState(402);
        match(openeParser::RBRACK);
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

openeParser::Condition_statementContext::Condition_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeParser::Condition_statementContext::getRuleIndex() const {
  return openeParser::RuleCondition_statement;
}

void openeParser::Condition_statementContext::copyFrom(Condition_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IfStmtContext ------------------------------------------------------------------

tree::TerminalNode* openeParser::IfStmtContext::K_IF() {
  return getToken(openeParser::K_IF, 0);
}

tree::TerminalNode* openeParser::IfStmtContext::LBRACK() {
  return getToken(openeParser::LBRACK, 0);
}

openeParser::ExpressionContext* openeParser::IfStmtContext::expression() {
  return getRuleContext<openeParser::ExpressionContext>(0);
}

tree::TerminalNode* openeParser::IfStmtContext::RBRACK() {
  return getToken(openeParser::RBRACK, 0);
}

openeParser::Statement_listContext* openeParser::IfStmtContext::statement_list() {
  return getRuleContext<openeParser::Statement_listContext>(0);
}

tree::TerminalNode* openeParser::IfStmtContext::K_END_IF() {
  return getToken(openeParser::K_END_IF, 0);
}

openeParser::Condition_statement_elseContext* openeParser::IfStmtContext::condition_statement_else() {
  return getRuleContext<openeParser::Condition_statement_elseContext>(0);
}

openeParser::IfStmtContext::IfStmtContext(Condition_statementContext *ctx) { copyFrom(ctx); }

void openeParser::IfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStmt(this);
}
void openeParser::IfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStmt(this);
}

antlrcpp::Any openeParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfTrueStmtContext ------------------------------------------------------------------

tree::TerminalNode* openeParser::IfTrueStmtContext::K_IF_TRUE() {
  return getToken(openeParser::K_IF_TRUE, 0);
}

tree::TerminalNode* openeParser::IfTrueStmtContext::LBRACK() {
  return getToken(openeParser::LBRACK, 0);
}

openeParser::ExpressionContext* openeParser::IfTrueStmtContext::expression() {
  return getRuleContext<openeParser::ExpressionContext>(0);
}

tree::TerminalNode* openeParser::IfTrueStmtContext::RBRACK() {
  return getToken(openeParser::RBRACK, 0);
}

openeParser::Statement_listContext* openeParser::IfTrueStmtContext::statement_list() {
  return getRuleContext<openeParser::Statement_listContext>(0);
}

tree::TerminalNode* openeParser::IfTrueStmtContext::K_END_IF_TRUE() {
  return getToken(openeParser::K_END_IF_TRUE, 0);
}

openeParser::IfTrueStmtContext::IfTrueStmtContext(Condition_statementContext *ctx) { copyFrom(ctx); }

void openeParser::IfTrueStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfTrueStmt(this);
}
void openeParser::IfTrueStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfTrueStmt(this);
}

antlrcpp::Any openeParser::IfTrueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitIfTrueStmt(this);
  else
    return visitor->visitChildren(this);
}
openeParser::Condition_statementContext* openeParser::condition_statement() {
  Condition_statementContext *_localctx = _tracker.createInstance<Condition_statementContext>(_ctx, getState());
  enterRule(_localctx, 66, openeParser::RuleCondition_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(423);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeParser::K_IF: {
        _localctx = dynamic_cast<Condition_statementContext *>(_tracker.createInstance<openeParser::IfStmtContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(406);
        match(openeParser::K_IF);
        setState(407);
        match(openeParser::LBRACK);
        setState(408);
        expression(0);
        setState(409);
        match(openeParser::RBRACK);
        setState(410);
        statement_list();
        setState(412);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == openeParser::K_ELSE) {
          setState(411);
          condition_statement_else();
        }
        setState(414);
        match(openeParser::K_END_IF);
        break;
      }

      case openeParser::K_IF_TRUE: {
        _localctx = dynamic_cast<Condition_statementContext *>(_tracker.createInstance<openeParser::IfTrueStmtContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(416);
        match(openeParser::K_IF_TRUE);
        setState(417);
        match(openeParser::LBRACK);
        setState(418);
        expression(0);
        setState(419);
        match(openeParser::RBRACK);
        setState(420);
        statement_list();
        setState(421);
        match(openeParser::K_END_IF_TRUE);
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

//----------------- Condition_statement_elseContext ------------------------------------------------------------------

openeParser::Condition_statement_elseContext::Condition_statement_elseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Condition_statement_elseContext::K_ELSE() {
  return getToken(openeParser::K_ELSE, 0);
}

openeParser::Statement_listContext* openeParser::Condition_statement_elseContext::statement_list() {
  return getRuleContext<openeParser::Statement_listContext>(0);
}


size_t openeParser::Condition_statement_elseContext::getRuleIndex() const {
  return openeParser::RuleCondition_statement_else;
}

void openeParser::Condition_statement_elseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondition_statement_else(this);
}

void openeParser::Condition_statement_elseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondition_statement_else(this);
}


antlrcpp::Any openeParser::Condition_statement_elseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitCondition_statement_else(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Condition_statement_elseContext* openeParser::condition_statement_else() {
  Condition_statement_elseContext *_localctx = _tracker.createInstance<Condition_statement_elseContext>(_ctx, getState());
  enterRule(_localctx, 68, openeParser::RuleCondition_statement_else);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(425);
    match(openeParser::K_ELSE);
    setState(426);
    statement_list();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Hierarchy_identifierContext ------------------------------------------------------------------

openeParser::Hierarchy_identifierContext::Hierarchy_identifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<openeParser::Name_componentContext *> openeParser::Hierarchy_identifierContext::name_component() {
  return getRuleContexts<openeParser::Name_componentContext>();
}

openeParser::Name_componentContext* openeParser::Hierarchy_identifierContext::name_component(size_t i) {
  return getRuleContext<openeParser::Name_componentContext>(i);
}

std::vector<tree::TerminalNode *> openeParser::Hierarchy_identifierContext::DOT() {
  return getTokens(openeParser::DOT);
}

tree::TerminalNode* openeParser::Hierarchy_identifierContext::DOT(size_t i) {
  return getToken(openeParser::DOT, i);
}


size_t openeParser::Hierarchy_identifierContext::getRuleIndex() const {
  return openeParser::RuleHierarchy_identifier;
}

void openeParser::Hierarchy_identifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHierarchy_identifier(this);
}

void openeParser::Hierarchy_identifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHierarchy_identifier(this);
}


antlrcpp::Any openeParser::Hierarchy_identifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitHierarchy_identifier(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Hierarchy_identifierContext* openeParser::hierarchy_identifier() {
  Hierarchy_identifierContext *_localctx = _tracker.createInstance<Hierarchy_identifierContext>(_ctx, getState());
  enterRule(_localctx, 70, openeParser::RuleHierarchy_identifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(428);
    name_component(0);
    setState(433);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(429);
        match(openeParser::DOT);
        setState(430);
        name_component(0); 
      }
      setState(435);
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

//----------------- Name_componentContext ------------------------------------------------------------------

openeParser::Name_componentContext::Name_componentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeParser::Name_componentContext::getRuleIndex() const {
  return openeParser::RuleName_component;
}

void openeParser::Name_componentContext::copyFrom(Name_componentContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IdentifierContext ------------------------------------------------------------------

tree::TerminalNode* openeParser::IdentifierContext::IDENTIFIER() {
  return getToken(openeParser::IDENTIFIER, 0);
}

openeParser::IdentifierContext::IdentifierContext(Name_componentContext *ctx) { copyFrom(ctx); }

void openeParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}
void openeParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}

antlrcpp::Any openeParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallWithArguContext ------------------------------------------------------------------

openeParser::Name_componentContext* openeParser::FuncCallWithArguContext::name_component() {
  return getRuleContext<openeParser::Name_componentContext>(0);
}

tree::TerminalNode* openeParser::FuncCallWithArguContext::LBRACK() {
  return getToken(openeParser::LBRACK, 0);
}

std::vector<openeParser::ExpressionContext *> openeParser::FuncCallWithArguContext::expression() {
  return getRuleContexts<openeParser::ExpressionContext>();
}

openeParser::ExpressionContext* openeParser::FuncCallWithArguContext::expression(size_t i) {
  return getRuleContext<openeParser::ExpressionContext>(i);
}

tree::TerminalNode* openeParser::FuncCallWithArguContext::RBRACK() {
  return getToken(openeParser::RBRACK, 0);
}

std::vector<tree::TerminalNode *> openeParser::FuncCallWithArguContext::COMMA() {
  return getTokens(openeParser::COMMA);
}

tree::TerminalNode* openeParser::FuncCallWithArguContext::COMMA(size_t i) {
  return getToken(openeParser::COMMA, i);
}

openeParser::FuncCallWithArguContext::FuncCallWithArguContext(Name_componentContext *ctx) { copyFrom(ctx); }

void openeParser::FuncCallWithArguContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCallWithArgu(this);
}
void openeParser::FuncCallWithArguContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCallWithArgu(this);
}

antlrcpp::Any openeParser::FuncCallWithArguContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitFuncCallWithArgu(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallWithoutArguContext ------------------------------------------------------------------

openeParser::Name_componentContext* openeParser::FuncCallWithoutArguContext::name_component() {
  return getRuleContext<openeParser::Name_componentContext>(0);
}

tree::TerminalNode* openeParser::FuncCallWithoutArguContext::LBRACK() {
  return getToken(openeParser::LBRACK, 0);
}

tree::TerminalNode* openeParser::FuncCallWithoutArguContext::RBRACK() {
  return getToken(openeParser::RBRACK, 0);
}

openeParser::FuncCallWithoutArguContext::FuncCallWithoutArguContext(Name_componentContext *ctx) { copyFrom(ctx); }

void openeParser::FuncCallWithoutArguContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCallWithoutArgu(this);
}
void openeParser::FuncCallWithoutArguContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCallWithoutArgu(this);
}

antlrcpp::Any openeParser::FuncCallWithoutArguContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitFuncCallWithoutArgu(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayIndexContext ------------------------------------------------------------------

openeParser::Name_componentContext* openeParser::ArrayIndexContext::name_component() {
  return getRuleContext<openeParser::Name_componentContext>(0);
}

tree::TerminalNode* openeParser::ArrayIndexContext::LSQUBRACK() {
  return getToken(openeParser::LSQUBRACK, 0);
}

openeParser::ExpressionContext* openeParser::ArrayIndexContext::expression() {
  return getRuleContext<openeParser::ExpressionContext>(0);
}

tree::TerminalNode* openeParser::ArrayIndexContext::RSQUBRACK() {
  return getToken(openeParser::RSQUBRACK, 0);
}

openeParser::ArrayIndexContext::ArrayIndexContext(Name_componentContext *ctx) { copyFrom(ctx); }

void openeParser::ArrayIndexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayIndex(this);
}
void openeParser::ArrayIndexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayIndex(this);
}

antlrcpp::Any openeParser::ArrayIndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitArrayIndex(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Name_componentContext* openeParser::name_component() {
   return name_component(0);
}

openeParser::Name_componentContext* openeParser::name_component(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  openeParser::Name_componentContext *_localctx = _tracker.createInstance<Name_componentContext>(_ctx, parentState);
  openeParser::Name_componentContext *previousContext = _localctx;
  size_t startState = 72;
  enterRecursionRule(_localctx, 72, openeParser::RuleName_component, precedence);

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

    setState(437);
    match(openeParser::IDENTIFIER);
    _ctx->stop = _input->LT(-1);
    setState(463);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(461);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<FuncCallWithoutArguContext>(_tracker.createInstance<Name_componentContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleName_component);
          setState(439);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(440);
          match(openeParser::LBRACK);
          setState(441);
          match(openeParser::RBRACK);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<FuncCallWithArguContext>(_tracker.createInstance<Name_componentContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleName_component);
          setState(442);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(443);
          match(openeParser::LBRACK);
          setState(444);
          expression(0);
          setState(451);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == openeParser::COMMA) {
            setState(445);
            match(openeParser::COMMA);
            setState(447);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if ((((_la & ~ 0x3fULL) == 0) &&
              ((1ULL << _la) & ((1ULL << openeParser::K_TRUE)
              | (1ULL << openeParser::K_FALSE)
              | (1ULL << openeParser::K_SUB_OPT)
              | (1ULL << openeParser::LBRACK)
              | (1ULL << openeParser::SHARP)
              | (1ULL << openeParser::ADDRESS)
              | (1ULL << openeParser::INTEGER_LITERAL)
              | (1ULL << openeParser::FLOAT_LITERAL)
              | (1ULL << openeParser::IDENTIFIER)
              | (1ULL << openeParser::STRING_LITERAL))) != 0)) {
              setState(446);
              expression(0);
            }
            setState(453);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(454);
          match(openeParser::RBRACK);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ArrayIndexContext>(_tracker.createInstance<Name_componentContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleName_component);
          setState(456);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(457);
          match(openeParser::LSQUBRACK);
          setState(458);
          expression(0);
          setState(459);
          match(openeParser::RSQUBRACK);
          break;
        }

        } 
      }
      setState(465);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
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

openeParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeParser::ExpressionContext::getRuleIndex() const {
  return openeParser::RuleExpression;
}

void openeParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BracketContext ------------------------------------------------------------------

tree::TerminalNode* openeParser::BracketContext::LBRACK() {
  return getToken(openeParser::LBRACK, 0);
}

openeParser::ExpressionContext* openeParser::BracketContext::expression() {
  return getRuleContext<openeParser::ExpressionContext>(0);
}

tree::TerminalNode* openeParser::BracketContext::RBRACK() {
  return getToken(openeParser::RBRACK, 0);
}

openeParser::BracketContext::BracketContext(ExpressionContext *ctx) { copyFrom(ctx); }

void openeParser::BracketContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBracket(this);
}
void openeParser::BracketContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBracket(this);
}

antlrcpp::Any openeParser::BracketContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitBracket(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OptElementContext ------------------------------------------------------------------

openeParser::NumberContext* openeParser::OptElementContext::number() {
  return getRuleContext<openeParser::NumberContext>(0);
}

openeParser::Bool_valueContext* openeParser::OptElementContext::bool_value() {
  return getRuleContext<openeParser::Bool_valueContext>(0);
}

openeParser::Macro_valueContext* openeParser::OptElementContext::macro_value() {
  return getRuleContext<openeParser::Macro_valueContext>(0);
}

openeParser::String_valueContext* openeParser::OptElementContext::string_value() {
  return getRuleContext<openeParser::String_valueContext>(0);
}

openeParser::Hierarchy_identifierContext* openeParser::OptElementContext::hierarchy_identifier() {
  return getRuleContext<openeParser::Hierarchy_identifierContext>(0);
}

openeParser::Func_ptrContext* openeParser::OptElementContext::func_ptr() {
  return getRuleContext<openeParser::Func_ptrContext>(0);
}

openeParser::OptElementContext::OptElementContext(ExpressionContext *ctx) { copyFrom(ctx); }

void openeParser::OptElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOptElement(this);
}
void openeParser::OptElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOptElement(this);
}

antlrcpp::Any openeParser::OptElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitOptElement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryExprContext ------------------------------------------------------------------

std::vector<openeParser::ExpressionContext *> openeParser::BinaryExprContext::expression() {
  return getRuleContexts<openeParser::ExpressionContext>();
}

openeParser::ExpressionContext* openeParser::BinaryExprContext::expression(size_t i) {
  return getRuleContext<openeParser::ExpressionContext>(i);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_MUL_OPT() {
  return getToken(openeParser::K_MUL_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_DIV_OPT() {
  return getToken(openeParser::K_DIV_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_FULL_DIV_OPT() {
  return getToken(openeParser::K_FULL_DIV_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_MOD_OPT() {
  return getToken(openeParser::K_MOD_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_ADD_OPT() {
  return getToken(openeParser::K_ADD_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_SUB_OPT() {
  return getToken(openeParser::K_SUB_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_NOT_EQUAL_OPT() {
  return getToken(openeParser::K_NOT_EQUAL_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_EQUAL_OPT() {
  return getToken(openeParser::K_EQUAL_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_AECOM_OPT() {
  return getToken(openeParser::K_AECOM_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_LESS_OPT() {
  return getToken(openeParser::K_LESS_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_GREAT_OPT() {
  return getToken(openeParser::K_GREAT_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_LESS_EQU_OPT() {
  return getToken(openeParser::K_LESS_EQU_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_GREAT_EQU_OPT() {
  return getToken(openeParser::K_GREAT_EQU_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_LIKE_EQU_OPT() {
  return getToken(openeParser::K_LIKE_EQU_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_AND_OPT() {
  return getToken(openeParser::K_AND_OPT, 0);
}

tree::TerminalNode* openeParser::BinaryExprContext::K_OR_OPT() {
  return getToken(openeParser::K_OR_OPT, 0);
}

openeParser::BinaryExprContext::BinaryExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void openeParser::BinaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBinaryExpr(this);
}
void openeParser::BinaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBinaryExpr(this);
}

antlrcpp::Any openeParser::BinaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitBinaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprContext ------------------------------------------------------------------

openeParser::ExpressionContext* openeParser::UnaryExprContext::expression() {
  return getRuleContext<openeParser::ExpressionContext>(0);
}

tree::TerminalNode* openeParser::UnaryExprContext::K_SUB_OPT() {
  return getToken(openeParser::K_SUB_OPT, 0);
}

openeParser::UnaryExprContext::UnaryExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void openeParser::UnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpr(this);
}
void openeParser::UnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpr(this);
}

antlrcpp::Any openeParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}

openeParser::ExpressionContext* openeParser::expression() {
   return expression(0);
}

openeParser::ExpressionContext* openeParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  openeParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  openeParser::ExpressionContext *previousContext = _localctx;
  size_t startState = 74;
  enterRecursionRule(_localctx, 74, openeParser::RuleExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(479);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeParser::LBRACK: {
        _localctx = _tracker.createInstance<BracketContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(467);
        match(openeParser::LBRACK);
        setState(468);
        expression(0);
        setState(469);
        match(openeParser::RBRACK);
        break;
      }

      case openeParser::K_SUB_OPT: {
        _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(471);
        dynamic_cast<UnaryExprContext *>(_localctx)->opt = match(openeParser::K_SUB_OPT);
        setState(472);
        expression(23);
        break;
      }

      case openeParser::INTEGER_LITERAL:
      case openeParser::FLOAT_LITERAL: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(473);
        number();
        break;
      }

      case openeParser::K_TRUE:
      case openeParser::K_FALSE: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(474);
        bool_value();
        break;
      }

      case openeParser::SHARP: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(475);
        macro_value();
        break;
      }

      case openeParser::STRING_LITERAL: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(476);
        string_value();
        break;
      }

      case openeParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(477);
        hierarchy_identifier();
        break;
      }

      case openeParser::ADDRESS: {
        _localctx = _tracker.createInstance<OptElementContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(478);
        func_ptr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(531);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(529);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(481);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(482);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_MUL_OPT);
          setState(483);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(23);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(484);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(485);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_DIV_OPT);
          setState(486);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(22);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(487);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(488);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_FULL_DIV_OPT);
          setState(489);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(21);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(490);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(491);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_MOD_OPT);
          setState(492);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(20);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(493);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(494);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_ADD_OPT);
          setState(495);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(19);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(496);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(497);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_SUB_OPT);
          setState(498);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(18);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(499);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(500);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_NOT_EQUAL_OPT);
          setState(501);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(17);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(502);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(503);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_EQUAL_OPT);
          setState(504);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(16);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(505);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(506);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_AECOM_OPT);
          setState(507);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(15);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(508);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(509);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_LESS_OPT);
          setState(510);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(14);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(511);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(512);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_GREAT_OPT);
          setState(513);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(13);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(514);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(515);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_LESS_EQU_OPT);
          setState(516);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(12);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(517);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(518);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_GREAT_EQU_OPT);
          setState(519);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(11);
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(520);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(521);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_LIKE_EQU_OPT);
          setState(522);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(10);
          break;
        }

        case 15: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(523);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(524);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_AND_OPT);
          setState(525);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(9);
          break;
        }

        case 16: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lval = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(526);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(527);
          dynamic_cast<BinaryExprContext *>(_localctx)->opt = match(openeParser::K_OR_OPT);
          setState(528);
          dynamic_cast<BinaryExprContext *>(_localctx)->rval = expression(8);
          break;
        }

        } 
      }
      setState(533);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
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

openeParser::Macro_valueContext::Macro_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Macro_valueContext::SHARP() {
  return getToken(openeParser::SHARP, 0);
}

tree::TerminalNode* openeParser::Macro_valueContext::IDENTIFIER() {
  return getToken(openeParser::IDENTIFIER, 0);
}


size_t openeParser::Macro_valueContext::getRuleIndex() const {
  return openeParser::RuleMacro_value;
}

void openeParser::Macro_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMacro_value(this);
}

void openeParser::Macro_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMacro_value(this);
}


antlrcpp::Any openeParser::Macro_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitMacro_value(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Macro_valueContext* openeParser::macro_value() {
  Macro_valueContext *_localctx = _tracker.createInstance<Macro_valueContext>(_ctx, getState());
  enterRule(_localctx, 76, openeParser::RuleMacro_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(534);
    match(openeParser::SHARP);
    setState(535);
    match(openeParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_ptrContext ------------------------------------------------------------------

openeParser::Func_ptrContext::Func_ptrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Func_ptrContext::ADDRESS() {
  return getToken(openeParser::ADDRESS, 0);
}

tree::TerminalNode* openeParser::Func_ptrContext::IDENTIFIER() {
  return getToken(openeParser::IDENTIFIER, 0);
}


size_t openeParser::Func_ptrContext::getRuleIndex() const {
  return openeParser::RuleFunc_ptr;
}

void openeParser::Func_ptrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_ptr(this);
}

void openeParser::Func_ptrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_ptr(this);
}


antlrcpp::Any openeParser::Func_ptrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitFunc_ptr(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Func_ptrContext* openeParser::func_ptr() {
  Func_ptrContext *_localctx = _tracker.createInstance<Func_ptrContext>(_ctx, getState());
  enterRule(_localctx, 78, openeParser::RuleFunc_ptr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(537);
    match(openeParser::ADDRESS);
    setState(538);
    match(openeParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bool_valueContext ------------------------------------------------------------------

openeParser::Bool_valueContext::Bool_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::Bool_valueContext::K_TRUE() {
  return getToken(openeParser::K_TRUE, 0);
}

tree::TerminalNode* openeParser::Bool_valueContext::K_FALSE() {
  return getToken(openeParser::K_FALSE, 0);
}


size_t openeParser::Bool_valueContext::getRuleIndex() const {
  return openeParser::RuleBool_value;
}

void openeParser::Bool_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBool_value(this);
}

void openeParser::Bool_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBool_value(this);
}


antlrcpp::Any openeParser::Bool_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitBool_value(this);
  else
    return visitor->visitChildren(this);
}

openeParser::Bool_valueContext* openeParser::bool_value() {
  Bool_valueContext *_localctx = _tracker.createInstance<Bool_valueContext>(_ctx, getState());
  enterRule(_localctx, 80, openeParser::RuleBool_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(542);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeParser::K_TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(540);
        dynamic_cast<Bool_valueContext *>(_localctx)->bval = match(openeParser::K_TRUE);
        break;
      }

      case openeParser::K_FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(541);
        dynamic_cast<Bool_valueContext *>(_localctx)->bval = match(openeParser::K_FALSE);
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

openeParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t openeParser::NumberContext::getRuleIndex() const {
  return openeParser::RuleNumber;
}

void openeParser::NumberContext::copyFrom(NumberContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FloatContext ------------------------------------------------------------------

tree::TerminalNode* openeParser::FloatContext::FLOAT_LITERAL() {
  return getToken(openeParser::FLOAT_LITERAL, 0);
}

openeParser::FloatContext::FloatContext(NumberContext *ctx) { copyFrom(ctx); }

void openeParser::FloatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloat(this);
}
void openeParser::FloatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloat(this);
}

antlrcpp::Any openeParser::FloatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitFloat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntContext ------------------------------------------------------------------

tree::TerminalNode* openeParser::IntContext::INTEGER_LITERAL() {
  return getToken(openeParser::INTEGER_LITERAL, 0);
}

openeParser::IntContext::IntContext(NumberContext *ctx) { copyFrom(ctx); }

void openeParser::IntContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInt(this);
}
void openeParser::IntContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInt(this);
}

antlrcpp::Any openeParser::IntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitInt(this);
  else
    return visitor->visitChildren(this);
}
openeParser::NumberContext* openeParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 82, openeParser::RuleNumber);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(546);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case openeParser::INTEGER_LITERAL: {
        _localctx = dynamic_cast<NumberContext *>(_tracker.createInstance<openeParser::IntContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(544);
        match(openeParser::INTEGER_LITERAL);
        break;
      }

      case openeParser::FLOAT_LITERAL: {
        _localctx = dynamic_cast<NumberContext *>(_tracker.createInstance<openeParser::FloatContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(545);
        match(openeParser::FLOAT_LITERAL);
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

openeParser::String_valueContext::String_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* openeParser::String_valueContext::STRING_LITERAL() {
  return getToken(openeParser::STRING_LITERAL, 0);
}


size_t openeParser::String_valueContext::getRuleIndex() const {
  return openeParser::RuleString_value;
}

void openeParser::String_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterString_value(this);
}

void openeParser::String_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<openeParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitString_value(this);
}


antlrcpp::Any openeParser::String_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<openeParserVisitor*>(visitor))
    return parserVisitor->visitString_value(this);
  else
    return visitor->visitChildren(this);
}

openeParser::String_valueContext* openeParser::string_value() {
  String_valueContext *_localctx = _tracker.createInstance<String_valueContext>(_ctx, getState());
  enterRule(_localctx, 84, openeParser::RuleString_value);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(548);
    match(openeParser::STRING_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool openeParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 36: return name_componentSempred(dynamic_cast<Name_componentContext *>(context), predicateIndex);
    case 37: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool openeParser::name_componentSempred(Name_componentContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool openeParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 22);
    case 4: return precpred(_ctx, 21);
    case 5: return precpred(_ctx, 20);
    case 6: return precpred(_ctx, 19);
    case 7: return precpred(_ctx, 18);
    case 8: return precpred(_ctx, 17);
    case 9: return precpred(_ctx, 16);
    case 10: return precpred(_ctx, 15);
    case 11: return precpred(_ctx, 14);
    case 12: return precpred(_ctx, 13);
    case 13: return precpred(_ctx, 12);
    case 14: return precpred(_ctx, 11);
    case 15: return precpred(_ctx, 10);
    case 16: return precpred(_ctx, 9);
    case 17: return precpred(_ctx, 8);
    case 18: return precpred(_ctx, 7);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> openeParser::_decisionToDFA;
atn::PredictionContextCache openeParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN openeParser::_atn;
std::vector<uint16_t> openeParser::_serializedATN;

std::vector<std::string> openeParser::_ruleNames = {
  "opene_src", "src_content", "program_set_file", "data_structure_file", 
  "global_variable_file", "dll_define_file", "dll_command", "global_variable_list", 
  "global_variable_item", "edition_spec", "struct_declare", "table_comment", 
  "member_list", "member_item", "library_list_opt", "library_spec", "prog_set", 
  "prog_set_variable_decl_opt", "prog_set_variable_decl", "variable_decl", 
  "variable_comment", "variable_comment_element", "variable_name", "variable_type", 
  "dimension_decl", "sub_program_opt", "sub_program", "parameter_decl_list", 
  "parameter_decl", "local_variable_decl", "statement_list", "statement", 
  "loop_statement", "condition_statement", "condition_statement_else", "hierarchy_identifier", 
  "name_component", "expression", "macro_value", "func_ptr", "bool_value", 
  "number", "string_value"
};

std::vector<std::string> openeParser::_literalNames = {
  "", "'.\u7248\u672C'", "'.\u652F\u6301\u5E93'", "'.\u7A0B\u5E8F\u96C6'", 
  "'.\u7A0B\u5E8F\u96C6\u53D8\u91CF'", "'.\u5C40\u90E8\u53D8\u91CF'", "'.\u5168\u5C40\u53D8\u91CF'", 
  "'.\u0044\u004C\u004C\u547D\u4EE4'", "'.\u6210\u5458'", "'.\u53C2\u6570'", 
  "'.\u5B50\u7A0B\u5E8F'", "'.\u6570\u636E\u7C7B\u578B'", "'.\u5982\u679C\u771F'", 
  "'.\u5982\u679C\u771F\u7ED3\u675F'", "'.\u5982\u679C'", "'.\u5426\u5219'", 
  "'.\u5982\u679C\u7ED3\u675F'", "'.\u5224\u65AD\u5FAA\u73AF\u9996'", "'.\u5224\u65AD\u5FAA\u73AF\u5C3E'", 
  "'.\u8BA1\u6B21\u5FAA\u73AF\u9996'", "'.\u8BA1\u6B21\u5FAA\u73AF\u5C3E'", 
  "'\u771F'", "'\u5047'", "", "", "", "", "", "", "'\uFF1D'", "'='", "'=='", 
  "", "", "", "", "", "", "", "", "", "'('", "')'", "'['", "']'", "'#'", 
  "'&'", "'\"'", "'.'"
};

std::vector<std::string> openeParser::_symbolicNames = {
  "", "K_VERSION", "K_LIBRARY", "K_PROGRAM_SET", "K_PROGRAM_SET_VARIABLE", 
  "K_LOCAL_VARIABLE", "K_GLOBAL_VARIABLE", "K_DLL_DEFINE", "K_MEMBER_VARIABLE", 
  "K_PARAMETER", "K_SUB_PROGRAM", "K_STRUCTURE", "K_IF_TRUE", "K_END_IF_TRUE", 
  "K_IF", "K_ELSE", "K_END_IF", "K_WHILE", "K_WHILE_END", "K_FOR", "K_FOR_END", 
  "K_TRUE", "K_FALSE", "K_ADD_OPT", "K_SUB_OPT", "K_MUL_OPT", "K_DIV_OPT", 
  "K_FULL_DIV_OPT", "K_MOD_OPT", "K_AECOM_OPT", "K_ASSIGN_OPT", "K_EQUAL_OPT", 
  "K_NOT_EQUAL_OPT", "K_GREAT_OPT", "K_LESS_OPT", "K_GREAT_EQU_OPT", "K_LESS_EQU_OPT", 
  "K_LIKE_EQU_OPT", "K_OR_OPT", "K_AND_OPT", "COMMA", "LBRACK", "RBRACK", 
  "LSQUBRACK", "RSQUBRACK", "SHARP", "ADDRESS", "DQUOTE", "DOT", "INTEGER_LITERAL", 
  "FLOAT_LITERAL", "IDENTIFIER", "WHITESPACE", "NEWLINE", "STRING_LITERAL", 
  "OTHER_CHAR", "TABLE_END", "TABLE_ITEM", "TABLE_WS", "TABLE_COMMA"
};

dfa::Vocabulary openeParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> openeParser::_tokenNames;

openeParser::Initializer::Initializer() {
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
    0x3, 0x3d, 0x229, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
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
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x62, 0xa, 0x3, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x7, 0x5, 0x68, 0xa, 0x5, 0xc, 0x5, 0xe, 
    0x5, 0x6b, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x7, 0x7, 0x70, 0xa, 
    0x7, 0xc, 0x7, 0xe, 0x7, 0x73, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x5, 0x8, 0x79, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x7d, 
    0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x83, 0xa, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x87, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 
    0x8a, 0xb, 0x8, 0x3, 0x8, 0x7, 0x8, 0x8d, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 
    0x90, 0xb, 0x8, 0x3, 0x9, 0x7, 0x9, 0x93, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 
    0x96, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x9c, 
    0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0xa0, 0xa, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x5, 0xa, 0xa4, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0xa8, 0xa, 
    0xa, 0x5, 0xa, 0xaa, 0xa, 0xa, 0x5, 0xa, 0xac, 0xa, 0xa, 0x5, 0xa, 0xae, 
    0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0xb9, 0xa, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x5, 0xc, 0xbd, 0xa, 0xc, 0x5, 0xc, 0xbf, 0xa, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x7, 0xc, 0xc4, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0xc7, 0xb, 
    0xc, 0x3, 0xd, 0x7, 0xd, 0xca, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xcd, 0xb, 
    0xd, 0x3, 0xe, 0x7, 0xe, 0xd0, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0xd3, 0xb, 
    0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x7, 0x10, 0xd9, 0xa, 
    0x10, 0xc, 0x10, 0xe, 0x10, 0xdc, 0xb, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 
    0xe6, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xea, 0xa, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x5, 0x12, 0xee, 0xa, 0x12, 0x5, 0x12, 0xf0, 0xa, 0x12, 
    0x5, 0x12, 0xf2, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x13, 0x7, 0x13, 0xf9, 0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 0xfc, 0xb, 
    0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x5, 0x15, 0x104, 0xa, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 
    0x109, 0xa, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x10d, 0xa, 0x15, 
    0x5, 0x15, 0x10f, 0xa, 0x15, 0x5, 0x15, 0x111, 0xa, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x16, 0x7, 0x16, 0x116, 0xa, 0x16, 0xc, 0x16, 0xe, 0x16, 
    0x119, 0xb, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x7, 
    0x1b, 0x126, 0xa, 0x1b, 0xc, 0x1b, 0xe, 0x1b, 0x129, 0xb, 0x1b, 0x3, 
    0x1b, 0x3, 0x1b, 0x7, 0x1b, 0x12d, 0xa, 0x1b, 0xc, 0x1b, 0xe, 0x1b, 
    0x130, 0xb, 0x1b, 0x7, 0x1b, 0x132, 0xa, 0x1b, 0xc, 0x1b, 0xe, 0x1b, 
    0x135, 0xb, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 
    0x13b, 0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x13f, 0xa, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x143, 0xa, 0x1c, 0x5, 0x1c, 0x145, 
    0xa, 0x1c, 0x5, 0x1c, 0x147, 0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x7, 0x1c, 0x14c, 0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 0x14f, 0xb, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x7, 0x1d, 0x154, 0xa, 0x1d, 0xc, 0x1d, 
    0xe, 0x1d, 0x157, 0xb, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 0x15f, 0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 
    0x162, 0xb, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x166, 0xa, 0x1e, 
    0x5, 0x1e, 0x168, 0xa, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 
    0x3, 0x1f, 0x3, 0x20, 0x5, 0x20, 0x170, 0xa, 0x20, 0x3, 0x20, 0x7, 0x20, 
    0x173, 0xa, 0x20, 0xc, 0x20, 0xe, 0x20, 0x176, 0xb, 0x20, 0x3, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 
    0x21, 0x17f, 0xa, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 
    0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x18f, 0xa, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 
    0x22, 0x197, 0xa, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 0x19f, 0xa, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x5, 0x23, 0x1aa, 0xa, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 
    0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x7, 0x25, 0x1b2, 0xa, 0x25, 0xc, 0x25, 
    0xe, 0x25, 0x1b5, 0xb, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 
    0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 
    0x26, 0x5, 0x26, 0x1c2, 0xa, 0x26, 0x7, 0x26, 0x1c4, 0xa, 0x26, 0xc, 
    0x26, 0xe, 0x26, 0x1c7, 0xb, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 
    0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x7, 0x26, 0x1d0, 0xa, 0x26, 
    0xc, 0x26, 0xe, 0x26, 0x1d3, 0xb, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 
    0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x1e2, 0xa, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 
    0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 
    0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 
    0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 
    0x27, 0x3, 0x27, 0x3, 0x27, 0x7, 0x27, 0x214, 0xa, 0x27, 0xc, 0x27, 
    0xe, 0x27, 0x217, 0xb, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x29, 
    0x3, 0x29, 0x3, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x221, 0xa, 0x2a, 
    0x3, 0x2b, 0x3, 0x2b, 0x5, 0x2b, 0x225, 0xa, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 
    0x3, 0x2c, 0x2, 0x4, 0x4a, 0x4c, 0x2d, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
    0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 
    0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 
    0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 
    0x56, 0x2, 0x5, 0x4, 0x2, 0x3b, 0x3b, 0x3d, 0x3d, 0x5, 0x2, 0x2a, 0x2a, 
    0x35, 0x35, 0x39, 0x39, 0x3, 0x2, 0x1f, 0x20, 0x2, 0x257, 0x2, 0x58, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x61, 0x3, 0x2, 0x2, 0x2, 0x6, 0x63, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x69, 0x3, 0x2, 0x2, 0x2, 0xa, 0x6c, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x71, 0x3, 0x2, 0x2, 0x2, 0xe, 0x74, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0x94, 0x3, 0x2, 0x2, 0x2, 0x12, 0x97, 0x3, 0x2, 0x2, 0x2, 0x14, 0xb1, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0xb4, 0x3, 0x2, 0x2, 0x2, 0x18, 0xcb, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0xd1, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xd4, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0xda, 0x3, 0x2, 0x2, 0x2, 0x20, 0xdd, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0xe1, 0x3, 0x2, 0x2, 0x2, 0x24, 0xfa, 0x3, 0x2, 0x2, 0x2, 
    0x26, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x28, 0x100, 0x3, 0x2, 0x2, 0x2, 0x2a, 
    0x117, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x11c, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x32, 0x120, 0x3, 
    0x2, 0x2, 0x2, 0x34, 0x133, 0x3, 0x2, 0x2, 0x2, 0x36, 0x136, 0x3, 0x2, 
    0x2, 0x2, 0x38, 0x155, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x158, 0x3, 0x2, 0x2, 
    0x2, 0x3c, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x174, 0x3, 0x2, 0x2, 0x2, 
    0x40, 0x17e, 0x3, 0x2, 0x2, 0x2, 0x42, 0x196, 0x3, 0x2, 0x2, 0x2, 0x44, 
    0x1a9, 0x3, 0x2, 0x2, 0x2, 0x46, 0x1ab, 0x3, 0x2, 0x2, 0x2, 0x48, 0x1ae, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x1b6, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x1e1, 0x3, 
    0x2, 0x2, 0x2, 0x4e, 0x218, 0x3, 0x2, 0x2, 0x2, 0x50, 0x21b, 0x3, 0x2, 
    0x2, 0x2, 0x52, 0x220, 0x3, 0x2, 0x2, 0x2, 0x54, 0x224, 0x3, 0x2, 0x2, 
    0x2, 0x56, 0x226, 0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x5, 0x14, 0xb, 0x2, 
    0x59, 0x5a, 0x7, 0x37, 0x2, 0x2, 0x5a, 0x5b, 0x5, 0x4, 0x3, 0x2, 0x5b, 
    0x5c, 0x7, 0x2, 0x2, 0x3, 0x5c, 0x3, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x62, 
    0x5, 0x6, 0x4, 0x2, 0x5e, 0x62, 0x5, 0x8, 0x5, 0x2, 0x5f, 0x62, 0x5, 
    0xa, 0x6, 0x2, 0x60, 0x62, 0x5, 0xc, 0x7, 0x2, 0x61, 0x5d, 0x3, 0x2, 
    0x2, 0x2, 0x61, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x61, 0x5f, 0x3, 0x2, 0x2, 
    0x2, 0x61, 0x60, 0x3, 0x2, 0x2, 0x2, 0x62, 0x5, 0x3, 0x2, 0x2, 0x2, 
    0x63, 0x64, 0x5, 0x1e, 0x10, 0x2, 0x64, 0x65, 0x5, 0x22, 0x12, 0x2, 
    0x65, 0x7, 0x3, 0x2, 0x2, 0x2, 0x66, 0x68, 0x5, 0x16, 0xc, 0x2, 0x67, 
    0x66, 0x3, 0x2, 0x2, 0x2, 0x68, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x69, 0x67, 
    0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x6b, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x5, 0x10, 
    0x9, 0x2, 0x6d, 0xb, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x70, 0x5, 0xe, 0x8, 
    0x2, 0x6f, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x70, 0x73, 0x3, 0x2, 0x2, 0x2, 
    0x71, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x3, 0x2, 0x2, 0x2, 0x72, 
    0xd, 0x3, 0x2, 0x2, 0x2, 0x73, 0x71, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 
    0x7, 0x9, 0x2, 0x2, 0x75, 0x76, 0x7, 0x3b, 0x2, 0x2, 0x76, 0x78, 0x7, 
    0x3d, 0x2, 0x2, 0x77, 0x79, 0x7, 0x3b, 0x2, 0x2, 0x78, 0x77, 0x3, 0x2, 
    0x2, 0x2, 0x78, 0x79, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 
    0x2, 0x7a, 0x7c, 0x7, 0x3d, 0x2, 0x2, 0x7b, 0x7d, 0x7, 0x3b, 0x2, 0x2, 
    0x7c, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x7d, 
    0x7e, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 0x7, 0x3d, 0x2, 0x2, 0x7f, 0x82, 
    0x7, 0x3b, 0x2, 0x2, 0x80, 0x81, 0x7, 0x3d, 0x2, 0x2, 0x81, 0x83, 0x5, 
    0x18, 0xd, 0x2, 0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x3, 0x2, 
    0x2, 0x2, 0x83, 0x84, 0x3, 0x2, 0x2, 0x2, 0x84, 0x88, 0x7, 0x3a, 0x2, 
    0x2, 0x85, 0x87, 0x5, 0x3a, 0x1e, 0x2, 0x86, 0x85, 0x3, 0x2, 0x2, 0x2, 
    0x87, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x88, 0x86, 0x3, 0x2, 0x2, 0x2, 0x88, 
    0x89, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x88, 
    0x3, 0x2, 0x2, 0x2, 0x8b, 0x8d, 0x7, 0x37, 0x2, 0x2, 0x8c, 0x8b, 0x3, 
    0x2, 0x2, 0x2, 0x8d, 0x90, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8c, 0x3, 0x2, 
    0x2, 0x2, 0x8e, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x8f, 0xf, 0x3, 0x2, 0x2, 
    0x2, 0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x91, 0x93, 0x5, 0x12, 0xa, 0x2, 
    0x92, 0x91, 0x3, 0x2, 0x2, 0x2, 0x93, 0x96, 0x3, 0x2, 0x2, 0x2, 0x94, 
    0x92, 0x3, 0x2, 0x2, 0x2, 0x94, 0x95, 0x3, 0x2, 0x2, 0x2, 0x95, 0x11, 
    0x3, 0x2, 0x2, 0x2, 0x96, 0x94, 0x3, 0x2, 0x2, 0x2, 0x97, 0x98, 0x7, 
    0x8, 0x2, 0x2, 0x98, 0xad, 0x7, 0x3b, 0x2, 0x2, 0x99, 0x9b, 0x7, 0x3d, 
    0x2, 0x2, 0x9a, 0x9c, 0x7, 0x3b, 0x2, 0x2, 0x9b, 0x9a, 0x3, 0x2, 0x2, 
    0x2, 0x9b, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x9c, 0xab, 0x3, 0x2, 0x2, 0x2, 
    0x9d, 0x9f, 0x7, 0x3d, 0x2, 0x2, 0x9e, 0xa0, 0x7, 0x3b, 0x2, 0x2, 0x9f, 
    0x9e, 0x3, 0x2, 0x2, 0x2, 0x9f, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa9, 
    0x3, 0x2, 0x2, 0x2, 0xa1, 0xa3, 0x7, 0x3d, 0x2, 0x2, 0xa2, 0xa4, 0x7, 
    0x3b, 0x2, 0x2, 0xa3, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa4, 0x3, 0x2, 
    0x2, 0x2, 0xa4, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa6, 0x7, 0x3d, 0x2, 
    0x2, 0xa6, 0xa8, 0x5, 0x18, 0xd, 0x2, 0xa7, 0xa5, 0x3, 0x2, 0x2, 0x2, 
    0xa7, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xa9, 
    0xa1, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xac, 
    0x3, 0x2, 0x2, 0x2, 0xab, 0x9d, 0x3, 0x2, 0x2, 0x2, 0xab, 0xac, 0x3, 
    0x2, 0x2, 0x2, 0xac, 0xae, 0x3, 0x2, 0x2, 0x2, 0xad, 0x99, 0x3, 0x2, 
    0x2, 0x2, 0xad, 0xae, 0x3, 0x2, 0x2, 0x2, 0xae, 0xaf, 0x3, 0x2, 0x2, 
    0x2, 0xaf, 0xb0, 0x7, 0x3a, 0x2, 0x2, 0xb0, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0xb1, 0xb2, 0x7, 0x3, 0x2, 0x2, 0xb2, 0xb3, 0x7, 0x33, 0x2, 0x2, 0xb3, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xb5, 0x7, 0xd, 0x2, 0x2, 0xb5, 0xbe, 
    0x7, 0x3b, 0x2, 0x2, 0xb6, 0xb8, 0x7, 0x3d, 0x2, 0x2, 0xb7, 0xb9, 0x7, 
    0x3b, 0x2, 0x2, 0xb8, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb9, 0x3, 0x2, 
    0x2, 0x2, 0xb9, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 0x7, 0x3d, 0x2, 
    0x2, 0xbb, 0xbd, 0x5, 0x18, 0xd, 0x2, 0xbc, 0xba, 0x3, 0x2, 0x2, 0x2, 
    0xbc, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbe, 
    0xb6, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc0, 
    0x3, 0x2, 0x2, 0x2, 0xc0, 0xc1, 0x7, 0x3a, 0x2, 0x2, 0xc1, 0xc5, 0x5, 
    0x1a, 0xe, 0x2, 0xc2, 0xc4, 0x7, 0x37, 0x2, 0x2, 0xc3, 0xc2, 0x3, 0x2, 
    0x2, 0x2, 0xc4, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc3, 0x3, 0x2, 0x2, 
    0x2, 0xc5, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc6, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0xc7, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xca, 0x9, 0x2, 0x2, 0x2, 0xc9, 
    0xc8, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xc9, 
    0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xcc, 0x19, 0x3, 
    0x2, 0x2, 0x2, 0xcd, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xce, 0xd0, 0x5, 0x1c, 
    0xf, 0x2, 0xcf, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xd3, 0x3, 0x2, 0x2, 
    0x2, 0xd1, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd2, 0x3, 0x2, 0x2, 0x2, 
    0xd2, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd4, 
    0xd5, 0x7, 0xa, 0x2, 0x2, 0xd5, 0xd6, 0x5, 0x28, 0x15, 0x2, 0xd6, 0x1d, 
    0x3, 0x2, 0x2, 0x2, 0xd7, 0xd9, 0x5, 0x20, 0x11, 0x2, 0xd8, 0xd7, 0x3, 
    0x2, 0x2, 0x2, 0xd9, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xda, 0xd8, 0x3, 0x2, 
    0x2, 0x2, 0xda, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdb, 0x1f, 0x3, 0x2, 0x2, 
    0x2, 0xdc, 0xda, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xde, 0x7, 0x4, 0x2, 0x2, 
    0xde, 0xdf, 0x7, 0x35, 0x2, 0x2, 0xdf, 0xe0, 0x7, 0x37, 0x2, 0x2, 0xe0, 
    0x21, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe2, 0x7, 0x5, 0x2, 0x2, 0xe2, 0xf1, 
    0x7, 0x3b, 0x2, 0x2, 0xe3, 0xe5, 0x7, 0x3d, 0x2, 0x2, 0xe4, 0xe6, 0x7, 
    0x3b, 0x2, 0x2, 0xe5, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe6, 0x3, 0x2, 
    0x2, 0x2, 0xe6, 0xef, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe9, 0x7, 0x3d, 0x2, 
    0x2, 0xe8, 0xea, 0x7, 0x3b, 0x2, 0x2, 0xe9, 0xe8, 0x3, 0x2, 0x2, 0x2, 
    0xe9, 0xea, 0x3, 0x2, 0x2, 0x2, 0xea, 0xed, 0x3, 0x2, 0x2, 0x2, 0xeb, 
    0xec, 0x7, 0x3d, 0x2, 0x2, 0xec, 0xee, 0x5, 0x18, 0xd, 0x2, 0xed, 0xeb, 
    0x3, 0x2, 0x2, 0x2, 0xed, 0xee, 0x3, 0x2, 0x2, 0x2, 0xee, 0xf0, 0x3, 
    0x2, 0x2, 0x2, 0xef, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xef, 0xf0, 0x3, 0x2, 
    0x2, 0x2, 0xf0, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xe3, 0x3, 0x2, 0x2, 
    0x2, 0xf1, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf3, 0x3, 0x2, 0x2, 0x2, 
    0xf3, 0xf4, 0x7, 0x3a, 0x2, 0x2, 0xf4, 0xf5, 0x5, 0x24, 0x13, 0x2, 0xf5, 
    0xf6, 0x5, 0x34, 0x1b, 0x2, 0xf6, 0x23, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf9, 
    0x5, 0x26, 0x14, 0x2, 0xf8, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xfc, 0x3, 
    0x2, 0x2, 0x2, 0xfa, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfb, 0x3, 0x2, 
    0x2, 0x2, 0xfb, 0x25, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xfa, 0x3, 0x2, 0x2, 
    0x2, 0xfd, 0xfe, 0x7, 0x6, 0x2, 0x2, 0xfe, 0xff, 0x5, 0x28, 0x15, 0x2, 
    0xff, 0x27, 0x3, 0x2, 0x2, 0x2, 0x100, 0x110, 0x7, 0x3b, 0x2, 0x2, 0x101, 
    0x103, 0x7, 0x3d, 0x2, 0x2, 0x102, 0x104, 0x7, 0x3b, 0x2, 0x2, 0x103, 
    0x102, 0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 0x3, 0x2, 0x2, 0x2, 0x104, 
    0x10e, 0x3, 0x2, 0x2, 0x2, 0x105, 0x106, 0x7, 0x3d, 0x2, 0x2, 0x106, 
    0x108, 0x7, 0x3d, 0x2, 0x2, 0x107, 0x109, 0x7, 0x3b, 0x2, 0x2, 0x108, 
    0x107, 0x3, 0x2, 0x2, 0x2, 0x108, 0x109, 0x3, 0x2, 0x2, 0x2, 0x109, 
    0x10c, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10b, 0x7, 0x3d, 0x2, 0x2, 0x10b, 
    0x10d, 0x5, 0x18, 0xd, 0x2, 0x10c, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x10c, 
    0x10d, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x10e, 
    0x105, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x10f, 
    0x111, 0x3, 0x2, 0x2, 0x2, 0x110, 0x101, 0x3, 0x2, 0x2, 0x2, 0x110, 
    0x111, 0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 0x3, 0x2, 0x2, 0x2, 0x112, 
    0x113, 0x7, 0x3a, 0x2, 0x2, 0x113, 0x29, 0x3, 0x2, 0x2, 0x2, 0x114, 
    0x116, 0x5, 0x2c, 0x17, 0x2, 0x115, 0x114, 0x3, 0x2, 0x2, 0x2, 0x116, 
    0x119, 0x3, 0x2, 0x2, 0x2, 0x117, 0x115, 0x3, 0x2, 0x2, 0x2, 0x117, 
    0x118, 0x3, 0x2, 0x2, 0x2, 0x118, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x119, 0x117, 
    0x3, 0x2, 0x2, 0x2, 0x11a, 0x11b, 0x9, 0x3, 0x2, 0x2, 0x11b, 0x2d, 0x3, 
    0x2, 0x2, 0x2, 0x11c, 0x11d, 0x7, 0x35, 0x2, 0x2, 0x11d, 0x2f, 0x3, 
    0x2, 0x2, 0x2, 0x11e, 0x11f, 0x7, 0x35, 0x2, 0x2, 0x11f, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0x120, 0x121, 0x7, 0x31, 0x2, 0x2, 0x121, 0x122, 0x7, 
    0x33, 0x2, 0x2, 0x122, 0x123, 0x7, 0x31, 0x2, 0x2, 0x123, 0x33, 0x3, 
    0x2, 0x2, 0x2, 0x124, 0x126, 0x7, 0x37, 0x2, 0x2, 0x125, 0x124, 0x3, 
    0x2, 0x2, 0x2, 0x126, 0x129, 0x3, 0x2, 0x2, 0x2, 0x127, 0x125, 0x3, 
    0x2, 0x2, 0x2, 0x127, 0x128, 0x3, 0x2, 0x2, 0x2, 0x128, 0x12a, 0x3, 
    0x2, 0x2, 0x2, 0x129, 0x127, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12e, 0x5, 
    0x36, 0x1c, 0x2, 0x12b, 0x12d, 0x7, 0x37, 0x2, 0x2, 0x12c, 0x12b, 0x3, 
    0x2, 0x2, 0x2, 0x12d, 0x130, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x12c, 0x3, 
    0x2, 0x2, 0x2, 0x12e, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x132, 0x3, 
    0x2, 0x2, 0x2, 0x130, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x131, 0x127, 0x3, 
    0x2, 0x2, 0x2, 0x132, 0x135, 0x3, 0x2, 0x2, 0x2, 0x133, 0x131, 0x3, 
    0x2, 0x2, 0x2, 0x133, 0x134, 0x3, 0x2, 0x2, 0x2, 0x134, 0x35, 0x3, 0x2, 
    0x2, 0x2, 0x135, 0x133, 0x3, 0x2, 0x2, 0x2, 0x136, 0x137, 0x7, 0xc, 
    0x2, 0x2, 0x137, 0x146, 0x7, 0x3b, 0x2, 0x2, 0x138, 0x13a, 0x7, 0x3d, 
    0x2, 0x2, 0x139, 0x13b, 0x7, 0x3b, 0x2, 0x2, 0x13a, 0x139, 0x3, 0x2, 
    0x2, 0x2, 0x13a, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x144, 0x3, 0x2, 
    0x2, 0x2, 0x13c, 0x13e, 0x7, 0x3d, 0x2, 0x2, 0x13d, 0x13f, 0x7, 0x3b, 
    0x2, 0x2, 0x13e, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13e, 0x13f, 0x3, 0x2, 
    0x2, 0x2, 0x13f, 0x142, 0x3, 0x2, 0x2, 0x2, 0x140, 0x141, 0x7, 0x3d, 
    0x2, 0x2, 0x141, 0x143, 0x5, 0x18, 0xd, 0x2, 0x142, 0x140, 0x3, 0x2, 
    0x2, 0x2, 0x142, 0x143, 0x3, 0x2, 0x2, 0x2, 0x143, 0x145, 0x3, 0x2, 
    0x2, 0x2, 0x144, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x144, 0x145, 0x3, 0x2, 
    0x2, 0x2, 0x145, 0x147, 0x3, 0x2, 0x2, 0x2, 0x146, 0x138, 0x3, 0x2, 
    0x2, 0x2, 0x146, 0x147, 0x3, 0x2, 0x2, 0x2, 0x147, 0x148, 0x3, 0x2, 
    0x2, 0x2, 0x148, 0x149, 0x7, 0x3a, 0x2, 0x2, 0x149, 0x14d, 0x5, 0x38, 
    0x1d, 0x2, 0x14a, 0x14c, 0x5, 0x3c, 0x1f, 0x2, 0x14b, 0x14a, 0x3, 0x2, 
    0x2, 0x2, 0x14c, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x14b, 0x3, 0x2, 
    0x2, 0x2, 0x14d, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x150, 0x3, 0x2, 
    0x2, 0x2, 0x14f, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x150, 0x151, 0x5, 0x3e, 
    0x20, 0x2, 0x151, 0x37, 0x3, 0x2, 0x2, 0x2, 0x152, 0x154, 0x5, 0x3a, 
    0x1e, 0x2, 0x153, 0x152, 0x3, 0x2, 0x2, 0x2, 0x154, 0x157, 0x3, 0x2, 
    0x2, 0x2, 0x155, 0x153, 0x3, 0x2, 0x2, 0x2, 0x155, 0x156, 0x3, 0x2, 
    0x2, 0x2, 0x156, 0x39, 0x3, 0x2, 0x2, 0x2, 0x157, 0x155, 0x3, 0x2, 0x2, 
    0x2, 0x158, 0x159, 0x7, 0xb, 0x2, 0x2, 0x159, 0x15a, 0x7, 0x3b, 0x2, 
    0x2, 0x15a, 0x15b, 0x7, 0x3d, 0x2, 0x2, 0x15b, 0x167, 0x7, 0x3b, 0x2, 
    0x2, 0x15c, 0x160, 0x7, 0x3d, 0x2, 0x2, 0x15d, 0x15f, 0x7, 0x3b, 0x2, 
    0x2, 0x15e, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x162, 0x3, 0x2, 0x2, 
    0x2, 0x160, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x160, 0x161, 0x3, 0x2, 0x2, 
    0x2, 0x161, 0x165, 0x3, 0x2, 0x2, 0x2, 0x162, 0x160, 0x3, 0x2, 0x2, 
    0x2, 0x163, 0x164, 0x7, 0x3d, 0x2, 0x2, 0x164, 0x166, 0x5, 0x18, 0xd, 
    0x2, 0x165, 0x163, 0x3, 0x2, 0x2, 0x2, 0x165, 0x166, 0x3, 0x2, 0x2, 
    0x2, 0x166, 0x168, 0x3, 0x2, 0x2, 0x2, 0x167, 0x15c, 0x3, 0x2, 0x2, 
    0x2, 0x167, 0x168, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 0x3, 0x2, 0x2, 
    0x2, 0x169, 0x16a, 0x7, 0x3a, 0x2, 0x2, 0x16a, 0x3b, 0x3, 0x2, 0x2, 
    0x2, 0x16b, 0x16c, 0x7, 0x7, 0x2, 0x2, 0x16c, 0x16d, 0x5, 0x28, 0x15, 
    0x2, 0x16d, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x170, 0x5, 0x40, 0x21, 
    0x2, 0x16f, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x170, 0x3, 0x2, 0x2, 
    0x2, 0x170, 0x171, 0x3, 0x2, 0x2, 0x2, 0x171, 0x173, 0x7, 0x37, 0x2, 
    0x2, 0x172, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x173, 0x176, 0x3, 0x2, 0x2, 
    0x2, 0x174, 0x172, 0x3, 0x2, 0x2, 0x2, 0x174, 0x175, 0x3, 0x2, 0x2, 
    0x2, 0x175, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x176, 0x174, 0x3, 0x2, 0x2, 0x2, 
    0x177, 0x17f, 0x5, 0x44, 0x23, 0x2, 0x178, 0x179, 0x5, 0x48, 0x25, 0x2, 
    0x179, 0x17a, 0x9, 0x4, 0x2, 0x2, 0x17a, 0x17b, 0x5, 0x4c, 0x27, 0x2, 
    0x17b, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x17c, 0x17f, 0x5, 0x4c, 0x27, 0x2, 
    0x17d, 0x17f, 0x5, 0x42, 0x22, 0x2, 0x17e, 0x177, 0x3, 0x2, 0x2, 0x2, 
    0x17e, 0x178, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x17c, 0x3, 0x2, 0x2, 0x2, 
    0x17e, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x41, 0x3, 0x2, 0x2, 0x2, 0x180, 
    0x181, 0x7, 0x13, 0x2, 0x2, 0x181, 0x182, 0x7, 0x2b, 0x2, 0x2, 0x182, 
    0x183, 0x5, 0x4c, 0x27, 0x2, 0x183, 0x184, 0x7, 0x2c, 0x2, 0x2, 0x184, 
    0x185, 0x5, 0x3e, 0x20, 0x2, 0x185, 0x186, 0x7, 0x14, 0x2, 0x2, 0x186, 
    0x187, 0x7, 0x2b, 0x2, 0x2, 0x187, 0x188, 0x7, 0x2c, 0x2, 0x2, 0x188, 
    0x197, 0x3, 0x2, 0x2, 0x2, 0x189, 0x18a, 0x7, 0x15, 0x2, 0x2, 0x18a, 
    0x18b, 0x7, 0x2b, 0x2, 0x2, 0x18b, 0x18c, 0x5, 0x4c, 0x27, 0x2, 0x18c, 
    0x18e, 0x7, 0x2a, 0x2, 0x2, 0x18d, 0x18f, 0x7, 0x35, 0x2, 0x2, 0x18e, 
    0x18d, 0x3, 0x2, 0x2, 0x2, 0x18e, 0x18f, 0x3, 0x2, 0x2, 0x2, 0x18f, 
    0x190, 0x3, 0x2, 0x2, 0x2, 0x190, 0x191, 0x7, 0x2c, 0x2, 0x2, 0x191, 
    0x192, 0x5, 0x3e, 0x20, 0x2, 0x192, 0x193, 0x7, 0x16, 0x2, 0x2, 0x193, 
    0x194, 0x7, 0x2b, 0x2, 0x2, 0x194, 0x195, 0x7, 0x2c, 0x2, 0x2, 0x195, 
    0x197, 0x3, 0x2, 0x2, 0x2, 0x196, 0x180, 0x3, 0x2, 0x2, 0x2, 0x196, 
    0x189, 0x3, 0x2, 0x2, 0x2, 0x197, 0x43, 0x3, 0x2, 0x2, 0x2, 0x198, 0x199, 
    0x7, 0x10, 0x2, 0x2, 0x199, 0x19a, 0x7, 0x2b, 0x2, 0x2, 0x19a, 0x19b, 
    0x5, 0x4c, 0x27, 0x2, 0x19b, 0x19c, 0x7, 0x2c, 0x2, 0x2, 0x19c, 0x19e, 
    0x5, 0x3e, 0x20, 0x2, 0x19d, 0x19f, 0x5, 0x46, 0x24, 0x2, 0x19e, 0x19d, 
    0x3, 0x2, 0x2, 0x2, 0x19e, 0x19f, 0x3, 0x2, 0x2, 0x2, 0x19f, 0x1a0, 
    0x3, 0x2, 0x2, 0x2, 0x1a0, 0x1a1, 0x7, 0x12, 0x2, 0x2, 0x1a1, 0x1aa, 
    0x3, 0x2, 0x2, 0x2, 0x1a2, 0x1a3, 0x7, 0xe, 0x2, 0x2, 0x1a3, 0x1a4, 
    0x7, 0x2b, 0x2, 0x2, 0x1a4, 0x1a5, 0x5, 0x4c, 0x27, 0x2, 0x1a5, 0x1a6, 
    0x7, 0x2c, 0x2, 0x2, 0x1a6, 0x1a7, 0x5, 0x3e, 0x20, 0x2, 0x1a7, 0x1a8, 
    0x7, 0xf, 0x2, 0x2, 0x1a8, 0x1aa, 0x3, 0x2, 0x2, 0x2, 0x1a9, 0x198, 
    0x3, 0x2, 0x2, 0x2, 0x1a9, 0x1a2, 0x3, 0x2, 0x2, 0x2, 0x1aa, 0x45, 0x3, 
    0x2, 0x2, 0x2, 0x1ab, 0x1ac, 0x7, 0x11, 0x2, 0x2, 0x1ac, 0x1ad, 0x5, 
    0x3e, 0x20, 0x2, 0x1ad, 0x47, 0x3, 0x2, 0x2, 0x2, 0x1ae, 0x1b3, 0x5, 
    0x4a, 0x26, 0x2, 0x1af, 0x1b0, 0x7, 0x32, 0x2, 0x2, 0x1b0, 0x1b2, 0x5, 
    0x4a, 0x26, 0x2, 0x1b1, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1b5, 0x3, 
    0x2, 0x2, 0x2, 0x1b3, 0x1b1, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1b4, 0x3, 
    0x2, 0x2, 0x2, 0x1b4, 0x49, 0x3, 0x2, 0x2, 0x2, 0x1b5, 0x1b3, 0x3, 0x2, 
    0x2, 0x2, 0x1b6, 0x1b7, 0x8, 0x26, 0x1, 0x2, 0x1b7, 0x1b8, 0x7, 0x35, 
    0x2, 0x2, 0x1b8, 0x1d1, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x1ba, 0xc, 0x5, 
    0x2, 0x2, 0x1ba, 0x1bb, 0x7, 0x2b, 0x2, 0x2, 0x1bb, 0x1d0, 0x7, 0x2c, 
    0x2, 0x2, 0x1bc, 0x1bd, 0xc, 0x4, 0x2, 0x2, 0x1bd, 0x1be, 0x7, 0x2b, 
    0x2, 0x2, 0x1be, 0x1c5, 0x5, 0x4c, 0x27, 0x2, 0x1bf, 0x1c1, 0x7, 0x2a, 
    0x2, 0x2, 0x1c0, 0x1c2, 0x5, 0x4c, 0x27, 0x2, 0x1c1, 0x1c0, 0x3, 0x2, 
    0x2, 0x2, 0x1c1, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c2, 0x1c4, 0x3, 0x2, 
    0x2, 0x2, 0x1c3, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1c4, 0x1c7, 0x3, 0x2, 
    0x2, 0x2, 0x1c5, 0x1c3, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1c6, 0x3, 0x2, 
    0x2, 0x2, 0x1c6, 0x1c8, 0x3, 0x2, 0x2, 0x2, 0x1c7, 0x1c5, 0x3, 0x2, 
    0x2, 0x2, 0x1c8, 0x1c9, 0x7, 0x2c, 0x2, 0x2, 0x1c9, 0x1d0, 0x3, 0x2, 
    0x2, 0x2, 0x1ca, 0x1cb, 0xc, 0x3, 0x2, 0x2, 0x1cb, 0x1cc, 0x7, 0x2d, 
    0x2, 0x2, 0x1cc, 0x1cd, 0x5, 0x4c, 0x27, 0x2, 0x1cd, 0x1ce, 0x7, 0x2e, 
    0x2, 0x2, 0x1ce, 0x1d0, 0x3, 0x2, 0x2, 0x2, 0x1cf, 0x1b9, 0x3, 0x2, 
    0x2, 0x2, 0x1cf, 0x1bc, 0x3, 0x2, 0x2, 0x2, 0x1cf, 0x1ca, 0x3, 0x2, 
    0x2, 0x2, 0x1d0, 0x1d3, 0x3, 0x2, 0x2, 0x2, 0x1d1, 0x1cf, 0x3, 0x2, 
    0x2, 0x2, 0x1d1, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x1d2, 0x4b, 0x3, 0x2, 0x2, 
    0x2, 0x1d3, 0x1d1, 0x3, 0x2, 0x2, 0x2, 0x1d4, 0x1d5, 0x8, 0x27, 0x1, 
    0x2, 0x1d5, 0x1d6, 0x7, 0x2b, 0x2, 0x2, 0x1d6, 0x1d7, 0x5, 0x4c, 0x27, 
    0x2, 0x1d7, 0x1d8, 0x7, 0x2c, 0x2, 0x2, 0x1d8, 0x1e2, 0x3, 0x2, 0x2, 
    0x2, 0x1d9, 0x1da, 0x7, 0x1a, 0x2, 0x2, 0x1da, 0x1e2, 0x5, 0x4c, 0x27, 
    0x19, 0x1db, 0x1e2, 0x5, 0x54, 0x2b, 0x2, 0x1dc, 0x1e2, 0x5, 0x52, 0x2a, 
    0x2, 0x1dd, 0x1e2, 0x5, 0x4e, 0x28, 0x2, 0x1de, 0x1e2, 0x5, 0x56, 0x2c, 
    0x2, 0x1df, 0x1e2, 0x5, 0x48, 0x25, 0x2, 0x1e0, 0x1e2, 0x5, 0x50, 0x29, 
    0x2, 0x1e1, 0x1d4, 0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1d9, 0x3, 0x2, 0x2, 
    0x2, 0x1e1, 0x1db, 0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1dc, 0x3, 0x2, 0x2, 
    0x2, 0x1e1, 0x1dd, 0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1de, 0x3, 0x2, 0x2, 
    0x2, 0x1e1, 0x1df, 0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1e0, 0x3, 0x2, 0x2, 
    0x2, 0x1e2, 0x215, 0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e4, 0xc, 0x18, 0x2, 
    0x2, 0x1e4, 0x1e5, 0x7, 0x1b, 0x2, 0x2, 0x1e5, 0x214, 0x5, 0x4c, 0x27, 
    0x19, 0x1e6, 0x1e7, 0xc, 0x17, 0x2, 0x2, 0x1e7, 0x1e8, 0x7, 0x1c, 0x2, 
    0x2, 0x1e8, 0x214, 0x5, 0x4c, 0x27, 0x18, 0x1e9, 0x1ea, 0xc, 0x16, 0x2, 
    0x2, 0x1ea, 0x1eb, 0x7, 0x1d, 0x2, 0x2, 0x1eb, 0x214, 0x5, 0x4c, 0x27, 
    0x17, 0x1ec, 0x1ed, 0xc, 0x15, 0x2, 0x2, 0x1ed, 0x1ee, 0x7, 0x1e, 0x2, 
    0x2, 0x1ee, 0x214, 0x5, 0x4c, 0x27, 0x16, 0x1ef, 0x1f0, 0xc, 0x14, 0x2, 
    0x2, 0x1f0, 0x1f1, 0x7, 0x19, 0x2, 0x2, 0x1f1, 0x214, 0x5, 0x4c, 0x27, 
    0x15, 0x1f2, 0x1f3, 0xc, 0x13, 0x2, 0x2, 0x1f3, 0x1f4, 0x7, 0x1a, 0x2, 
    0x2, 0x1f4, 0x214, 0x5, 0x4c, 0x27, 0x14, 0x1f5, 0x1f6, 0xc, 0x12, 0x2, 
    0x2, 0x1f6, 0x1f7, 0x7, 0x22, 0x2, 0x2, 0x1f7, 0x214, 0x5, 0x4c, 0x27, 
    0x13, 0x1f8, 0x1f9, 0xc, 0x11, 0x2, 0x2, 0x1f9, 0x1fa, 0x7, 0x21, 0x2, 
    0x2, 0x1fa, 0x214, 0x5, 0x4c, 0x27, 0x12, 0x1fb, 0x1fc, 0xc, 0x10, 0x2, 
    0x2, 0x1fc, 0x1fd, 0x7, 0x1f, 0x2, 0x2, 0x1fd, 0x214, 0x5, 0x4c, 0x27, 
    0x11, 0x1fe, 0x1ff, 0xc, 0xf, 0x2, 0x2, 0x1ff, 0x200, 0x7, 0x24, 0x2, 
    0x2, 0x200, 0x214, 0x5, 0x4c, 0x27, 0x10, 0x201, 0x202, 0xc, 0xe, 0x2, 
    0x2, 0x202, 0x203, 0x7, 0x23, 0x2, 0x2, 0x203, 0x214, 0x5, 0x4c, 0x27, 
    0xf, 0x204, 0x205, 0xc, 0xd, 0x2, 0x2, 0x205, 0x206, 0x7, 0x26, 0x2, 
    0x2, 0x206, 0x214, 0x5, 0x4c, 0x27, 0xe, 0x207, 0x208, 0xc, 0xc, 0x2, 
    0x2, 0x208, 0x209, 0x7, 0x25, 0x2, 0x2, 0x209, 0x214, 0x5, 0x4c, 0x27, 
    0xd, 0x20a, 0x20b, 0xc, 0xb, 0x2, 0x2, 0x20b, 0x20c, 0x7, 0x27, 0x2, 
    0x2, 0x20c, 0x214, 0x5, 0x4c, 0x27, 0xc, 0x20d, 0x20e, 0xc, 0xa, 0x2, 
    0x2, 0x20e, 0x20f, 0x7, 0x29, 0x2, 0x2, 0x20f, 0x214, 0x5, 0x4c, 0x27, 
    0xb, 0x210, 0x211, 0xc, 0x9, 0x2, 0x2, 0x211, 0x212, 0x7, 0x28, 0x2, 
    0x2, 0x212, 0x214, 0x5, 0x4c, 0x27, 0xa, 0x213, 0x1e3, 0x3, 0x2, 0x2, 
    0x2, 0x213, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x213, 0x1e9, 0x3, 0x2, 0x2, 
    0x2, 0x213, 0x1ec, 0x3, 0x2, 0x2, 0x2, 0x213, 0x1ef, 0x3, 0x2, 0x2, 
    0x2, 0x213, 0x1f2, 0x3, 0x2, 0x2, 0x2, 0x213, 0x1f5, 0x3, 0x2, 0x2, 
    0x2, 0x213, 0x1f8, 0x3, 0x2, 0x2, 0x2, 0x213, 0x1fb, 0x3, 0x2, 0x2, 
    0x2, 0x213, 0x1fe, 0x3, 0x2, 0x2, 0x2, 0x213, 0x201, 0x3, 0x2, 0x2, 
    0x2, 0x213, 0x204, 0x3, 0x2, 0x2, 0x2, 0x213, 0x207, 0x3, 0x2, 0x2, 
    0x2, 0x213, 0x20a, 0x3, 0x2, 0x2, 0x2, 0x213, 0x20d, 0x3, 0x2, 0x2, 
    0x2, 0x213, 0x210, 0x3, 0x2, 0x2, 0x2, 0x214, 0x217, 0x3, 0x2, 0x2, 
    0x2, 0x215, 0x213, 0x3, 0x2, 0x2, 0x2, 0x215, 0x216, 0x3, 0x2, 0x2, 
    0x2, 0x216, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x217, 0x215, 0x3, 0x2, 0x2, 0x2, 
    0x218, 0x219, 0x7, 0x2f, 0x2, 0x2, 0x219, 0x21a, 0x7, 0x35, 0x2, 0x2, 
    0x21a, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x21b, 0x21c, 0x7, 0x30, 0x2, 0x2, 
    0x21c, 0x21d, 0x7, 0x35, 0x2, 0x2, 0x21d, 0x51, 0x3, 0x2, 0x2, 0x2, 
    0x21e, 0x221, 0x7, 0x17, 0x2, 0x2, 0x21f, 0x221, 0x7, 0x18, 0x2, 0x2, 
    0x220, 0x21e, 0x3, 0x2, 0x2, 0x2, 0x220, 0x21f, 0x3, 0x2, 0x2, 0x2, 
    0x221, 0x53, 0x3, 0x2, 0x2, 0x2, 0x222, 0x225, 0x7, 0x33, 0x2, 0x2, 
    0x223, 0x225, 0x7, 0x34, 0x2, 0x2, 0x224, 0x222, 0x3, 0x2, 0x2, 0x2, 
    0x224, 0x223, 0x3, 0x2, 0x2, 0x2, 0x225, 0x55, 0x3, 0x2, 0x2, 0x2, 0x226, 
    0x227, 0x7, 0x38, 0x2, 0x2, 0x227, 0x57, 0x3, 0x2, 0x2, 0x2, 0x43, 0x61, 
    0x69, 0x71, 0x78, 0x7c, 0x82, 0x88, 0x8e, 0x94, 0x9b, 0x9f, 0xa3, 0xa7, 
    0xa9, 0xab, 0xad, 0xb8, 0xbc, 0xbe, 0xc5, 0xcb, 0xd1, 0xda, 0xe5, 0xe9, 
    0xed, 0xef, 0xf1, 0xfa, 0x103, 0x108, 0x10c, 0x10e, 0x110, 0x117, 0x127, 
    0x12e, 0x133, 0x13a, 0x13e, 0x142, 0x144, 0x146, 0x14d, 0x155, 0x160, 
    0x165, 0x167, 0x16f, 0x174, 0x17e, 0x18e, 0x196, 0x19e, 0x1a9, 0x1b3, 
    0x1c1, 0x1c5, 0x1cf, 0x1d1, 0x1e1, 0x213, 0x215, 0x220, 0x224, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

openeParser::Initializer openeParser::_init;
