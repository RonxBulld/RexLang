
grammar opene;

opene_src
    : edition_spec library_list_opt prog_set_name prog_set_variable_decl_opt sub_program_opt
    ;

edition_spec
    : VERSION DIGIT
    ;

library_list_opt
    : library_spec*
    ;

library_spec
    : LIBRARY FILENAME
    ;

prog_set_name
    : PROGRAM_SET IDENTIFIER
    ;

prog_set_variable_decl_opt
    : variable_decl*
    ;

variable_decl
    : PROGRAM_SET_VARIABLE IDENTIFIER ',' IDENTIFIER ',' ',' dimension_decl? ',' IDENTIFIER
    ;

dimension_decl
    : '"' DIGIT '"'
    ;
    
sub_program_opt
    : SUB_PROGRAM IDENTIFIER
    ;

VERSION: '.版本';

LIBRARY: '.支持库';

PROGRAM_SET: '.程序集';

PROGRAM_SET_VARIABLE: '.程序集变量';

SUB_PROGRAM: '.子程序';

DIGIT: ('0' .. '9')+;

FILENAME: [a-zA-Z0-9_]+;

IDENTIFIER
    : ('a' .. 'z' | 'A' .. 'Z' | '0' .. '9' | '_' | '\u4E00'..'\u9FA5' | '\uF900'..'\uFA2D')+
    ;

WHITESPACE: (' ' | '\t')+ -> skip;

NEWLINE: '\r' ? '\n' -> skip;
