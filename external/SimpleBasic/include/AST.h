#ifndef AST_H
#define AST_H

#include <stddef.h>

typedef struct AST_STRUCT {

    enum {

        AST_VAR_DEF,
        AST_FUNC_DEF,
        AST_VAR,
        AST_FUNC_CALL,
        AST_STR,
        AST_COMPOUND,
        AST_NOOP

    } type;

    struct SCOPE_STRUCT * scope;

    char * var_def_name;
    struct AST_STRUCT * var_def_val;

    struct AST_STRUCT * func_def_body;
    struct AST_STRUCT ** func_def_args;
    char * func_def_name;
    size_t func_def_args_size;

    char * var_name;

    struct AST_STRUCT ** func_call_args;
    size_t func_call_arg_size;
    char * func_name;

    char * str_val;

    struct AST_STRUCT ** comp_value;
    size_t comp_size;

} AST;

int ast_var_def   (AST * ast);
int ast_var_name  (AST * ast);
int ast_func_def  (AST * ast);
int ast_func_name (AST * ast);
int ast_string    (AST * ast);
int ast_string    (AST * ast);
int ast_compound  (AST * ast);


AST * ast_init (int type);

#endif
