parser grammar openeParser;

options { tokenVocab = openeLexer; }

opene_src
    : edition_spec NEWLINE
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
    : library_spec*
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
    : K_DLL_DEFINE name=TABLE_ITEM TABLE_COMMA type=TABLE_ITEM? TABLE_COMMA file=TABLE_ITEM? TABLE_COMMA cmd=TABLE_ITEM (TABLE_COMMA table_comment)? TABLE_END
      parameter_decl*
      NEWLINE*
    ;

global_variable_list
    : global_variable_item*
    ;

global_variable_item
    : K_GLOBAL_VARIABLE name=TABLE_ITEM (TABLE_COMMA type=TABLE_ITEM? (TABLE_COMMA access=TABLE_ITEM? (TABLE_COMMA dimension=TABLE_DIMENSION? (TABLE_COMMA table_comment)?)?)?)? TABLE_END
    ;

edition_spec
    : K_VERSION INTEGER_LITERAL
    ;

struct_declare
    : K_STRUCTURE name=TABLE_ITEM (TABLE_COMMA access=TABLE_ITEM? (TABLE_COMMA table_comment)?)? TABLE_END
      member_item*
      NEWLINE*
    ;

table_comment
    : (TABLE_COMMA | TABLE_ITEM | TABLE_DIMENSION)*
    ;

member_item
    : K_MEMBER_VARIABLE variable_decl
    ;

library_spec
    : K_LIBRARY IDENTIFIER NEWLINE
    ;

prog_set
    : K_PROGRAM_SET name=TABLE_ITEM (TABLE_COMMA base=TABLE_ITEM? (TABLE_COMMA access=TABLE_ITEM? (TABLE_COMMA table_comment)?)?)? TABLE_END
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
    : name=TABLE_ITEM (TABLE_COMMA type=TABLE_ITEM? (TABLE_COMMA TABLE_COMMA dimension=TABLE_DIMENSION? (TABLE_COMMA table_comment)?)?)? TABLE_END
    ;

sub_program_opt
    : (NEWLINE* sub_program NEWLINE*)*
    ;

sub_program
    : K_SUB_PROGRAM name=TABLE_ITEM (TABLE_COMMA type=TABLE_ITEM? (TABLE_COMMA access=TABLE_ITEM? (TABLE_COMMA table_comment)?)?)? TABLE_END
      parameter_decl*
      local_variable_decl*
      statement_list
    ;

parameter_decl
    : K_PARAMETER name=TABLE_ITEM TABLE_COMMA type=TABLE_ITEM (TABLE_COMMA attributes=TABLE_ITEM* (TABLE_COMMA table_comment)?)? TABLE_END
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
    | switch_statement                                              # SwitchStatement
    ;

switch_statement
    : K_SWITCH_START LBRACK condition_expr=expression RBRACK NEWLINE
      cond_body=statement_list
      (
        K_SWITCH_CASE LBRACK condition_expr=expression RBRACK NEWLINE
        cond_body=statement_list
      )*
      K_SWITCH_DEFAULT NEWLINE
      default_body=statement_list
      K_SWITCH_END
    ;

loop_statement
    : K_WHILE LBRACK condition_expr=expression RBRACK NEWLINE
      loop_body=statement_list
      K_WHILE_END LBRACK RBRACK                             # While

    | K_RANGE_FOR LBRACK condition_expr=expression COMMA loop_variable=IDENTIFIER? RBRACK NEWLINE
      loop_body=statement_list
      K_RANGE_FOR_END LBRACK RBRACK                         # RangeFor

    | K_FOR LBRACK loop_start=expression COMMA loop_end=expression COMMA loop_step=expression (COMMA loop_variable=expression)? RBRACK NEWLINE
      loop_body=statement_list
      K_FOR_END LBRACK RBRACK                               # For

    | K_DO_WHILE LBRACK RBRACK NEWLINE
      loop_body=statement_list
      K_DO_WHILE_END LBRACK condition_expr=expression RBRACK               # DoWhile
    ;

condition_statement
    : K_IF LBRACK condition_expr=expression RBRACK
      true_stmt_list=statement_list
      (K_ELSE false_stmt_list=statement_list)?
      K_END_IF                              # IfStmt
    | K_IF_TRUE LBRACK condition_expr=expression RBRACK
      true_stmt_list=statement_list
      K_END_IF_TRUE                         # IfTrueStmt
    ;

hierarchy_identifier
    : name_component (DOT name_component)*
    ;

name_component
    : IDENTIFIER                                                        # Identifier
    | name_component LBRACK expression? (COMMA expression?)* RBRACK     # FuncCall
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
    | datetime_value                                            # OptElement
    | data_set_value                                            # OptElement
    ;

data_set_value
    : LCURLYBRACE expression RCURLYBRACE
    ;

datetime_value
    : LSQUBRACK DATETIME_LITERAL RSQUBRACK
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
