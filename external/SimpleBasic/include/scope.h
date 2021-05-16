#ifndef SCOPE_H
#define SCOPE_H

#include "AST.h"

typedef struct SCOPE
{
    AST ** func_defs;
    size_t func_defs_size;

    AST ** var_defs;
    size_t var_defs_size;
} Scope;


Scope * scope_init ();


AST * scope_add_var_def  (Scope * scp, AST * vd);

AST * scope_get_var_def  (Scope * scp, const char * vn);


AST * scope_add_func_def (Scope * scp, AST * fd);

AST * scope_get_func_def (Scope * scp, const char * fn);

#endif
