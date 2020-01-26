grammar openeLang;

 /*
  * antlr4 -o opene_parse/gen -lib opene_parse/gen -encoding utf-8 -long-messages -listener -visitor -package opene -Dlanguage=Cpp openeLang.g4
  */

K_ADD_OPT: '＋' | '+';
K_SUB_OPT: '－' | '-';
K_MUL_OPT: '×' | '*';
K_DIV_OPT: '÷' | '/';
K_FULL_DIV_OPT: '／' | '\\';
K_MOD_OPT: '％' | '%' | 'Mod';
K_AECOM_OPT: '＝';
K_ASSIGN_OPT: '=';
K_EQUAL_OPT: '==';
K_NOT_EQUAL_OPT: '≠' | '<>' | '!=';
K_GREAT_OPT: '＞' | '>';
K_LESS_OPT: '＜' | '<';
K_GREAT_EQU_OPT: '≥' | '>=';
K_LESS_EQU_OPT: '≤' | '<=';
K_LIKE_EQU_OPT: '≈' | '?=';
K_OR_OPT: '或' | 'Or' | '||';
K_AND_OPT: '且' | 'And' | '&&';

INTEGER_LITERAL: ('-'|'+')? ('0' .. '9')+;
FLOAT_LITERAL
    : INTEGER_LITERAL? '.' INTEGER_LITERAL
    | INTEGER_LITERAL '.' INTEGER_LITERAL?
    ;
