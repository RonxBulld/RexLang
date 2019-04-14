
grammar opene;

K_VERSION: '.版本';

K_LIBRARY: '.支持库';

K_PROGRAM_SET: '.程序集';

K_PROGRAM_SET_VARIABLE: '.程序集变量';

K_LOCAL_VARIABLE: '.局部变量';

K_PARAMETER: '.参数';

K_SUB_PROGRAM: '.子程序';

K_IF_TRUE: '.如果真';

K_IF_TRUE_END: '.如果真结束';

K_IF: '.如果';

K_ELSE: '.否则';

K_END_IF: '.如果结束';

K_WHILE: '.判断循环首';

K_WHILE_END: '.判断循环尾';

K_FOR: '.计次循环首';

K_FOR_END: '.计次循环尾';

K_TRUE: '真';

K_FALSE: '假';

K_ADD_OPT: '＋';

K_SUB_OPT: '－';

K_MUL_OPT: '×';

K_DIV_OPT: '÷';

K_ASSIGN_OPT: '＝';

K_NOT_EQUAL_OPT: '≠';

K_OR_OPT: '或';

INTEGER_LITERAL: ('0' .. '9')+;

FLOAT_LITERAL
    : INTEGER_LITERAL? '.' INTEGER_LITERAL
    | INTEGER_LITERAL '.' INTEGER_LITERAL?
    ;

fragment
UNICODE_CHAR: '\u4E00'..'\u9FA5' | '\uF900'..'\uFA2D';

IDENTIFIER
    : ([a-z] | [A-Z] | ('0' .. '9') | '_' | UNICODE_CHAR)+
    ;

WHITESPACE: (' ' | '\t')+ -> skip;

NEWLINE: '\r' ? '\n' -> skip;

STRING_LITERAL: '“'.*?'”';

CODE_COMMIT: '\''.*? '\r' ? '\n' -> skip;

OTHER_CHAR: .;

opene_src
    : edition_spec library_list_opt prog_set
    ;

edition_spec
    : K_VERSION INTEGER_LITERAL
    ;

library_list_opt
    : library_spec*
    ;

library_spec
    : K_LIBRARY IDENTIFIER
    ;

prog_set
    : K_PROGRAM_SET IDENTIFIER prog_set_variable_decl_opt sub_program_opt
    ;

prog_set_variable_decl_opt
    : prog_set_variable_decl*
    ;

prog_set_variable_decl
    : K_PROGRAM_SET_VARIABLE variable_decl
    ;

variable_decl
    : variable_name ',' variable_type (',' ',' dimension_decl?)? (',' variable_comment)?
    ;

variable_comment
    : variable_comment_element*
    ;

variable_comment_element
    : IDENTIFIER
    | OTHER_CHAR
    ;

variable_name
    : IDENTIFIER
    ;

variable_type
    : IDENTIFIER
    ;

dimension_decl
    : '"' INTEGER_LITERAL '"'
    ;
    
sub_program_opt
    : sub_program*
    ;

sub_program
    : K_SUB_PROGRAM IDENTIFIER (',' variable_type)? parameter_decl_list local_variable_decl* statement_list
    ;

parameter_decl_list
    : parameter_decl*
    ;

parameter_decl
    : K_PARAMETER variable_decl
    ;

local_variable_decl
    : K_LOCAL_VARIABLE variable_decl
    ;

statement_list
    : statement*
    ;

statement
    : expression
    | condition_statement
    | hierarchy_identifier K_ASSIGN_OPT expression
    | K_WHILE '(' expression ')' statement_list K_WHILE_END '(' ')'
    | K_FOR '(' expression ',' expression? ')' statement_list K_FOR_END '(' ')'
    ;

condition_statement
    : K_IF '(' expression ')' statement_list condition_statement_else? K_END_IF     # IfStmt
    | K_IF_TRUE_END '(' expression ')' statement_list K_IF_TRUE_END                 # IfTrueStmt
    ;

condition_statement_else
    : K_ELSE statement_list
    ;

hierarchy_identifier
    : name_component ('.' name_component)*
    ;

name_component
    : IDENTIFIER                                        # Identifier
    | IDENTIFIER '(' ')'                                # FuncCallWithoutArgu
    | IDENTIFIER '(' expression (',' expression?)* ')'  # FuncCallWithArgu
    | IDENTIFIER '[' expression ']'                     # ArrayIndex
    ;

expression
    : '(' expression ')'                                # Bracket
    | opt='-' expression                                # UnaryExpr
// ------------------------------------- 四则运算
    | expression opt=K_ADD_OPT expression               # BinaryExpr
    | expression opt=K_SUB_OPT expression               # BinaryExpr
    | expression opt=K_MUL_OPT expression               # BinaryExpr
    | expression opt=K_DIV_OPT expression               # BinaryExpr
// ------------------------------------- 比较运算
    | expression opt=K_ASSIGN_OPT    expression         # BinaryExpr
    | expression opt=K_NOT_EQUAL_OPT expression         # BinaryExpr
// ------------------------------------- 逻辑运算
    | expression opt=K_OR_OPT expression                # BinaryExpr
// -------------------------------------
    | number                                            # OptElement
    | bool_value                                        # OptElement
    | macro_value                                       # OptElement
    | string_value                                      # OptElement
    | hierarchy_identifier                              # OptElement
    ;

macro_value
    : '#' IDENTIFIER
    ;

bool_value
    : bval=K_TRUE
    | bval=K_FALSE
    ;

number
    : INTEGER_LITERAL                                   # Int
    | FLOAT_LITERAL                                     # Float
    ;

string_value
    : STRING_LITERAL
    ;
