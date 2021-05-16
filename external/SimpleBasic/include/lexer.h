#ifndef LEXER_H
#define LEXER_H

/** TOKEN **/

typedef struct
{
    enum
    {
        TOKEN_ID,
        TOKEN_EQUAL,
        TOKEN_STRING,
        TOKEN_SEMI,

        TOKEN_LPAR,
        TOKEN_RPAR,

        TOKEN_LBRACE,
        TOKEN_RBRACE,

        TOKEN_COMMA,
        TOKEN_EOF,

    } type;

    char* value;

} Token;


Token* token_init (int type, char* value);

/** LEXER **/

typedef struct {

    char c;
    unsigned int i;
    char * content;

} Lexer;


Lexer* lexer_init (char * content);


void lexer_advance     (Lexer * lxr);

void lexer_spaces_skip (Lexer * lxr);


Token* lexer_get_token   (Lexer * lxr);

Token* lexer_collect_str (Lexer * lxr);

Token* lexer_collect_id  (Lexer * lxr);


Token* lexer_advance_with_token (Lexer * lxr, Token * tkn);


char* lexer_get_current_char (Lexer * lxr);

#endif