fragment UNICODE_CHAR: ('\u4E00'..'\u9FA5' | '\uF900'..'\uFA2D');
fragment WS: (' ' | '\t')+;
IDENTIFIER: ([a-z] | [A-Z] | ('0' .. '9') | '_' | UNICODE_CHAR)+;
WHITESPACE: WS -> skip;
NEWLINE: ('\r' ? '\n')+;
STRING_LITERAL
    : '\u201c'.*?'\u201d'    // “...”
    | '"' ~["\r\n]*? '"'
    ;
CODE_COMMENT: '\''.*? '\r' ? '\n' -> type(NEWLINE);
OTHER_CHAR: .;


opene_src
    : edition_spec
      NEWLINE
      src_content
      EOF
    ;

src_content
    : program_set_file
    | data_structure_file
    | global_variable_file
    | dll_define_file
    ;

program_set_file
    : ('.支持库' libraries+=IDENTIFIER NEWLINE)*
      prog_set
    ;

data_structure_file
    : struct_declare*
    ;

global_variable_file
    : global_variable_list
    ;

dll_define_file
    : dll_command*
    ;

dll_command
    : '.DLL命令' name=IDENTIFIER ',' type=IDENTIFIER? ',' file=STRING_LITERAL? ',' cmd=STRING_LITERAL (',' table_comment)? NEWLINE
      parameter_decl*
      NEWLINE*
    ;

global_variable_list
    : global_variable_item*
    ;

global_variable_item
    : '.全局变量' name=IDENTIFIER (',' type=IDENTIFIER? (',' access=IDENTIFIER? (',' dimension=STRING_LITERAL? (',' table_comment)?)?)?)? NEWLINE
    ;

edition_spec
    : '.版本' INTEGER_LITERAL
    ;

struct_declare
    : '.数据类型' name=IDENTIFIER (',' access=IDENTIFIER? (',' table_comment)?)? NEWLINE
      ('.成员' struct_mems+=member_vari_decl)*
      NEWLINE*
    ;

table_comment
    : comment=.*?
    ;

prog_set
    : '.程序集' name=IDENTIFIER (',' base=IDENTIFIER? (',' access=IDENTIFIER? (',' table_comment)?)?)? NEWLINE
      ('.程序集变量' prog_set_varis+=file_vari_decl)*
      (NEWLINE* functions+=sub_program NEWLINE*)*
    ;

variable_decl
    : name=IDENTIFIER (',' type=IDENTIFIER? (',' ',' dimension=STRING_LITERAL? (',' table_comment)?)?)? NEWLINE
    ;

member_vari_decl
    : variable_decl
    ;

file_vari_decl
    : variable_decl
    ;

sub_program
    : '.子程序' name=IDENTIFIER (',' type=IDENTIFIER? (',' access=IDENTIFIER? (',' table_comment)?)?)? NEWLINE
      (params+=parameter_decl)*
      (local_vari+=local_variable_decl)*
      statement_list
    ;

local_variable_decl
    : '.局部变量' name=IDENTIFIER (',' type=IDENTIFIER? (',' attribute=IDENTIFIER? (',' dimension=STRING_LITERAL? (',' table_comment)?)?)?)? NEWLINE
    ;

parameter_decl
    : '.参数' name=IDENTIFIER ',' type=IDENTIFIER (',' (attributes+=IDENTIFIER)* (',' table_comment)?)? NEWLINE
    ;

statement_list
    : (stmts+=statement? NEWLINE)*
    ;

statement
    : condition_statement                                           # ConditionStatement
    | hierarchy_identifier (K_ASSIGN_OPT | K_AECOM_OPT) expression  # AssignStatement
    | expression                                                    # ExpressionStatement
    | loop_statement                                                # LoopStatement
    | switch_statement                                              # SwitchStatement
    ;

switch_statement
    : '.判断开始' '(' major_condition_expr=expression ')' NEWLINE
      major_cond_body=statement_list
      (
        '.判断' '(' minor_condition_expr+=expression ')' NEWLINE
        minor_cond_body+=statement_list
      )*
      '.默认' NEWLINE
      default_body=statement_list
      '.判断结束'
    ;

loop_statement
    : '.判断循环首' '(' condition_expr=expression ')' NEWLINE
      loop_body=statement_list
      '.判断循环尾' '(' ')'
                                                                                        # While

    | '.计次循环首' '(' times_expr=expression ',' loop_variable=IDENTIFIER? ')' NEWLINE
      loop_body=statement_list
      '.计次循环尾' '(' ')'
                                                                                        # RangeFor

    | '.变量循环首' '(' loop_start=expression ',' loop_end=expression ',' loop_step=expression (',' loop_variable=hierarchy_identifier)? ')' NEWLINE
      loop_body=statement_list
      '.变量循环尾' '(' ')'
                                                                                        # For

    | '.循环判断首' '(' ')' NEWLINE
      loop_body=statement_list
      '.循环判断尾' '(' condition_expr=expression ')'
                                                                                        # DoWhile
    ;

condition_statement
    : '.如果' '(' condition_expr=expression ')'
      true_stmt_list=statement_list
      ('.否则' false_stmt_list=statement_list)?
      '.如果结束'
                                                        # IfStmt
    | '.如果真' '(' condition_expr=expression ')'
      true_stmt_list=statement_list
      '.如果真结束'
                                                        # IfTrueStmt
    ;

hierarchy_identifier
    : components+=name_component ('.' components+=name_component)*
    ;

name_component
    : IDENTIFIER                                                                    # Identifier
    | name_component '(' arguments+=expression? (',' arguments+=expression?)* ')'   # FuncCall
    | name_component '[' expression ']'                                             # ArrayIndex
    ;

expression
    : '(' expression ')'                                        # Bracket
    | opt=K_SUB_OPT expression                                  # UnaryExpr
// ------------------------------------- 四则运算
    | lval=expression opt=K_MUL_OPT       rval=expression       # BinaryExpr
    | lval=expression opt=K_DIV_OPT       rval=expression       # BinaryExpr
    | lval=expression opt=K_FULL_DIV_OPT  rval=expression       # BinaryExpr
    | lval=expression opt=K_MOD_OPT       rval=expression       # BinaryExpr
    | lval=expression opt=K_ADD_OPT       rval=expression       # BinaryExpr
    | lval=expression opt=K_SUB_OPT       rval=expression       # BinaryExpr
// ------------------------------------- 比较运算
    | lval=expression opt=K_NOT_EQUAL_OPT rval=expression       # BinaryExpr
    | lval=expression opt=K_EQUAL_OPT     rval=expression       # BinaryExpr
    | lval=expression opt=K_AECOM_OPT     rval=expression       # BinaryExpr
    | lval=expression opt=K_LESS_OPT      rval=expression       # BinaryExpr
    | lval=expression opt=K_GREAT_OPT     rval=expression       # BinaryExpr
    | lval=expression opt=K_LESS_EQU_OPT  rval=expression       # BinaryExpr
    | lval=expression opt=K_GREAT_EQU_OPT rval=expression       # BinaryExpr
    | lval=expression opt=K_LIKE_EQU_OPT  rval=expression       # BinaryExpr
// ------------------------------------- 逻辑运算
    | lval=expression opt=K_AND_OPT       rval=expression       # BinaryExpr
    | lval=expression opt=K_OR_OPT        rval=expression       # BinaryExpr
// -------------------------------------
    | number                                                    # OptElement
    | bool_value                                                # OptElement
    | macro_value                                               # OptElement
    | string_value                                              # OptElement
    | hierarchy_identifier                                      # OptElement
    | func_ptr                                                  # OptElement
    | datetime_value                                            # OptElement
    | data_set_value                                            # OptElement
    ;

data_set_value
    : '{' (elems+=expression (',' elems+=expression)*)? '}'
    ;

datetime_value
    : '[' datetime_value_core ']'
    ;

datetime_value_core
    : time=INTEGER_LITERAL
                                                                        # DatetimePureNumber
    | year=INTEGER_LITERAL '年' month=INTEGER_LITERAL '月' day=INTEGER_LITERAL '日'
      (hour=INTEGER_LITERAL '时' minute=INTEGER_LITERAL '分' second=INTEGER_LITERAL '秒')?
                                                                        # DatetimeSeparateByChinese
    | year=INTEGER_LITERAL '/' month=INTEGER_LITERAL '/' day=INTEGER_LITERAL
      ('/' hour=INTEGER_LITERAL '/' minute=INTEGER_LITERAL '/' second=INTEGER_LITERAL)?
                                                                        # DatetimeSeparateBySlash
    | year=INTEGER_LITERAL '/' month=INTEGER_LITERAL '/' day=INTEGER_LITERAL
      ('/' hour=INTEGER_LITERAL ':' minute=INTEGER_LITERAL ':' second=INTEGER_LITERAL)?
                                                                        # DatetimeSeparateBySlashColon
    | year=INTEGER_LITERAL '-' month=INTEGER_LITERAL '-' day=INTEGER_LITERAL
      ('-' hour=INTEGER_LITERAL '-' minute=INTEGER_LITERAL '-' second=INTEGER_LITERAL)?
                                                                        # DatetimeSeparateByBar
    | year=INTEGER_LITERAL '-' month=INTEGER_LITERAL '-' day=INTEGER_LITERAL
      ('-' hour=INTEGER_LITERAL ':' minute=INTEGER_LITERAL ':' second=INTEGER_LITERAL)?
                                                                        # DatetimeSeparateByBarColon
    ;

macro_value
    : '#' IDENTIFIER
    ;

func_ptr
    : '&' IDENTIFIER
    ;

bool_value
    : bval='真'      # BoolValueTrue
    | bval='假'      # BoolValueFalse
    ;

number
    : INTEGER_LITERAL                                   # Int
    | FLOAT_LITERAL                                     # Float
    ;

string_value
    : STRING_LITERAL
    ;
