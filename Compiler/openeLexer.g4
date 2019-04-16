lexer grammar openeLexer;

K_VERSION: '.\u7248\u672c';                                                     // 版本
K_LIBRARY: '.\u652f\u6301\u5e93';                                               // 支持库
K_PROGRAM_SET: '.\u7a0b\u5e8f\u96c6' -> mode(TABLE_MODE);                       // 程序集
K_PROGRAM_SET_VARIABLE: '.\u7a0b\u5e8f\u96c6\u53d8\u91cf' -> mode(TABLE_MODE);  // 程序集变量
K_LOCAL_VARIABLE: '.\u5c40\u90e8\u53d8\u91cf' -> mode(TABLE_MODE);              // 局部变量
K_GLOBAL_VARIABLE: '.\u5168\u5c40\u53d8\u91cf' -> mode(TABLE_MODE);             // 全局变量
K_DLL_DEFINE: '.\u0044\u004c\u004c\u547d\u4ee4' -> mode(TABLE_MODE);            // DLL命令定义表
K_MEMBER_VARIABLE: '.\u6210\u5458' -> mode(TABLE_MODE);                         // 成员
K_PARAMETER: '.\u53c2\u6570' -> mode(TABLE_MODE);                               // 参数
K_SUB_PROGRAM: '.\u5b50\u7a0b\u5e8f' -> mode(TABLE_MODE);                       // 子程序
K_STRUCTURE: '.\u6570\u636e\u7c7b\u578b' -> mode(TABLE_MODE);                   // 数据类型
K_IF_TRUE: '.\u5982\u679c\u771f';                                               // 如果真
K_END_IF_TRUE: '.\u5982\u679c\u771f\u7ed3\u675f';                               // 如果真结束
K_IF: '.\u5982\u679c';                                                          // 如果
K_ELSE: '.\u5426\u5219';                                                        // 否则
K_END_IF: '.\u5982\u679c\u7ed3\u675f';                                          // 如果结束
K_WHILE: '.\u5224\u65ad\u5faa\u73af\u9996';                                     // 判断循环首
K_WHILE_END: '.\u5224\u65ad\u5faa\u73af\u5c3e';                                 // 判断循环尾
K_FOR: '.\u8ba1\u6b21\u5faa\u73af\u9996';                                       // 计次循环首
K_FOR_END: '.\u8ba1\u6b21\u5faa\u73af\u5c3e';                                   // 计次循环尾
K_TRUE: '\u771f';                                                               // 真
K_FALSE: '\u5047';                                                              // 假

K_ADD_OPT
    : '\uff0b'  // ＋
    | '+'
    ;
K_SUB_OPT
    : '\uff0d'  // －
    | '-'
    ;
K_MUL_OPT
    : '\u00d7'  // ×
    | '*'
    ;
K_DIV_OPT
    : '\u00f7'  // ÷
    | '/'
    ;
K_FULL_DIV_OPT
    : '\uff3c'  // ／
    | '\\'
    ;
K_MOD_OPT
    : '\uff05'  // ％
    | '%'
    | 'Mod'
    ;

K_AECOM_OPT: '\uff1d';  // ＝
K_ASSIGN_OPT: '=';
K_EQUAL_OPT: '==';
K_NOT_EQUAL_OPT
    : '\u2260'      // ≠
    | '<>'
    | '!='
    ;
K_GREAT_OPT
    : '\uff1e'      // ＞
    | '>'
    ;
K_LESS_OPT
    : '\uff1c'      // ＜
    | '<'
    ;
K_GREAT_EQU_OPT
    : '\u2265'      // ≥
    | '>='
    ;
K_LESS_EQU_OPT
    : '\u2264'      // ≤
    | '<='
    ;
K_LIKE_EQU_OPT
    : '\u2248'      // ≈
    | '?='
    ;

K_OR_OPT
    : '\u6216'       // 或
    | 'Or'
    | '||'
    ;
K_AND_OPT
    : '\u4e14'       // 且
    | 'And'
    | '&&'
    ;

COMMA: ',';
LBRACK: '(';
RBRACK: ')';
LSQUBRACK: '[';
RSQUBRACK: ']';
SHARP: '#';
ADDRESS: '&';
DQUOTE: '"';
DOT: '.';

INTEGER_LITERAL: ('0' .. '9')+;
FLOAT_LITERAL
    : INTEGER_LITERAL? '.' INTEGER_LITERAL
    | INTEGER_LITERAL '.' INTEGER_LITERAL?
    ;

fragment
UNICODE_CHAR: '\u4E00'..'\u9FA5' | '\uF900'..'\uFA2D';
IDENTIFIER: ([a-z] | [A-Z] | ('0' .. '9') | '_' | UNICODE_CHAR)+;
fragment
WS: (' ' | '\t')+;
WHITESPACE: WS -> skip;
NEWLINE: ('\r' ? '\n')+;
STRING_LITERAL: '\u201c'.*?'\u201d';    // “...”
CODE_COMMENT: '\''.*? '\r' ? '\n' -> type(NEWLINE);
OTHER_CHAR: .;

mode TABLE_MODE;
TABLE_END: '\r' ? '\n' -> mode(DEFAULT_MODE);
TABLE_ITEM: ~[ ,\r\n]+;
TABLE_WS: WS -> skip;
TABLE_COMMA: ',';