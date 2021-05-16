#include <string.h>

#include "scope.h"

Scope * scope_init ()
{
    Scope * scp = malloc (sizeof (Scope));

    scp -> func_defs = NULL;
    scp -> func_defs_size = 0;

    scp -> var_defs = NULL;
    scp -> var_defs_size = 0;

    return scp;
}

AST * scope_add_var_def (Scope * scp, AST * vd)
{
    if (scp -> var_defs == NULL) {
        scp -> var_defs = malloc (sizeof (AST *));
        scp -> var_defs [0] = vd;
        scp -> var_defs_size ++;
    } else {
        scp -> var_defs = realloc (scp -> var_defs, scp -> var_defs_size * sizeof (AST *));;
        scp -> var_defs_size ++;
        scp -> var_defs [scp -> var_defs_size - 1] = vd;
    }

    return vd;
}

AST * scope_get_var_def (Scope * scp, const char * vn)
{
    for (int i = 0; i < scp -> var_defs_size; i++) {
        AST * vd = scp -> var_defs [i];

        if (strcmp (vd -> var_def_name, vn) == 0) return vd;
    }

    return NULL;
}


AST * scope_add_func_def  (Scope * scp, AST * fd)
{
    scp -> func_defs_size ++;

    if (scp -> func_defs == NULL)
        scp -> func_defs = malloc  (sizeof (AST));

    else
        scp -> func_defs = realloc (scp -> func_defs, scp -> func_defs_size * sizeof (AST));

    scp -> func_defs [scp -> func_defs_size - 1] = fd;

    return fd;
}

AST * scope_get_func_def  (Scope * scp, const char * fn)
{
    for (int i = 0; i < scp -> func_defs_size; i++) {
        AST * fd = scp -> func_defs [i];

        if (strcmp (fd -> func_def_name, fn) == 0) return fd;
    }

    return NULL;
}


