#include <stdlib.h>

#include "AST.h"

int ast_var_def (AST * ast)
{
    if (ast == NULL) return 0;

    ast -> var_def_name = NULL;
    ast -> var_def_val  = NULL;

    return 1;
}

int ast_var_name (AST * ast)
{
    if (ast == NULL) return 0;

    ast -> var_name = NULL;

    return 1;
}

int ast_func_def (AST * ast)
{
    if (ast == NULL) return 0;

    ast -> func_def_body      = NULL;
    ast -> func_def_name      = NULL;
    ast -> func_def_args      = NULL;
    ast -> func_def_args_size = 0;

    return 1;
}

int ast_func_name (AST * ast)
{
    if (ast == NULL) return 0;

    ast -> func_name           = NULL;
    ast -> func_call_args      = NULL;
    ast -> func_call_arg_size = 0;

    return 1;
}

int ast_string (AST * ast)
{
    if (ast == NULL) return 0;

    ast -> str_val = NULL;

    return 1;
}

int ast_compound (AST * ast)
{
    if (ast == NULL) return 0;

    ast -> comp_value = NULL;
    ast -> comp_size  = 0;

    return 1;
}


AST * ast_init (int type) {

    AST * ast = malloc (sizeof (AST));

    ast -> type = type;

    ast -> scope = (void*)0;

    ast_var_def   (ast);
    ast_var_name  (ast);
    ast_func_def  (ast);
    ast_func_name (ast);
    ast_string    (ast);
    ast_string    (ast);
    ast_compound  (ast);

    return ast;
}
