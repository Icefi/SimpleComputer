#include <stdio.h>

#include "sc_simple_assembler.h"

int main (int argc, char** argv)
{
    if (argc == 1 || argc > 3) {
        printf ("Usage: ./sambr <input>.sambr [output]");
        return 0;
    }

    translate (argv[1], argv[2] == NULL ? "out.sbin" : argv[2]);

    return 0;
}
