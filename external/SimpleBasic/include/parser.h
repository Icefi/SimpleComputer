#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "AST.h"
#include "scope.h"

typedef struct PARSER
{
    Lexer * lexer;
    Token * cur_token;
    Token * prev_token;
    Scope * scope;

} Parser;

Parser * parser_init (Lexer * lxr);

void parser_eat (Parser * psr, int tkn);

AST * parser_parse (Parser * psr);

AST * parser_statement  (Parser * psr, Scope * scp);

AST * parser_statements (Parser * psr, Scope * scp);

AST * parser_expr (Parser * psr, Scope * scp);

AST * parser_factor (Parser * psr, Scope * scp);

AST * parser_term (Parser * psr, Scope * scp);

AST * parser_func_call (Parser * psr, Scope * scp);

AST * parser_func_def (Parser * psr, Scope * scp);

AST * parser_var (Parser * psr, Scope * scp);

AST * parser_var_def (Parser * psr, Scope * scp);

AST * parser_parse_str (Parser * psr, Scope * scp);

AST * parser_parse_id (Parser * psr, Scope * scp);

#endif
