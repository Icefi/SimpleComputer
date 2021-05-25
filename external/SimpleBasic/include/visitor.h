#ifndef VISITOR_H
#define VISITOR_H

#include "AST.h"

AST * visit           (AST * node);
AST * visit_var_def   (AST * node);
AST * visit_func_def  (AST * node);
AST * visit_var       (AST * node);
AST * visit_func_call (AST * node);
AST * visit_string    (AST * node);
AST * visit_compound   (AST * node);

#endif