#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

Token* token_init (int type, char * value)
{
    Token* tkn = malloc (sizeof (Token));

    tkn->type  = type;
    tkn->value = value;

    return tkn;
}


Lexer* lexer_init (char * content)
{
    Lexer* lxr = malloc (sizeof (Lexer));

    lxr -> content = content;
    lxr -> i = 0;
    lxr -> c = content [lxr -> i];

    return lxr;
}


void lexer_advance     (Lexer * lxr)
{
    if (lxr == NULL) return;

    if (lxr->c != '\0' && lxr -> i < strlen (lxr -> content)) {
        lxr -> i ++;
        lxr -> c = lxr->content [lxr -> i];
    }
}

void lexer_spaces_skip (Lexer * lxr)
{
    if (lxr == NULL) return;

    while (lxr -> c == ' ' || lxr -> c == 10) {
        lexer_advance (lxr);
    }
}


Token* lexer_get_token   (Lexer * lxr)
{
    while (lxr -> c != '\0' && lxr -> i < strlen (lxr -> content)) {
        if (lxr -> c == ' ' || lxr -> c == 10) lexer_spaces_skip (lxr);

        if (isalnum (lxr -> c)) return lexer_collect_id (lxr);

        if (lxr -> c == '"') return lexer_collect_str (lxr);

        switch (lxr -> c) {
            case '=': return lexer_advance_with_token ( lxr, token_init ( TOKEN_EQUAL,  lexer_get_current_char ( lxr ) ) ); break;
            case ';': return lexer_advance_with_token ( lxr, token_init ( TOKEN_SEMI,   lexer_get_current_char ( lxr ) ) ); break;
            case '(': return lexer_advance_with_token ( lxr, token_init ( TOKEN_LPAR,   lexer_get_current_char ( lxr ) ) ); break;
            case ')': return lexer_advance_with_token ( lxr, token_init ( TOKEN_RPAR,   lexer_get_current_char ( lxr ) ) ); break;
            case '{': return lexer_advance_with_token ( lxr, token_init ( TOKEN_LBRACE, lexer_get_current_char ( lxr ) ) ); break;
            case '}': return lexer_advance_with_token ( lxr, token_init ( TOKEN_RBRACE, lexer_get_current_char ( lxr ) ) ); break;
            case ',': return lexer_advance_with_token ( lxr, token_init ( TOKEN_COMMA,  lexer_get_current_char ( lxr ) ) ); break;
        }
    }
}

Token* lexer_collect_str (Lexer * lxr)
{
    lexer_advance (lxr);

    char * value = malloc (sizeof (char));

    value [0] = '\0';

    while (lxr -> c != '"') {
        char * s = lexer_get_current_char (lxr);

        value = realloc (value, (strlen (value) + strlen (s) + 1) * sizeof (char));

        strcat (value, s);

        lexer_advance (lxr);
    }

    lexer_advance (lxr);

    return token_init (TOKEN_STRING, value);
}

Token* lexer_collect_id  (Lexer * lxr)
{
    char * value = malloc (sizeof (char));

    value [0] = '\0';

    while (isalnum (lxr -> c)) {
        char * s = lexer_get_current_char (lxr);

        value = realloc (value, (strlen (value) + strlen (s) + 1) * sizeof (char));

        strcat (value, s);

        lexer_advance (lxr);
    }

    return token_init (TOKEN_ID, value);
}


Token* lexer_advance_with_token (Lexer * lxr, Token * tkn)
{
    lexer_advance (lxr);

    return tkn;
}


char*  lexer_get_current_char (Lexer * lxr)
{
    char * str = malloc (2 * sizeof (char));

    str [0] = lxr -> c;
    str [1] = '\0';

    return str;
}
