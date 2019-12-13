
// Generated from openeLexer.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime/antlr4-runtime.h"


namespace opene {


class  openeLexer : public antlr4::Lexer {
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
    TABLE_MODE = 1
  };

  openeLexer(antlr4::CharStream *input);
  ~openeLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace opene
