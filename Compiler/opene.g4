parser grammar opene;

options { tokenVocab = openeLexer; }

opene
    : edition_spec NEWLINE
      library_list_opt
      prog_set
    | edition_spec struct_declare*
    ;

edition_spec
    : K_VERSION INTEGER_LITERAL
    ;

struct_declare
    : K_STRUCTURE IDENTIFIER (COMMA access_level?)? (COMMA variable_comment)? member_list*
    ;

access_level
    : IDENTIFIER
    ;

member_list
    : K_MEMBER_VARIABLE variable_decl
    ;

library_list_opt
    : library_spec*
    ;

library_spec
    : K_LIBRARY IDENTIFIER NEWLINE
    ;

prog_set
    : K_PROGRAM_SET name=TABLE_ITEM TABLE_END
      prog_set_variable_decl_opt
      sub_program_opt
    ;

prog_set_variable_decl_opt
    : prog_set_variable_decl*
    ;

prog_set_variable_decl
    : K_PROGRAM_SET_VARIABLE variable_decl
    ;

variable_decl
    : name=TABLE_ITEM TABLE_COMMA type=TABLE_ITEM (TABLE_COMMA TABLE_COMMA dimension=TABLE_ITEM?)? (TABLE_COMMA comment=TABLE_ITEM)? TABLE_END
    ;

variable_comment
    : variable_comment_element*
    ;

variable_comment_element
    : IDENTIFIER
    | OTHER_CHAR
    | COMMA
    ;

variable_name
    : IDENTIFIER
    ;

variable_type
    : IDENTIFIER
    ;

dimension_decl
    : DQUOTE INTEGER_LITERAL DQUOTE
    ;

sub_program_opt
    : (NEWLINE* sub_program NEWLINE*)*
    ;

sub_program
    : K_SUB_PROGRAM name=TABLE_ITEM (TABLE_COMMA type=TABLE_ITEM? (TABLE_COMMA access=TABLE_ITEM? (TABLE_COMMA comment=TABLE_ITEM)?)?)? TABLE_END
      parameter_decl_list local_variable_decl*
      statement_list
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
    : (statement? NEWLINE)*
    ;

statement
    : condition_statement                                           # ConditionStatement
    | hierarchy_identifier (K_ASSIGN_OPT | K_AECOM_OPT) expression  # AssignStatement
    | expression                                                    # ExpressionStatement
    | loop_statement                                                # LoopStatement
    ;


loop_statement
    : K_WHILE LBRACK expression RBRACK
      statement_list
      K_WHILE_END LBRACK RBRACK                             # While
    | K_FOR LBRACK expression COMMA IDENTIFIER? RBRACK
      statement_list
      K_FOR_END LBRACK RBRACK                               # For
    ;

condition_statement
    : K_IF LBRACK expression RBRACK
      statement_list
      condition_statement_else?
      K_END_IF                              # IfStmt
    | K_IF_TRUE LBRACK expression RBRACK
      statement_list
      K_END_IF_TRUE                         # IfTrueStmt
    ;

condition_statement_else
    : K_ELSE statement_list
    ;

hierarchy_identifier
    : name_component (DOT name_component)*
    ;

name_component
    : IDENTIFIER                                                        # Identifier
    | name_component LBRACK RBRACK                                      # FuncCallWithoutArgu
    | name_component LBRACK expression (COMMA expression?)* RBRACK      # FuncCallWithArgu
    | name_component LSQUBRACK expression RSQUBRACK                     # ArrayIndex
    ;

expression
    : LBRACK expression RBRACK                                  # Bracket
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
    ;

macro_value
    : SHARP IDENTIFIER
    ;

func_ptr
    : ADDRESS IDENTIFIER
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
