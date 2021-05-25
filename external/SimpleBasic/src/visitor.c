#include <string.h>
#include <stdio.h>

#include "scope.h"

#include "visitor.h"

AST * visit           (AST * node)
{
	switch (node -> type) {
		case AST_VAR_DEF:   return visit_var_def   (node);
		case AST_VAR:       return visit_var       (node);

		case AST_FUNC_DEF:  return visit_func_def  (node);
		case AST_FUNC_CALL: return visit_func_call (node);

		case AST_STR:       return visit_string    (node);

		case AST_COMPOUND:  return visit_compound  (node);

		case AST_NOOP:      return node;

		default:
			printf ("Incorrect statement of type \"%d\"\n", node -> type);
			exit (1);
			return ast_init (NOOP);
	}
}

AST * visit_var_def   (AST * node)
{
	scope_add_var_def (node->scope, node);
	return node;
}

AST * visit_func_def  (AST * node)
{
	scope_add_func_def (node->scope, node);
	return node;
}

AST * visit_var       (AST * node)
{
	AST * vd = scope_get_var_def (node -> scope, node -> var_name);

	if (vd != NULL) return visit (vd -> var_def_val);

	printf ("Undefined variable \"%s\"\n", node -> var_name);
	exit (1);
}

AST * visit_func_call (AST * node)
{
	if      (strcmp (node -> func_name, "print") == 0)
		return ;
	
	AST * fd = scope_get_func_def (node -> scope, node -> func_name);

	if (fd == NULL) {
		printf("Undefined function \"%s\"\n", node -> func_name);
		exit (1);
	}

	for (int i = 0; i < (int) node -> func_call_arg_size; i++) {
		AST * var   = fd   -> func_def_args [i];
		AST * value = node -> func_call_args [i];
		AST * var_def = ast_init (AST_VAR_DEF);
		
		var_def -> var_def_val  = value;
		var_def -> var_def_name = malloc ( (strlen (var -> var_name) + 1) * sizeof (char));
		strcpy (var_def -> var_def_name, var -> var_name);

		scope_add_var_def (fd -> func_def_body -> scope, var_def);
	}

	return visit (fd -> func_def_body);

}

AST * visit_string    (AST * node)
{
	return node;
}


AST * visit_compund   (AST * node)
{
	for (int i = 0; i < node -> compound_size; i++)
		visit (node -> compound_value [i]);

	return ast_init (AST_NOOP);
}