#include "parser.h"

Parser * parser_init (Lexer * lxr)
{
	Parser * psr = malloc (sizeof (Parser));

	psr -> lexer = lxr;
	psr -> cur_token = lexer_get_token (lxr);
	psr -> prev_token = psr -> cur_token;

	psr -> scope = scope_init ();
}

void parser_eat (Parser * psr, int tkn_type)
{
	if (psr -> cur_token -> type == tkn_type) {
		psr -> prev_token = psr -> cur_token;
		psr -> cur_token  = lexer_get_token (psr -> lexer);
	} else {
		printf
		(
			"Syntax error: unexpected token \"%s\"\n",
			psr -> cur_token -> value,
		);

		exit (0);
	}
}

AST * parser_parse (Parser * psr, Scope * scp)
{
	return parser_statements (psr, scp);
}

AST * parser_statement  (Parser * psr, Scope * scp)
{
	switch (psr -> cur_token -> type) {
		case TOKE_ID:
			return parser_parse_id (psr, scp);

		default:
			return ast_init (AST_NOOP);
	}
}

AST * parser_statements (Parser * psr, Scope * scp)
{
	AST * cmp = ast_init (AST_COMPOUND);
	AST * statement = parser_statement (psr, scp);

	cmp -> scope = scp;
	cmp -> compound_value = malloc (sizeof (AST *));

	statement -> scope = scp;

	cmp -> compound_value [0] = statement;
	cmp -> compound_size ++;

	while (psr -> cur_token -> type == TOKEN_SEMI) {
		parser_eat (psr, TOKEN_SEMI);

		statement = parser_statements (psr, scp);

		if (statement) {
			cmp -> compound_size ++;
			cmp -> compound_value = realloc
			(
				cmp -> compound_value,
				cmp -> compound_size * sizeof (AST *)
			);

			cmp -> compound_value [cmp -> compound_size - 1] = statement;
		}
	}

	return cmp;
}

AST * parser_expr (Parser * psr, Scope * scp)
{
	switch (psr -> cur_token -> type) {
		case TOKEN_STR:
			return parser_parse_str (psr, scp);

		case TOKEN_ID:
			return parser_parse_id  (psr, scp);

		default:
			return ast_init (AST_NOOP);
	}
}

AST * parser_factor (Parser * psr, Scope * scp)
{
}

AST * parser_term (Parser * psr, Scope * scp)
{
}

AST * parser_func_call (Parser * psr, Scope * scp)
{
	AST * func_call = ast_init (AST_FUNC_CALL);

	func_call -> func_name = psr -> prev_token -> value;

	parser_eat (psr, TOKEN_LPAR);

	func_call -> func_call_args = malloc (sizeof (AST *));

	AST * expr = parser_expr (psr, scp);

	func_call -> func_call_args [0] = expr;
	func_call -> func_call_arg_size ++;

	while (psr -> cur_token -> type == TOKEN_COMMA) {
		parser_eat (psr, TOKEN_COMMA);

		expr = parser_expr (psr, scp);

		func_call -> func_call_arg_size ++;
		func_call -> func_call_args = realloc
		(
			func_call_args,
			func_call_arg_size * sizeof (AST *)
		);
		func_call -> func_call_args [func_call -> func_call_arg_size - 1] = expr;
	}

	parser_eat (psr, TOKEN_RPAR);

	func_call -> scp = scp;

	return func_call;
}

AST * parser_func_def (Parser * psr, Scope * scp)
{
	AST * ast = ast_init (AST_FUNC_DEF);
	parser_eat (psr, TOKEN_ID);

	char * func_name = psr -> cur_token -> value;

	ast -> func_def_name = malloc (sizeof (char) * (strlen (func_name) + 1));

	strcpy (ast -> func_def_name, func_name);

	parser_eat (psr, TOKEN_ID);
	parser_eat (psr, TOKEN_LPAR);

	ast -> func_def_args = malloc (sizeof (AST *));

	AST * arg = parser_var (psr, scp);

	ast -> func_def_args_size ++;
	ast -> func_def_args [ast -> func_def_args_size - 1] = arg;

	while (psr -> cur_token -> type == TOKEN_COMMA) {
		parser_eat (psr, TOKEN_COMMA);

		ast -> func_def_args_size ++;
		ast -> func_def_args = realloc
		(
			ast -> func_def_args,
			ast -> func_def_args_size * sizeof (AST *)
		);

		arg = parser_var (psr, scp);

		ast -> func_def_args [ast -> func_def_args_size - 1] = arg;
	}

	parser_eat (psr, TOKEN_RPAR);

	parser_eat (psr, TOKEN_LBRACE);

	ast -> func_def_body = parser_statements (psr, scp);

	parser_eat (psr, TOKEN_RBRACE);

	ast -> scope = scp;

	return ast;
}

AST * parser_var (Parser * psr, Scope * scp)
{
	parser_eat (psr, TOKEN_ID);

	if (psr -> cur_token -> type == TOKEN_LPAR)
		return parser_func_call (psr, scp);

	AST * var = ast_init (AST_VAR);

	var -> var_name = psr -> cur_token -> value;
	var -> scope = scp;

	return var;
}

AST * parser_var_def (Parser * psr, Scope * scp)
{
	parser_eat (psr, TOKEN_ID);

	char * var_name = psr -> cur_token -> value;

	parser_eat (psr, TOKE_ID);

	parser_eat (psr, TOKEN_EQUAL);

	AST * var_val = parser_expr (psr, scp);
	AST * var_def = ast_init (AST_VAR_DEF);

	var_def -> var_def_name = var_name;
}

AST * parser_parse_str (Parser * psr, Scope * scp);

AST * parser_parse_id (Parser * psr, Scope * scp);
