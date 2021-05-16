#include <stdio.h>

#include "lexer.h"

int main (int argc, char** argv)
{
    Lexer * lexer = lexer_init (
        "var name = \"Nik doe\";\n"
        "print (name);"
    );

    Token * token = (void*)0;

    while ((token = lexer_get_token (lexer)) != (void*)0) {
        printf ("TOKEN (%d, %s);\n", token->type, token->value);
    }

    return 0;
}
